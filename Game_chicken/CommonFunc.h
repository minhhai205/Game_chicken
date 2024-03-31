#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
#include<Windows.h>
#include<string>
#include <cstdlib>

// Biến toàn cục để lưu trữ cửa sổ và các bộ vẽ của SDL
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


// Màu RGB được sử dụng để xác định màu chính (color key)
const int COLOR_KEY_R = 0;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

// Thông số màn hình
const int SCREEN_WIDTH = 860;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int FRAME_PER_SECOND = 30; // fps

// Giá trị màu được sử dụng khi vẽ các đối tượng lên màn hình
const int RENDER_DRAW_COLOR = 0xff;

static Mix_Chunk* g_sound_chicken_die;
static Mix_Chunk* g_sound_player_die;
static Mix_Chunk* g_sound_game;
static Mix_Chunk* g_sound_eat_chicken;
static Mix_Chunk* g_sound_chicken_hit;

namespace SDLCommonFunc {
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

