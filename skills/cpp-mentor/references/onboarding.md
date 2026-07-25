# Onboarding — first run in a project

Run this the first time the skill is active in a project and there's no profile
yet. Goal: make the skill *individual to this project* — its topic, its
conventions, and this developer's level — and persist that so later sessions
don't re-ask.

## 0. Is there already a profile?

Look for a profile first: a `project-profile.md` (or `.claude/project-profile.md`)
in the repo, relevant notes in `CLAUDE.md`, or calibration in memory. If one
exists, load it and skip onboarding — greet, summarize what you know, and get to
work. Only run the steps below when there's nothing.

Tell the developer what's about to happen ("quick setup so I can pitch this to
your project and level — a few questions") and keep it brisk.

## 1. Project goal & domain

Establish, from the repo (`README`, existing code) or by asking:
- **Goal** — what the project is for; what "v1" does. State it back in one line.
- **Domain / topic** — the subject area the code lives in (networking, parsing,
  graphics, audio, embedded, databases, games, ...). This drives the *domain
  theory* in every ticket intro, so name it explicitly.

## 2. Conventions

Read them from the repo when present (`.clang-format`, `.clang-tidy`, `README` /
`CONTRIBUTING`, license, `CMakeLists.txt`, existing headers); otherwise propose
the house defaults from `SKILL.md` and confirm. Settle: C++ standard, style,
error policy, layout, license + author, build system, test framework.

## 3. Namespace (from the goal)

There is no baked-in namespace. Derive it from the project:
- Propose **2-3 short root-namespace options** drawn from the goal/name (e.g. a
  chat app "Marlin" → `marlin`, `mln`, or `chat`; a ray tracer → `rt`, `ray`,
  `render`). Let the developer pick or supply their own. Keep it short,
  lowercase, collision-unlikely.
- Note that **per-module sub-namespaces** get suggested when each module is
  created (e.g. under root `rt`: `rt::math`, `rt::scene`, `rt::io`) — propose a
  fitting one at that point, don't pre-invent them all now.
- Record the chosen root; it fills the `{{NS}}` token in the templates.

## 4. Audit the developer (two short checks)

Calibrate how much theory and scaffolding to give. Frame it honestly: it's
calibration, not a test with a grade; "don't know / haven't used" is a useful
answer; answer in your own words without looking things up; write nothing to the
profile until both checks are done, then report plainly.

### 4a. C++ skill-check (~6-8 questions, easy → C++20)

Pick a spread so the answers reveal the real level. A reusable set:
1. `unique_ptr` vs `shared_ptr`, and what's wrong with "`shared_ptr` everywhere".
2. What `std::move` actually does; the state of the moved-from object.
3. The bug in a function that returns a `string_view` to a local `std::string`.
4. A class holding a raw resource handle: which special members matter, and what
   breaks if you skip them (Rule of Three/Five, double-free).
5. `const int*` vs `int* const` vs a `const` member function.
6. How to signal a recoverable error, and what the choice depends on.
7. data race vs race condition; which tool detects a data race.
8. One line each (or "not used"): `concepts`, `ranges`, `std::span`, `<=>`.

Calibrate a **C++ level** plus the **specific gaps/misconceptions** to watch (the
gaps matter more than the label — record them so ticket theory targets them).

### 4b. Domain skill-check (~4-6 questions, composed from the goal)

Generate these from the project's domain — they are not fixed. Aim at the
fundamentals the project will lean on. Examples:
- *TCP messenger:* Is TCP message- or stream-oriented? What does "framing" solve?
  Difference between a message and a TCP segment? What is backpressure? What can
  a half-open connection do to a naive read loop?
- *Parser:* tokens vs grammar? What is an AST? recursive-descent vs a parser
  generator — when each?
- *Ray tracer:* what is a ray? ray-sphere intersection at a high level? why is a
  bounding-volume hierarchy worth it?

Calibrate a **domain level** separately from the C++ level (someone can be strong
in C++ and new to the domain, or the reverse).

## 4c. Vim (Zed) practice — ask (default OFF)

Ask once, plainly: *"Want Vim (Zed) shortcuts included with each ticket, so you
learn Vim as you go?"* Default is **off**. If yes, each LEAD card ends with a
comprehensive per-ticket keyboard walkthrough (`references/vim-zed.md`, which is
also a full standalone Vim guide). Record `Vim (Zed) practice: on` or `off` in the
profile; the developer can toggle it anytime ("turn vim on/off"). The guide
targets **Zed's** vim mode — for a different editor, the pure-Vim motions still
apply but panel/file keys differ; note the editor in the profile.

## 5. Write the profile

Fill `templates/project-profile.md` and save it: goal, domain, root namespace,
conventions, C++ level + gaps, domain level + gaps, notes. In Claude Code, write
the file into the repo (and it will be read next session); in the chat app, show
the filled profile for the developer to save, and store the level calibration in
memory if available.

## 6. Then work to the profile

From here, every ticket's theory depth, task difficulty, hints, and reviews are
calibrated to *this* profile: weaker C++ area → more C++ theory and smaller
slices; weaker domain → more domain theory; strong in both → push harder. Revisit
the profile when the developer clearly levels up or the project pivots.
