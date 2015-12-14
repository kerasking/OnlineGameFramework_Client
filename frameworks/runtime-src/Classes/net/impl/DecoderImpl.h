//
//  DecoderImpl.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/16.
//
//

#ifndef DecoderImpl_h
#define DecoderImpl_h

#include "net/tools/ByteArray.h"

namespace red {
    
template <typename MAP>
class DecoderImpl {
public:
    virtual ~DecoderImpl() {}
    
    virtual int decode(const ByteArray& bytes, MAP& dict) = 0;
};
    
}

#endif /* DecoderImpl_h */
