# Modern C++ Idioms

Lessons from code reviews of my LeetCode solutions.

## From LeetCode 380 (Insert Delete GetRandom O(1))

### Remove from a vector in O(1): swap with the last element, then pop_back

When order doesn't matter, overwrite the removed slot with the last element and call `vec.pop_back()`. Then `vec.size()` is always the real size.

- Don't keep a separate `size` counter next to the vector. Two sources of truth is how bugs get in (e.g. `emplace_back` lands past "dead" slots while the map records a different index).

### Make the random engine a member, seeded once

```cpp
std::mt19937 rng_{std::random_device{}()};
```

Building a new `mt19937` and `random_device` on every call is slow and gives poor randomness.

### Avoid double hashing: if-with-initializer (C++17)

`find` followed by `operator[]` hashes the key twice. Keep the iterator:

```cpp
if (auto it = map.find(val); it == map.end()) return false;
// else use it->second
```

The `it` variable is scoped to the if/else. For checks that only test existence, use `contains` (C++20).

### Pick one index type: std::size_t

- Don't store `int` in the map and read it into `unsigned int`. Use `std::size_t` everywhere.
- Watch out for `size - 1` on an unsigned type: it wraps around when the container is empty.

### In-class member initializers

```cpp
std::vector<int> vals_;
std::unordered_map<int, std::size_t> idx_;
std::mt19937 rng_{std::random_device{}()};
```

Initialize members where they're declared and drop the constructor (or `= default` it).

### Small things

- `emplace_back` gains nothing over `push_back` for an `int`.
- Short names with a trailing underscore (`vals_`, `idx_`) are the common style for members.
- `[[nodiscard]]` on member functions whose return value shouldn't be ignored.
