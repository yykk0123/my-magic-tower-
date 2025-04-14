#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "elements.hpp"

#define ZOOM_RATE 5
#define CELL_SIZE (ZOOM_RATE * 16) // 80

#define LEFT_BAR (5 * CELL_SIZE)  // 400
#define RIGHT_BAR (5 * CELL_SIZE) // 400

#define SCREEN_HEIGHT (CELL_SIZE * HEIGHT)                      // 800
#define SCREEN_WIDTH (LEFT_BAR + CELL_SIZE * WIDTH + RIGHT_BAR) // 1600

class Ltexture {
public:
  Ltexture();
  ~Ltexture();

  bool loadFromFile(std::string path);

  bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
                            Uint32 wrapLength);

  void free();

  void renderLeft(int x, int y);
  void renderMap(int x, int y);
  void renderRight(int x, int y);

  int getWidth();
  int getHeight();

private:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
};

extern SDL_Window *gWindow;

extern SDL_Renderer *gRenderer;

extern TTF_Font *gFont;

extern Ltexture gTextureWall, gTextureSpace, gTextureLava, gTextureDoor,
    gTextureUpBlock, gTextureDownBlock, gTextureSlime, gTextureSkeleton,
    gTextureBat, gTextureApostle, gTextureBeelzebub, gTextureSmallBottle,
    gTextureBigBottle, gTextureSword, gTextureShield, gTextureLifeGem,
    gTextureKey, gTextureHero;

bool init();

bool loadMedia();

void close();

void display();
