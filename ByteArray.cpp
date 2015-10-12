//
//  ByteArray.cpp
//  LuaTest38
//
//  Created by Buwenjie on 15/9/28.
//
//

#include "ByteArray.h"

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
    writeInt16(data.size());
    for(auto& d : data) {
        _buffer.push_back(uint8_t(d));
    }
}

void ByteArray::writeBytes(uint8_t* bytes, size_t count) {
    _buffer.insert(_buffer.end(), bytes, bytes + count);
}

uint8_t ByteArray::readInt8(size_t offset) {
    return *(first() + offset);
}

uint16_t ByteArray::readInt16(size_t offset) {
    byte* data = first() + offset;
    
    if(_endian == ByteEndian::LITTLE) {
        return (data[1] << 8) | (data[0]);
    } else {
        return (data[0] << 8) | (data[1]);
    }
}

uint32_t ByteArray::readInt32(size_t offset) {
    byte* data = first() + offset;
    
    if(_endian == ByteEndian::LITTLE) {
        return (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | (data[0]);
    } else {
        return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]);
    }
}

std::string ByteArray::readString(size_t offset, size_t len) {
    byte* data = first() + offset;
    
    char* buf = new char[len+1];
    for(size_t i = 0; i < len; i++) {
        buf[i] = data[i];
    }
    buf[len] = 0;
    
    std::string result(buf);
    delete[] buf;
    return result;
}

byte* ByteArray::first() {
    return &_buffer.data()[0];
}

size_t ByteArray::size() {
    return _buffer.size();
}

void ByteArray::clear() {
    _buffer.clear();
}

void ByteArray::erase(size_t len) {
    _buffer.erase(_buffer.begin(), _buffer.begin() + len);
}
