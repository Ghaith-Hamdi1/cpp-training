package com.cppquiz

import android.content.Context
import org.json.JSONArray
import org.json.JSONObject

/** One lesson node on the path: info slides first, then the items (question or build exercise ids). */
data class Node(
    val id: String, val title: String, val intro: List<String>, val items: List<String>,
    val cardIds: List<String> = emptyList(),
)

/** A CppQuiz.org puzzle: [result] is OK (it prints [answer]), CE, UD (undefined) or US (unspecified). */
data class Puzzle(
    val id: String, val difficulty: Int, val result: String, val answer: String,
    val code: String, val hint: String, val explanation: String,
)

/** The licence under which the puzzles are used. */
data class PuzzleLicense(val name: String, val url: String, val credit: String, val source: String, val changes: String)

/** A book section to read for a lesson section the learner got wrong. */
data class Deeper(val title: String, val rows: List<String>)

/** A recap flashcard from a lesson's cheat sheet. */
data class RecapCard(val id: String, val question: String, val answer: String)

data class Chapter(val id: String, val title: String, val nodes: List<Node>, val ready: Boolean)

/**
 * The course. Chapters, nodes and questions come from assets/content.json, generated from the site by
 * tools/export-android-content.mjs. The hand-written chapter on virtual functions is added as the last
 * nodes of the OOP chapter.
 */
object Content {
    var chapters: List<Chapter> = emptyList(); private set
    private var questionById: Map<String, Question> = emptyMap()
    private var buildById: Map<String, BuildExercise> = emptyMap()
    private var cardById: Map<String, RecapCard> = emptyMap()
    private var books: Map<String, String> = emptyMap()
    private var puzzleById: Map<String, Puzzle> = emptyMap()
    var puzzleLicense = PuzzleLicense("", "", "", "", ""); private set
    private var sections: Map<String, Pair<String, List<Triple<String, String, String>>>> = emptyMap()

    val readyChapters: List<Chapter> get() = chapters.filter { it.ready }
    val readyNodes: List<Node> get() = readyChapters.flatMap { it.nodes }
    val allReadyItems: List<String> get() = readyNodes.flatMap { it.items }

    fun question(id: String): Question = questionById.getValue(id)
    fun build(id: String): BuildExercise? = buildById[id]
    fun card(id: String): RecapCard? = cardById[id]
    fun puzzle(id: String): Puzzle? = puzzleById[id]
    fun chapterOf(nodeId: String): Chapter? = chapters.firstOrNull { c -> c.nodes.any { it.id == nodeId } }
    fun node(nodeId: String): Node? = chapters.firstNotNullOfOrNull { c -> c.nodes.firstOrNull { it.id == nodeId } }

    fun load(context: Context) {
        val text = context.assets.open("content.json").bufferedReader().use { it.readText() }
        val root = JSONObject(text)
        val qs = HashMap<String, Question>()
        val arr = root.getJSONArray("questions")
        for (i in 0 until arr.length()) {
            val o = arr.getJSONObject(i)
            qs[o.getString("id")] = Question(
                type = QType.valueOf(o.getString("type")),
                topic = o.getString("topic"),
                prompt = o.getString("prompt"),
                code = if (o.has("code")) o.getString("code") else null,
                options = o.getJSONArray("options").strings(),
                answer = o.getInt("answer"),
                explanation = o.getString("explanation"),
                sec = if (o.has("sec")) o.getString("sec") else null,
            )
        }
        virtualQuestions.forEachIndexed { i, q -> qs["v:$i"] = q }
        questionById = qs
        val bs = HashMap<String, BuildExercise>()
        virtualBuilds.forEachIndexed { i, b -> bs["vb:$i"] = b }
        val barr = root.getJSONArray("builds")
        for (i in 0 until barr.length()) {
            val o = barr.getJSONObject(i)
            bs[o.getString("id")] = BuildExercise(
                o.getString("topic"), o.getString("prompt"),
                o.getJSONArray("answer").strings(), o.getJSONArray("extra").strings(), o.getString("explanation"),
            )
        }
        buildById = bs
        val carr = root.getJSONArray("cards")
        cardById = (0 until carr.length()).map { carr.getJSONObject(it) }.associate {
            it.getString("id") to RecapCard(it.getString("id"), it.getString("q"), it.getString("a"))
        }

        val pz = JSONObject(context.assets.open("puzzles.json").bufferedReader().use { it.readText() })
        val lic = pz.getJSONObject("license")
        puzzleLicense = PuzzleLicense(
            lic.getString("name"), lic.getString("url"), lic.getString("credit"),
            lic.getString("source"), lic.getString("changes"),
        )
        val parr = pz.getJSONArray("puzzles")
        puzzleById = (0 until parr.length()).map { parr.getJSONObject(it) }.associate {
            val id = "pz:" + it.getInt("id")
            id to Puzzle(
                id, it.getInt("difficulty"), it.getString("result"), it.getString("answer"),
                it.getString("code"), it.getString("hint"), it.getString("explanation"),
            )
        }

        val rm = root.getJSONObject("readMore")
        val bk = rm.getJSONObject("books")
        books = bk.keys().asSequence().associateWith { bk.getString(it) }
        val sec = rm.getJSONObject("sections")
        sections = sec.keys().asSequence().associateWith { key ->
            val o = sec.getJSONObject(key)
            val rows = o.getJSONArray("r")
            o.getString("t") to (0 until rows.length()).map { i ->
                val r = rows.getJSONArray(i)
                Triple(r.getString(0), r.getString(1), r.getString(2))
            }
        }

        val chs = root.getJSONArray("chapters")
        chapters = (0 until chs.length()).map { ci ->
            val c = chs.getJSONObject(ci)
            val nodes = c.getJSONArray("nodes")
            var list = (0 until nodes.length()).map { ni ->
                val n = nodes.getJSONObject(ni)
                Node(
                    n.getString("id"), n.getString("title"), n.getJSONArray("intro").strings(),
                    n.getJSONArray("items").strings(), n.getJSONArray("cards").strings(),
                )
            }
            if (c.getString("id") == "classes") list = list + virtualNodes
            Chapter(c.getString("id"), c.getString("title"), list, c.getBoolean("ready"))
        }
    }

    /** Book sections for the lesson sections behind the wrongly answered items, at most [limit]. */
    fun deeper(wrongIds: List<String>, limit: Int = 3): List<Deeper> {
        val keys = wrongIds.mapNotNull { id ->
            val s = questionById[id]?.sec ?: return@mapNotNull null
            id.substringBefore(":") + ":" + s
        }.distinct().filter { it in sections }.take(limit)
        return keys.map { k ->
            val (title, rows) = sections.getValue(k)
            Deeper(title, rows.take(2).map { (book, label, pages) ->
                val name = (books[book] ?: book).substringBefore(" (")
                "$name: $label (PDF pages $pages)"
            })
        }
    }

    private fun JSONArray.strings(): List<String> = (0 until length()).map { getString(it) }
}

private fun v(vararg ids: Int) = ids.map { if (it >= 1000) "vb:${it - 1000}" else "v:$it" }

/** The virtual-functions deep dive, built from the hand-written questions and build exercises. */
private val virtualNodes = listOf(
    Node(
        "virtual:0", "Virtual: dynamic dispatch",
        listOf(
            "By default C++ picks the function to call **at compile time**, from the type of the pointer or reference. This is called **static binding**.",
            "Mark a member function `virtual` and the choice moves to **run time**: the real type of the object decides. This is **dynamic binding**.",
        ),
        v(19, 0, 1, 1000, 2, 6, 8),
    ),
    Node(
        "virtual:1", "Virtual: slicing and overriding",
        listOf(
            "Virtual dispatch needs a **pointer or a reference**. Copy a `Dog` into an `Animal` by value and the Dog part is sliced off.",
            "Once a function is virtual, every override down the chain is virtual too, even without the keyword. The call reaches the **final overrider**.",
        ),
        v(3, 4, 1001, 5, 7, 32),
    ),
    Node(
        "virtual:2", "Virtual: override pitfalls",
        listOf(
            "`override` asks the compiler to check that you really override a base virtual. A wrong signature becomes a **compile error** instead of a silent bug.",
            "Watch for a different `const`, different parameter types, hidden names, and default arguments, which are bound at **compile time**.",
        ),
        v(21, 9, 10, 1002, 11, 12, 13, 22, 27, 28, 30),
    ),
    Node(
        "virtual:3", "Virtual: constructors and destructors",
        listOf(
            "While a constructor or destructor runs, the object is only the class being built or torn down, so virtual calls **do not reach** derived overrides.",
            "A polymorphic base class needs a **virtual destructor**. Deleting a derived object through a base pointer without one is undefined behavior.",
        ),
        v(14, 15, 16, 1003, 17, 23, 26, 29, 31),
    ),
    Node(
        "virtual:4", "Virtual: abstract classes and internals",
        listOf(
            "`= 0` makes a function **pure virtual** and the class **abstract**: it cannot be instantiated, only used through pointers and references.",
            "Under the hood each object holds a hidden **vptr** pointing to a per-class **vtable**. The cost is about one pointer per object and one indirect call.",
        ),
        v(18, 25, 1004, 20, 24, 33, 34),
    ),
)
