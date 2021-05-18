#ifndef __MXRE_OBJ_DETECTOR__
#define __MXRE_OBJ_DETECTOR__

#include <bits/stdc++.h>
#include <raft>

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include "defs.h"
#include "utils/cv_utils.h"
#include "types/cv/types.h"
#include "types/clock_types.h"
#include "types/frame.h"

#include "kernels/kernel.h"

namespace mxre
{
  namespace kernels
  {
    using ORBDetectorInFrameType   = types::Message<types::Frame>;
    using ORBDetectorOutMarkerType = types::Message<std::vector<cv_types::DetectedMarker>>;

    class ORBDetector : public MXREKernel
    {
      private:
        // TODO: components::ORBExtractor
        // TODO: components::ORBDetector
        std::vector<mxre::cv_types::MarkerInfo> registeredMarkers;
        cv::Ptr<cv::Feature2D> detector;
        cv::Ptr<cv::DescriptorMatcher> matcher;

        double knnMatchRatio;
        int knnParam;
        double ransacThresh;
        int minInlierThresh;

      public:
        ORBDetector(std::vector<mxre::cv_types::MarkerInfo> registeredMarkers);
        raft::kstatus run() override;
        bool logic(ORBDetectorInFrameType   *inFrame,
                   ORBDetectorOutMarkerType *outDetectedMarkers);
    };

  }   // namespace pipeline
} // namespace mxre

#endif
