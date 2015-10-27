//
//  ProtoLoader.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef ProtoLoader_h
#define ProtoLoader_h

#include <string>
#include <map>
#include <vector>

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

class ProtoLoader {
public:
    static ProtoLoader* getInstance();
    
    void loadAllProtos();
    std::vector<std::string> split(const std::string &text, char sep);
    
    const rapidjson::Document* getProtoByName(const std::string& name);
    const rapidjson::Document* getProtoById(int id);
    const int getIdByName(const std::string& name); // id < 0 表示错误
    
private:
    ProtoLoader();
    
    std::map<std::string, int> _map_proto;
    rapidjson::Document _protos[65500];  // 100~65499
};

#endif /* ProtoLoader_h */
