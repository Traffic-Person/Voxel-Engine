#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
  //initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "uh oh! SDL failed :( heres why: " << SDL_GetError() << std::endl;
    return 1;
  }

  // window :drooling:
  SDL_Window* window = SDL_CreateWindow(
      "what am i even doing lmao", //title
      SDL_WINDOWPOS_CENTERED,      // x pos
      SDL_WINDOWPOS_CENTERED,      // y pos
      800,                         // width (x axis size)
      600,                         // height (y axis size)
      SDL_WINDOW_SHOWN             // random flag idk
    );
  
  SDL_Renderer* renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED
  );

  // loooop
  bool running = true;
  SDL_Event event;

  while (running) {
    // event handler
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    // clear screen to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO drawing code lmao (test line for now)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderDrawLine(renderer, 100, 100, 700, 500);
    
    // show what was drawn
    SDL_RenderPresent(renderer);

    SDL_Delay(16); // 60ish fps?
  }

  // Clean
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0; // returns 0
}
