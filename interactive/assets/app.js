/* C++ Interview Prep: shared lesson/quiz engine. Vanilla JS, no dependencies.
 *
 * A page declares <body data-topic="..." data-kind="lesson|quiz|home"> and this
 * script builds the header, table of contents, progress tracking and pager.
 * Page scripts then call CT.stepper(), CT.threadsim() or CT.quiz().
 */
(function () {
  'use strict';

  const TOPICS = [
    { id: 'basics', n: 1, title: 'C++ Basics & Pointers', file: '01-basics.html', quiz: '01-basics-quiz.html', time: '60 min', hot: false,
      blurb: 'Types, functions, memory, pointers, references, const and dynamic allocation, built up from zero.' },
    { id: 'oop', n: 2, title: 'Object-Oriented Programming', file: '02-oop.html', quiz: '02-oop-quiz.html', time: '60 min', hot: false,
      blurb: 'Classes, constructors, rule of 3/5/0, inheritance, virtual functions, abstract classes, operator overloading.' },
    { id: 'core', n: 3, title: 'Core Language & Modern C++', file: '03-core-language.html', quiz: '03-core-language-quiz.html', time: '75 min', hot: true,
      blurb: 'RAII, move semantics, smart pointers, lambdas, exceptions, casts and the C++11/14/17 features interviewers ask about.' },
    { id: 'stl', n: 4, title: 'The STL', file: '04-stl.html', quiz: '04-stl-quiz.html', time: '60 min', hot: false,
      blurb: 'Containers, iterators, algorithms, complexity, iterator invalidation and how to choose the right container.' },
    { id: 'templates', n: 5, title: 'Templates', file: '05-templates.html', quiz: '05-templates-quiz.html', time: '60 min', hot: true,
      blurb: 'Function and class templates, specialization, forwarding references, variadic templates, type traits, if constexpr.' },
    { id: 'patterns', n: 6, title: 'Design Patterns', file: '06-design-patterns.html', quiz: '06-design-patterns-quiz.html', time: '50 min', hot: true,
      blurb: 'Singleton, Factory, Strategy, Observer and State in modern C++, plus the idioms you should recognise.' },
    { id: 'threads', n: 7, title: 'Multithreading', file: '07-multithreading.html', quiz: '07-multithreading-quiz.html', time: '90 min', hot: true,
      blurb: 'From your first thread to mutexes, deadlocks, atomics, condition variables, futures and thread pools.' }
  ];

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

  function renderCodeBlocks() {
    $$('script[type="text/x-cpp"],script[type="text/x-out"]').forEach((s) => {
      const isOut = s.type === 'text/x-out';
      const txt = clean(s.textContent);
      const fig = document.createElement('figure');
      fig.className = 'code' + (isOut ? ' out' : '');
      const title = s.getAttribute('data-title');
      fig.innerHTML = (title || isOut ? '<figcaption>' + (title ? esc(title) : '') + '</figcaption>' : '') +
        '<pre><code>' + (isOut ? esc(txt) : highlight(txt)) + '</code></pre>' +
        (isOut ? '' : '<button class="copy" type="button">Copy</button>');
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

  function buildHeader(kind) {
    const cur = document.body.dataset.topic;
    const links = TOPICS.map((t) =>
      '<a href="' + t.file + '"' + (t.id === cur && kind === 'lesson' ? ' class="cur"' : '') + '>' + t.n + '. ' + esc(t.title) + '</a>' +
      '<a href="' + t.quiz + '"' + (t.id === cur && kind === 'quiz' ? ' class="cur"' : '') + '>&nbsp;&nbsp;&nbsp;&nbsp;&#8627; Quiz</a>').join('');
    const h = document.createElement('header');
    h.className = 'top';
    h.innerHTML = '<a class="brand" href="index.html">C++ Interview Prep</a><span class="spacer"></span>' +
      '<details class="menu"><summary>Topics &#9662;</summary><div class="panel">' + links + '</div></details>' +
      '<button class="icon-btn" id="theme" type="button" aria-label="Toggle light or dark theme">&#9680;</button><div class="progress"></div>';
    document.body.prepend(h);
    $('#theme').addEventListener('click', () => {
      const root = document.documentElement;
      const dark = root.dataset.theme ? root.dataset.theme === 'dark' : matchMedia('(prefers-color-scheme: dark)').matches;
      root.dataset.theme = dark ? 'light' : 'dark';
      store.set('theme', root.dataset.theme);
    });
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
    const secs = $$('main > section');
    secs.forEach((s, i) => {
      if (!s.id) s.id = 's' + (i + 1);
      if (!s.dataset.title) s.dataset.title = ($('h2', s) || {}).textContent || 'Section ' + (i + 1);
    });
    const done = new Set(store.get('done:' + id, []));
    store.set('total:' + id, secs.length);

    const aside = document.createElement('aside');
    aside.className = 'toc';
    aside.innerHTML = '<button class="toggle" type="button">Contents &#9662;</button><nav class="list"><h4>In this lesson</h4>' +
      secs.map((s) => '<a href="#' + s.id + '" data-id="' + s.id + '"><span class="tick"></span><span>' + esc(s.dataset.title) + '</span></a>').join('') +
      '<div class="count"></div></nav>';
    const layout = document.createElement('div');
    layout.className = 'layout';
    main.parentNode.insertBefore(layout, main);
    layout.append(aside, main);
    $('.toggle', aside).addEventListener('click', () => aside.classList.toggle('open'));

    function paint() {
      secs.forEach((s) => {
        const a = $('a[data-id="' + s.id + '"] .tick', aside);
        if (a) a.textContent = done.has(s.id) ? '✓' : '';
      });
      $('.count', aside).textContent = done.size + ' of ' + secs.length + ' sections understood';
      const bar = $('.top .progress');
      if (bar) bar.style.width = (secs.length ? (done.size / secs.length) * 100 : 0) + '%';
    }

    secs.forEach((s) => {
      const lab = document.createElement('label');
      lab.className = 'done' + (done.has(s.id) ? ' on' : '');
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

    if ('IntersectionObserver' in window) {
      const io = new IntersectionObserver((es) => {
        es.forEach((e) => {
          if (e.isIntersecting) {
            $$('a', aside).forEach((a) => a.classList.toggle('active', a.dataset.id === e.target.id));
          }
        });
      }, { rootMargin: '-80px 0px -65% 0px' });
      secs.forEach((s) => io.observe(s));
    }
  }

  /* ---------------- step-through memory visualiser ---------------- */
  function stepper(sel, cfg) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.className = 'widget stepper';
    const code = clean(cfg.code).split('\n');
    const lines = code.map((l, i) => '<span class="ln" data-l="' + (i + 1) + '"><i>' + (i + 1) + '</i>' + (highlight(l) || ' ') + '</span>').join('');
    root.innerHTML = '<div class="w-head"><span class="tag">Step through</span>' + esc(cfg.title || '') + '</div>' +
      '<div class="st-body"><pre class="st-code">' + lines + '</pre><div class="st-side"><div class="st-mem"></div><div class="st-out"></div></div></div>' +
      '<div class="st-note"></div>' +
      '<div class="w-foot"><button class="btn sm ghost" data-a="back" type="button">&#9664; Back</button>' +
      '<button class="btn sm" data-a="next" type="button">Next &#9654;</button>' +
      '<button class="btn sm ghost" data-a="reset" type="button">Reset</button><span class="info"></span></div>';
    let i = -1;
    const N = cfg.steps.length;
    const GROUPS = [['stack', 'Stack'], ['heap', 'Heap'], ['static', 'Static / global'], ['call', 'Call stack'], ['inst', 'Compiler-generated functions']];

    function render() {
      const s = i >= 0 ? cfg.steps[i] : null;
      const p = i > 0 ? cfg.steps[i - 1] : null;
      const cur = s ? [].concat(s.line) : [];
      $$('.ln', root).forEach((el) => el.classList.toggle('cur', cur.indexOf(+el.dataset.l) >= 0));
      let mem = '';
      if (s && s.mem && s.mem.length) {
        GROUPS.forEach((g) => {
          const es = s.mem.filter((e) => (e.k || 'stack') === g[0]);
          if (!es.length) return;
          mem += '<div class="mem-group"><h5>' + g[1] + '</h5><div class="mem">' + es.map((e) => {
            const before = p && p.mem ? p.mem.find((x) => x.n === e.n) : null;
            const chg = !before || before.v !== e.v || !!before.dead !== !!e.dead;
            return '<div class="cell' + (chg ? ' chg' : '') + (e.dead ? ' dead' : '') + (g[0] === 'heap' ? ' heap' : '') + '">' +
              '<div class="nm">' + esc(e.n) + (e.t ? ' &middot; ' + esc(e.t) : '') + '</div><div class="vl">' + esc(e.v) + '</div>' +
              (e.p ? '<div class="tg">&rarr; ' + esc(e.p) + '</div>' : '') + '</div>';
          }).join('') + '</div></div>';
        });
      }
      $('.st-mem', root).innerHTML = mem || '<div class="mem-group"><h5>Memory</h5><div class="mem"><span class="cell">(nothing yet)</span></div></div>';
      $('.st-out', root).textContent = cfg.steps.slice(0, i + 1).map((x) => x.out || '').join('');
      $('.st-note', root).innerHTML = s ? s.note : (cfg.intro || 'Press <b>Next</b> to run the first line.');
      $('[data-a="back"]', root).disabled = i < 0;
      $('[data-a="next"]', root).disabled = i >= N - 1;
      $('.info', root).textContent = 'Step ' + (i + 1) + ' of ' + N;
    }
    root.addEventListener('click', (e) => {
      const b = e.target.closest('button[data-a]');
      if (!b) return;
      if (b.dataset.a === 'next' && i < N - 1) i++;
      else if (b.dataset.a === 'back' && i >= 0) i--;
      else if (b.dataset.a === 'reset') i = -1;
      render();
    });
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
        '<div class="ts-state">' + vars + muts + '</div><div class="ts-msg' + cls + '">' + esc(msg) + '</div>' + h + '</div>' +
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
    });
    render();
  }

  /* ---------------- quiz runner ---------------- */
  function quiz(sel, cfg) {
    const root = typeof sel === 'string' ? $(sel) : sel;
    root.classList.add('quiz');
    const key = 'quiz:' + cfg.id;
    let order, pos, missed, right;

    const codeHtml = (c) => '<figure class="code"><pre><code>' + highlight(clean(c)) + '</code></pre></figure>';

    function intro() {
      const best = store.get(key, null);
      root.innerHTML = '<div class="result"><p><b>' + cfg.questions.length + ' questions.</b> Pick an answer to see the explanation straight away. ' +
        'Questions and answers are shuffled each time.' + (best ? ' Your best score so far: <b>' + best.best + '%</b>.' : '') + '</p>' +
        '<button class="btn" id="qstart" type="button">Start the quiz</button></div>';
      $('#qstart', root).addEventListener('click', () => begin(cfg.questions));
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
        '<div class="opts">' + opts.map((o, i) => '<button class="opt" type="button" data-i="' + i + '"><span class="k">' + 'ABCDEFG'[i] + '</span><span>' + fmt(o.t) + '</span></button>').join('') + '</div><div class="fb"></div>';
      let locked = false;
      $$('.opt', root).forEach((b) => b.addEventListener('click', () => {
        if (locked) return;
        locked = true;
        const pick = opts[+b.dataset.i];
        $$('.opt', root).forEach((x, i) => { x.disabled = true; if (opts[i].ok) x.classList.add('right'); });
        if (!pick.ok) b.classList.add('wrong');
        if (pick.ok) right++; else missed.push(q);
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
      store.set(key, { best: Math.max(pct, prev ? prev.best : 0), last: pct, total: cfg.questions.length });
      const verdict = pct >= 90 ? 'Excellent. You are interview-ready on this topic.' : pct >= 70 ? 'Solid. Review the explanations below and retry the ones you missed.' :
        pct >= 50 ? 'Getting there. Re-read the lesson sections for the questions you missed.' : 'Go back through the lesson, then try again. This is a normal first score for new material.';
      root.innerHTML = '<div class="result ' + (pct >= 70 ? 'good' : 'bad') + '"><div class="score">' + right + ' / ' + order.length + ' (' + pct + '%)</div><p>' + verdict + '</p></div>' +
        (missed.length ? '<h3>Questions to review</h3>' + missed.map((q) => '<div class="miss"><div class="qq">' + fmt(q.q) + '</div>' + (q.code ? codeHtml(q.code) : '') +
          '<div><b class="ok" style="color:var(--good)">Answer:</b> ' + fmt(q.opts[q.a]) + '</div><div style="color:var(--muted)">' + fmt(q.why) + '</div></div>').join('') : '') +
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
        '<span class="pill">' + (total ? done + '/' + total + ' sections' : 'not started') + '</span>' + (q ? '<span class="pill">quiz best ' + q.best + '%</span>' : '') + '</div>' +
        '<div class="bar-track"><span style="width:' + pct + '%"></span></div>' +
        '<div class="row"><a class="btn sm" href="' + t.file + '">Lesson</a><a class="btn sm ghost" href="' + t.quiz + '">Quiz</a></div></div>';
    }).join('');
    const rb = $('#reset-progress');
    if (rb) {
      rb.addEventListener('click', () => {
        if (!confirm('Clear all lesson progress and quiz scores stored in this browser?')) return;
        try { Object.keys(localStorage).filter((k) => k.indexOf('cpptrain:') === 0 && k !== 'cpptrain:theme').forEach((k) => localStorage.removeItem(k)); } catch (e) { /* ignore */ }
        home();
      });
    }
  }

  /* ---------------- boot ---------------- */
  function boot() {
    const kind = document.body.dataset.kind || 'lesson';
    renderCodeBlocks();
    buildHeader(kind);
    const main = $('main');
    if (kind === 'lesson' && main) { buildLesson(main); buildPager(main, 'lesson'); }
    else if (kind === 'quiz' && main) { main.classList.add('solo'); buildPager(main, 'quiz'); }
    else if (kind === 'home') { if (main) main.classList.add('solo'); home(); }
  }

  window.CT = { TOPICS, stepper, threadsim, quiz, highlight, fmt, esc };
  boot();
})();
