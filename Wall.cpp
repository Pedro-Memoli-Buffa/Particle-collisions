#include "Wall.h"

Wall::Wall (Vector2f topLeft, Vector2f topRight, int width) {

}

float Wall::rotationAngle() {
	return 3;
}

RectangleShape Wall::getShape() {
	return RectangleShape();
}