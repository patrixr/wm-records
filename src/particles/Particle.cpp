//
//  Particle.cpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 5/3/2017.
//
//

#include <stdlib.h>
#include <iostream>
#include "Particle.h"

long int Particle::count = 0;

//--------------------------------------------------------------
Particle::Particle(int x, int y, int z, unsigned int lifespan) :  lifespan(lifespan), pos(x,y,z), destination(0, 0, 0)
{
    alive = true;
    speed = 10;
    tick = getTimestamp();
    elapsed = 0;
    
    setSize(10);
    id = Particle::count++;
    
    velocity.set(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------
Particle::Particle(int x, int y, int z, float maxSpeed, unsigned int lifespan) : pos(x,y,z), lifespan(lifespan), speed(maxSpeed), destination(0, 0, 0)
{
    alive = true;
    tick = getTimestamp();
    elapsed = 0;
    
    setSize(10);
    id = Particle::count++;
    
    velocity.set(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
Particle::~Particle()
{
    
}

//--------------------------------------------------------------
void Particle::setSize(unsigned int s)
{
    size = s;
    
}

//--------------------------------------------------------------
void Particle::update()
{
    if (!isAlive())
        return;
    
    int now = getTimestamp();
    
    elapsed = now - tick;
    
    lifespan -= elapsed;
    tick = now;
    
    if (lifespan < 0) {
        return die();
    }
    
    //std::cout << elapsed << "*" << speed << "/1000" << std::endl;
    
    //std::cout << "before :" << pos.x << std::endl;
    float distance = pos.distance(destination);
    //float acceleration = distance > 60 ? 1 : distance/ 60;

    pos += speed * velocity;
    
//    if (pos.distance(destination) > 15) {
//        pos.x += acceleration * velocity.x * (elapsed * speed / 1000);
//        pos.y += acceleration * velocity.y * (elapsed * speed / 1000);
//        pos.z += acceleration * velocity.z * (elapsed * speed / 1000);
//    }
    //std::cout << "distance : " << distance << std::endl;
    
    elapsed = 0;
}

//--------------------------------------------------------------
void Particle::draw()
{
    if (!isAlive())
        return;

    ofSeedRandom(id);
    ofSetColor(255 * ofRandomf(), 255 * ofRandomf(), 255 * ofRandomf());
    ofDrawSphere(pos.x, pos.y, pos.z, size);
}

//--------------------------------------------------------------
void Particle::setDestination(ofVec3f dest)
{
    destination = dest;
    ofVec3f dir = dest - pos;
    velocity.set(dir.getNormalized());
}

//--------------------------------------------------------------
void Particle::updateLifespan()
{
    
}

//--------------------------------------------------------------
unsigned long int Particle::getTimestamp()
{
    return ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
bool Particle::isAlive()
{
    return alive;
}

//--------------------------------------------------------------
void Particle::die()
{
    lifespan = 0;
    alive = false;
}

//--------------------------------------------------------------
float Particle::random()
{
    return ofRandomf();
}
