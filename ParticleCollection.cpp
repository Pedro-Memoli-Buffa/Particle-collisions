#include "ParticleCollection.h"

Color rgb(double ratio)  // Getting rainbow color array
{
	//we want to normalize ratio so that it fits in to 6 regions
	//where each region is 256 units long
	int normalized = int(ratio * 256 * 6);

	//find the distance to the start of the closest region
	int x = normalized % 256;

	int red = 0, grn = 0, blu = 0;
	switch (normalized / 256)
	{
	case 0: red = 255;      grn = x;        blu = 0;       break;  //red
	case 1: red = 255 - x;  grn = 255;      blu = 0;       break;  //yellow
	case 2: red = 0;        grn = 255;      blu = x;       break;  //green
	case 3: red = 0;        grn = 255 - x;  blu = 255;     break;  //cyan
	case 4: red = x;        grn = 0;        blu = 255;     break;  //blue
	case 5: red = 255;      grn = 0;        blu = 255 - x; break;  //magenta
	}

	return Color(red, grn, blu);
}

void ParticleCollection::sortParticles() {  // Applies insertion sort (will generally work at O(n) due to frames being so similar)
	for (int i = 0; i < particles_.size() - 1; i++) {
		int j = i + 1;
		while (j > 0 && (particles_[j].getPosition().x - particles_[j].getRadius()) < 
			(particles_[j - 1].getPosition().x - particles_[j - 1].getRadius())) {
			Particle metaParticle = particles_[j];
			particles_[j] = particles_[j - 1];
			particles_[j - 1] = metaParticle;

			j--;
		}
	}
}

ParticleCollection::ParticleCollection(int numberOfParticles) {
	for (int i = 0; i < numberOfParticles; i++) {
		int maxSpeed = 400;
		Vector2f position(rand() % 790 + 5, rand() % 590 + 5);
		Vector2f velocity(rand() % maxSpeed * 2 - maxSpeed, rand() % maxSpeed * 2 - maxSpeed);
		int mass = 4; // rand() % 2 + 4;
		int radius = 13; // rand() % 8 + 6; //4 + 3 * (mass - 2) / 5;

		particles_.push_back(Particle(mass, position, velocity, radius, rgb((float)i / 50)));
	}
}

void ParticleCollection::moveParticles() {	// Possible force application 
	for (int i = 0; i < particles_.size(); i++) {
		particles_[i].move();
		particles_[i].applyForce(Vector2f(0, 1000));
	}
}

void ParticleCollection::checkCollisions(const vector<Wall>& walls, bool friction) {  // Using sweep and prune
	sortParticles();

	for (int i = 0; i < particles_.size(); i++) {
		// For particles
		float particle1Radius = particles_[i].getRadius();
		float particle1Position = particles_[i].getPosition().x;

		for (int j = i + 1; j < particles_.size(); j++) {
			float particle2Radius = particles_[j].getRadius();
			float particle2Position = particles_[j].getPosition().x;

			if (particle2Position - particle2Radius <= particle1Position + particle1Radius) {
				particles_[i].collideParticle(particles_[j]);
			}
			else break;
		}

		// For walls
		Vector2f particleVelocity = particles_[i].getVelocity();
		float velocityNorm = sqrt(pow(particleVelocity.x, 2) + pow(particleVelocity.y, 2)) / 60;

		if (particles_[i].getPosition().x - particles_[i].getRadius() <= 0 ||    // Left border
			particles_[i].getPosition().x + particles_[i].getRadius() >= 800) {  // Right border
			particles_[i].setVelocity(Vector2f(-particleVelocity.x, particleVelocity.y));
			particles_[i].addPosition(particles_[i].getVelocity(), velocityNorm);
		}
		if (particles_[i].getPosition().y - particles_[i].getRadius() <= 0 ||    // Top border
			particles_[i].getPosition().y + particles_[i].getRadius() >= 600) {  // Bottom border
			particles_[i].setVelocity(Vector2f(particleVelocity.x, -particleVelocity.y));
			particles_[i].addPosition(particles_[i].getVelocity(), velocityNorm);

			if (friction && particleVelocity.y > 0) {
				particles_[i].applyForce(Vector2f(-particles_[i].getVelocity().x * 30, -particles_[i].getVelocity().y * 30));
				if (abs(particleVelocity.x) < 90 && abs(particleVelocity.y) < 90) particles_[i].setVelocity(Vector2f(0, 0));
			}
		}
	}
}

void ParticleCollection::draw(RenderWindow& window) {
	for (const Particle& particle : particles_) {
		window.draw(particle.getShape());
	}
}
