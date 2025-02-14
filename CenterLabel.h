#ifndef CENTERLABEL_H
#define CENTERLABEL_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>
#include <QPainter>

class CenterLabel : public QWidget
{
    Q_OBJECT
public:
    CenterLabel(const QString &text, QWidget *parent = nullptr);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *label;
};

#endif // CENTERLABEL_H
