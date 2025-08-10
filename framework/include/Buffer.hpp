#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include "common.hpp"

namespace srib {

class Buffer {
public:
    Buffer(size_t size = 0) : data_(size) {}

    void resize(size_t size) { data_.resize(size); }
    uint8_t* data() { return data_.data(); }
    const uint8_t* data() const { return data_.data(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<uint8_t> data_;
};

using BufferPtr = std::shared_ptr<Buffer>;

} // namespace srib


#endif // __BUFFER_HPP__
