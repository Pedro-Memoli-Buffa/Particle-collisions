#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Wall.h"
using namespace std;
using namespace sf;

class ParticleCollection {
public:
	ParticleCollection(int numberOfParticles);

	void moveParticles();
	void checkCollisions(const vector<Wall>& walls = {}, bool friction = false);
	void sortParticles();

	void draw(RenderWindow& window);

private:
	vector<Particle> particles_;
};

