//
// Created by Pyrrha on 18/01/2016.
//

#include <SFML/Audio.hpp>

sf::SoundBuffer BufferSound_Tir, BufferSound_Reload, BufferSound_GameOver;
sf::Sound Sound_Tir, Sound_Reload, Sound_GameOver;

void ChargeLesSons()
{
    BufferSound_Tir.loadFromFile("../sounds/laser_shoot.wav");
    BufferSound_Reload.loadFromFile("../sounds/laser_reload.wav");
    BufferSound_GameOver.loadFromFile("../sounds/game_over.wav");

    Sound_Tir.setBuffer(BufferSound_Tir);
    Sound_Reload.setBuffer(BufferSound_Reload);
    Sound_GameOver.setBuffer(BufferSound_GameOver);
}

void JoueLeSon(unsigned Son = 0)
{
    switch (Son)
    {
        case 0:
            Sound_Tir.play();
            break;

        case 1:
            Sound_Reload.play();
            break;
        case 2:
            //Son victoire
            break;
        case 3:
            Sound_GameOver.play();
            break;

    }
}