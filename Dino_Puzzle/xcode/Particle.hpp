//
//  Particle.hpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 5/8/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

class Particle;

typedef std::shared_ptr<Particle> ParticleRef;

class Particle
{
public:
    static ParticleRef create(glm::vec2 startPosition, ci::Color color);
    
    Particle( glm::vec2 startPosition, ci::Color color );
    
    void setup();
    void update();
    void draw();
    
    glm::vec2 getPosition(){ return position; }
    
    void bounceForce( float damping, bool isVertical );
    void applyForce( glm::vec2 force );
    glm::vec2 getPos();
    
private:
    
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec2 force;
    
    ci::Color mColor;
    
    float mass;
    float friction;
    
};

#endif /* Particle_hpp */
