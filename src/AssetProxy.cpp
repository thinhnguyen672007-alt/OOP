#include "AssetProxy.h"

#include "AssetManager.h"

#include <utility>

AssetProxy::AssetProxy(std::string id, AssetManager* manager)
    : id_(std::move(id)), manager_(manager) {}

std::shared_ptr<Asset> AssetProxy::resolve() {
    if (!realAsset_) {
        realAsset_ = manager_->getAsset(id_);
    }
    return realAsset_;
}

void AssetProxy::load() {
    resolve()->load();
}

void AssetProxy::unload() {
    if (realAsset_) {
        realAsset_->unload();
    }
}

std::string AssetProxy::getId() const {
    return id_;
}

std::size_t AssetProxy::getSize() const {
    return realAsset_ ? realAsset_->getSize() : 0;
}
