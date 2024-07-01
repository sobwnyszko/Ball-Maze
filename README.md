Ball Maze
Introduction
"Ball Maze" is an interactive application written in Qt that simulates the movement of a ball in a maze. The movement of the ball is controlled by data read from a board with an accelerometer, allowing dynamic and interactive control based on the input data.

Project Purpose
The purpose of this project is to create an interactive game where the user can control the movement of the ball in the maze using data read from an accelerometer. The project aims to:

Demonstrate the interaction between software and hardware.
Develop programming skills in Qt.
Provide fun and education through creating this game.
Features
Accelerometer Data Reading: The application reads data from a connected board with an accelerometer, which is used to control the movement of the ball.
Ball Movement: An algorithm processes the input data and moves the ball in the maze accordingly (the movement is implemented in two ways).
User Interface: An intuitive user interface allows easy tracking of the ball's movement.
Real-Time Graphics: The application displays current accelerometer data on graphs in three axes (X, Y, Z).
How It Works
The application works based on the following steps:

Data Reading: The application reads data from the board with the accelerometer, providing information about its position.
Data Processing: The read data is processed by an algorithm that determines the direction and speed of the ball's movement.
Ball Movement: Based on the processed data, the ball is moved in the maze.
Interface and Graph Updates: The user interface and graphs are updated in real-time to reflect the current position of the ball and the accelerometer data.
