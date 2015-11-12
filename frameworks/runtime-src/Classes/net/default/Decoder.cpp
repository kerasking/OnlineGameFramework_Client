//
//  Decoder.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/19.
//
//

#include "Decoder.h"
#include "ProtoLoader.h"

USING_NS_CC;
using namespace std;

Decoder::Decoder()
: _offset(0) {
    _loader = ProtoLoader::getInstance();
}

int Decoder::decode(const ByteArray& bytes, ValueMap& dict) {
    auto loader = ProtoLoader::getInstance();
    
    uint16_t id = bytes.readInt16(0);
    _offset += 2;
    
    auto proto = loader->getProtoById(id);
    if(proto == nullptr) {
        return -1;
    }
    
    dict["_proto_name_"] = (*proto)["name"].GetString();
    readStruct(*proto, bytes, dict);
    
    return 0;
}

int Decoder::readStruct(const rapidjson::Value& fields, const ByteArray& bytes, cocos2d::ValueMap& dict) {
    int result = 0;
    
    auto& array = fields["field"];
    for(int i = 0; i < array.Size(); i++) {
        string field(array[i].GetString());
        
        auto subs = _loader->split(field, ' ');
        auto& name = subs[0];
        auto& type = subs[1];
        
        if(type == "list") {
            ValueVector item;
            result += readList(subs, 2, bytes, item);
            dict[name] = item;
        }
        else if(type == "struct") {
            auto struc = _loader->getProtoByName(subs[2]);
            if(struc == nullptr) {
                return -1;
            }
            ValueMap item;
            result += readStruct(*struc, bytes, item);
            dict[name] = item;
        }
        else if(type == "enum") {
            if(!fields.HasMember("enum")) {
                return -1;
            }
            string item;
            result += readEnum(fields["enum"], bytes, item);
            dict[name] = item;
        }
        else {
            Value item;
            result += readPrime(type, bytes, item);
            dict[name] = item;
        }
        
        if(result != 0) {
            return -1;
        }
    }
    return result;
}

int Decoder::readList(const std::vector<std::string>& subs, int index, const ByteArray& bytes, cocos2d::ValueVector& array) {
    // 读取数组长度
    uint16_t len = bytes.readInt16(_offset);
    _offset += 2;
    
    // 读取数组每一项
    auto& type = subs[index];
    int result = 0;
    
    if(type == "list") {
        for(int i = 0; i < len; ++i) {
            ValueVector item;
            result += readList(subs, index+1, bytes, item);
            if(result != 0) {
                return -1;
            }
            array.push_back(Value(item));
        }
    }
    else if(type == "struct") {
        auto struc = _loader->getProtoByName(subs[index+1]);
        for(int i = 0; i < len; ++i) {
            ValueMap item;
            result += readStruct(*struc, bytes, item);
            if(result != 0) {
                return -1;
            }
            array.push_back(Value(item));
        }
    }
    else {
        for(int i = 0; i < len; ++i) {
            Value item;
            result += readPrime(type, bytes, item);
            if(result != 0) {
                return -1;
            }
            array.push_back(item);
        }
    }
    return result;
}

int Decoder::readEnum(const rapidjson::Value& enums, const ByteArray& bytes, string& value) {
    int value_int = static_cast<int>(bytes.readInt8(_offset));
    _offset += 1;
    
    for(auto it = enums.MemberonBegin(); it != enums.MemberonEnd(); ++it) {
        if(it->value.GetInt() == value_int) {
            value = it->name.GetString();
            return 0;
        }
    }
    return -1;
}

int Decoder::readPrime(const std::string& type, const ByteArray& bytes, cocos2d::Value& value) {
    if(type == "int") {
        value = static_cast<int>(bytes.readInt32(_offset));
        _offset += 4;
    }
    else if(type == "string") {
        int len = 0;
        value = bytes.readString(_offset, len);
        _offset += len + 1;
    }
    else {
        log("unknown type: %s", type.c_str());
        return -1;
    }
    return 0;
}
