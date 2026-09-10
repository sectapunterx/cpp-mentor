# {{PROJECT}}

{{ONE_LINE_DESCRIPTION}}

Modern C++20, header-first, MIT-licensed. Everything public lives under the
`{{NS}}::` namespace, one sub-namespace per module (e.g. `{{NS}}::{{MODULE}}`).

## Layout

```
{{PROJECT}}/
├── include/{{NS}}/{{MODULE}}/   # public headers (header-only libraries)
├── src/                      # command-line front-ends over the libraries
├── tests/                    # GoogleTest unit tests
├── CMakePresets.json         # clang debug+sanitizers / clang release / gcc CI
├── LICENSE                   # MIT
└── README.md
```

## Build

Requires a C++20 toolchain (clang by default), CMake ≥ 3.24, and Ninja.

```bash
cmake --preset clang-debug
cmake --build --preset clang-debug
ctest --preset clang-debug        # run the unit tests
```

Release build: swap `clang-debug` for `clang-release`. CI parity on GCC:
`gcc-release`.

## Conventions

- Strict C++20, Google C++ Style, Doxygen comments: `/** ... */` blocks with
  `\`-style tags and a mandatory `\brief`; `///<` trailing only on variables.
- Recoverable errors are reported by {{ERROR_POLICY}}; invariants use `assert`.
- Only `std::unique_ptr` / `std::shared_ptr` for ownership; no owning raw
  pointers.

## License

MIT © {{YEAR}} {{AUTHOR}}
