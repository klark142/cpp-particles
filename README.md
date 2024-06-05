# Ideal Gas Simulation

## Overview

This project is a C++ Qt application that simulates an ideal gas. The user can configure the number of small particles, the number of big particles, and the temperature of the system. The simulation displays the particles colliding and moving within a defined area, demonstrating the principles of the ideal gas law.

## Features

- Configure the number of small and big particles.
- Adjust the temperature of the simulation.
- Visualize particles colliding and moving according to physical principles.
- Real-time updates of particle movements and collisions.

## Requirements

- Qt 5.15 or higher
- CMake 3.5 or higher
- C++11 or higher

## Installation

1. Clone the repository:

    ```sh
    git clone https://github.com/klark142/cpp-particles.git
    cd cpp-particles
    ```

2. Create a build directory:

    ```sh
    mkdir build
    cd build
    ```

3. Configure the project with CMake:

    ```sh
    cmake ..
    ```

4. Build the project:

    ```sh
    cmake --build .
    ```

## Usage

### Running the Application

1. **Navigate to the build directory:**

    ```sh
    cd path/to/your/folder/build
    ```

2. **Run the application:**

    On Windows:

    ```sh
    cpp-particles.exe
    ```

    On macOS:

    ```sh
    ./cpp-pparticles.app/Contents/MacOS/cpp-particles
    ```

    On Linux:

    ```sh
    ./cpp-particles
    ```

### Configuring the Simulation

1. **Set the number of particles and temperature:**

    - Use the input fields in the control panel to specify the number of small and big particles.
    - Adjust the temperature using the temperature slider or input field.

2. **Start the Simulation:**

    - Click the "Start Simulation" button to begin the simulation.
    - Observe the particles colliding and moving within the simulation area.

### Stopping the Simulation

- To stop the simulation, click the "Stop Simulation" button. You can adjust the parameters and start the simulation again if needed.

By following these steps, you will be able to build and run the ideal gas simulation application, configure the simulation parameters, and observe the particles in motion.
