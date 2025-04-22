#include "global.hpp"
#include "gui.hpp"
#include "hero.hpp"
#include "keymap.hpp"
#include "operation.hpp"

void initialize() {
  end = 0;

  // restore the map
  map = map_original;

  hero.init("yykk", 50, 20, 5, NONE);
  hero.update_location();

  slime.init("slime", 10, 5, 5, 5, NONE);
  skeleton.init("skeleton", 16, 8, 8, 8, NONE);
  bat.init("bat", 25, 15, 0, 10, BLOODSUCKING);
  apostle.init("apostle", 50, 30, 15, 25, MENTAL_POLLUTION);
  beelzebub.init("beelzebub", 100, 25, 15, 100, NONE);
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
        case MOVE_LEFT:
          end == 0 && move(LEFT);
          break;
        case MOVE_RIGHT:
          end == 0 && move(RIGHT);
          break;
        case MOVE_UP:
          end == 0 && move(UP);
          break;
        case MOVE_DOWN:
          end == 0 && move(DOWN);
          break;
        case USE_SMALL_BOTTLE:
          end == 0 && hero.use_small_bottle();
          break;
        case USE_BIG_BOTTLE:
          end == 0 && hero.use_big_bottle();
          break;
        case RESTART:
          initialize();
          break;
        case EXIT_GAME:
          return EXIT_SUCCESS;
          break;
        }
      }
      display();
    }
  }

  // Free resources and close SDL
  close();
  return 0;
}
