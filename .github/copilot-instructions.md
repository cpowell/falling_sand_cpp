# Copilot Instructions for Modern C++ Projects

This guide provides essential conventions and patterns for AI agents working on C++ codebases.

## Language & Standards

- **C++ Standard**: C++20 (minimum - check `CMakeLists.txt` for project-specific version)
- **Build System**: CMake (check `CMakeLists.txt` for version requirements)
- **Platform Support**: Cross-platform (Windows, Linux, macOS) unless otherwise documented

## Developer Workflows

## Developer Workflows

### Building the Project

This project uses CMake with **out-of-source builds** (preferred pattern).

**Prerequisites:**
- CMake (check `CMakeLists.txt` for minimum version)
- C++20+ compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- Project dependencies (see `CMakeLists.txt` for `find_package` calls)

**Linux/macOS:**
```bash
mkdir build
cd build
cmake ..
make
./falling_sand
```

**Windows (Visual Studio):**
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\Release\falling_sand.exe
```

**Rebuild/Clean:**
```bash
# Clean build
rm -rf build/
# Or within build directory
make clean
```

### Running Tests

Check for test directories (`test/`, `tests/`) or test frameworks (Google Test, Catch2) in the project.

### Debugging

Use standard C++ debuggers (GDB, LLDB, Visual Studio Debugger). Set breakpoints in implementation files to inspect program state.

## Project-Specific Conventions and Patterns

### Naming Conventions
- **Classes & Types**: `PascalCase` (e.g., `Particle`, `Grid`, `Kind`)
- **Member Variables**: `snake_case` with trailing underscore (e.g., `kind_`, `row_`, `cells_`)
  - **Critical**: This convention distinguishes members from parameters/locals at a glance
- **Functions**: `camelCase` (e.g., `addParticle()`, `evolve()`, `getParticle()`)
- **Local Variables**: `snake_case` (e.g., `nearest_row`, `pos`)
- **Constants**: `UPPER_SNAKE_CASE` with `constexpr` (e.g., `MAX_X`, `CELL_WIDTH`)

### Code Style
- **Headers**: Always use `#pragma once` for include guards
- **Braces**: K&R style (opening brace on same line)
  ```cpp
  if (condition) {
      // code
  }
  ```
- **Indentation**: 4 spaces, no tabs
- **Include Order**:
  1. Forward declarations (when needed to break circular dependencies)
  2. Standard library headers (`<vector>`, `<random>`)
  3. Third-party libraries (`<raylib.h>`, `<imgui.h>`)
  4. Project headers (`"Grid.h"`, `"Particle.h"`)

### Memory Management
**Preferred approach**: Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) for ownership semantics.

**If raw pointers are used** (check existing code patterns):
- Always check for `nullptr` before dereferencing
- Set to `nullptr` after delete
- Be vigilant about memory leaks and ownership transfer

**Rule of Three/Five/Zero**: 
- If a class manages resources, implement all five special member functions (destructor, copy constructor, copy assignment, move constructor, move assignment)
- Or follow Rule of Zero: use smart pointers and STL containers to avoid manual resource management

### Modern C++ Usage
- **Prefer `auto`** for type inference when it improves readability:
  ```cpp
  auto pos = GetMousePosition();  // Good
  Particle* p = getParticle(r, c);  // Also fine for clarity
  ```
- **Use `constexpr`** for compile-time constants (already used: `MAX_X`, `MAX_Y`)
- **Prefer `enum class`** for scoped enumerations:
  ```cpp
  enum class Kind { None, Sand, Rock };  // Current pattern
  ```
- **Range-based for loops** when iterating (use when appropriate in `evolve()`)
- **Member initializer lists** in constructors (see `Grid`, `Particle` constructors)
- **Aggregate initialization** with braces: `Grid g{COLS, ROWS};`

### Error Handling
- **Bounds checking**: Use `assert()` for debug-time validation in critical paths
  ```cpp
  assert(index >= 0 && index < size);
  ```
- **Runtime checks**: Return `std::optional`, `nullptr`, or throw exceptions based on project conventions
- **Exception safety**: Prefer RAII and smart pointers for exception-safe code

### Forward Declarations
Use forward declarations to minimize header dependencies and break circular includes:
```cpp
// In header file
class SomeClass;  // Forward declare instead of #include "SomeClass.h"
```
Only include the full header in the `.cpp` file when you need complete type information.

## Third-Party Dependencies

Check `CMakeLists.txt` for project dependencies via `find_package()` or `add_subdirectory()` calls. Common patterns:
- **Header-only libraries**: Often included directly in project
- **External packages**: Managed via CMake's `find_package()`
- **Submodules**: Check `.gitmodules` for vendored dependencies

## Platform-Specific Considerations

Check for platform-specific code using preprocessor directives:
```cpp
#if defined(_WIN32)
    // Windows-specific code
#elif defined(__linux__)
    // Linux-specific code
#elif defined(__APPLE__)
    // macOS-specific code
#endif
```
Document any platform-specific workarounds with comments explaining the rationale.

## Code Patterns

### Constructor Initialization Lists (Always Preferred)
```cpp
class MyClass {
public:
    MyClass(int a, int b) : member_a_(a), member_b_(b) {
        // Initialization list preferred over assignment in body
    }
private:
    int member_a_;
    int member_b_;
};
```

### Aggregate Initialization
```cpp
MyClass obj{value1, value2};  // Preferred over MyClass obj(value1, value2)
```

### RAII Pattern
Ensure resources are managed by object lifetimes:
```cpp
class ResourceHandler {
public:
    ResourceHandler() { /* acquire resource */ }
    ~ResourceHandler() { /* release resource */ }
    // Delete copy, allow move if appropriate
    ResourceHandler(const ResourceHandler&) = delete;
    ResourceHandler& operator=(const ResourceHandler&) = delete;
};
```

## Key Files to Reference

- **`CMakeLists.txt`**: Build configuration, C++ standard, dependencies
- **`README.md`**: Project overview, build instructions, usage
- **Header files (`.h`)**: Interface definitions, public APIs
- **Implementation files (`.cpp`)**: Implementation details
- **`.github/copilot-instructions.md`**: This file - coding standards and patterns
