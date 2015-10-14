//
//  ConnectDelegate.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#include "ConnectDelegate.h"
#include "UIThreadTask.h"

USING_NS_CC;

void ConnectDelegate::on_disconnect() {
    // todo 连接中途断开的处理
}

void ConnectDelegate::on_recv_proto(const ValueMap& data) {
    // 接收并解析协议后
    UIThreadTask::getInstance()->push_proto(data);
}