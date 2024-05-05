#include "particle.h"
#include <cmath>

Particle::Particle(float initX, float initY, float speedX, float speedY, float radius, float mass, ParticleType type)
    : x(initX), y(initY), vx(speedX), vy(speedY), radius(radius), mass(mass), type(type) {}


void Particle::move(float dt, int width, int height) {
    x += vx * dt;
    y += vy * dt;

    if (x - radius < 0 || x + radius > width) {
        vx = -vx;
    }
    if (y - radius < 0 || y + radius > height) {
        vy = -vy;
    }
}

void Particle::draw(QPainter &painter) const {
    if (this->getType() == ParticleType::Big) {
        painter.setBrush(Qt::blue);
    } else {
        painter.setBrush(Qt::green);
    }

    painter.drawEllipse(QPointF(x, y), radius, radius);
}

bool Particle::collidesWith(const Particle &other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    float dist = std::sqrt(dx * dx + dy * dy);
    return dist < radius + other.radius;
}
