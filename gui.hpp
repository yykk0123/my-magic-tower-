#ifndef _GUI_HPP_
#define _GUI_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "elements.hpp"

#define ZOOM_RATE 5
#define CELL_SIZE (ZOOM_RATE * 16) // 80

// lcg/0.png is 640x400 and uses 32px tiles.  At 80px per tile its
// pixel-perfect scale is 2.5, producing a 1600x1000 window.
#define SCREEN_WIDTH (20 * CELL_SIZE)          // 1600
#define SCREEN_HEIGHT ((25 * CELL_SIZE) / 2)   // 1000
#define MAP_LEFT ((9 * CELL_SIZE) / 2)         // 360
#define MAP_TOP ((3 * CELL_SIZE) / 4)          // 60
#define LEFT_BAR (4 * CELL_SIZE)               // 320
#define RIGHT_PANEL_X (16 * CELL_SIZE)         // 1280
#define RIGHT_BAR (4 * CELL_SIZE)              // 320

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
  void renderScaled(int x, int y, int width, int height);

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

extern Ltexture gTexture[TOTAL_SUM];

bool init();

bool loadMedia();

void close();

void display();

#endif // !_GUI_HPP_
