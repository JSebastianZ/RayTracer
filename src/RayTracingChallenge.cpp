// RayTracingChallenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix.h"
#include "Object.h"
#include "Sphere.h"
#include "Canvas.h"
#include "World.h"
#include "Ray.h"
#include "Canvas.h"

using namespace rtc;

int main()
{
    World w = World();
    Point from = Point(0, 1.5, -5);
    Point to = Point(0, 1, 0);
    Vector up = Vector(0, 1, 0);
    Matrix transform = Matrix::view_transform(from, to, up);
    Camera c = Camera(175, 175, (PI / 3), transform);
    Canvas image = Canvas::render(c, w);

    return 0;
    
}

/*
   real hits = 0;
    Color black{ 0,0,0 };
    Point p{ 0,0,65 };
    Point p1 = Point(10, 0.01, 10);
    real diameter = 2;
    Color ctest(0.2, 1, 0.5);
    Material material(ctest, 0, 0.9, 0.9, 200.0);
    Color light_color(Color(1, 1, 1));
    Point light_position(Point(-10, 10, -10));
    Light light(light_position, light_color);
    Canvas knvas = Canvas(100, 100);
    int knvas_depth = 100;
    Point scale{ 15 ,5,5 };
    Matrix m = Matrix::identity(4);
    Matrix translation = Matrix::translation_matrix_p(p);
    Matrix ry = Matrix::rotation_matrix_y(PI / 4);
    Matrix rx = Matrix::rotation_matrix_x(PI / 2);
    Matrix rz = Matrix::rotation_matrix_z(PI /2 );
    Matrix scaling = Matrix::scaling_matrix_p(scale);
    Matrix shearing = Matrix::shearing_matrix(25, 2, 15, 5, 5, 6);
    Matrix final = Matrix::multiplyMatrices(translation, (Matrix::multiplyMatrices(ry, (Matrix::multiplyMatrices(rx, scaling)))));

    Matrix t1 = Matrix::scaling_matrix_p(p1);
    Matrix rs1 = Matrix::multiplyMatrices(rx, t1);
    Matrix rs = Matrix::multiplyMatrices(ry, rs1);

    Matrix custom = Matrix::multiplyMatrices(translation, rs);

    Sphere sphere = Sphere(diameter, Point(0,0,0), material, custom);




    for (int x = (-knvas.m_width / 2), i = 0; x < (knvas.m_width / 2); x++, i++) {
        for (int y = (-knvas.m_height / 2), j = 0; y < (knvas.m_height / 2); y++, j++) {

            // Creo el rayo y determino si le pega a la esfera o no
            Ray r(Point(0, 0, 0), (Vector::normalize(Point::subPoints(Point(x, y, knvas_depth), Point(0, 0, 0)))));
            r.sphere_intersections(r, sphere);
            hits = r.hit_location(r.accummulate_ix);

            // Defino el vector EYE como el negativo del rayo
            Vector eye(Vector::negate(r.m_direction));

            // Ahora necesito los PUNTOS de INTERSECCION en 3D Phit = ray.orig + ray.dir * t
            Point choke(Ray::position(r, hits));
            Matrix mti(Matrix::inverse(sphere.b_transform));

            // Calculo del vector Normal al hit point choke
            Point object_point(rtc::Matrix::multiplyByTuple(mti, choke));
            Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));
            Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(mti), object_normal));
            world_normal.m_w = 0;
            Vector normal(Vector::normalize(world_normal));

            // Lightning
            Color c(Ray::lighting(sphere.b_material, light, choke, eye, normal));
            c.m_r = static_cast<int>(255.999 * c.m_r);
            if (c.m_r > 255) c.m_r = 255;
            c.m_g = static_cast<int>(255.999 * c.m_g);
            if (c.m_g > 255) c.m_g = 255;
            c.m_b = static_cast<int>(255.999 * c.m_b);
            if (c.m_b > 255) c.m_b = 255;

            if (hits >= 0) {
                knvas.write_pixel(i, j, knvas, c);
            }
            else {
                knvas.write_pixel(i, j, knvas, black);
            }

        }
        hits = 0;
    }
    std::ofstream tcfile;
    tcfile.open("maricon.ppm");
    tcfile << "P3\n" << knvas.m_width << ' ' << knvas.m_height << '\n' << 255 << '\n';
    for (int j = knvas.m_height - 1; j >= 0; --j) {
        for (int i = 0; i < knvas.m_width; ++i) {
            tcfile << knvas.get_pixel(i, j, knvas).m_r << ' ' << knvas.get_pixel(i, j, knvas).m_g << ' ' << knvas.get_pixel(i, j, knvas).m_b << '\n';
        }
    }

    tcfile.close();
    std::cout << "maricon" << '\n';
    return 0;

*/

/*
int main()
{

    std::ofstream tcfile; 
    tcfile.open("test_sphere1.ppm");
    tcfile << "P3\n" << knvas.m_width << ' ' << knvas.m_height << '\n' << 255 << '\n';
    for (int j = knvas.m_height - 1; j >= 0; --j) {
        for (int i = 0; i < knvas.m_width; ++i) {
            tcfile << knvas.get_pixel(i,j,knvas).m_r << ' ' << knvas.get_pixel(i, j, knvas).m_g << ' ' << knvas.get_pixel(i, j, knvas).m_b << '\n';
        }
    }
    
tcfile.close();
std::cout << "maricon" << '\n';
return 0;

}
*/

/*
    Color black{ 0,0,0 };
    Point p{ 0,0,64 };

    Color ctest(0.2, 1, 0.5);
    Material material(ctest, 0.1, 0.9, 0.9, 200.0);
    Color light_color(Color(1, 1, 1));
    Point light_position(Point(-120, 120, -10));
    Light light(light_position, light_color);
    Canvas knvas = Canvas(256, 256);
    int knvas_depth = 128;
    Point scale{ 1 , 1,1 };
    Matrix t(Matrix::scaling_matrix_p(scale));
    Matrix transform(Matrix::multiplyMatrices(Matrix::translation_matrix_p(p), t));
    Sphere sphere = Sphere(64, p, material, transform);


    real hits = 0;

    for (int x = (-knvas.m_width / 2), i = 0; x < (knvas.m_width / 2); x++, i++) {
        for (int y = (-knvas.m_height / 2), j = 0; y < (knvas.m_height / 2); y++, j++) {

            // Creo el rayo y determino si le pega a la esfera o no
            Ray r(Point(0, 0, 0), (Vector::normalize(Point::subPoints(Point(x, y, knvas_depth), Point(0, 0, 0)))));
            r.sphere_intersections(r, sphere);
            hits = r.hit_location(r.accummulate_ix);

            // Defino el vector EYE como el negativo del rayo
            Vector eye(Vector::negate(r.m_direction));

            // Ahora necesito los PUNTOS de INTERSECCION en 3D Phit = ray.orig + ray.dir * t
            Point choke(Ray::position(r, hits));
            Matrix mti(Matrix::inverse(transform));

            // Calculo del vector Normal al hit point choke
            Point object_point(rtc::Matrix::multiplyByTuple(mti, choke));
            Vector object_normal(Point::subPoints(object_point, rtc::Point(0, 0, 0)));
            Vector world_normal(Matrix::multiplyByTuple(rtc::Matrix::transpose(Matrix::inverse(transform)), object_normal));
            world_normal.m_w = 0;
            Vector normal(Vector::normalize(world_normal));

            // Lightning
            Color c(Ray::lighting(sphere.b_material, light, choke, eye, normal));
            c.m_r = static_cast<int>(255.999 * c.m_r);
            if (c.m_r > 255) c.m_r = 255;
            c.m_g = static_cast<int>(255.999 * c.m_g);
            if (c.m_g > 255) c.m_g = 255;
            c.m_b = static_cast<int>(255.999 * c.m_b);
            if (c.m_b > 255) c.m_b = 255;

            if (hits >= 0) {
                knvas.write_pixel(i, j, knvas, c);
            }
            else {
                knvas.write_pixel(i, j, knvas, black);
            }

        }
        hits = 0;
    }
    std::ofstream tcfile;
    tcfile.open("maricon.ppm");
    tcfile << "P3\n" << knvas.m_width << ' ' << knvas.m_height << '\n' << 255 << '\n';
    for (int j = knvas.m_height - 1; j >= 0; --j) {
        for (int i = 0; i < knvas.m_width; ++i) {
            tcfile << knvas.get_pixel(i, j, knvas).m_r << ' ' << knvas.get_pixel(i, j, knvas).m_g << ' ' << knvas.get_pixel(i, j, knvas).m_b << '\n';
        }
    }

    tcfile.close();
    std::cout << "maricon" << '\n';
    return 0;

*/

/*

    World w = World();
    Point from = Point(0, 1.5, -5);
    Point to = Point(0, 1, 0);
    Vector up = Vector(0, 1, 0);
    Matrix transform = Matrix::view_transform(from, to, up);
    Camera c = Camera(100,50,PI/3, transform);
    Canvas image = Canvas::render(c, w);
    std::ofstream tcfile;
    tcfile.open("test_sphere1.ppm");
    tcfile << "P3\n" << image.m_width << ' ' << image.m_height << '\n' << 255 << '\n';
    for (int j = 0; j < image.m_height; --j) {
        for (int i = 0; i < image.m_width; ++i) {
            real r = 255 * image.get_pixel(i, j, image).m_r;
            if (r > 255) r = 255;
            real g = 255 * image.get_pixel(i, j, image).m_g;
            if (g > 255) g = 255;
            real b = 255 * image.get_pixel(i, j, image).m_b;
            if (b > 255) b = 255;
            tcfile << r << ' ' << g << ' ' << b << '\n';
        }
    }

    tcfile.close();
    std::cout << "maricon" << '\n';
    return 0;
*/