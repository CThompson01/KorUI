# KorUI

## Description

KorUI is a UI library for Raylib in C.

## Building

Building is a little different depending on your OS. Find your OS below, and follow the instructions.

### Linux

Currently, automated setup will only work on Ubuntu. 

Open terminal and run the following command.

```
./setup
```

This should automatically install all of the required dependencies.

After the setup is finished running, you should be able to build the project using make. If you've never used make, simply navigate to your terminal and run the following command.

```
make
```

The finished build can be found within the build/ directory. To run the program, you can execute the application from the command line with ./korui_test when in the build directory. You may need to mess with permissions in order to allow it to be executed using chmod. The following command should work.

```
chmod +x korui_test
```

## TODO

[x] Overhaul UIElement creation using pointers
[ ] Utilize function pointers for render and input detection to cut down CPU time and allow overrides
[ ] Combine Pressed and Released functions into one input function
[ ] Utilize void pointers with callbacks for UI input