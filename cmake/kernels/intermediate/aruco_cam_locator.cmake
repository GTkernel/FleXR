macro(kernel_aruco_cam_locator)
  if(${KERNEL_ARUCO_CAM_LOCATOR})
    add_definitions(-D__FLEXR_KERNEL_ARUCO_CAM_LOCATOR__)
    list(APPEND FLEXR_KERNEL_LINKER_FLAGS -D__FLEXR_KERNEL_ARUCO_CAM_LOCATOR__)
    message("\t [Intermediate] ArUcoCamLocator")
  endif()
endmacro()

