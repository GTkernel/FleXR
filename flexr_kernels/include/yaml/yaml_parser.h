#pragma once

#include <bits/stdc++.h>
#include <yaml-cpp/yaml.h>

#include "flexr_core/include/core.h"

#include "flexr_kernels/include/yaml/intermediate/yaml_aruco_cam_locator.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_aruco_detector.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_frame_converter.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_frame_decoder.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_frame_encoder.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_orb_cam_locator.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_cuda_orb_cam_locator.h"
#include "flexr_kernels/include/yaml/intermediate/yaml_sample_marker_renderer.h"

#include "flexr_kernels/include/yaml/sink/yaml_cv_display.h"
#include "flexr_kernels/include/yaml/sink/yaml_non_display.h"

#include "flexr_kernels/include/yaml/source/yaml_bag_camera.h"
#include "flexr_kernels/include/yaml/source/yaml_cv_camera.h"
#include "flexr_kernels/include/yaml/source/yaml_keyboard.h"

namespace flexr
{
  namespace yaml
  {

    /**
     * @brief Yaml FleXR Parser
     */
    class YamlFleXRParser
    {
      protected:
        YAML::Node doc;
        std::map<std::string, kernels::FleXRKernel*> parsedKernelMap;
        std::vector<kernels::FleXRKernel*> singleKernels;
        std::vector<YamlLocalConnection> parsedConnections;


      public:
        /**
         * @brief Init parser with YAML file
         * @param node
         *  YAML node to parse
         */
        YamlFleXRParser(std::string yamlFile)
        {
          loadYamlFile(yamlFile);
        }


        ~YamlFleXRParser()
        {
          removeParsedInfo();
        }


        /**
         * @brief Load YAML file
         * @param yamlFile
         *  YAML file to load
         */
        void loadYamlFile(std::string yamlFile)
        {
          doc = YAML::LoadFile(yamlFile);
        }


        /**
         * @brief Get instantiated kernel map
         * @return Kernel map
         */
        std::map<std::string, flexr::kernels::FleXRKernel*> getKernelMap()
        {
          return parsedKernelMap;
        }


        /**
         * @brief Get single kernel vector
         * @return Kernel vector
         */
        std::vector<flexr::kernels::FleXRKernel*> getSingleKernels()
        {
          return singleKernels;
        }


        /**
         * @brief Get parsed connections
         * @param Parsed connections
         */
        std::vector<YamlLocalConnection> getConnections()
        {
          return parsedConnections;
        }


        /**
         * @brief Remove parsed info and instantiated kernels
         */
        void removeParsedInfo()
        {
          removeParsedConnections();
          removeKernelMap();
          removeSingleKernelVector();
        }


        /**
         * @brief Remove parsed connections
         */
        void removeParsedConnections()
        {
          parsedConnections.clear();
        }


        /**
         * @brief Remove kernel map
         */
        void removeKernelMap()
        {
          std::map<std::string, flexr::kernels::FleXRKernel*>::iterator iter;
          for(iter = parsedKernelMap.begin(); iter != parsedKernelMap.end(); iter++)
          {
            destroyKernel(iter->second);
          }
          parsedKernelMap.clear();
        }


        /**
         * @brief Remove single kernel vector
         */
        void removeSingleKernelVector()
        {
          for(int i = 0; i < singleKernels.size(); i++)
          {
            destroyKernel(singleKernels[i]);
          }
          singleKernels.clear();
        }


        /**
         * @brief Destroy instantiated kernels
         */
        void destroyKernel(flexr::kernels::FleXRKernel *kernel)
        {
          // Source kernels
#ifdef __FLEXR_KERNEL_BAG_CAMERA__
          if(kernel->getName() == "BagCamera") delete (flexr::kernels::BagCamera*) kernel;
#endif
#ifdef __FLEXR_KERNEL_CV_CAMERA__
          if(kernel->getName() == "CVCamera") delete (flexr::kernels::CVCamera*) kernel;
#endif
#ifdef __FLEXR_KERNEL_KEYBOARD__
          if(kernel->getName() == "Keyboard") delete (flexr::kernels::Keyboard*) kernel;
#endif

          // Sink kernels
#ifdef __FLEXR_KERNEL_CV_DISPLAY__
          if(kernel->getName() == "CVDisplay") delete (flexr::kernels::CVDisplay*) kernel;
#endif
#ifdef __FLEXR_KERNEL_NON_DISPLAY__
          if(kernel->getName() == "NonDisplay") delete (flexr::kernels::NonDisplay*) kernel;
#endif

          // Intermediate kernels
#ifdef __FLEXR_KERNEL_FRAME_DECODER__
          if(kernel->getName() == "FrameDecoder") delete (flexr::kernels::FrameDecoder*) kernel;
#endif
#ifdef __FLEXR_KERNEL_FRAME_ENCODER__
          if(kernel->getName() == "FrameEncoder") delete (flexr::kernels::FrameEncoder*) kernel;
#endif
#ifdef __FLEXR_KERNEL_FRAME_CONVERTER__
          if(kernel->getName() == "FrameConverter") delete (flexr::kernels::FrameConverter*) kernel;
#endif
#ifdef __FLEXR_KERNEL_CUDA_ORB_CAM_LOCATOR__
          if(kernel->getName() == "CudaOrbCamLocator") delete (flexr::kernels::CudaOrbCamLocator*) kernel;
#endif
#ifdef __FLEXR_KERNEL_ORB_CAM_LOCATOR__
          if(kernel->getName() == "OrbCamLocator") delete (flexr::kernels::OrbCamLocator*) kernel;
#endif
#ifdef __FLEXR_KERNEL_ARUCO_DETECTOR__
          if(kernel->getName() == "ArUcoDetector") delete (flexr::kernels::ArUcoDetector*) kernel;
#endif
#ifdef __FLEXR_KERNEL_ARUCO_CAM_LOCATOR__
          if(kernel->getName() == "ArUcoCamLocator") delete (flexr::kernels::ArUcoCamLocator*) kernel;
#endif
#ifdef __FLEXR_KERNEL_SAMPLE_MARKER_RENDERER__
          if(kernel->getName() == "SampleMarkerRenderer") delete (flexr::kernels::SampleMarkerRenderer*) kernel;
#endif
        }


        /**
         * @brief Initialize and instantiate kernels while parsing YAML recipe
         * @see flexr::yaml::YamlBagCamera, flexr::yaml::YamlCvCamera, flexr::yaml::YamlKeyboard,
         * flexr::yaml::YamlFrameDecoder, flexr::yaml::YamlCvDisplay, flexr::yaml::YamlNonDisplay,
         * flexr::yaml::YamlFrameEncoder, flexr::yaml::YamlFrameConverter, flexr::yaml::YamlMarkerCtxExtractor,
         * flexr::yaml::YamlCudaOrbCamLocator, flexr::yaml::YamlOrbCamLocator
         * flexr::yaml::YamlArUcoDetector, flexr::yaml::YamlArUcoCamLocator
         */
        void initKernels()
        {
          for(int i = 0; i < doc.size(); i++)
          {
            if(doc[i]["kernel"].IsDefined())
            {
              kernels::FleXRKernel* temp = nullptr;

              // Source kernels
              if(doc[i]["kernel"].as<std::string>() == "BagCamera")
              {
#ifdef __FLEXR_KERNEL_BAG_CAMERA__
                YamlBagCamera yamlBagCamera;
                yamlBagCamera.parseBagCamera(doc[i]);
                yamlBagCamera.printBagCamera();
                temp = (kernels::FleXRKernel*)yamlBagCamera.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "CVCamera")
              {
#ifdef __FLEXR_KERNEL_CV_CAMERA__
                YamlCvCamera yamlCvCamera;
                yamlCvCamera.parseCvCamera(doc[i]);
                yamlCvCamera.printCvCamera();
                temp = (kernels::CVCamera*)yamlCvCamera.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "Keyboard")
              {
#ifdef __FLEXR_KERNEL_KEYBOARD__
                YamlKeyboard yamlKeyboard;
                yamlKeyboard.parseKeyboard(doc[i]);
                yamlKeyboard.printKeyboard();
                temp = (kernels::Keyboard*)yamlKeyboard.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }


              // Sink kernels
              if(doc[i]["kernel"].as<std::string>() == "CVDisplay")
              {
#ifdef __FLEXR_KERNEL_CV_DISPLAY__
                YamlCvDisplay yamlCvDisplay;
                yamlCvDisplay.parseCvDisplay(doc[i]);
                yamlCvDisplay.printCvDisplay();
                temp = (kernels::CVDisplay*)yamlCvDisplay.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "NonDisplay")
              {
#ifdef __FLEXR_KERNEL_NON_DISPLAY__
                YamlNonDisplay yamlNonDisplay;
                yamlNonDisplay.parseNonDisplay(doc[i]);
                yamlNonDisplay.printNonDisplay();
                temp = (kernels::CVDisplay*)yamlNonDisplay.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }


              // Intermediate kernels
              if(doc[i]["kernel"].as<std::string>() == "FrameDecoder")
              {
#ifdef __FLEXR_KERNEL_FRAME_DECODER__
                YamlFrameDecoder yamlFrameDecoder;
                yamlFrameDecoder.parseFrameDecoder(doc[i]);
                yamlFrameDecoder.printFrameDecoder();
                temp = (kernels::FrameDecoder*)yamlFrameDecoder.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "FrameEncoder")
              {
#ifdef __FLEXR_KERNEL_FRAME_ENCODER__
                YamlFrameEncoder yamlFrameEncoder;
                yamlFrameEncoder.parseFrameEncoder(doc[i]);
                yamlFrameEncoder.printFrameEncoder();
                temp = (kernels::FrameEncoder*)yamlFrameEncoder.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "FrameConverter")
              {
#ifdef __FLEXR_KERNEL_FRAME_CONVERTER__
                YamlFrameConverter yamlFrameConverter;
                yamlFrameConverter.parseFrameConverter(doc[i]);
                yamlFrameConverter.printFrameConverter();
                temp = (kernels::FrameConverter*)yamlFrameConverter.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "CudaOrbCamLocator")
              {
#ifdef __FLEXR_KERNEL_CUDA_ORB_CAM_LOCATOR__
                YamlCudaOrbCamLocator yamlCudaOrbCamLocator;
                yamlCudaOrbCamLocator.parseCudaOrbCamLocator(doc[i]);
                yamlCudaOrbCamLocator.printCudaOrbCamLocator();
                temp = (kernels::CudaOrbCamLocator*)yamlCudaOrbCamLocator.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "OrbCamLocator")
              {
#ifdef __FLEXR_KERNEL_ORB_CAM_LOCATOR__
                YamlOrbCamLocator yamlOrbCamLocator;
                yamlOrbCamLocator.parseOrbCamLocator(doc[i]);
                yamlOrbCamLocator.printOrbCamLocator();
                temp = (kernels::OrbCamLocator*)yamlOrbCamLocator.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "ArUcoDetector")
              {
#ifdef __FLEXR_KERNEL_ARUCO_DETECTOR__
                YamlArUcoDetector yamlArUcoDetector;
                yamlArUcoDetector.parseArUcoDetector(doc[i]);
                yamlArUcoDetector.printArUcoDetector();
                temp = (kernels::ArUcoDetector*)yamlArUcoDetector.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "ArUcoCamLocator")
              {
#ifdef __FLEXR_KERNEL_ARUCO_CAM_LOCATOR__
                YamlArUcoCamLocator yamlArUcoCamLocator;
                yamlArUcoCamLocator.parseArUcoCamLocator(doc[i]);
                yamlArUcoCamLocator.printArUcoCamLocator();
                temp = (kernels::ArUcoCamLocator*)yamlArUcoCamLocator.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }
              if(doc[i]["kernel"].as<std::string>() == "SampleMarkerRenderer")
              {
#ifdef __FLEXR_KERNEL_SAMPLE_MARKER_RENDERER__
                YamlArUcoCamLocator yamlArUcoCamLocator;
                YamlSampleMarkerRenderer yamlSampleMarkerRenderer;
                yamlSampleMarkerRenderer.parseSampleMarkerRenderer(doc[i]);
                yamlSampleMarkerRenderer.printSampleMarkerRenderer();
                temp = (kernels::SampleMarkerRenderer*)yamlSampleMarkerRenderer.make();
#else
                debug_print("%s is not enabled at the build time.", doc[i]["kernel"].as<std::string>().c_str());
#endif
              }

              if(temp != nullptr)
              {
                if(doc[i]["single"])
                  singleKernels.push_back(temp);
                else
                  parsedKernelMap[temp->getId()] = temp;
              }
            }
          }
        }


        /**
         * @brief Parse local connections from YAML recipe
         * @see flexr::yaml::YamlLocalConnection
         */
        void parseConnections()
        {
          for(int i = 0; i < doc.size(); i++)
          {
            if(doc[i]["local_connections"].IsDefined() && !doc[i]["single"].IsDefined())
            {
              YAML::Node connectionNode = doc[i]["local_connections"];
              for(int i = 0; i < connectionNode.size(); i++)
              {
                YamlLocalConnection temp;
                temp.sendKernel   = connectionNode[i]["send_kernel"].as<std::string>();
                temp.sendPortName = connectionNode[i]["send_port_name"].as<std::string>();
                temp.recvKernel   = connectionNode[i]["recv_kernel"].as<std::string>();
                temp.recvPortName = connectionNode[i]["recv_port_name"].as<std::string>();
                temp.queueSize    = connectionNode[i]["queue_size"].as<int>();
                temp.printConnection();
                std::cout << std::endl;
                parsedConnections.push_back(temp);
              }
            }
          }
        }

    };
  }
}

