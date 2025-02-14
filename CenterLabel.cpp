#include "CenterLabel.h"
#include <QResizeEvent>
#include <QPainter>

CenterLabel::CenterLabel(const QString &text, QWidget *parent) : QWidget(parent)
{
    label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: white; font-size: 24px; font-weight: bold;");
    setAttribute(Qt::WA_StyledBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void CenterLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.fillRect(rect(), QColor(0, 0, 0, 200)); // Semi-transparent black background
}


void CenterLabel::resizeEvent(QResizeEvent *event)
{
    // Manually center the label within the overlay
    if (label) {
        int labelWidth = label->sizeHint().width();
        int labelHeight = label->sizeHint().height();
        int centerX = (width() - labelWidth) / 2;
        int centerY = (height() - labelHeight) / 2;
        label->setGeometry(centerX, centerY, labelWidth, labelHeight);
    }
    QWidget::resizeEvent(event);
}

void CenterLabel::setText(const QString &text)
{
    label->setText(text);
}
