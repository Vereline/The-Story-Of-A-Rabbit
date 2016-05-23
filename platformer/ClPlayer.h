#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include "Content\TinyXML\tinyxml.h"
#include "ClEntity.h"
#include "ClAnimation.h"
#include "ClAnimationManager.h"

#include "ClLevel.h"

using namespace sf;
class PLAYER: public Entity
{
public:

	SoundBuffer jumpbuf;
	Sound JuMp;
	enum {stay,walk,jump,climb} STATE;
	bool onLadder, shoot, hit, onGround;
	std::map<std::string,bool> key;
	int score;
	bool fin, finish;

	PLAYER(AnimationManager &a, Level &lev,int x,int y):Entity(a,x,y)
	{
		option("Player",0,100,"stay");
        STATE=stay; hit=false; score = 0;
		obj = lev.GetAllObjects();
		jumpbuf.loadFromFile("Content/Jump.ogg");
		JuMp.setBuffer(jumpbuf);
		fin = 0; finish = 0;
	}

	void Keyboard()
	{
		if (key["L"])
		{
			dir=1;
			dx=-0.1;
			if (STATE==stay) STATE=walk;
		}

		if (key["R"])
		{
			dir=0;
			dx=0.1;
			if (STATE==stay) STATE=walk;
		}

		if (key["Up"])
		{
			if (onLadder) STATE=climb;
			if ((STATE==stay || STATE==walk)  ) { dy=-0.427; STATE=jump; anim.set("jump"); JuMp.play(); }
			if (STATE==climb) dy=-0.05;
			if (STATE==climb) if (key["L"] || key["R"]) STATE=stay;
		}

		if (key["Down"])
		{
			if (STATE==climb) dy=0.05;
		}

		if (key["Space"])
		{
			shoot=true;
		}
		if (!(key["R"] || key["L"]))
		{
			dx=0;
			if (STATE==walk) STATE=stay;
		}

		if (!(key["Up"] || key["Down"]))
		{
			if (STATE==climb) dy=0;
		}

		if (!key["Space"])
		{
			shoot=false;
		}

		key["R"]=key["L"]=key["Up"]=key["Down"]=key["Space"]=false;//
	}

	void update(float time)
	{
		Keyboard();

        Animation(time);

		if (STATE==climb) if (!onLadder) STATE=stay;
        if (STATE!=climb) dy+=0.0005*time;
        onLadder=false;

		x+=dx*time;
		Collision(0);
		y+=dy*time;
		Collision(1);
	};

	void Collision(int num)
	{
		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name=="solid")
				{
					if (dy>0 && num==1)	{ y = obj[i].rect.top -  h;  dy=0;   STATE=stay; onGround =1;}
					if (dy<0 && num==1)	{ y = obj[i].rect.top + obj[i].rect.height ;   dy=0;}
					if (dx>0 && num==0)	{ x =  obj[i].rect.left -  w; }
					if (dx<0 && num==0)	{ x =  obj[i].rect.left + obj[i].rect.width ;}
				}

				if (obj[i].name=="ladder")	{ onLadder=true; if (STATE==climb) x=obj[i].rect.left-10; }

				if (obj[i].name=="Finish")	{finish = 1;}

				if (obj[i].name=="Fin")
					fin =1;

				if (obj[i].name=="SlopeLeft")
				{  FloatRect r = obj[i].rect;
				   int y0 = (x+w/2-r.left) * r.height/r.width+ r.top - h;
				   if (y>y0)
					  if (x+w/2>r.left)
					   {y = y0; dy=0; STATE=stay;}
				}

				if (obj[i].name=="SlopeRight")
				{   FloatRect r = obj[i].rect;
					int y0 = - (x+w/2-r.left) * r.height/r.width + r.top+r.height - h;
					if (y > y0)
					  if (x+w/2<r.left+r.width)
					   {y = y0; dy=0; STATE=stay;}
				}
			}
	}
    void Animation(float time)
    {
 		if (STATE==stay) anim.set("stay");
		if (STATE==walk) anim.set("walk");
		if (STATE==jump) anim.set("jump");
		if (STATE==climb) {anim.set("climb"); anim.pause(); if (dy!=0) anim.play();}

		if (shoot) {anim.set("shoot");}

		if (hit) {timer+=time;
			      if (timer>1000) {hit=false; anim.set("hit");timer=0;}
				  anim.set("stay");}

		if (dir) anim.flip();

		anim.tick(time);
    }
	void PlayerDied(RenderWindow &window,float time)
	{
		timer+=time;
		timer_end+=timer;
			if (timer_end>4000*4) 
			{
				life=false;
				window.close();
			}	
	}
	void PlayerWin(RenderWindow &window,float time)
	{
		timer+=time;
		timer_end+=timer;
			if (timer_end>4000) 
			{
				life=false;
				window.close();
			}	
	}
};
