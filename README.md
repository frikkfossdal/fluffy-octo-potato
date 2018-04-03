# fluffy-octo-potato
An Openframeworks application for doing multi-headed additive manufacturing. The application is currently only working as a slicer. Long term goal is to optimize and generate the toolpaths the indevidual extruders. The application is part of a ongoing research project with Fellesverkstedet in Oslo, and their work on [Fabricatable Machines](https://github.com/fellesverkstedet/fabricatable-machines)

Currently under heavy development.

# The Slicer

The algorithms behind the slicer is mostly motivated by the work presented in this [paper.](http://www.dainf.ct.utfpr.edu.br/%7Emurilo/public/CAD-slicing.pdf) In the paper, the authors claims that they have developed a slicing algorithm that is time-wise optimal compared to other slicing algorithms known in litterature. We´ll see about that! The slicing algorithm goes something like this:

1. Mesh slicing:  Calculate triangle intersection points on each plane
2. Construct contours: Create polygons from the intersection points
3. Make sence of the polygons (Clockwice/Counterclockwise)

Easy right? Not so much. Turns out that I really have to reassess some fundamental vector math.

![Overview](img/currentOverview.png)

TODO: Post the main slicer code and explain it

# ToDo

1. Fix issue with slicer
2. Add addaptive slicing for better surface quality
3. Create toolpaths from sliced meshes
4. Implement simulation of the physical system.
5. Optimize the toolpaths for multiheaded system. Think a good start here could be to investigate how genetic algorithms are used  to optimize trajectories in robotics.
