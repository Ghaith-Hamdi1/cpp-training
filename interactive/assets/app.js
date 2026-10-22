/* C++ Interview Prep: shared lesson/quiz engine. Vanilla JS, no dependencies.
 *
 * A page declares <body data-topic="..." data-kind="lesson|quiz|home"> and this
 * script builds the header, table of contents, progress tracking and pager.
 * Page scripts then call CT.stepper(), CT.threadsim() or CT.quiz().
 */
(function () {
  'use strict';

  // The lesson list lives in assets/data/lessons.js (loaded before this file). The number shown is the position.
  if (!(window.CT && window.CT.lessons)) throw new Error('assets/data/lessons.js must be loaded before app.js');
  const TOPICS = window.CT.lessons.map((t, i) => Object.assign({ n: i + 1 }, t));

  const $ = (s, r) => (r || document).querySelector(s);
  const $$ = (s, r) => Array.from((r || document).querySelectorAll(s));
  const esc = (s) => String(s).replace(/[&<>"]/g, (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c]));
  const fmt = (t) => esc(t).replace(/`([^`]+)`/g, '<code>$1</code>').replace(/\*\*([^*]+)\*\*/g, '<b>$1</b>');

  const store = {
    get(k, d) { try { const v = localStorage.getItem('cpptrain:' + k); return v == null ? d : JSON.parse(v); } catch (e) { return d; } },
    set(k, v) { try { localStorage.setItem('cpptrain:' + k, JSON.stringify(v)); } catch (e) { /* storage unavailable */ } }
  };

  function dedent(t) {
    const ls = t.split('\n');
    let m = Infinity;
    ls.forEach((l) => { if (l.trim()) m = Math.min(m, l.match(/^[ \t]*/)[0].length); });
    return !isFinite(m) || m === 0 ? t : ls.map((l) => l.slice(m)).join('\n');
  }
  const clean = (t) => dedent(t.replace(/^\s*\n/, '').replace(/\s+$/, ''));
  const shuffle = (a) => { for (let i = a.length - 1; i > 0; i--) { const j = Math.floor(Math.random() * (i + 1)); [a[i], a[j]] = [a[j], a[i]]; } return a; };

  /* ---------------- syntax highlighting ---------------- */
  const KW = new Set(('alignas alignof and break case catch class const consteval constexpr constinit const_cast continue co_await co_return co_yield ' +
    'decltype default delete do dynamic_cast else enum explicit export extern false final for friend goto if inline mutable namespace new noexcept not ' +
    'nullptr operator or override private protected public register reinterpret_cast requires return sizeof static static_assert static_cast struct switch ' +
    'template this thread_local throw true try typedef typeid typename union using virtual volatile while concept').split(' '));
  const BT = new Set('auto bool char char8_t char16_t char32_t double float int long short signed unsigned void wchar_t'.split(' '));
  const TY = new Set(('size_t ptrdiff_t string string_view vector map unordered_map set unordered_set multimap multiset array deque list forward_list pair tuple optional variant any ' +
    'unique_ptr shared_ptr weak_ptr thread jthread mutex recursive_mutex shared_mutex atomic future promise packaged_task condition_variable lock_guard unique_lock scoped_lock ' +
    'function ostream istream cout cin cerr endl move forward ref size_type int8_t int16_t int32_t int64_t uint8_t uint16_t uint32_t uint64_t std queue stack priority_queue ' +
    'initializer_list exception runtime_error logic_error invalid_argument out_of_range chrono duration').split(' '));
  const RE = /(\/\/[^\n]*|\/\*[\s\S]*?\*\/)|(#[ \t]*\w+[^\n]*)|("(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])+')|(\b0[xX][0-9a-fA-F']+\b|\b\d[\d']*(?:\.\d+)?(?:[eE][+-]?\d+)?[fFuUlL]*\b)|([A-Za-z_]\w*)/g;

  function highlight(src) {
    let out = '';
    let last = 0;
    let m;
    RE.lastIndex = 0;
    while ((m = RE.exec(src))) {
      out += esc(src.slice(last, m.index));
      last = RE.lastIndex;
      const t = m[0];
      let cls = '';
      if (m[1]) cls = 'cm';
      else if (m[2]) cls = 'pp';
      else if (m[3]) cls = 'st';
      else if (m[4]) cls = 'nu';
      else if (m[5]) cls = KW.has(t) ? 'kw' : BT.has(t) ? 'ty' : TY.has(t) ? 'ty2' : '';
      out += cls ? '<span class="tk-' + cls + '">' + esc(t) + '</span>' : esc(t);
    }
    return out + esc(src.slice(last));
  }

  /* Compiler Explorer link: runs the snippet when it has main(), otherwise just compiles it. */
  function godboltUrl(src) {
    const opts = '-std=c++20 -O1 -pthread';
    const hasMain = /main\s*\(/.test(src);
    const state = { sessions: [{ id: 1, language: 'c++', source: src,
      compilers: [{ id: 'g132', options: opts }],
      executors: hasMain ? [{ compiler: { id: 'g132', options: opts }, stdin: '', stdout: true, wrap: true }] : [] }] };
    return 'https://godbolt.org/clientstate/' + encodeURIComponent(btoa(unescape(encodeURIComponent(JSON.stringify(state)))));
  }

  function renderCodeBlocks() {
    $$('script[type="text/x-cpp"],script[type="text/x-out"]').forEach((s) => {
      const isOut = s.type === 'text/x-out';
      const txt = clean(s.textContent);
      const fig = document.createElement('figure');
      fig.className = 'code' + (isOut ? ' out' : '');
      const title = s.getAttribute('data-title');
      fig.innerHTML = (title || isOut ? '<figcaption>' + (title ? esc(title) : '') + '</figcaption>' : '') +
        '<pre><code>' + (isOut ? esc(txt) : highlight(txt)) + '</code></pre>' +
        (isOut ? '' : '<a class="run" target="_blank" rel="noopener" href="' + esc(godboltUrl(txt)) + '">' + (/main\s*\(/.test(txt) ? 'Run' : 'Try') + ' &#8599;</a>' +
          '<button class="copy" type="button">Copy</button>');
      const btn = $('.copy', fig);
      if (btn) {
        btn.addEventListener('click', () => {
          try {
            navigator.clipboard.writeText(txt).then(() => { btn.textContent = 'Copied'; setTimeout(() => { btn.textContent = 'Copy'; }, 1200); });
          } catch (e) { btn.textContent = 'Select + Ctrl+C'; }
        });
      }
      s.replaceWith(fig);
    });
  }

  /* ---------------- page chrome ---------------- */
  function topicOf(id) { return TOPICS.find((t) => t.id === id); }

  /* ---------------- search across all lessons ---------------- */
  let searchDlg;
  let searchFailed = false;
  let loadIndex = () => {};
  function openSearch() {
    if (!searchDlg) {
      searchDlg = document.createElement('dialog');
      searchDlg.className = 'search';
      searchDlg.setAttribute('aria-label', 'Search the lessons');
      searchDlg.innerHTML = '<input type="search" placeholder="Search all lessons (e.g. mutex, rule of five)" aria-label="Search terms" autocomplete="off">' +
        '<div class="results" role="status" aria-live="polite"></div>';
      document.body.appendChild(searchDlg);
      searchDlg.addEventListener('click', (e) => { if (e.target === searchDlg) searchDlg.close(); });
      const input = $('input', searchDlg);
      const box = $('.results', searchDlg);
      const run = () => {
        const terms = input.value.toLowerCase().split(/\s+/).filter(Boolean);
        if (!terms.length) { box.textContent = ''; return; }
        if (!CT.searchIndex) { box.textContent = searchFailed ? 'The search index could not be loaded. Check your connection, then close and reopen search to retry.' : 'Loading the index...'; return; }
        const hits = [];
        CT.searchIndex.forEach((e) => {
          const hl = e.h.toLowerCase();
          const xl = e.x.toLowerCase();
          let score = 0;
          for (const t of terms) {
            const inH = hl.indexOf(t) >= 0;
            const n = xl.split(t).length - 1;
            if (!inH && !n) return;
            score += (inH ? 20 : 0) + Math.min(n, 10);
          }
          hits.push({ e, score, i: xl.indexOf(terms[0]) });
        });
        hits.sort((a, b) => b.score - a.score);
        box.innerHTML = hits.length ? hits.slice(0, 12).map((h) => {
          const x = h.e.x;
          const at = Math.max(0, h.i - 50);
          const snip = (at ? '...' : '') + x.slice(at, at + 130) + '...';
          return '<a href="' + h.e.f + '#' + h.e.id + '"><b>' + esc(h.e.h) + '</b><span>' + esc(h.e.n) + '</span><small>' + esc(snip) + '</small></a>';
        }).join('') : 'No matches.';
      };
      input.addEventListener('input', run);
      loadIndex = () => {
        if (CT.searchIndex) return;
        searchFailed = false;
        const sc = document.createElement('script');
        sc.src = 'assets/data/search-index.js';
        sc.onload = run;
        sc.onerror = () => { sc.remove(); searchFailed = true; run(); };   // offline with nothing cached
        document.head.appendChild(sc);
      };
      loadIndex();
    } else if (searchFailed) {
      loadIndex();                          // reopening after a failure retries the download
      $('input', searchDlg).dispatchEvent(new Event('input'));
    }
    if (!searchDlg.open) searchDlg.showModal();
    $('input', searchDlg).focus();
    $('input', searchDlg).select();
  }

  function buildHeader(kind) {
    const cur = document.body.dataset.topic;
    const links = '<a href="study-checklist.html"' + (kind === 'checklist' ? ' class="cur"' : '') + '>Study checklist</a>' +
      '<a href="assess.html"' + (kind === 'assess' ? ' class="cur"' : '') + '>Level check</a>' +
      '<a href="mock-interview.html"' + (kind === 'mock' ? ' class="cur"' : '') + '>Mock interview</a>' + TOPICS.map((t) =>
      '<a href="' + t.file + '"' + (t.id === cur && kind === 'lesson' ? ' class="cur"' : '') + '>' + t.n + '. ' + esc(t.title) + '</a>' +
      '<a href="' + t.quiz + '"' + (t.id === cur && kind === 'quiz' ? ' class="cur"' : '') + '>&nbsp;&nbsp;&nbsp;&nbsp;&#8627; Quiz</a>').join('');
    const h = document.createElement('header');
    h.className = 'top';
    h.innerHTML = '<a class="brand" href="index.html">C++ Interview Prep</a><span class="spacer"></span>' +
      '<button class="icon-btn" id="search-btn" type="button" aria-label="Search the lessons (press /)">&#128269;</button>' +
      '<details class="menu"><summary>Topics &#9662;</summary><div class="panel">' + links + '</div></details>' +
      '<button class="icon-btn" id="theme" type="button" aria-label="Toggle light or dark theme">&#9680;</button><div class="progress"></div>';
    document.body.prepend(h);
    const mainEl = $('main');
    if (mainEl) {
      if (!mainEl.id) mainEl.id = 'content';
      mainEl.tabIndex = -1;
      const skip = document.createElement('a');
      skip.className = 'skip';
      skip.href = '#' + mainEl.id;
      skip.textContent = 'Skip to content';
      document.body.prepend(skip);
    }
    h.setAttribute('role', 'banner');
    $('#search-btn').addEventListener('click', openSearch);
    document.addEventListener('keydown', (e) => {
      if (e.key === '/' && !/^(INPUT|TEXTAREA|SELECT)$/.test((e.target.tagName || '')) && !e.ctrlKey && !e.metaKey) { e.preventDefault(); openSearch(); }
    });
    $('#theme').addEventListener('click', () => {
      const root = document.documentElement;
      const dark = root.dataset.theme ? root.dataset.theme === 'dark' : matchMedia('(prefers-color-scheme: dark)').matches;
      root.dataset.theme = dark ? 'light' : 'dark';
      store.set('theme', root.dataset.theme);
      $('#theme').setAttribute('aria-pressed', String(root.dataset.theme === 'dark'));
    });
    $('#theme').setAttribute('aria-pressed', String(document.documentElement.dataset.theme ? document.documentElement.dataset.theme === 'dark' : matchMedia('(prefers-color-scheme: dark)').matches));
    document.addEventListener('click', (e) => { const m = $('.menu', h); if (m && !m.contains(e.target)) m.open = false; });
  }

  function buildPager(main, kind) {
    const t = topicOf(document.body.dataset.topic);
    if (!t) return;
    const prev = TOPICS[t.n - 2];
    const next = TOPICS[t.n];
    const p = document.createElement('div');
    p.className = 'pager';
    if (kind === 'lesson') {
      p.innerHTML = (prev ? '<a class="btn ghost" href="' + prev.file + '">&larr; ' + esc(prev.title) + '</a>' : '<span></span>') +
        '<a class="btn" href="' + t.quiz + '">Take the quiz &rarr;</a>' +
        (next ? '<a class="btn ghost" href="' + next.file + '">' + esc(next.title) + ' &rarr;</a>' : '<span></span>');
    } else {
      p.innerHTML = '<a class="btn ghost" href="' + t.file + '">&larr; Back to the lesson</a>' +
        (next ? '<a class="btn" href="' + next.file + '">Next: ' + esc(next.title) + ' &rarr;</a>' : '<a class="btn" href="index.html">Home</a>');
    }
    main.appendChild(p);
  }

  function buildLesson(main) {
    const id = document.body.dataset.topic;
    const wanted = decodeURIComponent(location.hash.slice(1));
    if (wanted && !document.getElementById(wanted)) {            // a link to a section that has moved to another lesson
      const moved = CT.resolveMoved(location.pathname.split('/').pop(), wanted);
      if (moved) { location.replace(moved); return; }
    }
    const secs = $$('main > section');
    secs.forEach((s, i) => {
      if (!s.id) s.id = 's' + (i + 1);
      if (!s.dataset.title) s.dataset.title = ($('h2', s) || {}).textContent || 'Section ' + (i + 1);
    });
    const done = new Set(store.get('done:' + id, []));
    store.set('total:' + id, secs.length);

    const aside = document.createElement('aside');
    aside.className = 'toc';
    aside.setAttribute('aria-label', 'Lesson contents');
    aside.innerHTML = '<button class="toggle" type="button" aria-expanded="false">Contents &#9662;</button><nav class="list" aria-label="Sections in this lesson"><h4>In this lesson</h4>' +
      secs.map((s) => '<a href="#' + s.id + '" data-id="' + s.id + '"><span class="tick"></span><span>' + esc(s.dataset.title) + '</span></a>').join('') +
      '<div class="count"></div></nav>';
    const layout = document.createElement('div');
    layout.className = 'layout';
    main.parentNode.insertBefore(layout, main);
    layout.append(aside, main);
    $('.toggle', aside).addEventListener('click', () => {
      $('.toggle', aside).setAttribute('aria-expanded', String(aside.classList.toggle('open')));
    });

    function paint() {
      secs.forEach((s) => {
        const a = $('a[data-id="' + s.id + '"] .tick', aside);
        if (a) a.textContent = done.has(s.id) ? '✓' : '';
        a.parentNode.title = done.has(s.id) ? 'Marked as understood' : '';
      });
      $('.count', aside).textContent = done.size + ' of ' + secs.length + ' sections understood';
      if (typeof navLabel === 'function') navLabel();
      const bar = $('.top .progress');
      if (bar) bar.style.width = (secs.length ? (done.size / secs.length) * 100 : 0) + '%';
    }

    secs.forEach((s) => {
      const lab = document.createElement('label');
      lab.className = 'done' + (done.has(s.id) ? ' on' : '');
      lab.hidden = true;                  // the button at the bottom of the section does the ticking
      lab.innerHTML = '<input type="checkbox"' + (done.has(s.id) ? ' checked' : '') + '> I understand this section';
      $('input', lab).addEventListener('change', (e) => {
        if (e.target.checked) done.add(s.id); else done.delete(s.id);
        lab.classList.toggle('on', e.target.checked);
        store.set('done:' + id, Array.from(done));
        paint();
      });
      s.appendChild(lab);
    });
    paint();
    function navLabel() { secs.forEach((s, i) => {
      const b = $('[data-done]', s);
      const n = secs[i + 1];
      const next = n ? 'next: ' + esc(n.dataset.title) : 'take the quiz';
      if (b) b.innerHTML = (done.has(s.id) ? next.charAt(0).toUpperCase() + next.slice(1) : '&#10003; Understood, ' + next) + ' &rarr;';
    }); }

    /* one section per page: #id shows that section, prev/next buttons walk through them */
    secs.forEach((s, i) => {
      const nav = document.createElement('div');
      nav.className = 'secnav';
      const p = secs[i - 1], n = secs[i + 1];
      const topic = topicOf(id);
      nav.innerHTML = (p ? '<a class="btn sm ghost" href="#' + p.id + '">&larr; ' + esc(p.dataset.title) + '</a>' : '<span></span>') +
        '<span class="secpos">' + (i + 1) + ' / ' + secs.length + '</span>' +
        '<a class="btn sm" data-done href="' + (n ? '#' + n.id : topic ? topic.quiz : '#') + '">&#10003; Understood, ' + (n ? 'next: ' + esc(n.dataset.title) : 'take the quiz') + ' &rarr;</a>';
      $('[data-done]', nav).addEventListener('click', () => {      // tick the section, then follow the link
        const box = $('.done input', s);
        if (box && !box.checked) { box.checked = true; box.dispatchEvent(new Event('change')); }
      });
      s.appendChild(nav);
    });
    navLabel();
    aside.addEventListener('click', (e) => {                         // click a tick in the contents list to toggle it
      const t = e.target.closest ? e.target.closest('.tick') : null;
      if (!t) return;
      e.preventDefault();
      const box = $('.done input', document.getElementById(t.parentNode.dataset.id));
      if (box) { box.checked = !box.checked; box.dispatchEvent(new Event('change')); }
    });
    document.addEventListener('keydown', (e) => {                  // left / right arrows walk through the sections
      if (e.ctrlKey || e.metaKey || e.altKey || e.shiftKey || /^(INPUT|TEXTAREA|SELECT)$/.test((e.target.tagName || ''))) return;
      if (e.key !== 'ArrowLeft' && e.key !== 'ArrowRight') return;
      const i = secs.findIndex((s) => !s.hidden);
      const t = secs[i + (e.key === 'ArrowRight' ? 1 : -1)];
      if (t) { e.preventDefault(); location.hash = '#' + t.id; }
    });
    let intro = true;
    function show(first) {
      let cur = null;
      const h = decodeURIComponent(location.hash.slice(1));
      if (h) {
        const t = document.getElementById(h);
        cur = t && t.closest ? t.closest('main > section') : null;
      }
      if (!cur && first && !h) {                                    // no link target: resume where you stopped
        const saved = store.get('last:' + id, '');
        cur = secs.find((s) => s.id === saved) || null;
      }
      if (!cur) cur = secs[0];
      store.set('last:' + id, cur.id);
      store.set('lastinfo', { id: id, sec: cur.id, n: secs.indexOf(cur) + 1, of: secs.length, title: cur.dataset.title });
      secs.forEach((s) => { s.hidden = s !== cur; });
      Array.from(main.children).forEach((el) => {       // intro paragraphs between the title and the first section: first page only
        if (el === secs[0]) { intro = false; }
        else if (intro && el.tagName !== 'H1') el.hidden = cur !== secs[0];
      });
      intro = true;
      main.classList.toggle('last-page', cur === secs[secs.length - 1]);
      $$('a', aside).forEach((a) => {
        const on = a.dataset.id === cur.id;
        a.classList.toggle('active', on);
        if (on) a.setAttribute('aria-current', 'page'); else a.removeAttribute('aria-current');
      });
      aside.classList.remove('open');
      $('.toggle', aside).setAttribute('aria-expanded', 'false');
      if (!first || h) {
        const t = h && document.getElementById(h);
        if (t && t !== cur) t.scrollIntoView(); else window.scrollTo(0, 0);
      }
    }
    window.addEventListener('hashchange', () => show(false));
    show(true);
  }

  /* ---------------- step-through memory visualiser ---------------- */
  function stepper(sel, cfg) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.className = 'widget stepper';
    root.tabIndex = 0;
    const code = clean(cfg.code).split('\n');
    const lines = code.map((l, i) => '<span class="ln" data-l="' + (i + 1) + '"><i>' + (i + 1) + '</i>' + (highlight(l) || ' ') + '</span>').join('');
    const N = cfg.steps.length;
    const maxLen = code.reduce((m, l) => Math.max(m, l.length), 0);
    root.style.setProperty('--st-cols', maxLen <= 30 ? 'minmax(0, 0.7fr) minmax(0, 1.5fr)' : maxLen <= 46 ? 'minmax(0, 0.9fr) minmax(0, 1.3fr)' : 'minmax(0, 1.1fr) minmax(0, 1fr)');
    root.innerHTML = '<div class="w-head"><span class="tag">Step through</span>' + esc(cfg.title || '') + '</div>' +
      '<div class="st-body"><div class="st-pane st-codepane"><div class="st-label">Code</div><pre class="st-code">' + lines + '</pre></div>' +
      '<div class="st-pane st-side"><div class="st-label">Memory</div><div class="st-mem"></div><div class="st-legend"><span><i class="lg chg"></i>changed this step (ring)</span><span><i class="lg dead"></i>freed or gone</span><span><i class="lg arr">&rarr;</i>points to</span><span><i class="lg col"></i>same colour = same variable or object</span></div><div class="st-label">Output</div><div class="st-out" aria-label="Program output"></div></div></div>' +
      '<div class="st-note" role="status" aria-live="polite"></div>' +
      '<div class="st-dots" role="group" aria-label="Jump to a step">' + Array.from({ length: N }, (_, k) => '<button type="button" class="st-dot" data-j="' + k + '" aria-label="Step ' + (k + 1) + '"></button>').join('') + '</div>' +
      '<div class="w-foot" role="group" aria-label="Step controls"><button class="btn sm ghost" data-a="back" type="button">&#9664; Back</button>' +
      '<button class="btn sm" data-a="next" type="button">Next &#9654;</button>' +
      '<button class="btn sm ghost" data-a="play" type="button">&#9654;&#9654; Play</button>' +
      '<button class="btn sm ghost" data-a="reset" type="button">Reset</button><span class="info"></span></div>';
    const uid = Math.random().toString(36).slice(2, 8);
    let i = -1, timer = null;
    const GROUPS = [['stack', 'Stack', 'locals, freed automatically'], ['heap', 'Heap', 'new / make_unique, freed explicitly'], ['static', 'Static / global', 'lives for the whole program'], ['call', 'Call stack', ''], ['inst', 'Compiler-generated functions', ''], ['queue', 'Shared queue', ''], ['threads', 'Threads', '']];
    // One colour per variable / object: a.ptr and a.size share a colour; a heap block takes the colour of the pointer that holds its address.
    const PALETTE = ['210 75% 56%', '28 90% 55%', '150 58% 42%', '280 55% 62%', '340 72% 60%', '182 62% 42%', '48 88% 48%', '240 62% 68%'];
    const famBase = (n) => n.replace(/\s*@0x[0-9a-fA-F]+/, '').split(/[.\[]/)[0].trim();
    const owners = {}, famIdx = {};
    cfg.steps.forEach((st) => (st.mem || []).forEach((e) => {
      const m = /@(0x[0-9a-fA-F]+)/.exec(e.n);
      if (e.k === 'heap' && m && !(e.n in owners)) {
        const o = st.mem.find((x) => x !== e && x.k !== 'heap' && (x.v || '').indexOf(m[1]) >= 0);
        if (o) owners[e.n] = o.fam || famBase(o.n);
      }
    }));
    cfg.steps.forEach((st) => (st.mem || []).forEach((e) => { const f = owners[e.n] || e.fam || famBase(e.n); if (!(f in famIdx)) famIdx[f] = Object.keys(famIdx).length; }));
    const colorOf = (e) => PALETTE[famIdx[owners[e.n] || e.fam || famBase(e.n)] % PALETTE.length];
    const addrOf = (v) => { const m = /0x[0-9a-fA-F]+/.exec(v || ''); return m ? m[0] : null; };

    function arrows() {
      const memEl = $('.st-mem', root);
      const old = $('svg.st-arrows', memEl);
      if (old) old.remove();
      const cells = $$('.cell[data-n]', memEl);
      if (!cells.length) return;
      const box = memEl.getBoundingClientRect();
      const ns = 'http://www.w3.org/2000/svg';
      const svg = document.createElementNS(ns, 'svg');
      svg.setAttribute('class', 'st-arrows');
      svg.setAttribute('width', box.width);
      svg.setAttribute('height', box.height);
      svg.innerHTML = '<defs>' + PALETTE.map((c, k) => '<marker id="sa' + uid + k + '" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto"><path d="M0 0L10 5L0 10z" fill="hsl(' + c + ')"/></marker>').join('') + '</defs>';
      const s = cfg.steps[i];
      const rel = (c) => { const r = c.getBoundingClientRect(); return { l: r.left - box.left, r: r.right - box.left, t: r.top - box.top, b: r.bottom - box.top }; };
      const cx = (R) => (R.l + R.r) / 2, cy = (R) => (R.t + R.b) / 2;
      const bez = (P, t) => { const u = 1 - t; return [0, 1].map((k) => u * u * u * P[0][k] + 3 * u * u * t * P[1][k] + 3 * u * t * t * P[2][k] + t * t * t * P[3][k]); };
      const poly = (P) => { const out = []; for (let t = 0; t <= 1.0001; t += 1 / 24) out.push(bez(P, t)); return out; };
      const ccw = (a, b, c) => (c[1] - a[1]) * (b[0] - a[0]) > (b[1] - a[1]) * (c[0] - a[0]);
      const segX = (a, b, c, d) => ccw(a, c, d) !== ccw(b, c, d) && ccw(a, b, c) !== ccw(a, b, d);
      const crossCount = (L1, L2) => {                                  // ignore the first and last 15% so shared endpoints do not count
        const lo = Math.floor(L1.length * 0.15), hi = Math.ceil(L1.length * 0.85), lo2 = Math.floor(L2.length * 0.15), hi2 = Math.ceil(L2.length * 0.85);
        let n = 0;
        for (let a = lo; a < hi - 1; a++) for (let b = lo2; b < hi2 - 1; b++) if (segX(L1[a], L1[a + 1], L2[b], L2[b + 1])) n++;
        return n;
      };

      // 1. every arrow gets a list of candidate routes
      const specs = [];
      (s.mem || []).forEach((e) => {
        const src = cells.find((c) => c.dataset.n === e.n);
        if (!src) return;
        let dst = null;
        if (e.to) dst = cells.find((c) => c.dataset.n === e.to || c.dataset.n.split(' ')[0] === e.to);
        const a = addrOf(e.v);
        if (!dst && a) dst = cells.find((c) => c !== src && c.dataset.n.indexOf('@' + a) >= 0);
        if (!dst) return;
        const A = rel(src), B = rel(dst);
        const others = cells.filter((c) => c !== src && c !== dst).map(rel);
        const sameRow = Math.abs(cy(A) - cy(B)) < (A.b - A.t) * 0.6;
        const C = {
          right: () => { const x1 = A.r, x2 = B.l - 2, dx = Math.max(28, (x2 - x1) / 2); return B.l - A.r > 10 ? [[x1, cy(A)], [x1 + dx, cy(A)], [x2 - dx, cy(B)], [x2, cy(B)]] : null; },
          rightStub: () => { const x1 = A.r, x2 = B.l - 2; if (B.l - A.r <= 10) return null; const edge = Math.max.apply(null, cells.map(rel).filter((o) => o.l < A.r && o.r > A.l - 1).map((o) => o.r)); const w = Math.max(40, edge - x1 + 26), dx = Math.max(28, (x2 - x1) / 2); return [[x1, cy(A)], [x1 + w, cy(A)], [x2 - dx, cy(B)], [x2, cy(B)]]; },
          left: () => { const x1 = A.l, x2 = B.r + 2, dx = Math.max(28, (x1 - x2) / 2); return A.l - B.r > 10 ? [[x1, cy(A)], [x1 - dx, cy(A)], [x2 + dx, cy(B)], [x2, cy(B)]] : null; },
          vert: () => {
            if (B.b <= A.t) { const m = (A.t + B.b) / 2; return [[cx(A), A.t], [cx(A), m], [cx(B), m], [cx(B), B.b + 2]]; }
            if (B.t >= A.b) { const m = (A.b + B.t) / 2; return [[cx(A), A.b], [cx(A), m], [cx(B), m], [cx(B), B.t - 2]]; }
            return null;
          },
          above: () => { const top = Math.min(A.t, B.t) - 36; return [[cx(A), A.t], [cx(A), top], [cx(B), top], [cx(B), B.t - 2]]; },
          below: () => { const bot = Math.max(A.b, B.b) + 36; return [[cx(A), A.b], [cx(A), bot], [cx(B), bot], [cx(B), B.b + 2]]; },
          loopR: () => { const out = Math.min(Math.max(A.r, B.r) + 34, box.width - 4); return [[A.r, cy(A)], [out, cy(A)], [out, cy(B)], [B.r + 2, cy(B)]]; },
          loopL: () => { const out = Math.max(Math.min(A.l, B.l) - 34, 4); return [[A.l, cy(A)], [out, cy(A)], [out, cy(B)], [B.l - 2, cy(B)]]; }
        };
        const apart = B.l - A.r > 10 || A.l - B.r > 10;
        const order = sameRow ? ['right', 'rightStub', 'left', 'above', 'below'] : apart ? ['right', 'rightStub', 'left', 'vert', 'loopR', 'loopL', 'above', 'below'] : ['vert', 'loopR', 'loopL', 'above', 'below'];
        const hitsCell = (P) => { for (let t = 0.06; t < 0.95; t += 0.04) { const p = bez(P, t); if (others.some((o) => p[0] > o.l + 2 && p[0] < o.r - 2 && p[1] > o.t + 2 && p[1] < o.b - 2)) return true; } return false; };
        const cands = [];
        order.forEach((k, pref) => { const P = C[k](); if (P) cands.push({ P: P, L: poly(P), pref: pref, cell: hitsCell(P) ? 1 : 0 }); });
        if (cands.length) specs.push({ e: e, dst: dst, cands: cands });
      });

      // 2. choose one route per arrow: never through a cell, then fewest arrow-arrow crossings, then the preferred shape
      let best = null, bestScore = Infinity;
      const pick = [];
      (function search(k, score) {
        if (score >= bestScore) return;
        if (k === specs.length) { best = pick.slice(); bestScore = score; return; }
        specs[k].cands.forEach((c, ci) => {
          let add = c.cell * 1000 + c.pref;
          for (let j = 0; j < k; j++) add += 40 * crossCount(c.L, specs[j].cands[pick[j]].L);
          pick[k] = ci;
          search(k + 1, score + add);
        });
      })(0, 0);

      // 3. draw
      let drawn = 0;
      specs.forEach((sp, k) => {
        const P = sp.cands[best[k]].P;
        const path = document.createElementNS(ns, 'path');
        path.setAttribute('d', 'M' + P[0][0] + ' ' + P[0][1] + ' C' + P[1][0] + ' ' + P[1][1] + ' ' + P[2][0] + ' ' + P[2][1] + ' ' + P[3][0] + ' ' + P[3][1]);
        const dead = sp.dst.classList.contains('dead');
        path.setAttribute('class', 'st-arrow' + (dead ? ' dead' : ''));
        path.setAttribute('marker-end', 'url(#sa' + uid + PALETTE.indexOf(colorOf(sp.e)) + ')');
        if (!dead) path.style.stroke = 'hsl(' + colorOf(sp.e) + ')';
        svg.appendChild(path);
        drawn++;
      });
      if (drawn) memEl.appendChild(svg);
    }

    function render() {
      const s = i >= 0 ? cfg.steps[i] : null;
      const p = i > 0 ? cfg.steps[i - 1] : null;
      const cur = s ? [].concat(s.line) : [];
      $$('.ln', root).forEach((el) => el.classList.toggle('cur', cur.indexOf(+el.dataset.l) >= 0));
      const curEl = $('.ln.cur', root);
      if (curEl && curEl.scrollIntoView && false) curEl.scrollIntoView({ block: 'nearest' });
      let mem = '';
      if (s && s.mem && s.mem.length) {
        GROUPS.forEach((g) => {
          const es = s.mem.filter((e) => (e.k || 'stack') === g[0]);
          if (!es.length) return;
          mem += '<div class="mem-group g-' + g[0] + '"><h5>' + g[1] + (g[2] ? ' <small>' + g[2] + '</small>' : '') + '</h5><div class="mem">' + es.map((e) => {
            const before = p && p.mem ? p.mem.find((x) => x.n === e.n) : null;
            const chg = !before || before.v !== e.v || !!before.dead !== !!e.dead;
            return '<div class="cell' + (chg ? ' chg' : '') + (e.dead ? ' dead' : '') + (g[0] === 'heap' ? ' heap' : '') + (e.t && /\*|&|ptr/.test(e.t) ? ' ptr' : '') + '" data-n="' + esc(e.n) + '" style="--vc:hsl(' + colorOf(e) + ')">' +
              '<div class="nm">' + esc(e.n) + (e.t ? ' <span class="ty">' + esc(e.t) + '</span>' : '') + '</div><div class="vl">' + esc(e.v) + '</div>' +
              (e.p ? '<div class="tg">&rarr; ' + esc(e.p) + '</div>' : '') + '</div>';
          }).join('') + '</div></div>';
        });
      }
      $('.st-mem', root).innerHTML = mem || '<div class="mem-group"><div class="mem"><span class="cell empty">(nothing yet)</span></div></div>';
      if (s) arrows();
      $('.st-out', root).textContent = cfg.steps.slice(0, i + 1).map((x) => x.out || '').join('');
      $('.st-note', root).innerHTML = s ? '<span class="st-badge">' + (i + 1) + '</span>' + s.note : (cfg.intro || 'Press <b>Next</b> (or the right arrow key) to run the first line.');
      $('[data-a="back"]', root).disabled = i < 0;
      $('[data-a="next"]', root).disabled = i >= N - 1;
      $$('.st-dot', root).forEach((d, k) => { d.classList.toggle('done', k < i); d.classList.toggle('cur', k === i); });
      $('.info', root).textContent = 'Step ' + (i + 1) + ' of ' + N;
      if (i >= N - 1) stop();
    }
    function stop() {
      if (timer) { clearInterval(timer); timer = null; }
      const b = $('[data-a="play"]', root);
      if (b) b.innerHTML = '&#9654;&#9654; Play';
    }
    function play() {
      if (timer) { stop(); return; }
      if (i >= N - 1) i = -1;
      $('[data-a="play"]', root).innerHTML = '&#10074;&#10074; Pause';
      i++; render();
      timer = setInterval(() => { if (i < N - 1) { i++; render(); } else stop(); }, 1800);
    }
    root.addEventListener('click', (e) => {
      const dot = e.target.closest('.st-dot');
      if (dot) { stop(); i = +dot.dataset.j; render(); return; }
      const b = e.target.closest('button[data-a]');
      if (!b) return;
      if (b.dataset.a === 'play') { play(); return; }
      stop();
      if (b.dataset.a === 'next' && i < N - 1) i++;
      else if (b.dataset.a === 'back' && i >= 0) i--;
      else if (b.dataset.a === 'reset') i = -1;
      render();
    });
    root.addEventListener('keydown', (e) => {                      // arrow keys while the widget has focus
      if (e.target.closest && e.target.closest('input, select, textarea')) return;
      if (e.key === 'ArrowRight' && i < N - 1) { e.preventDefault(); e.stopPropagation(); stop(); i++; render(); }
      else if (e.key === 'ArrowLeft' && i >= 0) { e.preventDefault(); e.stopPropagation(); stop(); i--; render(); }
    });
    window.addEventListener('resize', () => { if (i >= 0) arrows(); });
    render();
  }

  /* ---------------- thread interleaving simulator ---------------- */
  function threadsim(sel, cfg) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.className = 'widget threadsim';

    function parse(line) {
      let m;
      if (/^r\s*=\s*r\s*\+\s*1$/.test(line)) return { k: 'inc' };
      if ((m = /^r\s*=\s*(\w+)$/.exec(line))) return { k: 'load', v: m[1] };
      if ((m = /^(\w+)\s*=\s*r$/.exec(line))) return { k: 'store', v: m[1] };
      if ((m = /^(\w+)\.fetch_add\(1\)$/.exec(line))) return { k: 'fadd', v: m[1] };
      if ((m = /^(\w+)\.lock\(\)$/.exec(line))) return { k: 'lock', m: m[1] };
      if ((m = /^(\w+)\.unlock\(\)$/.exec(line))) return { k: 'unlock', m: m[1] };
      throw new Error('threadsim: cannot parse "' + line + '"');
    }
    const fresh = () => ({
      vars: Object.assign({}, cfg.vars),
      owner: {},
      last: '',
      th: cfg.threads.map((t) => ({ pc: 0, r: 0, src: t.prog, ops: t.prog.map(parse) }))
    });
    const blockedOn = (S, i) => {
      const t = S.th[i];
      if (t.pc >= t.ops.length) return null;
      const o = t.ops[t.pc];
      return o.k === 'lock' && S.owner[o.m] !== undefined ? o.m : null;
    };
    const can = (S, i) => S.th[i].pc < S.th[i].ops.length && blockedOn(S, i) === null;
    const finished = (S) => S.th.every((t) => t.pc >= t.ops.length);
    const stuck = (S) => !finished(S) && S.th.every((_, i) => !can(S, i));

    function exec(S, i) {
      const t = S.th[i];
      const o = t.ops[t.pc];
      let m = cfg.threads[i].name + ': ';
      if (o.k === 'load') { t.r = S.vars[o.v]; m += 'r = ' + o.v + ' (r is now ' + t.r + ')'; }
      else if (o.k === 'inc') { t.r += 1; m += 'r = r + 1 (r is now ' + t.r + ')'; }
      else if (o.k === 'store') { S.vars[o.v] = t.r; m += o.v + ' = r (' + o.v + ' is now ' + t.r + ')'; }
      else if (o.k === 'fadd') { S.vars[o.v] += 1; m += o.v + '.fetch_add(1) in ONE indivisible step (' + o.v + ' is now ' + S.vars[o.v] + ')'; }
      else if (o.k === 'lock') { S.owner[o.m] = i; m += o.m + '.lock() acquired'; }
      else if (o.k === 'unlock') { delete S.owner[o.m]; m += o.m + '.unlock() released'; }
      t.pc++;
      S.last = m;
    }
    function runRandom() {
      const s = fresh();
      for (let g = 0; g < 2000; g++) {
        const ready = s.th.map((_, i) => i).filter((i) => can(s, i));
        if (!ready.length) break;
        exec(s, ready[Math.floor(Math.random() * ready.length)]);
      }
      return s;
    }

    let S = fresh();
    let hist = null;

    function render() {
      const cols = S.th.map((t, i) => {
        const b = blockedOn(S, i);
        const ops = t.src.map((l, k) => {
          const cls = k < t.pc ? 'fin' : k === t.pc ? (b ? 'blocked' : 'next') : '';
          return '<div class="ts-op ' + cls + '">' + esc(l) + '</div>';
        }).join('');
        const ended = t.pc >= t.ops.length;
        return '<div class="ts-col"><h5><span>' + esc(cfg.threads[i].name) + '</span><span class="reg">r = ' + t.r + '</span></h5>' + ops +
          '<div style="margin-top:8px"><button class="btn sm" data-a="step" data-i="' + i + '" type="button"' + (can(S, i) ? '' : ' disabled') + '>Step ' + esc(cfg.threads[i].name) + '</button>' +
          (b ? ' <span class="reg">waiting for ' + esc(b) + '</span>' : ended ? ' <span class="reg">finished</span>' : '') + '</div></div>';
      }).join('');
      const vars = Object.keys(S.vars).map((k) => '<div class="cell' + (k === cfg.show ? ' chg' : '') + '"><div class="nm">shared ' + esc(k) + '</div><div class="vl">' + S.vars[k] + '</div></div>').join('');
      const muts = (cfg.mutexes || []).map((m) => '<div class="cell' + (S.owner[m] !== undefined ? ' dead' : '') + '"><div class="nm">mutex ' + esc(m) + '</div><div class="vl">' +
        (S.owner[m] !== undefined ? 'held by ' + esc(cfg.threads[S.owner[m]].name) : 'free') + '</div></div>').join('');
      let msg = S.last || cfg.help || 'Pick a thread and press its Step button to run one instruction.';
      let cls = '';
      if (stuck(S)) { msg = 'DEADLOCK: every unfinished thread is waiting for a mutex another thread holds. Nothing can ever run again.'; cls = ' bad'; }
      else if (finished(S)) {
        const v = S.vars[cfg.show];
        const ok = cfg.expect === undefined || v === cfg.expect;
        msg = 'All threads finished. ' + cfg.show + ' = ' + v + (cfg.expect === undefined ? '' : ok ? ' (correct)' : ' (expected ' + cfg.expect + ': an update was lost)');
        cls = ok ? ' good' : ' bad';
      }
      let h = '';
      if (hist) {
        const keys = Object.keys(hist.c).sort((a, b) => (a === 'deadlock') - (b === 'deadlock') || (+a) - (+b));
        h = '<div class="hist"><div>' + hist.n + ' random schedules:</div>' + keys.map((k) => {
          const pct = (hist.c[k] / hist.n) * 100;
          const c = k === 'deadlock' ? 'dl' : (cfg.expect !== undefined && +k === cfg.expect ? 'ok' : '');
          return '<div class="row"><span>' + esc(cfg.show) + ' = ' + esc(k) + '</span><span class="bar ' + c + '" style="width:' + Math.max(pct, 0.5) + '%"></span><span>' + pct.toFixed(0) + '%</span></div>';
        }).join('') + '</div>';
      }
      root.innerHTML = '<div class="w-head"><span class="tag">Simulator</span>' + esc(cfg.title || 'Thread interleaving') + '</div><div class="w-body"><div class="ts-cols">' + cols + '</div>' +
        '<div class="ts-state">' + vars + muts + '</div><div class="ts-msg' + cls + '" role="status">' + esc(msg) + '</div>' + h + '</div>' +
        '<div class="w-foot"><button class="btn sm ghost" data-a="reset" type="button">Reset</button><button class="btn sm ghost" data-a="run1" type="button">Finish randomly</button>' +
        '<button class="btn sm" data-a="run500" type="button">Run 500 random schedules</button><span class="info">The scheduler may switch threads between any two instructions.</span></div>';
    }
    root.addEventListener('click', (e) => {
      const b = e.target.closest('button[data-a]');
      if (!b) return;
      const a = b.dataset.a;
      if (a === 'step') exec(S, +b.dataset.i);
      else if (a === 'reset') { S = fresh(); hist = null; }
      else if (a === 'run1') { const done = runRandom(); S = done; }
      else if (a === 'run500') {
        const c = {};
        for (let k = 0; k < 500; k++) { const r = runRandom(); const key = stuck(r) ? 'deadlock' : String(r.vars[cfg.show]); c[key] = (c[key] || 0) + 1; }
        hist = { n: 500, c };
      }
      render();
      /* render() rebuilds the DOM; put keyboard focus back on the equivalent control */
      const again = a === 'step' ? $('button[data-a="step"][data-i="' + b.dataset.i + '"]', root) : $('button[data-a="' + a + '"]', root);
      if (again && !again.disabled) again.focus();
    });
    render();
  }

  /* ---------------- quiz runner ---------------- */
  function quiz(sel, cfg) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.classList.add('quiz');
    const key = 'quiz:' + cfg.id;
    let order, pos, missed, right;
    /* Leitner-style weak list: question text -> box (0 = just missed). Answering right twice in later runs clears it. */
    const wkey = 'weak:' + cfg.id;
    const weak = () => store.get(wkey, {});
    const qid = (q) => q.q + (q.code ? '\n' + q.code.trim() : '');
    const weakList = () => { const w = weak(); return cfg.questions.filter((q) => qid(q) in w); };
    function record(q, ok) {
      const w = weak();
      const k = qid(q);
      if (!ok) w[k] = 0;
      else if (k in w) { w[k]++; if (w[k] >= 2) delete w[k]; }
      store.set(wkey, w);
    }
    const lessonHref = () => { const t = topicOf(document.body.dataset.topic); return t ? t.file : 'index.html'; };

    const codeHtml = (c) => '<figure class="code"><pre><code>' + highlight(clean(c)) + '</code></pre></figure>';

    function intro() {
      const best = store.get(key, null);
      root.innerHTML = '<div class="result"><p><b>' + cfg.questions.length + ' questions.</b> Pick an answer to see the explanation straight away. ' +
        'Questions and answers are shuffled each time.' + (best ? ' Your best score so far: <b>' + best.best + '%</b>.' : '') + '</p>' +
        '<div class="pickrow"><button class="btn" id="qstart" type="button">Start the quiz</button>' +
        (weakList().length ? '<button class="btn ghost" id="qweak" type="button">Review ' + weakList().length + ' weak question' + (weakList().length > 1 ? 's' : '') + '</button>' : '') + '</div></div>';
      $('#qstart', root).addEventListener('click', () => begin(cfg.questions));
      const wb = $('#qweak', root);
      if (wb) wb.addEventListener('click', () => begin(weakList()));
    }
    function begin(list) {
      order = shuffle(list.slice());
      pos = 0; missed = []; right = 0;
      ask();
    }
    function ask() {
      const q = order[pos];
      const opts = shuffle(q.opts.map((t, i) => ({ t, ok: i === q.a })));
      root.innerHTML = '<div class="q-top"><span>Question ' + (pos + 1) + ' of ' + order.length + '</span><span>' + right + ' correct</span></div>' +
        '<div class="q-bar"><span style="width:' + (pos / order.length) * 100 + '%"></span></div>' +
        '<p class="q-text">' + fmt(q.q) + '</p>' + (q.code ? codeHtml(q.code) : '') +
        '<div class="opts" role="group" aria-label="Answer choices">' + opts.map((o, i) => '<button class="opt" type="button" data-i="' + i + '"><span class="k">' + 'ABCDEFG'[i] + '</span><span>' + fmt(o.t) + '</span></button>').join('') + '</div><div class="fb" role="status" aria-live="polite"></div>';
      let locked = false;
      $$('.opt', root).forEach((b) => b.addEventListener('click', () => {
        if (locked) return;
        locked = true;
        const pick = opts[+b.dataset.i];
        $$('.opt', root).forEach((x, i) => { x.disabled = true; if (opts[i].ok) x.classList.add('right'); });
        if (!pick.ok) b.classList.add('wrong');
        if (pick.ok) right++; else missed.push(q);
        record(q, pick.ok);
        const last = pos === order.length - 1;
        $('.fb', root).innerHTML = '<div class="why"><b class="' + (pick.ok ? 'ok">Correct.' : 'no">Not quite.') + '</b> ' + fmt(q.why) + '</div>' +
          '<button class="btn" id="qnext" type="button">' + (last ? 'See results' : 'Next question') + '</button>';
        $('#qnext', root).addEventListener('click', () => { pos++; if (pos >= order.length) finish(); else ask(); });
        $('#qnext', root).focus();
      }));
    }
    function finish() {
      const pct = Math.round((right / order.length) * 100);
      const prev = store.get(key, null);
      const full = order.length === cfg.questions.length;
      store.set(key, { best: full ? Math.max(pct, prev ? prev.best : 0) : (prev ? prev.best : 0), last: full ? pct : (prev ? prev.last : pct), total: cfg.questions.length });
      const verdict = pct >= 90 ? 'Excellent. You are interview-ready on this topic.' : pct >= 70 ? 'Solid. Review the explanations below and retry the ones you missed.' :
        pct >= 50 ? 'Getting there. Re-read the lesson sections for the questions you missed.' : 'Go back through the lesson, then try again. This is a normal first score for new material.';
      root.innerHTML = '<div class="result ' + (pct >= 70 ? 'good' : 'bad') + '"><div class="score">' + right + ' / ' + order.length + ' (' + pct + '%)</div><p>' + verdict + '</p></div>' +
        (missed.length ? '<h3>Questions to review</h3>' + missed.map((q) => '<div class="miss"><div class="qq">' + fmt(q.q) + '</div>' + (q.code ? codeHtml(q.code) : '') +
          '<div><b class="ok" style="color:var(--good)">Answer:</b> ' + fmt(q.opts[q.a]) + '</div><div style="color:var(--muted)">' + fmt(q.why) + '</div>' +
          '<div><a href="' + lessonHref() + (q.sec ? '#' + q.sec : '') + '">Re-read this in the lesson &rarr;</a></div></div>').join('') : '') +
        '<div class="pickrow">' + (missed.length ? '<button class="btn" id="qretry" type="button">Retry the ' + missed.length + ' missed</button>' : '') +
        '<button class="btn ghost" id="qagain" type="button">Restart the full quiz</button></div>';
      const r = $('#qretry', root);
      if (r) r.addEventListener('click', () => begin(missed.slice()));
      $('#qagain', root).addEventListener('click', () => begin(cfg.questions));
    }
    intro();
  }

  /* ---------------- home page ---------------- */
  function home() {
    const grid = $('#topics');
    if (!grid) return;
    grid.className = 'cards';
    grid.innerHTML = TOPICS.map((t) => {
      const total = store.get('total:' + t.id, 0);
      const done = store.get('done:' + t.id, []).length;
      const q = store.get('quiz:' + t.id, null);
      const pct = total ? Math.round((done / total) * 100) : 0;
      return '<div class="card"><span class="num">TOPIC ' + t.n + '</span><h3>' + esc(t.title) + '</h3><p>' + esc(t.blurb) + '</p>' +
        '<div class="meta"><span class="pill">' + t.time + '</span>' + (t.hot ? '<span class="pill hot">named in the job description</span>' : '') +
        '<span class="pill">' + (total ? done + '/' + total + ' sections' : 'not started') + '</span>' + (q ? '<span class="pill">quiz best ' + q.best + '%</span>' : '') +
        (Object.keys(store.get('weak:' + t.id, {})).length ? '<span class="pill hot">' + Object.keys(store.get('weak:' + t.id, {})).length + ' to review</span>' : '') + '</div>' +
        '<div class="bar-track"><span style="width:' + pct + '%"></span></div>' +
        '<div class="row"><a class="btn sm" href="' + t.file + '">Lesson</a><a class="btn sm ghost" href="' + t.quiz + '">Quiz</a></div></div>';
    }).join('');
    const rs = $('#resume');
    const li = store.get('lastinfo', null);
    const lt = li && topicOf(li.id);
    if (rs) rs.innerHTML = lt ? '<a class="resume" href="' + lt.file + '#' + esc(li.sec) + '"><small>Continue where you left off</small><b>' + esc(lt.title) + ', section ' + li.n + ' of ' + li.of + '</b><span>' + esc(li.title) + '</span><i>&rarr;</i></a>' : '';
    const rb = $('#reset-progress');
    if (rb) {
      rb.addEventListener('click', () => {
        if (!confirm('Clear all lesson progress and quiz scores stored in this browser?')) return;
        try { Object.keys(localStorage).filter((k) => k.indexOf('cpptrain:') === 0 && k !== 'cpptrain:theme').forEach((k) => localStorage.removeItem(k)); } catch (e) { /* ignore */ }
        home();
      });
    }
  }

  /* ---------------- export / import of progress ---------------- */
  /* Progress lives in this browser's localStorage only. The code below turns the ticks and best
     scores into a short text code that can be pasted into another browser or machine. */
  const PROGRESS_KEY = /^(checklist|mock:missed|(done|total|quiz):[a-z][a-z0-9]*)$/;
  const hash32 = (s) => {
    let h = 0x811c9dc5;
    for (let i = 0; i < s.length; i++) { h ^= s.charCodeAt(i); h = Math.imul(h, 0x01000193) >>> 0; }
    return ('00000000' + h.toString(16)).slice(-8);
  };
  const b64e = (s) => btoa(s).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/, '');
  const b64d = (s) => atob(s.replace(/-/g, '+').replace(/_/g, '/') + '='.repeat((4 - (s.length % 4)) % 4));

  function collectProgress() {
    const d = {};
    try {
      Object.keys(localStorage).forEach((k) => {
        if (k.indexOf('cpptrain:') !== 0) return;
        const name = k.slice(9);
        if (PROGRESS_KEY.test(name)) d[name] = JSON.parse(localStorage.getItem(k));
      });
    } catch (e) { /* storage unavailable */ }
    return d;
  }
  function makeCode() {
    const p = b64e(JSON.stringify({ v: 1, s: CT.schemaVersion(), d: collectProgress() }));
    return 'CPP1.' + p + '.' + hash32(p);
  }
  function parseCode(text) {
    const m = /^CPP1\.([A-Za-z0-9_-]+)\.([0-9a-f]{8})$/.exec(text.replace(/\s+/g, ''));
    if (!m) throw new Error('That does not look like a progress code. It should start with CPP1.');
    if (hash32(m[1]) !== m[2]) throw new Error('The code is damaged: a character was lost or changed while copying. Copy it again.');
    let obj;
    try { obj = JSON.parse(b64d(m[1])); } catch (e) { throw new Error('The code could not be read.'); }
    if (!obj || obj.v !== 1 || !obj.d || typeof obj.d !== 'object') throw new Error('Unsupported code version.');
    const data = {};
    let count = 0;
    Object.keys(obj.d).forEach((k) => {
      const v = obj.d[k];
      if (!PROGRESS_KEY.test(k)) return;
      if (k === 'checklist' || k === 'mock:missed' || k.indexOf('done:') === 0) {
        if (Array.isArray(v) && v.length <= 300 && v.every((x) => typeof x === 'string' && /^[\w-]{1,40}$/.test(x))) { data[k] = v; count += v.length; }
      } else if (k.indexOf('total:') === 0) {
        if (Number.isInteger(v) && v >= 0 && v <= 1000) data[k] = v;
      } else if (v && [v.best, v.last, v.total].every((x) => Number.isInteger(x) && x >= 0 && x <= 1000)) {
        data[k] = { best: v.best, last: v.last, total: v.total };
        count++;
      }
    });
    if (!Object.keys(data).length) throw new Error('The code contains no progress.');
    const schema = Number.isInteger(obj.s) && obj.s >= 1 && obj.s <= 99 ? obj.s : 1;
    return { data, count, schema };
  }
  function applyProgress(data, replace, schema) {
    if (replace) {
      try { Object.keys(localStorage).forEach((k) => { if (k.indexOf('cpptrain:') === 0 && PROGRESS_KEY.test(k.slice(9))) localStorage.removeItem(k); }); } catch (e) { /* ignore */ }
    }
    Object.keys(data).forEach((k) => {
      const v = data[k];
      const cur = store.get(k, null);
      if (cur === null) store.set(k, v);
      else if (Array.isArray(v)) store.set(k, Array.from(new Set([].concat(cur, v))));      // union of ticks
      else if (typeof v === 'number') store.set(k, Math.max(cur, v));
      else if (v.best > (cur.best || 0)) store.set(k, v);                                    // keep the better quiz score
    });
    // A code from an older schema holds old ids: mark the browser as old so the migrations run again after the reload.
    if (schema < CT.schemaVersion()) store.set('schema', replace ? schema : Math.min(store.get('schema', CT.schemaVersion()), schema));
  }

  function progressTools(el) {
    el.className = 'widget';
    el.innerHTML = '<div class="w-head"><span class="tag">Backup</span>Save or move your progress</div><div class="w-body">' +
      '<p class="ck-note">Your progress is stored only in this browser. To continue on another browser or machine, show a code here and import it there. The code covers checklist ticks, lesson section ticks and best quiz scores.</p>' +
      '<div class="pickrow"><button class="btn sm" id="pt-export" type="button">Show my progress code</button><button class="btn sm ghost" id="pt-copy" type="button" hidden>Copy</button></div>' +
      '<textarea id="pt-out" class="pt-box" rows="3" readonly hidden aria-label="Your progress code"></textarea>' +
      '<p style="margin:16px 0 6px"><label for="pt-in"><b>Import a code</b></label></p>' +
      '<textarea id="pt-in" class="pt-box" rows="3" placeholder="Paste a code that starts with CPP1." spellcheck="false"></textarea>' +
      '<div class="pickrow"><button class="btn sm" id="pt-import" type="button">Import</button><label><input type="checkbox" id="pt-replace"> Replace the progress in this browser instead of merging</label></div>' +
      '<div class="result" id="pt-msg" role="status" aria-live="polite" hidden></div></div>';
    const q = (id) => $('#' + id, el);
    const say = (text, cls) => { const m = q('pt-msg'); m.hidden = false; m.className = 'result ' + (cls || ''); m.textContent = text; };
    q('pt-export').addEventListener('click', () => {
      if (!Object.keys(collectProgress()).length) { say('Nothing to export yet. Tick a checklist item or finish a quiz first.'); return; }
      const out = q('pt-out');
      out.value = makeCode();
      out.hidden = false;
      q('pt-copy').hidden = false;
      out.focus();
      out.select();
      say('Copy this code and paste it into the Import box on the other machine.', 'good');
    });
    q('pt-copy').addEventListener('click', () => {
      const out = q('pt-out');
      out.select();
      try { navigator.clipboard.writeText(out.value).then(() => say('Copied.', 'good'), () => say('Press Ctrl+C to copy the selected code.')); } catch (e) { say('Press Ctrl+C to copy the selected code.'); }
    });
    q('pt-import').addEventListener('click', () => {
      let parsed;
      try { parsed = parseCode(q('pt-in').value); } catch (e) { say(e.message, 'bad'); return; }
      const replace = q('pt-replace').checked;
      if (replace && !confirm('Replace the checklist ticks, lesson ticks and quiz scores in this browser with the imported ones?')) return;
      applyProgress(parsed.data, replace, parsed.schema);
      say('Imported ' + parsed.count + ' item' + (parsed.count === 1 ? '' : 's') + (replace ? ' (replaced)' : ' (merged)') + '. Reloading the page...', 'good');
      setTimeout(() => location.reload(), 900);
    });
  }

  /* ---------------- boot ---------------- */
  /* ---------------- study checklist page ---------------- */
  function checklist(main) {
    const KEY = 'checklist';
    const boxes = $$('input[type="checkbox"][data-ck]', main);
    const done = new Set(store.get(KEY, []));
    const sections = $$('section[data-ck-section]', main);
    const sum = $('#ck-summary', main);

    function paint() {
      boxes.forEach((b) => b.closest('label').classList.toggle('on', b.checked));
      sections.forEach((s) => {
        const bs = $$('input[data-ck]', s);
        const n = bs.filter((b) => b.checked).length;
        const c = $('.ck-count', s);
        if (c) c.textContent = n + ' / ' + bs.length;
        s.classList.toggle('complete', bs.length > 0 && n === bs.length);
      });
      const total = boxes.length;
      const n = boxes.filter((b) => b.checked).length;
      if (sum) {
        $('.ck-text', sum).textContent = n + ' of ' + total + ' done' + (total && n === total ? ': everything is ticked. Good luck!' : '');
        const bar = $('.bar-track', sum);
        bar.setAttribute('aria-valuenow', String(n));
        bar.setAttribute('aria-valuemax', String(total));
        $('span', bar).style.width = (total ? (n / total) * 100 : 0) + '%';
      }
    }

    boxes.forEach((b) => {
      b.checked = done.has(b.dataset.ck);
      b.addEventListener('change', () => {
        if (b.checked) done.add(b.dataset.ck); else done.delete(b.dataset.ck);
        store.set(KEY, Array.from(done));
        paint();
      });
    });

    // Live results from the lessons and quizzes completed on this device.
    $$('[data-lesson]', main).forEach((el) => {
      const id = el.dataset.lesson;
      const total = store.get('total:' + id, 0);
      el.textContent = total ? store.get('done:' + id, []).length + '/' + total + ' sections' : 'not started';
    });
    $$('[data-quiz]', main).forEach((el) => {
      const q = store.get('quiz:' + el.dataset.quiz, null);
      el.textContent = q ? 'quiz best ' + q.best + '%' : 'quiz not taken';
    });

    const reset = $('#ck-reset', main);
    if (reset) {
      reset.addEventListener('click', () => {
        if (!confirm('Untick every item on this checklist? Lesson progress and quiz scores are not affected.')) return;
        done.clear();
        store.set(KEY, []);
        boxes.forEach((b) => { b.checked = false; });
        paint();
      });
    }
    paint();
  }

  /* ---------------- level check: a mixed quiz that scores each topic ---------------- */
  const ASSESS_COUNTS = {};                                  // lesson id -> questions drawn (the `assess` field in lessons.js)
  TOPICS.forEach((t) => { if (t.assess > 0) ASSESS_COUNTS[t.id] = t.assess; });
  function assess(sel) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.classList.add('quiz');
    const qid = (q) => q.q + (q.code ? '\n' + q.code.trim() : '');
    const codeHtml = (c) => '<figure class="code"><pre><code>' + highlight(clean(c)) + '</code></pre></figure>';
    const secTitle = (t, q) => {
      const e = q.sec && (CT.searchIndex || []).find((x) => x.f === t.file && x.id === q.sec);
      return e ? e.h : 'the lesson';
    };
    const secHref = (t, q) => t.file + (q.sec ? '#' + q.sec : '');
    let order, pos, onKey = null;

    function intro() {
      const total = Object.keys(ASSESS_COUNTS).reduce((n, k) => n + ASSESS_COUNTS[k], 0);
      const last = store.get('assess:last', null);
      root.innerHTML = '<div class="result"><p><b>' + total + ' multiple-choice questions</b> from every topic, weighted towards the ones named in the job description (about 20 minutes). ' +
        'No explanations until the end, like a real test. If you would be guessing, press <b>I don&rsquo;t know</b> (or key 0) instead: a lucky guess would hide a gap, and it counts the same as a wrong answer. Go back and change answers freely with the buttons or the &larr; &rarr; keys. ' +
        'At the end you get your level, a score per topic, and the lesson section to review for every question.' +
        (last ? ' Last result: <b>' + last.pct + '%</b>.' : '') + '</p><div class="pickrow"><button class="btn" id="astart" type="button">Start</button></div></div>';
      $('#astart', root).addEventListener('click', begin);
    }
    function begin() {
      order = [];
      Object.keys(ASSESS_COUNTS).forEach((id) => {
        const d = CT.quizData[id];
        if (d) shuffle(d.questions.slice()).slice(0, ASSESS_COUNTS[id]).forEach((q) => order.push({ q: q, topic: id, opts: shuffle(q.opts.map((t, i) => ({ t: t, ok: i === q.a }))), pick: -1, dk: false }));
      });
      order = shuffle(order);
      pos = 0;
      if (onKey) document.removeEventListener('keydown', onKey);
      onKey = (e) => {
        if (e.ctrlKey || e.metaKey || e.altKey || /^(INPUT|TEXTAREA|SELECT)$/.test((e.target.tagName || ''))) return;
        const k = e.key;
        if (k === 'ArrowRight' && pos < order.length - 1) { e.preventDefault(); pos++; ask(); }
        else if (k === 'ArrowLeft' && pos > 0) { e.preventDefault(); pos--; ask(); }
        else if (/^[a-gA-G1-7]$/.test(k)) {
          const i = /\d/.test(k) ? +k - 1 : k.toLowerCase().charCodeAt(0) - 97;
          if (i < order[pos].opts.length) { order[pos].pick = i; order[pos].dk = false; ask(); }
        }
        else if (k === '0' || k === 'x' || k === 'X') { order[pos].pick = -1; order[pos].dk = true; ask(); }
      };
      document.addEventListener('keydown', onKey);
      ask();
    }
    function ask() {
      const item = order[pos], q = item.q;
      const answered = order.filter((x) => x.pick >= 0 || x.dk).length;
      root.innerHTML = '<div class="q-top"><span>Question ' + (pos + 1) + ' of ' + order.length + '</span><span>' + esc(topicOf(item.topic).title) + ' &middot; ' + answered + ' answered</span></div>' +
        '<div class="q-bar"><span style="width:' + (answered / order.length) * 100 + '%"></span></div>' +
        '<p class="q-text">' + fmt(q.q) + '</p>' + (q.code ? codeHtml(q.code) : '') +
        '<div class="opts" role="group" aria-label="Answer choices">' + item.opts.map((o, i) => '<button class="opt' + (item.pick === i ? ' picked' : '') + '" type="button" data-i="' + i + '" aria-pressed="' + (item.pick === i) + '"><span class="k">' + 'ABCDEFG'[i] + '</span><span>' + fmt(o.t) + '</span></button>').join('') + '</div>' +
        '<div class="pickrow"><button class="btn ghost dk' + (item.dk ? ' picked' : '') + '" id="adk" type="button" aria-pressed="' + item.dk + '">I don&rsquo;t know (counts as not known, not as a guess)</button></div>' +
        '<div class="pickrow anav"><button class="btn ghost" id="aprev" type="button"' + (pos === 0 ? ' disabled' : '') + '>&larr; Back</button>' +
        (pos < order.length - 1 ? '<button class="btn" id="anext" type="button">Next &rarr;</button>' : '<button class="btn" id="afinish" type="button">Finish and see results</button>') + '</div>' +
        '<div class="qdots" aria-label="Jump to a question">' + order.map((x, i) => '<button type="button" class="qdot' + (x.pick >= 0 ? ' done' : x.dk ? ' dk' : '') + (i === pos ? ' cur' : '') + '" data-j="' + i + '" aria-label="Question ' + (i + 1) + '">' + (i + 1) + '</button>').join('') + '</div>';
      $$('.opt', root).forEach((b) => b.addEventListener('click', () => { item.pick = +b.dataset.i; item.dk = false; ask(); }));
      $('#adk', root).addEventListener('click', () => { item.dk = !item.dk; if (item.dk) item.pick = -1; ask(); });
      $$('.qdot', root).forEach((b) => b.addEventListener('click', () => { pos = +b.dataset.j; ask(); }));
      $('#aprev', root).addEventListener('click', () => { if (pos > 0) { pos--; ask(); } });
      const nx = $('#anext', root);
      if (nx) nx.addEventListener('click', () => { pos++; ask(); });
      const fin = $('#afinish', root);
      if (fin) fin.addEventListener('click', () => {
        const left = order.length - answered;
        if (left && !confirm(left + ' question' + (left > 1 ? 's are' : ' is') + ' unanswered and will count as not known. Finish anyway?')) return;
        finish();
      });
    }
    function finish() {
      if (onKey) { document.removeEventListener('keydown', onKey); onKey = null; }
      const ok = (x) => x.pick >= 0 && x.opts[x.pick].ok;
      const per = {};
      order.forEach((x) => {
        const p = per[x.topic] || (per[x.topic] = { right: 0, n: 0 });
        p.n++;
        if (ok(x)) p.right++;
        const w = store.get('weak:' + x.topic, {});            // feed the same weak-question list as the topic quizzes
        const k = qid(x.q);
        if (!ok(x)) w[k] = 0; else if (k in w) { w[k]++; if (w[k] >= 2) delete w[k]; }
        store.set('weak:' + x.topic, w);
      });
      const right = order.filter(ok).length;
      const unknown = order.filter((x) => x.dk || x.pick < 0).length;
      const pct = Math.round((right / order.length) * 100);
      const level = pct >= 80 ? 'Interview-ready' : pct >= 60 ? 'Solid, with gaps' : pct >= 40 ? 'Developing' : 'Early stage';
      const advice = pct >= 80 ? 'Keep sharp: use the mock interview and retake the quizzes of your weakest topics.' :
        pct >= 60 ? 'Fix the weakest topics below, then retest.' :
        pct >= 40 ? 'Work through the lessons of the weakest topics first, then their quizzes.' : 'Start with the lessons in order (basics first), then take each quiz. This is a normal first score.';
      store.set('assess:last', { pct: pct });
      const rows = Object.keys(per).map((id) => ({ id: id, p: per[id], pc: Math.round((per[id].right / per[id].n) * 100) }))
        .sort((a, b) => a.pc - b.pc || (topicOf(b.id).hot ? 1 : 0) - (topicOf(a.id).hot ? 1 : 0));
      // sections to review: every section a question pointed at, missed ones first
      const secs = {};
      order.forEach((x) => {
        const t = topicOf(x.topic);
        const key = x.topic + '#' + (x.q.sec || '');
        const s = secs[key] || (secs[key] = { t: t, q: x.q, missed: 0, n: 0 });
        s.n++;
        if (!ok(x)) s.missed++;
      });
      const secList = Object.keys(secs).map((k) => secs[k]).sort((a, b) => b.missed - a.missed || a.t.n - b.t.n);
      root.innerHTML = '<div class="result ' + (pct >= 60 ? 'good' : 'bad') + '"><div class="score">' + right + ' / ' + order.length + ' (' + pct + '%): ' + level + '</div><p>' + advice + '</p>' +
        '<p style="color:var(--muted)">' + unknown + ' marked &ldquo;don&rsquo;t know&rdquo; or skipped, ' + (order.length - right - unknown) + ' answered wrongly. Honest gaps are the most useful result: start with the &ldquo;don&rsquo;t know&rdquo; ones.</p></div>' +
        '<h3>By topic, weakest first</h3>' + rows.map((r) => { const t = topicOf(r.id); return '<div class="miss"><div class="qq">' + esc(t.n + '. ' + t.title) + (t.hot ? ' <span class="pill hot">in the job description</span>' : '') + ': ' + r.p.right + ' / ' + r.p.n + '</div>' +
          '<div class="bar-track"><span style="width:' + r.pc + '%"></span></div><div class="pickrow"><a class="btn sm" href="' + t.file + '">Lesson</a><a class="btn sm ghost" href="' + t.quiz + '">Topic quiz</a></div></div>'; }).join('') +
        '<p style="color:var(--muted)">Only 2 to 5 questions per topic, so treat each topic score as a hint, not a verdict.</p>' +
        '<h3>Sections to review</h3><p style="color:var(--muted)">Every section these questions drew on, missed ones first. Worth a read even when you answered correctly.</p>' +
        '<ul class="seclist">' + secList.map((s) => '<li class="' + (s.missed ? 'miss-sec' : 'ok-sec') + '"><a href="' + secHref(s.t, s.q) + '">' + esc(s.t.n + '. ' + s.t.title + ' › ' + secTitle(s.t, s.q)) + '</a> <span>' +
          (s.missed ? s.missed + ' of ' + s.n + ' missed' : 'all correct') + '</span></li>').join('') + '</ul>' +
        '<h3>Every question</h3>' + order.map((x, i) => { const t = topicOf(x.topic), q = x.q; const good = ok(x);
          return '<details class="aq ' + (good ? 'good' : x.dk ? 'dk' : 'bad') + '"><summary><span class="mark">' + (good ? '&#10003;' : x.dk ? '?' : x.pick < 0 ? '&ndash;' : '&#10007;') + '</span> ' + (i + 1) + '. ' + fmt(q.q) + '</summary><div>' +
            (q.code ? codeHtml(q.code) : '') +
            (x.pick >= 0 && !good ? '<div><b style="color:var(--bad)">Your answer:</b> ' + fmt(x.opts[x.pick].t) + '</div>' : x.dk ? '<div><b style="color:var(--warn)">You marked this &ldquo;don&rsquo;t know&rdquo;.</b></div>' : '<div><b style="color:var(--bad)">Not answered.</b></div>') +
            '<div><b style="color:var(--good)">Answer:</b> ' + fmt(q.opts[q.a]) + '</div><div style="color:var(--muted)">' + fmt(q.why) + '</div>' +
            '<div><a href="' + secHref(t, q) + '">Review: ' + esc(secTitle(t, q)) + ' &rarr;</a></div></div></details>'; }).join('') +
        '<div class="pickrow"><button class="btn" id="aagain" type="button">Take it again with new questions</button></div>';
      $('#aagain', root).addEventListener('click', begin);
    }
    intro();
  }

  /* ---------------- mock interview: random cheat-sheet questions ---------------- */
  function mock() {
    const root = $('#mock');
    const MKEY = 'mock:missed';
    let bank = null, order = [], pos = 0, got = 0, miss = [];
    async function load() { return (CT.mockBank || []).slice(); }   // generated by tools/build-mock-bank.mjs
    function setup() {
      const missedIds = new Set(store.get(MKEY, []));
      const nMiss = bank.filter((c) => missedIds.has(c.id)).length;
      root.innerHTML = '<div class="widget"><div class="w-head"><span class="tag">Setup</span>' + bank.length + ' questions available</div><div class="w-body">' +
        '<div class="pickrow"><label for="mk-topic">Topic:</label><select id="mk-topic"><option value="all">All topics</option>' +
        TOPICS.map((t) => '<option value="' + t.id + '">' + esc(t.n + '. ' + t.title) + '</option>').join('') + '</select></div>' +
        '<div class="pickrow"><button class="btn" id="mk-start" type="button">Start</button>' +
        (nMiss ? '<button class="btn ghost" id="mk-missed" type="button">Missed only (' + nMiss + ')</button>' : '') + '</div></div></div>';
      $('#mk-start', root).addEventListener('click', () => {
        const v = $('#mk-topic', root).value;
        begin(bank.filter((c) => v === 'all' || c.topic === v));
      });
      const mb = $('#mk-missed', root);
      if (mb) mb.addEventListener('click', () => begin(bank.filter((c) => missedIds.has(c.id))));
    }
    function begin(list) { order = shuffle(list.slice()); pos = 0; got = 0; miss = []; ask(); }
    function mark(c, ok) {
      const m = new Set(store.get(MKEY, []));
      if (ok) { m.delete(c.id); got++; } else { m.add(c.id); miss.push(c); }
      store.set(MKEY, Array.from(m));
      pos++;
      ask();
    }
    function ask() {
      if (pos >= order.length) { finish(); return; }
      const c = order[pos];
      root.innerHTML = '<div class="widget"><div class="w-head"><span class="tag">' + (pos + 1) + ' / ' + order.length + '</span>' + esc(topicOf(c.topic).title) + '</div><div class="w-body">' +
        '<p class="mock-q">' + c.q + '</p><div id="mk-a" class="mock-a" hidden>' + c.a + '</div>' +
        '<div class="pickrow" id="mk-btns"><button class="btn" id="mk-show" type="button">Show answer</button></div></div></div>';
      const show = $('#mk-show', root);
      show.focus();
      show.addEventListener('click', () => {
        $('#mk-a', root).hidden = false;
        $('#mk-btns', root).innerHTML = '<button class="btn" id="mk-got" type="button">Got it</button><button class="btn ghost" id="mk-no" type="button">Missed it</button>';
        $('#mk-got', root).addEventListener('click', () => mark(c, true));
        $('#mk-no', root).addEventListener('click', () => mark(c, false));
        $('#mk-got', root).focus();
      });
    }
    function finish() {
      root.innerHTML = '<div class="result"><p><b>' + got + ' of ' + order.length + '</b> answered correctly.</p><div class="pickrow">' +
        (miss.length ? '<button class="btn" id="mk-retry" type="button">Retry the ' + miss.length + ' missed</button>' : '') +
        '<button class="btn ghost" id="mk-again" type="button">New round</button></div></div>';
      const rt = $('#mk-retry', root);
      if (rt) rt.addEventListener('click', () => begin(miss));
      $('#mk-again', root).addEventListener('click', setup);
    }
    root.textContent = 'Loading questions...';
    load().then((b) => {
      bank = b;
      if (!bank.length) { root.textContent = 'No questions found. Run node tools/build-mock-bank.mjs.'; return; }
      setup();
    });
  }

  function boot() {
    CT.migrate(store);
    const kind = document.body.dataset.kind || 'lesson';
    renderCodeBlocks();
    buildHeader(kind);
    const main = $('main');
    if (kind === 'lesson' && main) { buildLesson(main); buildPager(main, 'lesson'); }
    else if (kind === 'quiz' && main) { main.classList.add('solo'); buildPager(main, 'quiz'); }
    else if (kind === 'home') { if (main) main.classList.add('solo'); home(); }
    else if (kind === 'checklist' && main) { main.classList.add('solo'); checklist(main); }
    else if (kind === 'mock' && main) { main.classList.add('solo'); }
    else if (kind === 'assess' && main) { main.classList.add('solo'); }
    const pt = $('#progress-tools');
    if (pt) progressTools(pt);
  }

  /* offline support: manifest + service worker (only on http/https) */
  if (/^https?:$/.test(location.protocol)) {
    const link = document.createElement('link');
    link.rel = 'manifest';
    link.href = 'manifest.webmanifest';
    document.head.appendChild(link);
    if ('serviceWorker' in navigator) navigator.serviceWorker.register('sw.js').catch(() => { /* optional */ });
  }

  window.CT = Object.assign(window.CT || {}, { quizData: {}, TOPICS, stepper, threadsim, quiz, assess, mock, highlight, fmt, esc });
  boot();
})();
