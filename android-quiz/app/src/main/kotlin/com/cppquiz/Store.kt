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

    /** Lessons per day that keep the streak alive (1 to 3), and how many were finished today. */
    var goal by mutableIntStateOf(p.getInt("goal", 1)); private set
    private var todayCount by mutableIntStateOf(p.getInt("todayCount", 0))
    private var countDay by mutableStateOf(p.getLong("countDay", -1L))
    var placementDone by mutableStateOf(p.getBoolean("placementDone", false)); private set

    val doneToday: Int get() = if (countDay == today()) todayCount else 0

    /** The streak as shown: it is over once a whole day has passed without meeting the goal. */
    val liveStreak: Int get() = if (lastDay >= today() - 1) streak else 0

    fun chooseGoal(g: Int) {
        goal = g
        p.edit().putInt("goal", g).apply()
    }

    fun setPlacementDone() {
        placementDone = true
        p.edit().putBoolean("placementDone", true).apply()
    }

    /** Marks lessons as done without playing them (the result of the placement test). */
    fun markCompleted(ids: Collection<String>) {
        completed = completed + ids
        p.edit().putStringSet("completed", completed).apply()
    }

    /** Recap cards in Leitner boxes: id to (box 0..4, day it is due). */
    var cards by mutableStateOf<Map<String, Pair<Int, Long>>>(emptyMap()); private set

    init {
        if (!p.getBoolean("ids2", false)) migrateNumberIds()
        completed = p.getStringSet("completed", emptySet()) ?: emptySet()
        missed = p.getStringSet("missed", emptySet()) ?: emptySet()
        cards = (p.getStringSet("cards", emptySet()) ?: emptySet()).mapNotNull {
            val parts = it.split("|")
            if (parts.size == 3) parts[0] to (parts[1].toInt() to parts[2].toLong()) else null
        }.toMap()
    }

    private val leitnerDays = longArrayOf(1, 3, 7, 14, 30)

    fun dueCards(): List<String> = cards.filter { it.value.second <= today() }.keys.toList()

    private fun saveCards() {
        p.edit().putStringSet("cards", cards.map { "${it.key}|${it.value.first}|${it.value.second}" }.toSet()).apply()
    }

    /** Good moves a card up a box (back after 1, 3, 7, 14, 30 days); Again sends it to box 0 for tomorrow. */
    fun gradeCard(id: String, good: Boolean) {
        val box = if (good) minOf((cards[id]?.first ?: 0) + 1, leitnerDays.size - 1) else 0
        val days = if (good) leitnerDays[box] else 1L
        cards = cards + (id to (box to today() + days))
        saveCards()
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
        if (nodeId != null) {
            completed = completed + nodeId
            // The recap cards of a finished lesson join the daily review, due tomorrow.
            val fresh = Content.node(nodeId)?.cardIds.orEmpty().filter { it !in cards }
            if (fresh.isNotEmpty()) { cards = cards + fresh.associateWith { 0 to today() + 1 }; saveCards() }
        }
        var m = missed
        results.forEach { (id, ok) -> m = if (ok) m - id else m + id }
        recovered.forEach { m = m - it }
        missed = m
        val done = chapter != null && !wasDone && chapter.nodes.all { it.id in completed }
        if (done) xp += CHAPTER_BONUS
        val t = today()
        if (countDay != t) { countDay = t; todayCount = 0 }
        todayCount += 1
        // The streak grows on the first day the daily goal is met, not on any activity.
        if (todayCount >= goal && lastDay != t) {
            streak = if (lastDay == t - 1) streak + 1 else 1
            lastDay = t
        }
        p.edit()
            .putInt("xp", xp).putInt("streak", streak).putInt("answered", answered)
            .putInt("activities", activities).putLong("lastDay", lastDay)
            .putInt("todayCount", todayCount).putLong("countDay", countDay)
            .putStringSet("completed", completed).putStringSet("missed", missed)
            .apply()
        return if (done) chapter else null
    }

    fun reset() {
        p.edit().clear().putBoolean("ids2", true).apply()
        xp = 0; streak = 0; answered = 0; activities = 0; lastDay = -1L
        goal = 1; todayCount = 0; countDay = -1L; placementDone = false
        completed = emptySet(); missed = emptySet(); cards = emptyMap()
    }
}
