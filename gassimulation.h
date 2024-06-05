// #ifndef GASSIMULATION_H
// #define GASSIMULATION_H

// #include <QWidget>
// #include "particle.h"
// #include <QPushButton>

// class ParticleDrawingWidget : public QWidget {
//     Q_OBJECT

// public:
//     explicit ParticleDrawingWidget(QWidget *parent = nullptr);

// protected:
//     void paintEvent(QPaintEvent *event) override;
// };


// namespace Ui {
// class GasSimulation;
// }

// class GasSimulation : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit GasSimulation(QWidget *parent = nullptr);
//     ~GasSimulation();
//     void start();
//     void stop();
//     void initializeParticles(int bigCount, int smallCount, float temperature);

//     void resolveCollision(Particle &particle1, Particle &particle2);
//     QPointF vectorSubtract(const QPointF &vec1, const QPointF &vec2) const;
//     double dotProduct(const QPointF &vec1, const QPointF &vec2) const;

// protected:
//     void paintEvent(QPaintEvent *event) override;

// signals:
//     void stopRequested();

// private:
//     Ui::GasSimulation *ui;
//     QTimer *timer;
//     QPushButton *stopButton;
//     std::vector<Particle> particles;
//     void updatePositions();
//     void keepWithinBorders(Particle &particle);
//     bool isOverlapping(float x, float y, float radius);
// };

// #endif // GASSIMULATION_H

#ifndef GASSIMULATION_H
#define GASSIMULATION_H

#include <QWidget>
#include "particle.h"
#include <QPushButton>
#include <vector>

class ParticleDrawingWidget : public QWidget {
    Q_OBJECT

public:
    explicit ParticleDrawingWidget(const std::vector<Particle>& particles, QWidget *parent = nullptr);
    void setParticles(const std::vector<Particle> &particles);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<Particle> particles;
};


namespace Ui {
class GasSimulation;
}

class GasSimulation : public QWidget
{
    Q_OBJECT

public:
    explicit GasSimulation(QWidget *parent = nullptr);
    ~GasSimulation();
    void start();
    void stop();
    void initializeParticles(int bigCount, int smallCount, float temperature);

    void resolveCollision(Particle &particle1, Particle &particle2);
    QPointF vectorSubtract(const QPointF &vec1, const QPointF &vec2) const;
    double dotProduct(const QPointF &vec1, const QPointF &vec2) const;

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void stopRequested();

private:
    Ui::GasSimulation *ui;
    QTimer *timer;
    QPushButton *stopButton;
    ParticleDrawingWidget *drawingWidget;
    std::vector<Particle> particles;
    void updatePositions();
    void keepWithinBorders(Particle &particle);
    bool isOverlapping(float x, float y, float radius);
};

#endif // GASSIMULATION_H

