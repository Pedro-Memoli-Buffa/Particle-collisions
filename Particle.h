#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Wall.h"
using namespace std;
using namespace sf;

class Particle {
public:
	Particle(int mass, Vector2f position, Vector2f velocity, int radius, Color color);

	void applyForce(Vector2f force);
	void move();

	void collideParticle(Particle&);
	void collideWall(Wall);

	Vector2f getVelocity() { return velocity_; }
	Vector2f getPosition() { return position_; }
	int getRadius() { return radius_; }
	int getMass() { return mass_; }
	void setColor(Color color) { color_ = color; }
	void setVelocity(Vector2f newVelocity) { velocity_ = newVelocity; }
	void addPosition(Vector2f direction, float magnitude);

	CircleShape getShape() const;

private:
	int mass_;
	int radius_;
	Color color_;
	Vector2f position_;
	Vector2f velocity_;
};
