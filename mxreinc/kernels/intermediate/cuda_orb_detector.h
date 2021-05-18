#ifdef __USE_OPENCV_CUDA__
#ifndef __MXRE_CUDA_OBJ_DETECTOR__
#define __MXRE_CUDA_OBJ_DETECTOR__

#include <bits/stdc++.h>
#include <opencv2/core/cvstd.hpp>
#include <raft>

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include "defs.h"
#include "kernels/kernel.h"
#include "utils/cv_utils.h"
#include "types/cv/types.h"
#include "types/clock_types.h"
#include "types/frame.h"

namespace mxre
{
  namespace kernels
  {
    using CudaORBDetectorInFrameType = types::Message<types::Frame>;
    using CudaORBDetectorOutMarkerType = types::Message<std::vector<cv_types::DetectedMarker>>;

    class CudaORBDetector : public MXREKernel
    {
      private:
        // TODO: components::CudaORBExtractor
        // TODO: components::ORBDetector

        std::vector<mxre::cv_types::MarkerInfo> registeredMarkers;
        cv::Ptr<cv::cuda::ORB> detector;
        cv::Ptr<cv::cuda::DescriptorMatcher> matcher;
        cv::cuda::Stream stream;
        cv::cuda::GpuMat cuFrame;
        cv::cuda::GpuMat cuKp, cuDesc;
        cv::cuda::GpuMat cuMatches;

        double knnMatchRatio;
        int knnParam;
        double ransacThresh;
        int minInlierThresh;

      public:
        CudaORBDetector(std::vector<mxre::cv_types::MarkerInfo> registeredMarkers);
        raft::kstatus run() override;
        bool logic(CudaORBDetectorInFrameType   *inFrame,
                   CudaORBDetectorOutMarkerType *outDetectedMarkers);
    };

  }   // namespace kernels
} // namespace mxre

#endif
#endif

