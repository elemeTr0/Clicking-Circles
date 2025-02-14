#ifndef STARTOVERLAY_H
#define STARTOVERLAY_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QResizeEvent>
#include <QShowEvent>

class StartOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit StartOverlay(QWidget *parent = nullptr);

signals:
    void overlayClicked();

public slots:
    void setLabelText(const QString &text);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    QLabel *startLabel;
};

#endif // STARTOVERLAY_H
