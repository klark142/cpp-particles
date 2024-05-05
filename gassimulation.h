#ifndef GASSIMULATION_H
#define GASSIMULATION_H

#include <QWidget>
#include "particle.h"
#include <QPushButton>

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
    std::vector<Particle> particles;
    void updatePositions();
    void keepWithinBorders(Particle &particle);
    bool isOverlapping(float x, float y, float radius);
};

#endif // GASSIMULATION_H
