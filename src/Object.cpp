#include "../include/Object.hpp"
#include <SDL3/SDL.h>
#include <string>

Object::Object(std::string name) {
	this->name = name;
} 	
Object::Object(SDL_Texture* texture, SDL_FRect src, SDL_FRect destination) {
	this->texture = texture;
	this->destination = destination;
	this->src = src;
} 
void Object::setStartPosition(int x, int y, float spriteSize) {
	this->x = x;
	this->y = y;
	this->spriteSize = spriteSize;
} 

void Object::changeSpeed(int x, int y) {
	this->speedX += x;
	this->speedY += y;

}

void Object::setSpeed(int x, int y) {
	this->speedX = x;
	this->speedY =y;
}

void Object::updatePosition() {
	this->x += this->speedX;
	this->y += this->speedY;
} 	

