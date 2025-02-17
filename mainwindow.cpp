#include "mainwindow.h"
#include "circleGenerator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <circleGenerator.h>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), score(0)
{
    hits=0;
    clicks=0;
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0); //Remove the margins

    // Top Bar Layout (Score, Timer, High Score)
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    topBarLayout->setContentsMargins(0, 0, 0, 0); //Remove the margins

    // Score Label (Top Left, Bigger Font)
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;"); // Set the font color to white
    scoreLabel->setAlignment(Qt::AlignLeft);
    topBarLayout->addWidget(scoreLabel);

    // Accuracy Label
    accuracyLabel = new QLabel("Accuracy: ", this);
    accuracyLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white; maring-right:60px"); // Set the font color to white
    accuracyLabel->setAlignment(Qt::AlignLeft);
    topBarLayout->addWidget(accuracyLabel);

    //Time Label
    timeLabel = new QLabel("60", this);
    timeLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;"); // Set the font color to white
    timeLabel->setAlignment(Qt::AlignLeft);
    topBarLayout->addWidget(timeLabel);

    //High Score Label
    highScoreLabel = new QLabel("High Score: 0", this);
    highScoreLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: white;"); // Set the font color to white
    highScoreLabel->setAlignment(Qt::AlignRight);
    topBarLayout->addWidget(highScoreLabel);

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
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect signals
    connect(circleGenerator, &CircleGenerator::circleClicked, this, &MainWindow::onCircleClicked);
    connect(circleGenerator, &CircleGenerator::emptyClicked, this, &MainWindow::onEmptyClicked);

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
    score = qMax(0, score + points); // Ensure score doesn't go below 0
    scoreLabel->setText("Score: " + QString::number(score));
    Accuracy(hits,clicks);
}

void MainWindow::onCircleClicked()
{
    if (isGameActive) {
        updateScore(10); // Add 10 points when a circle is clicked
        hits++;
        clicks++;
        Accuracy(hits,clicks);
    }
}

void MainWindow::onEmptyClicked()
{
    if (isGameActive) {
        updateScore(-5); // Subtract 5 points when empty space is clicked
        clicks++;
        Accuracy(hits,clicks);
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
    if (overlayWidget) { //Check to prevent nullptr access
        overlayWidget->close();
        overlayWidget->deleteLater(); // Schedule the overlay for deletion
        overlayWidget = nullptr;
    }
    gameTime = 60.0;
    score = 0;
    updateScore(0);
    isGameActive = true;
    gameTimer->start(100); // Start the game with a 0.1 second interval
}

void MainWindow::updateGame()
{
    if (isGameActive) {
        gameTime -= 0.1; // Decrement game time
        if (gameTime <= 0) {
            gameTime = 0; // Prevent negative time
            isGameActive = false; // Stop the game
            gameTimer->stop(); // Stop the game timer
            saveHighscore(); // Save the high score
            close(); // Close the main window. Consider a game over dialog instead.
        }
        timeLabel->setText(QString::number(gameTime, 'f', 0)); // Display with 0 decimal places
    }
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

void MainWindow::Accuracy(int hits, int clicks)
{
    double accuracy = 0.0; // Initialize to a default value
    if (clicks > 0) { // Prevent division by zero
        accuracy = 100.0 * (double)hits / (double)clicks; // Calculate accuracy as a percentage
    }
    accuracyLabel->setText("Accuracy: " + QString::number(accuracy, 'f', 2) + "%"); // Set label text, limit to 2 decimal places
}
