// This is an automatically generated file.
// Generated from this FloorPlane.msg definition:
//   # This represents the floor plane.
//   #
//   #Floor Determination
//   #Each skeleton frame also contains a floor-clipping-plane vector, which contains the coefficients of an estimated floor-plane equation. The skeleton tracking system updates this estimate for each frame and uses it as a clipping plane for removing the background and segmenting players. The general plane equation is:
//   #        Ax + By + Cz + D = 0
//   #      
//   #where:
//   #        A = vFloorClipPlane.x
//   #        B = vFloorClipPlane.y
//   #        C = vFloorClipPlane.z
//   #        D = vFloorClipPlane.w
//   #      
//   #The equation is normalized so that the physical interpretation of D is the height of the camera from the floor, in meters. Note that the floor might not always be visible or detectable. In this case, the floor clipping plane is a zero vector.
//   #The floor clipping plane is used in the vFloorClipPlane member of the NUI_SKELETON_FRAME structure (for C++) and in the FloorClipPlane property in managed code.
//   
//   float64 x
//   float64 y
//   float64 z
//   float64 w
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_FloorPlane
#define YARPMSG_TYPE_FloorPlane

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class FloorPlane : public yarp::os::idl::WirePortable {
public:
  yarp::os::NetFloat64 x;
  yarp::os::NetFloat64 y;
  yarp::os::NetFloat64 z;
  yarp::os::NetFloat64 w;

  FloorPlane() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** x ***
    x = connection.expectDouble();

    // *** y ***
    y = connection.expectDouble();

    // *** z ***
    z = connection.expectDouble();

    // *** w ***
    w = connection.expectDouble();
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(4)) return false;

    // *** x ***
    x = reader.expectDouble();

    // *** y ***
    y = reader.expectDouble();

    // *** z ***
    z = reader.expectDouble();

    // *** w ***
    w = reader.expectDouble();
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** x ***
    connection.appendDouble(x);

    // *** y ***
    connection.appendDouble(y);

    // *** z ***
    connection.appendDouble(z);

    // *** w ***
    connection.appendDouble(w);
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(4);

    // *** x ***
    connection.appendInt(BOTTLE_TAG_DOUBLE);
    connection.appendDouble((double)x);

    // *** y ***
    connection.appendInt(BOTTLE_TAG_DOUBLE);
    connection.appendDouble((double)y);

    // *** z ***
    connection.appendInt(BOTTLE_TAG_DOUBLE);
    connection.appendDouble((double)z);

    // *** w ***
    connection.appendInt(BOTTLE_TAG_DOUBLE);
    connection.appendDouble((double)w);
    connection.convertTextMode();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<FloorPlane> rosStyle;
  typedef yarp::os::idl::BottleStyle<FloorPlane> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "# This represents the floor plane.\n\
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
float64 w";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("FloorPlane","FloorPlane");
    typ.addProperty("md5sum",yarp::os::Value("a779879fadf0160734f906b8c19c7004"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
