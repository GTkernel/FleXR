macro(core_use_rosbag)
  pkg_search_module(ROSBAG REQUIRED rosbag)
  if(ROSBAG_FOUND)
    message(STATUS "ROSBAG Details")
    message("\t ROSBAG_INCLUDE_DIRS: ${ROSBAG_INCLUDE_DIRS}")
    message("\t ROSBAG_LDFLAGS: ${ROSBAG_LDFLAGS}")

    include_directories(${ROSBAG_INCLUDE_DIRS})
    list(APPEND FLEXR_CORE_CXX_FLAGS ${ROSBAG_CFLAGS_OTHER})
    list(APPEND FLEXR_CORE_LINKER_FLAGS ${ROSBAG_LDFLAGS})
  endif(ROSBAG_FOUND)
endmacro()

