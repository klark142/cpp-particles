#ifndef GASCONTAINER_H
#define GASCONTAINER_H

#include <QWidget>
#include <QStackedWidget>
#include "controlpanel.h"
#include "gassimulation.h"

class GasContainer : public QWidget {
    Q_OBJECT

public:
    explicit GasContainer(QWidget *parent = nullptr);

private slots:
    void startSimulation();
    void stopSimulation();

private:
    QStackedWidget *stackedWidget;
    ControlPanel *controlPanel;
    GasSimulation *simulationPanel;
};

#endif // GASCONTAINER_H
