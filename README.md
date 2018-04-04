# fluffy-octo-potato
An Openframeworks application for doing multi-headed additive manufacturing. The application is currently only working as a slicer. Long term goal is to optimize and generate the toolpaths the indevidual extruders. The application is part of a ongoing research project with Fellesverkstedet in Oslo, and their work on [Fabricatable Machines](https://github.com/fellesverkstedet/fabricatable-machines)

Currently under heavy development.

# The Slicer

The algorithms behind the slicer is mostly motivated by the work presented in this [paper.](http://www.dainf.ct.utfpr.edu.br/%7Emurilo/public/CAD-slicing.pdf) In the paper, the authors claims that they have developed a slicing algorithm that is time-wise optimal compared to other slicing algorithms known in litterature. We´ll see about that! The slicing algorithm goes something like this:

1. **Create a list containing all triangles of the mesh model.** All the triangles are sorted in ascending order in terms of the lowst point in the triangle. I´ve commented this in the code.  Getting the triangles  was a bit of a struggle in Openframeworks. To import .stl files, I use the [ofxAssimpModelLoader](http://openframeworks.cc/documentation/ofxAssimpModelLoader/ofxAssimpModelLoader/) addon in openframeworks.  It took some tweaking to get the triangle faces, with it´s belonging vertices, extracted from the assimp class.  NOTE: It would probaly be easier to use some kind of existing C++ framework for geometry like CGAL, but not as much fun! 
2. **Mesh slicing:  Calculate triangle intersection points on each plane.** This is fairly easy. 
3. **Construct contours: Create polygons from the intersection points**
4. **Make sence of the polygons (Clockwice/Counterclockwise)**

Easy right? Not so much. Turns out that I really have to reassess some fundamental vector math.

![Overview](img/currentOverview.png)

TODO: Post the main slicer code and explain it

# ToDo

1. Relearn vector calculus and fix issue with intersection calculation
2. Create toolpaths from sliced meshes
3. Add addaptive slicing for better surface quality
4. Implement simulation of the physical system (I think this is better in a separate applciation)
5. Optimize the toolpaths for multiheaded system. Think a good start here could be to investigate how genetic algorithms are used  to optimize trajectories in robotics.
