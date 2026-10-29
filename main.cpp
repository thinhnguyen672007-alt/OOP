#include "AssetManager.h"
#include "AssetProxy.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    AssetManager& manager = AssetManager::instance();
    assert(&AssetManager::instance() == &manager);

    auto treeA = manager.getAsset("tree.png");
    auto treeB = manager.getAsset("tree.png");
    assert(treeA == treeB);
    assert(manager.cachedCount() == 1);

    treeA->load();
    assert(treeA->getSize() > 0);
    assert(treeA->getSize() == treeB->getSize());

    std::vector<std::shared_ptr<Asset>> trees(100, treeA);
    std::cout << "[SHARE] 100 trees use one texture, use_count="
              << treeA.use_count() << '\n';
    assert(treeA.use_count() >= 101);

    {
        AssetProxy lazy("rock.png", &manager);
        assert(manager.cachedCount() == 1);
        assert(lazy.getSize() == 0);

        lazy.load();
        assert(lazy.getSize() > 0);
        assert(manager.cachedCount() == 2);
    }

    auto music = manager.getAsset("theme.wav");
    music->load();
    assert(music->getSize() > 0);
    assert(manager.cachedCount() == 3);

    trees.clear();
    treeA.reset();
    treeB.reset();
    manager.releaseAsset("tree.png");
    assert(manager.cachedCount() == 2);

    music.reset();
    manager.clear();
    assert(manager.cachedCount() == 0);

    std::cout << "[DONE] MVP checks passed\n";
    return 0;
}
