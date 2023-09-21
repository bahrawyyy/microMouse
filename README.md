# Micromouse README

## Table of Contents

1. [Introduction](#introduction)
2. [Prerequisites](#prerequisites)
3. [Getting Started](#getting-started)
   - [Simulation Version](#simulation-version)
   - [Hardware Integration Version](#hardware-integration-version)
4. [Meet the Team](#meet-the-team)

## Introduction

The Micromouse robot is a small autonomous robot designed to navigate a maze. This README covers two versions of the project:

1. **Simulation Version:** This version is designed to work with the MMS (Micromouse Simulator) written in C++. It allows you to develop and test your Micromouse algorithms in a simulated maze environment before deploying them to actual hardware.

2. **Hardware Integration Version:** This version includes instructions for integrating your Micromouse algorithm with real hardware, such as sensors, motors, and a physical maze.

## Prerequisites

Before you begin, make sure you have the following prerequisites in place:

### For the Simulation Version:

- **C++ Compiler:** You need a C++ compiler installed on your system.
- **MMS Simulator:** Download and install the Micromouse Simulator (MMS) for your platform. You can find the MMS repository and installation instructions [here](https://github.com/micromouseonline/micromouse-simulator).

### For the Hardware Integration Version:

- **Micromouse Hardware:** You'll need a Micromouse robot with sensors (e.g., ultrasonic or infrared or tof), motors, encoders, mpu6050 and a microcontroller (e.g., esp32 or Raspberry Pi).
- **Development Environment:** Set up the development environment for your microcontroller platform.
- **Micromouse Maze:** Prepare a physical maze for testing your hardware-integrated Micromouse.

## Getting Started

### Simulation Version

1. Clone or download the simulation version of the Micromouse project from the repository.

2. Build the project using your C++ compiler. Typically, you can use the following command:

   ```shell
   g++ Code.cpp API.cpp -o micromouse_simulator
3. Follow the instuctions [here](https://github.com/mackorone/mms).

### Hardware Integration Version

1- Clone or download the hardware integration version of the Micromouse project from the repository.

2- Follow the hardware setup instructions provided in [Project documentation](https://github.com/bahrawyyy/microMouse/blob/main/Algorithm%20Integration/hardware_setup.md) to connect sensors, motors, and other hardware components to your microcontroller.

3- Build and upload the project code to your microcontroller using the appropriate development environment (e.g., Arduino IDE, Raspberry Pi development tools).

4- Place your hardware-integrated Micromouse in a physical maze.

5- Run the Micromouse code on your hardware and observe its performance in navigating the maze.


## Meet the Team

This Micromouse Robot project was developed by a dedicated team of individuals passionate about robotics and engineering. Meet the team members:

- [**Mahmoud Samy**](https://github.com/MahmoudSamy511)

- [**Abdallah Almasry**](https://github.com/AbdullahElmasry)

- [**Mohamed Aref**](https://github.com/MuhammedAreff)

- [**Abdalla Elbahrawy**](https://github.com/bahrawyyy)

Each team member contributed their unique skills and expertise to make this project a reality. Feel free to explore their GitHub profiles to learn more about their work and interests.


