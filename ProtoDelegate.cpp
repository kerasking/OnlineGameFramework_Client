//
//  ProtoDelegate.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#include "ProtoDelegate.h"
#include <functional>
#include <utility>

USING_NS_CC;
using namespace std;

int ProtoDelegate::check_bytes(ByteArray &bytes) {
    if(bytes.size() < 4) {
        return -1;
    }
    
    auto len = bytes.readInt16(0);
    if(bytes.size() < len + 4) {
        return -1;
    }
    
    return len + 4;
}

ByteArray ProtoDelegate::pack(const std::string &proto, const cocos2d::ValueMap &data) {
    // todo test
    ByteArray b(ByteEndian::BIG);
    b.writeString("Mike");
    
    return std::move(b);
}

ValueMap ProtoDelegate::unpack(ByteArray& bytes) {
    ValueMap map;
    map["_MOD_"] = Value("Player");
    map["_ACT_"] = Value("Test");
    map["Hello"] = Value("World");
    
    return std::move(map);
}
