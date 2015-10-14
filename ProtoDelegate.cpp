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

int ProtoDelegate::check_bytes(ByteArray& bytes) {
    if(bytes.size() < 4) {
        return -1;
    }
    
    auto len = bytes.readInt16(0);
    if(bytes.size() < len + 4) {
        return -1;
    }
    
    return len + 4;
}

ByteArray ProtoDelegate::pack(const std::string& name_proto, cocos2d::ValueMap& data) {
    int id = getIdByName(name_proto);
    
    auto& proto = _protos[id];
    auto& send = proto["send"];
    
    ByteArray body(ByteEndian::BIG);
    
    for(int i = 0; i < send.Size(); i++) {
        string field(send[i].GetString());
        
        auto subs = split(field, ' ');
        auto& type = subs[0];
        auto& name = subs[1];
        
        auto& value = data[name];
        
        if(type == "int") {
            body.writeInt32(value.asInt());
        } else if(type == "string") {
            body.writeString(value.asString());
        } else {
            log("unknown type: %s", type.c_str());
        }
    }
    
    // 把head和body写入
    ByteArray bytes(ByteEndian::BIG);
    bytes.writeInt16(body.size());
    bytes.writeInt16(id);
    bytes.writeBytes(body.first(), body.size());
    
    return std::move(bytes);
}

ValueMap ProtoDelegate::unpack(ByteArray& bytes) {
    uint16_t id = bytes.readInt16(2);
    
    auto& proto = _protos[id];
    auto& recv = proto["recv"];
    
    ValueMap data;
    int offset = 4;
    
    for(int i = 0; i < recv.Size(); i++) {
        string field(recv[i].GetString());
        auto subs = split(field, ' ');
        auto& type = subs[0];
        auto& name = subs[1];
        
        if(type == "int") {
            data[name] = Value(int(bytes.readInt32(offset)));
            offset += 4;
        } else if(type == "string") {
            int length = 0;
            data[name] = Value(bytes.readString(offset, length));
            offset += length + 1;
        }
    }
    
    return std::move(data);
}

void ProtoDelegate::loadAllProto() {
    auto data = FileUtils::getInstance()->getStringFromFile("proto/ALL.json");
    
    rapidjson::Document doc;
    doc.Parse<0>(data.c_str());
    
    if(doc.HasParseError()) {
        log("ALL.json解析失败！");
        return;
    }
    
    auto& protos_conf = doc["protos"];
    for(int i = 0; i < protos_conf.Size(); i++) {
        auto& proto = protos_conf[i];
        
        uint id = proto["id"].GetUint();
        auto name = proto["name"].GetString();
        
        // 插入到map中
        _map_name.insert(pair<string, int>(name, id));
        
        // 读取协议文件内容
        string proto_file = string("proto/") + name;
        auto proto_data = FileUtils::getInstance()->getStringFromFile(proto_file);
        
        // 解析并保存到_protos
        _protos[id].Parse<0>(proto_data.c_str());
        if(_protos[id].HasParseError()) {
            log("proto parse error: %d %s", id, name);
        } else {
            log("load proto: %d %s", id, name);
        }
    }
}

int ProtoDelegate::getIdByName(const string& name) {
    return _map_name[name];
}

vector<std::string> ProtoDelegate::split(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    int start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}
