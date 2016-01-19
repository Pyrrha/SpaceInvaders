//
// Created by Pyrrha on 15/01/2016.
//

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


// Constantes Deplacement

const char KEmpty               = ' ';  // case vide de l'écran
char KRight;  // déplacement vers la droite
char KLeft;  // Déplacement vers la gauche
char KShoot;  // Lancé de torpille

//  Constantes liées à l'envahisseur

const string KInvadersColor (KYellow);  // Couleur de l'envahisseur
const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur
const char KMissile             = 'T';  // missile
const unsigned KInvadersSize    =  3;   // nombre de caractères qui forment l'envahisseur
const unsigned KInvadersMiddle  = KInvadersSize / 2;
const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

//Constantes liées au boss
const char KInsideBoss          = 'M';  // caractèrere formant le boss
const char KBossWeapon          = 'I';  // missile
const char KBossSpecialWeapon   = '|';  // Missiles de l'attaque spéciale croix-bleue
const unsigned KBossShoot       = 2;
const unsigned KBossSize        = 3;
const unsigned KRatioMeBoss     = 2;
const unsigned KBossLife        = 4;
const string KBossColor         = KRed;
const string KBossSpecialColor  = KCyan;


//Constantes liées à l'ULTRA boss
const char KInsideUltraBoss     = 'H';  // caractèrere formant le boss
const char KUltraBossWeapon          = 'o';  // missile
const char KUltraBossSpecialWeapon   = '|';  // Missiles de l'attaque spéciale croix-bleue
const unsigned KUltraBossShoot       = 2;
const unsigned KUltraBossSize        = 2;
const unsigned KRatioMeUltraBoss     = 1;
const unsigned KUltraBossLife        = 4;
const string KUltraBossColor         = KMAgenta;
const string KUltraBossSpecialColor  = KYellow;

//Constantes liée aux boucliers

const char KInsideShield            = '=';

// Constantes liées au joueur

const string KMyColor (KGreen);
const char KInsideMe            = 'A';
const char KTorpedo             = '^';
const unsigned KMySize          = 1;
const unsigned KMyMiddle        = KMySize / 2;
const string KMyForm (KMySize, KInsideMe);
const unsigned KMyLives			= 4; // Vie du joueur
const unsigned KMyBullet        = 3; //Nombre de munition
const unsigned KReloadBullet	= 15; //temps de rechargement

// Constantes liées à l'eapace (l'écran)

const unsigned KSizeLine   = 40;   // Nombre de caractères par ligne
const unsigned KSizeSpace  = 12;   // Nombre de lignes de l'écran (de l'espace)

const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur
const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

typedef vector<string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice

const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


// Constantes liées au score

const unsigned KScoreByWeapon       = 10;
const unsigned KScoreByInvader      = 100;
const unsigned KScoreByBoss         = 500;
const unsigned KScoreByUltraBoss    = 1000;
const float KMultScoreByInvader     = 0.1;
const float KMultScoreByBoss        = 0.3;
const float KMultScoreByUltraBoss   = 1.0;