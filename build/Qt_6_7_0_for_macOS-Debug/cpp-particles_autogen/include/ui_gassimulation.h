/********************************************************************************
** Form generated from reading UI file 'gassimulation.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GASSIMULATION_H
#define UI_GASSIMULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GasSimulation
{
public:
    QPushButton *stopSimulationButton;

    void setupUi(QWidget *GasSimulation)
    {
        if (GasSimulation->objectName().isEmpty())
            GasSimulation->setObjectName("GasSimulation");
        GasSimulation->resize(659, 454);
        stopSimulationButton = new QPushButton(GasSimulation);
        stopSimulationButton->setObjectName("stopSimulationButton");
        stopSimulationButton->setGeometry(QRect(12, 213, 123, 32));

        retranslateUi(GasSimulation);

        QMetaObject::connectSlotsByName(GasSimulation);
    } // setupUi

    void retranslateUi(QWidget *GasSimulation)
    {
        GasSimulation->setWindowTitle(QCoreApplication::translate("GasSimulation", "Form", nullptr));
        stopSimulationButton->setText(QCoreApplication::translate("GasSimulation", "Stop simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GasSimulation: public Ui_GasSimulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GASSIMULATION_H
