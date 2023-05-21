#pragma once

#include "vmath.hpp"
#include <vector>

#ifndef WALLS_FLOORS_H
#define WALLS_FLOORS_H

class SurfaceC {
public:
    short vertices[3][3];
    float normal[3];
    float origin_offset;
    float lower_y;
    float upper_y;

    float min_x;
    float max_x;
    float min_z;
    float max_z;

    SurfaceC(short x0, short y0, short z0, short x1, short y1, short z1, short x2, short y2, short z2) {
        short verts[3][3] = { {x0, y0, z0}, {x1, y1, z1}, {x2, y2, z2} };
        set_vertices(verts);
    }

    SurfaceC(short verts[3][3]) {
        set_vertices(verts);
    }

    SurfaceC() {}

    void set_vertices(short verts[3][3]) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                vertices[i][j] = verts[i][j];
            }
        }

        lower_y = fminf(fminf(vertices[0][1], vertices[1][1]), vertices[2][1]) - 5;
        upper_y = fmaxf(fmaxf(vertices[0][1], vertices[1][1]), vertices[2][1]) + 5;

        min_x = fminf(fminf(vertices[0][0], vertices[1][0]), vertices[2][0]);
        max_x = fmaxf(fmaxf(vertices[0][0], vertices[1][0]), vertices[2][0]);
        min_z = fminf(fminf(vertices[0][2], vertices[1][2]), vertices[2][2]);
        max_z = fmaxf(fmaxf(vertices[0][2], vertices[1][2]), vertices[2][2]);

        calculate_normal();
    }

    void calculate_normal() {
        normal[0] = (vertices[1][1] - vertices[0][1]) * (vertices[2][2] - vertices[1][2]) - (vertices[1][2] - vertices[0][2]) * (vertices[2][1] - vertices[1][1]);
        normal[1] = (vertices[1][2] - vertices[0][2]) * (vertices[2][0] - vertices[1][0]) - (vertices[1][0] - vertices[0][0]) * (vertices[2][2] - vertices[1][2]);
        normal[2] = (vertices[1][0] - vertices[0][0]) * (vertices[2][1] - vertices[1][1]) - (vertices[1][1] - vertices[0][1]) * (vertices[2][0] - vertices[1][0]);

        float mag = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

        mag = (float)(1.0 / mag);
        normal[0] *= mag;
        normal[1] *= mag;
        normal[2] *= mag;

        origin_offset = -(normal[0] * vertices[0][0] + normal[1] * vertices[0][1] + normal[2] * vertices[0][2]);
    }
};

extern SurfaceC wallsC[];
extern SurfaceC floorsC[];
extern SurfaceC object_walls[];
extern SurfaceC object_floors[];
extern SurfaceC pyramid_platform_floors[];
extern SurfaceC track_platform_floors[];
extern SurfaceC track_platform_walls[];

extern const int total_wallsC;
extern const int total_floorsC;
extern const int total_pyramid_floors;
extern const int total_track_floors;
extern const int total_track_walls;
extern const int total_object_walls;
extern const int total_object_floors;

extern int n_walls;
extern int n_floors;
extern int n_object_floors;
extern int n_object_walls;

int find_floor(float* position, SurfaceC** floor, float& floor_y, SurfaceC floor_set[], int n_floor_set);

#endif