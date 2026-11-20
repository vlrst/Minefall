#pragma once 
#include <SDL3/SDL.h>
#include <string>

class Object { 
	public:
		std::string name;
		int x, y, angle;
		float spriteSize, speedX, speedY;
		SDL_Texture* texture;
		SDL_FRect destination;
		SDL_FRect src;
		Object(SDL_Texture* texture, SDL_FRect src, SDL_FRect destination); 
		Object(std::string name);
		void setStartPosition(int x, int y, float spriteSize);
		void changeSpeed(int x, int y);
		void setSpeed(int x, int y);
		void updatePosition();
};


