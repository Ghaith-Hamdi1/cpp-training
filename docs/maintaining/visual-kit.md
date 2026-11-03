# Visual kit: figures for lessons

Every lesson explains an idea in three steps: **plain words, then a picture, then about ten lines of code.** This page has copy-paste pictures for the shapes that come up again and again. They are inline SVG inside `<figure class="fig">`, styled by `interactive/assets/style.css`, and they follow the light/dark theme and print in the light palette.

## Rules

- `viewBox="0 0 640 H"`: always 640 wide, so every figure has the same text size. Pick `H` to fit (usually 120 to 260).
- Text: `<text>` is 13 px; add `class="t"` for bold, `class="m"` for muted small text, `class="mono"` for code, `class="addr"` for addresses.
- Boxes: `box` (neutral), `acc` (blue, the thing the picture is about), `gd` (green, good or owner), `bd` (red, bad or dead), `wn` (amber, a warning or the heap), `cell` (a memory cell with a dark outline), `dead` (dashed red: freed or moved-from).
- Lines: `ar` (blue arrow), `ar2` (green arrow: owns), `ar3` (red arrow: dangling or wrong), `ln` (grey line), add `dash` for dashed.
- Arrow heads: a `<marker>` per colour with an id that is **unique on the page** (`a1`, `a2`, ... never reused in another figure), and a `<path class="ah">` (or `ah2`, `ah3`) inside it.
- One idea per figure, at most about 12 shapes. Always set `role="img"` and an `aria-label` that says what the picture shows, and a one-line `<figcaption>`.
- Keep the stack above the heap.

## 1. Stack above heap, with a pointer

```html
<figure class="fig"><svg viewBox="0 0 640 230" role="img" aria-label="A pointer on the stack holding the address of an int on the heap"><defs><marker id="k1" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah" d="M0 0L10 5L0 10z"/></marker></defs>
<rect class="lane" x="0" y="0" width="640" height="92" rx="8"/><text class="lane-label" x="10" y="18">STACK</text>
<text class="addr" x="60" y="38">0x7ffc10</text><rect class="acc" x="50" y="44" width="150" height="34" rx="5"/><text class="mono" x="125" y="66" text-anchor="middle">p = 0x5a20</text>
<rect class="lane" x="0" y="130" width="640" height="92" rx="8"/><text class="lane-label" x="10" y="148">HEAP</text>
<text class="addr" x="440" y="196">0x5a20</text><rect class="wn" x="340" y="174" width="90" height="34" rx="5"/><text class="mono" x="385" y="196" text-anchor="middle">42</text>
<path class="ar" d="M125 78C125 120 385 110 385 172" marker-end="url(#k1)"/>
<text class="m" x="430" y="112">p points to the int</text></svg><figcaption>p stores an address; *p follows it.</figcaption></figure>
```

## 2. Before and after (copy versus move, ownership transfer)

```html
<figure class="fig"><svg viewBox="0 0 640 170" role="img" aria-label="Before: a owns the buffer. After: b owns it and a is empty"><defs><marker id="k2" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah2" d="M0 0L10 5L0 10z"/></marker></defs>
<text class="t" x="10" y="20">before</text>
<rect class="acc" x="10" y="30" width="60" height="30" rx="5"/><text x="40" y="50" text-anchor="middle">a</text>
<path class="ar2" d="M70 45H120" marker-end="url(#k2)"/><rect class="wn" x="122" y="30" width="90" height="30" rx="5"/><text x="167" y="50" text-anchor="middle">buffer</text>
<path class="ln" d="M320 8V162"/>
<text class="t" x="340" y="20">after</text>
<rect class="dead" x="340" y="30" width="60" height="30" rx="5"/><text x="370" y="50" text-anchor="middle">a</text>
<rect class="gd" x="340" y="100" width="60" height="30" rx="5"/><text x="370" y="120" text-anchor="middle">b</text>
<path class="ar2" d="M400 115H450" marker-end="url(#k2)"/><rect class="wn" x="452" y="100" width="90" height="30" rx="5"/><text x="497" y="120" text-anchor="middle">buffer</text>
<text class="m" x="420" y="50">a is now empty</text></svg><figcaption>A move hands the buffer over; it copies nothing.</figcaption></figure>
```

## 3. Cells in a row (array, vector, memory layout)

```html
<figure class="fig"><svg viewBox="0 0 640 110" role="img" aria-label="Four ints next to each other in memory, with their addresses"><g class="mono">
<rect class="cell" x="20" y="30" width="70" height="36"/><text x="55" y="54" text-anchor="middle">10</text>
<rect class="cell" x="90" y="30" width="70" height="36"/><text x="125" y="54" text-anchor="middle">20</text>
<rect class="cell" x="160" y="30" width="70" height="36"/><text x="195" y="54" text-anchor="middle">30</text>
<rect class="cell" x="230" y="30" width="70" height="36"/><text x="265" y="54" text-anchor="middle">40</text></g>
<text class="addr" x="20" y="86">+0</text><text class="addr" x="90" y="86">+4</text><text class="addr" x="160" y="86">+8</text><text class="addr" x="230" y="86">+12</text>
<text class="m" x="20" y="20">a[0]</text><text class="m" x="90" y="20">a[1]</text><text class="m" x="160" y="20">a[2]</text><text class="m" x="230" y="20">a[3]</text></svg><figcaption>Array elements sit side by side; a[i] is the address plus i times 4.</figcaption></figure>
```

## 4. Timeline lanes (threads)

```html
<figure class="fig"><svg viewBox="0 0 640 170" role="img" aria-label="Two threads each read counter, then each write it, so one increment is lost"><defs><marker id="k3" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah3" d="M0 0L10 5L0 10z"/></marker></defs>
<rect class="lane" x="0" y="20" width="640" height="50" rx="6"/><text class="lane-label" x="8" y="14">thread A</text>
<rect class="lane" x="0" y="100" width="640" height="50" rx="6"/><text class="lane-label" x="8" y="94">thread B</text>
<rect class="acc" x="60" y="30" width="110" height="30" rx="5"/><text class="mono" x="115" y="50" text-anchor="middle">read 5</text>
<rect class="acc" x="200" y="30" width="110" height="30" rx="5"/><text class="mono" x="255" y="50" text-anchor="middle">write 6</text>
<rect class="acc" x="130" y="110" width="110" height="30" rx="5"/><text class="mono" x="185" y="130" text-anchor="middle">read 5</text>
<rect class="bd" x="330" y="110" width="110" height="30" rx="5"/><text class="mono" x="385" y="130" text-anchor="middle">write 6</text>
<path class="ar3 dash" d="M385 110C385 90 330 80 310 62" marker-end="url(#k3)"/>
<line class="tick" x1="60" y1="156" x2="560" y2="156"/><text class="m" x="566" y="160">time</text></svg><figcaption>Both read 5, both write 6: one increment is lost.</figcaption></figure>
```

## 5. Ownership arrows (good and dangling)

Use `ar2` (green) from an owner to the object it frees, `ar3 dash` (red, dashed) from a pointer to an object that is gone, and a `dead` box for the freed object.

```html
<figure class="fig"><svg viewBox="0 0 640 120" role="img" aria-label="An owner with a green arrow to a live object, and a raw pointer with a red dashed arrow to a freed object"><defs><marker id="k4" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah2" d="M0 0L10 5L0 10z"/></marker><marker id="k5" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah3" d="M0 0L10 5L0 10z"/></marker></defs>
<rect class="gd" x="10" y="20" width="110" height="34" rx="5"/><text class="mono" x="65" y="42" text-anchor="middle">unique_ptr</text>
<path class="ar2" d="M120 37H190" marker-end="url(#k4)"/><rect class="wn" x="192" y="20" width="100" height="34" rx="5"/><text x="242" y="42" text-anchor="middle">Widget</text>
<rect class="acc" x="340" y="20" width="110" height="34" rx="5"/><text class="mono" x="395" y="42" text-anchor="middle">raw *</text>
<path class="ar3 dash" d="M450 37H520" marker-end="url(#k5)"/><rect class="dead" x="522" y="20" width="100" height="34" rx="5"/><text x="572" y="42" text-anchor="middle">freed</text>
<text class="m" x="10" y="90">owns, frees it</text><text class="m" x="340" y="90">dangling: do not use</text></svg><figcaption>Green: owns and frees. Red dashed: points at something that is gone.</figcaption></figure>
```

## 6. A decision in three boxes (which tool for which job)

```html
<figure class="fig"><svg viewBox="0 0 640 130" role="img" aria-label="If one owner use unique_ptr; if shared use shared_ptr; if only observing use a reference"><defs><marker id="k6" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path class="ah" d="M0 0L10 5L0 10z"/></marker></defs>
<rect class="box" x="10" y="45" width="130" height="40" rx="6"/><text class="t" x="75" y="70" text-anchor="middle">who owns it?</text>
<path class="ar" d="M140 55L200 24" marker-end="url(#k6)"/><path class="ar" d="M140 65L200 65" marker-end="url(#k6)"/><path class="ar" d="M140 75L200 106" marker-end="url(#k6)"/>
<rect class="gd" x="202" y="6" width="220" height="32" rx="5"/><text x="312" y="27" text-anchor="middle">one owner: unique_ptr</text>
<rect class="acc" x="202" y="49" width="220" height="32" rx="5"/><text x="312" y="70" text-anchor="middle">several: shared_ptr</text>
<rect class="wn" x="202" y="92" width="220" height="32" rx="5"/><text x="312" y="113" text-anchor="middle">nobody: a reference</text></svg><figcaption>Start from ownership, not from the pointer type.</figcaption></figure>
```

## Checking a figure

1. Open the lesson in the browser (`node tools/serve.mjs`), light and dark theme.
2. `node tools/build-lessons-pdf.mjs` and look at the PDF page: nothing clipped, nothing smaller than the surrounding text.
3. Each marker id must appear once per page (`check-interactive` does not catch duplicates, the arrows just point wrong).
