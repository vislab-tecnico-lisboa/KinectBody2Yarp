// This is an automatically generated file.
// Generated from this JointROSmsg.msg definition:
//   # A body joint that is tracked by kinect
//   
//   # The joint number and description
//   int64 typeNum
//   string typeStr
//   
//   # Position in space and orientation
//   geometry_msgs/Pose pose
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_JointROSmsg
#define YARPMSG_TYPE_JointROSmsg

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "FloorPlane.h"
#include "geometry_msgs_Point.h"
#include "geometry_msgs_Quaternion.h"
#include "geometry_msgs_Pose.h"

class JointROSmsg : public yarp::os::idl::WirePortable {
public:
  yarp::os::NetInt64 typeNum;
  std::string typeStr;
  geometry_msgs_Pose pose;

  JointROSmsg() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** typeNum ***
    if (!connection.expectBlock((char*)&typeNum,8)) return false;

    // *** typeStr ***
    int len = connection.expectInt();
    typeStr.resize(len);
    if (!connection.expectBlock((char*)typeStr.c_str(),len)) return false;

    // *** pose ***
    if (!pose.read(connection)) return false;
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(3)) return false;

    // *** typeNum ***
    typeNum = reader.expectInt();

    // *** typeStr ***
    if (!reader.readString(typeStr)) return false;

    // *** pose ***
    if (!pose.read(connection)) return false;
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** typeNum ***
    connection.appendBlock((char*)&typeNum,8);

    // *** typeStr ***
    connection.appendInt(typeStr.length());
    connection.appendExternalBlock((char*)typeStr.c_str(),typeStr.length());

    // *** pose ***
    if (!pose.write(connection)) return false;
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(3);

    // *** typeNum ***
    connection.appendInt(BOTTLE_TAG_INT);
    connection.appendInt((int)typeNum);

    // *** typeStr ***
    connection.appendInt(BOTTLE_TAG_STRING);
    connection.appendInt(typeStr.length());
    connection.appendExternalBlock((char*)typeStr.c_str(),typeStr.length());

    // *** pose ***
    if (!pose.write(connection)) return false;
    connection.convertTextMode();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<JointROSmsg> rosStyle;
  typedef yarp::os::idl::BottleStyle<JointROSmsg> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "# A body joint that is tracked by kinect\n\
\n\
# The joint number and description\n\
int64 typeNum\n\
string typeStr\n\
\n\
# Position in space and orientation\n\
geometry_msgs/Pose pose\n\
\n================================================================================\n\
MSG: geometry_msgs/Pose\n\
geometry_msgs/Point position\n\
geometry_msgs/Quaternion orientation\n================================================================================\n\
MSG: geometry_msgs/Point\n\
float64 x\n\
float64 y\n\
float64 z\n================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("JointROSmsg","JointROSmsg");
    typ.addProperty("md5sum",yarp::os::Value("065fbcec9e2108bdde107818c01f5684"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
