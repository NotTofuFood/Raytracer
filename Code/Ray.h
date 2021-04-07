#ifndef RAY_DEF
#define RAY_DEF
#include "vec3.h"
#include "Object.h"

class Ray {
public:
	Vector3 position;

	vec3 manager;

	Ray() {}

	Ray(Vector3 position) {
		this->position = position;
	}
};

#endif RAY_DEF