#pragma once
#include "waifu.h"

#define _CRT_SECURE_NO_DEPRECATE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class char_gen : public waifu
{
public:
	char_gen(sf::RectangleShape& andy_girl, sf::Texture& asset, std::string file_name) : waifu(andy_girl) 
	{
		set_asset(andy_girl, asset, file_name);
	};
	
	void set_asset(sf::RectangleShape& andy_girl, sf::Texture& asset, std::string file_name)
	{
		asset.loadFromFile(file_name);
		asset.setSmooth(true);
		andy_girl.setTexture(&asset);
	}

};