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
#include "ClMenu.h"
#include "ClMyText.h"
#include "ClPlayer.h"
using namespace sf;


void ChangeLevel (Texture &bg ,Level &lvl, int levelNum )
{
	if (levelNum == 1)
	{
		lvl.LoadFromFile("Content/111.tmx");
		bg.loadFromFile("Content/bg.png");
	}
		
	if (levelNum == 2)
	{
		bg.loadFromFile("Content/bg2.png");
		lvl.LoadFromFile("Content\\1.tmx");
	}
		

}

bool RunGame(RenderWindow &window, int & levNum)
{

	View view( FloatRect(0, 0, 450, 280) );
	Texture bg;
	Level lvl;
	ChangeLevel( bg,lvl,levNum);
	
	Texture enemy_t, moveplatform_t, megaman_t, bullet_t/* bg*/, coin_t, jump, walk, hit, stay, climb, attack;

	enemy_t.loadFromFile("Content/enemy.png");

	megaman_t.loadFromFile("Content/11.png"); 
	bullet_t.loadFromFile("Content/bullet.png");
	coin_t.loadFromFile("Content/coin.png");

	AnimationManager anim;

	anim.loadFromXML("Content/13133.xml",megaman_t);


	AnimationManager anim2;
	anim2.create("move",bullet_t,7,10,8,8,1,0);
	anim2.create("explode",bullet_t,27,7,18,18,4,0.01,29,false);

	AnimationManager anim3;
	anim3.create("move",enemy_t,0,0,16,16,2,0.002,18);
	anim3.create("dead",enemy_t,58,0,16,16,1,0);

	AnimationManager anim4;
	anim4.create("stay", coin_t, 0,0,31,31,1,0);

	Music mus;
	mus.openFromFile("Content/track02.ogg");
	mus.play();
	mus.setLoop(true);

    Sprite background(bg);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);
	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::vector<Object> e = lvl.GetObjects("enemy");
	for (int i=0;i < e.size();i++)
		entities.push_back(new ENEMY(anim3, lvl, e[i].rect.left, e[i].rect.top) );

	e = lvl.GetObjects("star");
	for (int i=0;i < e.size();i++)
		entities.push_back(new COIN(anim4, lvl, e[i].rect.left, e[i].rect.top) );
	Object pl = lvl.GetObject("player");
	PLAYER Mario(anim, lvl, pl.rect.left, pl.rect.top);
	MyText texscore;
	HealthBar healthBar;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/500;  
		if (time > 40) time = 40;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code==Keyboard::Space)
		        	entities.push_back(new Bullet(anim2,lvl,Mario.x+18,Mario.y+18,Mario.dir) );
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) Mario.key["L"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Right)) Mario.key["R"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Up)) Mario.key["Up"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Down)) Mario.key["Down"]=true;
		if (Keyboard::isKeyPressed(Keyboard::Space)) Mario.key["Space"]=true;
		for(it=entities.begin();it!=entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life==false)	{ it  = entities.erase(it); delete b;}
			else it++;
		}

		if (Keyboard::isKeyPressed(Keyboard::Tab)) return true;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return false;

		Mario.update(time);
		healthBar.update(Mario.Health);
		
		for(it=entities.begin();it!=entities.end();it++)
		{
		
			if ((*it)->Name=="Enemy")
			{
				Entity *enemy = *it;

				if (enemy->Health<=0) continue;

				if  (Mario.getRect().intersects( enemy->getRect() ))
				    if (Mario.dy>0) { enemy->dx=0; Mario.dy=-0.2; enemy->Health=0;}
				    else if (!Mario.hit) { Mario.Health-=5; Mario.hit=true;
				                         if (Mario.dir) Mario.x+=10; else Mario.x-=10;}
				for (std::list<Entity*>::iterator it2=entities.begin(); it2!=entities.end(); it2++)
				{
					Entity *bullet = *it2;
					if (bullet->Name=="Bullet")
						if ( bullet->Health>0)
							if  (bullet->getRect().intersects( enemy->getRect() ) )
							 { bullet->Health=0; enemy->Health-=5;}
				}
			}

			if ((*it)->Name=="Coin")
			{
				Entity *coin = *it;
				if  (Mario.getRect().intersects( coin->getRect() ))
				{ coin->Health=0;Mario.score++;}

			}
		}

		view.setCenter( Mario.x,Mario.y);
		window.setView(view);
		background.setPosition(view.getCenter());
		window.draw(background);
		lvl.Draw(window);
		for(it=entities.begin();it!=entities.end();it++)
			(*it)->draw(window);
		Mario.draw(window);
		healthBar.draw(window);
		if (!healthBar.health)
		{
			MyText text;
			text.drawDead(window);
			Mario.PlayerDied(window, time);
		}
		if (Mario.finish)
		{
			MyText text;
			text.drawWin(window);
			Mario.PlayerWin(window, time); 
		};
		if (Mario.fin)
		{
			return true;
		};
		texscore.draw(window, Mario.score);
		window.display();
	}
};

void Gamerunning( RenderWindow &window,int & levelNum)
{
	if (RunGame(window, levelNum))
	{
		if (levelNum!=2)
			levelNum++;
		Gamerunning(window,levelNum);

	}
}