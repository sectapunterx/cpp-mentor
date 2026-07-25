#ifndef {{NS_UPPER}}_EXPECTED_H_
#define {{NS_UPPER}}_EXPECTED_H_

#include <cassert>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <variant>

namespace {{NS}} {

/**
 * \brief Wrapper that tags a value as an error, mirroring std::unexpected.
 *
 * Constructing a \ref {{NS}}::expected from an \ref unexpected places the object
 * into the error state. This mirrors the C++23 std::unexpected interface so a
 * later migration to the standard type is mechanical.
 *
 * \see https://en.cppreference.com/w/cpp/utility/expected/unexpected
 */
template <class E>
class unexpected {
 public:
  constexpr explicit unexpected(E error) : error_(std::move(error)) {}

  constexpr const E& error() const& noexcept { return error_; }
  constexpr E& error() & noexcept { return error_; }
  constexpr E&& error() && noexcept { return std::move(error_); }

 private:
  E error_;
};

template <class E>
unexpected(E) -> unexpected<E>;

/**
 * \brief C++20-compatible subset of std::expected<T, E> (standardized in
 *        C++23).
 *
 * Provides a drop-in vocabulary type for the "assert for invariants,
 * {{NS}}::expected for recoverable errors, never throw" policy while the project
 * targets strict C++20. The public surface deliberately mirrors
 * std::expected so switching to std::expected later is a search-and-replace.
 *
 * The error alternative is stored as \ref unexpected<E> so the underlying
 * std::variant alternatives are always distinct even when \c T and \c E are
 * the same type.
 *
 * Naming follows the standard-library convention (lowercase type, std-style
 * members) instead of Google style, on purpose: this is a compatibility shim
 * that must stay interface-identical to std::expected.
 *
 * \see https://en.cppreference.com/w/cpp/utility/expected
 */
template <class T, class E>
class [[nodiscard]] expected {
  static_assert(!std::is_reference_v<T>, "T must be a non-reference type");
  static_assert(!std::is_void_v<T>,
                "use the expected<void, E> specialization for void");

 public:
  using value_type = T;
  using error_type = E;
  using unexpected_type = unexpected<E>;

  constexpr expected()
    requires std::is_default_constructible_v<T>
      : storage_(std::in_place_index<0>) {}

  constexpr expected(T value)  // NOLINT(google-explicit-constructor)
      : storage_(std::in_place_index<0>, std::move(value)) {}

  constexpr expected(unexpected<E> error)  // NOLINT(google-explicit-constructor)
      : storage_(std::in_place_index<1>, std::move(error)) {}

  [[nodiscard]] constexpr bool has_value() const noexcept {
    return storage_.index() == 0;
  }
  constexpr explicit operator bool() const noexcept { return has_value(); }

  constexpr const T& value() const& {
    assert(has_value());
    return std::get<0>(storage_);
  }
  constexpr T& value() & {
    assert(has_value());
    return std::get<0>(storage_);
  }
  constexpr T&& value() && {
    assert(has_value());
    return std::get<0>(std::move(storage_));
  }

  constexpr const E& error() const& {
    assert(!has_value());
    return std::get<1>(storage_).error();
  }
  constexpr E& error() & {
    assert(!has_value());
    return std::get<1>(storage_).error();
  }

  template <class U>
  constexpr T value_or(U&& default_value) const& {
    return has_value() ? std::get<0>(storage_)
                       : static_cast<T>(std::forward<U>(default_value));
  }

  constexpr const T& operator*() const& noexcept {
    assert(has_value());
    return std::get<0>(storage_);
  }
  constexpr T& operator*() & noexcept {
    assert(has_value());
    return std::get<0>(storage_);
  }
  constexpr const T* operator->() const noexcept {
    assert(has_value());
    return std::addressof(std::get<0>(storage_));
  }
  constexpr T* operator->() noexcept {
    assert(has_value());
    return std::addressof(std::get<0>(storage_));
  }

 private:
  std::variant<T, unexpected<E>> storage_;  ///< Index 0 = value, 1 = error.
};

/**
 * \brief Specialization for operations that yield no value, only success or an
 *        error (the most common recoverable-error return shape).
 */
template <class E>
class [[nodiscard]] expected<void, E> {
 public:
  using value_type = void;
  using error_type = E;
  using unexpected_type = unexpected<E>;

  constexpr expected() noexcept = default;

  constexpr expected(unexpected<E> error)  // NOLINT(google-explicit-constructor)
      : error_(std::move(error).error()) {}

  [[nodiscard]] constexpr bool has_value() const noexcept {
    return !error_.has_value();
  }
  constexpr explicit operator bool() const noexcept { return has_value(); }

  constexpr void value() const { assert(has_value()); }

  constexpr const E& error() const& {
    assert(!has_value());
    return *error_;
  }
  constexpr E& error() & {
    assert(!has_value());
    return *error_;
  }

 private:
  std::optional<E> error_;  ///< Engaged only in the error state.
};

}  // namespace {{NS}}

#endif  // {{NS_UPPER}}_EXPECTED_H_
