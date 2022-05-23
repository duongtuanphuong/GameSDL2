// SDL2Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CommonFunc.h"
#include "BaseObject.h" 
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"

BaseObject g_background;
TTF_Font* font_time;

bool InitData()
{
	bool success =true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret <0) 
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
	g_window = SDL_CreateWindow("SDL2Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
		if(g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) && imgFlags  ))
				success = false;
		}
		if(TTF_Init() == -1)
		{
			success = false;
		}
		font_time = TTF_OpenFont("font//dlxfont.ttf",15);
		if(font_time == NULL)
		{
			success =false;
		}

	}
	return success;

}

bool loadBackground()
{
	bool ret = g_background.LoadImg("img//back.png",g_screen);
	if(ret ==false)
		return false;
	return true;
}

void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL; 
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}


std::vector<ThreatsObject*> MakeThreatList()
{
	std::vector<ThreatsObject*> list_threats;
	ThreatsObject* threats_objs = new ThreatsObject[20];
	ThreatsObject* dynamic_threats = new ThreatsObject[20];

	for(int i=0;i<20;i++)
	{
		ThreatsObject* p_threat = (threats_objs + i);
		if(p_threat != NULL)
		{
			p_threat -> LoadImg("img//threat_level.png",g_screen);
			p_threat -> set_clips();
			p_threat -> set_x_pos(1000+i*1000);
			p_threat -> set_y_pos(250);	
			p_threat -> set_type_move(ThreatsObject::STATIC_THREAT);
			BulletObject* p_bullet = new BulletObject();
			p_threat -> InitBullet(p_bullet,g_screen);

			list_threats.push_back(p_threat);
		}

	}

	for(int i=0;i<20;i++)
	{
		ThreatsObject* p_threat = (dynamic_threats +i);
		if(p_threat != NULL)
		{
			p_threat -> LoadImg("img//thread_left.png",g_screen);
			p_threat -> set_clips();
			p_threat -> set_type_move(ThreatsObject::MOVE_IN_SPACE);
			p_threat -> set_x_pos(500 + i*1000);
			p_threat -> set_y_pos(200);
			int pos1 = p_threat -> get_x_pos() - 50;
			int pos2 = p_threat -> get_x_pos() + 50;
			p_threat -> setAnimationPos(pos1,pos2);
			p_threat -> set_input_left(1);

			BulletObject* p_bullet = new BulletObject();
			p_threat -> InitBullet(p_bullet,g_screen);

			list_threats.push_back(p_threat);
		}

	}


	
	return list_threats;
}


int main(int argc, char* argv[])
{

	ImpTimer fps_timer;

	if(InitData()== false)
	{
		return -1;
	}
	if(loadBackground() == false)
	{
		return -1;
	}

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_right.png",g_screen);
	p_player.set_clips();

	std::vector<ThreatsObject*> threats_list = MakeThreatList();

	bool is_quit = false;

	int num_die = 0;

	TextObject font_game;
	font_game.SetColor(TextObject::WHITE_TEXT);

	while (!is_quit)
	{

		fps_timer.start();

		while(SDL_PollEvent(&g_event) !=0)
		{
			if(g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			p_player.HandleInputAction(g_event,g_screen);

		}

		SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen,NULL);

		Map map_data = game_map.getMap();

		p_player.HandleBullet(g_screen);
		p_player.setMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);
		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		for(int i=0;i < threats_list.size();i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			if(p_threat != NULL)
			{
				p_threat -> SetMapXY(map_data.start_x_,map_data.start_y_);
				p_threat -> ImpMoveType(g_screen);
				p_threat -> DoPlayer(map_data);
				p_threat -> MakeBullet(g_screen,SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat -> Show(g_screen);

				SDL_Rect rect_player = p_player.getRectFrame();
				std::vector<BulletObject*> tBullet_list = p_threat -> get_bullet_list();
				bool bCol1 = false;
				int count =0;
				for(int j=0;j<tBullet_list.size();++j)
				{
					BulletObject* pt_bullet = tBullet_list.at(j);
					if(pt_bullet)
					{
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet -> GetRect(), rect_player);
						if(bCol1)
						{
							
						}


					}

				}



				SDL_Rect rect_threat = p_threat -> getRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player,rect_threat);
				if( bCol2)
				{
					num_die++;
					if(num_die <= 3)
					{
						p_player.SetRect(0,0);
						p_player.set_comeback_time(60);
						continue;
					}
					else
					{
						if(MessageBox(NULL,L"GAME OVER" ,L"INFO",MB_OK | MB_ICONSTOP) == IDOK)
						{
							p_threat -> Free();
							close();
							SDL_Quit();
							return 0;
						}

					}

				}


			}

		}

		std::string str_time = "Time: " ;
		Uint32	time_val = SDL_GetTicks()/1000;
		Uint32 val_time = 300 - time_val;
		if(val_time < 0)
		{
			is_quit = true;
			break;
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;
			font_game.SetText(str_time);
			font_game.LoadFromRenderText(font_time,g_screen);
			font_game.RenderText(g_screen,SCREEN_WIDTH - 200,15);
		}



		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for(int r = 0;r < bullet_arr.size();r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if(p_bullet != NULL)
			{
				for(int t = 0;t < threats_list.size();t++)
				{
					ThreatsObject* obj_threats = threats_list.at(t);
					if(obj_threats != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threats -> GetRect().x;
						tRect.y = obj_threats -> GetRect().y;
						tRect.w = obj_threats -> get_width_frame();
						tRect.h = obj_threats -> get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect,tRect);
						if(bCol)
						{
							p_player.RemoveBullet(r);
							obj_threats -> Free();
							threats_list.erase(threats_list.begin() + t);
						}

					}

				}

			}

		}



		SDL_RenderPresent(g_screen);
		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000/FRAME_PER_SECOND;
		if(real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
			{
				SDL_Delay(delay_time);
			}

		}

	}
	for(int i = 0; i < threats_list.size();i++)
	{
		ThreatsObject* p_threat = threats_list.at(1);
		if(p_threat)
		{
			p_threat -> Free();
			p_threat = NULL;
		}

	}
	threats_list.clear();
	close();

	return 0;
}

