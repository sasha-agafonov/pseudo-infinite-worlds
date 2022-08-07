#ifndef EXTERN_HPP
#define EXTERN_HPP

enum POLYGON_MODE {
    FILL,
    FILL_NORMALS,
    WIREFRAME,
    WIREFRAME_NORMALS
};

enum MOVEMENT_MODE {
    FULL_STOP,
    AUTO_FORWARD,
    AUTO_BACKWARDS
};

enum ANTI_ALIASING {
    OFF,
    MSAA_4X
};

enum TRANSFORMATIONS {
    NONE,
    ROTATE
};

enum CULL_FACE {
    DISABLED,
    FRONT,
    BACK
};

extern int extern_width;
extern int extern_height;
extern int extern_polygon_mode;
extern int extern_movement_mode;
extern int extern_anti_aliasing;
extern int extern_transformation;

#endif
