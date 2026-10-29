#include "FileAssetLoader.h"

#include <fstream>
#include <iostream>
#include <iterator>

std::vector<unsigned char> FileAssetLoader::loadRaw(const std::string& id) {
    std::ifstream file(id, std::ios::binary);
    if (file) {
        return std::vector<unsigned char>(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());
    }

    std::cout << "[WARN] File not found: " << id << ", using simulated data\n";
    return std::vector<unsigned char>(64 * 1024, 0);
}
