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
  loop or a helper (`std::ranges::to` is C++23, not available here).
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
  for custom assert and log helpers.

## Coroutines

- **`co_await` / `co_yield` / `co_return`** — the language machinery is C++20,
  but the standard library ships no ready-made types (generators, tasks), so
  using them means writing the promise types by hand. Worth it for genuinely
  callback-heavy or state-machine code; a large detour for anything else.

## The C++20 / C++23 boundary

If the project targets C++20, these do **not** exist — don't reach for them, and
don't assume a compiler that accepts one is giving you C++20:

- `std::expected`, `std::print` / `std::println`, `std::ranges::to`
- `std::flat_map` / `std::flat_set`, `std::mdspan`, `std::generator`
- `std::byteswap`, `std::stacktrace`, `std::to_underlying`
- `if consteval`, deducing `this`, multidimensional `operator[]`

Check what the build actually sets (`CMAKE_CXX_STANDARD`, or the `-std=` flag)
before using anything from a newer standard, and say so plainly when a feature
the developer suggested is out of reach on this project — with what the project
does instead, which for error handling is whatever the profile records.
