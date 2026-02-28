# Lumen Forge - C++ (W.I.P)

A basic Raytracer with no external dependencies, implemented in C/C++ as part of my 3D graphics and computer simulations learning process. feel free to fork, comment suggestions, tips or add pull requests. </br>

> [!NOTE]  
> This project is a work in progress.

# Step-by-Step Results

<div align="center">
    <img src="https://github.com/AliMoghimii/LumenForge-CPP-Raytracer/blob/main/Results/01%20-%20Render%20Test.png" width="360" height="360">
    <img src="https://github.com/AliMoghimii/LumenForge-CPP-Raytracer/blob/main/Results/02%20-%20Shading%20Test.png" width="360" height="360">
    <img src="https://github.com/AliMoghimii/LumenForge-CPP-Raytracer/blob/main/Results/03%20-%20Reflection%20Test.png" width="720" height="405">
    <img src="https://github.com/AliMoghimii/LumenForge-CPP-Raytracer/blob/main/Results/04%20-%20Raytraced%20Scene.png" width="720" height="405">
    <img src="https://github.com/AliMoghimii/LumenForge-CPP-Raytracer/blob/main/Results/06%20-%20Models%20&%20Primitives.png" width="720" height="405">
</div>

# Manual compile examples

**To compile and create an .o file (Compiler)**

* g++ -c Raytracer.cpp

**To create a output.exe file from the .o files (Linker)**

* g++ Raytracer.o Image.o (etc...) -o output

**To run the output.exe file**

* ./output

# Compile using CMake file

**Prerequisites**
1. Make sure "g++" and "make" are present in your enviroment variables, test with, g++ --version and make --version
    if missing add the following to "Path" in "User variables for YOURNAME" (VSCode MSYS2) </br>
    * Base compiler files :   C:\msys64\ucrt64\bin </br>
    * CMake :                 C:\msys64\usr\bin </br>

2. Install the Makefile extension by Microsoft and add the "C:\msys64\usr\bin" path to the Make Path extension settings field.


**To run the make file**

* make

**To clear the compiled files**

* make clean

**To make the files and run the program**

* make run

# References and resources
Some books and references that helped me learn the basics :<br>

* Raytracing Book Series by Peter Shirley, Trevor David Black, Steve Hollasch <br>
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) <br>
[_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html) <br>
[_Ray Tracing: The Rest of Your Life_](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html) <br>

* Arun Ravindran's (ArunRocks) references on raytracing and tutorials <br>
[_Website_](https://arunrocks.com/)

* LearningTwice's tutorials <br>
[_Website_](https://www.youtube.com/@learningtwice)
