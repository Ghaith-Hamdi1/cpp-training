package com.cppquiz

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
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
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

/**
 * Daily review of recap cards. Read the question, answer in your head, reveal, then grade yourself.
 * [onGrade] saves each answer; [onClose] ends the review (also used by the X before finishing).
 */
@Composable
fun CardReview(
    deck: List<RecapCard>, onGrade: (RecapCard, Boolean) -> Unit, onClose: () -> Unit,
    label: String = "Recap card", doneTitle: String = "Review done!",
    waitText: String = "Answer in your head first, then reveal.",
    doneText: (total: Int, again: Int) -> String = { t, a -> "$t card${if (t == 1) "" else "s"} reviewed, $a to see again tomorrow." },
) {
    var idx by remember { mutableIntStateOf(0) }
    var revealed by remember { mutableStateOf(false) }
    var again by remember { mutableIntStateOf(0) }

    if (idx >= deck.size) {
        CardsDone(doneTitle, doneText(deck.size, again), onClose)
        return
    }
    val card = deck[idx]
    Column(Modifier.fillMaxSize().background(C.Bg)) {
        Row(
            Modifier.fillMaxWidth().background(C.Bar).padding(horizontal = 16.dp, vertical = 14.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            Text("✕", color = C.Dim, fontSize = 26.sp, modifier = Modifier.clickable(onClick = onClose).padding(end = 14.dp))
            Box(Modifier.weight(1f)) { ProgressPill(idx / deck.size.toFloat()) }
        }
        Column(Modifier.weight(1f).verticalScroll(rememberScrollState()).padding(20.dp)) {
            Text("$label ${idx + 1} of ${deck.size}", color = C.Dim, fontSize = 14.sp)
            Spacer(Modifier.height(10.dp))
            Text(md(card.question), color = Color.White, fontSize = 22.sp, lineHeight = 30.sp, fontWeight = FontWeight.SemiBold)
            Spacer(Modifier.height(20.dp))
            if (revealed) {
                Column(Modifier.fillMaxWidth().background(C.Bar, RoundedCornerShape(20.dp)).padding(16.dp)) {
                    Text(md(card.answer), color = Color.White, fontSize = 17.sp, lineHeight = 26.sp)
                }
            } else {
                Text(waitText, color = C.Dim, fontSize = 16.sp)
            }
        }
        Box(Modifier.fillMaxWidth().background(C.Bar).padding(16.dp)) {
            if (!revealed) {
                Chunky("Show answer", onClick = { revealed = true })
            } else {
                Row(horizontalArrangement = Arrangement.spacedBy(12.dp)) {
                    Box(Modifier.weight(1f)) {
                        Chunky("Again", face = C.Red, edge = Color(0xFF9E3037), onClick = {
                            onGrade(card, false); again++; idx++; revealed = false
                        })
                    }
                    Box(Modifier.weight(1f)) {
                        Chunky("Got it", onClick = { onGrade(card, true); idx++; revealed = false })
                    }
                }
            }
        }
    }
}

@Composable
private fun CardsDone(title: String, text: String, onClose: () -> Unit) {
    Column(Modifier.fillMaxSize().background(C.Bg).padding(20.dp), horizontalAlignment = Alignment.CenterHorizontally) {
        Spacer(Modifier.weight(1f))
        Mascot(170.dp, Mood.HAPPY)
        Spacer(Modifier.height(20.dp))
        Text(title, color = Color.White, fontSize = 30.sp, fontWeight = FontWeight.Bold)
        Spacer(Modifier.height(12.dp))
        Text(
            text,
            color = C.Dim, fontSize = 17.sp, textAlign = TextAlign.Center,
        )
        Spacer(Modifier.weight(1f))
        Chunky("Continue", onClick = onClose)
    }
}
