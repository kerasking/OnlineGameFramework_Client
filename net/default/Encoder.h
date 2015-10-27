//
//  Encoder.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef Encoder_h
#define Encoder_h

#include "net/impl/EncoderImpl.h"
#include "cocos2d.h"
#include <string>
#include "ProtoLoader.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class Encoder : public EncoderImpl<cocos2d::ValueMap> {
public:
    Encoder();
    virtual int encode(const cocos2d::ValueMap& dict, ByteArray& bytes) override;
    
private:
    // 写入struct
    int writeStruct(const rapidjson::Value& fields, const cocos2d::ValueMap& dict, ByteArray& bytes);
    
    // 写入数组
    int writeList(const std::vector<std::string>& subs, int index, const cocos2d::ValueVector& array, ByteArray& bytes);
    
    // 写入枚举值
    int writeEnum(const rapidjson::Value& enums, const cocos2d::Value& value, ByteArray& bytes);
    
    // 写入基本类型（int, string等）
    int writePrime(const std::string& type, const cocos2d::Value& value, ByteArray& bytes);
    
    ProtoLoader* _loader;
};

#endif /* Encoder_h */
