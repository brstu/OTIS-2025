#pragma once
#include <memory>

template <typename T>
class IFactoryModel {
public:
    virtual std::unique_ptr<T> create() const = 0;
    virtual ~IFactoryModel() = default;
};
