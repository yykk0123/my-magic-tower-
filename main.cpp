#include "elements.hpp"
#include "gui.hpp"
#include "operation.hpp"

void initialize() {
  end = 0;
  hero = {
      "yykk", // name
      50,     // hp
      50,     // hp_limit
      5,      // attack
      20,     // defence
  };
  // std::cout << "请输入你的名字：";
  // std::cin >> hero.name;

  // set current map to the origin
  for (int i = 0; i < LAYERS; i++)
    for (int j = 0; j < HEIGHT; j++)
      for (int k = 0; k < WIDTH; k++)
        map[i][j][k] = map_original[i][j][k];

  // initialize hero's location
  hero.lct.floor = 0;
  update_hero_location(&hero);
}

int main() {
  // Game initialize
  initialize();

  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
    exit(EXIT_FAILURE);
  }

  // Load media
  if (!loadMedia()) {
    printf("Failed to load media!\n");
    exit(EXIT_FAILURE);
  }

  SDL_Event e;
  bool quit = false;
  while (quit == false) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = true;
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {

          // colemake layout
        case SDLK_a:
          end == 0 && move(&hero, LEFT);
          break;
        case SDLK_s:
          end == 0 && move(&hero, RIGHT);
          break;
        case SDLK_w:
          end == 0 && move(&hero, UP);
          break;
        case SDLK_r:
          end == 0 && move(&hero, DOWN);
          break;
        case SDLK_q:
          end == 0 && use_bottle(&hero, 1);
          break;
        case SDLK_f:
          end == 0 && use_bottle(&hero, 0);
          break;
        case SDLK_p:
          initialize();
          break;
        case SDLK_z:
          return EXIT_SUCCESS;
          break;
        }
        // // move or use bottles only when not ended
        // case SDLK_a:
        //   end == 0 && move(&hero, LEFT);
        //   break;
        // case SDLK_d:
        //   end == 0 && move(&hero, RIGHT);
        //   break;
        // case SDLK_w:
        //   end == 0 && move(&hero, UP);
        //   break;
        // case SDLK_s:
        //   end == 0 && move(&hero, DOWN);
        //   break;
        // case SDLK_q:
        //   end == 0 && use_bottle(&hero, 1);
        //   break;
        // case SDLK_e:
        //   end == 0 && use_bottle(&hero, 0);
        //   break;
        // case SDLK_r:
        //   initialize();
        //   break;
        // case SDLK_z:
        //   return EXIT_SUCCESS;
        //   break;
        // }
      }
      display();
    }
  }

  // Free resources and close SDL
  close();
  return 0;
}
