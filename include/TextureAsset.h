#pragma once

#include "Asset.h"
#include "AssetLoader.h"

#include <string>
#include <vector>

class TextureAsset : public Asset {
    std::string id_;
    AssetLoader* loader_;
    std::vector<unsigned char> data_;
    bool loaded_ = false;

public:
    TextureAsset(std::string id, AssetLoader* loader);

    ~TextureAsset() override;

    void load() override;
    void unload() override;
    std::string getId() const override;
    std::size_t getSize() const override;
};
