#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer> // Include QTimer
#include "circleGenerator.h"
#include "starteroverlay.h"
#include "Timer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCircleClicked();
    void onEmptyClicked();
    void startGame();
    void updateGame(); // New slot for timer updates
    void startCountdown(); // New slot for countdown start
    void countdownTick(); // New slot for countdown tick
    void Accuracy(int hits, int clicks);
private:
    Ui::MainWindow *ui; // Declare the ui pointer
    CircleGenerator *circleGenerator;
    QLabel *scoreLabel;
    QLabel *highScoreLabel; // New label for displaying high score
    StartOverlay *overlayWidget; // Overlay widget for "Click to Start"
    int score;
    int clicks;
    int hits;
    Timer *timer;
    QTimer *gameTimer; // Timer for the game
    double gameTime = 60; // Time elapsed during the game
    bool isGameActive;
    QTimer *countdownTimer; // Timer for the countdown
    int countdownValue; // value to count down from
    QLabel *timeLabel;
    QLabel *accuracyLabel;

    void updateScore(int points);

    void saveHighscore();
    void loadHighscore();
};

#endif // MAINWINDOW_H
