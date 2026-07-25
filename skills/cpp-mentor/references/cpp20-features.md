# C++20 features to reach for

Prefer these over pre-C++20 equivalents. The goal is expressive, safe, modern
code — not novelty for its own sake. Reach for a feature when it makes intent
clearer or removes a class of bug, not just because it exists.

## Everyday

- **`std::format` / `std::format_to`** — replace `sprintf`, stringstreams, and
  manual concatenation. Type-safe, fast, locale-independent by default.
- **Ranges (`<ranges>`, `<algorithm>` range overloads)** — `std::ranges::sort`,
  views (`filter`, `transform`, `take`, `drop`). Compose pipelines instead of
  hand-rolled loops. Note: some range adaptors are lazy — materialize with a
  loop or a helper (see `references/wrappers.md`, `ranges::to` is C++23).
- **Concepts (`<concepts>`, `requires`)** — constrain templates. Turns cryptic
  template errors into readable diagnostics and documents intent at the API.
- **`std::span`** — non-owning view over contiguous memory. Use for parameters
  instead of `(ptr, len)` pairs or forcing a container type.
- **Designated initializers** — `Config{.retries = 3, .timeout = 5}` for clear
  aggregate construction.
- **`<=>` (three-way comparison)** — default it (`auto operator<=>(...) const =
  default;`) to synthesize all six relational operators.
- **`[[nodiscard]]`, `[[likely]]`/`[[unlikely]]`** — express intent the
  compiler and reader can both use. Mark factory and error-returning functions
  `[[nodiscard]]`.

## Compile-time

- **`consteval`** — force compile-time evaluation (immediate functions).
- **`constinit`** — guarantee constant initialization, avoid the static init
  order fiasco.
- **Expanded `constexpr`** — `constexpr` now covers much of `<algorithm>`,
  `std::vector`, `std::string`, virtual calls, try/catch (no throw). Push work
  to compile time where it pays off.
- **`<bit>`** — `std::countl_zero`, `std::popcount`, `std::bit_width`,
  `std::bit_cast`. Portable, branch-free bit manipulation; prefer over
  intrinsics and UB-laden type punning.

## Concurrency

- **`std::jthread`** — auto-joining thread with cooperative `std::stop_token`.
  Prefer over `std::thread` (no manual join, no terminate-on-destroy).
- **`std::latch`, `std::barrier`, `std::counting_semaphore`** — structured
  synchronization primitives; clearer than condition-variable hand-rolling.
- **`std::atomic_ref`**, atomic `wait`/`notify` — fine-grained low-latency sync.

## Diagnostics

- **`std::source_location`** — capture file/line/function without macros. Ideal
  for custom assert/log wrappers (this one *is* C++20, no shim needed).

## Coroutines

- **`co_await` / `co_yield` / `co_return`** — the language machinery is C++20,
  but the standard library ships no ready-made types (generators, tasks).
  Either write the promise types yourself or wrap them under `{{NS}}::` — see
  `references/wrappers.md`.

## The C++20 / C++23 boundary (do NOT assume these exist)

The project targets **strict C++20**. These are C++23 — provide a `{{NS}}::`
wrapper instead of using them directly (see `references/wrappers.md`):

- `std::expected` → use `{{NS}}::expected` (bundled component).
- `std::print` / `std::println` → wrap `std::format` + stream/`fputs`.
- `std::ranges::to` → small `{{NS}}::to_vector` / `{{NS}}::ranges_to` helper.
- `std::flat_map` / `std::flat_set`, `std::mdspan`, `std::generator`,
  `std::byteswap`, `std::stacktrace` → wrap only if actually needed.

Rule of thumb: if a handy standard name turns out to be C++23+, do not silently
drop the feature or downgrade the code — write a minimal `{{NS}}::` shim with the
same interface so migration later is mechanical.
