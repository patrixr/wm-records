//
//  ParticleEmitter.hpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 5/3/2017.
//
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp

#include <list>
#include "ofMain.h"
#include "Particle.h"

typedef std::list<Particle*> ParticleList;

class ParticleEmitter
{
    
private:
    
    std::list<Particle*> particles;
    
public:
    ParticleEmitter();
    ~ParticleEmitter();
    
    void map(ofMesh &);
    void update();
    void draw();
    
};

#endif /* ParticleEmitter_hpp */
