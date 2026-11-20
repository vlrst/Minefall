#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "../include/Minefall.hpp"
#include "../include/Object.hpp"
#include <iostream>
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800


struct SDL_State {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width, height, logW, logH;
};

bool initialize(SDL_State &state);
void cleanup(SDL_State &state);

void grun() {

	SDL_State state;
	state.width = 480;
	state.height = 800;
	state.logW = 480;
	state.logH = 800;
	if (!initialize(state)) {
		printf("INITIALIZATION ERROR");
	}
	Object* dynamite = new Object("Dynamite");
	SDL_Texture* idleTex = IMG_LoadTexture(state.renderer, "./images/transparent/dynamite.png"); // make the file in respect to where you are building the project 
	if (!idleTex) {

		printf("DYNAMITE TEXTURE ERROR");
	}

	dynamite->texture = idleTex;

	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST); 
	// sdl texture loaded on gpu and sdl_surface loaded on system memory

	const bool* keys = SDL_GetKeyboardState(nullptr);
	float playerX = 200;
	float playerY = 200;
	const float floor = state.logH;
	uint64_t prevTime = SDL_GetTicks();
	bool running = true;
	while(running) {
		uint64_t nowTime = SDL_GetTicks(); // time between frames in m/s
		float deltaTime = (nowTime - prevTime) / 1000.0f; // converting to secs	
		SDL_Event event{0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;

				case SDL_EVENT_WINDOW_RESIZED: // maintain aspect ratio
					state.width = event.window.data1;
					state.height = event.window.data2;
					break;
			} 
		}
	
	// do time based movement instead of frame based movement because different people have different hardware leading to different frame rates

	float moveAmount = 0;
	//float horizontalSpeed = 75.f;
	dynamite->setSpeed(75, 0); // do not set this to any value to avoid double counting
									// if i hold both the left and right, it will go left at double the speed (considering the speed is +75)
	if (keys[SDL_SCANCODE_A]) {
		std::cout << "A\n";
		//moveAmount += -horizontalSpeed;
		//dynamite->setSpeed(-dynamite->speedX, 0);
		dynamite->setSpeed(-75, 0); 
		dynamite->updatePosition();
		
	}
	if (keys[SDL_SCANCODE_D]) {
		std::cout << "D\n";
		//moveAmount += horizontalSpeed;
		dynamite->setSpeed(dynamite->speedX, 0); // change func from changeSpeed to setSpeed()
		dynamite->setSpeed(75, 0);
		dynamite->updatePosition();
	} 
	//dynamite->x += moveAmount * deltaTime;
	std::cout << dynamite->x << std::endl;
	//dynamite->updatePosition();
	
	//playerX += moveAmount * deltaTime;

	
	// draw
	SDL_SetRenderDrawColor(state.renderer, 150, 111, 109, 255);
	
	SDL_RenderClear(state.renderer);
	const float spriteSize = 128.f;
	dynamite->spriteSize = 128.f;
	//SDL_FRect src {
	dynamite->src = {
		.x = 0,
		.y = 0,
		.w = spriteSize,
		.h = spriteSize
	} ;
	

	// sizing
	
	dynamite->destination = { 
	//SDL_FRect destination {
	
	 	.x = float(dynamite->x)/20,
		/*.y = floor - spriteSize,*/
		.y = float(dynamite->y),
		.w = spriteSize,
		.h = spriteSize
	}; 
	
	
	//SDL_RenderTexture(state.renderer, idleTex, &src, nullptr);
	//SDL_RenderTexture(state.renderer, idleTex, nullptr, &destination); 
	/*SDL_RenderTextureRotated(
			state.renderer,
			idleTex,
			nullptr,
			&destination,
			-90.0,
			nullptr,
			SDL_FLIP_NONE
			);
	*/
	SDL_RenderTextureRotated(
			state.renderer,
			dynamite->texture,
			nullptr,
			&dynamite->destination,
			-90.0f,
			nullptr,
			SDL_FLIP_NONE
			 );
	SDL_RenderPresent(state.renderer);
	prevTime = nowTime;
	}
	// free the vram used from textures
	SDL_DestroyTexture(dynamite->texture);
	cleanup(state);
	
} 


void cleanup(SDL_State &state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
} 

bool initialize(SDL_State &state) {
	bool initialization = true;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		initialization = false;
	}

	state.window = SDL_CreateWindow("Minefall", state.width, state.height, SDL_WINDOW_RESIZABLE);

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
		cleanup(state);
		initialization = false;
	}

	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", state.window);
		initialization = false;
	}

	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	return initialization;	
}

