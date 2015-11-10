//
//  ProtoLoader.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#include "ProtoLoader.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

ProtoLoader::ProtoLoader() {
    
}

ProtoLoader* ProtoLoader::getInstance() {
    static ProtoLoader instance;
    return &instance;
}

void ProtoLoader::loadAllProtos() {
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
        _map_proto.insert(pair<string, int>(name, id));
        
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

vector<string> ProtoLoader::split(const std::string &text, char sep) {
    std::vector<std::string> tokens;
    int start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

const rapidjson::Document* ProtoLoader::getProtoByName(const std::string& name) {
    int id = getIdByName(name);
    if(id < 0) {
        return nullptr;
    }
    return getProtoById(id);
}

const rapidjson::Document* ProtoLoader::getProtoById(int id) {
    if(id >= 100 && id <= 65499) {
        return &_protos[id];
    }
    return nullptr;
}

const int ProtoLoader::getIdByName(const std::string& name) {
    auto it = _map_proto.find(name);
    if(it != _map_proto.end()) {
        return it->second;
    }
    return -1;
}
