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

## Mathematical basis for the simulation
### Temperature and initial velocities
The temperature of the gas, 𝑇, in Kelvin affects the average kinetic energy of the particles. According to the kinetic theory of gases, the average kinetic energy ⟨𝐸𝑘⟩ of a particle is given by:

⟨𝐸𝑘⟩ = (3/2) 𝑘𝐵𝑇

where 𝑘𝐵 is the Boltzmann constant. The velocities of the particles are initialized to reflect this average kinetic energy, with higher temperatures resulting in higher velocities.

### Collision Detection
Collisions between particles are detected by checking the distance between their centers. If the distance is less than the sum of their radii, a collision is detected.

### Collision Resolution
When two particles collide, their positions and velocities are used to calculate the outcomes. The collision resolution process involves:

#### Relative Position and Distance:
The difference in positions of the two particles is used to calculate the distance between them. This distance is essential in determining if a collision has occurred and in what direction the collision forces will act.

#### Normal and Tangent Vectors:
The normal vector (𝑛) is calculated along the line connecting the centers of the two particles, while the tangent vector (𝑡) is perpendicular to it. These vectors help in decomposing the velocities into components parallel and perpendicular to the collision axis.

#### Velocity Decomposition:
The velocities of the particles are decomposed into components along the normal and tangent vectors. This allows the calculation of the effect of the collision in one-dimensional terms along the collision axis, simplifying the math involved.

#### Elastic Collision Equations:
The equations for one-dimensional elastic collisions are used to compute the new velocities of the particles along the normal direction. These equations ensure that both momentum and kinetic energy are conserved during the collision.

#### Recomposing Velocities:
Finally, the new normal velocities are combined with the unchanged tangent velocities to update the overall velocities of the particles after the collision.

By using these mathematical principles, the simulation ensures realistic behavior of particles during collisions, maintaining the physical laws of conservation of momentum and energy.
