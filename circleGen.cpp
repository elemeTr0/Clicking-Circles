#include "circleGenerator.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QResizeEvent>
#include <QShowEvent>

CircleGenerator::CircleGenerator(QWidget *parent)
    : QWidget(parent)
{
    // Circles will be generated in showEvent
}

void CircleGenerator::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(circleColor);

    for (const Circle &circle : circles) {
        painter.drawEllipse(circle.x - radius, circle.y - radius, 2 * radius, 2 * radius);
    }
}

void CircleGenerator::mousePressEvent(QMouseEvent *event)
{
    bool clickedOnCircle = false;
    for (int i = 0; i < circles.size(); ++i) {
        const Circle &circle = circles[i];
        int dx = event->x() - circle.x;
        int dy = event->y() - circle.y;
        if (dx * dx + dy * dy <= radius * radius) {
            regenerateCircle(i);
            emit circleClicked();
            clickedOnCircle = true;
            update();
            break;
        }
    }

    if (!clickedOnCircle) {
        emit emptyClicked();
    }
}

void CircleGenerator::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    generateCircles();
}

void CircleGenerator::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    generateCircles();
}

void CircleGenerator::generateCircles()
{
    circles.clear();
    for (int i = 0; i < 3; ++i) {
        regenerateCircle(i);
    }
    update();
}

void CircleGenerator::regenerateCircle(int index)
{
    if (width() <= 2 * radius || height() <= 2 * radius) {
        qDebug() << "Error: Widget size is too small to generate circles.";
        return;
    }

    Circle newCircle;
    newCircle.x = QRandomGenerator::global()->bounded(radius, width() - radius);
    newCircle.y = QRandomGenerator::global()->bounded(radius, height() - radius);

    if (index >= 0 && index < circles.size()) {
        circles[index] = newCircle;
    } else {
        circles.append(newCircle);
    }
}
