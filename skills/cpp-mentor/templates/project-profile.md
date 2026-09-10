# Project profile — cpp-mentor

Written once during onboarding, read at the start of every session so the skill
stays individual to this project and this developer. Keep it in the repo root or
`.claude/`. Update it when the project pivots, when the developer levels up, and
after every re-check.

## Project

- **Goal:** <one line — what this project is for, what v1 does>
- **Domain / topic:** <the subject area: networking, parsing, graphics, ...>
- **Root namespace:** <chosen from the goal, fills `{{NS}}` in templates>
- **Module sub-namespaces:** <filled in as modules are added, e.g. ns::io, ns::math>

## Conventions

- **C++ standard:** <e.g. C++20 — what the build actually sets>
- **Style:** <e.g. Google C++ Style, per .clang-format>
- **Error policy:** <the one scheme this project uses for recoverable failures:
  exceptions / error codes / std::optional / std::expected / own result type.
  Fills `{{ERROR_POLICY}}` in prose and `{{RESULT_TYPE}}` in code. `assert`
  covers invariants under any of them. Never introduce a second scheme.>
- **Layout / build / tests:** <e.g. include/<ns>/…, CMake+FetchContent, GoogleTest>
- **License + author:** <e.g. MIT, Name (handle)>

## Developer level (calibration, not a grade)

- **C++ level:** <e.g. junior / mid / strong>
  - Solid on: <…>
  - Gaps / watch: <specific misconceptions to target in ticket theory>
- **Domain level:** <separate from C++: new / some / strong in this topic>
  - Solid on: <…>
  - Gaps / watch: <…>

## Audit log

What has already been asked, so the next audit and the next review ask something
else (see `references/skill-audit.md`). Append, never overwrite.

- <date> — onboarding audit — C++ areas: <numbers/names> — formats: <…> —
  domain axes: <…> — outcome: <one line>
- <date> — re-check after <n> tickets — areas: <…> — outcome: <what moved>

## How to work here

- Theory depth: more where the level is weaker (C++ or domain), lighter where
  strong.
- **Vim (Zed) practice:** <on / off — default off; if on, each ticket ends with a
  keyboard walkthrough>
- **Editor:** <e.g. Zed (vim mode) — the Vim guide targets Zed; note if different>
- <any project-specific rules: "always do X", files not to touch, etc.>

## Log

- <date> — <milestone reached / concept locked in / level change>
