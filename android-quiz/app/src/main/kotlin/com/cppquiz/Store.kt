package com.cppquiz

import android.content.Context
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import java.util.TimeZone

const val CHAPTER_BONUS = 50

/** Progress saved on the device. Nodes and items are saved by their string ids from content.json. */
class Store(context: Context) {
    private val p = context.getSharedPreferences("cppquiz", Context.MODE_PRIVATE)

    var xp by mutableIntStateOf(p.getInt("xp", 0)); private set
    var streak by mutableIntStateOf(p.getInt("streak", 0)); private set
    var answered by mutableIntStateOf(p.getInt("answered", 0)); private set
    var activities by mutableIntStateOf(p.getInt("activities", 0)); private set
    private var lastDay by mutableStateOf(p.getLong("lastDay", -1L))
    var completed by mutableStateOf<Set<String>>(emptySet()); private set
    var missed by mutableStateOf<Set<String>>(emptySet()); private set

    init {
        if (!p.getBoolean("ids2", false)) migrateNumberIds()
        completed = p.getStringSet("completed", emptySet()) ?: emptySet()
        missed = p.getStringSet("missed", emptySet()) ?: emptySet()
    }

    /** Version 1 saved the five virtual lessons as 0 to 4 and its questions as numbers (1000 and up for build exercises). */
    private fun migrateNumberIds() {
        val oldDone = (p.getStringSet("completed", emptySet()) ?: emptySet()).mapNotNull { it.toIntOrNull() }
        val oldMissed = (p.getStringSet("missed", emptySet()) ?: emptySet()).mapNotNull { it.toIntOrNull() }
        p.edit()
            .putStringSet("completed", oldDone.map { "virtual:$it" }.toSet())
            .putStringSet("missed", oldMissed.map { if (it >= 1000) "vb:${it - 1000}" else "v:$it" }.toSet())
            .putBoolean("ids2", true)
            .apply()
    }

    private fun today(): Long = (System.currentTimeMillis() + TimeZone.getDefault().rawOffset) / 86_400_000L

    /**
     * Records a finished lesson or review. [results] pairs an item id with whether the first try was right.
     * Returns the chapter this finished lesson completed, if any (it earns the chapter bonus).
     */
    fun finish(nodeId: String?, results: List<Pair<String, Boolean>>, recovered: List<String>): Chapter? {
        val chapter = nodeId?.let { Content.chapterOf(it) }
        val wasDone = chapter != null && chapter.nodes.all { it.id in completed }
        xp += results.count { it.second } * 10
        answered += results.size
        activities += 1
        if (nodeId != null) completed = completed + nodeId
        var m = missed
        results.forEach { (id, ok) -> m = if (ok) m - id else m + id }
        recovered.forEach { m = m - it }
        missed = m
        val done = chapter != null && !wasDone && chapter.nodes.all { it.id in completed }
        if (done) xp += CHAPTER_BONUS
        val t = today()
        if (lastDay != t) {
            streak = if (lastDay == t - 1) streak + 1 else 1
            lastDay = t
        }
        p.edit()
            .putInt("xp", xp).putInt("streak", streak).putInt("answered", answered)
            .putInt("activities", activities).putLong("lastDay", lastDay)
            .putStringSet("completed", completed).putStringSet("missed", missed)
            .apply()
        return if (done) chapter else null
    }

    fun reset() {
        p.edit().clear().putBoolean("ids2", true).apply()
        xp = 0; streak = 0; answered = 0; activities = 0; lastDay = -1L
        completed = emptySet(); missed = emptySet()
    }
}
