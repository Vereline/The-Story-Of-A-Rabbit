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


using namespace sf;
class MyText 
{
public:
	Font font;
	Text text;
	
	MyText()
	{
		font.loadFromFile("Content\\whata2.ttf");
		text.setFont(font);
	}

	void drawDead (RenderWindow &window)
	{
		
		text.setString("You are dead!");
		text.setCharacterSize(50);
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		text.setPosition( center.x - size.x/2 + 100, center.y - size.y/2 + 100);
		window.draw(text);
	}

	void drawWin (RenderWindow &window)
	{
		
		text.setString("You win!");
		text.setCharacterSize(50);
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		text.setPosition( center.x - size.x/2 + 100, center.y - size.y/2 + 100);
		window.draw(text);
	}

	void draw (RenderWindow &window, int a)
	{
		std::ostringstream playerscore;
		playerscore << a;
		text.setString("Score:"+playerscore.str());
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();
		text.setPosition(   center.x - size.x/2 + 30, center.y - size.y/2 + 10);
		window.draw(text);
	}

};