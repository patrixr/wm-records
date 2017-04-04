//
//  ParticleEmitter.cpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 5/3/2017.
//
//

#include "ParticleEmitter.h"
#include "../audio/AudioManager.h"
#include <iostream>

//--------------------------------------------------------------
ParticleEmitter::ParticleEmitter() : particles()
{
    
}

//--------------------------------------------------------------
ParticleEmitter::~ParticleEmitter()
{
    
}

//--------------------------------------------------------------
void ParticleEmitter::map(ofMesh & mesh)
{
    int numVertices             = mesh.getNumVertices();
    int numParticles            = particles.size();
    //ParticleList::iterator  it  = particles.begin();
    //int ended                   = false;
    ofVec3f vertex;
    Particle *p;
    
    for (int i = 0; i < numVertices; i += 1) {
        vertex = mesh.getVertex(i);

        p = new Particle(vertex.x, vertex.y, vertex.z, 8, 50 + ofRandomf() * 300);
        p->setSize(2);
        p->setDestination(ofVec3f(vertex.x  - ofRandomf() * 40, vertex.y + 40, vertex.z - ofRandomf() * 40));
        particles.push_back(p);
        
//        if (ended || it == particles.end()) {
//            // Case: there are more vertices than existing particles
//            ended = true;
//            p = new Particle(vertex.x, vertex.y, vertex.z, 3, -1);
//            p->setSize(2);
//            p->setDestination(vertex);
//            particles.push_back(p);
//        } else {
//            p = *it;
//            p->setDestination(vertex);
//            it++;
//        }
    }
    
    //std::cout << particles.size() << " particles" << std::endl;
}

//--------------------------------------------------------------
void    ParticleEmitter::update()
{
    ParticleList::iterator  it  = particles.begin();
    
    while (it != particles.end())
    {
        Particle* p = *it;
        
        if (!p->isAlive())
        {
            // Cleanup
            delete p;
            it = particles.erase(it);
        }
        else
        {
            p->update();
        }
        ++it;
    }
}

//--------------------------------------------------------------
void    ParticleEmitter::draw()
{
    int s = particles.size();
    int i = 0;
    int threshold = 20000;
    
    ParticleList::iterator  it  = particles.begin();
    ParticleList::iterator  end = particles.end();
    
    while (it != end)
    {
        (*it)->draw();
        ++it;
    }
}
