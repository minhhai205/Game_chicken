#pragma once
#include "BaseObject.h"
#include <vector>

class HealthPlayer : public BaseObject {
public:
	HealthPlayer();
	~HealthPlayer();

	void SetNumber(int num) { number_ = num; }
	void AddPos(const int& xpos);
	void ResetHealth();
	void LoadHealth(SDL_Renderer* gscreen);

	void Init(SDL_Renderer* screen);

	void Decrease();
private:
	int number_;
	std::vector<int> pos_list_;
};
