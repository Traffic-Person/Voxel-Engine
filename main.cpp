#include <SDL2/SDL.h>
#include <iostream>

// i think this gon be haard
struct Vec3 {
  float x, y, z;
};

Vec3 rotateY(Vec3 point, float angle) {
  float rad = angle * 3.14159f / 180.0f; // radians conversion
  return {
    point.x * cos(rad) - point.z * sin(rad),
    point.y,
    point.x * sin(rad) + point.z * cos(rad) // no idea whats happeneing here
  };
}

void project(Vec3 point, int& screenX, int& screenY) {
  float fov = 400.0f;

  if (point.z <= 0) { //behind cam (we cant see)
    screenX = -1;
    screenY = -1;
    return;
  }

  screenX = (int)((point.x / point.z) * fov + 400);
  screenY = (int)((point.y / point.z) * fov + 300);
}

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

    // Define cube which is 8 corners
    Vec3 cube[8] = {
      {-1, -1, 5}, // front bottom left
      { 1, -1, 5}, // front bottom right
      { 1,  1, 5}, // front top right
      {-1,  1, 5}, // front top left
      {-1, -1, 7}, // back bottom left
      { 1, -1, 7}, // back bottom right
      { 1,  1, 7}, // back top right
      {-1,  1, 7}  // back top left
    };

    Vec3 rotatedCube[8]; // rotate all points
    static float angle = 0.0f;
    angle += 1.0f;
    for (int i = 0; i < 8; i++) {
      rotatedCube[i] = rotateY(cube[i], angle);
    }
    
    // white 
    SDL_SetRenderDrawColor(renderer, 255, 255 ,255, 255);

    // draw front face (connect them points)
    for (int i = 0; i < 4; i++) {
      int sx1, sy1, sx2, sy2;
      project(rotatedCube[i], sx1, sy1);
      project(rotatedCube[(i+1) % 4], sx2, sy2);
      SDL_RenderDrawLine(renderer, sx1, sy1, sx2, sy2);
    }
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
