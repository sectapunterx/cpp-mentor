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
  theory* in every ticket intro and the domain half of the audit, so name it
  explicitly.

## 2. Conventions

Read them from the repo when present (`.clang-format`, `.clang-tidy`, `README` /
`CONTRIBUTING`, license, `CMakeLists.txt`, existing headers); otherwise propose
the house defaults from `SKILL.md` and confirm.

Settle and record: **C++ standard**, **style**, **error policy**, **layout**,
**license + author**, **build system**, **test framework**.

**The error policy is a real question, not a default.** Projects differ, and this
skill imposes nothing. Read it from the code if the code already says (does
anything `throw`? do functions return status codes, `std::optional`, a result
type?), and otherwise ask which of these the project uses for a *recoverable*
failure:

- exceptions (mainstream C++, and what most third-party libraries assume);
- error codes / `std::error_code` / an enum return;
- `std::optional` where "absent" is the whole story;
- `std::expected` (C++23) or the project's own result type;
- a mix, split by layer — hot paths one way, the outer API another.

Whatever comes back goes in the profile and wins from then on, in both modes.
Separately, note that `assert` covers *invariants* — programmer bugs, not runtime
failures — under every one of those policies. Don't argue for a scheme the
project doesn't use.

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

## 4. Audit the developer — two short checks

Calibrate how much theory and scaffolding to give: one check on **C++**, one on
the **project's domain**, scored separately (someone can be strong in C++ and new
to the domain, or the reverse).

**The questions are generated fresh for this project — follow
`references/skill-audit.md`.** It carries the bank of areas and angles, the
selection rule that makes each project's audit different, the format catalogue,
the domain recipe, and the rounds-and-adapt loop. Do not invent your own fixed
list and do not reuse an audit you've given before: a memorised answer tells you
nothing about this developer.

In short: roll the selection, land on 5-7 C++ areas and 4-6 domain questions, ask
in rounds of three, adapt to what comes back, and write nothing to the profile
until both checks are done. Then report plainly — solid on, shaky on, hasn't met
— and record the **specific gaps and misconceptions**, which matter far more than
any level label, because they're what ticket theory will target.

## 5. Vim (Zed) practice — ask (default OFF)

Ask once, plainly: *"Want Vim (Zed) shortcuts included with each ticket, so you
learn Vim as you go?"* Default is **off**. If yes, each LEAD card ends with a
comprehensive per-ticket keyboard walkthrough (`references/vim-zed.md`, which is
also a full standalone Vim guide). Record `Vim (Zed) practice: on` or `off` in the
profile; the developer can toggle it anytime ("turn vim on/off"). The guide
targets **Zed's** vim mode — for a different editor, the pure-Vim motions still
apply but panel/file keys differ; note the editor in the profile.

## 6. Write the profile

Fill `templates/project-profile.md` and save it: goal, domain, root namespace,
conventions (including the settled error policy), C++ level + gaps, domain level
+ gaps, Vim preference, and the **audit log entry** — date, which areas and
angles you used, which formats — so the next audit can avoid them.

In Claude Code, write the file into the repo (and it will be read next session);
in the chat app, show the filled profile for the developer to save, and store the
level calibration in memory if available.

## 7. Then work to the profile

From here, every ticket's theory depth, task difficulty, hints, and reviews are
calibrated to *this* profile: weaker C++ area → more C++ theory and smaller
slices; weaker domain → more domain theory; strong in both → push harder. The
picture isn't frozen — LEAD mode re-checks it with fresh probes every few tickets
(`skill-audit.md`), and the profile gets updated when it moves.
