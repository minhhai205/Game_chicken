#pragma once
#include "CommonFunc.h"

class Text {
public:
	Text();
	~Text();

	enum TEXT_COLOR {
		RED = 5,
		WHITE = 6,
		BLACK = 7,
	};
	void RenderText(SDL_Renderer* screen,
		int xp, int yp,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();
	
	
	void SetText(const std::string& text) { str_val = text; }
	

private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;

	int wight;
	int height;
};