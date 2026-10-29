#pragma once

#include "Asset.h"
#include "AssetLoader.h"

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

class AssetManager {
    std::unordered_map<std::string, std::shared_ptr<Asset>> cache_;
    std::unique_ptr<AssetLoader> loader_;

    explicit AssetManager(std::unique_ptr<AssetLoader> loader);
    std::shared_ptr<Asset> create(const std::string& id);

public:
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    static AssetManager& instance();

    std::shared_ptr<Asset> getAsset(const std::string& id);
    void releaseAsset(const std::string& id);
    void clear();
    std::size_t cachedCount() const;
};
