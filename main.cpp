#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ParticleCollection.h"
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Particle Collision", Style::Close | Style::Resize);
    ParticleCollection collection(50);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case Event::Closed:
                window.close();
                break;
            }
        }

        collection.moveParticles();
        collection.checkCollisions();
        
        // Drawing
        window.clear();
        
        collection.draw(window);

        window.display();
    }

    return 0;
}
