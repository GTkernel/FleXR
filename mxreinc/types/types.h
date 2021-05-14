#ifndef __MXRE_TYPES__
#define __MXRE_TYPES__

#include <bits/stdc++.h>
#include <defs.h>

// TODO: integrate all the types into this file
namespace mxre {
  namespace types {
    typedef struct RTPTrackingInfo {
      int32_t invoice; // for sanity check
      uint32_t dataSize;
      char tag[MXRE_MSG_TAG_SIZE];
      uint32_t seq;
      double ts;
    } RTPTrackingInfo;

    template <class T>
    class Message
    {
      public:
      char     tag[MXRE_MSG_TAG_SIZE];
      uint32_t seq;
      double   ts;
      T        data;
    };

    template <typename T>
    void freePrimitiveMsg(void *msg)
    {
      T* castedMessage = static_cast<T*>(msg);
      delete castedMessage;
    }
  }
}
#endif

