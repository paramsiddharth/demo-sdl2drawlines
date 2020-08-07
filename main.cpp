#include <iostream>
#include <list>
#include <SDL2/SDL.h>

// Type definition for lines
typedef struct Line {
	int x1, y1, x2, y2;
} Line;

int main(int argc, char* argv[]) {
	bool quit = false;
	SDL_Event event;

	// Initialize Windows and Renderer
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Line Drawing",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Store the co-ordinates of the newborn line, drawing status, and previously drawn lines
	int x1 = 0,
		x2 = 0,
		y1 = 0,
		y2 = 0;
	bool drawing = false;
	std::list<Line> lines;

	// Main loop
	while(!quit) {
		SDL_Delay(10);
		SDL_PollEvent(&event);

		// Event handlers
		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						// Store the co-ordinates and start drawing a newborn line
						x1 = x2 = event.motion.x;
						y1 = y2 = event.motion.y;
						drawing = true;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button) {
					case SDL_BUTTON_LEFT:
						// Stop drwaing and store line
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
				// Continue drawing the newborn line
				if (drawing) {
					x2 = event.motion.x;
					y2 = event.motion.y;
				}
				break;
		}

		// Clear the canvas
		SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
		SDL_RenderClear(renderer);

		// Draw the newborn line
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		if (drawing)
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		// Draw the stored lines
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		for (auto i: lines) {
			SDL_RenderDrawLine(renderer, i.x1, i.y1, i.x2, i.y2);
		}

		// Display the result
		SDL_RenderPresent(renderer);
	}

	// Kill the Window and Renderer
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
