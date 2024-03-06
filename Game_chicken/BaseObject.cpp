#include "BaseObject.h"

// Constructor
BaseObject::BaseObject() {
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

// Destructor
BaseObject::~BaseObject() {
    Free(); // Gọi hàm Free để giải phóng bộ nhớ trước khi hủy đối tượng
}

// Load ảnh từ đường dẫn lên màn hình
bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen) {
    SDL_Texture* new_texture = NULL;

    // Load surface từ đường dẫn
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL) {

        // Xóa màu nền của ảnh để làm màu nền trong suốt
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        // Tạo texture từ surface và gán cho new_texture
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);

        // Lưu kích thước của đối tượng
        if (new_texture != NULL) {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }

        // Giải phóng surface sau khi đã tạo texture
        SDL_FreeSurface(load_surface);
    }

    // Gán texture mới cho p_object_ và kiểm tra
    p_object_ = new_texture;
    return p_object_ != NULL;
}

// Render đối tượng lên màn hình
void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
    // Vị trí và kích thước của ảnh trên màn hình
    SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };

    // Đưa toàn bộ thông số lên renderer
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

// Giải phóng bộ nhớ của các đối tượng
void BaseObject::Free() {
    if (p_object_ != NULL) {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
