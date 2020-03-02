/*
 * square.h
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

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
);

struct s_square*SquareDel(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd
);

struct s_square*SquareDraw(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer
);


struct s_square*SquareHide(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd
);

struct s_square*SquareMove(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd,
		int			 iWmax,
		int			 iHmax
);

struct s_square*SquareNext(struct s_square*pSquare);

struct s_square*SquareAdd(struct s_square*pSquare, struct s_square*pNew);

struct s_square*SquareCollision(struct s_square*	pSquareA,
								struct s_square*	pSquareB,
								struct s_square*	pSquare,
								SDL_Renderer   *	pRenderer,
								SDL_Color 			colorBkgnd);
