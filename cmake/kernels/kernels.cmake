set(FLEXR_KERNEL_CXX_FLAGS "")
set(FLEXR_KERNEL_LINKER_FLAGS "")
set(FLEXR_KERNEL_LINKER_LIBS "")

include(cmake/kernels/source/bag_camera.cmake)
include(cmake/kernels/source/cv_camera.cmake)
include(cmake/kernels/source/keyboard.cmake)

include(cmake/kernels/sink/cv_display.cmake)
include(cmake/kernels/sink/non_display.cmake)

include(cmake/kernels/intermediate/aruco_cam_locator.cmake)
include(cmake/kernels/intermediate/aruco_detector.cmake)
include(cmake/kernels/intermediate/orb_cam_locator.cmake)
include(cmake/kernels/intermediate/cuda_orb_cam_locator.cmake)
include(cmake/kernels/intermediate/sample_marker_renderer.cmake)
include(cmake/kernels/intermediate/frame_decoder.cmake)
include(cmake/kernels/intermediate/frame_encoder.cmake)
include(cmake/kernels/intermediate/frame_converter.cmake)

macro(kernel_setup_dependencies)
  message(STATUS "[Enabled Kernels]")
  # Source
  kernel_bag_camera()
  kernel_cv_camera()
  kernel_keyboard()

  # Sink
  kernel_cv_display()
  kernel_non_display()

  # Intermediate
  kernel_aruco_cam_locator()
  kernel_aruco_detector()
  kernel_orb_cam_locator()
  kernel_cuda_orb_cam_locator()
  kernel_sample_marker_renderer()
  kernel_frame_decoder()
  kernel_frame_encoder()
  kernel_frame_converter()
endmacro()

