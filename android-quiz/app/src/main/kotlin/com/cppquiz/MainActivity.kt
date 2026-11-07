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

private class Session(val lessonIndex: Int?, val steps: List<Step>)

private fun lessonSession(index: Int): Session {
    val l = chapterOne.lessons[index]
    val rnd = Random(System.nanoTime())
    val steps = l.intro.map { Step.Info(it) } + l.questionIds.map { stepFor(it, rnd) }
    return Session(index, steps)
}

/** Practice from mistakes, or a mixed set when nothing is missed. */
private fun reviewSession(store: Store): Session {
    val rnd = Random(System.nanoTime())
    val pool = if (store.missed.isNotEmpty()) store.missed.toList() else allStepIds
    val ids = pool.shuffled(rnd).take(10)
    return Session(null, ids.map { stepFor(it, rnd) })
}

@Composable
private fun App(store: Store) {
    var tab by remember { mutableIntStateOf(0) }
    var session by remember { mutableStateOf<Session?>(null) }
    var result by remember { mutableStateOf<List<Pair<Int, Boolean>>?>(null) }
    var chapterDone by remember { mutableStateOf(false) }
    var showChapter by remember { mutableStateOf(false) }

    val s = session
    val r = result
    when {
        showChapter -> {
            BackHandler { showChapter = false }
            ChapterComplete(chapterOne.title, CHAPTER_BONUS, lockedChapters.firstOrNull()) { showChapter = false }
        }
        r != null -> {
            BackHandler { result = null }
            LessonResult(r) {
                result = null
                if (chapterDone) { chapterDone = false; showChapter = true }
            }
        }
        s != null -> {
            BackHandler { }
            LessonRunner(
                steps = s.steps,
                onQuit = { session = null },
                onDone = { res, recovered ->
                    chapterDone = store.finish(s.lessonIndex, res, recovered)
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
                        onLesson = { session = lessonSession(it) },
                        onPracticeChapter = { session = reviewSession(store) },
                    )
                    1 -> PracticeScreen(
                        store,
                        onStartMistakes = { session = reviewSession(store) },
                        onStartLesson = { session = lessonSession(it) },
                    )
                    else -> ProfileScreen(store)
                }
            }
            BottomNav(tab) { tab = it }
        }
    }
}
