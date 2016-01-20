/*!
 * \file const.h
 *
 * \author
 *
 * \date
 *
 * \version
 *
 * \brief
 */

#pragma once

using namespace std;

#ifndef SPACE_INVADERS_CONST_H
#define SPACE_INVADERS_CONST_H

#endif //SPACE_INVADERS_CONST_H

// Constantes couleurs

const string KReset   ("0");
const string KBlack    ("30");
const string KRed   ("31");
const string KGreen    ("32");
const string KYellow   ("33");
const string KBlue    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");
const string KBackgroundGreen    ("42");
const string KBackgroundYellow    ("43");
const string KBackgroundRed    ("41");

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
 * \brief Alias mettant en noir la couleur des caractères.
 */
const string KBlack    ("30");

/*!
 * \biref Alias mettant en rouge la couleur des caractères.
 */
const string KRed   ("31");

/*!
 * \brief Alias mettant en vert la couleur des caractères.
 */
const string KGreen    ("32");

/*!
 * \brief Alias mettant en jaune la couleur des caratères.
 */
const string KYellow   ("33");

/*!
 * \brief ALias mettant en bleu la couleur des caractères.
 */
const string KBlue    ("34");

/*!
 * \brief Alias mettant en magenta la couleur des caractères.
 */
const string KMAgenta ("35");

/*!
 * \brief Alias mettant en cyan la couleur des caractères.
 */
const string KCyan    ("36");

/*!
 * \brief Alias mettant en vert le terminal.
 */
const string KBackgroundGreen    ("42");

/*!
 * \brief Alias mettant en jaune le terminal.
 */
const string KBackgroundYellow    ("43");

/*!
 * \brief Alias mettant en rouge .
 */
const string KBackgroundRed    ("41");


// Constantes Deplacement

/*!
 * \brief Alias pour les case vide qui seront à l'écran.
 */
const char KEmpty               = ' ';  // case vide de l'écran

/*!
 * \brief Alias pour les déplacement vers la droite.
 */
char KRight;  // déplacement vers la droite

/*!
 * \brief Alias pour les déplacement vers la gauche.
 */
char KLeft;  // Déplacement vers la gauche

/*!
 * \brief Alias pour les torplille.
 */
char KShoot;  // Lancé de torpille

//  Constantes liées à l'envahisseur

/*!
 * \brief Alias pour la couleur de l'envahisseur.
 */
const string KInvadersColor (KYellow);  // Couleur de l'envahisseur

/*!
 * \brief Alias pour les caractère formant l'envahisseur.
 */
const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur

/*!
 * \brief Alias pour le caractère formant un missile.
 */
const char KMissile             = 'T';  // missile

/*!
 * \brief Alias pour le nombre de caractères qui forment l'envahisseur.
 */
const unsigned KInvadersSize    =  3;   // nombre de caractères qui forment l'envahisseur

/*!
 * \brief Alias pour le millieu de l'envahisseur.
 */
const unsigned KInvadersMiddle  = KInvadersSize / 2;

/*!
 * \brief Alias pour la forma de l'envahisseur.
 */
const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

//Constantes liées au boss


/*!
 * \brief Alias pour le caractère formant le boss.
 */
const char KInsideBoss          = 'M';  // caractèrere formant le boss

/*!
 * \brief Alias pour le caractère du missile.
 */
const char KBossWeapon          = 'I';  // missile

/*!
 * \brief Alias pour la forme du missile de l'attaque spécial du boss.
 */
const char KBossSpecialWeapon   = '|';  // Missiles de l'attaque spéciale croix-bleue

/*!
 * \brief Alias nombre de fois que le bosse tire.
 */
const unsigned KBossShoot       = 2;

/*!
 * \brief Alias pour la taille du boss.
 */
const unsigned KBossSize        = 3;

/*!
 * \brief Alias pour le nombre de tour que le joueur peux joueur avant que le boss joue.
 */
const unsigned KRatioMeBoss     = 2;

/*!
 * \brief Alias pour le nombre de vie du boss.
 */
const unsigned KBossLife        = 4;

/*!
 * \brief Alias pour la couleur du boss.
 */
const string KBossColor         = KRed;

/*!
 * \bief Alias pour la couleur de l'attaque spécial du boss.
 */
const string KBossSpecialColor  = KCyan;


//Constantes liées à l'ULTRA boss

/*!
 * \brief Alias pour le caractère formant le boss.
 */
const char KInsideUltraBoss     = 'H';  // caractèrere formant le boss

/*!
 * \brief Alias pour le caractère du missile du boss.
 */
const char KUltraBossWeapon          = 'o';  // missile

/*!
 * \brief Alias pour le caractère formant l'attaque spécial du boss.
 */
const char KUltraBossSpecialWeapon   = '|';  // Missiles de l'attaque spéciale croix-bleue

/*!
 * \brief Alias pour le nombre de fois que le boss joue.
 */
const unsigned KUltraBossShoot       = 2;

/*!
 * \brief Alias pour la taille du boss.
 */
const unsigned KUltraBossSize        = 2;

/*!
 * \brief Alias pour le nombre du tour que joue le joueur avant le boss
 */
const unsigned KRatioMeUltraBoss     = 1;

/*!
 * \brief Alias pour le nombre de vie du boss.
 */
const unsigned KUltraBossLife        = 4;

/*!
 * \brief Alias pour la couleur du boss.
 */
const string KUltraBossColor         = KMAgenta;

/*!
 * \brief Alias pour la couleur de l'attaque spécial.
 */
const string KUltraBossSpecialColor  = KYellow;

//Constantes liée aux boucliers


/*!
 * \brief Alias pour la constant pour le bouclier.
 */
const char KInsideShield            = '=';

// Constantes liées au joueur


/*!
 * \brief Alias pour la couleur du joueur.
 */
const string KMyColor (KGreen);

/*!
 * \brief Alias pour la forme du joueur.
 */
const char KInsideMe            = 'A';

/*!
 * \brief Alias pour la forme des torpille du joueur.
 */
const char KTorpedo             = '^';

/*!
 * \brief Alias pour la taille du joueur.
 */
const unsigned KMySize          = 1;

/*!
 * \brief Alias pour le millieu du joueur.
 */
const unsigned KMyMiddle        = KMySize / 2;

/*!
 * \brief Alias pour .......zzzzzzzz.
 */
const string KMyForm (KMySize, KInsideMe);

/*!
 * \brief Alias pou la vie du joueur.
 */
const unsigned KMyLives			= 4; // Vie du joueur

/*!
 * \brief Alias pour le nombre de munition du joueur.
 */
const unsigned KMyBullet        = 3; //Nombre de munition

/*!
 * \brief Alias pour le nombres de temps pour le rechargement des missile du joueur.
 */
const unsigned KReloadBullet	= 15; //temps de rechargement

//Constante liées au temps

/*!
 * \brief Alias pour avoir un chronometre
 */
typedef std::chrono::high_resolution_clock Time;

/*!
 * \brief Alias pour avoir le temps en ms.
 */
typedef std::chrono::milliseconds ms;

/*!
 * \brief Alias pour avoir un temps en sec.
 */
typedef std::chrono::duration<float> fsec;

// Constantes liées à l'eapace (l'écran)


/*!
 * \brief Alias pour le nombre de caractère par ligne.
 */
const unsigned KSizeLine   = 40;   // Nombre de caractères par ligne

/*!
 * \brief Alias pour le nombre de ligne à l'écran.
 */
const unsigned KSizeSpace  = 12;   // Nombre de lignes de l'écran (de l'espace)


/*!
 * \brief Alias pour le numéro de la colonne ou commence l'envahisseur.
 */
const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur

/*!
 * \brief Alias numéro de colonne ou commence le joueur.
 */
const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

/*!
 * \brief Alias le type de l'écran (l'espace, la matrice).
 */
typedef vector<string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

/*!
 * \brief Alias pour une ligne vide de la matrice.
 */
const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice


/*!
 * \brief Alias nombre de fois où c'est le tout du joueur pour un tour de l'envahisseur.
 */
const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


// Constantes liées au score

/*!
 * \brief Alias pour le nombre de point quand tu détruie un missile enemie.
 */
const unsigned KScoreByWeapon       = 10;

/*!
 * \brief Alias pour le nombre de point quand tu tué un invader.
 */
const unsigned KScoreByInvader      = 100;

/*!
 * \brief Alias pour le nomdre de point quand tu tue un boss.
 */
const unsigned KScoreByBoss         = 500;

/*!
 * \biref Alias pour le nombre de point quand tu tue un UltaBoss.
 */
const unsigned KScoreByUltraBoss    = 1000;

/*!
 * \brief Alias pour un multiplicateur de score si le joueur tue plusieurs invader dans un temps apartie.
 */
const float KMultScoreByInvader     = 0.1;

/*!
 * \brief Alias pour un multiplicateur de score si le joueur tue plusieurs boss dans un temps apartie.
 */
const float KMultScoreByBoss        = 0.3;

/*!
 * \brief Alias pour un multiplicateur de score si un joueur tue plusieurs Ulta boss dans un temps apartie.
 */
const float KMultScoreByUltraBoss   = 1.0;
