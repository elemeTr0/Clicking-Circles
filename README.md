# Circle Click Trainer (Qt Creator)

A Qt-based application for training aiming skills, similar to Aimlabs.

## Overview

This project is a circle-clicking trainer application developed using the Qt framework and C++. It's designed to help users improve their aim and reaction time by clicking randomly appearing circles.

## Features

*   Random circle generation
*   Timer-based gameplay
*   Score tracking

## Technologies Used

*   C++
*   Qt Framework
*   Qt Designer (for UI design)

## Prerequisites

*   Qt Creator (version 6.8.2 or later, based on your build directory)
*   A C++ compiler compatible with Qt (e.g., MinGW)

## Building and Running the Application

1.  Clone the repository:

    ```
    git clone <your-repository-url>
    ```

2.  Open the `aimlabs.pro` file in Qt Creator.
3.  Configure the project build settings (if necessary) to use a compatible compiler.
4.  Build the project (typically by pressing Ctrl+B or Cmd+B).
5.  Run the executable located in the build directory (e.g., `build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/aimlabs.exe` or similar).  The executable name will likely be based on the project name (`aimlabs.pro`).

## How to Play

1.  Run the application.
2.  Circles will appear randomly on the screen.
3.  Click on the circles as quickly and accurately as possible.
4.  Your score and time left will be displayed.

## Project Structure

*   `main.cpp`: Contains the main function and application entry point.
*   `mainwindow.h`: Header file for the `MainWindow` class, which manages the main application window and game logic.
*   `mainwindow.cpp`: Implementation file for the `MainWindow` class.
*   `mainwindow.ui`: UI design file created with Qt Designer, defining the layout of the main window.
*   `circleGen.h`: Header file for the `CircleGenerator` class (or similar), responsible for generating random circles.
*   `circleGen.cpp`: Implementation file for the `CircleGenerator` class.
*   `CenterLabel.h`: Header file for a custom label class (likely used for displaying scores or other information).  *Describe its purpose more accurately if you know what it does.*
*   `CenterLabel.cpp`: Implementation file for the `CenterLabel` class.
*   `Timer.h`: Header file for a custom timer class (likely used for game timing). *Describe its purpose more accurately if you know what it does.*
*   `Timer.cpp`: Implementation file for the `Timer` class.
*   `starteroverlay.h`: Header file for a starting overlay. *Describe its purpose more accurately if you know what it does.*
*   `starteroverlay.cpp`: Implementation file for the starting overlay.
*   `aimlabs.pro`: Qt project file, containing project settings and dependencies.
*   `aimlabs.pro.user`: User-specific settings for the Qt project (usually ignored by Git).

## Future Enhancements

*   Accuracy calculation
*   Implement different game modes (e.g., timed mode, endless mode).
*   Improve the UI with better graphics and animations.
*   Add sound effects.
*   Implement user profiles to save settings and track progress.

## Author

*   Mateo/elemeTr0

## License

No License
