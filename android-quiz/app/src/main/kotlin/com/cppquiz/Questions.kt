package com.cppquiz

enum class QType(val label: String) {
    OUTPUT("Guess the output"),
    CONCEPT("Concept"),
    BUG("Spot the bug"),
    TRUE_FALSE("True / False"),
}

/** [options] are in authoring order; the UI shuffles them. [answer] indexes into [options]. */
data class Question(
    val type: QType,
    val topic: String,
    val prompt: String,
    val code: String?,
    val options: List<String>,
    val answer: Int,
    val explanation: String,
)

private fun output(topic: String, code: String, answer: String, wrong: List<String>, why: String) =
    Question(
        QType.OUTPUT, topic, "What is the output?", code.trimIndent(),
        listOf(answer) + wrong, 0, why,
    )

private fun concept(topic: String, prompt: String, answer: String, wrong: List<String>, why: String, code: String? = null) =
    Question(QType.CONCEPT, topic, prompt, code?.trimIndent(), listOf(answer) + wrong, 0, why)

private fun bug(topic: String, code: String, answer: String, wrong: List<String>, why: String) =
    Question(
        QType.BUG, topic, "What is wrong with this code?", code.trimIndent(),
        listOf(answer) + wrong, 0, why,
    )

private fun tf(topic: String, statement: String, isTrue: Boolean, why: String) =
    Question(
        QType.TRUE_FALSE, topic, statement, null,
        listOf("True", "False"), if (isTrue) 0 else 1, why,
    )

val questions: List<Question> = listOf(
    // ---------- Static vs dynamic binding ----------
    output(
        "Without virtual",
        """
        struct Animal {
            void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() {
                std::cout << "Dog";
            }
        };

        int main() {
            Dog d;
            Animal* p = &d;
            p->speak();
        }
        """,
        "Animal",
        listOf("Dog", "AnimalDog", "Compile error"),
        "speak() is not virtual, so the call is resolved at compile time from the static type of the pointer (Animal*). This is static binding. The object really is a Dog, but the compiler never looks.",
    ),
    output(
        "With virtual",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        int main() {
            Dog d;
            Animal* p = &d;
            p->speak();
        }
        """,
        "Dog",
        listOf("Animal", "AnimalDog", "Undefined behavior"),
        "speak() is virtual, so the call goes through the object's vptr to the vtable and finds Dog::speak at run time. This is dynamic binding: the dynamic type (Dog) decides, not the pointer type.",
    ),
    output(
        "Virtual + references",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        void talk(Animal& a) { a.speak(); }

        int main() {
            Dog d;
            talk(d);
        }
        """,
        "Dog",
        listOf("Animal", "Compile error", "Nothing is printed"),
        "Virtual dispatch works through references exactly like through pointers. The reference refers to the real Dog object, so Dog::speak runs.",
    ),
    output(
        "Slicing",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        int main() {
            Dog d;
            Animal a = d;
            a.speak();
        }
        """,
        "Animal",
        listOf("Dog", "Compile error", "Undefined behavior"),
        "Animal a = d copy-constructs an Animal from the Animal part of d: object slicing. a is a real Animal with Animal's vptr, so there is nothing 'Dog' left to dispatch to. Virtual only helps with pointers and references.",
    ),
    output(
        "Slicing by value parameter",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        void talk(Animal a) { a.speak(); }

        int main() {
            Dog d;
            talk(d);
        }
        """,
        "Animal",
        listOf("Dog", "Compile error", "AnimalDog"),
        "The parameter is taken by value, so the Dog is sliced into an Animal when it is copied in. Take polymorphic arguments by reference or pointer (Animal& / const Animal&).",
    ),
    output(
        "Slicing in containers",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        int main() {
            std::vector<Animal> v;
            v.push_back(Dog());
            v[0].speak();
        }
        """,
        "Animal",
        listOf("Dog", "Compile error", "Undefined behavior"),
        "std::vector<Animal> stores Animal objects by value, so the Dog is sliced on push_back. For polymorphism use std::vector<std::unique_ptr<Animal>> (or pointers/references).",
    ),
    output(
        "Virtual is inherited",
        """
        struct A {
            virtual void f() {
                std::cout << "A";
            }
        };
        struct B : A {
            void f() {
                std::cout << "B";
            }
        };
        struct C : B {
            void f() {
                std::cout << "C";
            }
        };

        int main() {
            C c;
            A* p = &c;
            p->f();
        }
        """,
        "C",
        listOf("A", "B", "Compile error"),
        "Once a function is virtual in A, every function in a derived class with the same signature is virtual too, even without the keyword (and even without override). p->f() reaches the final overrider, C::f.",
    ),
    output(
        "Multi-level override",
        """
        struct A {
            virtual void f() {
                std::cout << "A";
            }
        };
        struct B : A {
            void f() override {
                std::cout << "B";
            }
        };
        struct C : B { };

        int main() {
            C c;
            A* p = &c;
            p->f();
        }
        """,
        "B",
        listOf("A", "C", "Compile error"),
        "C does not override f, so its vtable entry for f points at the nearest overrider up the chain: B::f.",
    ),
    output(
        "Suppressing virtual",
        """
        struct Animal {
            virtual void speak() {
                std::cout << "Animal";
            }
        };
        struct Dog : Animal {
            void speak() override {
                std::cout << "Dog";
            }
        };

        int main() {
            Dog d;
            Animal* p = &d;
            p->Animal::speak();
        }
        """,
        "Animal",
        listOf("Dog", "AnimalDog", "Compile error"),
        "A qualified name (Animal::speak) disables virtual dispatch and calls that exact function. This is how an override calls its base version: Base::f().",
    ),

    // ---------- Pitfalls ----------
    output(
        "override vs overload",
        """
        struct A {
            virtual void f(int) {
                std::cout << "A::f(int)";
            }
        };
        struct B : A {
            void f(double) {
                std::cout << "B::f(double)";
            }
        };

        int main() {
            B b;
            A* p = &b;
            p->f(1);
        }
        """,
        "A::f(int)",
        listOf("B::f(double)", "Compile error", "Both lines are printed"),
        "B::f(double) has a different signature, so it does not override A::f(int); it is a new function. Through an A* only A's interface is seen. Marking it override would have caught this.",
    ),
    output(
        "const mismatch",
        """
        struct A {
            virtual void f() const {
                std::cout << "A ";
            }
        };
        struct B : A {
            void f() {
                std::cout << "B ";
            }
        };

        int main() {
            B b;
            A& r = b;
            r.f();
            b.f();
        }
        """,
        "A B ",
        listOf("B B ", "A A ", "Compile error"),
        "const is part of the signature. B::f() (non-const) does not override A::f() const. r.f() uses A's version; b.f() uses B's. With override, the compiler would reject B::f.",
    ),
    output(
        "Default arguments",
        """
        struct A {
            virtual void f(int x = 1) {
                std::cout << "A" << x;
            }
        };
        struct B : A {
            void f(int x = 2) override {
                std::cout << "B" << x;
            }
        };

        int main() {
            B b;
            A* p = &b;
            p->f();
        }
        """,
        "B1",
        listOf("B2", "A1", "A2"),
        "The function body is chosen at run time (B::f), but default arguments are bound at compile time from the static type (A*), so x = 1. Avoid different defaults on overrides.",
    ),
    output(
        "Data members are not virtual",
        """
        struct A {
            int x = 1;
            virtual int get() { return x; }
        };
        struct B : A {
            int x = 2;
            int get() override { return x; }
        };

        int main() {
            B b;
            A* p = &b;
            std::cout << p->x << p->get();
        }
        """,
        "12",
        listOf("22", "11", "21"),
        "Only member functions can be virtual. p->x is looked up statically in A (1). p->get() dispatches to B::get, which returns B::x (2).",
    ),
    output(
        "Private virtual",
        """
        class Base {
        public:
            void run() { step(); }
        private:
            virtual void step() { std::cout << "Base"; }
        };
        class Derived : public Base {
        private:
            void step() override { std::cout << "Derived"; }
        };

        int main() {
            Derived d;
            d.run();
        }
        """,
        "Derived",
        listOf("Base", "Compile error", "Undefined behavior"),
        "Access control is checked statically, dispatch happens at run time. Base::run may call its own private virtual, and the override is selected dynamically. This is the Non-Virtual Interface idiom.",
    ),

    // ---------- Constructors / destructors ----------
    output(
        "Virtual call in constructor",
        """
        struct Base {
            Base() { init(); }
            virtual void init() { std::cout << "Base::init "; }
        };
        struct Derived : Base {
            Derived() {}
            void init() override { std::cout << "Derived::init "; }
        };

        int main() { Derived d; }
        """,
        "Base::init ",
        listOf("Derived::init ", "Base::init Derived::init ", "Undefined behavior"),
        "While Base's constructor runs, the object is only a Base (the Derived part does not exist yet), so virtual calls resolve to Base's version. Never rely on virtual dispatch inside constructors.",
    ),
    output(
        "Virtual call in destructor",
        """
        struct Base {
            virtual void who() { std::cout << "Base "; }
            ~Base() { who(); }
        };
        struct Derived : Base {
            void who() override { std::cout << "Derived "; }
        };

        int main() { Derived d; }
        """,
        "Base ",
        listOf("Derived ", "Derived Base ", "Nothing is printed"),
        "Derived is destroyed first, then Base's destructor runs. At that point the object is a Base again, so who() resolves to Base::who. Same rule as constructors, in reverse.",
    ),
    output(
        "Non-virtual destructor",
        """
        struct Base {
            ~Base()    {
                std::cout << "~Base ";
            }
        };
        struct Derived : Base {
            ~Derived() {
                std::cout << "~Derived ";
            }
        };

        int main() {
            Base* p = new Derived;
            delete p;
        }
        """,
        "Undefined behavior (typically only ~Base is printed)",
        listOf("~Derived ~Base ", "~Base ~Derived ", "Compile error"),
        "Deleting a derived object through a base pointer with a non-virtual destructor is undefined behavior. In practice only ~Base runs, so Derived's resources leak. Make the base destructor virtual.",
    ),
    output(
        "Virtual destructor",
        """
        struct Base {
            virtual ~Base() {
                std::cout << "~Base ";
            }
        };
        struct Derived : Base {
            ~Derived() {
                std::cout << "~Derived ";
            }
        };

        int main() {
            Base* p = new Derived;
            delete p;
        }
        """,
        "~Derived ~Base ",
        listOf("~Base ", "~Base ~Derived ", "~Derived "),
        "With a virtual destructor, delete p dispatches to ~Derived, which runs its body and then automatically chains to ~Base. Destruction order is the reverse of construction: derived first, then base.",
    ),

    // ---------- Pure virtual / abstract ----------
    output(
        "Abstract class",
        """
        struct Shape {
            virtual double area() const = 0;
        };

        int main() {
            Shape s;
            std::cout << "ok";
        }
        """,
        "Compile error",
        listOf("ok", "0", "Undefined behavior"),
        "A class with a pure virtual function is abstract and cannot be instantiated. You can still use Shape* and Shape& to refer to concrete derived objects.",
    ),

    // ---------- Concept questions ----------
    concept(
        "What virtual does",
        "What does marking a member function virtual do?",
        "Chooses the function to call from the object's dynamic type at run time",
        listOf(
            "Makes the function run faster by inlining it",
            "Forces derived classes to override it",
            "Lets the function be called without an object",
        ),
        "virtual enables run-time (dynamic) dispatch: the call is resolved from the real type of the object, not the declared type of the pointer/reference. It does not force overriding (that is = 0) and it usually costs a bit of speed.",
    ),
    concept(
        "vptr and vtable",
        "How do compilers typically implement virtual dispatch?",
        "Each polymorphic object holds a hidden vptr pointing to its class's vtable of function pointers",
        listOf(
            "Each object stores a full copy of every virtual function",
            "The compiler searches the class hierarchy by name at run time",
            "A global table maps object addresses to class names",
        ),
        "Typical implementation: one vtable per class (an array of function pointers) and one hidden vptr per object. A virtual call loads the vptr, indexes the vtable and calls through the pointer. This costs one pointer per object and one indirect call.",
    ),
    concept(
        "override keyword",
        "What does the override specifier do?",
        "Asks the compiler to verify the function really overrides a base virtual, and errors if not",
        listOf(
            "Makes a non-virtual function virtual",
            "Prevents any further overriding",
            "Changes the generated code to be faster",
        ),
        "override does not change behavior. It is a safety check that turns silent mistakes (wrong signature, missing const, typo, base not virtual) into compile errors. final is what prevents further overriding.",
    ),
    concept(
        "final keyword",
        "What does final on a virtual function (void f() final;) mean?",
        "Classes derived further cannot override it",
        listOf(
            "The function cannot be called on derived objects",
            "The function becomes pure virtual",
            "The function is bound at compile time and not virtual",
        ),
        "final stops overriding in further derived classes. The compiler can often devirtualize calls to final functions. final on a class forbids deriving from it at all.",
    ),
    concept(
        "Virtual destructors",
        "When must a base class destructor be virtual?",
        "When objects may be deleted through a pointer to the base class",
        listOf(
            "Whenever the class has any data members",
            "Only when the class has no virtual functions",
            "Only for classes with a user-written constructor",
        ),
        "If you delete a derived object through Base* and ~Base is not virtual, behavior is undefined. Rule: a class meant to be a polymorphic base gets a public virtual destructor (or a protected non-virtual one if not deleted through the base).",
    ),
    concept(
        "Cost of virtual",
        "Which are the typical costs of adding a virtual function to a class?",
        "An extra hidden pointer per object and an indirect call that is harder to inline",
        listOf(
            "Every member function becomes slower",
            "The class can no longer have constructors",
            "A full copy of the base class is stored in each derived object",
        ),
        "Cost is small: sizeof grows by about one pointer and virtual calls are indirect (often not inlined). Non-virtual calls are unaffected. Don't make everything virtual by reflex, only what is meant to be overridden.",
    ),
    concept(
        "Pure virtual",
        "What is the effect of declaring virtual void draw() = 0; in a class?",
        "The class becomes abstract; concrete derived classes must override draw to be instantiable",
        listOf(
            "draw gets a default body of zero statements",
            "draw can only be called once",
            "The class can no longer be used through pointers",
        ),
        "= 0 makes the function pure virtual and the class abstract. Derived classes that do not override all pure virtuals stay abstract. A pure virtual function may still have a definition that derived overrides can call.",
    ),

    // ---------- Spot the bug ----------
    bug(
        "Missing virtual destructor",
        """
        struct Shape {
            virtual double area() const = 0;
        };
        struct Circle : Shape {
            double r = 1;
            std::vector<int> cache;
            double area() const override { return 3.14 * r * r; }
        };

        int main() {
            std::unique_ptr<Shape> s = std::make_unique<Circle>();
        }
        """,
        "Shape has no virtual destructor, so destroying a Circle through Shape is undefined behavior",
        listOf(
            "make_unique cannot create a derived type",
            "area must not be const",
            "Circle must declare its own constructor",
        ),
        "unique_ptr<Shape> deletes through a Shape*. Without virtual ~Shape(), Circle's destructor (and its vector member) may never run. Add virtual ~Shape() = default; to Shape.",
    ),
    bug(
        "Wrong override signature",
        """
        struct Base {
            virtual void f();
        };
        struct Derived : Base {
            void f() const override;
        };
        """,
        "Derived::f is const, so it does not override Base::f and override makes this a compile error",
        listOf(
            "override cannot be used with const",
            "Base::f must be pure virtual",
            "Nothing, this compiles and Derived::f overrides Base::f",
        ),
        "const is part of the signature. Without override this would silently create an unrelated function. That is exactly the bug override exists to catch.",
    ),
    bug(
        "Name hiding",
        """
        struct B { virtual void f() { } };
        struct D : B {
            void f(int) { }
        };

        int main() {
            D d;
            d.f();
        }
        """,
        "D::f(int) hides B::f(), so d.f() does not compile",
        listOf(
            "f must be declared override",
            "B::f must be pure virtual",
            "Nothing, d.f() calls B::f()",
        ),
        "A function in a derived class hides every base function with the same name, whatever the signature. Fix with using B::f; inside D (or call d.B::f()).",
    ),
    bug(
        "Pure virtual in constructor",
        """
        struct Base {
            Base() { init(); }
            virtual void init() = 0;
        };
        struct Derived : Base {
            void init() override { }
        };

        int main() { Derived d; }
        """,
        "Base's constructor calls a pure virtual function while the object is only a Base: undefined behavior (usually a crash or link error)",
        listOf(
            "init must be public in Derived",
            "Derived needs a virtual destructor",
            "Nothing, Derived::init is called",
        ),
        "During Base's construction the dynamic type is Base, and Base::init is pure with no body to call. Typical result: 'pure virtual function called' at run time or a linker error. Use a separate init step or a factory function.",
    ),

    // ---------- True / False ----------
    tf(
        "Private virtuals",
        "A virtual function can be private, and a derived class can still override it.",
        true,
        "Access control only affects who can name the function, not whether it can be overridden. Private virtuals are used in the Non-Virtual Interface idiom.",
    ),
    tf(
        "Virtual constructors",
        "A constructor can be declared virtual.",
        false,
        "Constructors cannot be virtual: the object does not exist yet, so there is no vptr to dispatch through. Use a virtual clone() or a factory function instead.",
    ),
    tf(
        "Inherited virtualness",
        "If Base::f() is virtual, a Derived::f() with the same signature is virtual even without the virtual keyword.",
        true,
        "Virtualness is inherited by any function that overrides a virtual one. Writing virtual or override on Derived::f is optional but good style (prefer override).",
    ),
    tf(
        "Pure virtual definitions",
        "A pure virtual function may also have a definition.",
        true,
        "A pure virtual function can be defined out of class and called with a qualified name, e.g. Base::f(). A pure virtual destructor must have a definition.",
    ),
    tf(
        "Static virtual",
        "A static member function can be virtual.",
        false,
        "Static functions have no this pointer and no object, so there is nothing to dispatch on. virtual applies only to non-static member functions.",
    ),
)
