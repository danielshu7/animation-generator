#ifndef TRACE_COMMAND_H
#define TRACE_COMMAND_H

#include "Command.h"
#include "Vector3.h"
#include <utility>
#include <GL/glut.h>

#define	checkImageWidth 1024
#define	checkImageHeight 1024
extern GLubyte checkImage[checkImageHeight][checkImageWidth][3];
extern void display(void);

// forward declarations
class Object_Model;
struct Ilight;
class Dispatcher;

// small epsilon value
const double EPSILON = .000001;

struct Ray3 {
    Vector3 origin;
    Vector3 direction;
};

struct Camera {
    Vector3 eyepoint;
    Vector3 gazeDir;
    Vector3 up;
    double dist;
    double leftx;
    double lefty;
    double rightx;
    double righty;
};

class Trace_Command : public Command {
public:
    // constructor
    explicit Trace_Command(const std::vector<char*> & params);

    // Don't allow copy or assignment as there should never be a reason to use them
    Trace_Command(const Trace_Command&) = delete;
    const Trace_Command& operator=(const Trace_Command&) = delete;

    // destructor
    ~Trace_Command() override = default;

    /*
     * Function:    run
     * Description: Checks conditions & parameters; then runs the Trace command
     * Arguments:   none
     * Returns:     none
     */
    void run() const override;

private:
    /*
     * Function:    trace
     * Description: renders the virtual world through ray tracing
     * Arguments:   none
     * Returns:     void
     */
    void trace()  const;

    /*
     * Function:    rayTrace
     * Description: Calculates color of pixel ray passes through (by ray tracing)
     * Arguments:   ray - ray to calculate pixel color from
     * Returns:     Vector3 - rgb color of pixel
     */
    Vector3 rayTrace(const Ray3& ray) const;

    /*
     * Function:    hit
     * Description: Checks if ray intersects with an object
     * Arguments:   ray  - ray to intersect with
     *              t0   - earliest time of interest
     *              t1   - pointer to latest time of interest
     *              curObj - holds object (or none)
     *              uNormal - holds normal vector of intersection (or none)
     * Returns:     bool - true if intersection found; false otherwise
     * Post:        t1 holds time of intersection
     */
    bool hit(const Ray3& ray, double t0, double* t1, const Object_Model** curObj, Vector3* uNormal)
    const;

    /*
     * Function:    hit1
     * Description: Checks if ray intersects with an object, returning immediately if so
     * Arguments:   ray  - ray to intersect with
     *              t0   - earliest time of interest
     *              t1   - latest time of interest
     * Returns:     bool - true if intersection found; false otherwise
     */
    bool hit1(const Ray3& ray, double t0, double t1) const;

    /*
     * Function:    shade
     * Description: Calculates shade at particular point
     * Arguments:   point  - point to calculate shade at
     *              d      - direction of incoming ray
     *              curObj - holds object (or none)
     *              uNormal - holds normal vector of intersection (or none)
     * Returns:     Vector3 - rgb shade of pixel
     */
    Vector3 shade(const Vector3& point, const Vector3& d, const Object_Model** curObj,
                  Vector3* uNormal) const;


    // static member to hold list of objects
    static std::vector<const Object_Model*> objList;

    // friend class to give access to object list (all object types + clear)
    friend class Sphere_Command;
    friend class Triangle_Command;
    friend class Box_Command;
    friend class Clear_Command;

    // static member to hold list of lights
    static std::vector<const Ilight*> lightList;

    // friend class to give access to light list
    friend class Ilight_Command;

    // static boolean checking which camera perspective to use, default true
    static bool orthoCam;
    static Camera cam;

    // friend class to set camera perspective
    friend class Orthocamera_Command;
    friend class Camera_Command;

    // static vector holding background color, default black
    static Vector3 bg;

    // friend class to set background
    friend class Background_Command;

    // static int holding max reflective recursion depth
    static int reflectDepth;
};


#endif //TRACE_COMMAND_H
