package com.cppquiz

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.BackHandler
import androidx.activity.compose.setContent
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.safeDrawingPadding
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.darkColorScheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import kotlin.random.Random

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Content.load(applicationContext)
        val store = Store(applicationContext)
        setContent {
            MaterialTheme(colorScheme = darkColorScheme()) {
                Surface(Modifier.fillMaxSize(), color = C.Bg) {
                    Box(Modifier.safeDrawingPadding().background(C.Bg)) { App(store) }
                }
            }
        }
    }
}

private class Session(val nodeId: String?, val steps: List<Step>)

private fun nodeSession(nodeId: String): Session {
    val node = Content.node(nodeId)!!
    val rnd = Random(System.nanoTime())
    val steps = node.intro.map { Step.Info(it) } + node.items.map { stepFor(it, rnd) }
    return Session(nodeId, steps)
}

/** A short review: missed items first, else items of lessons already finished, else anything in [fallback]. */
private fun reviewSession(store: Store, scope: List<String>, fallback: List<String>, size: Int): Session {
    val rnd = Random(System.nanoTime())
    val missed = scope.filter { it in store.missed }
    val seen = scope.filter { id -> Content.readyNodes.any { it.id in store.completed && id in it.items } }
    val pool = missed.ifEmpty { seen }.ifEmpty { fallback }
    return Session(null, pool.shuffled(rnd).take(size).map { stepFor(it, rnd) })
}

@Composable
private fun App(store: Store) {
    var tab by remember { mutableIntStateOf(0) }
    var session by remember { mutableStateOf<Session?>(null) }
    var result by remember { mutableStateOf<List<Pair<String, Boolean>>?>(null) }
    var chapterDone by remember { mutableStateOf<Chapter?>(null) }
    var showChapter by remember { mutableStateOf<Chapter?>(null) }
    var deck by remember { mutableStateOf<List<RecapCard>?>(null) }

    val s = session
    val r = result
    val sc = showChapter
    val dk = deck
    when {
        dk != null -> {
            BackHandler { deck = null }
            CardReview(dk, onGrade = { c, good -> store.gradeCard(c.id, good) }, onClose = { deck = null })
        }
        sc != null -> {
            BackHandler { showChapter = null }
            val next = Content.chapters.getOrNull(Content.chapters.indexOf(sc) + 1)
            val nextText = next?.let { it.title + if (it.ready) "" else " (coming soon)" }
            ChapterComplete(sc.title, CHAPTER_BONUS, nextText) { showChapter = null }
        }
        r != null -> {
            BackHandler { result = null }
            LessonResult(r) {
                result = null
                chapterDone?.let { showChapter = it; chapterDone = null }
            }
        }
        s != null -> {
            BackHandler { }
            LessonRunner(
                steps = s.steps,
                onQuit = { session = null },
                onDone = { res, recovered ->
                    chapterDone = store.finish(s.nodeId, res, recovered)
                    session = null
                    result = res
                },
            )
        }
        else -> Column(Modifier.fillMaxSize()) {
            if (tab == 0) TopStats(store)
            Box(Modifier.weight(1f)) {
                when (tab) {
                    0 -> LearnScreen(
                        store,
                        onNode = { session = nodeSession(it) },
                        onPracticeChapter = { ch ->
                            val items = ch.nodes.flatMap { it.items }
                            session = reviewSession(store, items, items, 8)
                        },
                    )
                    1 -> PracticeScreen(
                        store,
                        onStartMistakes = {
                            session = reviewSession(store, Content.allReadyItems, Content.allReadyItems, 10)
                        },
                        onStartNode = { session = nodeSession(it) },
                        onStartCards = { deck = store.dueCards().mapNotNull { Content.card(it) }.shuffled() },
                    )
                    else -> ProfileScreen(store)
                }
            }
            BottomNav(tab) { tab = it }
        }
    }
}
