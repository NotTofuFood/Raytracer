#include <SFML/Graphics.hpp>
#include <stdint.h>
#include <vector>
#include <iostream>
#include "Object.h"
#include "Light.h"

#define WIDTH			1080
#define HEIGHT			1020
#define TORADS			0.01745
#define FOV				90

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Raytracer by Aiden Thakurdial (NotTofuFood)");

sf::Image buffer;
sf::Texture buffer_texture;
sf::Sprite buffer_render;

vec3 manager;

Ray rays[WIDTH][HEIGHT];

size_t amount_of_objects = 3;
std::vector<Object> objects(amount_of_objects);

size_t amount_of_lights = 1;
std::vector<Light> lights(amount_of_lights);

void init(void);
void trace(void);
void render(void);

int main()
{

	init();
	trace();

	render();

	return 0;
}

void init() {
	srand(time(NULL));
	buffer.create(WIDTH, HEIGHT, sf::Color::Black);

	for (uint16_t row = 0; row < WIDTH; row++) {
		for (uint16_t col = 0; col < HEIGHT; col++) {
			float dir_x = (row + 0.5) - WIDTH / 2.;
			float dir_y = (col + 0.5) - HEIGHT / 2.;
			float dir_z = -HEIGHT / (2.*tan(FOV*TORADS / 2.));
			rays[row][col] = Ray(manager.vector3(dir_x, dir_z, dir_y));
		}
	}

	for (uint16_t i = 0; i < amount_of_objects; i++) {
		objects[i] = Object(OBJECT_TYPE::SPHERE, manager.vector3(i*64, 200, 0), manager.vector3(0, 0, 255));
		objects[i].radius = 60;
		objects[i].diffuse_strength = 0.9;
	}

	for (uint16_t i = 0; i < amount_of_lights; i++) {
		lights[i] = Light(manager.vector3(255, 255, 255), manager.vector3(-10, -10, 70));
	}
}

void trace() {

	for (uint16_t row = 0; row < WIDTH; row++) {
		for (uint16_t col = 0; col < HEIGHT; col++) {
			buffer.setPixel(row, col, sf::Color(135, 206, 235));
		}
	}

	for (uint16_t i = 0; i < amount_of_objects; i++) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			objects[i].position.z-=10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			objects[i].position.z += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			objects[i].position.x -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			objects[i].position.x += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			objects[i].position.y -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			objects[i].position.y += 10;
		}
	}


	for (uint16_t i = 0; i < amount_of_lights; i++) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			lights[i].position.z -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			lights[i].position.z += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			lights[i].position.x -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			lights[i].position.x += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			lights[i].position.y -= 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			lights[i].position.y += 10;
		}
	}

	for (uint16_t row = 0; row < WIDTH; row++) {
		for (uint16_t col = 0; col < HEIGHT; col++) {
			for (uint16_t i = 0; i < amount_of_objects; i++) {
				if ((objects[i].check_intersection(rays[row][col]) == INTERSECTED_ONE) | (objects[i].check_intersection(rays[row][col]) == INTERSECTED_TWO)) {
					for (uint16_t light = 0; light < amount_of_lights; light++) {
						Vector3 pixel_color = lights[light].getLightingColor(objects[i], rays[row][col]);
						buffer.setPixel(row, col, sf::Color(pixel_color.x, pixel_color.y, pixel_color.z));
					}
				}
			}
		}
	}

	buffer_texture.loadFromImage(buffer);
	buffer_render.setTexture(buffer_texture, true);
}

void render() {
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{

			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(buffer_render);
		//trace();

		window.display();
	}
}