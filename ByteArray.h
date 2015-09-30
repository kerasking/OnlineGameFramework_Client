//
//  ByteArray.hpp
//  LuaTest38
//
//  Created by Buwenjie on 15/9/28.
//
//

#ifndef ByteArray_h
#define ByteArray_h

#include <vector>
#include <string>

typedef uint8_t byte;

enum class ByteEndian {
    BIG,    // 大端
    LITTLE  // 小端
};

class ByteArray {
public:
    ByteArray(ByteEndian endian);
    
    void clear();
    void writeInt8(uint8_t data);
    void writeInt16(uint16_t data);
    void writeInt32(uint32_t data);
    void writeString(const std::string& data);
    void writeBytes(uint8_t* bytes, size_t count);
    
    uint8_t readInt8(size_t offset);
    uint16_t readInt16(size_t offset);
    uint32_t readInt32(size_t offset);
    std::string readString(size_t offset, size_t len);
    
    byte* first();
    size_t size();
    
private:
    std::vector<byte> _buffer;
    ByteEndian _endian;
};

#endif /* ByteArray_h */
