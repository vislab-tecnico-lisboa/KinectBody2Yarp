# Copyright: Any??
# Authors: Dario Figueira
# CopyPolicy: Any??

cmake_minimum_required(VERSION 2.8.7) # Don't know what's the minimum required

set(PROJECTNAME KinectBody2Yarp)
project(${PROJECTNAME})
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}) # For reading the FindKinectSDK20.cmake

find_package(YARP REQUIRED) # Requires YARP_DIR to be set to the root directory, and to have the /bin folder in the PATH, but when installing from binaries it sets everything automatically :)
find_package(KinectSDK20 REQUIRED) # Requires KINECTSDK20_DIR environment variable (but when istaling the SDK he already sets it, automatically). Provides KinectSDK_LIB_DIR, KinectSDK_INCLUDE_DIRS, KinectSDK_LIBRARIES
find_package(OpenCV REQUIRED)  # Requires having the OpenCV_DIR environment variable set to the base directory of OpenCv tree to use (Note it is CASE-SENSITIVE).


list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}) # To be able to load files YarpInstallationHelpers
# message(WARNING "list(APPEND CMAKE_MODULE_PATH $ {YARP_MODULE_PATH}) contains an outdated FindOpenCV.cmake file, BEWARE!")
# Actually don't beware, it compiles fine with either


add_definitions(${YARP_DEFINES})   
include(YarpInstallationHelpers) 

include_directories(${OPENCV_INCLUDE_DIR} ${YARP_INCLUDE_DIRS} ${KinectSDK_INCLUDE_DIRS})

#add_subdirectory(library)
#add_subdirectory(modules)

#icubcontrib_finalize_export(${PROJECTNAME})
#icubcontrib_add_uninstall_target()

add_executable(${PROJECTNAME} KinectBody2Yarp.cpp stdafx.cpp)
target_link_libraries(${PROJECTNAME} ${OpenCV_LIBS} ${YARP_LIBRARIES} ${KinectSDK_LIBRARIES})

message("OpenCV_LIBS " ${OpenCV_LIBS}) # Hmm, in this variable there isn't the specific version of OpenCV dll's (i.e. opencv_highgui2411d.dll) so how is it correctly linking? Is there a link from "opencv_highgui" to the specific version dll ? 
