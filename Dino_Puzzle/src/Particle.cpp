//
//  Particle.cpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 5/8/17.
//
//

#include "Particle.hpp"

ParticleRef Particle::create(glm::vec2 startPosition, ci::Color color)
{
    ParticleRef ref = std::shared_ptr<Particle>( new Particle( startPosition, color ));
    ref->setup();
    return ref;
}

Particle::Particle( glm::vec2 startPosition, ci::Color color )
{
    position = startPosition;
    friction = 0.9f;
    velocity = glm::vec2( 0.f, 0.f );
    acceleration = glm::vec2( 0.f, 0.f );
    friction = 0.95f;
    mColor = color;
}

void Particle::setup()
{
//    position = cinder::app::getWindowCenter();
    friction = 0.9f;
}

void Particle::bounceForce(float damping, bool isVertical)
{
    if (isVertical) {
        velocity.y = - velocity.y * damping;
    } else{
        velocity.x = - velocity.x * damping;
    }
}

void Particle::applyForce(glm::vec2 force)
{
    acceleration += force;
}

glm::vec2 Particle::getPos()
{
    return position;
}

void Particle::update()
{
    velocity += acceleration;
    velocity *= friction;
    position += velocity;
    acceleration *= 0.f;
}

void Particle::draw()
{
    // fancy color
//    float value = ci::length(abs(velocity)) * 100.f;
//    glm::clamp(value, 0.f, 1.f);
//    ci::gl::color(ci::Color(value, 0.f, 0.7f));
    ci::gl::color(mColor);
    // draw cricle
    ci::gl::drawSolidCircle(position, 2.f, 4);
}
