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
#include "ClAnimationManager.h"

using namespace sf;


class Bullet:public Entity
{
public:

	Bullet(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y)
	{
		option("Bullet", 0.3, 10, "move");

		if (dir) dx=-0.3;
   		obj = lev.GetObjects("solid");
	}

	void update(float time)
	{
		x+=dx*time;

		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
		        {Health=0;}

		if (Health<=0) {anim.set("explode");dx=0;
		                if (anim.isPlaying()==false) life=false;
		                }

		anim.tick(time);
	}

};