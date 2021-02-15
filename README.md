![Logo](Resources/logo-black-transparent.png)
# Aquarius
A 2D game engine developed by Colton Smith, Daniel Burke, & Liam Warren for the Junior Software Design Project 
(ECE 5010).

## Additional Required Software
- CMake Version 3.10 ([Download](https://cmake.org/download/))

**The below commands and the sample application works for Windows, MAC, and Linux but not Windows
Subsystem for Linux (WSL)**

**For ease of building and running a sample Aquarius application scripts were developed to automate the building and 
running. Please see the below instructions based on your operating system.**

## Building and Running a Sample Aquarius Application Automatically on Mac & Linux
1. Navigate in a command-line interface to the project folder
2. In your command-line execute the following command `sh build-run-sample-app.sh`
3. If a window opens, you have successfully built and run a sample Aquarius application!

## Building and Running a Sample Aquarius Application Automatically on Windows
1. Navigate in a command-line interface to the project folder
2. In your command-line interface execute the following command `build-run-sample-app.bat`
3. If a window opens, you have successfully built and run a sample Aquarius application!

**Alternatively, the below instructions could be used to complete the building and running of a sample Aquarius 
application manually on Windows, MAC, and Linux but not WSL.**

## Building Aquarius Manually
1. Navigate in a command-line interface to the project folder 
2. Make a build directory by executing the following command `mkdir build`
3. Navigate to the build directory by executing the following command `cd build`
4. Execute CMake to build the project by executing the following command `cmake ..`
5. Generate an executable file by executing the following command `cmake --build . --config Release`

## Running a Sample Aquarius Application Manually
1. Remain in the same command-line interface window used to build the project, navigate to the Sandbox directory of the 
   build directory by executing the following command `cd Sandbox`. If you have exited out of the command-line interface
   used to build the project please navigate to `Aquarius/build/Sandbox` before proceeding to the next step. 
2. Run the generated executable file by executing the following command `./Sandbox`
3. If a window opens, you have successfully built and run a sample Aquarius application!