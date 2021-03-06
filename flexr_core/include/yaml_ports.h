#ifndef __FLEXR_CORE_YAML_PORTS__
#define __FLEXR_CORE_YAML_PORTS__

#include <bits/stdc++.h>
#include "flexr_core/include/defs.h"

namespace flexr
{
  namespace yaml
  {
    /**
     * @brief Yaml input kernel port
     * YAML attribute | Details
     * ---------------| ----------------------------
     * port_name      | Registered inport name of kernel class
     * connection_type| "local" or "remote"
     * remote_info    | [protocol, port number] for receive
     */
    class YamlInPort
    {
      public:
        std::string portName;
        std::string connectionType;
        std::string protocol;
        int bindingPortNum;


        YamlInPort()
        {
          portName       = "";
          connectionType = "";
          protocol       = "";
          bindingPortNum = -1;
        }


        void print()
        {
          std::cout << "Inport -------- " << std::endl;
          std::cout << "\tPort Name: " << portName << std::endl;
          std::cout << "\tConnection Type: " << connectionType << std::endl;
          if(connectionType == std::string("remote")) {
            std::cout << "\tProtocol: " << protocol << std::endl;
            std::cout << "\tBinding Port Number: " << bindingPortNum << std::endl;
          }
        }
    };


    /**
     * @brief Yaml output kernel port
     * YAML attribute | Details
     * ---------------| ----------------------------
     * port_name      | Outport name
     * connection_type| "local" or "remote"
     * remote_info    | [protocol, ip address, port number] of remote
     * duplicated_from| Registered outport name of kernel class
     */
    class YamlOutPort
    {
      public:
        std::string portName;
        std::string connectionType;
        std::string protocol;
        std::string connectingAddr;
        int connectingPortNum;
        std::string duplicatedFrom;


        YamlOutPort()
        {
          portName           = "";
          connectionType     = "";
          protocol           = "";
          connectingAddr     = "";
          connectingPortNum  = -1;
          duplicatedFrom     = "";
        }


        void print()
        {
          std::cout << "Outport -------- " << std::endl;
          std::cout << "\tPort Name: " << portName << std::endl;
          std::cout << "\tConnection Type: " << connectionType << std::endl;
          if(duplicatedFrom != "")
          {
            std::cout << "\tDuplicated From: " << duplicatedFrom << std::endl;
          }
          if(connectionType == std::string("remote"))
          {
            std::cout << "\tProtocol: " << protocol << std::endl;
            std::cout << "\tRemote Address: " << connectingAddr << std::endl;
            std::cout << "\tRemote Port Number: " << connectingPortNum << std::endl;
          }
        }
    };
  }
}
#endif

