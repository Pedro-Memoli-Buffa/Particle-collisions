#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Wall {
public:
	Wall(Vector2f topLeft, Vector2f topRight, int width);

	float rotationAngle();
	RectangleShape getShape();

private:
	Vector2f topLeftPosition_;
	Vector2f topRightPosition_;
	int width_;
};

