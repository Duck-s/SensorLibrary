# SensorLibrary
This is a lib put together for the FinalProgect 1 class.
Its basic in its functions but should streamline the programing process for a few.

The only things I could not add due to some compilation definition error was the IRremote.h functions
This was added in the .ino file so you can see how its done but doesent need to be used and will not be carried over if you copy the Functions library.

## Pin locations
All the pins are defined in the Functions.cpp file and should be changed before use.
These Functions may be component specific so dont expect it to work immediatly if you didnt get the ELEGOO kit.

Feel free to yoink the code you need for your own purpouses and change it to suit your needs.

## Test Cases
Theres a TestInit() function that runs through some basic sensor tests, you can keep it seperate as is in the SensorCompiled example.
Or you can add it to the Init() function found in the cpp file.

This code should still works even if you dont use all the sensors.
I take no blame if it fries your shit check the code over before use, we all make mistakes.

