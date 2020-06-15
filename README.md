# RayTracer
This Ray Tracer is a C++ implementation of the Whitted ray tracing algorithm*.

The goal of this project is to provide a 3D API that fully supports a recursive ray tracer as proposed by Turner Whitted in 1979.

To accomplish the goal, a 3D API is designed with an object oriented approach. It implements classes that support Vector and Matrix algebra.

## How does it work?
The color of each pixel of the final image is calculated as follows:

1- A ray is casted into the scene, and the point where a surface is "hitted" is identified.

2- A ray is casted from point #1 toward every light source in the scene, in order to determine the lights that illuminate it.

3- If #1 is a reflective surface, cast a ray in the reflection direction, and determine the color that is reflected there, recursively.

4- If #1 is a transparent surface, start the process in the direction of refraction.

5- Add all color values that contribute to #1 (surface color, reflection, refraction) and return the result as the final color of the pixel.

The development of this ray tracer is also inspired by Jamis Buck Ray Tracer Challenge work.**
 
 
 
 
 
 

**Turner Whitted. 1980. An improved illumination model for shaded display. Commun. ACM 23, 6 (June 1980), 343–349.*

***Buck, Jamis. Ray tracer challenge. Raleigh : The Pragmatic Bookshelf, 2018*
