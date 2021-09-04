#include "Particle.h"
#include <cmath>
#include <iostream>

Particle::Particle(int mass, Vector2f position, Vector2f velocity, int radius, Color color) {
	this->mass_ = mass;
	this->position_ = position;
	this->velocity_ = velocity;
	this->radius_ = radius;
	this->color_ = color;
}

void Particle::move() {
	position_.x += velocity_.x / 60;
	position_.y += velocity_.y / 60;
}

void Particle::applyForce(Vector2f force) {
	velocity_.x += force.x / (60 * mass_);
	velocity_.y += force.y / (60 * mass_);
}

void Particle::collideParticle(Particle& p) {  // Aplica formula de fisica 1 (Colision elastica)
	double distance = sqrt(pow(p.getPosition().x - position_.x, 2) + pow(p.getPosition().y - position_.y, 2));

	if (distance <= (double)radius_ + (double)p.getRadius()) {
		float massItem1 = 2 * p.getMass() / (mass_ + p.getMass());
		float vx1 = velocity_.x, vx2 = p.getVelocity().x;
		float x1 = position_.x, x2 = p.getPosition().x;

		float vy1 = velocity_.y, vy2 = p.getVelocity().y;
		float y1 = position_.y, y2 = p.getPosition().y;
		float norm = pow(x1 - x2, 2) + pow(y1 - y2, 2);
		float dotProduct1 = (vx1 - vx2) * (x1 - x2) + (vy1 - vy2) * (y1 - y2);

		velocity_.x = vx1 - massItem1 * dotProduct1 * (x1 - x2) / norm;
		velocity_.y = vy1 - massItem1 * dotProduct1 * (y1 - y2) / norm;

		float massItem2 = 2 * mass_ / (mass_ + p.getMass());
		float dotProduct2 = (vx2 - vx1) * (x2 - x1) + (vy2 - vy1) * (y2 - y1);

		float velocity2x = vx2 - massItem2 * dotProduct2 * (x2 - x1) / norm;
		float velocity2y = vy2 - massItem2 * dotProduct2 * (y2 - y1) / norm;
		p.setVelocity(Vector2f(velocity2x, velocity2y));

		// To avoid colliding into each other constantly
		Vector2f distanceDirection(abs(position_.x - p.getPosition().x), abs(position_.y - p.getPosition().y));
		if (position_.x > p.getPosition().x) distanceDirection.x *= -1;
		if (position_.y > p.getPosition().y) distanceDirection.y *= -1;

		float velocityNorm1 = sqrt(pow(p.getVelocity().x, 2) + pow(p.getVelocity().y, 2)) / 60;
		float velocityNorm2 = sqrt(pow(p.getVelocity().x, 2) + pow(p.getVelocity().y, 2)) / 60;
		addPosition(-distanceDirection, velocityNorm1);
		p.addPosition(distanceDirection, velocityNorm2);
	}
}

void Particle::collideWall(Wall w) {  // Hecho con matrices de rotacion
	float speedPerp = cos(w.rotationAngle()) * velocity_.x + -sin(w.rotationAngle()) * velocity_.y;  // La pared refleja la velocidad perpendicular
	float speedNorm = sin(w.rotationAngle()) * velocity_.x + cos(w.rotationAngle()) * velocity_.y;

	velocity_.x = cos(-w.rotationAngle()) * speedPerp + -sin(-w.rotationAngle()) * speedNorm;
	velocity_.y = sin(-w.rotationAngle()) * speedPerp + cos(-w.rotationAngle()) * speedNorm;
}

void Particle::addPosition(Vector2f direction, float magnitude) {
	float norm = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	position_.x += direction.x * magnitude / norm;
	position_.y += direction.y * magnitude / norm;
}

CircleShape Particle::getShape() {
	CircleShape shape(radius_);
	shape.setOrigin(Vector2f(radius_, radius_));
	shape.setPosition(position_);
	shape.setFillColor(color_);

	return shape;
}
