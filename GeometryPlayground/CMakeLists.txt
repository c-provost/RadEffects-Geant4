cmake_minimum_required(VERSION 3.16...3.27)

project(RadiationPackage)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES
"*.mac" )

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(RadPack RadiationPackage.cc ${sources} ${headers})
target_link_libraries(RadPack ${Geant4_LIBRARIES})

add_custom_target(RadiationPackage DEPENDS RadPack)


# saving this for later - I believe I can use this for copying macros easily.
#set(exgps_SCRIPTS
   # exgps_batch.in exgps.in exgps_MT.in macros/spectrum.dat plotHisto.C vis.mac
  #)