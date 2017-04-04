//
//  Particle.hpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 5/3/2017.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include "ofMain.h"
#include "Particle.h"
#include <sys/time.h>

class Particle {
    
private:
    ofVec3f     pos;
    int         lifespan;
    int         size;
    uint64_t    tick;
    float       elapsed;
    bool        alive;
    long int    id;
    float       speed; // px/s
    ofVec3f     velocity;
    ofVec3f     destination;
    static long int count;
    
    float   random();
    
public:
    
    Particle(int x, int y, int z, unsigned int lifespan);
    Particle(int x, int y, int z, float maxSpeed, unsigned int lifespan);
    ~Particle();
    
    void setSize(unsigned int size);
    void update();
    void draw();
    void updateLifespan();
    unsigned long int getTimestamp();
    bool isAlive();
    void die();
    void setDestination(ofVec3f dest);
    
};

#endif /* Particle_hpp */
