#include "gascontainer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QSpinBox>

#include "gascontainer.h"

GasContainer::GasContainer(QWidget *parent) : QWidget(parent) {
    controlPanel = new ControlPanel(this);
    simulationPanel = new GasSimulation(this);

    connect(controlPanel->findChild<QPushButton *>("startButton"), &QPushButton::clicked, this, &GasContainer::startSimulation);
    connect(simulationPanel, &GasSimulation::stopRequested, this, &GasContainer::stopSimulation);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(controlPanel);
    stackedWidget->addWidget(simulationPanel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void GasContainer::startSimulation() {
    int temperature = controlPanel->findChild<QSpinBox *>("temperatureInput")->value();
    int numBigParticles = controlPanel->findChild<QSpinBox *>("bigParticleCountInput")->value();
    int numSmallParticles = controlPanel->findChild<QSpinBox *>("smallParticleCountInput")->value();

    simulationPanel->initializeParticles(numBigParticles, numSmallParticles, temperature);
    simulationPanel->start();

    stackedWidget->setCurrentIndex(1);
}

void GasContainer::stopSimulation() {
    stackedWidget->setCurrentIndex(0);
}


