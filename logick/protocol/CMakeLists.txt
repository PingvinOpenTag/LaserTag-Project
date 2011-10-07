cmake_minimum_required(VERSION 2.6)
project(ProtocolLaserTag)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYFILE_LATEX "ON")
include(UseDoxygen)


IF (UNIX)
  ADD_CUSTOM_TARGET (gc 
      git clean -ndx && printf '***** Remove? **** (ctrl+c for exit)' && read && git clean -fdx
  )
  ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  ADD_CUSTOM_TARGET (dc make distclean)

  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   CMakeFiles
   cmake.check_cache
   Makefile
   core core.*
   gmon.out
   *~
  )
  
  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
ENDIF(UNIX)

add_library(PLT coder.c)
