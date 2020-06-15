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
    class Canvas {
    public:
        int m_height;
        int m_width;
        Color* pixels;

        Canvas(const int width, const int height) : m_width{ width }, m_height{ height }{
            pixels = new Color[m_height * m_width];
            for (int i = 0; i < (m_height * m_width); ++i) {
                pixels[i] = Color();
            }
        }

        static void write_pixel(int x, int y, Canvas& c, Color color) {
            int i = (x * (c.m_width) + y);
            c.pixels[i] = color;
        }

        Color get_pixel(int x, int y, Canvas c) {
            return c.pixels[(x * (c.m_width) + y)];
        }

        void test_canvas(Canvas& c);

        static Canvas render(Camera& camera, World& world) {
            std::ofstream tcfile;
            tcfile.open("test.ppm");
            tcfile << "P3\n" << 175 << ' ' << 175 << '\n' << 255 << '\n';
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
