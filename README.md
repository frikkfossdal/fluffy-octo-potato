# fluffy-octo-potato

An application for creating and optimizing toolpaths for a 3D printing system consisting of multiple indevidual nozzles. The application is part of a ongoing research collaboration between the Department of Computing, Mathematics and Physics at  Western Norway University of Applied Sciences and the fablab Fellesverkstedet in Oslo.  See separate git for mechanical prototype of the system, based on Fellesverkstedet´s [chamferrail](https://github.com/fellesverkstedet/fabricatable-machines) system.   All code is writter in the c++ framework Openframeworks. 

## Status
Currently under heavy development. 

## Getting the toolpaths - Slicing 

I´m creating my own mesh slicer as a separate addon to Openframeworks. This was a lot tougher then I first thought and very much still a work in progress. It´s documented [here](https://github.com/frikkfossdal/ofxSlicer). 

For now I´m using Cura to create my gcode, and python scripts to organize the gcode into a .json file. The python tools are linked [here](https://github.com/frikkfossdal/fluffy-octo-potato/tree/master/tools).

## Optimizing the toolpaths 

TODO: Explain the problem and how you are trying to solve it

## TODO

