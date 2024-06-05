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

ParticleDrawingWidget::ParticleDrawingWidget(const std::vector<Particle>& particles, QWidget *parent)
    : particles(particles), QWidget(parent) {
    setMinimumSize(600, 400);  // Set a minimum size for the drawing area
}

void ParticleDrawingWidget::setParticles(const std::vector<Particle> &particles) {
    this->particles = particles;
    update();
}

void ParticleDrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const auto &particle : particles) {
        particle.draw(painter);
    }
}

GasSimulation::GasSimulation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GasSimulation)
{
    ui->setupUi(this);
    setMinimumSize(800, 600);

    // Initialize and configure the timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GasSimulation::updatePositions);

    // Create the stop button
    QPushButton *stopButton = findChild<QPushButton*>("stopSimulationButton");
    // this->stopButton = stopButton;
    if (stopButton) {
        connect(stopButton, &QPushButton::clicked, this, &GasSimulation::stop);
    } else {
        qDebug() << "Stop button not found!";
    }

    // Create the drawing widget and layout
    drawingWidget = new ParticleDrawingWidget(particles, this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(drawingWidget);
    layout->addWidget(stopButton, 0, Qt::AlignBottom);
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

    const ParticleConfig smallParticle = {5.0f, 1.0f, ParticleType::Small};
    const ParticleConfig bigParticle = {15.0f, 3.0f, ParticleType::Big};

    auto generateParticles = [this](int count, const ParticleConfig& config, float temperature) {
        float baseSpeed = std::sqrt(temperature / config.mass);
        for (int i = 0; i < count; ++i) {
            float x, y, vx, vy;
            int maxAttempts = 100;
            bool overlapping = true;

            while (overlapping && maxAttempts-- > 0) {
                x = std::rand() % width();
                y = std::rand() % height();

                if (!isOverlapping(x, y, config.radius)) {
                    overlapping = false;
                }
            }

            if (overlapping) {
                qDebug() << "Skipping particle due to too many overlapping attempts.";
                continue;
            }

            vx = baseSpeed * ((std::rand() % 100) / 50.0f - 1.0f);
            vy = baseSpeed * ((std::rand() % 100) / 50.0f - 1.0f);

            particles.emplace_back(x, y, vx, vy, config.radius, config.mass, config.type);
        }
    };

    generateParticles(smallCount, smallParticle, temperature);
    generateParticles(bigCount, bigParticle, temperature);

    // drawingWidget->setParticles(particles);
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

    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            if (particles[i].collidesWith(particles[j])) {
                resolveCollision(particles[i], particles[j]);
            }
        }
    }

    // drawingWidget->setParticles(particles);
    update();
}

// Collision Resolution
void GasSimulation::resolveCollision(Particle &circle1, Particle &circle2) {
    // Calculate the difference in positions
    float dx = circle2.getX() - circle1.getX();
    float dy = circle2.getY() - circle1.getY();

    // Calculate the distance between the particles
    float distance = std::sqrt(dx * dx + dy * dy);

    // Calculate the normal and tangent vectors
    float nx = dx / distance;
    float ny = dy / distance;
    float tx = -ny;
    float ty = nx;

    // Calculate the dot products of the velocity vectors with the normal and tangent vectors
    float dpTan1 = circle1.getVX() * tx + circle1.getVY() * ty;
    float dpTan2 = circle2.getVX() * tx + circle2.getVY() * ty;

    float dpNorm1 = circle1.getVX() * nx + circle1.getVY() * ny;
    float dpNorm2 = circle2.getVX() * nx + circle2.getVY() * ny;

    // Calculate the new normal velocities using the 1D elastic collision equations
    float m1 = (dpNorm1 * (circle1.getMass() - circle2.getMass()) + 2.0f * circle2.getMass() * dpNorm2) / (circle1.getMass() + circle2.getMass());
    float m2 = (dpNorm2 * (circle2.getMass() - circle1.getMass()) + 2.0f * circle1.getMass() * dpNorm1) / (circle1.getMass() + circle2.getMass());

    // Update the velocities of the particles
    circle1.setVX(tx * dpTan1 + nx * m1);
    circle1.setVY(ty * dpTan1 + ny * m1);
    circle2.setVX(tx * dpTan2 + nx * m2);
    circle2.setVY(ty * dpTan2 + ny * m2);

}

QPointF GasSimulation::vectorSubtract(const QPointF &vec1, const QPointF &vec2) const {
    return QPointF(vec1.x() - vec2.x(), vec1.y() - vec2.y());
}

double GasSimulation::dotProduct(const QPointF &vec1, const QPointF &vec2) const {
    return vec1.x() * vec2.x() + vec2.y() * vec2.y();
}
