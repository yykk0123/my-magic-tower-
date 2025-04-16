#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <sstream>
#include <string>

#include "elements.hpp"
#include "gui.hpp"
#include "operation.hpp"

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

TTF_Font *gFont = NULL;

Ltexture gTextureWall, gTextureSpace, gTextureLava, gTextureDoor,
    gTextureUpBlock, gTextureDownBlock, gTextureSlime, gTextureSkeleton,
    gTextureBat, gTextureApostle, gTextureBeelzebub, gTextureSmallBottle,
    gTextureBigBottle, gTextureSword, gTextureShield, gTextureLifeGem,
    gTextureKey, gTextureHero;

Ltexture::Ltexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Ltexture::~Ltexture() { free(); }

bool Ltexture::loadFromRenderedText(std::string textureText,
                                    SDL_Color textColor, Uint32 wrapLength) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface *textSurface = TTF_RenderUTF8_Solid_Wrapped(
      gFont, textureText.c_str(), textColor, wrapLength);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return false;
  }

  // Create texture from surface pixels
  mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  if (mTexture == NULL) {
    printf("Unable to create texture from rendered text! SDL Error: %s\n",
           SDL_GetError());
    return false;
  }

  mWidth = textSurface->w;
  mHeight = textSurface->h;

  // Get rid of old surface
  SDL_FreeSurface(textSurface);

  return mTexture != NULL;
}

bool Ltexture::loadFromFile(std::string path) {
  // Get rid of preexisting texture
  free();

  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
    return false;
  }

  // Create texture fro surface pixels
  newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
  if (newTexture == NULL) {
    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
    return false;
  }

  // Get image dimensions
  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  // Get rid of old loaded surface
  SDL_FreeSurface(loadedSurface);

  mTexture = newTexture;
  return mTexture != NULL;
}

void Ltexture::free() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void Ltexture::renderMap(int x, int y) {
  SDL_Rect renderQuad = {LEFT_BAR + x * CELL_SIZE, y * CELL_SIZE, mWidth,
                         mHeight};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void Ltexture::renderLeft(int x, int y) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void Ltexture::renderRight(int x, int y) {
  SDL_Rect renderQuad = {LEFT_BAR + CELL_SIZE * WIDTH + x, y, mWidth, mHeight};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int Ltexture::getWidth() { return mWidth; }

int Ltexture::getHeight() { return mHeight; }

bool init() {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Create window
  gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (gWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // Create renderer for window
  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (gRenderer == NULL) {
    printf("Render could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

bool loadMedia() {
  if (!(gTextureWall.loadFromFile("assets/image/80x80/wall.png") &&
        gTextureSpace.loadFromFile("assets/image/80x80/space.png") &&
        gTextureLava.loadFromFile("assets/image/80x80/lava.png") &&
        gTextureDoor.loadFromFile("assets/image/80x80/door.png") &&
        gTextureUpBlock.loadFromFile("assets/image/80x80/up_block.png") &&
        gTextureDownBlock.loadFromFile("assets/image/80x80/down_block.png") &&
        gTextureSlime.loadFromFile("assets/image/80x80/slime.png") &&
        gTextureSkeleton.loadFromFile("assets/image/80x80/skeleton.png") &&
        gTextureBat.loadFromFile("assets/image/80x80/bat.png") &&
        gTextureApostle.loadFromFile("assets/image/80x80/apostle.png") &&
        gTextureBeelzebub.loadFromFile("assets/image/80x80/beelzebub.png") &&
        gTextureSmallBottle.loadFromFile(
            "assets/image/80x80/small_bottle.png") &&
        gTextureBigBottle.loadFromFile("assets/image/80x80/big_bottle.png") &&
        gTextureSword.loadFromFile("assets/image/80x80/sword.png") &&
        gTextureShield.loadFromFile("assets/image/80x80/shield.png") &&
        gTextureLifeGem.loadFromFile("assets/image/80x80/life_gem.png") &&
        gTextureKey.loadFromFile("assets/image/80x80/key.png") &&
        gTextureHero.loadFromFile("assets/image/80x80/hero.png"))) {
    printf("Failed to load texture image!\n");
    return false;
  }

  if ((gFont = TTF_OpenFont("assets/wqy-zenhei.ttc", 32)) == NULL) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

void close() {
  // Free loaded image
  gTextureWall.free();
  gTextureSpace.free();
  gTextureLava.free();
  gTextureDoor.free();
  gTextureUpBlock.free();
  gTextureDownBlock.free();
  gTextureSlime.free();
  gTextureSkeleton.free();
  gTextureBat.free();
  gTextureApostle.free();
  gTextureBeelzebub.free();
  gTextureSmallBottle.free();
  gTextureBigBottle.free();
  gTextureSword.free();
  gTextureShield.free();
  gTextureLifeGem.free();
  gTextureKey.free();
  gTextureHero.free();

  TTF_CloseFont(gFont);
  gFont = NULL;

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

static std::string hero_info() {
  std::stringstream ss;
  ss << "名字：" << hero.name << '\n'
     << "生命值：" << hero.hp << '\n'
     << "生命值上限：" << hero.hp_limit << '\n'
     << "防御力：" << hero.defence << '\n'
     << "攻击力：" << hero.attack << '\n'
     << "小血瓶：" << hero.small_bottle << '\n'
     << "大血瓶：" << hero.big_bottle << '\n'
     << "分数：" << hero.score << '\n';

  return ss.str();
}

static std::string monster_info() {
  int monster_quantity[5] = {};
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++)
      switch (map[hero.lct.floor][i][j]) {
      case SLIME:
        monster_quantity[0]++;
        break;
      case SKELETON:
        monster_quantity[1]++;
        break;
      case BAT:
        monster_quantity[2]++;
        break;
      case APOSTLE:
        monster_quantity[3]++;
        break;
      case BEELZEBUB:
        monster_quantity[4]++;
        break;
      }

  std::stringstream ss;
  ss << "名字：史莱姆酱\n"
     << "生命值：" << slime.hp << "\n"
     << "攻击力：" << slime.attack << "\n"
     << "防御力：" << slime.defence << "\n"
     << "特殊属性：无\n"
     << "本层数量：" << monster_quantity[0] << "\n"
     << "\n"
     << "名字：骷髅士兵\n"
     << "生命值：" << skeleton.hp << "\n"
     << "攻击力：" << skeleton.attack << "\n"
     << "防御力：" << skeleton.defence << "\n"
     << "特殊属性：无\n"
     << "本层数量：" << monster_quantity[1] << "\n"
     << "\n"
     << "名字：吸血蝙蝠\n"
     << "生命值：" << bat.hp << "\n"
     << "攻击力：" << bat.attack << "\n"
     << "防御力：" << bat.defence << "\n"
     << "特殊属性：吸血\n"
     << "本层数量：" << monster_quantity[2] << "\n"
     << "\n"
     << "名字：深渊使徒\n"
     << "生命值：" << apostle.hp << "\n"
     << "攻击力：" << apostle.attack << "\n"
     << "防御力：" << apostle.defence << "\n"
     << "特殊属性：精神污染\n"
     << "本层数量：" << monster_quantity[3] << "\n"
     << "\n"
     << "名字：魔王\n"
     << "生命值：" << beelzebub.hp << "\n"
     << "攻击力：" << beelzebub.attack << "\n"
     << "防御力：" << beelzebub.defence << "\n"
     << "特殊属性：无\n"
     << "本层数量：" << monster_quantity[4] << "\n";

  return ss.str();
}

void display() {
  // Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);

  SDL_Color textColor = {0, 0, 0}; // black

  // Render map
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      switch (map[hero.lct.floor][y][x]) {
      case WALL:
        gTextureWall.renderMap(x, y);
        break;
      case SPACE:
        gTextureSpace.renderMap(x, y);
        break;
      case LAVA:
        gTextureLava.renderMap(x, y);
        break;
      case DOOR:
        gTextureDoor.renderMap(x, y);
        break;
      case UP_BLOCK:
        gTextureUpBlock.renderMap(x, y);
        break;
      case DOWN_BLOCK:
        gTextureDownBlock.renderMap(x, y);
        break;
      case SLIME:
        gTextureSlime.renderMap(x, y);
        break;
      case SKELETON:
        gTextureSkeleton.renderMap(x, y);
        break;
      case BAT:
        gTextureBat.renderMap(x, y);
        break;
      case APOSTLE:
        gTextureApostle.renderMap(x, y);
        break;
      case BEELZEBUB:
        gTextureBeelzebub.renderMap(x, y);
        break;
      case SMALL_BOTTLE:
        gTextureSmallBottle.renderMap(x, y);
        break;
      case BIG_BOTTLE:
        gTextureBigBottle.renderMap(x, y);
        break;
      case SWORD:
        gTextureSword.renderMap(x, y);
        break;
      case SHIELD:
        gTextureShield.renderMap(x, y);
        break;
      case LIFE_GEM:
        gTextureLifeGem.renderMap(x, y);
        break;
      case KEY:
        gTextureKey.renderMap(x, y);
        break;
      case HERO:
        gTextureHero.renderMap(x, y);
        break;
      }
    }
  }

  // Render hero's properties
  Ltexture textureProperties;
  textureProperties.loadFromRenderedText(hero_info(), textColor, LEFT_BAR - 10);
  textureProperties.renderLeft(10, 10);

  // Render monsters's information
  Ltexture textureMonster;
  textureMonster.loadFromRenderedText(monster_info(), textColor,
                                      RIGHT_BAR - 20);
  textureMonster.renderRight(10, 10);

  // Render end message
  if (end != 0) {
    Ltexture textureEnd;
    std::string message = (end == 1 ? "You win!" : "You lose :(");
    message += "\nPress R to restart\n Press Z to quit...";
    textureEnd.loadFromRenderedText(message, textColor, LEFT_BAR);
    textureEnd.renderLeft(10, SCREEN_HEIGHT / 2);
  }

  // Update screen
  SDL_RenderPresent(gRenderer);
}
