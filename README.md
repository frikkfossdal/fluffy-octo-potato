# fluffy-octo-potato
An Openframeworks application for doing multi-headed additive manufacturing. The application is currently only working as a slicer. Long term goal is to optimize and generate toolpaths the indevidual extruders. The application is part of a ongoing research project with Fellesverkstedet in Oslo, and their work on [Fabricatable Machines](https://github.com/fellesverkstedet/fabricatable-machines)

Currently under heavy development.

# The Slicer

The algorithms behind the slicer is mostly motivated by the work presented in this [paper.](http://www.dainf.ct.utfpr.edu.br/%7Emurilo/public/CAD-slicing.pdf)

![Overview](img/currentOverview.jpg)

TODO: Post the main slicer code and explain it

# ToDo

1. Create toolpaths from sliced meshes
2. Implement simulation of the physical system.
3. Optimize the toolpaths for multiheaded system. Think a good start here could be to investigate how genetic algorithms are used  to optimize trajectories in robotics.
