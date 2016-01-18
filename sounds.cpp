//
// Created by Pyrrha on 18/01/2016.
//

#include <SFML/Audio.hpp>

sf::SoundBuffer BufferSound_Tir, BufferSound_Reload;
sf::Sound Sound_Tir, Sound_Reload;

void ChargeLesSons()
{
    BufferSound_Tir.loadFromFile("../sounds/laser_shoot.wav");
    BufferSound_Reload.loadFromFile("../sounds/laser_reload.wav");

    Sound_Tir.setBuffer(BufferSound_Tir);
    Sound_Reload.setBuffer(BufferSound_Reload);
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
    }
}