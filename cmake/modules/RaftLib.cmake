macro(use_raftlib)
  pkg_search_module(RAFTLIB REQUIRED raftlib)
  if(RAFTLIB_FOUND)
    message(STATUS "[RaftLib Details]")
    message(STATUS "\t RaftLib_INCLUDE_DIRS: ${RAFTLIB_INCLUDE_DIRS}")
    message(STATUS "\t RaftLib_LDFLAGS: ${RAFTLIB_LDFLAGS}")

    include_directories(${RAFTLIB_INCLUDE_DIRS})
    list(APPEND MXRE_CXX_FLAGS ${RAFTLIB_CFLAGS_OTHER})
    list(APPEND MXRE_LINKER_FLAGS ${RAFTLIB_LDFLAGS})
  endif(RAFTLIB_FOUND)
endmacro()
