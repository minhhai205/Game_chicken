#include "CommonFunc.h"
#include "BaseObject.h"
#include "RocketObject.h"
#include "Timer.h"
#include "ChickenObject.h"
#include "EggObject.h"
#include "ExplosionObject.h"

BaseObject g_background;

// Khởi tạo các thành phần của SDL
bool InitData() {
    // Khởi tạo SDL
    bool check = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    int ret1 = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if (ret < 0 && ret1 < 0) return false;

    // Thiết lập cấu hình chất lượng render
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Tạo cửa sổ
    g_window = SDL_CreateWindow("Game SDL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window == NULL) {
        check = false;
    }
    else {
        // Tạo renderer
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

        if (g_screen == NULL) {
            check = false;
        }
        else {
            // Thiết lập màu nền cho renderer
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

            // Khởi tạo thư viện IMG cho việc load ảnh PNG
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) {
                check = false;
            }
        }
    }

    g_sound_chicken_die = Mix_LoadWAV("sounds/chickendie.wav");
    g_sound_player_die = Mix_LoadWAV("sounds/playerdie.wav");
    g_sound_game = Mix_LoadWAV("sounds/game.wav");

    if (g_sound_chicken_die == NULL || g_sound_game == NULL || g_sound_player_die == NULL) {
        return false;
    }
    return check;
}

// Load ảnh nền
bool LoadBackground() {
    bool ret = g_background.LoadImg("images/bk.png", g_screen);
    if (ret == false) return false;
    return true;
}

// Đóng các thành phần của SDL khi kết thúc chương trình
void close() {
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}


std::vector<ChickenObject*> MakeChickenList() {
    std::vector<ChickenObject*> list_chickens;
    ChickenObject* chickens_objs = new ChickenObject[5];
    srand(time(NULL)); // co the random tu 1 toi 3
    for (int i = 0; i < 5; i++) {
        ChickenObject* p_chicken = (chickens_objs + i);
        if (p_chicken != NULL) {
            p_chicken->LoadImgChicken(g_screen);
            p_chicken->SetRect(rand() % (SCREEN_WIDTH-100), rand() % 80);

            p_chicken->SetEgg(g_screen);

            p_chicken->set_chicken_x_val(2);
            p_chicken->set_chicken_move(true);
            list_chickens.push_back(p_chicken);
        }
    }

    return list_chickens;
}


int main(int argc, char* argv[]) {
    Timer fps_timer;

    // Khởi tạo SDL và load ảnh nền
    if (InitData() == false) {
        std::cout << "Initialization failed" << std::endl;
        return -1;
    }

    if (LoadBackground() == false) {
        std::cerr << "Loading background failed" << std::endl;
        return -1;
    }

    // Load player
    RocketObject p_player;
    p_player.LoadImg("images/rocket.png", g_screen);

    //Load chicken
   std::vector<ChickenObject*> chickens_list = MakeChickenList();


   // tạo hình ảnh vụ nổ
   
    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("images/exp_main.png", g_screen);
    if (!tRet) {
        return -1;
    }
    exp_threat.set_clip();

    // am thanh cho game
    Mix_PlayChannel(-1, g_sound_game, 0);

    // Vòng lặp chính của game
    bool quit = false;
    while (!quit) {
        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                quit = true;
            }
            p_player.HandelInput(g_event, g_screen);
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        
        // Hiển thị background và map
        g_background.Render(g_screen, NULL); // Load background

        p_player.HandelBullet(g_screen);

        // Hiển thị player
        p_player.Show(g_screen);
        
        if (chickens_list.size() < 5) {
           std::vector<ChickenObject*>  chickens_temp = MakeChickenList();
           for (auto it : chickens_temp) chickens_list.push_back(it);
        }
        // Load chicken
        for (int i = 0; i < chickens_list.size(); i++) {
            ChickenObject* p_chicken = chickens_list.at(i);
            if (p_chicken != NULL) {
                if (p_chicken->get_chicken_move() == true) {
                    p_chicken->HandelChickenMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_chicken->Render(g_screen);
                    p_chicken->HandelEgg(g_screen);

                    //check va chạm giữa tên lửa với vật cản
                    SDL_Rect rect_player = p_player.GetRectFrame();
                    bool bCol1 = false;
                    EggObject* tEgg = p_chicken->get_egg();
                    if (tEgg) {
                        bCol1 = SDLCommonFunc::CheckCollision(tEgg->GetRect(), rect_player);
                    }

                    SDL_Rect rect_chicken = p_chicken->GetRectFrame();
                    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_chicken);

                    if (bCol1 || bCol2) {
                        Mix_PlayChannel(-1, g_sound_player_die, 0);

                        if (MessageBox(NULL, L"GAMEOVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
                            p_chicken->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }

                }
                else {
                    chickens_list.erase(chickens_list.begin() + i);
                    if (p_chicken != NULL) {
                        p_chicken = NULL;
                    }
                   
                }
            }
        }
       
       
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        // xử lí va chạm cho game
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++) {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL) {
                for (int t = 0; t < chickens_list.size(); t++) {
                    ChickenObject* obj_chicken = chickens_list.at(t);
                    if (obj_chicken != NULL) {
                        SDL_Rect tRect;
                        tRect.x = obj_chicken->GetRect().x;
                        tRect.y = obj_chicken->GetRect().y;
                        tRect.w = obj_chicken->get_chicken_width_();
                        tRect.h = obj_chicken->get_chicken_height_();

                        //std::cout << obj_chicken->get_chicken_height_();
                        SDL_Rect bRect = p_bullet->GetRect();
                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if (bCol) {
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }


                            Mix_PlayChannel(-1, g_sound_chicken_die, 0);

                            p_player.RemoveBullet(r);
                            obj_chicken->Free();
                            chickens_list.erase(chickens_list.begin() + t);


                        }
                    }
                }
            }
        }
        

        // Hiển thị màn hình
        SDL_RenderPresent(g_screen);

        
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 600 / FRAME_PER_SECOND;

        if (real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0) {
                SDL_Delay(delay_time);
            }
        }
    }
    

    // Đóng các thành phần của SDL khi kết thúc chương trình
    close();
    return 0;
}
