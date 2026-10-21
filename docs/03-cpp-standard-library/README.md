# Embedded Team Academy — Advanced C++ Training

**Module 3: C++ Standard Library**
Document reference: **TR0014_G**

> Source note: this Markdown file was converted from a PowerPoint deck exported to PDF (`Advanced_cpp_training_module3_PDF.pdf`, 85 pages/slides). It was extracted with `pdftotext` (both raw reading-order mode and `-layout` column-preserving mode, cross-checked against each other) since no OCR/image-rendering tool was available in the environment; slides whose content was embedded as a code screenshot (image) rather than selectable text are flagged below. Every slide in the source PDF carries a repeated footer classification legend **"Provisoire Public Interne Confidentiel Secret"** — this is a standard document-classification banner, not confidential content; it has been stripped from every section below and is only mentioned here once. Where an actual C++ example file in this repository's `examples/` folder matches a slide's topic, the verified, complete source from that file is embedded instead of the (sometimes truncated) PDF-extracted snippet.

---

## Agenda

(Slide 2 — top-level training agenda)

- Module 1: C++ Basics
- Module 2: C++ Object Oriented Programming
- Module 3: C++ Standard Library
- Module 4: C++ Object Oriented Programming *(printed exactly this way in the source — identical title to Module 2; see Conversion notes)*

(Slide 3 — Module 3 agenda)

**Module 3: C++ Standard Library**

- Containers
- Iterators
- Smart pointers
- Algorithms
- String
- Date and time management
- Multi-threading and threads synchronization
- Exceptions
- Files management
- Regular expressions

---

## Standard Library

(Slide 4)

- One of the advantages of C++ is standard library
- It was written in optimized way to provide many common features that help developing programs without defining them and wasting time
- No need to include all the standard library, just choose the features that we need
- Always refer to documentation for further details: https://en.cppreference.com

---

## Closing Note (Closing slide)

(Slide 85 — final slide of the deck)

> AN ENTREPRENEURIAL SPIRIT TO MOVE FORWARD TOGETHER
>
> ACTIA Engineering Services

---


## Table of Contents

1. [Index (this file)](README.md)
2. [Containers Overview](01_containers_overview.md)
3. Sequence Containers
   - [Overview](02-sequence-containers/README.md)
   - [std::array](02-sequence-containers/01_array.md)
   - [std::vector](02-sequence-containers/02_vector.md)
   - [std::deque](02-sequence-containers/03_deque.md)
   - [std::list](02-sequence-containers/04_list.md)
   - [std::forward_list](02-sequence-containers/05_forward_list.md)
   - [std::stack](02-sequence-containers/06_stack.md)
   - [std::queue](02-sequence-containers/07_queue.md)
   - [std::priority_queue](02-sequence-containers/08_priority_queue.md)
4. Associative Containers
   - [Overview](03-associative-containers/README.md)
   - [std::set](03-associative-containers/01_set.md)
   - [std::map](03-associative-containers/02_map.md)
   - [std::multiset](03-associative-containers/03_multiset.md)
   - [std::multimap](03-associative-containers/04_multimap.md)
   - [std::unordered_set](03-associative-containers/05_unordered_set.md)
   - [std::unordered_map](03-associative-containers/06_unordered_map.md)
   - [std::unordered_multiset](03-associative-containers/07_unordered_multiset.md)
   - [std::unordered_multimap](03-associative-containers/08_unordered_multimap.md)
5. [Iterators](04_iterators.md)
6. Smart Pointers
   - [Overview](05-smart-pointers/README.md)
   - [std::unique_ptr](05-smart-pointers/01_unique_ptr.md)
   - [std::shared_ptr](05-smart-pointers/02_shared_ptr.md)
   - [std::weak_ptr](05-smart-pointers/03_weak_ptr.md)
7. [Algorithm Library Overview](06_algorithm_library_overview.md)
8. [Algorithm Library: Non-modifying](07_algorithm_library_non_modifying.md)
9. [Algorithm Library: Modifying](08_algorithm_library_modifying.md)
10. [String](09_string.md)
11. [Date and Time Management](10_date_and_time_management.md)
12. Multi-threading and Threads Synchronization
    - [Overview](11-multithreading-and-synchronization/README.md)
    - [Create and Manage Threads](11-multithreading-and-synchronization/01_create_and_manage_threads.md)
    - [Atomic Variables](11-multithreading-and-synchronization/02_atomic_variables.md)
    - [Mutual Exclusion](11-multithreading-and-synchronization/03_mutual_exclusion.md)
    - [Condition Variables](11-multithreading-and-synchronization/04_condition_variables.md)
    - [Futures and Promises](11-multithreading-and-synchronization/05_futures_and_promises.md)
13. [Back to Exceptions](12_back_to_exceptions.md)
14. [Files Management](13_files_management.md)
15. [Regular Expressions](14_regular_expressions.md)
16. [Conversion Notes](conversion-notes.md)
