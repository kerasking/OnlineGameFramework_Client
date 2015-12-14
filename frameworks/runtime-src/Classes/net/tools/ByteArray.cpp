//
//  ByteArray.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/9/28.
//
//

#include "ByteArray.h"

using namespace red;

ByteArray::ByteArray(ByteEndian endian)
: _endian(endian) {
    
}

void ByteArray::writeInt8(uint8_t data) {
    _buffer.push_back(data & 0xff);
}

void ByteArray::writeInt16(uint16_t data) {
    if(_endian == ByteEndian::LITTLE) {
        _buffer.push_back(data & 0xff);
        _buffer.push_back(data >> 8 & 0xff);
    } else {
        _buffer.push_back(data >> 8 & 0xff);
        _buffer.push_back(data & 0xff);
    }
}

void ByteArray::writeInt32(uint32_t data) {
    if(_endian == ByteEndian::LITTLE) {
        _buffer.push_back(data & 0xff);
        _buffer.push_back(data >> 8 & 0xff);
        _buffer.push_back(data >> 16 & 0xff);
        _buffer.push_back(data >> 24 & 0xff);
    } else {
        _buffer.push_back(data >> 24 & 0xff);
        _buffer.push_back(data >> 16 & 0xff);
        _buffer.push_back(data >> 8 & 0xff);
        _buffer.push_back(data & 0xff);
    }
}

void ByteArray::writeString(const std::string& data) {
    for(auto& d : data) {
        _buffer.push_back(uint8_t(d));
    }
    // 最后写入0表示字符串结尾
    _buffer.push_back(uint8_t(0));
}

void ByteArray::writeBytes(const uint8_t* bytes, size_t count) {
    _buffer.insert(_buffer.end(), bytes, bytes + count);
}

uint8_t ByteArray::readInt8(size_t offset) const {
    return *(first() + offset);
}

uint16_t ByteArray::readInt16(size_t offset) const {
    const byte* data = first() + offset;
    
    if(_endian == ByteEndian::LITTLE) {
        return (data[1] << 8) | (data[0]);
    } else {
        return (data[0] << 8) | (data[1]);
    }
}

uint32_t ByteArray::readInt32(size_t offset) const {
    const byte* data = first() + offset;
    
    if(_endian == ByteEndian::LITTLE) {
        return (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | (data[0]);
    } else {
        return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
    }
}

std::string ByteArray::readString(size_t offset, int& len) const {
    char* data = (char*)(first() + offset);
    
    len = 0;
    while(data[len] != 0) {
        ++len;
    }
    
    return std::move(std::string(data, 0, len));
}

size_t ByteArray::size() const {
    return _buffer.size();
}

const byte* ByteArray::first() const {
    return &_buffer.data()[0];
}

ByteEndian ByteArray::endian() const {
    return _endian;
}

void ByteArray::clear() {
    _buffer.clear();
}

void ByteArray::erase(size_t len) {
    _buffer.erase(_buffer.begin(), _buffer.begin() + len);
}
