//
//  Decoder.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef Decoder_h
#define Decoder_h

#include "net/impl/DecoderImpl.h"
#include "cocos2d.h"
#include "ProtoLoader.h"

class Decoder : public DecoderImpl<cocos2d::ValueMap> {
public:
    Decoder();
    virtual int decode(const ByteArray& bytes, cocos2d::ValueMap& dict) override;
    
private:
    // 读取struct
    int readStruct(const rapidjson::Value& fields, const ByteArray& bytes, cocos2d::ValueMap& dict);
    
    // 读取数组
    int readList(const std::vector<std::string>& subs, int index, const ByteArray& bytes, cocos2d::ValueVector& array);
    
    // 读取枚举值
    int readEnum(const rapidjson::Value& enums, const ByteArray& bytes, std::string& value);
    
    // 读取基本类型（int, string等）
    int readPrime(const std::string& type, const ByteArray& bytes, cocos2d::Value& value);
    
    ProtoLoader* _loader;
    size_t _offset;
};

#endif /* Decoder_h */
