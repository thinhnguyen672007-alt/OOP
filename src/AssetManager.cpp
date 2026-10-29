#include "AssetManager.h"

#include "AudioAsset.h"
#include "FileAssetLoader.h"
#include "TextureAsset.h"

#include <iostream>
#include <utility>

AssetManager::AssetManager(std::unique_ptr<AssetLoader> loader)
    : loader_(std::move(loader)) {}

AssetManager& AssetManager::instance() {
    static AssetManager manager(std::make_unique<FileAssetLoader>());
    return manager;
}

std::shared_ptr<Asset> AssetManager::create(const std::string& id) {
    const std::size_t dot = id.find_last_of('.');
    const std::string ext = dot == std::string::npos ? "" : id.substr(dot);

    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp") {
        return std::make_shared<TextureAsset>(id, loader_.get());
    }

    return std::make_shared<AudioAsset>(id, loader_.get());
}

std::shared_ptr<Asset> AssetManager::getAsset(const std::string& id) {
    auto it = cache_.find(id);
    if (it != cache_.end()) {
        std::cout << "[CACHE HIT] " << id << '\n';
        return it->second;
    }

    std::cout << "[CACHE MISS] " << id << '\n';
    auto asset = create(id);
    cache_.emplace(id, asset);
    return asset;
}

void AssetManager::releaseAsset(const std::string& id) {
    auto it = cache_.find(id);
    if (it == cache_.end()) {
        return;
    }

    if (it->second.use_count() == 1) {
        it->second->unload();
    }
    cache_.erase(it);
    std::cout << "[RELEASE] " << id << '\n';
}

void AssetManager::clear() {
    for (auto& entry : cache_) {
        if (entry.second.use_count() == 1) {
            entry.second->unload();
        }
    }

    cache_.clear();
    std::cout << "[CLEAR] cache empty\n";
}

std::size_t AssetManager::cachedCount() const {
    return cache_.size();
}
