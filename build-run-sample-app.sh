#!/bin/bash

# Simple build script for Aquarius sandbox application
set -x

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
cmake --build . 
echo "-----------------------------------"

echo "-----------------------------------"
echo "Running executable..."
cd Sandbox
./Sandbox
echo "-----------------------------------"
