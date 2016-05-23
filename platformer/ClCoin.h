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
#include "ClAnimation.h"
#include "ClAnimationManager.h"

#include "ClEntity.h"

#include "ClLevel.h"


using namespace sf;

class COIN:public Entity
{
public:
	COIN(AnimationManager &a, Level &lev, int x , int y):Entity(a,x,y)
	{
		option("Coin", 1, 1, "stay");
	};

	void update (float time)
	{
		timer+=time;
		if (timer>3200) {timer=0;}
		if (Health<=0) {life=false;}
		anim.tick(time);
	}
};