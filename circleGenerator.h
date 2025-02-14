#ifndef CIRCLEGENERATOR_H
#define CIRCLEGENERATOR_H

#include <QWidget>

struct Circle {
    int x;
    int y;
};

class CircleGenerator : public QWidget
{
    Q_OBJECT

public:
    explicit CircleGenerator(QWidget *parent = nullptr);

signals:
    void circleClicked();
    void emptyClicked();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    QColor circleColor = QColor(0, 255, 255); // CYAN
    QVector<Circle> circles;
    int radius = 30;

    void generateCircles();
    void regenerateCircle(int index);
};

#endif // CIRCLEGENERATOR_H
