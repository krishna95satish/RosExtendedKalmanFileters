// Technische Hochschule Ingolstadt

#include "extendedkalmanfilters/RosBagCreator.h"

int main(int argc, char **argv) {
    Ros ros;
    ros.initialize(argc, argv, gArgument);
    BagCreator *bagCreator;
    RosBagCreator rosBagCreator;
    bagCreator = &rosBagCreator;
    rosBagCreator.read();
    bagCreator->close();
    return 0;
}
