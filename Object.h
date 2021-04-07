#ifndef OBJECT_DEF
#define OBJECT_DEF
#include <math.h>
#include "vec3.h"
#include "Ray.h"
#include "cases.h"

class Object {
public:
	OBJECT_TYPE type;
	vec3 manager;

	Vector3 position;
	Vector3 hit_position;
	Vector3 color;

	float diffuse_strength;
	float specular_strength;
	float shininess;

	float radius;
	float t = -1;

	Object() {}

	Object(OBJECT_TYPE type, Vector3 position, Vector3 color) {
		this->type = type;
		this->color = color;
		this->position = position;
	}

	INTERSECTION_CASE check_intersection(Ray ray) {

		switch (type)
		{
		case SPHERE:
			return intersection_sphere(ray);
			break;
		case BOX:
			return NO_INTERSECTION;
			break;
		case TRIANGLE:
			return NO_INTERSECTION;
			break;
		default:
			return NO_INTERSECTION;
			break;
		}

		return NO_INTERSECTION;
	}

	Vector3 getSurfaceNormal(Vector3 pos) {
		switch (type)
		{
		case SPHERE:
			return manager.vecDivideScaler(manager.vecSubtract(pos, position), radius);
			break;
		case BOX:
			break;
		case TRIANGLE:
			break;
		default:
			break;
		}
	}

private: 
	INTERSECTION_CASE intersection_sphere(Ray ray) {
		/* I learned and used this intersection function from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		A reference source I used while making this function was from https://www.codeproject.com/Articles/19799/Simple-Ray-Tracing-in-C-Part-II-Triangles-Intersec
		and https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/, which helped me out a lot
		*/
		Vector3 ray_calculation = manager.vecSubtract(ray.position, position);
		float a = manager.getDotProduct(manager.getNormalizedVector(ray.position), manager.getNormalizedVector(ray.position));
		float b = 2.0 * manager.getDotProduct(ray_calculation, manager.getNormalizedVector(ray.position));
		float c = manager.getDotProduct(ray_calculation, ray_calculation) - radius*radius;
		float d = b*b - 4 * a*c;

		t = -1;

		if (d >= 0) {
			float t1 = (-b - sqrt(d)) / 2 * a;
			float t2 = (-b + sqrt(d)) / 2 * a;

			if (t1 > t2) {
				t = t1;
			}
			else { 
				t = t2;
			}

			hit_position = manager.vecAdd(ray.position, manager.vecMultiplyScaler(manager.vecSubtract(ray.position, ray.position), t));
			hit_position.y = abs(hit_position.y);

			if (t1 > 1 || t2 > 1) {
				hit_position = manager.vector3(0, 0, 0);
				return NO_INTERSECTION;
			}
			else {
				return INTERSECTED_ONE;
			}

		}

		return NO_INTERSECTION;
	}
};

#endif OBJECT_DEF