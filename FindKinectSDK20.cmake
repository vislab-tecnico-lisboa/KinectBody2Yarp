# Copyright: Any?
# Authors: Dario Figueira on top of Ilaria Gori's work
# CopyPolicy: Any?

####################   Helpers   #######################
macro(CHECK_FILES _FILES _DIR)
   set(_MISSING_FILES)
   foreach(_FILE ${${_FILES}})
      if(NOT EXISTS "${_FILE}")
         get_filename_component(_FILE ${_FILE} NAME)
         set(_MISSING_FILES "${_MISSING_FILES}${_FILE}, ")
      endif()
   endforeach()
   if(_MISSING_FILES)
      message(STATUS "In folder \"${${_DIR}}\" not found files: ${_MISSING_FILES}")
      set(KinectSDK20_FOUND FALSE)
   endif()
endmacro()

macro(CHECK_DIR _DIR)
   if(NOT EXISTS "${${_DIR}}")
      message(STATUS "Folder \"${${_DIR}}\" not found.")
      set(KinectSDK20_FOUND FALSE)
   endif()
endmacro()

##################### Checking #######################

set(KinectSDK20_ROOT         $ENV{KINECTSDK20_DIR})
set(KinectSDK20_LIB_DIR      ${KinectSDK20_ROOT}/Lib/x64) # THIS SHOULD BE AUTOMATIC TO CHOOSE BETWEEN x64 and x86
set(KinectSDK20_INCLUDE_DIRS ${KinectSDK20_ROOT}/inc)
set(KinectSDK20_LIBRARIES    ${KinectSDK20_LIB_DIR}/Kinect20.lib)
mark_as_advanced(KinectSDK20_ROOT)
mark_as_advanced(KinectSDK20_LIB_DIR)

message(STATUS "Searching KinectSDK.")
set(KinectSDK20_FOUND TRUE)

check_dir(KinectSDK20_ROOT)
if(KinectSDK20_FOUND)
   check_dir(KinectSDK20_LIB_DIR)
   check_dir(KinectSDK20_INCLUDE_DIRS)
   
   if(KinectSDK20_FOUND)
      check_files(KinectSDK20_LIBRARIES KinectSDK20_LIB_DIR)

      if(KinectSDK20_FOUND)	
	     set(KinectSDK20_INCLUDES ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionApi.h
                                ${KinectSDK20_INCLUDE_DIRS}/Kinect.Face.h
                                ${KinectSDK20_INCLUDE_DIRS}/Kinect.h
                                ${KinectSDK20_INCLUDE_DIRS}/Kinect.INPC.h
                                ${KinectSDK20_INCLUDE_DIRS}/Kinect.VisualGestureBuilder.h
                                ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionBase.h
                                ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionCameraPoseFinder.h
                                ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionColorVolume.h
                                ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionDepthProcessor.h
                                ${KinectSDK20_INCLUDE_DIRS}/NuiKinectFusionVolume.h)
		 mark_as_advanced(KinectSDK20_INCLUDES)
         check_files(KinectSDK20_INCLUDES KinectSDK20_INCLUDE_DIRS)
	  endif()
   endif()
endif()

message(STATUS "KinectSDK20_FOUND: ${KinectSDK20_FOUND}.")

if(NOT KinectSDK20_FOUND)
	message(FATAL_ERROR "KinectSDK20 NOT FOUND - AND WITHOUT THIS MESSAGE CMAKE IS NOT STOPPING WITH AN ERROR ON REQUIRED PACKAGE NOT FOUND!")
endif()

