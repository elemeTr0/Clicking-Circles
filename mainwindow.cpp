#include "mainwindow.h"
#include "circleGenerator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QDebug>
#include "starteroverlay.h"
#include <QTimer>
#include <QSettings> // Include QSettings

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), score(0)
{
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Top Bar Layout (Score, Timer, High Score)
    QHBoxLayout *topBarLayout = new QHBoxLayout();

    // Score Label (Top Left, Bigger Font)
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    scoreLabel->setAlignment(Qt::AlignLeft);
    topBarLayout->addWidget(scoreLabel);

    // Add Timer and High Score inside a Layout
    QVBoxLayout *timerHighScoreLayout = new QVBoxLayout();

    //Time Label
    timeLabel = new QLabel("60", this);
    timeLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    timeLabel->setAlignment(Qt::AlignCenter);

    //High Score Label
    highScoreLabel = new QLabel("High Score: 0", this);
    highScoreLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    highScoreLabel->setAlignment(Qt::AlignRight);

    timerHighScoreLayout->addWidget(highScoreLabel);
    timerHighScoreLayout->addWidget(timeLabel);

    topBarLayout->addLayout(timerHighScoreLayout);

    // Add stretch to push settings button to the right
    topBarLayout->addStretch();

    // Settings Button (Far Right)
    settingsButton = new QPushButton(this);
    settingsButton->setIcon(QIcon(":/icons/settings.png")); // Replace with your icon path
    settingsButton->setFixedSize(32, 32);
    settingsButton->setStyleSheet("border: none;");
    topBarLayout->addWidget(settingsButton);

    // Add the top bar layout to the main layout
    mainLayout->addLayout(topBarLayout);

    // Create overlay widget for "Click to Start"
    overlayWidget = new StartOverlay(this);
    overlayWidget->setGeometry(this->rect());
    overlayWidget->raise();
    overlayWidget->show();

    connect(overlayWidget, &StartOverlay::overlayClicked, this, &MainWindow::startCountdown);

    // Create and set up the CircleGenerator widget
    circleGenerator = new CircleGenerator(this);
    circleGenerator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //Expand the circle generator
    mainLayout->addWidget(circleGenerator);

    // Set central widget and layout
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Connect signals
    connect(circleGenerator, &CircleGenerator::circleClicked, this, &MainWindow::onCircleClicked);
    connect(circleGenerator, &CircleGenerator::emptyClicked, this, &MainWindow::onEmptyClicked);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettingsDialog);

    // Timer setup
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &MainWindow::countdownTick);

    loadHighscore();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateScore(int points)
{
    score = qMax(0, score + points);  // Ensure score doesn't go below 0
    scoreLabel->setText("Score: " + QString::number(score));
}

void MainWindow::onCircleClicked()
{
    if (isGameActive) {
        updateScore(10);  // Add 10 points when a circle is clicked
    }
}

void MainWindow::onEmptyClicked()
{
    if (isGameActive) {
        updateScore(-5);  // Subtract 5 points when empty space is clicked
    }
}

void MainWindow::startCountdown()
{
    overlayWidget->setLabelText("3");
    countdownValue = 3;
    countdownTimer->start(1000); // Tick every 1 second
    disconnect(overlayWidget, &StartOverlay::overlayClicked, this, &MainWindow::startCountdown);
}

void MainWindow::countdownTick()
{
    countdownValue--;
    if (countdownValue > 0) {
        overlayWidget->setLabelText(QString::number(countdownValue));
    } else {
        countdownTimer->stop();
        startGame(); // Actually start the game after countdown
    }
}

void MainWindow::startGame()
{
    if (overlayWidget) {  //Check to prevent nullptr access
        overlayWidget->close();
        overlayWidget->deleteLater(); // Schedule the overlay for deletion
        overlayWidget = nullptr;
    }
    gameTime = 60.0;
    score = 0;
    updateScore(0);
    isGameActive = true;
    gameTimer->start(100);  // Start the game with a 0.1 second interval
}

void MainWindow::updateGame()
{
    if (isGameActive) {
        gameTime -= 0.1; // Decrement game time
        if (gameTime <= 0) {
            gameTime = 0; // Prevent negative time
            isGameActive = false; // Stop the game
            gameTimer->stop(); // Stop the game timer
            saveHighscore();  // Save the high score
            close(); // Close the main window
        }
        timeLabel->setText(QString::number(gameTime, 'f', 0)); // Display with 0 decimal places
    }
}

void MainWindow::openSettingsDialog()
{
    // Create a dialog for settings
    QDialog dialog(this);
    dialog.setWindowTitle("Settings");

    QVBoxLayout *dialogLayout = new QVBoxLayout(&dialog);

    QLabel *sliderLabel = new QLabel("Mouse Sensitivity:", &dialog);
    dialogLayout->addWidget(sliderLabel);

    QSlider *sensitivitySlider = new QSlider(Qt::Horizontal, &dialog);
    sensitivitySlider->setRange(1, 100); // Sensitivity range from 1 to 100
    sensitivitySlider->setValue(50);     // Default value at 50
    dialogLayout->addWidget(sensitivitySlider);

    QPushButton *closeButton = new QPushButton("Close", &dialog);
    dialogLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec(); // Open the dialog modally
}

void MainWindow::saveHighscore()
{
    QSettings settings("YourCompany", "YourGame"); // Replace with your company and game name
    int currentHighScore = settings.value("highScore", 0).toInt();

    if (score > currentHighScore) {
        settings.setValue("highScore", score);
    }
}

void MainWindow::loadHighscore()
{
    QSettings settings("YourCompany", "YourGame");
    int highScore = settings.value("highScore", 0).toInt();
    highScoreLabel->setText("High Score: " + QString::number(highScore));
}
