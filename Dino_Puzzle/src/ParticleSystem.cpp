//
//  ParticleSystem.cpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 5/8/17.
//
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem()
{
    // define how many particles you wnat
    num = 500;
    // we dont want to initialize at same pos, so random range
    range = 10.f;
    // reduce repulsion
    repulsionFactor = 0.05f;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::setup( std::vector<std::vector<ci::vec2>> _grid, std::vector<std::vector<ci::Color>> _hues)

{
    particles.clear();
    for (int i = 0; i < _grid.size(); i++) {
        for (int j = 0; j < _grid[i].size(); j++) {
            particles.push_back(Particle::create( _grid[i][j], _hues[i][j]));
        }
    }
}

void ParticleSystem::repulseFrom(glm::vec2 position)
{
    // repulse function
    for (auto& p : particles){
        float distanceDiff = ci::length(p->getPos() - position);
        if (distanceDiff < 20.f){
            glm::vec2 repulsion = (p->getPos() - position) * repulsionFactor;
            p->applyForce(repulsion);
        }
    }
    
}

void ParticleSystem::bounceFromEdge()
{
    for (auto& p : particles){
        // define reaction when hit wall
        if (p->getPos().x <= 0.f || p->getPos().x >= ci::app::getWindowWidth()){
            p->bounceForce(0.95, false);
        }
        
        if (p->getPos().y <= 0.f || p->getPos().y >= ci::app::getWindowHeight()){
            p->bounceForce(0.95, true);
        }
    }
}

void ParticleSystem::update()
{
    bounceFromEdge();
    
//    for (int i = 0; i < particles.size(); i++){
//        for (int j = 0; j < particles.size(); j++){
//            if (i == j) continue;
//            // repel from each other
//            float distanceDiff = ci::length(particles[i]->getPos() - particles[j]->getPos());
//            if (distanceDiff < 5.f){
//                glm::vec2 repulsion = (particles[i]->getPos() - particles[j]->getPos()) * repulsionFactor;
//                particles[i]->applyForce(repulsion);
//            }
//        }
//    }
    
    for (auto& p : particles){
        p->update();
    }
}


void ParticleSystem::draw()
{
    for (auto& p : particles){
        p->draw();
    }
}
