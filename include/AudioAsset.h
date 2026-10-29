#pragma once

#include "Asset.h"
#include "AssetLoader.h"

#include <string>
#include <vector>

class AudioAsset : public Asset {
    std::string id_;
    AssetLoader* loader_;
    std::vector<unsigned char> data_;
    bool loaded_ = false;

public:
    AudioAsset(std::string id, AssetLoader* loader);

    ~AudioAsset() override;

    void load() override;
    void unload() override;
    std::string getId() const override;
    std::size_t getSize() const override;
};
