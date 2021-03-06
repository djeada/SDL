#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//given input -> set(words) -> members?

//linear search -> o(n)

//binary search -> o(logn)

//hash table constant

//how to create a window

//how to display words

//how to grab the input

#define BOOL u32
#define TRUE 1
#define FALSE 0

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;

typedef struct {
	int x;
	int y;
	int w;
	int h;
}rect_t;

void FillRect(rect_t rect, u32 pixel_color, u32 *screen_pixels){
	for(int row = 0; row < rect.h; row++){
		for(int col = 0; col < rect.w; col++){
			screen_pixels[(row + rect.y)*SCREEN_WIDTH + col + rect.x] = pixel_color;	
		}
	}
}

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *win = SDL_CreateWindow("Spell Checker", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0);
	
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
	
	SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
	
	SDL_Texture *screen = SDL_CreateTexture(renderer, 
		format->format,
		SDL_TEXTUREACCESS_STREAMING, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT);
	
	u32 *screen_pixels = (u32*)calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(u32));
	
	assert(screen_pixels);

	
	rect_t square = {0, 0, 30, 30};
	u32 pixel_color = SDL_MapRGB(format, 0, 0, 255);
	FillRect(square, pixel_color, screen_pixels);
	
	BOOL done = FALSE;
	
	while (!done) {
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT) {
			done = TRUE;
			break;
			}
			SDL_Keycode code = event.key.keysym.sym;
			
			switch(code){
				case SDLK_ESCAPE:
					done = TRUE;
					break;
				default:
					break;
			
			}
			
			SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH*sizeof(u32));
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, screen, NULL, NULL);
			SDL_RenderPresent(renderer);
			
			//SDL_Delay(5);
		}
	}

	return 0;
}


