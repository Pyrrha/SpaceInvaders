/*!
 * \file const.h
 *
 * \author Tristan Dietz, Diogo De Almeida, Romain Colonna, Alexandre Caron
 *
 * \date 18/01/2016
 *
 * \version 3.2.6
 *
 * \brief c'est le fichier que recueille toutes les constante
 */
//
// Created by Pyrrha on 15/01/2016.
//

#pragma once

using namespace std;

#ifndef SPACE_INVADERS_CONST_H
#define SPACE_INVADERS_CONST_H

#endif //SPACE_INVADERS_CONST_H

// Constantes couleurs

/*!
 * \brief Alias remetant la couleur du texte du terminal à sa valeur par défaut.
 */
const string KReset   ("0");

/*!
 * \brief Alias mettant en noir la couleur du texte du terminal.
 */
const string KBlack    ("30");

/*!
 *\brief Alias mettant en rouge la couleur du texte du terminal.
 */
const string KRed   ("31");

/*!
 * \brief Alias mettant en vert la couleur du texte du terminal.
 */
const string KGreen    ("32");

/*!
 * \brief Alias mettant en jaune la couleur du texte du terminal.
 */
const string KYellow   ("33");

/*!
 * \brief Alias mettant en bleu la couleur du texte du terminal.
 */
const string KBlue    ("34");

/*!
 * \brief Alias mettant en Magneta la couleur du texte du terminal.
 */
const string KMAgenta ("35");

/*!
 * \brief Alias mettant en Cyan la couleur du texte du terminal.
 */
const string KCyan    ("36");

// Constantes Deplacement

/*!
 * \brief Alias vers une case vide à l'écran.
 */
const char KEmpty               = ' ';  // case vide de l'écran

/*!
 * \brief Alias vers la touche servant à se déplacer à droite.
 */
char KRight;  // déplacement vers la droite

/*!
 * \brief Alias vers la touche servant à se déplacer à gauche.
 */
char KLeft;  // Déplacement vers la gauche

/*!
 * \brief Alias vers la touche servant à lancer une torpille.
 */
char KShoot;  // Lancé de torpille

//  Constantes liées à l'envahisseur

/*!
 * \brief Alias c'est la couleur de l'envahisseur
 */
const string KInvadersColor (KYellow);  // Couleur de l'envahisseur

/*!
 * \brief Alias caractère formant l'envahisseur
 */
const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur

/*!
 * \brief Alias caractère formant le missile
 */
const char KMissile             = 'T';  // missile

/*!
 * \brief Alias nombre de caractère qui forment l'envahisseur
 */
const unsigned KInvadersSize    =  5;   // nombre de caractères qui forment l'envahisseur

/*!
 * \brief Alias milieu de l'envahisseur
 */
const unsigned KInvadersMiddle  = KInvadersSize / 2;

/*!
 * \brief Alias forme de l'envahisseur
 */
const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

//Constantes liées au boss
/*!
 * \brief Alias caractère formant le boss
 */
const char KInsideBoss          = 'M';  // caractèrere formant le boss

/*!
 * \brief Alias forme des missile
 */
const char KBossWeapon          = 'I';  // missile

/*!
 * \brief Alias forme des missiles de l'attaque spéciale croix-bleu
 */
const char KBossSpecialWeapon   = 'V';  // Missiles de l'attaque spéciale croix-bleue

/*!
 * \brief Alias nombre de fois que le boss tire
 */
const unsigned KBossShoot       = 2;

/*!
 * \brief Alias taille du boss
 */
const unsigned KBossSize        = 3;

/*!
 * \brief Alias nombre de fois que le joueur joue avant le boss
 */
const unsigned KRatioMeBoss     = 2;

/*!
 * \brief Alias nombre de vie du boss
 */
const unsigned KBossLife     = 4;

/*!
 * \brief Alias la couleur du boss est le rouge
 */
const string KBossColor         = KRed;

/*!
 * \brief Alias couleur de l'attaque spécial du boss, elle est Cyan
 */
const string KBossSpecialColor  = KCyan;


//Constantes liées à l'ULTRA boss

/*!
 * \brief Alias caractère formant l'ulta boss
 */
const char KInsideUltraBoss     = 'H';  // caractèrere formant le boss

/*!
 * \brief Alias caractère du missile
 */
const char KUltraBossWeapon          = 'o';  // missile

/*!
 * \brief Alias caractere Missiles de l'attaque spéciale croix-bleue
 */
const char KUltraBossSpecialWeapon   = '|';  // Missiles de l'attaque spéciale croix-bleue

/*!
 * \brief Alias nombre de fois que l'ultra boss tire
 */
const unsigned KUltraBossShoot       = 2;

/*!
 * \brief Alias taille de l'ultra boss
 */
const unsigned KUltraBossSize        = 1;

/*!
 * \brief Alias nombre de fois que le joueur joue avant l'ultra boss
 */
const unsigned KRatioMeUltraBoss     = 1;

/*!
 * \brief Alias le nombre de vie de l'ultra boss
 */
const unsigned KUltraBossLife        = 4;

/*!
 * \brief Alias la couleur de l'ultra boss est magenta
 */
const string KUltraBossColor         = KMAgenta;

/*!
 * \brief Alias couleur de l'attaque spécial de l'ultra boss, elle est jaune
 */
const string KUltraBossSpecialColor  = KYellow;


// Constantes liées au joueur

/*!
 * \brief Alias le joueur a pour couleur le vert
 */
const string KMyColor (KGreen);

/*!
 * \brief Alias caractere representant le joueur
 */
const char KInsideMe            = 'A';

/*!
 * \brief Alias caractere formant les tropies
 */
const char KTorpedo             = '|';

/*!
 * \brief Alias de la taille du joueur
 */
const unsigned KMySize          = 1;

/*!
 * \brief Alias qui indique le milieu du joueur
 */
const unsigned KMyMiddle        = KMySize / 2;

/*!
 * \brief ..... ;p
 */
const string KMyForm (KMySize, KInsideMe);

/*!
 * \brief Alias pour le nombre de vie du joueur
 */
const unsigned KMyLives			= 4; // Vie du joueur

/*!
 * \brief Alias pour le nombre de numintion du joueur
 */
const unsigned KMyBullet        = 3; //Nombre de munition

/*!
 * \brief Alias temps de rechargement des missile
 */
const unsigned KReloadBullet	= 7; //temps de rechargement

// Constantes liées à l'eapace (l'écran)


/*!
 * \brief Alias Nombre de caractères par ligne
 */
const unsigned KSizeLine   = 40;   // Nombre de caractères par ligne

/*!
 * \brief Alias Nombre de lignes de l'écran (de l'espace
 */
const unsigned KSizeSpace  = 12;   // Nombre de lignes de l'écran (de l'espace)


/*!
 * \brief Alias Numéro de colonne où commence l'envahisseur
 */
const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur

/*!
 * \brief Alias Numéro de colonne où commence le joueur
 */
const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur


/*!
 * \bief c'est le type de l'écran (l'espace, la matrice)
 */
typedef vector<string> CVString;    // c'est le type de l'écran (l'espace, la matrice)


/*!
 * \brief Alias Une ligne vide de la matrice
 */
const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice


/*!
 * \brief Alias Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur
 */
const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur
