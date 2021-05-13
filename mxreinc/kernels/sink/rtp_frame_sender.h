#ifndef __MXRE_RTP_FRAME_SENDER__
#define __MXRE_RTP_FRAME_SENDER__

#include <bits/stdc++.h>
#include <raft>

#include "defs.h"
#include "kernels/kernel.h"
#include "types/cv/types.h"
#include "types/clock_types.h"
#include "types/frame.h"
#include "components/rtp_sender.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/frame.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
}

namespace mxre
{
  namespace kernels
  {
    using FrameSenderMsgType = types::Message<types::Frame>;

    class RTPFrameSender : public MXREKernel
    {
      private:
        components::RTPSender rtpSender;
        // TODO: components::Encoder encoder;

        // Encoder
        std::string encoderName;
        int width, height;

        AVCodec* encoder;
        AVCodecContext *encoderContext;
        AVFrame *encodingFrame;

        cv::Mat yuvFrame;

      public:
        RTPFrameSender(std::string destAddr, int destPortBase, std::string encoderName, int width, int height,
                       int bitrate, int fps=60);
        ~RTPFrameSender();
        raft::kstatus run() override;
      void activateInPortAsRemote(const std::string tag, int portNumber)
      {
        debug_print("not allow remote port activation.");
      }
    };

  } // namespace kernels
} // namespace mxre

#endif

