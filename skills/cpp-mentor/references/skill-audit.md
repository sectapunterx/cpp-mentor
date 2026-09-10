# Skill audit — generating fresh questions every time

The audit calibrates how much theory and scaffolding this developer needs. It is
used in three places: **onboarding** (the first, fullest audit), **LEAD re-checks**
(a couple of fresh probes every few tickets), and **reviews** (the questions you
ask about their code).

## The one rule

**There is no fixed question list, and you never ship the same audit twice.**

Everything below is a bank of *areas and angles* — raw material. You compose the
actual questions on the spot, in this project's own vocabulary, from a selection
that differs by project and by date. A developer who runs this skill on four
projects must meet four different audits; a developer who is re-checked in month
three must meet questions they have not seen. Memorised answers are worthless to
both of you — the point is to find out what they actually know.

Concretely, every question you ask must satisfy all four:

1. **Composed, not copied.** The angles below are one-line seeds. Never paste one
   as the question. Write the question yourself, freshly worded.
2. **Anchored in this project.** Use the project's own types, files, domain nouns
   and scenarios wherever the angle allows — "your `Session` object", "the frame
   buffer you'll be filling", not "a class holding a resource".
3. **Not previously asked.** Check the profile's audit log and skip areas and
   angles already used, until the bank is exhausted; then reuse an area but with a
   different angle *and* a different format.
4. **Answerable in a sentence or two.** If it needs a paragraph, it's a lecture in
   disguise. Split it or drop it.

## Framing it to the developer

Say plainly what this is before the first question: calibration, not a graded
test; there is no pass mark; **"don't know" / "haven't used that" is a genuinely
useful answer** and costs them nothing; answer in their own words without looking
things up; and nothing goes into the profile until the whole thing is done, at
which point you report the picture plainly. Keep it brisk and conversational — a
senior chatting over coffee, not an interviewer with a clipboard.

## The engine — composing one audit

### Step 1. Roll the selection

You need a starting point that genuinely differs between projects and over time.
Compute it, don't "pick":

```
seed  = (day of the month) + (number of letters in the project's root namespace)
start = (seed mod 15) + 1            -> an area number in 1..15
```

Then take six areas by counting on from `start` with these steps: `+0, +4, +7,
+9, +11, +13`, wrapping past 15 back to 1 (so 14 + 4 = 3). The six are always
distinct. Worked example: namespace `rt` on the 9th → seed 11, start 12, so
areas **12, 1, 4, 6, 8, 10**. The same project on the 20th starts at area 8 and
lands on a different six; a different project on the same day lands elsewhere
again.

### Step 2. Adjust the selection for the project

- **Drop what the project can't reach** and roll the next area along: no threads
  anywhere in sight → concurrency is a weak probe; a header-only single-target
  build → the build/linking area yields little.
- **Force in what it leans on hardest.** A project that lives on buffers pulls in
  *Lifetimes*; one with a plugin interface pulls in *Polymorphism*; anything
  parsing bytes pulls in *UB & tooling*.
- **Skip areas in the profile's audit log** (a re-check must be new ground).
- Land on **5-7 areas**. Fewer than five and you're guessing; more than eight and
  it stops feeling like a conversation.

### Step 3. Pick an angle and a format per area

Within each chosen area, pick the angle at index `seed mod (number of angles)`,
then step forward for each subsequent area so you don't sit on the same index.
Give each area a different **format** from the catalogue below.

Constraints for one audit:
- **At most two questions in the same format.**
- **At least one snippet** question (reading code reveals more than describing it).
- **At least one project-anchored** question phrased in the project's own domain.
- Mix the tiers: open around tier 2, and let step 5 move you.

### Step 4. Ask in rounds, not as a wall of text

Three questions, wait, then adapt. A batch of eight lands like an exam and
invites looking things up; three at a time keeps it a conversation and lets you
steer. Second round of three, then at most two more if the picture is still
unclear. Do not number them like an exam paper — ask them like questions.

### Step 5. Adapt as you go

- Fluent, precise answers with the *why* → step the tier up, and switch the next
  area to something the project will genuinely stress.
- Right answer, shaky reasoning → stay at the tier and probe the same idea from
  the neighbouring angle. This is the most informative move you have.
- "Haven't used it" → accept it, log it as a gap, don't drill. Move to an area
  that will yield signal.
- A **misconception** (confidently wrong) is the single most valuable find. Note
  the exact shape of it, and don't correct it on the spot — record it and target
  it in the first tickets that touch it.

### Step 6. Report and record

Report plainly: what they're solid on, what's shaky, what they haven't met. No
grade theatre, no flattery. Then write to the profile: C++ level, domain level,
the specific gaps and misconceptions (these matter far more than the label), and
the **audit log entry** — date, the areas and angles used, the formats used — so
the next audit can avoid them.

## Format catalogue

Rotate these. The format changes what a question reveals, so varying it matters
as much as varying the topic.

| Format | Shape | Reveals |
|---|---|---|
| **Snippet** | 3-8 lines of code: "what does this do / what's wrong / what does it print?" | Real reading ability, not recited definitions |
| **Consequence** | "If you do X, what happens — at compile time, at run time, a year later?" | Whether the model in their head predicts behaviour |
| **Trade-off** | "A or B here — what makes you pick?" | Judgement; that they know both, and the cost of each |
| **Diagnose** | A symptom: "it crashes only in release / only under load". First three hypotheses, and the tool? | Debugging method, tool awareness |
| **Design** | "Sketch the signature. Defend one choice." | API sense, what they consider the caller's problem |
| **Vocabulary** | "One line each, or say you haven't used it." | Breadth, cheaply — good for closing a round |
| **Project-anchored** | The same idea in the project's own nouns and scenario | Transfer — the thing that predicts how they'll actually do |
| **Recall-and-apply** | "You said X earlier; here's a case where X doesn't hold. Now what?" | Depth vs. memorised rule; use in round two |

## The C++ bank

Fifteen areas. Each angle is a **seed**, not a question — one angle can become a
snippet, a trade-off or a diagnosis depending on the format you pair it with.
Tiers: **1** foundations, **2** working knowledge, **3** senior judgement.

**1. Lifetimes & dangling**
- a `string_view` or `span` returned into a local or a temporary (1)
- a reference or pointer into a `vector` after it grows (2)
- lifetime extension by a `const&` — and the cases where it doesn't apply (3)
- a lambda capturing by reference that outlives the frame it captured (2)
- iterator invalidation for the container this project actually uses (2)
- `c_str()` on a temporary handed to a C API (2)
- a reference or `string_view` stored as a data member — what the class now owes (3)

**2. Ownership & RAII**
- `unique_ptr` vs `shared_ptr`, and what's wrong with "`shared_ptr` everywhere" (1)
- given a snippet: who frees this, and exactly when? (1)
- reference cycles between `shared_ptr`s; what `weak_ptr` is for (3)
- a class holding a raw handle (`FILE*`, fd, socket): which special members matter, what breaks if you skip them (2)
- a resource that isn't memory — custom deleter, or a small RAII type? (2)
- passing a `unique_ptr` by value vs by reference vs passing the raw pointer — what each *says* to the caller (3)
- an observer (non-owning) pointer as a member — how does the reader know it's non-owning? (2)

**3. Move semantics**
- what `std::move` actually does (and doesn't) (1)
- the state of a moved-from `string` / `vector` / `unique_ptr` — what's legal to do with it (2)
- `return std::move(local)` — why it can be *worse* than `return local` (3)
- what happens when you "move" out of a `const` object (2)
- a case where no move happens at all because the copy was elided (3)
- `noexcept` on the move constructor, and why `vector` growth cares (3)
- `T&&` in a template vs `T&&` on a concrete type (3)

**4. const, constexpr and friends**
- `const int*` vs `int* const` vs a `const` member function (1)
- `mutable`, and logical vs bitwise constness (3)
- a `const` member function handing out a non-const pointer to internals (2)
- `const` vs `constexpr` vs `constinit` vs `consteval` — one line each (2)
- when a `constexpr` function runs at run time after all (2)

**5. Error handling & contracts**
- how *this* project signals a recoverable failure, and what that choice costs (1)
- a programmer bug vs a runtime failure — different mechanisms, why (2)
- what `noexcept` promises, and what happens if the promise is broken (3)
- throwing from a destructor (3)
- a caller ignoring the returned error — what in the API stops them (2)
- reporting an error across a callback, thread or ABI boundary (3)
- validating an input vs asserting a precondition — which is which here (2)

**6. Templates & generics**
- why a template definition usually has to live in the header (1)
- `enable_if`/SFINAE vs a concept — what changes at the call site and in the error (2)
- an overload resolution surprise: an implicit conversion picking the wrong one (3)
- ADL: why `using std::swap;` then unqualified `swap(a, b)` (3)
- `auto` dropping `const`/reference; when you need `decltype(auto)` (2)
- class template argument deduction, and when a deduction guide is needed (3)
- given a wall of template error output — what do you read first? (2)

**7. Containers & algorithms**
- pick the container for a stated access pattern, and say what you gave up (1)
- the accidental O(n²): a linear operation inside a loop (2)
- `reserve`, growth, and why the pointers you saved died (2)
- `map::operator[]` inserting when you only meant to look (2)
- an `<algorithm>` call vs the hand-written loop — and when the loop is clearer (2)
- what a comparator must guarantee; what a hash and `==` must agree on (3)
- `const std::string&` vs `std::string_view` vs `std::string` as a parameter (2)

**8. Concurrency**
- data race vs race condition; which tool finds which (2)
- what a mutex actually protects (and the common wrong answer) (2)
- an atomic counter vs a mutex; where atomics stop being enough (3)
- how two locks become a deadlock, and how ordering fixes it (2)
- `jthread` + `stop_token` vs `thread` + a `bool` flag (2)
- what "this class is thread-safe" would mean for their API (3)
- handing data between threads: shared state, a queue, or an ownership handoff (3)

**9. Undefined behaviour & tooling**
- three things that are UB, and what the compiler is then allowed to do (2)
- signed overflow / out-of-range index / reading uninitialised memory / type punning (2)
- "works in debug, breaks in release" — first hypothesis, and why (3)
- which sanitiser for which class of bug, and why not all at once (2)
- what `-Wall -Wextra` catches, and a bug class it never will (2)
- a failure that reproduces one run in twenty — how do you corner it (3)

**10. Build, linking & the ODR**
- declaration vs definition; what a linker error is actually telling them (1)
- a function defined in a header — why `inline` (or a class) is needed (2)
- what an include guard prevents, and what it does not (1)
- self-contained headers; forward declaration vs `#include` (2)
- why touching one header rebuilds half the project (2)
- static vs shared library; what the ODR forbids across translation units (3)
- what `-O2` is allowed to reorder, and how that shows up in a debugger (3)

**11. Performance & the machine**
- what would you measure first, with what tool — before changing anything (1)
- cache locality: array-of-structs vs struct-of-arrays for a stated access (3)
- find the allocations in this snippet; remove one (2)
- `for (auto x : v)` where the copy is not free (1)
- when a linked list loses to a vector despite the complexity table (3)
- move vs copy cost for a small string; what the optimisation is (2)
- "this is faster" with no benchmark — what would you ask for (2)

**12. Polymorphism & design**
- where virtual dispatch actually costs, and where it doesn't (2)
- a missing virtual destructor: what breaks, and exactly when (2)
- object slicing on a copy into a base (2)
- inheritance vs composition for a stated relationship (2)
- `std::function` vs a template callable vs a function pointer (3)
- an interface with twelve methods — what's the smell, what's the fix (3)
- type erasure or CRTP: what problem is each solving (3)

**13. C++20 specifically**
- an `enable_if` rewritten as a concept — what improves (2)
- ranges and views: what is lazy, and the dangling-view trap (3)
- `std::span` — what it replaces, and what it emphatically does not own (2)
- `<=>` defaulted: what six operators appear; when you can't default it (2)
- designated initialisers and what makes a type an aggregate (2)
- `std::format` vs stringstream vs `printf` (1)
- `jthread`, `latch`, `barrier`, `counting_semaphore` — one line each (2)
- `std::source_location` vs `__FILE__`/`__LINE__` macros (2)
- `consteval` / `constinit`, and the static initialisation order fiasco (3)
- `<bit>`: `popcount`, `bit_width`, `bit_cast` vs a `reinterpret_cast` pun (2)
- coroutines at the "what problem do they solve" level (3)

**14. API & interface design**
- for this signature: by value, by `const&`, by `span`, or a sink argument? (2)
- `[[nodiscard]]`, `explicit`, `noexcept` on a given API — which, and why (2)
- name this function so a caller can't misuse it (2)
- what goes in the header vs the `.cc`; what the header is promising (1)
- how does a caller learn the preconditions without reading the body (3)
- change this signature — who breaks, and how would they find out (3)

**15. Testing**
- one input that would break the code they just wrote (1)
- the boundary cases for a stated function: empty, one, max, negative, duplicate (1)
- what a happy-path-only test actually proves (2)
- mock vs fake vs the real thing (2)
- a test that fails one run in ten — what causes that, what do you do (3)
- testing code that touches the clock, the filesystem or the network (3)
- what makes a test name useful when it's the only thing in the failure output (2)

## The domain audit

Composed from *this* project's topic, never from a list. Four to six questions,
same rounds, same adaptation. Aim at the fundamentals the project will actually
lean on — not trivia, not history.

### The recipe (works for any domain)

Derive one question from each axis, keep the four or five that fit this project:

1. **The core abstraction.** What is the central thing this domain manipulates,
   in their words? (a stream, a token, a ray, a sample, a page, a frame)
2. **The boundary.** How does data enter and leave — the wire, the file format,
   the device, the buffer — and what is guaranteed at that boundary?
3. **The classic gotcha.** The mistake everyone makes first in this domain. Ask
   for the consequence, not the name.
4. **Scale and cost.** What gets expensive here, and at what size? What is the
   budget (bytes, milliseconds, a frame, a packet)?
5. **A live trade-off.** The argument practitioners actually have — approach A vs
   approach B, and when each wins.
6. **Vocabulary.** Three to five terms from the domain: one line each, or "not
   used".

### Family angles

Seeds for common domains. Same rule as the C++ bank: compose, don't copy — and
if the project's domain isn't here, the recipe above covers it.

- **Networking / protocols** — stream vs message; framing; partial reads and
  short writes; backpressure; timeouts and half-open connections; ordering and
  retransmission; blocking vs non-blocking vs async; byte order on the wire.
- **Parsers / compilers / interpreters** — lexing vs parsing; grammar and
  ambiguity; parse tree vs AST; recursive descent vs a generator; precedence;
  error recovery and what makes a diagnostic good; symbol tables and scope.
- **Graphics / rendering** — coordinate spaces and transforms; the camera model;
  rasterisation vs ray tracing; colour and gamma; the depth buffer; acceleration
  structures; where float precision bites.
- **Audio / DSP** — sample rate and quantisation; buffer size vs latency; the
  real-time thread rule (no allocation, no locks, no blocking); aliasing; time
  vs frequency domain; clipping and headroom.
- **Embedded / firmware** — life without a heap; what an ISR may not do;
  `volatile` and memory-mapped registers; the timing budget; watchdogs; flash vs
  RAM; debouncing; power states.
- **Storage / databases** — pages and blocks; indexes and the B-tree; durability
  and `fsync`; write-ahead logging; transactions and isolation; sequential vs
  random I/O; the buffer pool.
- **Games** — the frame budget and a fixed timestep; entity organisation and data
  locality; determinism; input latency; broad phase vs narrow phase collision.
- **Systems / OS tooling** — processes vs threads; what a syscall costs; virtual
  memory and page faults; file descriptors and their inheritance; signals; exit
  codes, stdout vs stderr.
- **CLI / developer tooling** — argument parsing and UX; exit codes; streaming vs
  buffering output; configuration precedence; reproducible output; what makes a
  tool scriptable.
- **Cryptography / security** — why you don't implement the primitive; keys vs
  nonces vs salts; constant-time comparison; sources of randomness; what a hash
  does and does not give you.
- **Numerics / simulation** — floating-point representation and why `==` is a
  trap; catastrophic cancellation; stability vs accuracy; step size; carrying
  units through the code.
- **ML infrastructure** — tensors and shapes; batching; memory bandwidth as the
  real limit; precision choices; the data pipeline as the actual bottleneck.
- **GUI** — the event loop; the main-thread rule; layout vs paint; retained vs
  immediate mode; where the state lives.
- **Robotics / control** — sensor noise and filtering; loop rate and jitter;
  coordinate frames; actuator limits; end-to-end latency.
- **Services / distributed backends** — queues and backpressure; idempotency;
  timeouts and retries (and retry storms); at-least-once vs at-most-once;
  observability.

## Re-checks in LEAD mode

The onboarding audit is a snapshot, and it goes stale. Every four or five
signed-off tickets — or whenever their work suggests the profile is wrong — slip
**two or three fresh probes** into the conversation. Rules:

- **Woven in, never announced.** They belong in the review or the theory intro
  ("before I hand you the next one — quick one:"), not in a ceremony called
  "re-assessment".
- **From areas the audit log doesn't list.** That's the whole point.
- **One of them targets a logged gap**, to check whether it's closed. If it is,
  say so, update the profile, and raise the difficulty.
- Update the profile when the answer moves the picture — including downwards, if
  something that was marked solid clearly isn't.

## Rotating the review questions

Reviews suffer the same staleness: a fixed checklist becomes noise by the fifth
ticket, and they start pre-writing the answers. So per review:

- Pick **two to four categories** the diff actually exercises — correctness,
  ownership, errors, idiom fit, tests, style/docs — not all six every time.
- Phrase each from a **bank angle you haven't used on them recently**, in the
  terms of the code in front of you.
- Always include **one question aimed at a gap in the profile**, and **one that
  makes them defend a decision they made** — vary which decision, not just "why
  did you do it that way?" every time.
- Never paste the same wording twice. If a question would be word-for-word what
  you asked last review, that's the signal to reach for a different angle.
