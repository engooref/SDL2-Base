/*
 * square.h
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */

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
