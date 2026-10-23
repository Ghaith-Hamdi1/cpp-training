# Phase 8: Performance, memory layout and binary data

[Roadmap](README.md) | Previous: [Phase 7: Concurrency and the memory model](phase-7-concurrency-and-the-memory-model.md)

*Cache, allocation, struct layout, endianness, parsing, queues.*

**Time:** about **3.9 hours** (1.5 h reading, 2.0 h lessons and quizzes, 0.4 h exercises), plus 0.7 h if you also read the deepen list.

## Big topics

| Topic | What it covers |
|---|---|
| **Where latency comes from** | Tail latency, percentiles, measuring correctly, the cost of allocation, exceptions, system calls. |
| **Memory on the hot path** | Preallocation, object pools, arenas, placement `new`. |
| **Cache-friendly data** | Contiguous versus linked, array of structs versus struct of arrays, false sharing, dense keys instead of maps. |
| **Binary data and parsing** | Bit manipulation, struct padding and alignment, endianness, aliasing and `memcpy`, zero-copy parsing, fixed-point numbers, sequence numbers. |
| **Queues and pipelines** | SPSC ring buffers, bounded queues and drop policies, busy-polling and thread pinning. |

## Core reading (15 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Primer | 17.2 `bitset`; 19.8 bit-fields, `volatile`, `extern "C"` | 752 to 756; 883 to 892 | 15 | The only low-level chapters in the five books; the rest is in the lessons |

## Deepen (optional, 7 pages)

| Book | Chapters and sections | PDF pages | Pages | What it gives you |
|---|---|---|---|---|
| Concurrency in Action | 8.2 Factors affecting the performance of concurrent code (also in phase 7) | 283 to 289 | 7 | Cache ping-pong and false sharing |

## Lessons and exercises

| Lesson | Time |
|---|---|
| [19. Binary Data and Parsing](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/11-wire-formats-quiz.html) | 60 min |
| [20. Performance and Memory](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency.html) and its [quiz](https://ghaith-hamdi1.github.io/cpp-training/12-low-latency-quiz.html) | 60 min |

Exercises: 17 (`BucketTable`).

> None of the five books covers this phase, so the two lessons are the main source. The C++ Primer sections are a small supplement.

**Recap check.** Explain: why the average hides the tail, how an object pool works, why a struct is bigger than the sum of its members, what endianness is and the portable way to read a big-endian value, and what false sharing is.

---

[Roadmap](README.md) | Previous: [Phase 7: Concurrency and the memory model](phase-7-concurrency-and-the-memory-model.md)
