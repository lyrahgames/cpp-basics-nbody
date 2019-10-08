# C++ Basics: N-Body Simulation in Two Dimensions

## Get the Code and Start Developing

    mkdir cpp-basics
    cd cpp-basics
    git clone https://github.com/lyrahgames/cpp-basics-nbody.git nbody
    cd nbody

**Fast Building:**
In-source build without persistent configuration:
    
    # Build the executable with ad-hoc configuration and compiler flags.
    b config.cxx=clang++ "config.cxx.coptions=-O3 -march=native"
    # Run the application.
    nbody/nbody
    # Clean build output.
    b clean

**Persistent Building:**
Out-of-source build with persistent configuration:

    # Create the persistent configuration out-of-source and set appropiate compiler flags.
    bdep init -C @gcc cc config.cxx=g++ "config.cxx.coptions=-O3 -march=native"
    # Build the executable.
    b
    # Run the executable.
    nbody/nbody
    # Clean build output.
    b clean

From here on, open your editor inside the directory and look at the code and start with further developments.


## Get the Package and Install the Application

    # Go somewhere to install the package.
    mkdir ~/builds
    cd ~/builds
    # Create persistent configuration for all packages in the new directory
    # 'cpp-basics-packages' with appropriate compiler flags and installation options.
    bpkg create -d cpp-basics-packages cc \
        config.cxx=clang++ \
        "config.cxx.coptions=-O3 -march=native" \
        config.install.root=/usr/local \
        config.install.sudo=sudo
    cd cpp-basics-packages
    # Download and build this packages inside the configuration folder.
    bpkg build nbody@https://github.com/lyrahgames/cpp-basics-nbody.git#master
    # Install the built executable with its documentation.
    bpkg install nbody
    # Run the application in any directory.
    nbody
    # Uninstall the executable while in 'cpp-basics-packages'.
    bpkg uninstall nbody


## Usage
Call the program with an appropriate configuration file.
An example can be found in the source folder with the name `test-system.txt`.

    ./nbody <configuration file>

- Left Mouse: Move the origin.
- Mouse Wheel: Zoom in and out.
- Space: Play and pause simulation.
- Escape: Close the program.
- r: Reset particle system to starting values.

## Configuration File Syntax

Commands are separated by lines.
A new line means a new command.
The number of newlines tabs, or spaces before a new command does not matter.
The command `particle` creates a new particle.
Afterwards the commands `r`, `v`, and `m` set the position, velocity, and mass respectively.

    particle
      r <float> <float>
      v <float> <float>
      m <float>

**Example:**

    particle
      r 0 0
      v 1 0
      m 1
    particle
      r 1 0
      v 0 1
      m 1
    particle
      r 1 1
      v -1 0
      m 1
    particle
      r 0 1
      v 0 -1
      m 1