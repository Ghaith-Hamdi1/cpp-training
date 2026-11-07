package com.cppquiz

import android.content.Context
import org.json.JSONArray
import org.json.JSONObject

/** One lesson node on the path: info slides first, then the items (question or build exercise ids). */
data class Node(val id: String, val title: String, val intro: List<String>, val items: List<String>)

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

    val readyChapters: List<Chapter> get() = chapters.filter { it.ready }
    val readyNodes: List<Node> get() = readyChapters.flatMap { it.nodes }
    val allReadyItems: List<String> get() = readyNodes.flatMap { it.items }

    fun question(id: String): Question = questionById.getValue(id)
    fun build(id: String): BuildExercise? = buildById[id]
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
            )
        }
        virtualQuestions.forEachIndexed { i, q -> qs["v:$i"] = q }
        questionById = qs
        buildById = virtualBuilds.mapIndexed { i, b -> "vb:$i" to b }.toMap()

        val chs = root.getJSONArray("chapters")
        chapters = (0 until chs.length()).map { ci ->
            val c = chs.getJSONObject(ci)
            val nodes = c.getJSONArray("nodes")
            var list = (0 until nodes.length()).map { ni ->
                val n = nodes.getJSONObject(ni)
                Node(n.getString("id"), n.getString("title"), n.getJSONArray("intro").strings(), n.getJSONArray("items").strings())
            }
            if (c.getString("id") == "classes") list = list + virtualNodes
            Chapter(c.getString("id"), c.getString("title"), list, c.getBoolean("ready"))
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
