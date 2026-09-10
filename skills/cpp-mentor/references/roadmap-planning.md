# Composing a roadmap from the project goal

Use this in LEAD mode when the developer has no roadmap yet. You are doing sprint
planning *with* them, not handing down a spec. Draft, get their approval, save,
then start assigning tasks. Do not begin assigning work off an unapproved
roadmap.

## Steps

1. **Get the goal.** Ask what the project is for and what "version 1" should do,
   or read it from the repo: `README.md`, an existing `main`, open tickets, or
   the code that's already there. State the goal back in one sentence and have
   them confirm it. Don't invent the goal.

2. **Scope an MVP.** Find the smallest thing that delivers the goal end to end.
   Cut anything that isn't needed to prove it works; park it in a "later"
   section rather than the main line. A roadmap should reach something runnable
   fast, then grow.

3. **Decompose into milestones, then tasks.** Break the MVP into 3-6 milestones
   (epics), each a meaningful, demoable step. Under each, list tasks sized to the
   developer's level — one sitting each. Note dependencies so nothing is assigned
   before its prerequisite. As modules fall out of this, **suggest a sub-namespace
   for each** under the project's root namespace (e.g. root `rt` → `rt::math`,
   `rt::scene`, `rt::io`) — propose, don't impose; record chosen ones in the
   profile.

4. **Sequence foundation-first.** Order so early tasks unblock later ones:
   project scaffolding and build first (layout, CMake, one trivial module and a
   test that compiles, whatever the error policy needs in place), then the core
   data types, then
   features, then hardening (edge cases, more tests, docs). The developer should
   always have a green build to build on.

5. **Right-size the difficulty.** Front-load a couple of small, confidence-
   building tasks so they get an early win, then ramp. Flag which tasks
   introduce a *new* modern-C++ concept — those get extra scaffolding when
   assigned.

6. **Present, revise, approve.** Show the draft roadmap as milestones with
   task checklists. Invite edits — they know the project and their own pace.
   Only once they approve, save it to `roadmap-progress.md` (from the template),
   and assign the first task.

## Worked example (a small C++ utility library)

Goal (confirmed with the developer): "A header-only `app::` utility collection with
a first utility that reads latency numbers from stdin and prints percentiles."

> **Milestone 1 — Project skeleton (foundation)**
> - [ ] Repo layout + top-level CMake, `app::<project>` interface lib — builds empty.
> - [ ] A trivial `app::demo` header + passing test, to prove the loop works.
> - [ ] CMakePresets (clang debug+san, gcc CI); `.clang-format` / `.clang-tidy`.
>
> **Milestone 2 — Core type**
> - [ ] `Histogram` header: constructor + `RecordValue`, range-checked. *(new
>   concept: `std::span` params)*
> - [ ] Percentile query. *(new concept: the counts scan)*
> - [ ] Tests: empty, single value, known distribution.
>
> **Milestone 3 — CLI**
> - [ ] `src/` driver: read stdin, feed the histogram.
> - [ ] Render summary + ASCII output.
>
> **Later (parked):** merge across threads, log-scale bins, JSON output.

Save that shape into `roadmap-progress.md`, then assign Milestone 1's first task
as a task card (see `lead-mode.md`).
