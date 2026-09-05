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
  SDL_Rect renderQuad = {MAP_LEFT + x * CELL_SIZE, MAP_TOP + y * CELL_SIZE,
                         CELL_SIZE, CELL_SIZE};
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void Ltexture::renderLeft(int x, int y) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void Ltexture::renderRight(int x, int y) {
  SDL_Rect renderQuad = {RIGHT_PANEL_X + x, y, mWidth, mHeight};
  SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void Ltexture::renderScaled(int x, int y, int width, int height) {
  SDL_Rect renderQuad = {x, y, width, height};
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

//link element to png
const char* elements_to_png[TOTAL_SUM]={
  "player1.png",
  "ground/0.png","ground/1.png","ground/2.png","ground/3.png","ground/4.png",
  "ground/5.png","ground/6.png","ground/7.png","ground/8.png","ground/9.png",
  "ground/10.png","ground/11.png","ground/12.png","ground/13.png",
  "item/0.png","item/1.png","item/2.png","item/3.png","item/4.png","item/5.png",
  "item/6.png","item/7.png","item/8.png","item/9.png","item/10.png","item/11.png",
  "item/12.png","item/13.png","item/14.png","item/15.png","item/16.png","item/17.png",
  "item/18.png","item/19.png","item/20.png","item/21.png",
  "monster/1.png","monster/3.png","monster/5.png","monster/6.png","monster/8.png",
  "monster/10.png","monster/12.png","monster/14.png","monster/16.png","monster/18.png",
  "monster/20.png","monster/22.png","monster/24.png","monster/26.png","monster/28.png",
  "monster/30.png","monster/32.png","monster/34.png","monster/36.png","monster/37.png",
  "monster/38.png","monster/39.png","monster/40.png","monster/41.png","monster/42.png",
  "monster/43.png","monster/44.png","monster/54.png","monster/55.png","monster/56.png",
  "monster/57.png","monster/58.png","monster/59.png","monster/60.png","monster/61.png",
  "monster/62.png","monster/72.png","monster/74.png","monster/76.png","monster/78.png",
  "monster/80.png","monster/82.png","monster/84.png","monster/86.png","monster/88.png",
  "monster/90.png","monster/92.png","monster/94.png","monster/96.png","monster/98.png",
  "monster/100.png",
  "object/0.png","object/1.png","object/2.png","object/4.png","object/6.png",
  "object/8.png","object/10.png","object/12.png",
  "weapon/0.png","weapon/1.png","weapon/2.png","weapon/3.png","weapon/4.png",
  "weapon/5.png","weapon/6.png","weapon/7.png","weapon/8.png","weapon/9.png",
  "lcg/0.png",
  "picture/0.png","picture/1.png","picture/2.png",
};

//check png 
bool check_png(const std::string texture_path){
  for(int i=0;i<TOTAL_SUM;i++){
    if(!gTexture[i].loadFromFile(texture_path+elements_to_png[i])){
      printf("Failed to load texture image!\n");
      return false;
    }
  }
  return true;
}

bool loadMedia() {
  std::string texture_path = "assets/textures/";
  if(!check_png(texture_path)){
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

static void renderTextInLeftBox(const std::string &text, const SDL_Rect &box,
                                SDL_Color color) {
  Ltexture texture;
  if (!texture.loadFromRenderedText(text, color, box.w))
    return;

  const int x = box.x + (box.w - texture.getWidth()) / 2;
  const int y = box.y + (box.h - texture.getHeight()) / 2;
  texture.renderLeft(x, y);
}

static void renderHeroInfo(SDL_Color textColor) {
  // Coordinates of the five gray fields in lcg/0.png, scaled by 2.5.
  const SDL_Rect nameBox = {68, 113, 185, 55};
  const SDL_Rect hpBox = {110, 193, 180, 57};
  const SDL_Rect attackBox = {110, 253, 180, 55};
  const SDL_Rect defenceBox = {110, 315, 180, 50};
  const SDL_Rect coinBox = {110, 375, 180, 50};

  renderTextInLeftBox(hero.getName(), nameBox, textColor);
  renderTextInLeftBox("生命 " + std::to_string(hero.getHp()) + "/" +
                          std::to_string(hero.getHp_limit()),
                      hpBox, textColor);
  renderTextInLeftBox("攻击 " + std::to_string(hero.getAttack()), attackBox,
                      textColor);
  renderTextInLeftBox("防御 " + std::to_string(hero.getDefence()), defenceBox,
                      textColor);
  renderTextInLeftBox("金币 " + std::to_string(hero.getCoin()), coinBox,
                      textColor);
}

static std::string monster_info() {
  int monster_quantity[5] = {};
  for (int x = 0; x < 10; x++)
    for (int y = 0; y < 10; y++)
      switch (map.getCell(x, y, hero.getFloor())) {
      case SLIME_GREEN:
        monster_quantity[0]++;
        break;
      case SKELETON:
        monster_quantity[1]++;
        break;
      case BAT:
        monster_quantity[2]++;
        break;
      case APOSTLE_RED:
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

  // Render the original background before the map and UI text.
  gTexture[BACKGROUND].renderScaled(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF}; // white

  // Render the floor first, then place the current element on top.  This makes
  // transparent pixels around heroes, monsters and items show the floor
  // texture instead of the dark background of the UI frame.
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      const elements tile = map.getCell(x, y, hero.getFloor());
      gTexture[SPACE].renderMap(x, y);
      if (tile != SPACE)
        gTexture[tile].renderMap(x, y);
    }
  }

  // Render each hero property inside its matching field on the background.
  renderHeroInfo(textColor);

  /* Render monsters's information
  Ltexture textureMonster;
  textureMonster.loadFromRenderedText(monster_info(), textColor, RIGHT_BAR - 5);
  textureMonster.renderRight(5, 5);
  */

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
