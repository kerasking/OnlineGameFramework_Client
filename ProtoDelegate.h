//
//  ProtoDelegate.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef ProtoDelegate_h
#define ProtoDelegate_h

#include <vector>
#include <string>
#include <map>

#include "ByteArray.h"
#include "cocos2d.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class ProtoDelegate {
public:
    // 检查接收的字节是否足够，如果足够，返回长度，否则返回-1
    int               check_bytes(ByteArray& bytes);
    
    // 打包和解包。客户端打包的是send字段的协议，解包的是recv字段的协议
    ByteArray         pack(const std::string& name_proto, cocos2d::ValueMap& data);
    cocos2d::ValueMap unpack(ByteArray& bytes);
    
    void loadAllProto();
    int getIdByName(const std::string& name);
    
private:
    // 字符串分隔。暂时写在这里
    std::vector<std::string> split(const std::string &text, char sep);
    
    rapidjson::Document _protos[65500]; // 100~65499
    std::map<std::string, int> _map_name;
};

#endif /* ProtoDelegate_h */
