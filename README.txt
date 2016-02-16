MINESWEEPER ADVISER PROGRAM README FILE - Feb/11/2016

HOW TO BUILD AND RUN THIS PROGRAM ON THE DIFFERENT SYSTEMS
===========================================================


LINUX
======

To build this program on the Linux systems you need recent "g++" compiler 
and "make" program. This program is checked to build correctly on the 
Ubuntu 14.04 LTS with g++ 4.8.4, however, it should be possible to build it
on the other Linux systems and different g++ versions as well.

To build program use the following command:
make

This should build executable file called "minesweeper".

To run sample test case use the following command:
make test

To run program with some input use the following command;
./minesweeper input-file-name

where "input-file-name" is the name of the file that contains input data,
formatted according to rules, described  in the task description document.


WINDOWS
========

To build this program on Widows, you need to have Microsoft Visual Studio 2015
with Update 1 installed. It may work with earlier versions of Visual Studio,
but you will have to make Visual Studio project yourself.  However, we don't 
cover this topic in this README document.

You may download Visual Studio 2015 Comminity Edition for free
(at the moment, free for individual developers, small teams and educational 
organizations) at the following web site:
https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx

Assuming you have Visual Studio 2015 installated do the following:

1. Launch Visual Studio 2015.
2. Open solution file called "minesweeper.sln".
3. Choose command Build->Rebuild Solution.
4. Choose command Project->Properties
5. Choose section "Debugging" on the left side of the project properties dialog.
6. Fill the field called "Command Line Arguments" - specify name of the input file.
7. Click OK.
8. Choose comamnd Debug->Start Without Debugging.
