//
//  ProtoDelegate.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef ProtoDelegate_h
#define ProtoDelegate_h

#include <string>

#include "ByteArray.h"
#include "cocos2d.h"

class ProtoDelegate {
public:
    // 检查接收的字节是否足够，如果足够，返回长度，否则返回-1
    int               check_bytes(ByteArray& bytes);
    ByteArray         pack(const std::string& proto, const cocos2d::ValueMap& data);
    cocos2d::ValueMap unpack(ByteArray& bytes);
};

#endif /* ProtoDelegate_h */
