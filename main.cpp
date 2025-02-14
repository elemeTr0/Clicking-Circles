#include "mainwindow.h"
#include "circleGenerator.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setCursor(Qt::CrossCursor); // Set the cursor to a cross
    window.showFullScreen();

    return app.exec();
}
