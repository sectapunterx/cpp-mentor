# Vim — full guide & shortcut reference

**Opt-in.** This is off by default. The profile records a Vim preference
(`Vim practice: on/off`; older profiles may still say `Vim (Zed) practice`, which
is the same toggle). Only when it's `on` does each LEAD task card end with a
**"Vim practice"** block. When unset, ask once (see onboarding), store the
answer, and let the developer toggle it anytime ("turn vim on/off").

This file is both the source for those per-ticket blocks and a standalone guide
the developer can read start to finish.

**Editor-agnostic.** The Vim language — modes, motions, operators, text objects,
search, marks — is the same in Vim, Neovim, and every serious Vim emulation:
Zed's vim mode, VS Code with the Vim extension, JetBrains IDEs with IdeaVim,
and others. That core is everything from "Modes" to "Jumps & marks" below. What
differs between editors is the layer *around* the text: the file tree, the file
finder, project search, the terminal, build and test commands. Those keys come
from the profile's **Editor** line, never from guesswork.

## How the per-ticket block works (when enabled)

Walk the **whole keyboard workflow the ticket needs**, in order — open or create
the files, navigate to the folder, edit, save, build, run the tests — listing
every shortcut used, marking the **new** ones (`<- new`) against what they know.
Group by phase; one line each.

- **Core Vim keys** come from the guide below and work in any editor.
- **Editor keys** (file tree, finder, terminal, build, tests) come from the
  profile. If the profile records the developer's own bindings, use those —
  they beat any default. If it names only the editor, use that editor's defaults
  from "Editor layer" below, and mark each one as editor-specific (e.g.
  "(VS Code)") so the developer knows it won't carry over to another editor.
  If the editor isn't recorded, ask once and store it.
- Chords use **Ctrl** (Windows/Linux); on macOS substitute **Cmd** where the
  editor does. Take the platform from the profile if it records one.

---

# The guide

## Modes (the core idea)

Vim is modal — the same keys do different things per mode.

- **Normal** — the home base: keys are commands/motions (not typed text). Press
  `Esc` to get here from anywhere.
- **Insert** — you type text. Enter with `i a o` (and friends below); leave with
  `Esc`.
- **Visual** — select text, then act on it. `v` (character), `V` (line),
  `Ctrl-v` (block).
- **Command** — `:` opens the command line; e.g. `:w` saves. In some emulations
  `:` opens a reduced command line or the editor's command palette that accepts
  the common commands (`:w`, `:q`, `:s`), not the full Vim set.

## Move within a file

- `w` / `b` / `e` — next word start / previous word start / end of word
  (`W`/`B`/`E` = same but whitespace-separated "big words").
- `0` / `^` / `$` — start of line / first non-blank / end of line.
- `f{c}` / `F{c}` — jump to next / previous occurrence of char `{c}` on the line;
  `t{c}` / `T{c}` — up to (before) it. `;` / `,` repeat that jump forward/back.
- `{` / `}` — previous / next blank line (by paragraph/block).
- `%` — jump to the matching bracket `()`, `[]`, `{}`.
- `gg` / `G` — top / bottom of file; `:42<enter>` or `42G` — go to line 42.
- `H` / `M` / `L` — top / middle / bottom of the visible screen.
- `Ctrl-d` / `Ctrl-u` — half page down / up; `Ctrl-f` / `Ctrl-b` — full page.
- `/text<enter>` then `n` / `N` — search forward, next / previous match.
  `?text` searches backward. `*` — search the word under the cursor.
- `%` also pairs with editing (see text objects).

## Insert & append

- `i` / `a` — insert before / after the cursor.
- `I` / `A` — insert at first non-blank / at end of line.
- `o` / `O` — open a line below / above and insert.
- `Esc` — back to normal mode.

## Operators (operator + motion = edit)

Combine an operator with any motion or text object above.

- `d` delete · `c` change (delete + insert) · `y` yank (copy).
- Doubled acts on the line: `dd` delete line · `cc` change line · `yy` yank line.
- Examples: `dw` delete to next word · `d$` delete to end of line · `c%` change to
  the matching bracket · `y}` yank to next blank line.
- `x` delete char · `r{c}` replace one char with `{c}` · `R` overwrite mode.
- `p` / `P` — paste after / before. `>>` / `<<` — indent / dedent.
- `u` undo · `Ctrl-r` redo · `.` repeat the last change (very powerful with `ciw`).

## Text objects (act "inside"/"around" something)

Use as the motion for an operator: `{op}i{obj}` (inner) or `{op}a{obj}` (around).

- `iw` / `aw` — inner / a word. `ciw` = change the whole word under the cursor.
- `i(` `i{` `i[` `i<` — inside the matching brackets (`a(` includes them). Great
  for a function's args or an initializer list: `ci{`, `di(`, `yi[`.
- `i"` `i'` `` i` `` — inside quotes/backticks. `ci"` retypes a string literal.
- `ip` / `ap` — inner / a paragraph.

## Visual mode

- `v` char · `V` line · `Ctrl-v` block. Extend the selection with motions.
- Then act: `d` delete · `y` yank · `c` change · `>` / `<` indent · `=` reformat ·
  `u` / `U` lower/upper-case.

## Search & replace

- `:%s/old/new/g` — replace all `old` with `new` in the file (`%` = whole file,
  `g` = every match on each line). Drop `%` to do just the current line. Add `c`
  (`/gc`) to confirm each. The regex dialect differs between Vim and some
  emulations (several use the host editor's regex engine); plain words work
  everywhere.

## Jumps & marks

- `Ctrl-o` / `Ctrl-i` — jump back / forward through your jump history (e.g. after
  a go-to-definition).
- `` m{a} `` set mark `a`; `` `{a} `` jump to it. `` `` `` jumps to the previous spot.

## Windows / splits

Supported by Vim, Neovim and most emulations:

- `Ctrl-w s` / `Ctrl-w v` — split horizontally / vertically.
- `Ctrl-w h/j/k/l` — move focus between splits. `Ctrl-w q` — close the split.

## Code navigation

- `gd` — go to definition of the symbol under the cursor (Neovim with an LSP,
  Zed, VS Code Vim, IdeaVim).
- `]d` / `[d` — next / previous diagnostic: a default in Neovim 0.10+ and Zed;
  other editors bind it differently — take it from the profile.

---

# Editor layer

Everything outside the text itself. **The developer's recorded bindings always
win** — a heavily customised Neovim or a remapped IDE makes every default below
wrong. Use this table only when the profile names the editor and records no
custom keys.

| Task | Vim / Neovim (stock) | Zed | VS Code | JetBrains (CLion) |
| --- | --- | --- | --- | --- |
| Open a file by name | `:e path` | `Ctrl-p` | `Ctrl-p` | `Ctrl-Shift-n` |
| File tree | `:Ex` (netrw) | `Ctrl-Shift-e` | `Ctrl-Shift-e` | `Alt-1` |
| Search the project | `:vimgrep /x/ **/*.h` | `Ctrl-Shift-f` | `Ctrl-Shift-f` | `Ctrl-Shift-f` |
| Command palette | — | `Ctrl-Shift-p` | `Ctrl-Shift-p` | `Ctrl-Shift-a` |
| Terminal | `:terminal` | `` Ctrl-` `` | `` Ctrl-` `` | `Alt-F12` |
| Save | `:w` | `:w` / `Ctrl-s` | `:w` / `Ctrl-s` | `:w` / `Ctrl-s` |

**Creating a new file** works everywhere through the command line or the
terminal: `:e include/app/net/framer.h` opens the new buffer and `:w` creates it
(in stock Vim the directory must already exist; create it with
`mkdir -p include/app/net` from the terminal first, unless the profile says the
developer's config does that automatically). Editor-native alternatives: the
file tree's "new file" action, or the command palette.

**Build and tests** are the project's commands run from the terminal (e.g.
`cmake --build --preset clang-debug && ctest --preset clang-debug`), unless the
profile records editor bindings for them — then use those.
