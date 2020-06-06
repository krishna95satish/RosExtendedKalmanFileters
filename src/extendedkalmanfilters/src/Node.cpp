// Copyright 2019 KPIT  [legal/copyright]

#include "extendedkalmanfilters/Node.h"

void Node::getData() {}
void Node::publish() {}
void Node::subscribe() {}
void Node::repeatTransmission() {}
int Node::length() {return 0;}
void Node::nextFrame() {}

Node::~Node() {
    delete(lidarInput_);
    delete(radarInput_);
}
