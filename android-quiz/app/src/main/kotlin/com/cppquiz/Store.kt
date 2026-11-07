package com.cppquiz

import android.content.Context
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import java.util.TimeZone

const val CHAPTER_BONUS = 50

/** Progress saved on the device. */
class Store(context: Context) {
    private val p = context.getSharedPreferences("cppquiz", Context.MODE_PRIVATE)

    var xp by mutableIntStateOf(p.getInt("xp", 0)); private set
    var streak by mutableIntStateOf(p.getInt("streak", 0)); private set
    var answered by mutableIntStateOf(p.getInt("answered", 0)); private set
    var activities by mutableIntStateOf(p.getInt("activities", 0)); private set
    private var lastDay by mutableStateOf(p.getLong("lastDay", -1L))
    var completed by mutableStateOf(load("completed")); private set
    var missed by mutableStateOf(load("missed")); private set

    private fun load(key: String): Set<Int> =
        (p.getStringSet(key, emptySet()) ?: emptySet()).mapNotNull { it.toIntOrNull() }.toSet()

    private fun today(): Long = (System.currentTimeMillis() + TimeZone.getDefault().rawOffset) / 86_400_000L

    /** [results] pairs question id with whether it was answered correctly. */
    fun finish(lessonIndex: Int?, results: List<Pair<Int, Boolean>>, recovered: List<Int>): Boolean {
        val before = completed.size
        xp += results.count { it.second } * 10
        answered += results.size
        activities += 1
        if (lessonIndex != null) completed = completed + lessonIndex
        var m = missed
        results.forEach { (id, ok) -> m = if (ok) m - id else m + id }
        recovered.forEach { m = m - it }
        missed = m
        val chapterDone = lessonIndex != null && before < chapterOne.lessons.size && completed.size == chapterOne.lessons.size
        if (chapterDone) xp += CHAPTER_BONUS
        val t = today()
        if (lastDay != t) {
            streak = if (lastDay == t - 1) streak + 1 else 1
            lastDay = t
        }
        p.edit()
            .putInt("xp", xp).putInt("streak", streak).putInt("answered", answered)
            .putInt("activities", activities).putLong("lastDay", lastDay)
            .putStringSet("completed", completed.map { it.toString() }.toSet())
            .putStringSet("missed", missed.map { it.toString() }.toSet())
            .apply()
        return chapterDone
    }

    fun reset() {
        p.edit().clear().apply()
        xp = 0; streak = 0; answered = 0; activities = 0; lastDay = -1L
        completed = emptySet(); missed = emptySet()
    }
}
