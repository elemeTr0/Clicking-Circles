#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include "CenterLabel.h" // Include the CenterLabel header

class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = nullptr);
    ~Timer() override;

    void setText(const QString &text);

protected:
    CenterLabel *timerLabel; // Use CenterLabel instead of QLabel
};

#endif // TIMER_H
