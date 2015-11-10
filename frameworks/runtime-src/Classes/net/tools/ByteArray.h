//
//  ByteArray.h
//  OnlineGameFramework_Client
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
    
    void writeInt8(uint8_t data);
    void writeInt16(uint16_t data);
    void writeInt32(uint32_t data);
    void writeString(const std::string& data);
    void writeBytes(const uint8_t* bytes, size_t count);
    
    uint8_t readInt8(size_t offset) const;
    uint16_t readInt16(size_t offset) const;
    uint32_t readInt32(size_t offset) const;
    std::string readString(size_t offset, int& len) const;
    
    size_t      size()   const;
    const byte* first()  const;
    ByteEndian  endian() const;
    
    void clear();
    void erase(size_t len);
    
private:
    std::vector<byte> _buffer;
    ByteEndian _endian;
};

#endif /* ByteArray_h */
