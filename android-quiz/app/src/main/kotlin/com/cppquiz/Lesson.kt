package com.cppquiz

import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.FlowRow
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.OutlinedTextFieldDefaults
import androidx.compose.material3.Text
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlinx.coroutines.delay
import kotlin.random.Random

/** A question with its options shuffled for one run. */
class RunQ(val id: String, val q: Question, val options: List<String>, val correct: Int)

/** A build exercise with its tiles shuffled for one run. */
class RunB(val id: String, val b: BuildExercise, val tiles: List<String>)

fun runQuestion(id: String, rnd: Random): RunQ {
    val q = Content.question(id)
    return if (q.type == QType.TRUE_FALSE) {
        RunQ(id, q, q.options, q.answer)
    } else {
        val order = q.options.indices.shuffled(rnd)
        RunQ(id, q, order.map { q.options[it] }, order.indexOf(q.answer))
    }
}

sealed interface Step {
    val id: String
    val retry: Boolean

    data class Info(val text: String) : Step {
        override val id get() = ""
        override val retry get() = false
    }
    data class Quiz(val rq: RunQ, override val retry: Boolean = false) : Step {
        override val id get() = rq.id
    }
    data class Build(val rb: RunB, override val retry: Boolean = false) : Step {
        override val id get() = rb.id
    }
    data class PuzzleStep(val p: Puzzle, override val retry: Boolean = false) : Step {
        override val id get() = p.id
    }
}

/** Builds the step for an item id: a build exercise when Content knows it as one, else a quiz question. */
fun stepFor(id: String, rnd: Random, retry: Boolean = false): Step {
    Content.puzzle(id)?.let { return Step.PuzzleStep(it, retry) }
    val b = Content.build(id)
    return if (b != null) {
        Step.Build(RunB(id, b, (b.answer + b.extra).shuffled(rnd)), retry)
    } else {
        Step.Quiz(runQuestion(id, rnd), retry)
    }
}

@Composable
fun LessonRunner(
    steps: List<Step>,
    onQuit: () -> Unit,
    onDone: (results: List<Pair<String, Boolean>>, recovered: List<String>) -> Unit,
) {
    val all = remember { mutableStateListOf<Step>().apply { addAll(steps) } }
    var idx by remember { mutableIntStateOf(0) }
    var selected by remember { mutableIntStateOf(-1) }
    var picked by remember { mutableStateOf(listOf<Int>()) }
    var submitted by remember { mutableStateOf(false) }
    var lastOk by remember { mutableStateOf(false) }
    var pcat by remember { mutableIntStateOf(-1) }
    var ptext by remember { mutableStateOf("") }
    var phint by remember { mutableStateOf(false) }
    var confirmQuit by remember { mutableStateOf(false) }
    var retriesAdded by remember { mutableStateOf(false) }
    val results = remember { mutableListOf<Pair<String, Boolean>>() }
    val recovered = remember { mutableListOf<String>() }
    val missedIds = remember { mutableListOf<String>() }

    fun record(step: Step, ok: Boolean) {
        lastOk = ok
        submitted = true
        if (step.retry) {
            if (ok) recovered += step.id
        } else {
            results += step.id to ok
            // A puzzle already shows its full explanation, so only the other items come back for a retry.
            if (!ok && step !is Step.PuzzleStep) missedIds += step.id
        }
    }

    fun next() {
        if (idx + 1 >= all.size && !retriesAdded && missedIds.isNotEmpty()) {
            retriesAdded = true
            val rnd = Random(System.nanoTime())
            missedIds.forEach { all += stepFor(it, rnd, retry = true) }
        }
        if (idx + 1 < all.size) {
            idx++; selected = -1; picked = emptyList(); submitted = false
            pcat = -1; ptext = ""; phint = false
        } else {
            onDone(results.toList(), recovered.toList())
        }
    }

    val step = all[idx]
    Box(Modifier.fillMaxSize().background(C.Bg)) {
        Column(Modifier.fillMaxSize()) {
            Row(
                Modifier.fillMaxWidth().background(C.Bar).padding(horizontal = 16.dp, vertical = 14.dp),
                verticalAlignment = Alignment.CenterVertically,
            ) {
                Text("✕", color = C.Dim, fontSize = 26.sp, modifier = Modifier.clickable { confirmQuit = true }.padding(end = 14.dp))
                Box(Modifier.weight(1f)) { ProgressPill(idx / all.size.toFloat()) }
            }
            when (step) {
                is Step.Info -> InfoStep(step.text, onContinue = ::next)
                is Step.Quiz -> QuizStep(
                    rq = step.rq, retry = step.retry, selected = selected, submitted = submitted,
                    onSelect = { if (!submitted) selected = it },
                    onSubmit = { record(step, selected == step.rq.correct) },
                    onContinue = ::next,
                )
                is Step.PuzzleStep -> PuzzleView(
                    p = step.p, cat = pcat, text = ptext, hint = phint, submitted = submitted, ok = lastOk,
                    onCat = { if (!submitted) pcat = it },
                    onText = { if (!submitted) ptext = it },
                    onHint = { phint = true },
                    onSubmit = {
                        val code = PUZZLE_RESULTS[pcat].first
                        record(step, code == step.p.result && (step.p.result != "OK" || ptext.trim() == step.p.answer.trim()))
                    },
                    onContinue = ::next,
                )
                is Step.Build -> BuildStep(
                    rb = step.rb, retry = step.retry, picked = picked, submitted = submitted, ok = lastOk,
                    onPick = { if (!submitted) picked = picked + it },
                    onUndo = { if (!submitted && picked.isNotEmpty()) picked = picked.dropLast(1) },
                    onClear = { if (!submitted) picked = emptyList() },
                    onSubmit = { record(step, picked.map { step.rb.tiles[it] } == step.rb.b.answer) },
                    onContinue = ::next,
                )
            }
        }
        if (confirmQuit) QuitSheet(onCancel = { confirmQuit = false }, onQuit = onQuit)
    }
}

@Composable
private fun InfoStep(text: String, onContinue: () -> Unit) {
    Column(Modifier.fillMaxSize().padding(20.dp)) {
        Column(Modifier.weight(1f).verticalScroll(rememberScrollState()), horizontalAlignment = Alignment.CenterHorizontally) {
            Spacer(Modifier.height(32.dp))
            Mascot(if (text.length > 160) 110.dp else 180.dp)
            Spacer(Modifier.height(32.dp))
            Text(md(text), color = Color.White, fontSize = 20.sp, lineHeight = 30.sp, modifier = Modifier.fillMaxWidth())
        }
        Chunky("Continue", onClick = onContinue)
    }
}

@Composable
private fun RetryTag(retry: Boolean) {
    if (retry) {
        Text(
            "TRY AGAIN · you missed this one", color = Color(0xFFFFD166), fontSize = 13.sp,
            fontWeight = FontWeight.Bold, modifier = Modifier.padding(bottom = 6.dp),
        )
    }
}

@Composable
private fun FeedbackCard(ok: Boolean, text: String) {
    Column(
        Modifier.fillMaxWidth()
            .background(C.Bar, RoundedCornerShape(20.dp))
            .border(2.dp, if (ok) C.Green else C.Red, RoundedCornerShape(20.dp))
            .padding(16.dp),
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Mascot(56.dp, if (ok) Mood.HAPPY else Mood.SAD)
            Spacer(Modifier.size(14.dp))
            Text(
                if (ok) "Well done!" else "Not quite",
                color = if (ok) C.Green else C.Red, fontSize = 24.sp, fontWeight = FontWeight.Bold,
            )
        }
        Spacer(Modifier.height(10.dp))
        Text(md(text), color = Color.White, fontSize = 16.sp, lineHeight = 24.sp)
    }
}

@Composable
private fun BottomAction(submitted: Boolean, ok: Boolean, canSubmit: Boolean, onSubmit: () -> Unit, onContinue: () -> Unit) {
    Box(Modifier.fillMaxWidth().background(C.Bar).padding(16.dp)) {
        if (!submitted) {
            Chunky("Submit", enabled = canSubmit, onClick = onSubmit)
        } else {
            Chunky(
                "Continue", onClick = onContinue,
                face = if (ok) C.Purple else C.Red, edge = if (ok) C.PurpleDark else Color(0xFF9E3037),
            )
        }
    }
}

@Composable
private fun QuizStep(
    rq: RunQ, retry: Boolean, selected: Int, submitted: Boolean,
    onSelect: (Int) -> Unit, onSubmit: () -> Unit, onContinue: () -> Unit,
) {
    val ok = selected == rq.correct
    val scroll = rememberScrollState()
    LaunchedEffect(submitted) {
        if (submitted) {
            delay(80)
            scroll.animateScrollTo(scroll.maxValue)
        }
    }
    Column(Modifier.fillMaxSize()) {
        Column(
            Modifier.weight(1f).verticalScroll(scroll).padding(horizontal = 20.dp, vertical = 16.dp),
        ) {
            RetryTag(retry)
            Text(rq.q.type.label + " · " + rq.q.topic, color = C.Dim, fontSize = 14.sp)
            Spacer(Modifier.height(6.dp))
            Text(md(rq.q.prompt), color = Color.White, fontSize = 20.sp, lineHeight = 28.sp)
            rq.q.code?.let { Spacer(Modifier.height(14.dp)); CodeBlock(it) }
            Spacer(Modifier.height(14.dp))
            rq.options.forEachIndexed { i, t ->
                val border = when {
                    submitted && i == rq.correct -> C.Green
                    submitted && i == selected -> C.Red
                    !submitted && i == selected -> C.Cyan
                    else -> Color.Transparent
                }
                Box(
                    Modifier.padding(vertical = 5.dp).fillMaxWidth()
                        .background(if (i == selected && !submitted) C.Card else C.Option, RoundedCornerShape(16.dp))
                        .border(2.dp, border, RoundedCornerShape(16.dp))
                        .clickable { onSelect(i) }
                        .padding(horizontal = 18.dp, vertical = 18.dp),
                ) {
                    Text(
                        md(t), color = Color.White, fontSize = 17.sp, lineHeight = 24.sp,
                        fontFamily = if (rq.q.type == QType.OUTPUT) FontFamily.Monospace else null,
                    )
                }
            }
            if (submitted) {
                Spacer(Modifier.height(14.dp))
                FeedbackCard(ok, rq.q.explanation)
                Spacer(Modifier.height(8.dp))
            }
        }
        BottomAction(submitted, ok, selected >= 0, onSubmit, onContinue)
    }
}

@OptIn(ExperimentalLayoutApi::class)
@Composable
private fun BuildStep(
    rb: RunB, retry: Boolean, picked: List<Int>, submitted: Boolean, ok: Boolean,
    onPick: (Int) -> Unit, onUndo: () -> Unit, onClear: () -> Unit,
    onSubmit: () -> Unit, onContinue: () -> Unit,
) {
    val scroll = rememberScrollState()
    LaunchedEffect(submitted) {
        if (submitted) {
            delay(80)
            scroll.animateScrollTo(scroll.maxValue)
        }
    }
    val built = picked.joinToString(" ") { rb.tiles[it] }.replace(" ;", ";")
    Column(Modifier.fillMaxSize()) {
        Column(Modifier.weight(1f).verticalScroll(scroll).padding(horizontal = 20.dp, vertical = 16.dp)) {
            RetryTag(retry)
            Text("Build the code · " + rb.b.topic, color = C.Dim, fontSize = 14.sp)
            Spacer(Modifier.height(6.dp))
            Text(md(rb.b.prompt), color = Color.White, fontSize = 20.sp, lineHeight = 28.sp)
            Spacer(Modifier.height(16.dp))
            Column(
                Modifier.fillMaxWidth().background(C.Code, RoundedCornerShape(12.dp))
                    .border(2.dp, if (!submitted) Color.Transparent else if (ok) C.Green else C.Red, RoundedCornerShape(12.dp)),
            ) {
                Text(
                    "main.cpp", color = C.Dim, fontSize = 13.sp,
                    modifier = Modifier.fillMaxWidth().background(C.Bar, RoundedCornerShape(topStart = 12.dp, topEnd = 12.dp)).padding(horizontal = 14.dp, vertical = 8.dp),
                )
                Text(
                    if (built.isEmpty()) "Tap the tiles below" else built,
                    color = if (built.isEmpty()) Color(0xFF6A6C95) else Color(0xFFE6E6F0),
                    fontFamily = FontFamily.Monospace, fontSize = 18.sp, lineHeight = 26.sp,
                    modifier = Modifier.fillMaxWidth().heightIn(min = 90.dp).padding(14.dp),
                )
            }
            Spacer(Modifier.height(10.dp))
            Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.End) {
                Text("↶", color = C.Dim, fontSize = 28.sp, modifier = Modifier.clickable(onClick = onUndo).padding(horizontal = 14.dp, vertical = 4.dp))
                Text("⌫", color = C.Dim, fontSize = 28.sp, modifier = Modifier.clickable(onClick = onClear).padding(horizontal = 14.dp, vertical = 4.dp))
            }
            Spacer(Modifier.height(8.dp))
            FlowRow(
                Modifier.fillMaxWidth(),
                horizontalArrangement = Arrangement.spacedBy(10.dp),
                verticalArrangement = Arrangement.spacedBy(10.dp),
            ) {
                rb.tiles.forEachIndexed { i, t ->
                    val used = i in picked
                    Text(
                        t, fontFamily = FontFamily.Monospace, fontSize = 17.sp,
                        color = if (used) Color(0xFF6A6C95) else Color.White,
                        modifier = Modifier
                            .background(if (used) Color(0xFF2C2F55) else C.Card, RoundedCornerShape(12.dp))
                            .clickable(enabled = !used && !submitted) { onPick(i) }
                            .padding(horizontal = 16.dp, vertical = 12.dp),
                    )
                }
            }
            if (submitted) {
                Spacer(Modifier.height(18.dp))
                val shown = if (ok) rb.b.explanation else "Correct code: `${rb.b.answer.joinToString(" ").replace(" ;", ";")}`\n\n${rb.b.explanation}"
                FeedbackCard(ok, shown)
                Spacer(Modifier.height(8.dp))
            }
        }
        BottomAction(submitted, ok, picked.isNotEmpty(), onSubmit, onContinue)
    }
}

val PUZZLE_RESULTS = listOf(
    "OK" to "It prints:",
    "CE" to "It does not compile",
    "UD" to "Undefined behavior",
    "US" to "Unspecified or implementation-defined",
)

/** Turns the few HTML bits and *italic* marks of the puzzle texts into plain text; code spans stay untouched. */
private fun cleanInline(s: String): String {
    val decoded = s.replace("&nbsp;", " ").replace("&lt;", "<").replace("&gt;", ">").replace("&amp;", "&")
        .replace(Regex("<sup>(.*?)</sup>"), "^$1")
    return decoded.split('`').mapIndexed { i, seg ->
        if (i % 2 == 0) {
            seg.replace(Regex("</?[a-z]+>"), "").replace(Regex("(?<![*\\w])\\*([^*\\n]+?)\\*(?![*\\w])"), "$1")
        } else {
            seg
        }
    }.joinToString("`")
}

/** The small Markdown the puzzle explanations use: paragraphs, lists, quotes, links and fenced code. */
@Composable
fun MarkdownBlock(src: String) {
    val link = Regex("""\[([^\]]+)\]\([^)]*\)""")
    val parts = src.replace("\r\n", "\n").split("```")
    Column(Modifier.fillMaxWidth()) {
        parts.forEachIndexed { i, part ->
            if (i % 2 == 1) {
                CodeBlock(part.substringAfter('\n').trimEnd())
                Spacer(Modifier.height(10.dp))
            } else {
                part.trim().split(Regex("""\n\s*\n""")).filter { it.isNotBlank() }.forEach { para ->
                    val text = para.lines().joinToString("\n") { line ->
                        line.replace(Regex("^>\\s?"), "").replace(Regex("^\\s*[-*] "), "\u2022 ")
                    }.let { cleanInline(link.replace(it, "$1")) }
                    Text(md(text), color = Color.White, fontSize = 16.sp, lineHeight = 24.sp)
                    Spacer(Modifier.height(10.dp))
                }
            }
        }
    }
}

@Composable
private fun PuzzleView(
    p: Puzzle, cat: Int, text: String, hint: Boolean, submitted: Boolean, ok: Boolean,
    onCat: (Int) -> Unit, onText: (String) -> Unit, onHint: () -> Unit,
    onSubmit: () -> Unit, onContinue: () -> Unit,
) {
    val scroll = rememberScrollState()
    LaunchedEffect(submitted) {
        if (submitted) {
            delay(80)
            scroll.animateScrollTo(scroll.maxValue)
        }
    }
    val prints = cat == 0
    Column(Modifier.fillMaxSize()) {
        Column(Modifier.weight(1f).verticalScroll(scroll).padding(horizontal = 20.dp, vertical = 16.dp)) {
            Text("Boss puzzle \u00b7 difficulty ${p.difficulty} of 3", color = Color(0xFFFFD166), fontSize = 14.sp, fontWeight = FontWeight.Bold)
            Spacer(Modifier.height(6.dp))
            Text("According to the C++ standard, what happens when this program runs?", color = Color.White, fontSize = 20.sp, lineHeight = 28.sp)
            Spacer(Modifier.height(14.dp))
            CodeBlock(p.code)
            Spacer(Modifier.height(14.dp))
            PUZZLE_RESULTS.forEachIndexed { i, (code, label) ->
                val border = when {
                    submitted && code == p.result -> C.Green
                    submitted && i == cat -> C.Red
                    !submitted && i == cat -> C.Cyan
                    else -> Color.Transparent
                }
                Box(
                    Modifier.padding(vertical = 5.dp).fillMaxWidth()
                        .background(if (i == cat && !submitted) C.Card else C.Option, RoundedCornerShape(16.dp))
                        .border(2.dp, border, RoundedCornerShape(16.dp))
                        .clickable { onCat(i) }
                        .padding(horizontal = 18.dp, vertical = 16.dp),
                ) { Text(label, color = Color.White, fontSize = 17.sp) }
            }
            if (prints && !submitted) {
                Spacer(Modifier.height(8.dp))
                OutlinedTextField(
                    value = text, onValueChange = onText, singleLine = true,
                    label = { Text("Type the exact output") },
                    keyboardOptions = KeyboardOptions(autoCorrectEnabled = false, keyboardType = KeyboardType.Ascii),
                    textStyle = androidx.compose.ui.text.TextStyle(fontFamily = FontFamily.Monospace, fontSize = 18.sp),
                    modifier = Modifier.fillMaxWidth(),
                    colors = OutlinedTextFieldDefaults.colors(
                        focusedTextColor = Color.White, unfocusedTextColor = Color.White,
                        focusedBorderColor = C.Cyan, unfocusedBorderColor = C.Dim,
                        focusedLabelColor = C.Cyan, unfocusedLabelColor = C.Dim, cursorColor = C.Cyan,
                    ),
                )
            }
            if (!submitted) {
                Spacer(Modifier.height(8.dp))
                if (hint) {
                    Text("Hint: " + p.hint, color = Color(0xFFFFD166), fontSize = 15.sp, lineHeight = 22.sp)
                } else {
                    Text("Show a hint", color = Color(0xFFB79CF2), fontSize = 16.sp, modifier = Modifier.clickable(onClick = onHint).padding(vertical = 8.dp))
                }
            } else {
                Spacer(Modifier.height(14.dp))
                Column(
                    Modifier.fillMaxWidth()
                        .background(C.Bar, RoundedCornerShape(20.dp))
                        .border(2.dp, if (ok) C.Green else C.Red, RoundedCornerShape(20.dp))
                        .padding(16.dp),
                ) {
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Mascot(56.dp, if (ok) Mood.HAPPY else Mood.SAD)
                        Spacer(Modifier.size(14.dp))
                        Text(
                            if (ok) "Well done!" else "Not quite",
                            color = if (ok) C.Green else C.Red, fontSize = 24.sp, fontWeight = FontWeight.Bold,
                        )
                    }
                    Spacer(Modifier.height(10.dp))
                    val answer = if (p.result == "OK") "It prints `" + (p.answer.ifEmpty { "(nothing)" }) + "`." else PUZZLE_RESULTS.first { it.first == p.result }.second + "."
                    Text(md("**Answer:** $answer"), color = Color.White, fontSize = 17.sp)
                    Spacer(Modifier.height(10.dp))
                    MarkdownBlock(p.explanation)
                    Text("Puzzle from CppQuiz.org, CC BY-SA 4.0", color = C.Dim, fontSize = 12.sp)
                }
                Spacer(Modifier.height(8.dp))
            }
        }
        BottomAction(submitted, ok, cat >= 0 && (cat != 0 || text.isNotBlank()), onSubmit, onContinue)
    }
}

@Composable
private fun QuitSheet(onCancel: () -> Unit, onQuit: () -> Unit) {
    Box(Modifier.fillMaxSize().background(Color(0xAA000000)).clickable(onClick = onCancel)) {
        Column(
            Modifier.align(Alignment.BottomCenter).fillMaxWidth()
                .background(C.Bg, RoundedCornerShape(topStart = 28.dp, topEnd = 28.dp))
                .clickable(enabled = false) {}
                .padding(20.dp),
            verticalArrangement = Arrangement.spacedBy(12.dp),
        ) {
            Text("Are you sure you want to quit?", color = Color.White, fontSize = 24.sp, fontWeight = FontWeight.SemiBold)
            Text("You will lose your progress from this lesson.", color = C.Dim, fontSize = 17.sp)
            Chunky("Quit lesson", onClick = onQuit)
            Text(
                "Cancel", color = Color(0xFFB79CF2), fontSize = 20.sp, fontWeight = FontWeight.SemiBold,
                modifier = Modifier.fillMaxWidth().clickable(onClick = onCancel).padding(12.dp),
                textAlign = TextAlign.Center,
            )
        }
    }
}

@Composable
fun LessonResult(results: List<Pair<String, Boolean>>, onContinue: () -> Unit) {
    val correct = results.count { it.second }
    val pct = if (results.isEmpty()) 0 else correct * 100 / results.size
    val deeper = Content.deeper(results.filter { !it.second }.map { it.first })
    Column(Modifier.fillMaxSize().background(C.Bg).padding(20.dp)) {
        Column(
            Modifier.weight(1f).verticalScroll(rememberScrollState()).fillMaxWidth(),
            horizontalAlignment = Alignment.CenterHorizontally,
        ) {
            Spacer(Modifier.height(if (deeper.isEmpty()) 60.dp else 12.dp))
            Mascot(if (deeper.isEmpty()) 170.dp else 110.dp, Mood.HAPPY)
            Spacer(Modifier.height(16.dp))
            Text("Lesson complete!", color = Color.White, fontSize = 30.sp, fontWeight = FontWeight.Bold)
            Spacer(Modifier.height(20.dp))
            Row(horizontalArrangement = Arrangement.spacedBy(12.dp)) {
                ResultStat("XP", "+${correct * 10}", "⚡", Modifier.weight(1f))
                ResultStat("Correct", "$correct/${results.size}", "✅", Modifier.weight(1f))
                ResultStat("Accuracy", "$pct%", "🎯", Modifier.weight(1f))
            }
            if (deeper.isNotEmpty()) {
                Spacer(Modifier.height(20.dp))
                Column(Modifier.fillMaxWidth().background(C.Bar, RoundedCornerShape(20.dp)).padding(16.dp)) {
                    Text("GO DEEPER", color = C.Dim, fontSize = 13.sp, fontWeight = FontWeight.Bold)
                    Text("Sections to read again", color = Color.White, fontSize = 20.sp, fontWeight = FontWeight.Bold)
                    deeper.forEach { d ->
                        Spacer(Modifier.height(12.dp))
                        Text(d.title, color = Color(0xFFB79CF2), fontSize = 17.sp, fontWeight = FontWeight.SemiBold)
                        d.rows.forEach { r ->
                            Text(r, color = Color.White, fontSize = 14.sp, lineHeight = 20.sp, modifier = Modifier.padding(top = 3.dp))
                        }
                    }
                }
            }
            Spacer(Modifier.height(12.dp))
        }
        Chunky("Continue", onClick = onContinue)
    }
}

@Composable
fun ChapterComplete(title: String, bonus: Int, next: String?, onContinue: () -> Unit) {
    Column(Modifier.fillMaxSize().background(C.Bg).padding(20.dp), horizontalAlignment = Alignment.CenterHorizontally) {
        Spacer(Modifier.weight(1f))
        Text("🎉  🏆  🎉", fontSize = 40.sp)
        Spacer(Modifier.height(12.dp))
        Mascot(170.dp, Mood.HAPPY)
        Spacer(Modifier.height(20.dp))
        Text("Chapter complete!", color = Color.White, fontSize = 32.sp, fontWeight = FontWeight.Bold, textAlign = TextAlign.Center)
        Spacer(Modifier.height(8.dp))
        Text(title, color = C.Dim, fontSize = 20.sp, textAlign = TextAlign.Center)
        Spacer(Modifier.height(24.dp))
        Row(
            Modifier.background(C.Card, RoundedCornerShape(18.dp)).padding(horizontal = 24.dp, vertical = 14.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            Text("⚡", fontSize = 28.sp)
            Spacer(Modifier.size(10.dp))
            Text("+$bonus XP bonus", color = Color.White, fontSize = 24.sp, fontWeight = FontWeight.Bold)
        }
        if (next != null) {
            Spacer(Modifier.height(16.dp))
            Text("Next up: $next", color = C.Dim, fontSize = 16.sp, textAlign = TextAlign.Center)
        }
        Spacer(Modifier.weight(1f))
        Chunky("Continue", onClick = onContinue)
    }
}

@Composable
private fun ResultStat(label: String, value: String, icon: String, modifier: Modifier) {
    Column(
        modifier.background(C.Card, RoundedCornerShape(18.dp)).padding(vertical = 16.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Text(icon, fontSize = 26.sp)
        Text(value, color = Color.White, fontSize = 22.sp, fontWeight = FontWeight.Bold)
        Text(label, color = C.Dim, fontSize = 13.sp)
    }
}
