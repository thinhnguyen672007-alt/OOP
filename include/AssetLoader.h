#pragma once

#include <string>
#include <vector>

class AssetLoader {
public:
    virtual ~AssetLoader() = default;
    virtual std::vector<unsigned char> loadRaw(const std::string& id) = 0;
};
