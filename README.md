![Logo](Resources/logo-black-transparent.png)
# Aquarius
A 2D game engine developed by Colton Smith, Daniel Burke, & Liam Warren for the Junior Software Design Project 
(ECE 5010).

## Additional Required Software
- CMake Version 3.10 ([Download](https://cmake.org/download/))

**The below commands and the sample application works for Windows, MAC, and Linux but not Windows Subsystem for Linux 
(WSL)**

## Building Aquarius
1. Extract the zip file to Aquarius/
2. Navigate in command-line interface to the unzipped project folder 
3. Make a build directory by executing the following command `mkdir build`
4. Navigate to the build directory by executing the following command `cd build`
5. Execute CMake to build the project by executing the following command `cmake ..`
6. Generate an executable file by executing the following command `cmake --build . --config Release`

## Running Sample Aquarius Application
1. Remain in the same command-line interface window used to build the project, navigate to the Sandbox directory of the 
   build directory by executing the following command `cd Sandbox`. If you have exited out of the command-line interface
   used to build the project please navigate to `Aquarius/build/Sandbox` before proceeding to the next step. 
2. Run the generated executable file by executing the following command `./Sandbox`
3. If a window opens, you have successfully built and run a sample Aquarius application!