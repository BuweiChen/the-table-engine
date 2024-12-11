#!/bin/bash

# Ensure Python3 and Pip are installed
command -v python3 &>/dev/null || { echo "Installing Python 3..."; sudo apt-get install -y python3; }
command -v pip3 &>/dev/null || { echo "Installing Pip..."; sudo apt-get install -y python3-pip; }

# Install Python dependencies using pip
pip3 install Pillow tk

# Navigate to the directory containing main.py, adjust the path as necessary
cd Engine_GUI

# Run the Python script
python3 main.py
