#ifndef _KEYMAP_HPP_
#define _KEYMAP_HPP_

// #define COLEMAK

#ifdef COLEMAK
#define MOVE_RIGHT SDLK_s
#define MOVE_LEFT SDLK_a
#define MOVE_UP SDLK_w
#define MOVE_DOWN SDLK_r
#define USE_BIG_BOTTLE SDLK_f
#define USE_SMALL_BOTTLE SDLK_q
#define RESTART SDLK_p
#define EXIT_GAME SDLK_z
#else
#define MOVE_RIGHT SDLK_d
#define MOVE_LEFT SDLK_a
#define MOVE_UP SDLK_w
#define MOVE_DOWN SDLK_s
#define USE_BIG_BOTTLE SDLK_q
#define USE_SMALL_BOTTLE SDLK_e
#define RESTART SDLK_r
#define EXIT_GAME SDLK_z
#endif

#endif // _KEYMAP_HPP_
