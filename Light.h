#ifndef LIGHT_DEF
#define LIGHT_DEF
#define LIGHT_DETAIL 3
#define MAX_DIST	 1000

#include "Object.h"
#include <iostream>
#include <time.h>

class Light {
public:

	Vector3 position;

	Vector3 light_color;

	vec3 manager;

	Light() {}

	Light(Vector3 light_color, Vector3 position) {
		this->light_color = light_color;
		this->position = position;
		srand(NULL);
	}

	Vector3 getLightingColor(Object obj, Ray ray) {
		Vector3 multiplied_colors = manager.vecDivideScaler(manager.vecAdd(obj.color, light_color), 2);
		Vector3 diffuse_pixel = obj.color;
		Vector3 diffuse_calc = manager.vecAdd(ray.position, manager.vecMultiplyScaler(manager.getNormalizedVector(ray.position), obj.t));
		Vector3 L = manager.vecSubtract(position, diffuse_calc);
		Vector3 N = obj.getSurfaceNormal(diffuse_calc);
		double dt = manager.getDotProduct(manager.getNormalizedVector(L), manager.getNormalizedVector(N));
		diffuse_pixel = manager.vecMultiplyScaler(manager.vecMultiplyScaler(multiplied_colors, dt), obj.diffuse_strength);
		diffuse_pixel.x = manager.getClampedValue(diffuse_pixel.x, 0, 255);
		diffuse_pixel.y = manager.getClampedValue(diffuse_pixel.y, 0, 255);
		diffuse_pixel.z = manager.getClampedValue(diffuse_pixel.z, 0, 255);
		return diffuse_pixel;
	}
};

#endif LIGHT_DEF