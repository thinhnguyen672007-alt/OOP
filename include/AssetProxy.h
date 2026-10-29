#pragma once

#include "Asset.h"

#include <memory>
#include <string>

class AssetManager;

class AssetProxy : public Asset {
    std::string id_;
    AssetManager* manager_;
    std::shared_ptr<Asset> realAsset_;

    std::shared_ptr<Asset> resolve();

public:
    AssetProxy(std::string id, AssetManager* manager);

    void load() override;
    void unload() override;
    std::string getId() const override;
    std::size_t getSize() const override;
};
