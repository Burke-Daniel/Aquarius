#!/bin/bash

# Simple build script for Aquarius sandbox application
echo "-----------------------------------"
echo "Creating build folder..."
mkdir build
echo "-----------------------------------"

echo "-----------------------------------"
echo "Generating build files..."
cd build 
cmake ..
echo "-----------------------------------"

echo "-----------------------------------"
echo "Building executable..."
cmake --build . --config Release
echo "-----------------------------------"

echo "-----------------------------------"
echo "Running executable..."
cd .. 
./buid/Sandbox/Sandbox
echo "-----------------------------------"
