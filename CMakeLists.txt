cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(SHORT_NAME vnvita)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "VNVita Alpha")
set(VITA_TITLEID  "VNVT12345")
set(VITA_VERSION  "01.50")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCES src/*.cpp)
add_executable(${SHORT_NAME}.elf
  src/ini/INIReader.cpp
  src/ini/ini.c
  ${SOURCES}
)

target_link_libraries(${SHORT_NAME}.elf
  SDL2
  vita2d
  freetype
  png
  jpeg
  ScePgf_stub
  ScePvf_stub
  SceDisplay_stub
  SceCtrl_stub
  SceAudio_stub
  SceSysmodule_stub
  SceGxm_stub
  SceCommonDialog_stub
  c
  m
  z
)

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME}.elf)

vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/logo0.png sce_sys/livearea/contents/logo0.png
  FILE sce_sys/livearea/contents/logo1.png sce_sys/livearea/contents/logo1.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml

  FILE assets/logosmall.png assets/logosmall.png
  FILE assets/scrolldown.png assets/scrolldown.png
  FILE assets/scrollup.png assets/scrollup.png
)
