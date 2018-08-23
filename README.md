# fluffy-octo-potato

An application for creating and optimizing toolpaths for a 3D printing system consisting of multiple indevidual nozzles. The application is part of a ongoing research collaboration between the Department of Computing, Mathematics and Physics at  Western Norway University of Applied Sciences and the fablab Fellesverkstedet in Oslo.  See separate git for mechanical prototype of the system, based on Fellesverkstedet´s [chamferrail](https://github.com/fellesverkstedet/fabricatable-machines) system.   All code is writter in the c++ framework Openframeworks. 

## Status
Currently under heavy development. Getting close with the slicing algorithm. 

## Getting the toolpaths - Slicing 

I´m creating my own mesh slicer as a separate addon to Openframeworks. This was a lot tougher then I first thought and very much still a work in progress. It´s documented [here](https://github.com/frikkfossdal/ofxSlicer). 

For now I´m using Cura to create my gcode, and some python scripts to organize the gcode into a .json file. 

## Optimizing the toolpaths 

TODO: Explain the problem and how you are trying to solve it

## TODO

1. Add progress bar to slicing. 
2. Add addaptive slicing for better surface quality and increased speed
3. Implement simulation of the physical system (I think this is better in a separate application for now)
6. Optimize the toolpaths for multiheaded system. Think a good start here could be to investigate how genetic algorithms are used  to optimize trajectories in robotics.
