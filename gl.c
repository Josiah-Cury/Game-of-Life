/**
 * @file gl.c
 * @brief Conway's Game of Life
 * @details Takes user's input in the command line using getopt.
 * Initializes the matrixes and begins to use sdl to display the game.
 * Offers several options for border, color of sprites, sprite size, width
  * and height of the screen, and life initialization pattern. 
 * @author Josiah Cury
 * @date 4/29/2019
 * @todo Implement more error checking to make sure the initialization pattern
 * and the origin are within parameters.
 * @bug there is little error checking, so if someone tries to set a point
 * that is out of bounds, then the program crashes.
 */

#include <stdlib.h>
#include "SDL2/SDL.h" 
#include "sdl.h"
#include "life.h"
#include <unistd.h> /* used for getopt */
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int width = 800;
	int height = 600;
	int sprite_size = 2; /* either 2, 4, 8, or 16 */
	//int m = -66;
	//int n = -10;
	int ws;
	int hs;
        /* colors are RGB model valid values [0, 255] */
	unsigned char red = 100;
	unsigned char green = 100;
	unsigned char blue = 250;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

	/* your life initialization code here */
	unsigned char **A, **B;
	int i, j;
	
	int x, y;
	char buf[1000];
	
	int c;
	char *border;
	
	FILE *fp = NULL;
	
	if (argc == 1) {
		printf("use -H for help\n");
		return 0;
	}
	//sample command line argument:./life -w 800 -h 600 2s 4 -r 100 -g 250 -b 0 -e torus -o 60,60 -f ./conway/acorn_106.lif
	//getopt logic
	while((c = getopt(argc, argv, ":w:h:e:r:g:b:s:f:o:H")) != -1) {
		switch(c) {
		case 'w':
			width = atoi(optarg);
			break;
		case 'h':
			height = atoi(optarg);
			break;
		case 'e':
			border = optarg;
			break;
		case 'r':
			red = atoi(optarg);
			break;
		case 'g':
			green = atoi(optarg);
			break;
		case 'b':
			blue = atoi(optarg);
			break;
		case 's':
			sprite_size = atoi(optarg);
			break;
		case 'f':
		
			ws = (width / sprite_size);
			hs = (height / sprite_size);
			A = init_matrix(ws, hs);

			B = init_matrix(ws, hs);

			fp = fopen(optarg, "r");
			fgets(buf, 1000, fp);
			while (fgets(buf, 1000, fp) != NULL) {
				sscanf(buf, "%d %d", &x, &y);
				A[i + x][j + y] = 1;
			}
			break;
		case 'o':
			//set a center origin using i and j!
			sscanf(optarg, "%d,%d", &i, &j);
			break;
		case 'H':
			printf("-w width of the screen argument 640, 800, 1024, etc.\n");
			printf("-h height of the screen argument 480, 600, 768, etc.\n");
			printf("-e type of edge. Values are hedge, torus, klein (strings)\n");
			printf("-r the red color value, an integer between [0, 255]\n");
			printf("-g the green color value, an integer between [0, 255]\n");
			printf("-b the blue color value, an integer between [0, 255]\n");
			printf("-s size of the sprite. Valid values are 2, 4, 6, 8, and 16 only.\n");
			printf("-f filename, a life pattern in file format 1.06\n");
			printf("-o x,y the initial x,y coordinate pattern found in the file. N\
o space between x and y.\n");
			printf("sample command line argument:./life -w 800 -h 600 -s 2 -r 100 \
-g 250 -b 0 -e torus -o 60,60 -f ./conway/acorn_106.lif\n");
			printf("\n");
			return 0;
		}
	}
	
	
	//read the file's stuff and initialize the matrix!

	fclose(fp);

        /* set up SDL -- works with SDL2 */
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

        /* Main loop: loop forever. */
	while (1)
	{
		/* your game of life code goes here  */		
		
		/* change the  modulus value to slow the rendering */
		//if (SDL_GetTicks() % 30 == 0)
			//sdl_test(&sdl_info, m, n);
		if (strcmp(border, "torus") == 0) {
			sdl_render_life(&sdl_info, A);

			torus_life(A, B, ws, hs);


			sdl_render_life(&sdl_info, B);

			torus_life(B, A, ws, hs);
		}
		
		if (strcmp(border, "hedge") == 0) {
			sdl_render_life(&sdl_info, A);

			hedge_life(A, B, ws, hs);


			sdl_render_life(&sdl_info, B);

			hedge_life(B, A, ws, hs);
		}
		
		if (strcmp(border, "klein") == 0) {
			sdl_render_life(&sdl_info, A);

			klein_life(A, B, ws, hs);


			sdl_render_life(&sdl_info, B);

			klein_life(B, A, ws, hs);
		}
                 /* Poll for events, and handle the ones we care about. 
                  * You can click the X button to close the window
                  */
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
                        /* If escape is pressed, return (and thus, quit) */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return 0;
				break;
			case SDL_QUIT:
				return(0);
			}
		}
	}

	free_matrix(A, ws);
	free_matrix(B, ws);
	
	return 0;
}
