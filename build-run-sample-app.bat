@echo off
REM Simple batch script to build and run the Sandbox application

@echo ---------------------------------------------------
@echo Creating build directory...
@echo ---------------------------------------------------
mkdir build

@echo ---------------------------------------------------
@echo Generating build files...
@echo ---------------------------------------------------
cd build
cmake ..

@echo ---------------------------------------------------
@echo Building sandbox executable...
@echo ---------------------------------------------------
cmake --build . --config Release

@echo ---------------------------------------------------
@echo Running executable...
@echo ---------------------------------------------------
cd ..
.\build\Sandbox\Release\Sandbox.exe
