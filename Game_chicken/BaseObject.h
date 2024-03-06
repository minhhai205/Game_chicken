#pragma once

// Class định nghĩa đối tượng cơ bản để hiển thị trên màn hình

#include "CommonFunc.h" // Sử dụng file CommonFunc.h, chứa các hàm và định nghĩa chung

class BaseObject {
public:
    // Constructor
    BaseObject();

    // Destructor
    ~BaseObject();

    // Thiết lập vị trí của đối tượng
    void SetRect(const int& x, const int& y) {
        rect_.x = x;
        rect_.y = y;
    }

    // Lấy kích thước và vị trí của đối tượng
    SDL_Rect GetRect() const { return rect_; }

    // Lấy con trỏ đến hình ảnh của đối tượng
    SDL_Texture* GetObject() const { return p_object_; }

    // Load ảnh từ đường dẫn lên màn hình
    bool LoadImg(std::string path, SDL_Renderer* screen);

    // Hiển thị đối tượng lên màn hình với khả năng cắt ảnh (clip)
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    // Giải phóng bộ nhớ của các đối tượng
    void Free();

protected:
    SDL_Texture* p_object_; // Biến lưu trữ hình ảnh
    SDL_Rect rect_; // Biến lưu trữ kích thước ảnh

};
