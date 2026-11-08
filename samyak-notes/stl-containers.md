# STL Containers (LeetCode cheat sheet)

## std::priority_queue (`<queue>`)

Max-heap by default: the largest element is on top.

```cpp
std::priority_queue<int> maxH;                                       // largest on top
std::priority_queue<int, std::vector<int>, std::greater<int>> minH;  // smallest on top

// custom comparator: returning true means a sits LOWER in the heap than b
auto cmp = [](const auto& a, const auto& b) { return a.second > b.second; }; // min by .second
std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(cmp)> pq(cmp);

pq.push(x); pq.emplace(a, b);
pq.top(); pq.pop(); pq.size(); pq.empty();
```

- `pop()` returns nothing, so read `top()` first.
- Pairs compare by `.first`, then `.second`.
- The comparator is "backwards": `std::greater` gives a min-heap.

## std::queue (`<queue>`)

First in, first out.

```cpp
std::queue<int> q;
q.push(x); q.emplace(a, b);   // add at the back
q.front(); q.back();          // peek at either end
q.pop();                      // remove the front (returns nothing)
q.size(); q.empty();
```

- Like `priority_queue`, `pop()` doesn't return the element, so read `front()` first.
- No iterators and no `clear()`. If you need either, use `std::deque<int>` (`push_back`, `pop_front`, `push_front`).

## contains (C++20)

Member function on every associative container: `map`, `set`, `unordered_map`, `unordered_set` and the multi versions.

```cpp
if (m.contains(k)) { ... }   // same as m.find(k) != m.end() or m.count(k)
```

- Before C++20, people used `count(k)` for this.
- Use it only for a yes/no check. If you will read the value afterward, keep the iterator from `find` so you don't hash twice (see [modern-cpp-idioms.md](modern-cpp-idioms.md)).
- LeetCode compiles with C++20 or later, so it's available there.
- C++23 also added `contains` to `std::string` and `std::string_view`, for substrings.
