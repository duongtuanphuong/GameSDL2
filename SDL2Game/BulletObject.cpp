#include "stdafx.h"
#include "BulletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type_ = MAIN_BULLET;
}

BulletObject::~BulletObject()
{

}


void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	if(bullet_dir_ == DIR_RIGHT)
	{
		rect_.x += x_val_;
		if(rect_.x > x_border)
		{
			is_move_ = false;
		}
	}
	else if(bullet_dir_ == DIR_LEFTT)
	{
		rect_.x -= x_val_;
		if(rect_.x < 0)
		{
			is_move_ = false;
		}

	}


	

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	bool ret = false;
	if(bullet_type_ == MAIN_BULLET)
	{
		ret = LoadImg("img//player_bullet.png",des);
	}
	else
	{
		ret = LoadImg("img//threat_bullet.png",des);
	}
	return ret;
}
