# Lab 4: Admittance Control

This repository contains code and data related to Lab 4 on Admittance Control. The project involves both Arduino for real-time control and MATLAB for data analysis and calibration.

## Folder Structure

- `Lab 4_Admittance Control.pdf`: The lab assignment document.
- `code/`: Contains the source code for the project.
    - `arduino/`: Arduino sketches for implementing admittance control on a microcontroller.
        - `main.ino`: The main Arduino program that orchestrates the control loop, reads sensors, controls motors, and handles serial communication.
        - `load_cell.ino`: Likely contains functions related to reading data from the load cell.
        - `motor.ino`: Likely contains functions for controlling the motor.
        - `reference_generator.ino`: Likely contains functions for generating reference signals for the control system.
        - `user_interface.ino`: Likely contains functions for handling user input via serial interface.
    - `matlab/`: MATLAB scripts for data analysis, calibration, and plotting.
        - `lab4.m`: The primary MATLAB script for force sensor calibration and analysis of admittance control trial data.
- `data/`: Stores experimental data.
    - `ForceHumana.txt`: Data file used by the MATLAB script.

## Basic Execution

### Arduino
The Arduino code is responsible for the real-time control system.

1.  **Open in Arduino IDE**: Open the `code/arduino/main.ino` file (or the entire `arduino` folder) in the Arduino IDE.
2.  **Upload to Board**: Connect your Arduino board and upload the `main.ino` sketch. Ensure all `.ino` files in the `arduino` directory are part of the same sketch.
3.  **Serial Monitor Interaction**: The `user_interface.ino` and `CheckKeyboard()` in `main.ino` suggest that there might be a serial menu for interacting with the control system. Use the Arduino IDE's Serial Monitor (or a similar tool) to send commands and observe output.

### MATLAB
The MATLAB script `lab4.m` is used for data processing and visualization.

1.  **Open in MATLAB**: Open `code/matlab/lab4.m` in MATLAB.
2.  **Run Script**: Run the script. It will perform:
    *   **Force Sensor Calibration**: Calculates calibration coefficients for the force sensor using `ForceHumana.txt` or similar data.
    *   **Trial Data Analysis**: Reads and processes trial data, likely from `data/ForceHumana.txt`, to analyze the admittance control performance, plotting desired vs. motor positions.

To run the MATLAB script, ensure the `data/ForceHumana.txt` file is accessible relative to the `lab4.m` script, or modify the `filename` variable in `lab4.m` to the correct path.
