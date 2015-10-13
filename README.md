Kinect Tracked People's Joints to Yarp and ROS
===

Connects to Kinect v2, opens Yarp Bottle port, ROS message topic, and sends the tracked people's joints positions and orientation alongside the floor estimation and a Header with a time stamp.

~~~~~~~~~~~~~~~~
~ Prerequisites: This code requires OpenCV, Yarp, and Kinect SDK v2.
~~~~~~~~~~~~~~~~

To compile in Windows, MSVS2013 you need to:

1. create a new project, turning off `Precompiled Headers` in the creation wizard
2. add these files to project,
3. add the opencv, Yarp and kinect SDK include folders to `Properties->Configuration Properties->VC++ Directories->Include Directories`
**i.e.,** `C:\Program Files\opencv\build\include;C:\Program Files\robotology\yarp-2.3.64\include;C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\inc`
4. add the opencv and kinext sdk libraries to `Properties->Configuration Properties->VC++ Directories->Library Directories`
**i.e.,** `C:\Program Files\opencv\build\x64\vc12\lib`;C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\Lib\x64;
5. list all the opencv, yarp and kinect sdk libraries in `Properties->Configuration Properties->Linker->Input->Additional Dependencies` 
**i.e.,** `C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\Lib\x64\Kinect20.lib;Kinect20.lib;Kinect20.Face.lib;Kinect20.Fusion.lib;Kinect20.VisualGestureBuilder.lib;opencv_core$(OPENCV_VER)d.lib;opencv_highgui$(OPENCV_VER)d.lib;opencv_imgproc$(OPENCV_VER)d.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_math.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_dev.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_name.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_init.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_sig.lib;C:\Program Files\robotology\yarp-2.3.64\lib\YARP_OS.lib;`

(this assumes you set the environment variable OPENCV_VER, in my case to 2411)
