//
//  EncoderImpl.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/16.
//
//

#ifndef EncoderImpl_h
#define EncoderImpl_h

#include "ByteArray.h"

template <typename MAP>
class EncoderImpl {
public:
    virtual ~EncoderImpl() {}
    
    virtual int encode(const MAP& dict, ByteArray& bytes) = 0;
};

#endif /* EncoderImpl_h */
