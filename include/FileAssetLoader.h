#pragma once

#include "AssetLoader.h"

class FileAssetLoader : public AssetLoader {
public:
    std::vector<unsigned char> loadRaw(const std::string& id) override;
};
