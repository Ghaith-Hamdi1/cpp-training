package com.cppquiz

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.BoxWithConstraints
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.CornerRadius
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.text.AnnotatedString
import androidx.compose.ui.text.SpanStyle
import androidx.compose.ui.text.buildAnnotatedString
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.withStyle
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

// Palette sampled from the live screens of the reference app.
object C {
    val Bg = Color(0xFF232846)
    val Bar = Color(0xFF333660)
    val Card = Color(0xFF4A4C85)
    val CardDark = Color(0xFF33365F)
    val Option = Color(0xFF424474)
    val Purple = Color(0xFF8B5CE0)
    val PurpleDark = Color(0xFF5E3BB5)
    val Path = Color(0xFF6F42C1)
    val Green = Color(0xFF6BCB77)
    val Cyan = Color(0xFF00BFFF)
    val Red = Color(0xFFE5535B)
    val Coin = Color(0xFFF5B82E)
    val Dot = Color(0xFF1B1F3A)
    val Dim = Color(0xFFA9AACB)
    val Code = Color(0xFF151728)
}

/** Tiny markup: **bold** and `code`. */
fun md(s: String): AnnotatedString = buildAnnotatedString {
    var i = 0
    while (i < s.length) {
        when {
            s.startsWith("**", i) -> {
                val e = s.indexOf("**", i + 2)
                if (e > 0) { withStyle(SpanStyle(fontWeight = FontWeight.Bold)) { append(s.substring(i + 2, e)) }; i = e + 2 } else { append(s[i]); i++ }
            }
            s[i] == '`' -> {
                val e = s.indexOf('`', i + 1)
                if (e > 0) {
                    withStyle(SpanStyle(fontFamily = FontFamily.Monospace, background = Color(0xFF30335B))) { append(s.substring(i + 1, e)) }
                    i = e + 1
                } else { append(s[i]); i++ }
            }
            else -> { append(s[i]); i++ }
        }
    }
}

/** Chunky button with a darker bottom edge. */
@Composable
fun Chunky(
    text: String,
    modifier: Modifier = Modifier,
    enabled: Boolean = true,
    face: Color = C.Purple,
    edge: Color = C.PurpleDark,
    textColor: Color = Color.White,
    onClick: () -> Unit,
) {
    val f = if (enabled) face else C.Option
    val e = if (enabled) edge else C.Option
    Box(
        modifier.fillMaxWidth().background(e, RoundedCornerShape(18.dp))
            .clickable(enabled = enabled, onClick = onClick),
    ) {
        Box(
            Modifier.fillMaxWidth().padding(bottom = 5.dp).background(f, RoundedCornerShape(18.dp)).height(56.dp),
            contentAlignment = Alignment.Center,
        ) {
            Text(text, color = if (enabled) textColor else C.Dim, fontSize = 20.sp, fontWeight = FontWeight.SemiBold)
        }
    }
}

enum class Mood { NEUTRAL, HAPPY, SAD }

@Composable
fun Mascot(size: Dp, mood: Mood = Mood.NEUTRAL, modifier: Modifier = Modifier) {
    Box(modifier.size(size), contentAlignment = Alignment.Center) {
        Canvas(Modifier.size(size)) {
            val w = this.size.width
            drawRoundRect(Color(0xFFE8E8F2), Offset(w * .08f, w * .08f), Size(w * .84f, w * .72f), CornerRadius(w * .22f))
            drawRoundRect(Color(0xFF22243F), Offset(w * .16f, w * .16f), Size(w * .68f, w * .5f), CornerRadius(w * .14f))
            drawRoundRect(Color(0xFFB7B8D6), Offset(w * .22f, w * .84f), Size(w * .56f, w * .12f), CornerRadius(w * .06f))
            if (mood == Mood.NEUTRAL) {
                drawCircle(C.Cyan, w * .07f, Offset(w * .38f, w * .36f))
                drawCircle(C.Cyan, w * .07f, Offset(w * .62f, w * .36f))
                drawRoundRect(C.Cyan, Offset(w * .44f, w * .5f), Size(w * .12f, w * .035f), CornerRadius(w * .02f))
            }
        }
        when (mood) {
            Mood.HAPPY -> Text("✓", color = C.Green, fontSize = (size.value * .34f).sp, fontWeight = FontWeight.Bold, modifier = Modifier.padding(bottom = size * .12f))
            Mood.SAD -> Text("✗", color = C.Red, fontSize = (size.value * .34f).sp, fontWeight = FontWeight.Bold, modifier = Modifier.padding(bottom = size * .12f))
            else -> {}
        }
    }
}

@Composable
fun ProgressPill(fraction: Float, modifier: Modifier = Modifier, height: Dp = 12.dp, track: Color = C.CardDark) {
    Box(modifier.fillMaxWidth().height(height).background(track, RoundedCornerShape(50))) {
        if (fraction > 0f) {
            Box(
                Modifier.fillMaxWidth(fraction.coerceIn(0.04f, 1f)).height(height)
                    .background(Color(0xFFB79CF2), RoundedCornerShape(50)),
            )
        }
    }
}

/** Code with no sideways scroll: the font shrinks (down to 9sp) until the longest line fits, then long lines wrap. */
@Composable
fun CodeBlock(code: String) {
    BoxWithConstraints(Modifier.fillMaxWidth().background(C.Code, RoundedCornerShape(12.dp)).padding(14.dp)) {
        val longest = code.lines().maxOfOrNull { it.length }?.coerceAtLeast(1) ?: 1
        val fontScale = LocalDensity.current.fontScale
        // A monospace character is about 0.6 em wide.
        val fit = maxWidth.value / (longest * 0.6f * fontScale)
        val size = fit.coerceIn(9f, 13f)
        Text(
            code, fontFamily = FontFamily.Monospace, fontSize = size.sp,
            lineHeight = (size * 1.4f).sp, color = Color(0xFFE6E6F0),
        )
    }
}
