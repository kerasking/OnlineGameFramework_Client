//
//  ProtoService.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef ProtoService_h
#define ProtoService_h

#include "net/impl/EncoderImpl.h"
#include "net/impl/DecoderImpl.h"

namespace red {

template <typename MAP>
class ProtoService {
public:
    ProtoService(EncoderImpl<MAP>* encoder,
                 DecoderImpl<MAP>* decoder)
    : _encoder(encoder)
    , _decoder(decoder) {
        
    }
    
    int encode(const MAP& dict, ByteArray& bytes) {
        return _encoder->encode(dict, bytes);
    }
    
    int decode(const ByteArray& bytes, MAP& dict) {
        return _decoder->decode(bytes, dict);
    }
    
private:
    EncoderImpl<MAP>* _encoder;
    DecoderImpl<MAP>* _decoder;
};
    
}

#endif /* ProtoService_h */
