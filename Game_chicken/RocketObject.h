﻿#pragma once

#include <vector>
#include "BaseObject.h"
#include "CommonFunc.h"
#include "BulletObject.h"
#include "ChickenObject.h"

// Class định nghĩa đối tượng chính (main object) của trò chơi

class RocketObject : public BaseObject {
public:
    RocketObject(); 
    ~RocketObject(); 

    // Hàm load ảnh đối tượng chính từ đường dẫn và renderer
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);

    // Hàm hiển thị đối tượng chính lên màn hình
    void Show(SDL_Renderer* des);

    // Hàm xử lý sự kiện khi bấm nút
    void HandelInput(SDL_Event events, SDL_Renderer* screen, int level);

    // Hàm xử lí đạn bắn
    void HandelBullet(SDL_Renderer* screen);
   

    void set_bullet_list(std::vector<BulletObject*> bullet_list) {
        p_bullet_list_ = bullet_list;
    }

    std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }

    int get_width_frame() { return width_frame_; }
    int get_height_frame() { return height_frame_; }


    void RemoveBullet(const int& idx);

private:

    std::vector<BulletObject*> p_bullet_list_; 

    int width_frame_; 
    int height_frame_;

    float x_pos_; 
    float y_pos_; 

    
};
