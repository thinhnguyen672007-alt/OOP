#pragma once

#include <cstddef>
#include <string>

class Asset {
public:
    virtual ~Asset() = default;
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual std::string getId() const = 0;
    virtual std::size_t getSize() const = 0;
};
