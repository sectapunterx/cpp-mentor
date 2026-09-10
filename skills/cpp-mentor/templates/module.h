#ifndef {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_
#define {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_

#include <cstdint>
#include <span>
#include <string>
#include <string_view>

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
   * \brief Example of the project's error policy in use: {{ERROR_POLICY}}.
   *
   * Recoverable failures are reported through {{RESULT_TYPE}}; a violated
   * precondition is a programmer bug and asserts instead.
   *
   * \param values Non-owning view over the input samples; must not be empty.
   * \return The computed result, or the failure reported per the policy above.
   */
  [[nodiscard]] {{RESULT_TYPE}} Process(
      std::span<const std::int64_t> values) const;

 private:
  std::string name_;  ///< Identifier supplied at construction; never empty.
};

}  // namespace {{NS}}::{{MODULE}}

#endif  // {{NS_UPPER}}_{{MODULE_UPPER}}_{{FILE_UPPER}}_H_
