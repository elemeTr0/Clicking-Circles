#include "starteroverlay.h"
#include <QPainter>

StartOverlay::StartOverlay(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: rgba(0, 0, 0, 200);"); // Semi-transparent black background

    startLabel = new QLabel("Click to Start", this);
    startLabel->setStyleSheet("color: white; font-size: 24px; font-weight: bold; background-color: transparent");
    startLabel->setAlignment(Qt::AlignCenter);

    setAttribute(Qt::WA_StyledBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);

    if (parentWidget()) {
        setGeometry(parentWidget()->rect());
    }
}

void StartOverlay::mousePressEvent(QMouseEvent *event)
{
    emit overlayClicked();
}

void StartOverlay::resizeEvent(QResizeEvent *event)
{
    if (parentWidget()) {
        setGeometry(parentWidget()->rect());
    }

    if (startLabel) {
        int labelWidth = startLabel->sizeHint().width();
        int labelHeight = startLabel->sizeHint().height();
        int centerX = (width() - labelWidth) / 2;
        int centerY = (height() - labelHeight) / 2;
        startLabel->setGeometry(centerX, centerY, labelWidth, labelHeight);
    }
    QWidget::resizeEvent(event);
}

void StartOverlay::showEvent(QShowEvent *event)
{
    raise();
    QWidget::showEvent(event);
}

void StartOverlay::setLabelText(const QString &text)
{
    startLabel->setText(text);
    update();
}
