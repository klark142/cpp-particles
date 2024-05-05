/********************************************************************************
** Form generated from reading UI file 'controlpanel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanel
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *temperatureInput;
    QLabel *label_2;
    QSpinBox *bigParticleCountInput;
    QLabel *label_3;
    QSpinBox *smallParticleCountInput;
    QPushButton *startButton;

    void setupUi(QWidget *ControlPanel)
    {
        if (ControlPanel->objectName().isEmpty())
            ControlPanel->setObjectName("ControlPanel");
        ControlPanel->resize(871, 456);
        verticalLayout_2 = new QVBoxLayout(ControlPanel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(ControlPanel);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        temperatureInput = new QSpinBox(ControlPanel);
        temperatureInput->setObjectName("temperatureInput");
        temperatureInput->setMinimum(1);
        temperatureInput->setMaximum(1500);
        temperatureInput->setSingleStep(50);
        temperatureInput->setValue(300);

        verticalLayout->addWidget(temperatureInput);

        label_2 = new QLabel(ControlPanel);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        bigParticleCountInput = new QSpinBox(ControlPanel);
        bigParticleCountInput->setObjectName("bigParticleCountInput");
        bigParticleCountInput->setMinimum(5);
        bigParticleCountInput->setMaximum(500);
        bigParticleCountInput->setSingleStep(5);
        bigParticleCountInput->setValue(20);

        verticalLayout->addWidget(bigParticleCountInput);

        label_3 = new QLabel(ControlPanel);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        smallParticleCountInput = new QSpinBox(ControlPanel);
        smallParticleCountInput->setObjectName("smallParticleCountInput");
        smallParticleCountInput->setMinimum(5);
        smallParticleCountInput->setMaximum(500);
        smallParticleCountInput->setSingleStep(5);
        smallParticleCountInput->setValue(20);

        verticalLayout->addWidget(smallParticleCountInput);

        startButton = new QPushButton(ControlPanel);
        startButton->setObjectName("startButton");

        verticalLayout->addWidget(startButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ControlPanel);

        QMetaObject::connectSlotsByName(ControlPanel);
    } // setupUi

    void retranslateUi(QWidget *ControlPanel)
    {
        ControlPanel->setWindowTitle(QCoreApplication::translate("ControlPanel", "Form", nullptr));
        label->setText(QCoreApplication::translate("ControlPanel", "<html><head/><body><p><span style=\" font-size:18pt;\">Set the temperature</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("ControlPanel", "<html><head/><body><p><span style=\" font-size:18pt;\">Set the amount of big particles</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("ControlPanel", "<html><head/><body><p><span style=\" font-size:18pt;\">Set the amount of small particles</span></p></body></html>", nullptr));
        startButton->setText(QCoreApplication::translate("ControlPanel", "Start simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlPanel: public Ui_ControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
