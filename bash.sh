#!/bin/bash
echo "Hi $USER! Just compiling the code now"
g++ -c  -std=c++11 src/*.cpp 
echo "Now linking the objects to the output"
g++ *.o -o StarshipFontana -lSDL -lSDL_image
echo "DONE! :)"