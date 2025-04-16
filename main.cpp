#include "elements.hpp"
#include "gui.hpp"
#include "hero.hpp"
#include "map.hpp"

extern Hero hero;

extern Map map_original, map;

void initialize() {
  end = 0;
  hero = Hero("yykk", // name
              50,     // hp_limit
              5,      // attack
              20,     // defence
              NONE,   // skill
  );
  // std::cout << "请输入你的名字：";
  // std::cin >> hero.name;

  map(map_original);

  // initialize hero's location
  hero.setFloor(0);
  hero.update_hero_location();
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
