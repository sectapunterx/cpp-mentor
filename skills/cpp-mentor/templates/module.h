#ifndef {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_
#define {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_

#include <cstdint>
#include <span>
#include <string>
#include <string_view>

#include "{{NS}}/expected.h"

/**
 * \file
 * \brief One-line summary of what this module provides.
 */

namespace {{NS}}::{{MODULE}} {

/**
 * \brief One-line summary of the type's responsibility.
 *
 * Longer description: the invariants it maintains, ownership model, and any
 * relevant algorithmic notes. Reference an external spec only after verifying
 * the link resolves.
 */
class {{CLASS}} {
 public:
  /**
   * \brief Describes the constructed state.
   * \param name Human-readable identifier for this instance.
   */
  explicit {{CLASS}}(std::string name) : name_(std::move(name)) {}

  /** \brief Returns the identifier supplied at construction. */
  [[nodiscard]] std::string_view name() const noexcept { return name_; }

  /**
   * \brief Example of the error policy: recoverable failures return an
   *        \ref {{NS}}::expected, invariants use assert, nothing throws.
   * \param values Non-owning view over the input samples.
   * \return The computed result, or an error describing why it failed.
   */
  [[nodiscard]] {{NS}}::expected<std::int64_t, std::string> Process(
      std::span<const std::int64_t> values) const;

 private:
  std::string name_;  ///< Identifier supplied at construction; never empty.
};

}  // namespace {{NS}}::{{MODULE}}

#endif  // {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_
