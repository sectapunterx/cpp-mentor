# Writing `{{NS}}::` wrappers

Strict C++20 means some ergonomic standard names are out of reach (they landed
in C++23+). Rather than downgrade the code, wrap the missing capability under
the `{{NS}}::` namespace with an interface that mirrors the eventual standard type.
Two payoffs: the calling code reads like modern C++, and migrating to the
standard type later is a search-and-replace.

Wrappers are welcome beyond just filling standard-library gaps — a small
`{{NS}}::` helper that removes boilerplate or encodes a project convention (a
scope guard, a strong typedef, a fixed-capacity buffer) is exactly the kind of
reusable utility this ecosystem is for. Keep each one small, documented, and
tested.

## Rules

1. **Namespace.** Everything goes in `{{NS}}::` (or a sub-namespace like
   `{{NS}}::meta`), never the global namespace.
2. **Mirror the standard interface for vocabulary types.** For types that shadow
   a standard one (`expected`, `print`, `generator`), match the standard's
   member names and semantics exactly — even where that means lowercase,
   std-style naming instead of Google style. The point is drop-in
   replaceability. Document the deviation in the header.
3. **Google style for everything else.** A `{{NS}}::` helper that has no standard
   counterpart follows the normal Google conventions (PascalCase types/methods).
4. **Document the migration path.** In the Doxygen block, name the standard type
   it stands in for and link cppreference (verify the link resolves first).
5. **Test it.** A shim is still production code. Cover it with GoogleTest.

## Worked example: `{{NS}}::expected` (bundled)

`templates/expected.h` is a ready-made, compile-tested C++20 subset of
`std::expected<T, E>` plus `{{NS}}::unexpected<E>` and an `expected<void, E>`
specialization. It is the backbone of the error policy: recoverable failures
return `{{NS}}::expected`, invariants use `assert`, nothing throws.

```cpp
{{NS}}::expected<Config, std::string> LoadConfig(std::string_view path) {
  if (!Exists(path)) return {{NS}}::unexpected(std::string("not found"));
  return Parse(path);  // implicit success construction
}

if (auto config = LoadConfig("app.toml")) {
  Use(config.value());
} else {
  Log(config.error());
}
```

Copy this component into every project's `include/{{NS}}/` (or vendor it once and
share). When the toolchain and project move to C++23, replace `{{NS}}::expected`
with `std::expected` and `{{NS}}::unexpected` with `std::unexpected` — the call
sites do not change.

## Sketch: `{{NS}}::print`

`std::print` (C++23) is just `std::format` written to a stream. A faithful shim:

```cpp
namespace app {
template <class... Args>
void print(std::format_string<Args...> fmt, Args&&... args) {
  std::fputs(std::format(fmt, std::forward<Args>(args)...).c_str(), stdout);
}
template <class... Args>
void println(std::format_string<Args...> fmt, Args&&... args) {
  print(fmt, std::forward<Args>(args)...);
  std::fputc('\n', stdout);
}
}  // namespace app
```

## Sketch: `{{NS}}::to_vector` (stand-in for `std::ranges::to<std::vector>`)

```cpp
namespace app {
template <std::ranges::input_range R>
auto to_vector(R&& range) {
  using T = std::ranges::range_value_t<R>;
  std::vector<T> out;
  if constexpr (std::ranges::sized_range<R>) out.reserve(std::ranges::size(range));
  for (auto&& element : range) out.push_back(static_cast<T>(element));
  return out;
}
}  // namespace app
```
