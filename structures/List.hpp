#pragma once

// Abstract class
template <typename T>
class List {
public:
    virtual void insert(const T& value) = 0;
    virtual void remove(const T& value) = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
};
