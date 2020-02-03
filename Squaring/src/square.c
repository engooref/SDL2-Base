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
	struct s_square* pSquareDel;

	pSquareDel = pSquare;



	free(pSquareDel);
	pSquareDel = NULL;

	return pSquareDel;
}
