#ifndef __FLEXR_CORE_KERNEL__
#define __FLEXR_CORE_KERNEL__

#include <bits/stdc++.h>
#include <iostream>
#include <raft>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <raftinc/rafttypes.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <unistd.h>

#include "flexr_core/include/defs.h"
#include "flexr_core/include/types/types.h"
#include "flexr_core/include/types/frame.h"

// Common Components
#include "flexr_core/include/components/flexr_port_manager.h"
#include "flexr_core/include/components/logger.h"
#include "flexr_core/include/components/frequency_manager.h"

#include "flexr_core/include/utils/local_copy_functions.h"
#include "flexr_core/include/utils/serialize_functions.h"
#include "flexr_core/include/utils/deserialize_functions.h"

namespace flexr
{
  namespace kernels
  {

    /**
     * @brief Base kernel
     */
    class FleXRKernel : public raft::kernel
    {
      protected:
        std::string name, id;
        components::FleXRPortManager portManager;
        components::Logger logger;
        components::FrequencyManager freqManager;

      public:
        FleXRKernel(): portManager(&input, &output)
        {
          id = "no_id";
          name = "FleXRKernel";
        }


        ~FleXRKernel()
        {};


        FleXRKernel(std::string id): FleXRKernel()
        {
          this->id = id;
        }

        /**
         * @brief Get kernel ID
         * @return Kernel ID as std::string
         */
        std::string getId()
        {
          return id;
        }


        /**
         * @brief Set kernel class name
         * @param newName
         *  Kernel class name to set
         */
        void setName(std::string newName)
        {
          name = newName;
        }


        /**
         * @brief Get kernel class name
         * @return Kernel class name as std::string
         */
        std::string getName()
        {
          return name;
        }


        /**
         * @brief Kernel interface for run
         */
        virtual raft::kstatus run() { return raft::stop; }


        /**
         * @brief Kernel interface to activate input port as local
         * @param tag
         *  Port tag to activate
         * @see flexr::components::FleXRPortManager.activateInPortAsLocal
         */
        template <typename T>
        void activateInPortAsLocal(const std::string tag)
        {
          portManager.activateInPortAsLocal<T>(tag);
        }


        /**
         * @brief Kernel interface to activate input port as remote
         * @param tag
         *  Tag of activating port
         * @param protocol
         *  Protocol to use
         * @param portNumber
         *  Port number to activate
         * @see flexr::components::FleXRPortManager.activateInPortAsRemote
         */
        template <typename T>
        void activateInPortAsRemote(const std::string tag, std::string protocol, int portNumber)
        {
          components::RemoteProtocol p = components::RemoteProtocol::TCP;
          if(protocol == std::string("TCP"))
          {
            p = components::RemoteProtocol::TCP;
          }
          else if(protocol == std::string("RTP"))
          {
            p = components::RemoteProtocol::RTP;
          }

          portManager.activateInPortAsRemote<T>(tag, p, portNumber);
        }


        /**
         * @brief Kernel interface to activate output port as local
         * @param tag
         *  Tag of activating port
         * @see flexr::components::FleXRPortManager.activateOutPortAsLocal
         */
        template <typename T>
        void activateOutPortAsLocal(const std::string tag)
        {
          portManager.activateOutPortAsLocal<T>(tag);
        }


        /**
         * @brief Kernel interface to activate output port as remote
         * @param tag
         *  Tag of activating port
         * @param protocol
         *  Protocol to use
         * @param addr
         *  Address of remote node to connect
         * @param portNumber
         *  Port number of remote node to connect
         * @see flexr::components::FleXRPortManager.activateOutPortAsRemote
         */
        template <typename T>
        void activateOutPortAsRemote(const std::string tag, std::string protocol,
                                     const std::string addr, int portNumber)
        {
          components::RemoteProtocol p = components::RemoteProtocol::TCP;
          if(protocol == std::string("TCP"))
          {
            p = components::RemoteProtocol::TCP;
          }
          else if(protocol == std::string("RTP"))
          {
            p = components::RemoteProtocol::RTP;
          }

          portManager.activateOutPortAsRemote<T>(tag, p, addr, portNumber);
        }


        /**
         * @brief Kernel interface to duplicate an activated output port to a local output port
         * @param originTag
         *  Tag of the original port to duplicate
         * @param newTag
         *  Tag of a new port
         * @see flexr::components::FleXRPortManager.duplicateOutPortAsLocal
         */
        template <typename T>
        void duplicateOutPortAsLocal(const std::string originTag, const std::string newTag)
        {
          portManager.duplicateOutPortAsLocal<T>(originTag, newTag);
        }


        /**
         * @brief Kernel interface to duplicate an activated output port to a remote output port
         * @param originTag
         *  Tag of activating port
         * @param newTag
         *  Tag of a new port
         * @param protocol
         *  Protocol to use
         * @param addr
         *  Address of remote node to connect a new port
         * @param portNumber
         *  Port number of remote node to connect a new port
         * @see flexr::components::FleXRPortManager.duplicateOutPortAsRemote
         */
        template <typename T>
        void duplicateOutPortAsRemote(const std::string originTag, const std::string newTag,
                                      std::string protocol, const std::string addr, int portNumber)
        {
          components::RemoteProtocol p = components::RemoteProtocol::TCP;
          if(protocol == std::string("TCP"))
          {
            p = components::RemoteProtocol::TCP;
          }
          else if(protocol == std::string("RTP"))
          {
            p = components::RemoteProtocol::RTP;
          }

          portManager.duplicateOutPortAsRemote<T>(originTag, newTag, p, addr, portNumber);
        }


        /**
         * @brief Kernel interface to set a logger
         * @param loggerID
         *  Logger identifier
         * @param logFileName
         *  File name of the saved log
         * @see flexr::components::Logger
         */
        void setLogger(std::string loggerID, std::string logFileName)
        {
          logger.set(loggerID, logFileName);
        }


        /**
         * @brief Kernel interface to set the running frequency
         * @param targetFrequency
         *  Target frequency to run
         * @see flexr::components::FrequencyManager
         */
        void setFrequency(int targetFrequency)
        {
          freqManager.setFrequency(targetFrequency);
        }
    };


    /**
     * @brief Thread function for running a pipeline
     * @details std::thread t1(runPipeline, &pipeline);
     * @param pipeline
     *  Pointer to the pipeline to run
     */
    static void runPipeline(raft::map *pipeline) {
      pipeline->exe();
    }


    /**
     * @brief Thread function for running a single kernel without pipelining
     * @details std::thread t1(runSigleKernel, &kernel);
     * @param kernel
     *  Pointer to the kernel to run
     */
    static void runSingleKernel (FleXRKernel *kernel)
    {
      while (1) {
        raft::kstatus ret = kernel->run();
        if (ret == raft::stop) break;
      }
    }

  }   // namespace kernels
} // namespace flexr

#endif

