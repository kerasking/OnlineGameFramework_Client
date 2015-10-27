//
//  Decoder.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef Decoder_h
#define Decoder_h

#include "net/impl/DecoderImpl.h"
#include "cocos2d.h"

class Decoder : public DecoderImpl<cocos2d::ValueMap> {
public:
    virtual int decode(const ByteArray& bytes, cocos2d::ValueMap& dict) override;
};

#endif /* Decoder_h */
