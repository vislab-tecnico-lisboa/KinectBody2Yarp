// This is an automatically generated file.
// Generated from this KinectTrackedPeopleMessage.msg definition:
//   # Message header for Kinect tracked people's message
//   #
//   #
//   
//   # The floor plane
//   FloorPlane floorPlane
//   
//   # The tracked people
//   Body[] bodies
//   
//   #Two-integer timestamp that is expressed as:
//   # * header.stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
//   # * header.stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
//   # The other fields of header are always zero
//   std_msgs/Header header
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_KinectTrackedPeopleMessage
#define YARPMSG_TYPE_KinectTrackedPeopleMessage

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "FloorPlane.h"
#include "geometry_msgs_Point.h"
#include "geometry_msgs_Quaternion.h"
#include "JointROSmsg.h"
#include "Body.h"
#include "TickTime.h"
#include "std_msgs_Header.h"

class KinectTrackedPeopleMessage : public yarp::os::idl::WirePortable {
public:
  FloorPlane floorPlane;
  std::vector<Body> bodies;
  std_msgs_Header header;

  KinectTrackedPeopleMessage() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** floorPlane ***
    if (!floorPlane.read(connection)) return false;

    // *** bodies ***
    int len = connection.expectInt();
    bodies.resize(len);
    for (int i=0; i<len; i++) {
      if (!bodies[i].read(connection)) return false;
    }

    // *** header ***
    if (!header.read(connection)) return false;
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(3)) return false;

    // *** floorPlane ***
    if (!floorPlane.read(connection)) return false;

    // *** bodies ***
    if (connection.expectInt()!=BOTTLE_TAG_LIST) return false;
    int len = connection.expectInt();
    bodies.resize(len);
    for (int i=0; i<len; i++) {
      if (!bodies[i].read(connection)) return false;
    }

    // *** header ***
    if (!header.read(connection)) return false;
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** floorPlane ***
    if (!floorPlane.write(connection)) return false;

    // *** bodies ***
    connection.appendInt(bodies.size());
    for (size_t i=0; i<bodies.size(); i++) {
      if (!bodies[i].write(connection)) return false;
    }

    // *** header ***
    if (!header.write(connection)) return false;
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(3);

    // *** floorPlane ***
    if (!floorPlane.write(connection)) return false;

    // *** bodies ***
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(bodies.size());
    for (size_t i=0; i<bodies.size(); i++) {
      if (!bodies[i].write(connection)) return false;
    }

    // *** header ***
    if (!header.write(connection)) return false;
    connection.convertTextMode();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<KinectTrackedPeopleMessage> rosStyle;
  typedef yarp::os::idl::BottleStyle<KinectTrackedPeopleMessage> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "# Message header for Kinect tracked people's message\n\
#\n\
#\n\
\n\
# The floor plane\n\
FloorPlane floorPlane\n\
\n\
# The tracked people\n\
Body[] bodies\n\
\n\
#Two-integer timestamp that is expressed as:\n\
# * header.stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * header.stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# The other fields of header are always zero\n\
std_msgs/Header header\n\
\n================================================================================\n\
MSG: FloorPlane\n\
# This represents the floor plane.\n\
#\n\
#Floor Determination\n\
#Each skeleton frame also contains a floor-clipping-plane vector, which contains the coefficients of an estimated floor-plane equation. The skeleton tracking system updates this estimate for each frame and uses it as a clipping plane for removing the background and segmenting players. The general plane equation is:\n\
#        Ax + By + Cz + D = 0\n\
#      \n\
#where:\n\
#        A = vFloorClipPlane.x\n\
#        B = vFloorClipPlane.y\n\
#        C = vFloorClipPlane.z\n\
#        D = vFloorClipPlane.w\n\
#      \n\
#The equation is normalized so that the physical interpretation of D is the height of the camera from the floor, in meters. Note that the floor might not always be visible or detectable. In this case, the floor clipping plane is a zero vector.\n\
#The floor clipping plane is used in the vFloorClipPlane member of the NUI_SKELETON_FRAME structure (for C++) and in the FloorClipPlane property in managed code.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n================================================================================\n\
MSG: Body\n\
# A tracked person\n\
\n\
# The person's track ID, usually very large numbers, converted to string just because historical reasons\n\
string trackID\n\
\n\
# The 25 joints to be tracked that compose a person\n\
JointROSmsg[25] joints\n================================================================================\n\
MSG: JointROSmsg\n\
# A body joint that is tracked by kinect\n\
\n\
# The joint number and description\n\
int64 typeNum\n\
string typeStr\n\
\n\
# Position in space and orientation\n\
geometry_msgs/Point position\n\
geometry_msgs/Quaternion orientation\n\
\n================================================================================\n\
MSG: geometry_msgs/Point\n\
float64 x\n\
float64 y\n\
float64 z\n================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n================================================================================\n\
MSG: std_msgs/Header\n\
uint32 seq\n\
time stamp\n\
string frame_id";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("KinectTrackedPeopleMessage","KinectTrackedPeopleMessage");
    typ.addProperty("md5sum",yarp::os::Value("27ffe427729ee77b420e15a61e0902d2"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
