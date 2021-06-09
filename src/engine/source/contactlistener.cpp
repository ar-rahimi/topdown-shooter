//
// Created by Ahmad Rahimi on 10/1/17.
//

#include <iostream>
#include "contactlistener.h"
#include "stdio.h"

ContactListener::ContactListener() {
}

ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact* contact) {
    std::cout << "START" << std::endl;
}

void ContactListener::EndContact(b2Contact* contact) {
    std::cout << "END" << std::endl;
}

void ContactListener::PreSolve(b2Contact* contact,
                                 const b2Manifold* oldManifold) {
}

void ContactListener::PostSolve(b2Contact* contact,
                                  const b2ContactImpulse* impulse) {
}