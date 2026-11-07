package com.cppquiz

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlin.random.Random

/** The placement check: a few questions per chapter, chapters passed in order are marked done. */
object Placement {
    const val PER_CHAPTER = 4
    const val PASS = 3

    /** The first five chapters are tested; concurrency and the boss puzzles are never skipped. */
    val chapters: List<Chapter> get() = Content.readyChapters.take(5)

    /** Picks questions from different lessons of the chapter, plain multiple choice only. */
    fun questionIds(ch: Chapter, rnd: Random): List<String> {
        val pool = ch.nodes.map { n ->
            n.items.filter {
                Content.build(it) == null && Content.puzzle(it) == null && !it.startsWith("v:") &&
                    Content.question(it).type != QType.TRUE_FALSE
            }
        }.filter { it.isNotEmpty() }.shuffled(rnd)
        val picked = mutableListOf<String>()
        var round = 0
        while (picked.size < PER_CHAPTER && pool.isNotEmpty() && round < 60) {
            val free = pool[round % pool.size].filter { it !in picked }
            if (free.isNotEmpty()) picked += free.random(rnd)
            round++
        }
        return picked
    }
}

/** One chapter's outcome: its title, correct answers, asked questions and whether it was skipped. */
class PlacementRow(val chapter: Chapter, val correct: Int, val asked: Int, val skipped: Boolean)

@Composable
fun PlacementBanner(onStart: () -> Unit, onDismiss: () -> Unit) {
    Column(
        Modifier.fillMaxWidth().padding(horizontal = 14.dp, vertical = 10.dp)
            .background(C.Card, RoundedCornerShape(24.dp)).padding(18.dp),
    ) {
        Text("Already know some C++?", color = Color.White, fontSize = 20.sp, fontWeight = FontWeight.Bold)
        Text(
            "Take a 20-question check and skip the chapters you already know.",
            color = C.Dim, fontSize = 15.sp, lineHeight = 21.sp, modifier = Modifier.padding(top = 4.dp, bottom = 14.dp),
        )
        Chunky("Take the check", onClick = onStart)
        Text(
            "Not now", color = Color(0xFFB79CF2), fontSize = 16.sp, textAlign = TextAlign.Center,
            modifier = Modifier.fillMaxWidth().clickable(onClick = onDismiss).padding(top = 12.dp),
        )
    }
}

@Composable
fun PlacementResult(rows: List<PlacementRow>, onContinue: () -> Unit) {
    val skipped = rows.count { it.skipped }
    Column(Modifier.fillMaxSize().background(C.Bg).padding(20.dp)) {
        Column(Modifier.weight(1f).verticalScroll(rememberScrollState()), horizontalAlignment = Alignment.CenterHorizontally) {
            Spacer(Modifier.height(24.dp))
            Mascot(120.dp, Mood.HAPPY)
            Spacer(Modifier.height(16.dp))
            Text("Check complete!", color = Color.White, fontSize = 28.sp, fontWeight = FontWeight.Bold)
            Text(
                if (skipped == 0) "You will start from chapter 1." else "You skip $skipped chapter${if (skipped == 1) "" else "s"}.",
                color = C.Dim, fontSize = 17.sp, modifier = Modifier.padding(top = 6.dp, bottom = 18.dp),
            )
            rows.forEach { r ->
                Row(
                    Modifier.fillMaxWidth().padding(vertical = 5.dp).background(C.Card, RoundedCornerShape(16.dp)).padding(16.dp),
                    verticalAlignment = Alignment.CenterVertically,
                ) {
                    Column(Modifier.weight(1f)) {
                        Text(r.chapter.title, color = Color.White, fontSize = 16.sp, fontWeight = FontWeight.SemiBold)
                        Text(
                            if (r.skipped) "Skipped: you know this" else "Start here when you reach it",
                            color = if (r.skipped) C.Green else C.Dim, fontSize = 14.sp,
                        )
                    }
                    Text("${r.correct}/${r.asked}", color = Color.White, fontSize = 20.sp, fontWeight = FontWeight.Bold)
                }
            }
            Spacer(Modifier.height(8.dp))
        }
        Chunky("Continue", onClick = onContinue)
    }
}
