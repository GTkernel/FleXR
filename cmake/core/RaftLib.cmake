macro(core_use_raftlib)
  pkg_search_module(RAFTLIB REQUIRED raftlib)
  if(RAFTLIB_FOUND)
    message(STATUS "RaftLib Details")
    message("\t RaftLib_INCLUDE_DIRS: ${RAFTLIB_INCLUDE_DIRS}")
    message("\t RaftLib_LDFLAGS: ${RAFTLIB_LDFLAGS}")

    include_directories(${RAFTLIB_INCLUDE_DIRS})
    list(APPEND FLEXR_CORE_CXX_FLAGS ${RAFTLIB_CFLAGS_OTHER})
    list(APPEND FLEXR_CORE_LINKER_FLAGS ${RAFTLIB_LDFLAGS})
    add_definitions(-DZEROCPY=1)
  endif(RAFTLIB_FOUND)
endmacro()

