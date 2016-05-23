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


class HealthBar
{
public:
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;
	bool health;

	HealthBar()
	{
		t.loadFromFile("Content/HealthBar.png");
		s.setTexture(t);

		bar.setFillColor(Color(0,0,0));
		max = 100;
		health = 1;
	}

	void update(int k)
	{
		if (k>0) if (k<max) bar.setSize( Vector2f(10, (max-k)*70/max) );
		if (k<0) health = 0;
	}

   	void draw(RenderWindow &window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(   center.x - size.x/2 + 10, center.y - size.y/2 + 10);
	    bar.setPosition( center.x - size.x/2 + 11, center.y - size.y/2 + 13);

		window.draw(s);
		window.draw(bar);
	}

};