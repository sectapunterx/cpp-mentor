# cpp-mentor

A general, self-adapting **C++ mentor** for any project. On first run it onboards
— settles the goal and domain, derives a namespace from the goal, agrees
conventions (including the project's own error policy — the skill imposes none),
and audits the developer's level in both C++ and the project's topic — then saves
a per-project profile and calibrates to it.

The audit is **generated, not recited**: the questions are composed for this
project from a bank of areas and angles, in this project's own vocabulary, and a
log in the profile keeps later re-checks and code reviews on fresh ground. Run
the skill on four projects and you get four different audits — there is nothing
to memorise, which is the point.

Two modes, picked on activation:

- **LEAD** — mentors from a roadmap: opens each ticket with domain + C++ theory,
  assigns one scoped task with acceptance criteria and a Vim (Zed) walkthrough,
  reviews without writing the code, and gives hints only when asked.
- **WRITE** — writes the code directly in the project's style.

Modern C++20, Google style, Doxygen, GoogleTest, CMake/FetchContent, MIT by
default. Nothing is hardcoded to one project — the namespace, the error policy,
the conventions, and the level all come from the project and its profile.

## Install in Claude Code

```text
/plugin marketplace add https://github.com/sectapunterx/cpp-mentor.git
/plugin install cpp-mentor@cpp-tools
```

The `sectapunterx/cpp-mentor` shorthand also works, but it clones over SSH — use
the HTTPS URL above unless you have an SSH key set up for GitHub.

Or drop the skill straight into a skills directory:

```bash
cp -r skills/cpp-mentor ~/.claude/skills/          # personal (all projects)
# or into <repo>/.claude/skills/ for one project
```

## Install in the Claude app (claude.ai / desktop chat)

Upload the skill zip: Settings -> Capabilities -> Skills -> upload
`cpp-mentor.skill` (a zip of `skills/cpp-mentor/`), then toggle it on. Rebuild it
anytime with `cd skills && zip -r ../cpp-mentor.skill cpp-mentor`.

## License

MIT (c) 2026 Anton (github.com/sectapunterx)
