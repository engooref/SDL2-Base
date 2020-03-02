/*
 * square.c
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */

#include "square.h"
#include "app.h"

struct s_square {
	SDL_Color 			color;
	SDL_Rect 			frame;
	SDL_Point 			speed;
	int					nbCollision;
	struct s_square*	pNext;
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

	pSquareNew->nbCollision = 0;

	pSquareNew->pNext = NULL;

	return pSquareNew;
}


struct s_square*SquareDel(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color	 colorBkgnd
) {
	struct s_square* pNext;
	pNext = pSquare->pNext;

	SquareHide(pSquare, pRenderer, colorBkgnd);
	//SDL_RenderPresent(pRenderer);
	free(pSquare);

	return pNext;
}

struct s_square*SquareDraw(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer
){
	SDL_SetRenderDrawColor(pRenderer, pSquare->color.r, pSquare->color.g , pSquare->color.b , pSquare->color.a);
	SDL_RenderFillRect(pRenderer, &pSquare->frame);

	return pSquare->pNext;
 }

struct s_square*SquareHide(
		struct s_square*pSquare,
		SDL_Renderer*pRenderer,
		SDL_Color colorBkgnd
){
	SDL_SetRenderDrawColor(pRenderer, colorBkgnd.r, colorBkgnd.g, colorBkgnd.b, colorBkgnd.a);
		SDL_RenderFillRect(pRenderer, &pSquare->frame);
		return pSquare->pNext;
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
	if((pSquare->frame.x < 0) || (pSquare->frame.x >= iWmax - pSquare->frame.w)) pSquare->speed.x *= -1;

	pSquare->frame.y += pSquare->speed.y;
	if((pSquare->frame.y < 0) || (pSquare->frame.y >= iHmax - pSquare->frame.h)) pSquare->speed.y *= -1;

	SquareDraw(pSquare, pRenderer);

	return pSquare->pNext;
}

struct s_square*SquareNext(struct s_square*pSquare){
	return pSquare->pNext;
}

struct s_square*SquareAdd(struct s_square*pSquare, struct s_square*pNew){
	pSquare->pNext = pNew;
	return pSquare->pNext;
}

struct s_square*SquareCollision(struct s_square*	pSquareA,
								struct s_square*	pSquareB,
								struct s_square* 	pSquare,
								SDL_Renderer   *	pRenderer,
								SDL_Color 			colorBkgnd) {


	struct s_square*pScan;

	if(SDL_HasIntersection(&pSquareA->frame, &pSquareB->frame)) {
		pSquareA->speed.x *= -1;
		pSquareA->speed.y *= -1;

		/*pSquareB->speed.x *= -1;
		pSquareB->speed.y *= -1;
	*/
		pScan = pSquareA;

		/*if ( (pSquareA->frame.h <= (SQUARE_SIZE * 2)) && (pSquareA->frame.w <= (SQUARE_SIZE * 2)) ) {
					pSquareA->frame.h += pSquareB->frame.h;
					pSquareA->frame.w += pSquareB->frame.w;

		}
		else {
			pSquareA->frame.h = SQUARE_SIZE ;
			pSquareA->frame.w = SQUARE_SIZE ;
			SDL_RenderPresent(pRenderer);
		}*/
		while(pScan->pNext != pSquareB) {pScan = pScan->pNext; }

		pScan->pNext = SquareDel(pSquareB, pRenderer, colorBkgnd);
		pSquareA->nbCollision++;
		pSquareB =pScan;


		if(pSquareA->nbCollision == 10) {
			pScan = pSquare;
			while(pScan->pNext != pSquareA) {pScan = pScan->pNext; }
			pScan->pNext = SquareDel(pSquareA, pRenderer, colorBkgnd);
		}
	}
	return pSquareB->pNext;
}
