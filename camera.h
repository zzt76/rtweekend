#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
public:
    // Camera
    camera(point3 lookfrom,
           point3 lookat,
           vec3 vup,
           double v_fov,
           double aspect_ratio,
           double aperture,
           double focus_dist) {
        auto theta = degrees_to_radians(v_fov);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = viewport_height * aspect_ratio;

        // auto w = -unit_vector(lookat - lookfrom);
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * u * viewport_width;
        vertical = focus_dist * v * viewport_height;
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

        lens_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        // +offset in origin and -offset in direction to simulate a convex len
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
};

#endif // implement a simple camera