#include "AudioAsset.h"

#include <iostream>
#include <utility>

AudioAsset::AudioAsset(std::string id, AssetLoader* loader)
    : id_(std::move(id)), loader_(loader) {}

AudioAsset::~AudioAsset() {
    unload();
}

void AudioAsset::load() {
    if (loaded_) {
        return;
    }

    data_ = loader_->loadRaw(id_);
    loaded_ = true;
    std::cout << "[LOAD] Audio " << id_ << " (" << data_.size() << " bytes)\n";
}

void AudioAsset::unload() {
    if (!loaded_) {
        return;
    }

    data_.clear();
    data_.shrink_to_fit();
    loaded_ = false;
    std::cout << "[UNLOAD] Audio " << id_ << '\n';
}

std::string AudioAsset::getId() const {
    return id_;
}

std::size_t AudioAsset::getSize() const {
    return data_.size();
}
