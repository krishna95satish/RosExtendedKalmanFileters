// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/Include.h"
#include "extendedkalmanfilters/CameraInputVideoToRosbag.h"
#include "extendedkalmanfilters/Ros.h"

int main(int argc, char **argv) {
    Ros ros_;
    ros_.initialize(argc, argv, gFrameArgument);
    /*OutPut *node;
    CameraInputVideoToRosbag input;
    node = &input;
    node->close();
    input.close();*/
    CameraInputVideoToRosbag *obj = CameraInputVideoToRosbag::instancecreation();
    obj->close();
    ros_.spin();
    return 0;
}
