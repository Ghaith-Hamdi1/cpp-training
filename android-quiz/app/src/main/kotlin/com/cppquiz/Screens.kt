package com.cppquiz

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.ExperimentalFoundationApi
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.LazyRow
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.drawBehind
import androidx.compose.ui.geometry.CornerRadius
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.Path
import androidx.compose.ui.graphics.PathEffect
import androidx.compose.ui.graphics.StrokeCap
import androidx.compose.ui.graphics.StrokeJoin
import androidx.compose.ui.graphics.drawscope.Stroke
import android.Manifest
import android.os.Build
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.material3.Switch
import androidx.compose.material3.SwitchDefaults
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.platform.LocalUriHandler
import androidx.compose.ui.text.style.TextDecoration
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.IntOffset
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlin.math.roundToInt

@Composable
fun StatChip(icon: String, value: String, modifier: Modifier = Modifier) {
    Row(
        modifier.background(C.Card, RoundedCornerShape(18.dp)).padding(vertical = 14.dp),
        horizontalArrangement = Arrangement.Center, verticalAlignment = Alignment.CenterVertically,
    ) {
        Text(icon, fontSize = 22.sp)
        Spacer(Modifier.width(8.dp))
        Text(value, color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold)
    }
}

@Composable
fun TopStats(store: Store) {
    Row(
        Modifier.fillMaxWidth().background(C.Bar).padding(horizontal = 16.dp, vertical = 12.dp),
        horizontalArrangement = Arrangement.spacedBy(12.dp),
    ) {
        StatChip("⚡", "${store.xp}", Modifier.weight(1f))
        StatChip("✅", "${store.completed.size}", Modifier.weight(1f))
        StatChip("🔥", "${store.liveStreak}", Modifier.weight(1f))
    }
}

private enum class NodeKind { DONE, OPEN, LOCKED, PRACTICE }

@Composable
private fun PathNode(kind: NodeKind, current: Boolean, onClick: () -> Unit) {
    val face = when (kind) {
        NodeKind.DONE -> C.Purple
        NodeKind.LOCKED -> Color(0xFF3A3C68)
        else -> C.Card
    }
    val shape = if (kind == NodeKind.PRACTICE) CircleShape else RoundedCornerShape(26.dp)
    val ring = Color(0xFF7A63B0)
    Box(
        Modifier.size(96.dp)
            .drawBehind {
                if (current) {
                    val r = 16.dp.toPx()
                    drawRoundRect(
                        ring, Offset(-r, -r), Size(size.width + 2 * r, size.height + 2 * r),
                        CornerRadius(40.dp.toPx()), style = Stroke(4.dp.toPx()),
                    )
                }
            }
            .background(C.CardDark, shape)
            .clickable(enabled = kind != NodeKind.LOCKED, onClick = onClick),
    ) {
        Box(Modifier.size(96.dp, 90.dp).background(face, shape), contentAlignment = Alignment.Center) {
            when (kind) {
                NodeKind.DONE -> Text("✓", color = Color.White, fontSize = 44.sp, fontWeight = FontWeight.Bold)
                NodeKind.LOCKED -> Text("🔒", fontSize = 34.sp)
                NodeKind.PRACTICE -> Text("⚡", fontSize = 38.sp)
                NodeKind.OPEN -> Canvas(Modifier.size(40.dp)) {
                    val p = Path().apply {
                        moveTo(size.width * .22f, size.height * .06f)
                        lineTo(size.width * .94f, size.height * .5f)
                        lineTo(size.width * .22f, size.height * .94f)
                        close()
                    }
                    drawPath(p, Color.White)
                }
            }
        }
    }
}

private val nodeFractions = floatArrayOf(0.5f, 1f, 0.5f, 0f)

@Composable
private fun ChapterPath(
    chapter: Chapter, store: Store, firstOpen: String?, onNode: (String) -> Unit, onPractice: () -> Unit,
) {
    val nodeCount = chapter.nodes.size + 1
    val step = 150.dp
    BoxWithConstraints(Modifier.fillMaxWidth().height(step * (nodeCount - 1) + 96.dp + 56.dp)) {
        val density = LocalDensity.current
        val wPx = with(density) { maxWidth.toPx() }
        val nodePx = with(density) { 96.dp.toPx() }
        val margin = with(density) { 20.dp.toPx() }
        val stepPx = with(density) { step.toPx() }
        val topPx = with(density) { 28.dp.toPx() }
        val left = margin + nodePx / 2
        val right = wPx - margin - nodePx / 2
        fun cx(i: Int) = left + (right - left) * nodeFractions[i % nodeFractions.size]
        fun cy(i: Int) = topPx + nodePx / 2 + stepPx * i

        Canvas(Modifier.fillMaxSize()) {
            val gap = 77.dp.toPx()
            var y = gap / 2
            while (y < size.height) {
                var x = gap / 2
                while (x < size.width) { drawCircle(C.Dot, 6.dp.toPx(), Offset(x, y)); x += gap }
                y += gap
            }
            val stroke = Stroke(
                10.dp.toPx(), cap = StrokeCap.Round, join = StrokeJoin.Round,
                pathEffect = PathEffect.cornerPathEffect(60.dp.toPx()),
            )
            for (i in 0 until nodeCount - 1) {
                val a = Offset(cx(i), cy(i)); val b = Offset(cx(i + 1), cy(i + 1))
                val path = Path().apply {
                    moveTo(a.x, a.y)
                    if (i % 2 == 0) lineTo(b.x, a.y) else lineTo(a.x, b.y)
                    lineTo(b.x, b.y)
                }
                drawPath(path, C.Path, style = stroke)
            }
        }
        for (i in 0 until nodeCount) {
            val isPractice = i == chapter.nodes.size
            val node = chapter.nodes.getOrNull(i)
            val kind = when {
                isPractice -> NodeKind.PRACTICE
                node!!.id in store.completed -> NodeKind.DONE
                node.id == firstOpen -> NodeKind.OPEN
                else -> NodeKind.LOCKED
            }
            Box(Modifier.offset { IntOffset((cx(i) - nodePx / 2).roundToInt(), (cy(i) - nodePx / 2).roundToInt()) }) {
                PathNode(kind, current = node != null && node.id == firstOpen, onClick = { if (node == null) onPractice() else onNode(node.id) })
            }
        }
    }
}

@OptIn(ExperimentalFoundationApi::class)
@Composable
fun LearnScreen(store: Store, onNode: (String) -> Unit, onPracticeChapter: (Chapter) -> Unit, onPlacement: () -> Unit) {
    var sheet by remember { mutableStateOf<Chapter?>(null) }
    val firstOpen = Content.readyNodes.firstOrNull { it.id !in store.completed }?.id
    Box(Modifier.fillMaxSize()) {
        LazyColumn(Modifier.fillMaxSize()) {
            if (!store.placementDone && store.completed.isEmpty()) {
                item(key = "placement") { PlacementBanner(onStart = onPlacement, onDismiss = { store.setPlacementDone() }) }
            }
            item(key = "goal") { DailyGoalCard(store) }
            for (ch in Content.readyChapters) {
                stickyHeader(key = "h-" + ch.id) {
                    val done = ch.nodes.count { it.id in store.completed }
                    ChapterHeader("C++", ch.title, done / ch.nodes.size.toFloat())
                }
                item(key = "p-" + ch.id) {
                    ChapterPath(ch, store, firstOpen, onNode, onPractice = { sheet = ch })
                }
            }
            items(Content.chapters.filter { !it.ready }, key = { "l-" + it.id }) { ch ->
                Column(Modifier.padding(horizontal = 16.dp, vertical = 10.dp)) {
                    Box(Modifier.fillMaxWidth().background(C.CardDark, RoundedCornerShape(26.dp)).padding(2.dp)) {
                        Column(
                            Modifier.fillMaxWidth().background(Color(0xFF1B1D38), RoundedCornerShape(24.dp)).padding(20.dp),
                        ) {
                            Text("Coming soon", color = C.Dim, fontSize = 14.sp)
                            Spacer(Modifier.height(6.dp))
                            Text(ch.title, color = Color(0xFF6A6C95), fontSize = 24.sp, fontWeight = FontWeight.Bold)
                        }
                    }
                }
            }
            item { Spacer(Modifier.height(24.dp)) }
        }
        sheet?.let { ch ->
            val done = ch.nodes.count { it.id in store.completed }
            Box(Modifier.fillMaxSize().background(Color(0xAA000000)).clickable { sheet = null }) {
                Column(
                    Modifier.align(Alignment.Center).padding(24.dp).fillMaxWidth()
                        .background(Color(0xFF1B1D38), RoundedCornerShape(28.dp)).clickable(enabled = false) {}
                        .padding(22.dp),
                    verticalArrangement = Arrangement.spacedBy(10.dp),
                ) {
                    Text("PRACTICE OPTIONAL", color = Color.White, fontSize = 15.sp, fontWeight = FontWeight.SemiBold)
                    Text(ch.title.substringAfter(". "), color = Color.White, fontSize = 28.sp, fontWeight = FontWeight.Bold)
                    Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.SpaceBetween) {
                        Text("CHAPTER", color = Color.White, fontSize = 15.sp, fontWeight = FontWeight.SemiBold)
                        Text("$done/${ch.nodes.size}", color = Color.White, fontSize = 15.sp, fontWeight = FontWeight.SemiBold)
                    }
                    ProgressPill(done / ch.nodes.size.toFloat(), track = C.Bar)
                    Spacer(Modifier.height(4.dp))
                    Chunky("Start practicing", onClick = { sheet = null; onPracticeChapter(ch) })
                }
            }
        }
    }
}

@Composable
private fun ChapterHeader(course: String, title: String, progress: Float) {
    Box(Modifier.fillMaxWidth().background(C.Bg).padding(horizontal = 14.dp, vertical = 10.dp)) {
        Box(Modifier.fillMaxWidth().background(C.CardDark, RoundedCornerShape(30.dp)).padding(bottom = 10.dp)) {
            Column(
                Modifier.fillMaxWidth().background(C.Card, RoundedCornerShape(30.dp)).padding(20.dp),
            ) {
                Text(course, color = C.Dim, fontSize = 20.sp)
                Spacer(Modifier.height(4.dp))
                Text(title, color = Color.White, fontSize = 26.sp, fontWeight = FontWeight.Bold)
                Spacer(Modifier.height(18.dp))
                ProgressPill(progress, height = 12.dp)
            }
        }
    }
}

@Composable
fun PracticeScreen(
    store: Store, onStartMistakes: () -> Unit, onStartNode: (String) -> Unit, onStartCards: () -> Unit,
    onInterview: () -> Unit,
) {
    val n = store.missed.size
    val due = store.dueCards().size
    val done = Content.readyNodes.filter { it.id in store.completed }
    Column(Modifier.fillMaxSize().verticalScroll(rememberScrollState())) {
        Column(
            Modifier.fillMaxWidth().background(Color(0xFFE9DDFF)).padding(20.dp),
        ) {
            Text(
                "DAILY REVIEW", color = Color.White, fontSize = 13.sp, fontWeight = FontWeight.Bold,
                modifier = Modifier.background(C.Bar, RoundedCornerShape(50)).padding(horizontal = 12.dp, vertical = 6.dp),
            )
            Spacer(Modifier.height(12.dp))
            Text(
                if (n > 0) "Fix your $n missed question${if (n == 1) "" else "s"}" else "Mixed review",
                color = Color(0xFF232846), fontSize = 26.sp, fontWeight = FontWeight.Bold,
            )
            Text("⚡ ${if (n > 0) minOf(n, 10) else 10} questions", color = Color(0xFF232846), fontSize = 16.sp)
            Spacer(Modifier.height(16.dp))
            Chunky("Start now", onClick = onStartMistakes)
        }
        Spacer(Modifier.height(20.dp))
        Column(
            Modifier.padding(horizontal = 20.dp).fillMaxWidth().background(C.Card, RoundedCornerShape(24.dp)).padding(18.dp),
        ) {
            Text("RECAP CARDS", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
            Spacer(Modifier.height(6.dp))
            Text(
                if (due > 0) "$due card${if (due == 1) "" else "s"} due today" else "No cards due",
                color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold,
            )
            Text(
                if (store.cards.isEmpty()) "Finish a lesson and its cheat-sheet cards come back here 1, 3, 7, 14 and 30 days later."
                else "${store.cards.size} cards in your review boxes.",
                color = C.Dim, fontSize = 15.sp, modifier = Modifier.padding(top = 4.dp),
            )
            if (due > 0) {
                Spacer(Modifier.height(14.dp))
                Chunky("Review cards", onClick = onStartCards)
            }
        }
        Spacer(Modifier.height(20.dp))
        Column(
            Modifier.padding(horizontal = 20.dp).fillMaxWidth().background(C.Card, RoundedCornerShape(24.dp)).padding(18.dp),
        ) {
            Text("INTERVIEW MODE", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
            Spacer(Modifier.height(6.dp))
            Text("10 random questions, out loud", color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold)
            Text(
                "Read the question, answer aloud as in an interview, then check the cheat-sheet answer and grade yourself.",
                color = C.Dim, fontSize = 15.sp, lineHeight = 21.sp, modifier = Modifier.padding(top = 4.dp),
            )
            Spacer(Modifier.height(14.dp))
            Chunky("Start interview", onClick = onInterview)
        }
        Spacer(Modifier.height(20.dp))
        Text("Practice past topics", color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold, modifier = Modifier.padding(horizontal = 20.dp))
        Spacer(Modifier.height(12.dp))
        if (done.isEmpty()) {
            Text("Finish a lesson to unlock it here.", color = C.Dim, fontSize = 16.sp, modifier = Modifier.padding(horizontal = 20.dp))
        } else {
            LazyRow(contentPadding = PaddingValues(horizontal = 20.dp), horizontalArrangement = Arrangement.spacedBy(12.dp)) {
                items(done, key = { it.id }) { node ->
                    Column(
                        Modifier.width(170.dp).height(150.dp).background(C.Card, RoundedCornerShape(24.dp))
                            .clickable { onStartNode(node.id) }.padding(16.dp),
                        verticalArrangement = Arrangement.SpaceBetween,
                    ) {
                        Text("⚡ ${node.items.size} questions", color = Color.White, fontSize = 14.sp)
                        Text(node.title, color = Color.White, fontSize = 19.sp, fontWeight = FontWeight.Bold)
                    }
                }
            }
        }
        Spacer(Modifier.height(24.dp))
        Text("Your practice progress", color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold, modifier = Modifier.padding(horizontal = 20.dp))
        Spacer(Modifier.height(12.dp))
        Row(
            Modifier.padding(horizontal = 20.dp).fillMaxWidth().background(C.Card, RoundedCornerShape(18.dp)).padding(18.dp),
        ) {
            Column(Modifier.weight(1f)) {
                Text("${store.activities}", color = Color(0xFF7FB7FF), fontSize = 28.sp, fontWeight = FontWeight.Bold)
                Text("Activities done", color = Color.White, fontSize = 15.sp)
            }
            Column(Modifier.weight(1f)) {
                Text("${store.answered}", color = Color(0xFFB79CF2), fontSize = 28.sp, fontWeight = FontWeight.Bold)
                Text("Questions answered", color = Color.White, fontSize = 15.sp)
            }
        }
        Spacer(Modifier.height(24.dp))
    }
}

@Composable
fun ProfileScreen(store: Store, onPlacement: () -> Unit) {
    var armed by remember { mutableStateOf(false) }
    Column(
        Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(12.dp))
        Box(Modifier.size(130.dp).background(Color(0xFFC2185B), CircleShape), contentAlignment = Alignment.Center) {
            Text("C++", color = Color.White, fontSize = 40.sp, fontWeight = FontWeight.Bold)
        }
        Spacer(Modifier.height(12.dp))
        Text("C++ learner", color = Color.White, fontSize = 28.sp, fontWeight = FontWeight.Bold)
        Spacer(Modifier.height(24.dp))
        Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.spacedBy(12.dp)) {
            ProfileStat("🔥", "${store.liveStreak}", "DAYS STREAK", Modifier.weight(1f))
            ProfileStat("⚡", "${store.xp}", "XP", Modifier.weight(1f))
            ProfileStat("✅", "${store.completed.size}/${Content.readyNodes.size}", "LESSONS", Modifier.weight(1f))
        }
        Spacer(Modifier.height(24.dp))
        Column(Modifier.fillMaxWidth().background(C.Card, RoundedCornerShape(18.dp)).padding(16.dp)) {
            Text("DAILY GOAL", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
            Text("Lessons to finish each day", color = Color.White, fontSize = 18.sp, modifier = Modifier.padding(top = 4.dp))
            Spacer(Modifier.height(10.dp))
            Row(horizontalArrangement = Arrangement.spacedBy(10.dp)) {
                for (g in 1..3) {
                    Box(
                        Modifier.weight(1f)
                            .background(if (store.goal == g) C.Purple else C.Option, RoundedCornerShape(14.dp))
                            .clickable { store.chooseGoal(g) }.padding(vertical = 12.dp),
                        contentAlignment = Alignment.Center,
                    ) { Text("$g", color = Color.White, fontSize = 20.sp, fontWeight = FontWeight.Bold) }
                }
            }
        }
        Spacer(Modifier.height(16.dp))
        ReminderCard()
        Spacer(Modifier.height(12.dp))
        Text(
            "Take the placement check", color = Color(0xFFB79CF2), fontSize = 16.sp, textAlign = TextAlign.Center,
            modifier = Modifier.clickable(onClick = onPlacement).padding(vertical = 14.dp),
        )
        Spacer(Modifier.height(12.dp))
        Text(
            if (armed) "Tap again to erase all progress" else "Reset progress",
            color = if (armed) C.Red else C.Dim, fontSize = 16.sp, textAlign = TextAlign.Center,
            modifier = Modifier.clickable { if (armed) { store.reset(); armed = false } else armed = true }.padding(12.dp),
        )
        Spacer(Modifier.height(20.dp))
        About()
        Spacer(Modifier.height(24.dp))
    }
}

/** Credit for the CppQuiz.org puzzles, as the CC BY-SA 4.0 licence requires. */
@Composable
private fun About() {
    val uri = LocalUriHandler.current
    val lic = Content.puzzleLicense
    @Composable
    fun Link(label: String, url: String) {
        Text(
            label, color = Color(0xFFB79CF2), fontSize = 15.sp, textDecoration = TextDecoration.Underline,
            modifier = Modifier.clickable { uri.openUri(url) }.padding(vertical = 6.dp),
        )
    }
    Column(Modifier.fillMaxWidth().background(C.Card, RoundedCornerShape(18.dp)).padding(16.dp)) {
        Text("ABOUT AND LICENCES", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
        Spacer(Modifier.height(8.dp))
        Text(
            lic.credit + " They are licensed under " + lic.name + ". " + lic.changes,
            color = Color.White, fontSize = 15.sp, lineHeight = 22.sp,
        )
        Link("cppquiz.org", "https://cppquiz.org")
        Link(lic.name + " licence", lic.url)
        Link("Source of the questions", lic.source)
    }
}

@Composable
private fun ProfileStat(icon: String, value: String, label: String, modifier: Modifier) {
    Column(
        modifier.background(C.Card, RoundedCornerShape(18.dp)).padding(vertical = 18.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Text(icon, fontSize = 30.sp)
        Text(value, color = Color.White, fontSize = 24.sp, fontWeight = FontWeight.Bold)
        Text(label, color = Color.White, fontSize = 12.sp, fontWeight = FontWeight.Bold)
    }
}

@Composable
fun BottomNav(tab: Int, onTab: (Int) -> Unit) {
    val items = listOf("🎓" to "Learn", "⚡" to "Practice", "👤" to "Profile")
    Row(Modifier.fillMaxWidth().background(C.Bar).padding(vertical = 8.dp)) {
        items.forEachIndexed { i, (icon, label) ->
            Column(
                Modifier.weight(1f).clickable { onTab(i) }.padding(vertical = 4.dp),
                horizontalAlignment = Alignment.CenterHorizontally,
            ) {
                Text(icon, fontSize = 26.sp, color = if (i == tab) Color.White else C.Dim)
                Text(
                    label, fontSize = 14.sp, color = if (i == tab) Color.White else C.Dim,
                    fontWeight = if (i == tab) FontWeight.Bold else FontWeight.Normal,
                )
            }
        }
    }
}

/** The ring for today's lessons against the daily goal, with the streak it protects. */
@Composable
private fun DailyGoalCard(store: Store) {
    val goal = store.goal
    val done = minOf(store.doneToday, goal)
    val met = done >= goal
    Row(
        Modifier.fillMaxWidth().padding(horizontal = 14.dp, vertical = 10.dp)
            .background(C.Card, RoundedCornerShape(24.dp)).padding(16.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(Modifier.size(64.dp), contentAlignment = Alignment.Center) {
            Canvas(Modifier.fillMaxSize()) {
                val w = 8.dp.toPx()
                val tl = Offset(w / 2, w / 2)
                val sz = Size(size.width - w, size.height - w)
                drawArc(C.CardDark, 0f, 360f, false, tl, sz, style = Stroke(w))
                if (done > 0) drawArc(if (met) C.Green else Color(0xFFB79CF2), -90f, 360f * done / goal, false, tl, sz, style = Stroke(w, cap = StrokeCap.Round))
            }
            Text(if (met) "\u2713" else "$done/$goal", color = Color.White, fontSize = 18.sp, fontWeight = FontWeight.Bold)
        }
        Spacer(Modifier.width(16.dp))
        Column {
            Text("Daily goal", color = Color.White, fontSize = 20.sp, fontWeight = FontWeight.Bold)
            Text(
                if (met) "Goal met. Streak: ${store.liveStreak} day${if (store.liveStreak == 1) "" else "s"}"
                else "Finish ${goal - done} more lesson${if (goal - done == 1) "" else "s"} today to keep your streak",
                color = C.Dim, fontSize = 15.sp, lineHeight = 21.sp,
            )
        }
    }
}

/** Switch and time for the daily reminder; asks for the notification permission when it is needed. */
@Composable
private fun ReminderCard() {
    val ctx = LocalContext.current
    var on by remember { mutableStateOf(Reminder.enabled(ctx) && Reminder.canNotify(ctx)) }
    var hour by remember { mutableStateOf(Reminder.hour(ctx)) }
    val ask = rememberLauncherForActivityResult(ActivityResultContracts.RequestPermission()) { granted ->
        on = granted
        Reminder.save(ctx, granted, hour)
    }
    Column(Modifier.fillMaxWidth().background(C.Card, RoundedCornerShape(18.dp)).padding(16.dp)) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Column(Modifier.weight(1f)) {
                Text("DAILY REMINDER", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
                Text("A nudge until you meet the goal", color = Color.White, fontSize = 18.sp, modifier = Modifier.padding(top = 4.dp))
            }
            Switch(
                checked = on,
                onCheckedChange = { want ->
                    if (!want) {
                        on = false; Reminder.save(ctx, false, hour)
                    } else if (Reminder.canNotify(ctx)) {
                        on = true; Reminder.save(ctx, true, hour)
                    } else if (Build.VERSION.SDK_INT >= 33) {
                        ask.launch(Manifest.permission.POST_NOTIFICATIONS)
                    }
                },
                colors = SwitchDefaults.colors(checkedTrackColor = C.Purple),
            )
        }
        if (on) {
            Spacer(Modifier.height(12.dp))
            Row(horizontalArrangement = Arrangement.spacedBy(8.dp)) {
                for (h in listOf(8, 12, 18, 20)) {
                    Box(
                        Modifier.weight(1f)
                            .background(if (hour == h) C.Purple else C.Option, RoundedCornerShape(12.dp))
                            .clickable { hour = h; Reminder.save(ctx, true, h) }.padding(vertical = 10.dp),
                        contentAlignment = Alignment.Center,
                    ) { Text("%02d:00".format(h), color = Color.White, fontSize = 15.sp, fontWeight = FontWeight.SemiBold) }
                }
            }
        }
    }
}
