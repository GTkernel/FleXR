#include <bits/stdc++.h>
#include <flexr_core/include/components/cv_frame_reader.h>


namespace flexr {
  namespace components
  {
    CVFrameReader::CVFrameReader (int devIdx, int width, int height):
      intrinsic (3, 3, CV_64FC1),
      distCoeffs (4, 1, CV_64FC1, {0, 0, 0, 0})
    {
      instance.open(devIdx, cv::CAP_ANY);
      instance.set(cv::CAP_PROP_FRAME_WIDTH, width);
      instance.set(cv::CAP_PROP_FRAME_HEIGHT, height);
      if (!instance.isOpened()) {
        std::cerr << "ERROR: unable to open camera" << std::endl;
        exit(1);
      }

      // set default camera intrinsic
      this->intrinsic.at<double>(0, 0) = width;
      this->intrinsic.at<double>(0, 1) = 0;
      this->intrinsic.at<double>(0, 2) = width/2;

      this->intrinsic.at<double>(1, 0) = 0;
      this->intrinsic.at<double>(1, 1) = width;
      this->intrinsic.at<double>(1, 2) = height/2;

      this->intrinsic.at<double>(2, 0) = 0;
      this->intrinsic.at<double>(2, 1) = 0;
      this->intrinsic.at<double>(2, 2) = 1;
    }


    CVFrameReader::~CVFrameReader () { if (instance.isOpened()) instance.release(); }


    flexr::types::Frame CVFrameReader::readFrame ()
    {
      flexr::types::Frame temp(height, width, CV_8UC3);

      while (1) {
        instance.read(temp.useAsCVMat());
        if (temp.useAsCVMat().empty()) {
          std::cerr << "ERROR: blank frame grabbed. Try again.." << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else break;
      }

      return temp;
    }
  }
}

