#pragma once

#include <Windows.h>
#include <vector>
#include <string>

class PatternScanner {
public:
    PatternScanner(HMODULE module);
    uintptr_t find(const std::string& pattern);
private:
    uintptr_t base;
    size_t size;
    std::vector<uint8_t> to_bytes(const std::string& pattern);
    bool match(const uint8_t* data, const std::vector<uint8_t>& bytes);
};
