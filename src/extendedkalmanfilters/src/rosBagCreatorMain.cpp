// Copyright 2019 KPIT

#include "extendedkalmanfilters/GlobalConsts.h"
#include "extendedkalmanfilters/Include.h"
#include "extendedkalmanfilters/rosBagCreator.h"
#include "extendedkalmanfilters/Ros.h"

int main(int argc, char **argv) {
    Ros ros_;
    ros_.initialize(argc, argv, gArgument);
    OutPut *node;
    RosBagCreator rosBagCreator;
    node = &rosBagCreator;
    rosBagCreator.read();
    node->close();
    return 0;
}
