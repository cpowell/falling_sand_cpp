# Copilot Instructions for C++

This guide outlines best practices and modern standards for the Falling Sand C++ project. Follow these conventions for consistency and maintainability.

## Naming Conventions

- **Classes & Types**: `PascalCase` (e.g., `Particle`, `Grid`, `Kind`)
- **Member Variables**: `snake_case` with trailing underscore (e.g., `kind_`, `row_`, `cells_`)
- **Functions**: `camelCase` (e.g., `addParticle()`, `getParticle()`, `evolve()`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MAX_X`, `CELL_WIDTH`)
- **Local Variables**: `snake_case` (e.g., `nearest_row`, `pos`)

## Header Files

- Always use `#pragma once` at the top of each header file.
- Forward declare classes when possible to reduce dependencies.
- Keep interface and implementation separate (headers vs. .cpp files).
- Group include statements logically:
  1. Forward declarations
  2. Standard library headers
  3. Third-party libraries
  4. Project headers

## Best Practices

- **Use Modern C++ (C++17 and newer)**
  - Prefer `auto` for type inference when it improves readability.
  - Use `std::vector` and STL containers over raw arrays.
  - Use `constexpr` for compile-time constants.
  - Prefer `enum class` for scoped enumerations (e.g., `Particle::Kind`).

- **Memory Management**
  - Prefer raw pointers for temporary references or in container structures.
  - Consider smart pointers (`std::unique_ptr`, `std::shared_ptr`) for ownership semantics.
  - Avoid unnecessary dynamic allocation when possible.

- **Member Access**
  - Public data members are acceptable for simple data types (as seen in `Particle`).
  - Use meaningful member names with trailing underscores for clarity.

## Modern Standards

- **Use Standard Library Features**
  - Prefer STL containers and algorithms over manual loops.
  - Use `std::optional` for values that may be absent.
  - Use `enum class` for scoped enumerations.

- **Formatting**
  - Indent with 4 spaces, no tabs.
  - Use K&R brace style with opening braces on the same line:
    ```cpp
    if (condition) {
        // code
    }
    ```
  - Keep lines under 120 characters when practical.
  - Use `//` for single-line comments and `/* ... */` for multi-line comments.
  - Add spacing around operators for readability.

- **Code Style**
  - Use range-based for loops where applicable.
  - Prefer standard library algorithms over manual loops.
  - Declare variables close to their usage point.
  - Use inline initialization where appropriate (e.g., member initializers in constructors).
  - Include constructors, copy constructors, and assignment operators when managing complex state.

## Example Code

```cpp
// Particle.h - Header with forward declaration and class definition
#pragma once

class Grid;

#include <random>
#include <raylib.h>

class Particle {
public:
    enum class Kind {
        None,
        Sand,
        Rock
    };

    Particle(int row, int col, Kind kind);
    Particle& operator=(const Particle& other);
    Particle(const Particle& other);

    Kind kind_;
    Color color_;
    int row_;
    int col_;

protected:
    std::mt19937 gen_;
    std::random_device rd_;
    std::uniform_int_distribution<> dist_{ 0, 1 };
};

// Grid.h - Constructor with inline initialization
#pragma once
#include "Particle.h"
#include <vector>

class Grid {
public:
    Grid(int width, int height) : height_(height), width_(width) {
        cells_.resize(height, std::vector<Particle*>(width));
    }

    void addParticle(const int row, const int col, Particle::Kind kind);
    void removeParticle(const int row, const int col);
    Particle* getParticle(const int row, const int col) const;
    Particle::Kind particleType(const int row, const int col) const;
    void evolve();

private:
    int height_, width_;
    std::vector<std::vector<Particle*>> cells_;
    std::mt19937 gen_;
};
```

## Platform-Specific Considerations

- Use preprocessor guards for platform-specific code (e.g., Windows-specific headers).
- Document platform-specific requirements in comments.
- Test on all target platforms when possible.

## Guidelines

- Write clear, self-documenting code; prefer explicit over implicit.
- Avoid `using namespace std;` in headers.
- Use const-correctness throughout the codebase.
- Test edge cases and boundary conditions.
- Keep functions focused and concise.

---

Follow these guidelines to maintain consistency and quality in the Falling Sand C++ codebase.