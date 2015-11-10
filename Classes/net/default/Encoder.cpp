//
//  Encoder.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#include "Encoder.h"

USING_NS_CC;
using namespace std;

Encoder::Encoder() {
    _loader = ProtoLoader::getInstance();
}

int Encoder::encode(const cocos2d::ValueMap& dict, ByteArray& bytes) {
    auto it = dict.find("_proto_name_");
    if(it == dict.end()) {
        return -1;
    }
    
    auto name = it->second.asString();
    auto proto = _loader->getProtoByName(name);
    if(proto == nullptr) {
        return -1;
    }

    auto id = _loader->getIdByName(name);
    if(id < 0) {
        return -1;
    }
    
    // 写入id
    bytes.writeInt16(id);
    
    // 写入数据
    writeStruct(*proto, dict, bytes);
    
    return 0;
}

int Encoder::writeStruct(const rapidjson::Value& fields, const ValueMap& dict, ByteArray& bytes) {
    int result = 0;
    
    auto& array = fields["field"];
    for(int i = 0; i < array.Size(); i++) {
        string field(array[i].GetString());
        
        auto subs = _loader->split(field, ' ');
        auto& name = subs[0];
        auto& type = subs[1];
        
        auto it = dict.find(name);
        if(it == dict.end()) {
            return -1;
        }
        
        auto& value = it->second;
        
        if(type == "list") {
            result += writeList(subs, 2, value.asValueVector(), bytes);
        }
        else if(type == "struct") {
            auto struc = _loader->getProtoByName(subs[2]);
            if(struc == nullptr) {
                return -1;
            }
            result += writeStruct(*struc, value.asValueMap(), bytes);
        }
        else if(type == "enum") {
            if(!fields.HasMember("enum")) {
                return -1;
            }
            result += writeEnum(fields["enum"], value.asString(), bytes);
        }
        else {
            result += writePrime(type, value, bytes);
        }
        
        if(result != 0) {
            return -1;
        }
    }
    return result;
}

int Encoder::writeList(const vector<string>& subs, int index, const cocos2d::ValueVector& array, ByteArray& bytes) {
    // 写入数组长度
    bytes.writeInt16(array.size());
    
    // 根据类型写入数组每一项
    auto& type = subs[index];
    int result = 0;
    
    if(type == "list") {
        for(auto& item : array) {
            result += writeList(subs, index+1, item.asValueVector(), bytes);
            if(result != 0) {
                return -1;
            }
        }
    }
    else if(type == "struct") {
        auto struc = _loader->getProtoByName(subs[index+1]);
        for(auto& item : array) {
            result += writeStruct(*struc, item.asValueMap(), bytes);
            if(result != 0) {
                return -1;
            }
        }
    }
    else {
        for(auto& item : array) {
            result += writePrime(type, item, bytes);
            if(result != 0) {
                return -1;
            }
        }
    }
    return result;
}

int Encoder::writeEnum(const rapidjson::Value& enums, const string& value, ByteArray& bytes) {
    auto value_enum = value.c_str();
    assert(enums.HasMember(value_enum));
    int value_int = enums[value_enum].GetInt();
    bytes.writeInt8(static_cast<uint8_t>(value_int));
    return 0;
}

int Encoder::writePrime(const string& type, const Value& value, ByteArray& bytes) {
    if(type == "int") {
        bytes.writeInt32(value.asInt());
    }
    else if(type == "string") {
        bytes.writeString(value.asString());
    }
    else {
        log("unknown type: %s", type.c_str());
        return -1;
    }
    return 0;
}
