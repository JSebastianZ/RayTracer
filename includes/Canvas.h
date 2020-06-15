/*
* Interface file for the Ray Tracer 2D rendered image canvas.
*
*
* This file contains the definitions for the canvas class,
* which provides the a plane where images will be draw.
*
*/


#ifndef CANVAS_H
#define CANVAS_H


#include "Color.h"
#include <array>
#include "precision.h"
#include <iostream>
#include <fstream>
#include "Camera.h"
#include "World.h"
#include "Ray.h"


namespace rtc {

    /*
    * The Ray Tracer canvas is a rectangular grid of pixels.
    * Its width and height can be configured upon creation.
    * A canvas is rendered by a Camera object for display.
    */

    class Canvas {

    public:

        // Canvas width and heigth;
        int m_height;
        int m_width;

        // A canvas is implemented as a one dimention array of pixels, each one storing an RGB color value.
        Color* pixels;

        // Canvas constructor. The pixels array size is width * height
        Canvas(const int width, const int height) : m_width{ width }, m_height{ height }{
            pixels = new Color[m_height * m_width];
            for (int i = 0; i < (m_height * m_width); ++i) {
                pixels[i] = Color();
            }
        }

        // Draws RGB color values into a single canvas pixel.
        static void write_pixel(int x, int y, Canvas& c, Color color) {
            int i = (x * (c.m_width) + y);
            c.pixels[i] = color;
        }

        // Returns the specified canvas pixel RGB color value.
        Color get_pixel(int x, int y, Canvas c) {
            return c.pixels[(x * (c.m_width) + y)];
        }

        // Camera renders a "world scene" into a 2D image drawn in the canvas.
        static Canvas render(Camera& camera, World& world) {
            std::ofstream tcfile;
            tcfile.open("test.ppm");
            tcfile << "P3\n" << camera.m_hsize << ' ' << camera.m_vsize << '\n' << 255 << '\n';
            Canvas image = Canvas(camera.m_hsize, camera.m_vsize);
            for (int x = 0; x < camera.m_vsize; x++) {
                for (int y = 0; y < camera.m_hsize; y++) {
                    Ray ray = Ray::ray_for_pixel(camera, x, y);
                    Color color = ray.color_at(world, ray);
                    image.write_pixel(x, y,image, color);
                    real r = color.m_r * 255;
                    if (r > 255) r = 255;
                    real g = color.m_g * 255;
                    if (g > 255) g = 255;
                    real b = color.m_b * 255;
                    if (b > 255) b = 255;
                    tcfile << r << ' ' << g << ' ' << b << '\n';
                }
            }
            tcfile.close();
            return image;
        }
    };
}
#endif // !CANVAS_H
