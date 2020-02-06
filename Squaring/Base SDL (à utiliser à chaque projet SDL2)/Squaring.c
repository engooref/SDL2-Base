/*
 ============================================================================
 Name        : Squaring.c
 Author      : Armand
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */


#include "app.h"


int main(int argc, char* argv[]) {
	printf("===================ENTER SQUARING===========================\n");

		if(AppNew(WINDOW_TITLE_STR) == EXIT_FAILURE)
		{
			fprintf(stderr, "Failed to initialize App! Program aborted!\n");
			printf("=========Exit Squaring WITH FAILURE==================\n");
			return EXIT_FAILURE;
		}
		AppRun();
		AppDel();
	printf("===================EXIT  SQUARING===========================\n");
		return EXIT_SUCCESS;
}
