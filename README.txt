Face Enhancer - C++ Project
Overview

This project enhances blurred face images using Unsharp Masking + CLAHE (Contrast Limited Adaptive Histogram Equalization) to make faces sharper and clearer.

Input: Blurred face image (place your test image in the same folder as the executable)
Output: Enhanced face image (face_enhanced.jpg) and comparison (face_comparison.jpg)

The project is implemented in C++ using OpenCV.

Folder Structure
FaceEnhancer/
├─ main.cpp               # Main program
├─ build/Debug/           # Executable and test image go here
│   ├─ opencvtest.exe
│   └─ test.JPG
├─ libs/                  # Required OpenCV DLLs
│   ├─ opencv_core412.dll
│   ├─ opencv_imgproc412.dll
│   └─ opencv_highgui412.dll
├─ CMakeLists.txt         # CMake build configuration
└─ README.txt             # This file

Requirements

C++ Compiler: MinGW or MSVC (Visual Studio)

CMake ≥ 3.10

OpenCV (DLLs included in libs/)

Windows OS (for the included DLLs)

Build & Run Instructions

Place your test image in build/Debug/ (same folder as executable).

Open Command Prompt / PowerShell in the project folder:

cd FaceEnhancer
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .


Copy DLLs:
Copy all DLLs from libs/ into build/Debug/ so the executable can run.

Run the program:

opencvtest.exe


The program will display:

Original image (left)

Enhanced image (right)

It will also save:

face_enhanced.jpg

face_comparison.jpg

Notes

Enhancement is done via Unsharp Masking + CLAHE.

You can increase the number of passes in main.cpp for stronger enhancement.

Make sure your test image is in the same folder as opencvtest.exe for correct loading.