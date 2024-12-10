## Cloning the Repo

```
git clone ...
git submodule update --init --recursive
```

## Setup
For MacOs (Arm architecture), make sure to install SDL2.framework and SDL2_ttf.frameworks in your Library/Frameworks folder for linking to properly work

## Running The Game Engine
To install python dependecies, run:
1) MacOs
``` 
    brew install python-tk
    pip3 install --break-system-packages Pillow
```

2) Linux
```
    sudo apt-get install python3-tk
```

Then, you should be able to run the game engine:

``` 
python3 main.py
```

## Running The Game
To run the code, type in the following commands starting from the main directory (Engine):

```
cd src 
make clean
make run
```

## Binding Setup
For Linux (WSL):
1) `sudo apt install cmake`

