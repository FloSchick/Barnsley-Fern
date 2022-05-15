# Barnsley-Fern


**C++ implementation of a [Barnsley-Fern](https://en.wikipedia.org/wiki/Barnsley_fern) based on Producer/Consumer model with multithreading**

_This Repository was used for educational purpose._

<img src="resources/farn_horizontal.png" alt="JobGuy Banner" width=1000/><br/>

# Insight
This script uses multiple Producer threads, each working on their own Barnsley fern and feeding Pixel coordinates and RGB color to a Ring Buffer.
Consumer threads then collect Data from this Buffer and draw these Pixels to a .png.

# Requirements
* CMake

        sudo apt-get install cmake

* libpng

        sudo apt-get install libpng-dev

# Usage

To build executable run the following commands:

        mkdir build
        cd build
        cmake ..
        make

To delete all build files simply run:

        make clean


