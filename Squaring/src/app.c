/*
 * app.c
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */


#include "app.h"
#include "square.h"

Uint32 _AppAnimateCallBack(Uint32 interval, void*pParam);
void   _AppCreateSquare(int x, int y);
void _AppMouseButtonUp(SDL_Event*pEvent);
void _AppDeleteSquare(void);

enum APP_STATUS {
	ST_ALL_CLEARED = 0x00000000,
	ST_ALL_SETTED  = 0xFFFFFFFF,
};

static struct {
	Uint32				nStatus;
	Uint32				nWindowID;
	SDL_Window		*	pWindow;
	SDL_Renderer    *	pRenderer;
	SDL_Color			colorBkgnd;
	SDL_Point			windowSize;
	SDL_TimerID			nTimerID;


	//struct s_square *  pSquares[NB_SQUARES];
	struct s_square *	pSquares;
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
	app.pSquares 		= NULL;

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
	SDL_GetWindowSize(app.pWindow, &app.windowSize.x, &app.windowSize.y);

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


	/*SDL_Point speed;

	for(int nbCreateSquares = 0; nbCreateSquares < NB_SQUARES; nbCreateSquares++) {
		do {
		speed.x = rand() % (SPEED_MAX - SPEED_MIN + 1) - SPEED_MAX;
		speed.y = rand() % (SPEED_MAX - SPEED_MIN + 1) - SPEED_MAX;
		} while(speed.x == 0 || speed.y == 0);

		app.pSquares[nbCreateSquares] = SquareNew(NULL,
									rand() % (app.windowSize.x - SQUARE_SIZE),
									rand() % (app.windowSize.y - SQUARE_SIZE),
									SQUARE_SIZE,
									speed.x,
									speed.y,
									rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
									rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
									rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
									rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN);

		app.pSquares[nbCreateSquares] = SquareDraw(app.pSquares[nbCreateSquares], app.pRenderer);

	}*/
	SDL_RenderPresent(app.pRenderer);



	app.nTimerID = SDL_AddTimer(ANIMATION_TICK, _AppAnimateCallBack, NULL);

	return 0;
}

int AppDel(void){

	/*for(int k = 0; k < NB_SQUARES; k++){
		if(app.pSquares[k] != NULL)
			app.pSquares[k] = SquareDel(app.pSquares[k], app.pRenderer, app.colorBkgnd);
	}*/

	while(app.pSquares != NULL)
	{
		app.pSquares = SquareDel(app.pSquares, app.pRenderer, app.colorBkgnd);
	}

	SDL_RemoveTimer(app.nTimerID);

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
				case SDLK_SPACE:
					_AppCreateSquare(rand() % (app.windowSize.x - SQUARE_SIZE), rand() % (app.windowSize.y - SQUARE_SIZE));
					break;
				case SDLK_BACKSPACE:
							_AppDeleteSquare();
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				 _AppMouseButtonUp(&event);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

Uint32 _AppAnimateCallBack(Uint32 interval, void*pParam){

	/*for(int k = 0; k < NB_SQUARES; k++){
		if(app.pSquares[k] != NULL)
			SquareMove(app.pSquares[k], app.pRenderer, app.colorBkgnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	}*/

	struct s_square* pScan;
	pScan = app.pSquares;
	while(pScan != NULL) {
		pScan = SquareMove(pScan, app.pRenderer, app.colorBkgnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	SDL_RenderPresent(app.pRenderer);
	return interval;
}

void _AppCreateSquare(int x, int y){


	SDL_Point speed;

	do {
	speed.x = rand() % (SPEED_MAX - SPEED_MIN + 1) - SPEED_MAX;
	speed.y = rand() % (SPEED_MAX - SPEED_MIN + 1) - SPEED_MAX;
	} while(speed.x == 0 || speed.y == 0);


	if(app.pSquares == NULL) {

		app.pSquares = SquareNew(
						NULL,
						x,
						y,
						SQUARE_SIZE,
						speed.x,
						speed.y,
						rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
						rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
						rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
						255
					);

		app.pSquares = SquareDraw(app.pSquares, app.pRenderer);

	} else {
		struct s_square* pScan;
		pScan = app.pSquares;
		while(SquareNext(pScan) != NULL) { pScan = SquareNext(pScan); }

		SquareAdd(pScan, SquareNew(
							NULL,
							x,
							y,
							SQUARE_SIZE,
							speed.x,
							speed.y,
							rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
							rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
							rand() % (COLOR_MAX - COLOR_MIN + 1) - COLOR_MIN,
							255
						)
		);
	}


}

void _AppMouseButtonUp(SDL_Event*pEvent) {

	if (pEvent->button.button != SDL_BUTTON_LEFT) return;

	int x, y;

	x = pEvent->motion.x;
	y = pEvent->motion.y;

	_AppCreateSquare(x, y);
}

void _AppDeleteSquare(void){

}
