macro(core_use_uvgrtp)
  pkg_search_module(UVGRTP REQUIRED uvgrtp)
  if(UVGRTP_FOUND)
    message(STATUS "uvgRTP Details")
    message("\t UVGRTP_INCLUDE_DIRS: ${UVGRTP_INCLUDE_DIRS}")
    message("\t UVGRTP_CXX_FLAGS: ${UVGRTP_CXX_FLAGS}")
    message("\t UVGRTP_LDFLAGS: ${UVGRTP_LDFLAGS}")

    include_directories(${UVGRTP_INCLUDE_DIRS})
    list(APPEND FLEXR_CORE_CXX_FLAGS ${UVGRTP_CXX_FLAGS})
    list(APPEND FLEXR_CORE_INCLUDE_DIRS -I${UVGRTP_INCLUDE_DIRS})
    list(APPEND FLEXR_CORE_LINKER_FLAGS ${UVGRTP_LDFLAGS})
  endif(UVGRTP_FOUND)
endmacro()

