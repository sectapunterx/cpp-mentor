# Style & documentation cheatsheet

## Naming (Google C++ Style)

| Entity                     | Convention            | Example                     |
|----------------------------|-----------------------|-----------------------------|
| File names                 | `snake_case.h` / `.cc`| `latency_histogram.h`       |
| Namespaces                 | `snake_case`          | `{{NS}}::latency`              |
| Types (class/struct/enum)  | `PascalCase`          | `LatencyHistogram`, `Mode`  |
| Functions & methods        | `PascalCase`          | `RecordValue()`             |
| Variables (local/param)    | `snake_case`          | `bucket_index`              |
| Private/protected members  | `snake_case_`         | `total_count_`              |
| Public struct data members | `snake_case` (no `_`) | `Options{ int bins; }`      |
| Constants / enumerators    | `kPascalCase`         | `kMaxBuckets`, `kReady`     |
| Macros (avoid; if needed)  | `UPPER_SNAKE`         | `{{NS_UPPER}}_INTERNAL_CHECK`        |
| Template params            | `PascalCase` / `T`    | `class Fn`, `typename T`    |

Header guards: `{{NS_UPPER}}_<PATH>_<FILE>_H_`, e.g. `{{NS_UPPER}}_LATENCY_HISTOGRAM_H_`.
Close namespaces with a comment: `}  // namespace {{NS}}::latency`.

**Deliberate exception:** vocabulary types that shadow a standard type
(`{{NS}}::expected`, `{{NS}}::unexpected`, `{{NS}}::print`) mirror the *standard's*
lowercase, std-style naming so they stay drop-in replaceable. This is the only
place lowercase type/member names are correct. See `references/wrappers.md`.

## Includes

Order (clang-format `IncludeBlocks: Regroup` handles spacing): the paired header
first, then C++ standard headers, then third-party, then project headers. Use
`"<ns>/module/file.h"` (project) and `<vector>` (standard).

## Doxygen

- English, on every public type, method, and file.
- **Two comment forms, and only two:**
  - `/** ... */` block for files, types, functions, methods, and any entity that
    needs more than a trailing phrase. Continuation lines start with ` * `.
  - `///<` trailing, **only on variables** — data members, public struct fields,
    enumerators, constants. It documents the thing on its left.
- Never `///` line comments as a doc block, and never `@` tags — `\` only:
  `\brief`, `\param`, `\return`, `\see`, `\file`, `\note`, `\pre`, `\post`.
- `\brief` is mandatory in every block and is one line. Follow with a blank
  ` *` line, then detail if needed.
- Document ownership, invariants, and error behavior — not the obvious.
- **Verify any external spec/URL before citing it.** Search for the reference,
  confirm it resolves and says what you claim, then link it. A wrong or dead
  spec link is worse than none.

```cpp
/**
 * \brief Records a single latency sample.
 *
 * \param value Sample in the configured unit; must be within the tracked
 *        range or it is rejected.
 * \return true if recorded, false if out of range.
 * \see https://example.org/spec#section (verify before committing)
 */
[[nodiscard]] bool RecordValue(std::int64_t value);
```

Variables take the trailing form — a block comment above a member is noise:

```cpp
 private:
  std::int64_t total_count_{0};  ///< Samples accepted so far.
  std::int64_t rejected_{0};     ///< Samples dropped as out of range.
```

## Testing names (GoogleTest)

- `suite_name` == the class under test, verbatim: `TEST(LatencyHistogram, ...)`.
- `test_name` == `MethodName_StateUnderTest_ExpectedBehavior`:
  `ValueAtPercentile_EmptyHistogram_ReturnsZero`.
- One behavior per test. Arrange–act–assert. No logic in tests beyond the setup
  the case needs.

## Ownership & memory

- Ownership only through `std::unique_ptr` / `std::shared_ptr`; prefer `unique`.
- Non-owning access via references, `std::span`, `std::string_view`, or plain
  observer pointers that are documented as non-owning.
- RAII for every resource. No naked `new`/`delete`. No owning raw pointers.
