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
#include "GiftObject.h"

//#include "Text.h"

BaseObject g_background;
BaseObject round2;
BaseObject round3;
TTF_Font* text_font;

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
        text_font = TTF_OpenFont("font/dlxfont_.ttf", 15);
        if (text_font == NULL) check = false;
        
    }

    g_sound_chicken_die = Mix_LoadWAV("sounds/chickendie.wav");
    g_sound_player_die = Mix_LoadWAV("sounds/playerdie.wav");
    g_sound_game = Mix_LoadWAV("sounds/game.mp3");
    g_sound_eat_chicken = Mix_LoadWAV("sounds/eatchicken.wav");
    g_sound_chicken_hit = Mix_LoadWAV("sounds/sound_ChickenHit.wav");

    if (g_sound_chicken_die == NULL || g_sound_game == NULL || g_sound_player_die == NULL || g_sound_chicken_hit == NULL) {
        return false;
    }
    return check;
}

// Load ảnh nền
bool LoadBackground() {
    bool ret = g_background.LoadImg("images/bk.png", g_screen, 0, 0, 0);
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


    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

std::vector<ChickenObject*> chickens_list;
std::vector<GiftObject*> gifts_list;
int level = 1;
int numberChickenLevel1 = 0;
int numberChickenLevel2 = 0;
int numberKillBoss = 0;
int dem1 = 0;
int dem2 = 0;
int dem3 = 0;
int point = 0;
bool quit = false;
int type_menu = 0;
bool check_boss_die = false;
unsigned int die_number = 0;
int scrollOffset = -(g_background.GetRect().h - SCREEN_HEIGHT);



bool check_mouse_vs_item(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void ShowMenu(SDL_Renderer* screen, TTF_Font* font) {
    BaseObject menu;
    if (!menu.LoadImg("images/menu.jpg", g_screen, 0, 0, 0)){
        quit = true;
        return;
    }

    BaseObject list_menu[6];
    list_menu[0].LoadImg("images/playbutton.png", g_screen, 0, 255, 255);
    list_menu[1].LoadImg("images/replaybutton.png", g_screen, 0, 255, 255);
    list_menu[2].LoadImg("images/exitbutton.png", g_screen, 0, 255, 255);
    list_menu[3].LoadImg("images/playbutton1.png", g_screen, 0, 255, 255);
    list_menu[4].LoadImg("images/replaybutton1.png", g_screen, 0, 255, 255);
    list_menu[5].LoadImg("images/exitbutton1.png", g_screen, 0, 255, 255);

    list_menu[0].SetRect(355, 300);
    list_menu[1].SetRect(355, 300);
    list_menu[2].SetRect(355, 370);
    list_menu[3].SetRect(345, 297);
    list_menu[4].SetRect(345, 297);
    list_menu[5].SetRect(345, 367);

    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            

            menu.Render(g_screen);
            if (type_menu == 0) {
                list_menu[0].Render(g_screen);
                list_menu[2].Render(g_screen);
            }
            else if(type_menu == 1) {
                list_menu[1].Render(g_screen);
                list_menu[2].Render(g_screen);
            }
            

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (g_event.type == SDL_QUIT) {
                quit = true;
                is_quit = true;
            }
            
            
            else if (g_event.type == SDL_MOUSEMOTION) {
                
                for (int i = 0; i < 3; i++) {
                    if (check_mouse_vs_item(mouseX, mouseY, list_menu[i].GetRect())) {
                        if(i == 0 && type_menu == 0) list_menu[3].Render(g_screen);
                        else if(i == 1 && type_menu == 1) list_menu[4].Render(g_screen);
                        else if(i == 2) list_menu[5].Render(g_screen);
                    }
                }
            }

            if (g_event.type == SDL_MOUSEBUTTONDOWN) {
                
                if (g_event.button.button == SDL_BUTTON_LEFT) {
                    for (int i = 3; i < 6; i++) {
                        if (check_mouse_vs_item(mouseX, mouseY, list_menu[i].GetRect())) {
                            if (i == 3 || i == 4) { is_quit = true; }
                            else if (i == 5) { quit = true; is_quit = true; }
                        }
                    }
                }
                
               
            }
            
        }
        


        SDL_RenderPresent(g_screen);
    }

}




void ResetGame() {
    level = 1;
    numberChickenLevel1 = 0;
    numberChickenLevel2 = 0;
    numberKillBoss = 0;
    chickens_list.clear();
    gifts_list.clear();
    dem1 = 0;
    dem2 = 0;
    dem3 = 0;
    point = 0;
    die_number = 0;
}




void MakeChickenList() {
    if (level == 1) {
        srand(time(NULL)); // co the random tu 1 toi 3
        for (int i = 0; i < 3; i++) {
            ChickenObject* p_chicken = new ChickenObject();
            if (p_chicken != NULL) {
                p_chicken->LoadImgChicken(g_screen);
                p_chicken->set_clip();
                p_chicken->SetRect(rand() % (SCREEN_WIDTH - 100), rand() % 80);

                p_chicken->SetEgg(g_screen, i);

                p_chicken->set_chicken_x_val(1);
                p_chicken->set_chicken_move(true);
                chickens_list.push_back(p_chicken);
                ++numberChickenLevel1;
            }
        }
    }

    else if (level == 2) {
        srand(time(NULL));
        int tmp = rand() % 100 + 1;
        int tmp1 = rand() % 450 + 1;
        for (int i = 0; i < 5; i++) {
            ChickenObject* p_chicken = new ChickenObject();
            if (p_chicken != NULL) {
                p_chicken->LoadImgChicken(g_screen);
                p_chicken->set_clip();
                p_chicken->SetRect(tmp1 + 75 * (i % 5), tmp);

                p_chicken->SetEgg(g_screen, i);

                p_chicken->set_chicken_x_val(1);
                p_chicken->set_chicken_move(true);
                chickens_list.push_back(p_chicken);
                ++numberChickenLevel2;
            }
        }
    }
  
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
    round2.LoadImg("images/Untitled.png", g_screen, 0, 255, 255);
    round2.SetRect(100, 100);

    // load anh chuyen man 2->3
    round3.LoadImg("images/Untitled1.png", g_screen, 0, 255, 255);
    round3.SetRect(100, 100);

    // Load Mạng
    HealthPlayer player_power;
    player_power.Init(g_screen);

    

    // Load player
    RocketObject p_player;
    p_player.LoadImg("images/rocket.png", g_screen);

    //Load chicken
    MakeChickenList();


    // tạo hình ảnh vụ nổ

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("images/exp_main.png", g_screen);
    if (!tRet) {
        return -1;
    }
    exp_threat.set_clip();

    // am thanh cho game
    Mix_PlayChannel(-1, g_sound_game, 0);

    

    // tạo boss
    BossObject* boss = new BossObject();
    boss->LoadImgBoss(g_screen);
    boss->set_clip();
    boss->SetRect(50, 50);
    boss->set_boss_x_val(6);
    boss->SetEgg(g_screen);

    

    Text point_game;
    point_game.SetColor(Text::WHITE);

    ShowMenu(g_screen, text_font);



    // Vòng lặp chính của game

    while (!quit) {
        
        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                quit = true;
            }
            p_player.HandelInput(g_event, g_screen, level);
        }

        // Xóa màn hình
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);


        // Hiển thị background 
        g_background.Render(g_screen);

        scrollOffset += 1;
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

        
        
        if (numberChickenLevel1 > 15 && chickens_list.size() == 0) {
            level = 2;
            numberChickenLevel1 = 0;
        }

        if (numberChickenLevel2 >100 && chickens_list.size() == 0) {
            level = 3;
            numberChickenLevel2 = 0;
        }

        else if (numberChickenLevel2 > 100 || numberChickenLevel1 > 15) {
            level = 0;
        }


        if ((level == 1 && chickens_list.size() < 3) || (level == 2 && chickens_list.size() < 4)) {
            MakeChickenList();
        }


        if (level == 2 && dem1 < 100) {
            round2.Render(g_screen, NULL);
            ++dem1;
        }
        if (level == 3 && dem2 < 100) {
            round3.Render(g_screen, NULL);
            ++dem2;
        }

        
        //std::cout << "dang chay vong lap while\n";
        // Load chicken
        for (int i = 0; i < chickens_list.size(); i++) {
            ChickenObject* p_chicken = chickens_list.at(i);
            if (p_chicken != NULL) {
                if (p_chicken->get_chicken_move() == true) {
                    p_chicken->HandelChickenMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                   
                    p_chicken->ShowChicken(g_screen);

                    p_chicken->ShowEgg(g_screen);

                    //check va chạm giữa tên lửa với vật cản
                    SDL_Rect rect_player = p_player.GetRect();
                    bool bCol1 = false;
                    EggObject* tEgg = p_chicken->get_egg();
                    if (tEgg) {
                        bCol1 = SDLCommonFunc::CheckCollision(tEgg->GetRect(), rect_player);
                    }

                    SDL_Rect rect_chicken = p_chicken->GetRectFrame();
                    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_chicken);

                    if (bCol1 || bCol2) {

                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                            int x_pos = p_player.GetRect().x - 30;
                            int y_pos = p_player.GetRect().y - 30;
                            
                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.Show(g_screen);

                        }

                        Mix_PlayChannel(-1, g_sound_player_die, 0);

                        ++die_number;
                        if (die_number <= 2) {
                            player_power.Decrease();
                            player_power.LoadHealth(g_screen);

                            p_chicken->Free();
                            chickens_list.erase(chickens_list.begin() + i);


                        }

                        else {
                            if (MessageBox(NULL, L"GAMEOVER", L"GAMEOVER", MB_OK | MB_ICONSTOP) == IDOK) {
                                p_chicken->Free();
                                type_menu = 1;
                                ResetGame();
                                player_power.ResetHealth();
                                ShowMenu(g_screen, text_font);
                            }
                        }
                    }

                }
                else {
                    chickens_list.erase(chickens_list.begin() + i);
                    if (p_chicken != NULL) {
                        p_chicken->Free();
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
                            point += 100;

                            // add gift
                            
                            if (t % 5 == 0) {
                                GiftObject* gift = new GiftObject();
                                gift->LoadImgGift("images/duiga.png", g_screen);
                                gift->SetRect(tRect.x, tRect.y + 30);
                                gift->set_gift_move(true);
                                gift->set_gift_x_val(4);
                                gifts_list.push_back(gift);
                            }
                            else if(t == 3) {
                                GiftObject* gift = new GiftObject();
                                gift->LoadImgGift("images/gift1.png", g_screen);
                                gift->SetRect(tRect.x, tRect.y + 30);
                                gift->set_gift_move(true);
                                gift->set_gift_x_val(7);
                                gifts_list.push_back(gift);
                            }
                            

                            Mix_PlayChannel(-1, g_sound_chicken_hit, 0);

                            p_player.RemoveBullet(r);
                            obj_chicken->Free();
                            chickens_list.erase(chickens_list.begin() + t);


                            
                        }
                    }
                }
            }
        }

        for (int k = 0; k < gifts_list.size(); k++) {
            GiftObject* gift = gifts_list.at(k);
            if (gift != NULL) {
                if (gift->get_gift_move() == true) {
                    gift->HandleGiftMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                    gift->Render(g_screen);
                    SDL_Rect gRect = gift->GetRect();
                    SDL_Rect pRect = p_player.GetRect();
                    bool bCol = SDLCommonFunc::CheckCollision(gRect, pRect);

                    if (bCol) {
                        point += 50;

                        Mix_PlayChannel(-1, g_sound_eat_chicken, 0);
                        gift->Free();
                        gifts_list.erase(gifts_list.begin() + k);



                    }
                }
            }
        }

        // hien menu game over
        if (check_boss_die == true) {
            
            if (dem3 < 50) ++dem3;
            else {
                if (MessageBox(NULL, L"WIN GAME", L"WIN GAME", MB_OK | MB_ICONINFORMATION) == IDOK) {
                    type_menu = 1;
                    player_power.ResetHealth();
                    ShowMenu(g_screen, text_font);
                    ResetGame();
                }
                check_boss_die = false;
            }
        }

        if (level == 3) {

            boss->set_boss_val();
            boss->ShowBoss(g_screen);
            boss->SetEgg(g_screen);
            boss->ShowEgg(g_screen);

            //
            SDL_Rect bossRect = boss->GetRectFrame();
            std::vector<EggObject*> listEgg = boss->getEggList();
            // check ban trung boss
            for (int r = 0; r < bullet_arr.size(); r++) {
                BulletObject* p_bullet = bullet_arr.at(r);
                if (p_bullet != NULL) {

                    SDL_Rect bulletRect = p_bullet->GetRect();
                    bool b_Col = SDLCommonFunc::CheckCollision(bulletRect, bossRect);

                    if (b_Col) {
                        for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                            int x_pos = p_bullet->GetRect().x - 30;
                            int y_pos = p_bullet->GetRect().y - 30;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos, y_pos);
                            exp_threat.Show(g_screen);
                        }


                        Mix_PlayChannel(-1, g_sound_chicken_die, 0);

                        p_player.RemoveBullet(r);
                        ++numberKillBoss;

                        if (numberKillBoss == 60) {
                            while (boss->getSizeEgglist() > 0) {
                                boss->RemoveEgg(0);
                            }
                            
                            level = 0;
                            check_boss_die = true;
                            Mix_PlayChannel(-1, g_sound_player_die, 0);
                        }
                    }

                }
            }
           
            // check va cham
            SDL_Rect rect_player = p_player.GetRect();
            bool b_Col1 = false;

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
                    int x_pos = p_player.GetRect().x - 30;
                    int y_pos = p_player.GetRect().y - 30;
                    
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
                    if (MessageBox(NULL, L"GAMEOVER", L"GAMEOVER", MB_OK | MB_ICONSTOP) == IDOK) {
                        type_menu = 1;
                        ResetGame();
                        player_power.ResetHealth();
                        while (boss->getSizeEgglist() > 0) {
                            boss->RemoveEgg(0);
                        }
                        ShowMenu(g_screen, text_font);
                    }
                }
               
            }
        }


        // hien point
        
        /*point_game.SetText("Point: " + std::to_string(point));
        point_game.LoadFromRenderText(text_font, g_screen);
        point_game.RenderText(g_screen, 120, 5);*/
        
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