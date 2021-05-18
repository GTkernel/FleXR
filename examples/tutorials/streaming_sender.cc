#include <mxre>

using namespace std;
using namespace mxre::kernels;

int main()
{
  string mxreHome = getenv("MXRE_HOME");
  if(mxreHome.empty()) {
    debug_print("Set MXRE_HOME as a environment variable"); return -1;
  }
  string configYaml = mxreHome + "/examples/tutorials/config.yaml";
  debug_print("configurations from %s", configYaml.c_str());

  YAML::Node config = YAML::LoadFile(configYaml);

  string bagFile  = config["bag_file"].as<string>();
  string bagTopic = config["bag_topic"].as<string>();
  int width       = config["width"].as<int>();
  int height      = config["height"].as<int>();
  int fps         = config["bag_fps"].as<int>();
  if(bagFile.empty() || bagTopic.empty()) {
    debug_print("Set your bag file info to %s", configYaml.c_str()); return -1;
  }

  string clientEncoder = config["client_encoder"].as<string>();

  string serverAddr    = config["server_addr"].as<string>();
  int serverFramePort  = config["server_frame_port"].as<int>();


  raft::map sendingPipeline;
  BagCamera bagCam("bag_cam", bagFile, bagTopic, fps);
  bagCam.setFramesToCache(400, 400);
  bagCam.setDebugMode();
  bagCam.setLogger("bag_cam_logger", "bag_cam.log");
  bagCam.activateOutPortAsLocal<BagCameraMsgType>("out_frame");

  RTPFrameSender rtpFrameSender(serverAddr, serverFramePort, clientEncoder, width, height, width*height*4, 60);
  rtpFrameSender.setDebugMode();
  rtpFrameSender.setLogger("rtp_frame_sender_logger", "rtp_frame_sender.log");
  rtpFrameSender.activateInPortAsLocal<FrameSenderMsgType>("in_frame");

  sendingPipeline += bagCam["out_frame"] >> rtpFrameSender["in_frame"];
  sendingPipeline.exe();

  return 0;
}
