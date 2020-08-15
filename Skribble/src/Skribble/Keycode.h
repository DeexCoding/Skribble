#pragma once

#include "Core.h"

#ifdef SKRIBBLE_WINDOWS

//This is auctally from glfw (glfw3.h), so these will NOT be the keycodes for windows

#define SKRIBBLE_KEY_UNKNOWN            -1

#define SKRIBBLE_KEY_SPACE              32
#define SKRIBBLE_KEY_APOSTROPHE         39  // '
#define SKRIBBLE_KEY_COMMA              44  // ,
#define SKRIBBLE_KEY_MINUS              45  // -
#define SKRIBBLE_KEY_PERIOD             46  // .
#define SKRIBBLE_KEY_SLASH              47  // /
#define SKRIBBLE_KEY_0                  48
#define SKRIBBLE_KEY_1                  49
#define SKRIBBLE_KEY_2                  50
#define SKRIBBLE_KEY_3                  51
#define SKRIBBLE_KEY_4                  52
#define SKRIBBLE_KEY_5                  53
#define SKRIBBLE_KEY_6                  54
#define SKRIBBLE_KEY_7                  55
#define SKRIBBLE_KEY_8                  56
#define SKRIBBLE_KEY_9                  57
#define SKRIBBLE_KEY_SEMICOLON          59  // ;
#define SKRIBBLE_KEY_EQUAL              61  // =
#define SKRIBBLE_KEY_A                  65
#define SKRIBBLE_KEY_B                  66
#define SKRIBBLE_KEY_C                  67
#define SKRIBBLE_KEY_D                  68
#define SKRIBBLE_KEY_E                  69
#define SKRIBBLE_KEY_F                  70
#define SKRIBBLE_KEY_G                  71
#define SKRIBBLE_KEY_H                  72
#define SKRIBBLE_KEY_I                  73
#define SKRIBBLE_KEY_J                  74
#define SKRIBBLE_KEY_K                  75
#define SKRIBBLE_KEY_L                  76
#define SKRIBBLE_KEY_M                  77
#define SKRIBBLE_KEY_N                  78
#define SKRIBBLE_KEY_O                  79
#define SKRIBBLE_KEY_P                  80
#define SKRIBBLE_KEY_Q                  81
#define SKRIBBLE_KEY_R                  82
#define SKRIBBLE_KEY_S                  83
#define SKRIBBLE_KEY_T                  84
#define SKRIBBLE_KEY_U                  85
#define SKRIBBLE_KEY_V                  86
#define SKRIBBLE_KEY_W                  87
#define SKRIBBLE_KEY_X                  88
#define SKRIBBLE_KEY_Y                  89
#define SKRIBBLE_KEY_Z                  90
#define SKRIBBLE_KEY_LEFT_BRACKET       91  // [
#define SKRIBBLE_KEY_BACKSLASH          92  // \ 
#define SKRIBBLE_KEY_RIGHT_BRACKET      93  // ]
#define SKRIBBLE_KEY_GRAVE_ACCENT       96  // `
#define SKRIBBLE_KEY_WORLD_1            161 // non-US #1
#define SKRIBBLE_KEY_WORLD_2            162 // non-US #2

#define SKRIBBLE_KEY_ESCAPE             256
#define SKRIBBLE_KEY_ENTER              257
#define SKRIBBLE_KEY_TAB                258
#define SKRIBBLE_KEY_BACKSPACE          259
#define SKRIBBLE_KEY_INSERT             260
#define SKRIBBLE_KEY_DELETE             261
#define SKRIBBLE_KEY_RIGHT              262
#define SKRIBBLE_KEY_LEFT               263
#define SKRIBBLE_KEY_DOWN               264
#define SKRIBBLE_KEY_UP                 265
#define SKRIBBLE_KEY_PAGE_UP            266
#define SKRIBBLE_KEY_PAGE_DOWN          267
#define SKRIBBLE_KEY_HOME               268
#define SKRIBBLE_KEY_END                269
#define SKRIBBLE_KEY_CAPS_LOCK          280
#define SKRIBBLE_KEY_SCROLL_LOCK        281
#define SKRIBBLE_KEY_NUM_LOCK           282
#define SKRIBBLE_KEY_PRINT_SCREEN       283
#define SKRIBBLE_KEY_PAUSE              284
#define SKRIBBLE_KEY_F1                 290
#define SKRIBBLE_KEY_F2                 291
#define SKRIBBLE_KEY_F3                 292
#define SKRIBBLE_KEY_F4                 293
#define SKRIBBLE_KEY_F5                 294
#define SKRIBBLE_KEY_F6                 295
#define SKRIBBLE_KEY_F7                 296
#define SKRIBBLE_KEY_F8                 297
#define SKRIBBLE_KEY_F9                 298
#define SKRIBBLE_KEY_F10                299
#define SKRIBBLE_KEY_F11                300
#define SKRIBBLE_KEY_F12                301
#define SKRIBBLE_KEY_F13                302
#define SKRIBBLE_KEY_F14                303
#define SKRIBBLE_KEY_F15                304
#define SKRIBBLE_KEY_F16                305
#define SKRIBBLE_KEY_F17                306
#define SKRIBBLE_KEY_F18                307
#define SKRIBBLE_KEY_F19                308
#define SKRIBBLE_KEY_F20                309
#define SKRIBBLE_KEY_F21                310
#define SKRIBBLE_KEY_F22                311
#define SKRIBBLE_KEY_F23                312
#define SKRIBBLE_KEY_F24                313
#define SKRIBBLE_KEY_F25                314
#define SKRIBBLE_KEY_KP_0               320
#define SKRIBBLE_KEY_KP_1               321
#define SKRIBBLE_KEY_KP_2               322
#define SKRIBBLE_KEY_KP_3               323
#define SKRIBBLE_KEY_KP_4               324
#define SKRIBBLE_KEY_KP_5               325
#define SKRIBBLE_KEY_KP_6               326
#define SKRIBBLE_KEY_KP_7               327
#define SKRIBBLE_KEY_KP_8               328
#define SKRIBBLE_KEY_KP_9               329
#define SKRIBBLE_KEY_KP_DECIMAL         330
#define SKRIBBLE_KEY_KP_DIVIDE          331
#define SKRIBBLE_KEY_KP_MULTIPLY        332
#define SKRIBBLE_KEY_KP_SUBTRACT        333
#define SKRIBBLE_KEY_KP_ADD             334
#define SKRIBBLE_KEY_KP_ENTER           335
#define SKRIBBLE_KEY_KP_EQUAL           336
#define SKRIBBLE_KEY_LEFT_SHIFT         340
#define SKRIBBLE_KEY_LEFT_CONTROL       341
#define SKRIBBLE_KEY_LEFT_ALT           342
#define SKRIBBLE_KEY_LEFT_SUPER         343
#define SKRIBBLE_KEY_RIGHT_SHIFT        344
#define SKRIBBLE_KEY_RIGHT_CONTROL      345
#define SKRIBBLE_KEY_RIGHT_ALT          346
#define SKRIBBLE_KEY_RIGHT_SUPER        347
#define SKRIBBLE_KEY_MENU               348

#endif