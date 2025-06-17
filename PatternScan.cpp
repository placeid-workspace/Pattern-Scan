#include "PatternScanner.h"

PatternScanner::PatternScanner(HMODULE module) {
    auto dos = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
    auto nt = reinterpret_cast<PIMAGE_NT_HEADERS>((uint8_t*)module + dos->e_lfanew);
    base = reinterpret_cast<uintptr_t>(module);
    size = nt->OptionalHeader.SizeOfImage;
}

uintptr_t PatternScanner::find(const std::string& pattern) {
    auto bytes = to_bytes(pattern);
    for (size_t i = 0; i < size - bytes.size(); i++) {
        auto addr = reinterpret_cast<uint8_t*>(base + i);
        if (match(addr, bytes)) return reinterpret_cast<uintptr_t>(addr);
    }
    return 0;
}

std::vector<uint8_t> PatternScanner::to_bytes(const std::string& pattern) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < pattern.length(); ) {
        if (pattern[i] == '?') {
            bytes.push_back(0xCC);
            if (i + 1 < pattern.length() && pattern[i + 1] == '?') i++;
            i++;
        } else {
            bytes.push_back(static_cast<uint8_t>(std::strtoul(pattern.substr(i, 2).c_str(), nullptr, 16)));
            i += 2;
        }
        while (i < pattern.length() && pattern[i] == ' ') i++;
    }
    return bytes;
}

bool PatternScanner::match(const uint8_t* data, const std::vector<uint8_t>& bytes) {
    for (size_t i = 0; i < bytes.size(); i++) {
        if (bytes[i] != 0xCC && data[i] != bytes[i]) return false;
    }
    return true;
}
