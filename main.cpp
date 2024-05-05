#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include "gascontainer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;
    GasContainer container;
    window.setCentralWidget(&container);
    window.resize(800, 600);
    window.show();
    return app.exec();
}
