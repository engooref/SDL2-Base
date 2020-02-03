/*
 * app.c
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */


#include "app.h"
#include "square.h"

enum APP_STATUS {
	ST_ALL_CLEARED = 0x00000000,
	ST_ALL_SETTED  = 0xFFFFFFFF,
};

static struct {
	Uint32				nStatus;
	Uint32				nWindowID;
	SDL_Window*			pWindow;
	SDL_Renderer*		pRenderer;
	SDL_Color			colorBkgnd;
	SDL_Point			windowSize;
	SDL_TimerID			nTimerID;
}app;

int AppNew(char*strWinTitle){
	app.nStatus			= ST_ALL_CLEARED;
	app.nWindowID		= -1;
	app.pRenderer		= NULL;
	app.pWindow			= NULL;
	app.colorBkgnd.r	= 0;
	app.colorBkgnd.g	= 0;
	app.colorBkgnd.b	= 0;
	app.colorBkgnd.a	= 255;

	srand((unsigned int)time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	app.pWindow = SDL_CreateWindow(
			strWinTitle,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
	);

	if (app.pWindow == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	app.nWindowID = SDL_GetWindowID(app.pWindow);
	app.pRenderer = SDL_CreateRenderer(app.pWindow,-1, SDL_RENDERER_ACCELERATED);
	if(app.pRenderer==NULL) {
		fprintf(stderr, "Failed to create accelerated renderer.\n");
		app.pRenderer = SDL_CreateRenderer(app.pWindow,-1, SDL_RENDERER_SOFTWARE);
		if(app.pRenderer==NULL){
			fprintf(stderr, "Failed to create software renderer.\n");
			SDL_DestroyWindow(app.pWindow);
			SDL_Quit();
			app.pWindow = NULL;
			return EXIT_FAILURE;
		}
		fprintf(stderr, "Software renderer created instead!\n");
	}

	return 0;
}

int AppDel(void){

	if(app.pWindow){
		SDL_DestroyWindow(app.pWindow);
		app.pWindow = NULL;
	}
	if(app.pRenderer){
		SDL_DestroyRenderer(app.pRenderer);
		app.pRenderer = NULL;
	}
	app.nWindowID = -1;
	SDL_Quit();
	return 0;
}

int AppRun(void){

	int quit;
	SDL_Event event;

	quit = 0;

	while(!quit){
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_WINDOWEVENT:
				if (event.window.windowID != app.nWindowID) break;
				switch (event.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
					event.type = SDL_QUIT;
					SDL_PushEvent(&event);
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
						quit =1;
						break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
