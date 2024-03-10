#include "CommonFunc.h"
#include "BaseObject.h"
#include "RocketObject.h"
#include "Timer.h"
#include "ChickenObject.h"
#include "EggObject.h"
#include "ExplosionObject.h"
#include "HealthPlayer.h"
#include "BossObject.h"
#include<vector>
#include "Text.h"

//#include "Text.h"

BaseObject g_background;
BaseObject round2;
BaseObject round3;
TTF_Font* font_point;

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
        
        if (TTF_Init() == -1) {
            check = false;
        }
        font_point = TTF_OpenFont("font/dlxfont_.ttf", 15);
        if (font_point == NULL) check = false;
        
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
    round2.Free();
    round3.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}


int number_health = 3;
int level = 1;
int numberChickenLevel1 = 0;
int numberChickenLevel2 = 0;
int numberKillBoss = 0;



std::vector<ChickenObject*> MakeChickenList() {
    std::vector<ChickenObject*> list_chickens;
    
    if (level == 1) {
        ChickenObject* chickens_objs = new ChickenObject[5];
        srand(time(NULL)); // co the random tu 1 toi 3
        for (int i = 0; i < 5; i++) {
            ChickenObject* p_chicken = (chickens_objs + i);
            if (p_chicken != NULL) {
                p_chicken->LoadImgChicken(g_screen);
                //
                p_chicken->set_clip();
                p_chicken->SetRect(rand() % (SCREEN_WIDTH - 100), rand() % 80);




                p_chicken->SetEgg(g_screen);

                p_chicken->set_chicken_x_val(1);
                p_chicken->set_chicken_move(true);
                list_chickens.push_back(p_chicken);
                ++numberChickenLevel1;
            }
        }
    }

    else if (level == 2) {
        ChickenObject* chickens_objs = new ChickenObject[8];
        srand(time(NULL));
        int tmp = rand() % 100 + 1;
        int tmp1 = rand() % 260 + 1;
        for (int i = 0; i < 8; i++) {
            ChickenObject* p_chicken = (chickens_objs + i);
            if (p_chicken != NULL) {
                p_chicken->LoadImgChicken(g_screen);
                //
                p_chicken->set_clip();
                p_chicken->SetRect(tmp1 + 75 * i, tmp);



                p_chicken->SetEgg(g_screen);

                p_chicken->set_chicken_x_val(1);
                p_chicken->set_chicken_move(true);
                list_chickens.push_back(p_chicken);
                ++numberChickenLevel2;
            }
        }
    }
  
    return list_chickens;
}


int main(int argc, char* argv[]) {
    Timer fps_timer;
    //level = 3;

     // Khởi tạo SDL và load ảnh nền
    if (InitData() == false) {
        std::cout << "Initialization failed" << std::endl;
        return -1;
    }

    if (LoadBackground() == false) {
        std::cerr << "Loading background failed" << std::endl;
        return -1;
    }

    // load anh chuyen man 1->2
    round2.LoadImg("images/Untitled.png", g_screen);
    round2.SetRect(100, 100);

    // load anh chuyen man 2->3
    round3.LoadImg("images/Untitled1.png", g_screen);
    round3.SetRect(100, 100);

    // Load Mạng
    HealthPlayer player_power;
    player_power.Init(g_screen);

    



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

    unsigned int die_number = 0;
    int scrollOffset = -(g_background.GetRect().h - SCREEN_HEIGHT);

    // tạo boss
    BossObject* boss = new BossObject();
    boss->LoadImgBoss(g_screen);
    boss->set_clip();
    boss->SetRect(50, 50);
    boss->set_boss_x_val(3);
    boss->SetEgg(g_screen);

    int dem1 = 0, dem2 = 0;
    int point = 0;

    Text point_game;
    point_game.SetColor(Text::WHITE);
    //std::string str_point = "Point: ";

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


        // Hiển thị background 
        //g_background.Render(g_screen, NULL); // Load background

        scrollOffset += 0.5;
        if (scrollOffset < 0) {
            g_background.Render(g_screen);
            g_background.SetRect(0, scrollOffset);
        }
        else {
            scrollOffset = -(g_background.GetRect().h - SCREEN_HEIGHT);
            g_background.Render(g_screen);
            g_background.SetRect(0, 0);
        }
        // Show mạng
        player_power.LoadHealth(g_screen);

        p_player.HandelBullet(g_screen);

        // Hiển thị player
        p_player.Show(g_screen);

        // thêm gà khi chết

        if (numberChickenLevel1 > 5 && chickens_list.size() == 0) {
            level = 2;
            numberChickenLevel1 = 0;
        }

        if (numberChickenLevel2 > 15 && chickens_list.size() == 0) {
            level = 3;
            numberChickenLevel2 = 0;
        }

        else if (numberChickenLevel2 > 15 || numberChickenLevel1 > 5) {
            level = 0;
        }

        //std::cout << chickens_list.size() << " " << level << std::endl;

        if ((level == 1 && chickens_list.size() < 3) || (level == 2 && chickens_list.size() < 7)) {
            std::vector<ChickenObject*>  chickens_temp = MakeChickenList();
            for (auto it : chickens_temp) chickens_list.push_back(it);
        }




        if (level == 2 && dem1 < 100) {
            round2.Render(g_screen, NULL);
            ++dem1;
        }
        if (level == 3 && dem2 < 100) {
            round3.Render(g_screen, NULL);
            ++dem2;
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();

        //std::cout << "dang chay vong lap while\n";
        // Load chicken
        for (int i = 0; i < chickens_list.size(); i++) {
            ChickenObject* p_chicken = chickens_list.at(i);
            if (p_chicken != NULL) {
                if (p_chicken->get_chicken_move() == true) {
                    p_chicken->HandelChickenMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                    //p_chicken->Render(g_screen);


                    p_chicken->ShowChicken(g_screen);


                    p_chicken->ShowEgg(g_screen);

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

                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                            int x_pos = p_player.GetRectFrame().x - frame_exp_width * 0.5;
                            int y_pos = p_player.GetRectFrame().y - frame_exp_height * 0.5;
                            
                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.Show(g_screen);

                        }

                        Mix_PlayChannel(-1, g_sound_player_die, 0);

                        ++die_number;
                        if (die_number <= 2) {
                            //SDL_Delay(100);
                            player_power.Decrease();
                            player_power.LoadHealth(g_screen);

                            p_chicken->Free();
                            chickens_list.erase(chickens_list.begin() + i);


                        }

                        else {
                            if (MessageBox(NULL, L"GAMEOVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
                                p_chicken->Free();
                                close();
                                SDL_Quit();
                                return 0;
                            }
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


        // xử lí va chạm cho game
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++) {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL) {
                for (int t = 0; t < chickens_list.size(); t++) {
                    ChickenObject* obj_chicken = chickens_list.at(t);
                    if (obj_chicken != NULL) {
                        SDL_Rect tRect = obj_chicken->GetRectFrame();
                        SDL_Rect bRect = p_bullet->GetRect();
                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                        if (bCol) {
                            ++point;
                          
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

        if (level == 3) {

            boss->set_boss_val();
            boss->ShowBoss(g_screen);
            boss->SetEgg(g_screen);
            boss->ShowEgg(g_screen);

            
            SDL_Rect bossRect = boss->GetRectFrame();

            // check ban trung boss
            for (int r = 0; r < bullet_arr.size(); r++) {
                BulletObject* p_bullet = bullet_arr.at(r);
                if (p_bullet != NULL) {

                    SDL_Rect bulletRect = p_bullet->GetRect();
                    bool b_Col = SDLCommonFunc::CheckCollision(bulletRect, bossRect);

                    if (b_Col) {
                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                            int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                            int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.Show(g_screen);
                        }


                        Mix_PlayChannel(-1, g_sound_chicken_die, 0);

                        p_player.RemoveBullet(r);
                        ++numberKillBoss;

                        if (numberKillBoss == 10) {
                           
                            //boss->getSizelist();
                            level = 0;
                            boss->Free();
                        }
                    }

                }
            }
           
            // check va cham
            SDL_Rect rect_player = p_player.GetRectFrame();
            bool b_Col1 = false;
            std::vector<EggObject*> listEgg = boss->getEggList();
            //std::cout << listEgg.size() << std::endl;
            for (int k = 0; k < listEgg.size(); k++) {
                EggObject* tEgg = listEgg.at(k);
                if (tEgg) {
                    b_Col1 = SDLCommonFunc::CheckCollision(tEgg->GetRect(), rect_player);
                    if (b_Col1 == true) {
                        boss->RemoveEgg(k);
                        break;
                    }
                }
            }
             

            bool b_Col2 = SDLCommonFunc::CheckCollision(rect_player, bossRect);

            if (b_Col1 == true || b_Col2 == true) {
                
                for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                    int x_pos = p_player.GetRectFrame().x - frame_exp_width * 0.5;
                    int y_pos = p_player.GetRectFrame().y - frame_exp_height * 0.5;
                    
                    exp_threat.set_frame(ex);
                    exp_threat.SetRect(x_pos, y_pos);
                    exp_threat.Show(g_screen);

                }

                Mix_PlayChannel(-1, g_sound_player_die, 0);

                ++die_number;
                if (die_number <= 2) {
                    player_power.Decrease();
                    player_power.LoadHealth(g_screen);

                }

                else {
                    if (MessageBox(NULL, L"GAMEOVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
                        boss->Free();
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }
               
            }
        }


        // hien point
        point_game.SetText("Point: " + std::to_string(point));
        point_game.LoadFromRenderText(font_point, g_screen);
        point_game.RenderText(g_screen, 120, 5);

        // Hiển thị màn hình
        SDL_RenderPresent(g_screen);


        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 800 / FRAME_PER_SECOND;

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