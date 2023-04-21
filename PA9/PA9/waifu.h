#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class waifu
{
public:
	waifu(sf::RectangleShape& andy_girl)
	{
		andy_girl.setSize(sf::Vector2f(506, 758));
		andy_girl.setPosition(575, -50);
	}

	void virtual set_asset(sf::RectangleShape& andy_girl, sf::Texture& asset)
	{
		asset.loadFromFile("Textures/andy_girl3.png");		
		asset.setSmooth(true);
		andy_girl.setTexture(&asset);
	}


};