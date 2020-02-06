/*
 * square.c
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */

#include "square.h"

struct s_square {
	SDL_Color color;
	SDL_Rect frame;
	SDL_Point speed;
};

struct s_square*SquareNew(
						struct 	s_square*pSquare,
						int 	iLocX,
						int		iLocY,
						int		iSize,
						int		iSpeedX,
						int		iSpeedY,
						Uint8	uRed,
						Uint8	uGreen,
						Uint8	uBlue,
						Uint8	uAlpha
) {
	struct s_square* pSquareNew;
	pSquareNew = (struct s_square*) malloc(sizeof(struct s_square));

	pSquareNew->frame.x = iLocX;
	pSquareNew->frame.y = iLocY;

	pSquareNew->frame.h = iSize;
	pSquareNew->frame.w = iSize;

	pSquareNew->speed.x = iSpeedX;
	pSquareNew->speed.y = iSpeedY;

	pSquareNew->color.r = uRed;
	pSquareNew->color.g = uGreen;
	pSquareNew->color.b = uBlue;
	pSquareNew->color.a = uAlpha;

	return pSquareNew;
}


struct s_square*SquareDel(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd
) {
	SquareHide(pSquare, pRenderer, colorBkgnd);
	SDL_RenderPresent(pRenderer);
	free(pSquare);

	return NULL;
}

struct s_square*SquareDraw(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer
){
	SDL_SetRenderDrawColor(pRenderer, pSquare->color.r, pSquare->color.g , pSquare->color.b , pSquare->color.a);
	SDL_RenderFillRect(pRenderer, &pSquare->frame);
	return pSquare;
 }

struct s_square*SquareHide(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color colorBkgnd
){
	SDL_SetRenderDrawColor(pRenderer, colorBkgnd.r, colorBkgnd.g, colorBkgnd.b, colorBkgnd.a);
		SDL_RenderFillRect(pRenderer, &pSquare->frame);
		SDL_RenderPresent(pRenderer);
		return pSquare;
}

struct s_square*SquareMove(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd,
		int			 iWmax,
		int			 iHmax
){

	SquareHide(pSquare, pRenderer, colorBkgnd);

	pSquare->frame.x += pSquare->speed.x;
	if((pSquare->frame.x < 0) || (pSquare->frame.x > iWmax)) pSquare->frame.x *= -1;

	pSquare->frame.y += pSquare->speed.y;
	if((pSquare->frame.y < 0) || (pSquare->frame.y > iHmax)) pSquare->frame.y *= -1;

	SquareDraw(pSquare, pRenderer);

	return pSquare;
}

