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
#include "ClBullet.h"
#include "ClCoin.h"
#include "ClEnemy.h"
#include "ClEntity.h"

#include "ClHealthBar.h"
#include "ClLevel.h"

#include "ClMyText.h"
#include "ClPlayer.h"
using namespace sf;

bool menu(RenderWindow & window) {

	Font font;
	font.loadFromFile("Content/whata2.ttf");
	Text menu1, menu2, menu3;
	menu1.setString("Start Game!");
	menu2.setString("How To Play");
	menu3.setString("Exit");
	menu1.setFont(font);
	menu2.setFont(font);
	menu3.setFont(font);

	Texture menuBackground, aboutTexture;
	aboutTexture.loadFromFile("Content/info.jpg");
	menuBackground.loadFromFile("Content/notr.jpg");

	Sprite menuBg(menuBackground),  about(aboutTexture);

	 
	Music mus;
	mus.openFromFile("Content/track08.ogg");
	mus.play();
	mus.setLoop(true);

	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0); 

	while (isMenu)
	{
		while (window.isOpen())
			{ 				Event event;
				while (window.pollEvent(event))
				{
				if (event.type == Event::Closed)
				{
				window.close();
				isMenu = false; 
				return isMenu;
				}

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));


				if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Magenta); menuNum = 1; }
				if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Magenta); menuNum = 2; }
				if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Magenta); menuNum = 3; }

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (menuNum == 1) {window.close(); isMenu = false;}//если нажали первую кнопку, то выходим из меню 
					if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
					if (menuNum == 3) { window.close(); isMenu = false; return isMenu; }
				}
				} 
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}  }

}