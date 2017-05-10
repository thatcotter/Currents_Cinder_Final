//
//  ParticleSystem.hpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 5/8/17.
//
//

#include "Particle.cpp"

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

class ParticleSystem{
    
public:
    ParticleSystem();
    ~ParticleSystem();
    
    void setup( std::vector<std::vector<ci::vec2>> _grid,
                std::vector<std::vector<ci::Color>> _hues);
    void update();
    void draw();
    
    void repulseFrom( glm::vec2 position );
    void bounceFromEdge();
    
private:
    
    float       repulsionFactor;
    float       range;
    int         num;
    std::vector<ParticleRef> particles;
    
};

#endif /* ParticleSystem_hpp */
