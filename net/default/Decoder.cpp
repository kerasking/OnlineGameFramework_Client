//
//  Decoder.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#include "Decoder.h"
#include "ProtoLoader.h"

USING_NS_CC;
using namespace std;

int Decoder::decode(const ByteArray& bytes, ValueMap& dict) {
    auto loader = ProtoLoader::getInstance();
    
    uint16_t id = bytes.readInt16(2);
    auto proto = loader->getProtoById(id);
    if(proto == nullptr) {
        return -1;
    }
    
    auto& recv = (*proto)["recv"];
    
    int offset = 4;
    
    for(int i = 0; i < recv.Size(); i++) {
        string field(recv[i].GetString());
        auto subs = loader->split(field, ' ');
        auto& type = subs[0];
        auto& name = subs[1];
        
        if(type == "int") {
            dict[name] = Value(static_cast<int>(bytes.readInt32(offset)));
            offset += 4;
        } else if(type == "string") {
            int length = 0;
            dict[name] = Value(bytes.readString(offset, length));
            offset += length + 1;
        }
        
        if(offset >= bytes.size()) {
            return -1;
        }
    }
    
    return 0;
}
