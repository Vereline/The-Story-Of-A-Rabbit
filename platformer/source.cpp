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
#include "ClBullet.h"
#include "ClCoin.h"
#include "ClEnemy.h"
#include "ClEntity.h"
#include "ClGame.h"
#include "ClHealthBar.h"
#include "ClLevel.h"
#include "ClMenu.h"
#include "ClMyText.h"
#include "ClPlayer.h"
using namespace sf;

int main()
{

	bool loop = true;

	while (loop)
	{
		RenderWindow window(VideoMode(766, 400), "The Story Of A Rabbit!");
		if (menu(window))
		{
			int levelNum = 1;
			RenderWindow wind(VideoMode(450, 280), "The Story Of A Rabbit!");
			Gamerunning(wind, levelNum);
		} 
		else loop = false;
	}
  return 0;
}
