#include "PatternScanner.h"

int main() {
    PatternScanner scanner(GetModuleHandle(nullptr));
    uintptr_t result = scanner.find("48 89 ?? ?? ?? 57 48 83 EC"); // example pattern LOL
    return 0;
}
