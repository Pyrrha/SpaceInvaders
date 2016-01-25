/*!
 * \file main.cpp
 *
 * \author Tristan Dietz, Diogo De Almeida, Romain Colonna, Alexandre Caron
 *
 * \date 18/01/2016
 *
 * \version 3.2.6
 *
 * \brief c'est le fichier qui regroupe tout ce qui touche au son qui seront présent dans notre pojets.
 */

#include <SFML/Audio.hpp>
#include <vector>


/*!
 * \typedef std::vector <sf::Sound> SoundList
 * \brief Alias pour lister nos son.
 */
typedef std::vector <sf::Sound> SoundList; //SoundList

sf::SoundBuffer BufferSound_Tir,
        BufferSound_Reload,
        BufferSound_GameOver,
        BufferSound_Degat,
        BufferSound_Drums,
        BufferSound_Begin,
        BufferSound_Start,
        BufferSound_Fight,
        BufferSound_UltraBoss
;
sf::Sound Sound_Tir,
        Sound_Reload,
        Sound_GameOver,
        Sound_Degat,
        Sound_Drums,
        Sound_Begin,
        Sound_Start,
        Sound_Fight,
        Sound_UltraBoss
;

SoundList BeginLevelSound;


/*!
 * \fn ChargeLesSons
 * \brief Procédure pour charger les sons
 */
void ChargeLesSons()
{
    srand(time(0));

    /*!
     * \brief Chargement des sons en mémoire
     */
    BufferSound_Tir.loadFromFile("sounds/laser_shoot.wav");
    BufferSound_Reload.loadFromFile("sounds/laser_reload.wav");
    BufferSound_GameOver.loadFromFile("sounds/game_over.wav");
    BufferSound_Degat.loadFromFile("sounds/degat.wav");
    BufferSound_Drums.loadFromFile("sounds/sound_drums.wav");
    BufferSound_Begin.loadFromFile("sounds/begin.wav");
    BufferSound_Start.loadFromFile("sounds/start.wav");
    BufferSound_Fight.loadFromFile("sounds/fight.wav");
    BufferSound_UltraBoss.loadFromFile("sounds/carmina.wav");

    /*!
     * \brief Création des objets sons activables
     */
    Sound_Tir.setBuffer(BufferSound_Tir);
    Sound_Reload.setBuffer(BufferSound_Reload);
    Sound_GameOver.setBuffer(BufferSound_GameOver);
    Sound_Degat.setBuffer(BufferSound_Degat);
    Sound_Drums.setBuffer(BufferSound_Drums);
    Sound_Begin.setBuffer(BufferSound_Begin);
    Sound_Start.setBuffer(BufferSound_Start);
    Sound_Fight.setBuffer(BufferSound_Fight);
    Sound_UltraBoss.setBuffer(BufferSound_UltraBoss);

    /*!
     * \brief Liste des sons de début de niveau
     */
    BeginLevelSound =
    {
        Sound_Begin,
        Sound_Start,
        Sound_Fight
    };
}


/*!
 * \fn JoueLeSon
 * \brief Fonction qui permet de changer le son du jeu
 * \param[in] Son Identifiant permettant de sélectionner le son
 */
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
        case 4:
            Sound_Degat.play();
            break;
        case 5:
            Sound_Drums.play();
            break;
        case 6:
            BeginLevelSound[rand() % 3].play();
            break;
        case 7:
            Sound_UltraBoss.play();

    }
}
