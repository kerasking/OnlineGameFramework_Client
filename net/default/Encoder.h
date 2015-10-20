//
//  Encoder.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef Encoder_h
#define Encoder_h

#include "net/impl/EncoderImpl.h"
#include "cocos2d.h"

class Encoder : public EncoderImpl<cocos2d::ValueMap> {
public:
    virtual int encode(const cocos2d::ValueMap& dict, ByteArray& bytes) override;
};

#endif /* Encoder_h */
