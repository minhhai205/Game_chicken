#include "RocketObject.h"

RocketObject::RocketObject() {
    x_pos_ = 0;
    y_pos_ = 0;

}

RocketObject::~RocketObject() {
}

bool RocketObject::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen, 0, 255, 255);
    return ret;
}


void RocketObject::Show(SDL_Renderer* des) {

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    x_pos_ = (mouseX - 20);
    y_pos_ = (mouseY - 20);


    rect_.x = mouseX - 20;
    rect_.y = mouseY - 20;

    width_frame_ = rect_.w;
    height_frame_ = rect_.h;

    SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void RocketObject::HandelInput(SDL_Event events, SDL_Renderer* screen) {
    
    if (events.type == SDL_MOUSEBUTTONDOWN) {
        BulletObject* p_bullet = new BulletObject();

        if (events.button.button == SDL_BUTTON_RIGHT) {
             p_bullet->set_bullet_type(BulletObject::FIRE_BULLET);
             p_bullet->LoadImgBullet(screen);
             p_bullet->SetRect(this->rect_.x + 12, rect_.y - 45);
             p_bullet->set_x_val(10);
             p_bullet->set_is_move(true);
             p_bullet_list_.push_back(p_bullet);
        }

        else if (events.button.button == SDL_BUTTON_LEFT) {
            p_bullet->set_bullet_type(BulletObject::RED_BULLET);
            p_bullet->LoadImgBullet(screen);
            p_bullet->SetRect(this->rect_.x + 16, rect_.y - 15);
            p_bullet->set_x_val(10);
            p_bullet->set_is_move(true);
            p_bullet_list_.push_back(p_bullet);
        }
    }
}


void RocketObject::HandelBullet(SDL_Renderer* screen) {
    for (int i = 0; i < p_bullet_list_.size(); i++) {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if (p_bullet != NULL) {
            if (p_bullet->get_is_move() == true) {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(screen);
            }
            else {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                if (p_bullet != NULL) {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void RocketObject::RemoveBullet(const int& idx) {
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size) {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);

        if (p_bullet) {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
