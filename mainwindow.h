#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QTimer>  // Include QTimer
#include "circleGenerator.h"
#include "starteroverlay.h"
#include "Timer.h"

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
    void openSettingsDialog();
    void updateGame(); // New slot for timer updates
    void startCountdown(); // New slot for countdown start
    void countdownTick();    // New slot for countdown tick

private:
    CircleGenerator *circleGenerator;
    QLabel *scoreLabel;
    QLabel *highScoreLabel; // New label for displaying high score
    QPushButton *settingsButton;
    StartOverlay *overlayWidget; // Overlay widget for "Click to Start"
    int score;
    Timer *timer;
    QTimer *gameTimer;    // Timer for the game
    double gameTime = 60;   // Time elapsed during the game
    bool isGameActive;
    QTimer *countdownTimer; // Timer for the countdown
    int countdownValue; // value to count down from
    QLabel *timeLabel;

    void updateScore(int points);
    void saveHighscore();
    void loadHighscore();
};

#endif // MAINWINDOW_H
