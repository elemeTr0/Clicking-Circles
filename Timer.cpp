#include "Timer.h"
#include <QVBoxLayout>

Timer::Timer(QWidget *parent)
    : QWidget(parent)
{
    timerLabel = new CenterLabel("60", this); // Initialize the timer label with 60
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(timerLabel);
    setLayout(layout);
}

Timer::~Timer()
{
}

void Timer::setText(const QString &text)
{
    timerLabel->setText(text);
}
