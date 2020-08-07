#include <iostream>
#include <list>
#include <SDL2/SDL.h>


typedef struct Line {
	int x1, y1, x2, y2;
} Line;

int main(int argc, char* argv[]) {
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Line Drawing",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	int x1 = 0,
		x2 = 0,
		y1 = 0,
		y2 = 0;
	bool drawing = false;
	std::list<Line> lines;

	while(!quit) {
		SDL_Delay(10);
		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						x1 = x2 = event.motion.x;
						y1 = y2 = event.motion.y;
						drawing = true;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						drawing = false;
						Line line = (Line) {
							.x1 = x1, .y1 = y1,
							.x2 = x2, .y2 = y2
						};
						lines.push_back(line);
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				if (drawing) {
					x2 = event.motion.x;
					y2 = event.motion.y;
				}
				break;
		}

		SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		if (drawing)
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		for (auto i: lines) {
			SDL_RenderDrawLine(renderer, i.x1, i.y1, i.x2, i.y2);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
