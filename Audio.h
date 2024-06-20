#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#include"game.h"

class Audio
{
public:
	Music music, selection;
	bool bingus = true;

	void Audiomenu()
	{
		music.openFromFile("audio/mainmenu.wav");
		music.setLoop(bingus);
		music.play();
	}

	void gametheme()
	{
		music.openFromFile("audio/gamesong.wav");
		music.setLoop(bingus);
		music.play();
	}

	void selectaudio()
	{
		music.openFromFile("audio/selection.wav");
		music.setLoop(true);
		music.play();
		music.setLoop(false);
	}

	void stopaudio()
	{
		music.stop();
	}
};