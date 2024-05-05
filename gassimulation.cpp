#include "gassimulation.h"
#include "ui_gassimulation.h"
#include "gassimulation.h"
#include <QPainter>
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>

GasSimulation::GasSimulation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GasSimulation)
{
    ui->setupUi(this);
    setMinimumSize(800, 600);

    // Initialize and configure the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GasSimulation::updatePositions);

    // create the stop button
    connect(findChild<QPushButton *>("stopSimulationButton"), &QPushButton::clicked, this, &GasSimulation::stop);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stopButton);
    setLayout(layout);

}

GasSimulation::~GasSimulation()
{
    delete ui;
}

void GasSimulation::start() {
    qDebug() << "Simulation started!";
    timer->start(16);  // Approximately 60 FPS
}

void GasSimulation::stop() {
    qDebug() << "Simulation stopped!";
    timer->stop();
    emit stopRequested();
}

void GasSimulation::initializeParticles(int bigCount, int smallCount, float temperature) {
    particles.clear();

    struct ParticleConfig {
        float radius;
        float mass;
        ParticleType type;
    };

    // Configuration for small and big particles
    const ParticleConfig smallParticle = {10.0f, 1.0f, ParticleType::Small};
    const ParticleConfig bigParticle = {15.0f, 3.0f, ParticleType::Big};

    // Function to generate a specific type of particle
    auto generateParticles = [this](int count, const ParticleConfig& config, float temperature) {
        float baseSpeed = std::sqrt(temperature / config.mass); // Adjust speed by mass

        for (int i = 0; i < count; ++i) {
            float x, y, vx, vy;
            int maxAttempts = 100;
            bool overlapping = true;

            // Find a position that's not overlapping
            while (overlapping && maxAttempts-- > 0) {
                x = std::rand() % width();
                y = std::rand() % height();

                if (!isOverlapping(x, y, config.radius)) {
                    overlapping = false;
                }
            }

            // If overlapping attempts failed, skip this particle
            if (overlapping) {
                qDebug() << "Skipping particle due to too many overlapping attempts.";
                continue;
            }

            // Generate random velocity with the calculated base speed
            vx = baseSpeed * ((std::rand() % 100) / 50.0f - 1.0f);
            vy = baseSpeed * ((std::rand() % 100) / 50.0f - 1.0f);

            // Add the particle to the simulation
            particles.emplace_back(x, y, vx, vy, config.radius, config.mass, config.type);
        }
    };

    // Generate small particles
    generateParticles(smallCount, smallParticle, temperature);

    // Generate big particles
    generateParticles(bigCount, bigParticle, temperature);
}



bool GasSimulation::isOverlapping(float x, float y, float radius) {
    for (const auto &particle : particles) {
        float dx = x - particle.getX();
        float dy = y - particle.getY();
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < radius + particle.getRadius()) {
            return true;
        }
    }
    return false;
}

void GasSimulation::keepWithinBorders(Particle &particle) {
    float x = particle.getX();
    float y = particle.getY();
    float radius = particle.getRadius();
    float vx = particle.getVX();
    float vy = particle.getVY();

    if (x - radius < 0) {
        x = radius;
        vx = std::abs(vx);
    }

    if (x + radius > width()) {
        x = width() - radius;
        vx = -std::abs(vx);
    }

    if (y - radius < 0) {
        y = radius;
        vy = std::abs(vy);
    }

    if (y + radius > height()) {
        y = height() - radius;
        vy = -std::abs(vy);
    }

    particle.setX(x);
    particle.setY(y);
    particle.setVX(vx);
    particle.setVY(vy);
}

void GasSimulation::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const auto &particle : particles) {
        particle.draw(painter);
    }
}

void GasSimulation::updatePositions() {
    for (auto &particle : particles) {
        particle.move(0.1f, width(), height());
        keepWithinBorders(particle);
    }

    // Check collisions between all pairs of particles
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            if (particles[i].collidesWith(particles[j])) {
                resolveCollision(particles[i], particles[j]);
            }
        }
    }

    update();
}

// Collision Resolution
void GasSimulation::resolveCollision(Particle &circle1, Particle &circle2) {
    // // Position difference
    // QPointF posDiffFirst = vectorSubtract(QPointF(circle1.getX(), circle1.getY()), QPointF(circle2.getX(), circle2.getY()));
    // QPointF posDiffSecond = vectorSubtract(QPointF(circle2.getX(), circle2.getY()), QPointF(circle1.getX(), circle1.getY()));

    // // Velocity vectors
    // QPointF velFirst(circle1.getVX(), circle1.getVY());
    // QPointF velSecond(circle2.getVX(), circle2.getVY());

    // // Velocity differences
    // QPointF velDiffFirst = vectorSubtract(velFirst, velSecond);
    // QPointF velDiffSecond = vectorSubtract(velSecond, velFirst);

    // // Calculate dot products of velocity and positions
    // double firstDot = dotProduct(velDiffFirst, posDiffFirst);
    // double secondDot = dotProduct(velDiffSecond, posDiffSecond);

    // // Calculate the squares of the norms
    // double firstSquare = posDiffFirst.x() * posDiffFirst.x() + posDiffFirst.y() * posDiffFirst.y();
    // double secondSquare = posDiffSecond.x() * posDiffSecond.x() + posDiffSecond.y() * posDiffSecond.y();

    // // Check if circles are already colliding
    // if (firstSquare == 0 || secondSquare == 0) return;

    // // Calculate new velocities
    // QPointF newFirstVel = velFirst - (firstDot / firstSquare) * posDiffFirst;
    // QPointF newSecondVel = velSecond - (secondDot / secondSquare) * posDiffSecond;

    // // Update velocity values in particles
    // circle1.setVX(newFirstVel.x());
    // circle1.setVY(newFirstVel.y());
    // circle2.setVX(newSecondVel.x());
    // circle2.setVY(newSecondVel.y());

    // Position difference
    QPointF posDiff = vectorSubtract(QPointF(circle1.getX(), circle1.getY()), QPointF(circle2.getX(), circle2.getY()));
    double distance = std::sqrt(posDiff.x() * posDiff.x() + posDiff.y() * posDiff.y());
    double minDist = circle1.getRadius() + circle2.getRadius();

    // Skip if the circles are not actually colliding
    if (distance >= minDist || distance == 0) return;

    // Calculate the normal unit vector
    QPointF normal(posDiff.x() / distance, posDiff.y() / distance);

    // Separate the circles if overlapping
    double overlap = 0.5 * (minDist - distance);
    circle1.setX(circle1.getX() + overlap * normal.x());
    circle1.setY(circle1.getY() + overlap * normal.y());
    circle2.setX(circle2.getX() - overlap * normal.x());
    circle2.setY(circle2.getY() - overlap * normal.y());

    // Velocity vectors
    QPointF vel1(circle1.getVX(), circle1.getVY());
    QPointF vel2(circle2.getVX(), circle2.getVY());

    // Calculate the relative velocity
    QPointF relVel = vectorSubtract(vel1, vel2);

    // Determine the relative velocity along the collision normal
    double velAlongNormal = dotProduct(relVel, normal);

    // If the circles are moving apart, skip
    if (velAlongNormal > 0) return;

    // Coefficient of restitution (elasticity)
    double restitution = 1.0;

    // Calculate the impulse scalar
    double impulseScalar = -(1 + restitution) * velAlongNormal / 2;

    // Calculate the impulse vector
    QPointF impulse(impulseScalar * normal.x(), impulseScalar * normal.y());

    // Apply impulse to the velocities of both particles
    circle1.setVX(vel1.x() + impulse.x());
    circle1.setVY(vel1.y() + impulse.y());
    circle2.setVX(vel2.x() - impulse.x());
    circle2.setVY(vel2.y() - impulse.y());
}

QPointF GasSimulation::vectorSubtract(const QPointF &vec1, const QPointF &vec2) const {
    return QPointF(vec1.x() - vec2.x(), vec1.y() - vec2.y());
}

double GasSimulation::dotProduct(const QPointF &vec1, const QPointF &vec2) const {
    return vec1.x() * vec2.x() + vec1.y() * vec2.y();
}

