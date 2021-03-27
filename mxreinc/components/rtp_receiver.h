#ifndef __MXRE_COMPONENTS_RTP_RECEIVER__
#define __MXRE_COMPONENTS_RTP_RECEIVER__

#include <uvgrtp/lib.hh>
#include "defs.h"

namespace mxre {
  namespace components {
    class RTPReceiver {
    private:
      uvg_rtp::context rtpContext;
      uvg_rtp::session *rtpSession;
      uvg_rtp::media_stream *rtpStream;

    public:
      ~RTPReceiver();
      RTPReceiver(std::string ip, int even_port);
      bool receive(uint8_t *outDataBuffer, uint32_t *outDataSize);
    };
  }
}
#endif

