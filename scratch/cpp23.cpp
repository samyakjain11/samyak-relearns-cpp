#include <print>
#include <expected>
#include <string>

std::expected<int, std::string> parse(int x) {
    if (x < 0) return std::unexpected("negative");
    return x * 2;
}

int main() {
    auto r = parse(21);
    std::println("result: {}", r.value());
}
