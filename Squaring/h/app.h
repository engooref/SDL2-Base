/*
 * app.h
 *
 *  Created on: 3 févr. 2020
 *      Author: eleve
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WINDOW_TITLE_STR	 "Squaring It!"
#define SCREEN_WIDTH 		 (640*5.0/3.0)
#define SCREEN_HEIGHT 		 (480*5.0/3.0)
#define ANIMATION_TICK		 (16)
#define SQUARE_SIZE		     30
#define NB_SQUARES			 0
#define SPEED_MIN			 -10
#define SPEED_MAX			 10
#define COLOR_MIN			 50
#define COLOR_MAX			 250

#define mBitsSet(f,m)		 ((f)|=(m))
#define mBitsClr(f,m)		 ((f)&=(~(m)))
#define mBitsTgl(f,m)		 ((f)^=(m))
#define mBitsMsk(f,m)		 ((f)& (m))
#define mIsBitsSet(f,m)		 (((f)&(m))==(m))
#define mIsBitsClr(f,m)		 (((~(f))&(m))==(m))

int AppNew(char*strWinTitle);
int AppDel(void);
int AppRun(void);
