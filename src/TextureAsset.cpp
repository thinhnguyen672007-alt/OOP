#include "TextureAsset.h"

#include <iostream>
#include <utility>

TextureAsset::TextureAsset(std::string id, AssetLoader* loader)
    : id_(std::move(id)), loader_(loader) {}

TextureAsset::~TextureAsset() {
    unload();
}

void TextureAsset::load() {
    if (loaded_) {
        return;
    }

    data_ = loader_->loadRaw(id_);
    loaded_ = true;
    std::cout << "[LOAD] Texture " << id_ << " (" << data_.size() << " bytes)\n";
}

void TextureAsset::unload() {
    if (!loaded_) {
        return;
    }

    data_.clear();
    data_.shrink_to_fit();
    loaded_ = false;
    std::cout << "[UNLOAD] Texture " << id_ << '\n';
}

std::string TextureAsset::getId() const {
    return id_;
}

std::size_t TextureAsset::getSize() const {
    return data_.size();
}
