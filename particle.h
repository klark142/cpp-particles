#ifndef PARTICLE_H
#define PARTICLE_H

#include<QPainter>

enum class ParticleType {
    Small,
    Big
};


class Particle
{
public:
    Particle(float initX, float initY, float speedX, float speedYm, float radius, float mass, ParticleType type);

    void move(float dt, int width, int height);
    void draw(QPainter &painter) const;
    bool collidesWith(const Particle &other) const;

    // getters
    float getRadius() const { return radius; }
    float getVX() const { return vx; }
    float getVY() const { return vy; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getMass() const { return mass; }
    ParticleType getType() const { return type; }
    // setters
    void setVX(float value) { vx = value; }
    void setVY(float value) { vy = value; }
    void setX(float value) { x = value; }
    void setY(float value) { y = value; }
    void setMass(float value) { mass = value; }

private:
    float x, y; // position
    float vx, vy; // velocity
    float radius;
    float mass;
    ParticleType type;
};

#endif // PARTICLE_H
