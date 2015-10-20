//
//  Encoder.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#include "Encoder.h"
#include "ProtoLoader.h"

USING_NS_CC;
using namespace std;

int Encoder::encode(const cocos2d::ValueMap& dict, ByteArray& bytes) {
    auto loader = ProtoLoader::getInstance();
    
    auto it = dict.find("_proto_name_");
    if(it == dict.end()) {
        return -1;
    }
    
    auto name = it->second.asString();
    auto proto = loader->getProtoByName(name);
    if(proto == nullptr) {
        return -1;
    }
    
    auto& send = (*proto)["send"];
    
    ByteArray body(ByteEndian::BIG);
    
    for(int i = 0; i < send.Size(); i++) {
        string field(send[i].GetString());
        
        auto subs = loader->split(field, ' ');
        auto& type = subs[0];
        auto& name = subs[1];
        
        auto it = dict.find(name);
        if(it == dict.end()) {
            return -1;
        }
        
        auto& value = it->second;
        
        if(type == "int") {
            body.writeInt32(value.asInt());
        } else if(type == "string") {
            body.writeString(value.asString());
        } else {
            log("unknown type: %s", type.c_str());
        }
    }

    // 写入长度、id、body
    auto id = loader->getIdByName(name);
    if(id < 0) {
        return -1;
    }
    
    bytes.writeInt16(body.size() + 2);
    bytes.writeInt16(id);
    bytes.writeBytes(body.first(), body.size());
    return 0;
}
