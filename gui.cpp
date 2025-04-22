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

#include "global.hpp"
#include "gui.hpp"

#define WIDTH map.getWidth()
#define HEIGHT map.getHeight()

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

TTF_Font *gFont = NULL;

Ltexture gTexture[TOTAL_SUM];

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
  std::string texture_path = "assets/image/80x80/";
  if (!(gTexture[WALL].loadFromFile(texture_path + "wall.png") &&
        gTexture[SPACE].loadFromFile(texture_path + "space.png") &&
        gTexture[LAVA].loadFromFile(texture_path + "lava.png") &&
        gTexture[DOOR].loadFromFile(texture_path + "door.png") &&
        gTexture[UP_BLOCK].loadFromFile(texture_path + "up_block.png") &&
        gTexture[DOWN_BLOCK].loadFromFile(texture_path + "down_block.png") &&
        gTexture[SLIME].loadFromFile(texture_path + "slime.png") &&
        gTexture[SKELETON].loadFromFile(texture_path + "skeleton.png") &&
        gTexture[BAT].loadFromFile(texture_path + "bat.png") &&
        gTexture[APOSTLE].loadFromFile(texture_path + "apostle.png") &&
        gTexture[BEELZEBUB].loadFromFile(texture_path + "beelzebub.png") &&
        gTexture[SMALL_BOTTLE].loadFromFile(texture_path +
                                            "small_bottle.png") &&
        gTexture[BIG_BOTTLE].loadFromFile(texture_path + "big_bottle.png") &&
        gTexture[SWORD].loadFromFile(texture_path + "sword.png") &&
        gTexture[SHIELD].loadFromFile(texture_path + "shield.png") &&
        gTexture[LIFE_GEM].loadFromFile(texture_path + "life_gem.png") &&
        gTexture[KEY].loadFromFile(texture_path + "key.png") &&
        gTexture[HERO].loadFromFile(texture_path + "hero.png"))) {
    printf("Failed to load texture image!\n");
    return false;
  }

  if ((gFont = TTF_OpenFont("assets/wqy-zenhei.ttc", 28)) == NULL) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

void close() {
  // Free loaded image
  for (auto &texture : gTexture)
    texture.free();

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
  ss << "" << hero.getName() << '\n'
     << "生命值：" << hero.getHp() << '\n'
     << "生命值上限：" << hero.getHp_limit() << '\n'
     << "攻击力：" << hero.getAttack() << '\n'
     << "防御力：" << hero.getDefence() << '\n'
     << "小血瓶：" << hero.getSmall_bottle() << '\n'
     << "大血瓶：" << hero.getBig_bottle() << '\n'
     << "分数：" << hero.getScore() << '\n';

  return ss.str();
}

static std::string monster_info() {
  int monster_quantity[5] = {};
  for (int x = 0; x < 10; x++)
    for (int y = 0; y < 10; y++)
      switch (map.getCell(x, y, hero.getFloor())) {
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
      default:;
      }

  std::stringstream ss;
  ss << "史莱姆酱        "
     << "生命值：" << slime.getHp() << "\n"
     << "攻击力：" << slime.getAttack() << "        "
     << "防御力：" << slime.getDefence() << "\n"
     << "本层数量：" << monster_quantity[0] << "\n"
     << "\n"
     << "骷髅士兵        "
     << "生命值：" << skeleton.getHp() << "\n"
     << "攻击力：" << skeleton.getAttack() << "        "
     << "防御力：" << skeleton.getDefence() << "\n"
     << "本层数量：" << monster_quantity[1] << "\n"
     << "\n"
     << "吸血蝙蝠        "
     << "生命值：" << bat.getHp() << "\n"
     << "攻击力：" << bat.getAttack() << "        "
     << "防御力：" << bat.getDefence() << "\n"
     << "特殊属性：吸血\n"
     << "本层数量：" << monster_quantity[2] << "\n"
     << "\n"
     << "深渊使徒        "
     << "生命值：" << apostle.getHp() << "\n"
     << "攻击力：" << apostle.getAttack() << "        "
     << "防御力：" << apostle.getDefence() << "\n"
     << "特殊属性：精神污染\n"
     << "本层数量：" << monster_quantity[3] << "\n"
     << "\n"
     << "魔王        "
     << "生命值：" << beelzebub.getHp() << "\n"
     << "攻击力：" << beelzebub.getAttack() << "        "
     << "防御力：" << beelzebub.getDefence() << "\n"
     << "本层数量：" << monster_quantity[4] << "\n";

  return ss.str();
}

void display() {
  // Clear screen
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(gRenderer);

  SDL_Color textColor = {0, 0, 0}; // black

  // Render map
  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      gTexture[map.getCell(x, y, hero.getFloor())].renderMap(x, y);

  // Render hero's properties
  Ltexture textureProperties;
  textureProperties.loadFromRenderedText(hero_info(), textColor, LEFT_BAR - 5);
  textureProperties.renderLeft(5, 5);

  // Render monsters's information
  Ltexture textureMonster;
  textureMonster.loadFromRenderedText(monster_info(), textColor, RIGHT_BAR - 5);
  textureMonster.renderRight(5, 5);

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
