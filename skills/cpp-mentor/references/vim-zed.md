# Vim (Zed) — full guide & shortcut reference

**Opt-in.** This is off by default. The profile records a Vim preference
(`Vim (Zed) practice: on/off`); only when it's `on` does each LEAD task card end
with a **"Vim (Zed) practice"** block. When unset, ask once (see onboarding),
store the answer, and let the developer toggle it anytime ("turn vim on/off").

This file is both the source for those per-ticket blocks and a standalone guide
the developer can read start to finish.

## How the per-ticket block works (when enabled)

Walk the **whole keyboard workflow the ticket needs**, in order — focus the
panel, create/open files, navigate to the folder, edit, save, run — listing every
shortcut used, marking the **new** ones (`<- new`) against what they know. Group
by phase; one line each; mark Zed keys (not pure Vim). Chords below use **Ctrl**
(Windows/Linux); on macOS substitute **Cmd**. Take the platform from the profile
if it records one.

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
- **Command** — `:` opens it (in Zed, the command palette); e.g. `:w` saves.

## Their custom keys (already in their keymap)

- `Ctrl-e` — focus the **project panel** (file tree).
- `Ctrl-j` — focus the **terminal**.
- `Escape` — return focus to the **code/editor**.

Pane flow: `Ctrl-e` to the tree -> file ops -> `Escape`/`Enter` back to code ->
`Ctrl-j` to the terminal to run -> `Escape` back.

## Already known (their base)

`h j k l` and line motions · `Ctrl-d` / `Ctrl-u` half-page down/up · `i` insert ·
`o` open line below · `v` visual (char) · `V` visual (line) · `gg` top of file ·
`g` (motion prefix).

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
  (`/g c`) to confirm each. (Zed uses a slightly different regex syntax — see its
  docs.)

## Jumps & marks

- `Ctrl-o` / `Ctrl-i` — jump back / forward through your jump history (e.g. after
  a go-to-definition).
- `` m{a} `` set mark `a`; `` `{a} `` jump to it. `` `` `` jumps to the previous spot.

## Windows / splits (Zed vim)

- `Ctrl-w s` / `Ctrl-w v` — split horizontally / vertically.
- `Ctrl-w h/j/k/l` — move focus between splits. `Ctrl-w q` — close the split.

## Code navigation (Zed vim defaults)

- `g d` — go to definition of the symbol under the cursor.
- `] d` / `[ d` — next / previous diagnostic (error or warning).

## Project panel — create files & navigate folders (Zed)

Focus with `Ctrl-e`; in vim mode the tree takes vim-style motions.

- `j` / `k` (or arrows) — move down / up the tree.
- `Enter` or `o` — open a file, or expand/collapse the folder under the cursor.
- `Ctrl-n` — **new file** in the selected directory (type the name, `Enter`).
- `Alt-Ctrl-n` — **new directory** in the selected directory.
- `Escape` — back to the editor.

Example — create `include/app/net/framer.h`: `Ctrl-e` -> `j`/`k` to
`include/app/net` (`Enter` to expand folders) -> `Ctrl-n` -> type `framer.h` ->
`Enter`.

## Files, search, run (Zed — not pure Vim)

- `Ctrl-p` — file finder: fuzzy-open any file by path.
- `Ctrl-shift-p` — command palette: run any Zed action by name.
- `Ctrl-shift-f` — search across the whole project.
- `Ctrl-n` — new buffer (name it by saving).
- `:w<enter>` / `Ctrl-s` — save.
- Run build/tests: `Ctrl-j` to the terminal and run `cmake ... && ctest ...`, or
  `Ctrl-shift-p` -> `task: spawn`.

Note: `:` in Zed's vim mode opens the command palette and accepts common vim
aliases (`:w`, `:q`, ...); it is not the full vim command line.
