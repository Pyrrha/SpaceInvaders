/*!
 * \file main.cpp
 *
 * \author Tristan Dietz, Diogo De Almeida, Romain Colonna, Alexandre Caron
 *
 * \date 18/01/2016
 *
 * \version 3.2.6
 *
 * \brief c'est le corps de notre pojets quuii n'est d'autre qu'un space invader
 */

/*!
 * \brief Variables de pré-réglage
 */
//#define DEBUG
#define SOUND


#include <termios.h> //FLAG
#include <iostream>
#include <vector>
#include <iomanip> //setw
#include <stdio.h>
#include <unistd.h> //sleep
#include <chrono> //AVEC CTIME, pour un chrono pour le rechargement des bullets
#include <ctime>
#include <fstream>
#include <map>

#include "const.h"
#ifdef SOUND
#include "sounds.h"
#endif



    //Fonction qui renvoie une string qui est égale à la couleur assosié
    string Couleur (const string & coul)
    {
#ifdef DEBUG
        return "";
#else
        return "\033["+coul+"m";
#endif
    }

    //Je dois expliquer ?
    void ClearScreen ()
    {
#ifdef DEBUG
        for(unsigned i = 0; i < 20; ++i)
        {
            cout << endl;
        }
#else
        cout << "\033[H\033[2J";
#endif
    }

    bool IsPowerUps(char Case)
    {
        for(unsigned i(0); i < PowerUps.size(); ++i)
            if(PowerUps[i] == Case) return true;
        return false;
    }

    //Le display qui s'adapte à la taille de la grille et affiche divers élements (vie/minition) --> Bouclier, KMeSpecialWeapon, KUltraBossSpecialWeapon ??
    void DisplaySpace (const CVString & Space, const bool & Win, const bool & Lost, const unsigned & NbLives, const unsigned & Bullet,const unsigned & Size,
                       unsigned End, unsigned Beg, ms TimeElapsed, bool IsKonami, bool & IncomingAttack, pair <unsigned, unsigned> PosShoot,
                       const unsigned & BossLife,const unsigned & UltraBossLife, const unsigned & Level, const float & Score, const float & MultScore, vector <pair<unsigned, unsigned>> Shield,
                        unsigned LifesMax, unsigned BulletMax)
    {

        //Merci au beau goss de Cedric qui a participé à 200% à la conception du display :)
        ClearScreen();
        string ColBord;
        vector <string> KonamiColor = {KBlue, KCyan, KRed, KGreen, KYellow, KMAgenta};
        srand(time(0));
#ifdef DEBUG
        cout << "Beg : " << Beg << "   End : " << End << "    Shot : " << End+(Beg-End)/2 << "   Temps : " << TimeElapsed.count() << endl;
        cout << "Konami : " << IsKonami << endl;
#endif // define

        //On adapte la couleur de la bordure (soit avec le KonamiCode activé soit en fonction de la vie)
        if (IsKonami)
        {
            ColBord = KonamiColor[rand()%5];
        }
        else
        {
            if(NbLives >= (LifesMax/2)+1) ColBord = KGreen;
            else if(NbLives > 1) ColBord = KYellow;
            else ColBord = KRed;
        }


        cout << "NIVEAU " << Level << "    Score : " << Score << "    Multiplicateur de score : " << MultScore << endl;
        //On affiche les points de vie restant
        cout << Couleur(KReset) << "Vie : ";
        for(unsigned i(0); i < LifesMax; ++i)
        {
            if(NbLives > i) cout << Couleur(KRed) << " ♥";
            else cout << Couleur(KBlack) << " ♥";
        }
        //On affiche les munitions actuel
        cout << "   " << Couleur(KReset) << "Munitions : ";
        for(unsigned i(0); i < BulletMax; ++i)
        {
            if(Bullet > i) cout << Couleur(KGreen) << " |";
            else cout << Couleur(KRed) << " |";
        }
        cout << endl;
        if (BossLife > 0)
        {
            cout << "   " << Couleur(KReset) << "Vie Boss : ";
            for(unsigned i(0); i < KBossLife; ++i)
            {
                if(BossLife > i) cout << Couleur(KYellow) << " ♥";
                else cout << Couleur(KBlack) << " ♥";
            }
            cout << endl;

        }
        if (UltraBossLife > 0)
        {
            cout << "   " << Couleur(KReset) << "Vie Ultra Boss : ";
            for(unsigned i(0); i < KUltraBossLife; ++i)
            {
                if(UltraBossLife > i) cout << Couleur(KMAgenta) << " ♥";
                else cout << Couleur(KBlack) << " ♥";
            }
            cout << endl;
        }


        //On place le haut  de la grille
        cout << Couleur(ColBord) << endl;
        cout << setw(2) << "╔";
        for(unsigned i(1); i < (Space[0].size()*2)+1/*(Size*2)+1*/; ++i)
            cout << setw(2) << "═";
        cout << setw(2) << "╗" << endl;

        //Et on affiche la grille (En fonction de si le Konami code est activé ou pas) (en placant les colonnes de gauche et de droite)
        for(unsigned i(0); i < Space.size(); ++i)
        {
            cout << Couleur(KReset);
            cout << setw(2)<< Couleur(ColBord) << "║";
            for(unsigned j(0); j < Space[0].size(); ++j)
            {
                cout << Couleur(KReset);
                if(IncomingAttack && i == PosShoot.second && j == PosShoot.first)
                {
                    cout << Couleur(KCyan) << setw(2) << 'X';
                    continue;
                }
                if(IsKonami)
                {
                    if (Space[i][j] == KInsideMe) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KInsideInvader) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KInsideBoss) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KInsideBoss) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KMissile) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KTorpedo) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KBossWeapon) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KUltraBossWeapon) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KUltraBossSpecialWeapon) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KBossSpecialWeapon) cout << Couleur(KonamiColor[rand()%2]) << setw(2) << KBossSpecialWeapon; //char(rand()%(33-126)+33);
                    else if (Space[i][j] == KInsideShield) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else cout << Couleur(KReset) << setw(2) << KEmpty;
                }
                else
                {
                    if (Space[i][j] == KInsideMe) cout << Couleur(KMyColor) << setw(2) << KInsideMe;
                    else if (Space[i][j] == KInsideInvader) cout << Couleur(KInvadersColor) << setw(2) << KInsideInvader;
                    else if (Space[i][j] == KInsideBoss) cout << Couleur(KBossColor) << setw(2) << KInsideBoss;
                    else if (Space[i][j] == KInsideUltraBoss) cout << Couleur(KUltraBossColor) << setw(2) << KInsideUltraBoss;
                    else if (Space[i][j] == KMissile) cout << Couleur(KInvadersColor) << setw(2) << KMissile;
                    else if (Space[i][j] == KTorpedo) cout << Couleur(KMyColor) << setw(2) << KTorpedo;
                    else if (Space[i][j] == KBossWeapon) cout << Couleur(KBossColor) << setw(2) << KBossWeapon;
                    else if (Space[i][j] == KUltraBossWeapon) cout << Couleur(KUltraBossColor) << setw(2) << KUltraBossWeapon;
                    else if (Space[i][j] == KUltraBossSpecialWeapon) cout << Couleur(KUltraBossSpecialColor) << setw(2) << KUltraBossSpecialWeapon;
                    else if (Space[i][j] == KBossSpecialWeapon) cout << Couleur(KBossSpecialColor) << setw(2) << KBossSpecialWeapon;
                    else if (IsPowerUps(Space[i][j])) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KInsideShield)
                    {
                        for (unsigned z(0); z < Shield.size(); ++z)
                            if (Shield[z].first == j)
                            {
                                if (Shield[z].second == 3) cout << Couleur(KBackgroundGreen) << setw(2) << KEmpty;
                                else if (Shield[z].second == 2) cout << Couleur(KBackgroundYellow) << setw(2)<< KEmpty;
                                else if (Shield[z].second == 1) cout << Couleur(KBackgroundRed) << setw(2)<< KEmpty;
                                else cout << Couleur(KReset) << setw(2) << KEmpty;
                                break;
                            }
                    }
                    else cout << Couleur(KReset) << setw(2) << KEmpty;
                }


            }
            cout << Couleur (KReset);
            cout << Couleur(ColBord)<< setw(2) << "║";
            cout << endl;
        }
        //Puis on affiche le bas du cadre
        cout << setw(2) << Couleur(ColBord) << "╚";
        for(unsigned i(1); i < (Space[0].size()*2)+1/*(Size*2)+1*/; ++i)
            cout << setw(2) << "═";
        cout << setw(2) << "╝" << endl;


    }

    void InitUltraBossSpace(CVString & Space, unsigned Line, unsigned Column)
    {
        Space.resize(0);
        Space.resize(Line);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Column);
        }
        for(unsigned i(0); i < KUltraBossSize; ++i)
            Space[0][i] = KInsideUltraBoss;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Line-1][((Column-1)/2)+i] = KInsideMe;
        Space[Space.size()-3][0] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)+((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][(Column-1)/2] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][Column -1] = KInsideShield;

    }


    //Fonction pour initié la grille en mode "Boss"
    void InitBossSpace(CVString & Space, unsigned Line, unsigned Column)
    {


        Space.resize(0);
        Space.resize(Line);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Column);
        }
        for(unsigned i(0); i < KBossSize; ++i)
            Space[0][i] = KInsideBoss;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Line-1][((Column-1)/2)+i] = KInsideMe;
        Space[Space.size()-3][0] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)+((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][(Column-1)/2] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][Column -1] = KInsideShield;

    }

    //Fonction pour inité la grille en mode standard
    void InitSpace (CVString & Space, unsigned Line, unsigned Column)
    {
        Space.resize(0);
        Space.resize(Line);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Column);
        }
        for(unsigned i(0); i < KInvadersSize; ++i)
            Space[0][i] = KInsideInvader;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Line-1][((Column-1)/2)+i] = KInsideMe;

        Space[Space.size()-3][0] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)+((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][(Column-1)/2] = KInsideShield;
        Space[Space.size()-3][((Column-1)/2)/2] = KInsideShield;
        Space[Space.size()-3][Column -1] = KInsideShield;
    }

    void Remove (CVString & Space, unsigned Line, unsigned Column);
    bool WhoExist(CVString Space, unsigned Line, char Who);

    //Fonction pour descendre les ennemie quand ils arrivent en bout de ligne
    void DownShift(CVString & Space, unsigned CurrentLine, bool & Lost, bool & Win)
    {
        if (CurrentLine < Space.size() - 2)
        {
            swap(Space[CurrentLine], Space[CurrentLine+1]);
            /*for(unsigned j (0); j < Space.size(); ++j)
             {
                 if(Space[CurrentLine][j] == KTorpedo) continue;
                 //if(Space[CurrentLine+1][j] != KTorpedo)
                     swap(Space[CurrentLine][j], Space[CurrentLine+1][j]);
                 else
                     Remove(Space, CurrentLine, j);
                     //if (!WhoExist(Space, CurrentLine +1, KInsideInvader)) Win = true;
             }*/
        }
        else
            Lost = true;
        //EndGame(false);

    }

    //Fonction du tire "Normal" des énnemies
    void Shoot (CVString & Space, unsigned Line, unsigned Middle, char Projectile, char Who)
    {

        if(Line < Space.size() && Middle < Space.size())
            Space[Line][Middle] = Projectile;


    }


    //Fonction qui vérifie l'existance de Who sur la ligne
    bool WhoExist(CVString Space, unsigned Line, char Who)
    {
        bool Exist = false;
        for(unsigned j(0); j < Space.size()-1; ++j)
        {

            if(Space[Line][j] == Who) Exist = true;

        }
        return Exist;
    }

    //Fonction qui supprime la case et les cases latérales
    void Remove (CVString & Space, unsigned Line, unsigned Column)
    {
        Space[Line][Column] = KEmpty;
        //Suppression des cases adjacentes à Space[Line][Column]
        if(Column > 0) Space[Line][Column-1] = KEmpty;
        if(Column < Space.size()-1) Space[Line][Column+1]= KEmpty;

    }

    //Fonction qui detect le debut et la fin des ennemies
    void DetectBegEnd(const CVString & Space, const unsigned & CurrentLine, unsigned & Beg, unsigned & End)
    {
        bool FirstFind = false;
        for(unsigned j(0); j < Space[0].size(); ++j)
        {
            if(Space[CurrentLine][j] == KInsideInvader || Space[CurrentLine][j] == KInsideBoss)
            {
                if(!FirstFind)
                {
                    End = j;

                    FirstFind = true;
                }
                Beg = j+1;
            }
        }
    }




    void AddPowerUps(char PowerUp, unsigned & NbLives, float & Score, float & MultScore, unsigned LivesMax, unsigned & Jeton)
    {
        if (PowerUp == 'L') ++NbLives;
        else if (PowerUp == 'S') Score += 1004.2;
        else if (PowerUp == 'E') MultScore += 0.5;
        else if (PowerUp == 'F') NbLives = LivesMax;
        else if (PowerUp == 'J') ++Jeton;

    }

    //Fonction qui recalcule la grille en bougeant les missile (allié et ennemie)
    void RecomputeSpace (CVString & Space, bool & Win, bool & Lost, unsigned & NbLives, unsigned & BossLife, unsigned & UltraBossLife, float & Score, float & MultScore,
                         vector <pair<unsigned, unsigned>> & Shield, unsigned LivesMax, unsigned & Jeton)
    {

        //BouclePowerUps
        for (unsigned j(0); j < Space[0].size(); ++j)
        {
            if (IsPowerUps(Space[0][j]) && j > 0) {
                Space[0][j] = PowerUps[rand() % PowerUps.size() - 1];
                swap(Space[0][j], Space[0][j - 1]);

            }
            else if (IsPowerUps(Space[0][j]) && j == 0) {
                Space[0][j] = KEmpty;
            }
        }
        //On parcous de haut en bas pour faire remonté les missile allié
        for(unsigned i (0); i < Space.size(); ++i)
            for(unsigned j(0); j < Space[i].size(); ++j)
            {

                if(Space[i][j] == KTorpedo && i > 0)
                {
                    if (Space[i-1][j] == KMissile || Space[i-1][j] == KBossWeapon || Space[i-1][j] == KBossSpecialWeapon || Space[i-1][j] == KUltraBossWeapon || Space[i-1][j] == KUltraBossSpecialWeapon)
                    {
                        Space[i][j] = KEmpty;
                        Space[i-1][j] = KEmpty;
                        Score += KScoreByWeapon*MultScore;
                        continue;
                    }
                    else if(Space[i-1][j] == KInsideInvader)
                    {
                        Remove(Space, i-1, j);
                        Score += KScoreByInvader*MultScore;
                        if (!WhoExist(Space, i-1, KInsideInvader)) Win = true;
                    }
                    else if (Space[i-1][j] == KInsideBoss)
                    {
                        Space[i][j] = KEmpty;
                        Score += KScoreByBoss*MultScore;
                        --BossLife;
                        if(BossLife == 0)
                            Win = true;

                    }
                    else if (Space[i-1][j] == KInsideShield)
                    {
                        Space[i][j] = KEmpty;
                        for(unsigned z(0); z < Shield.size(); ++z)
                        {
                            if (Shield[z].first == j) --Shield[z].second;
                            if (Shield[z].first == j && Shield[z].second == 0)
                                Space[i-1][j] = KEmpty;

                        }
                    }
                    else if (Space[i-1][j] == KInsideUltraBoss)
                    {
                        Space[i][j] = KEmpty;
                        Score += KScoreByUltraBoss*MultScore;
                        --UltraBossLife;
                        if(UltraBossLife == 0)
                            Win = true;
                    }
                    else if (IsPowerUps(Space[i-1][j]))
                    {
                        Space[i][j] = KEmpty;
                        AddPowerUps(Space[i-1][j], NbLives, Score, MultScore, LivesMax, Jeton);
                        Space[i-1][j] = KEmpty;

                    }
                    else
                        swap(Space[i][j],Space[i-1][j]);
                }
                //Disparition du missile à la case donnée (envahisseur)
                if((Space[i][j] == KMissile || Space[i][j] == KBossWeapon || Space[i][j] == KUltraBossWeapon || Space[i][j] == KBossSpecialWeapon || Space[i][j] == KUltraBossSpecialWeapon) && i == Space.size()-1)
                    Space[i][j] = KEmpty;
                //Bug fixed : rendu du missile spécial bugué
                //Si la case du dessous (si existante) n'est pas un missile spécial alors bug alors efface
                else if ((Space[i][j] == KBossSpecialWeapon || Space[i][j] == KUltraBossSpecialWeapon) && i < Space.size() && (Space[i+1][j] != KBossSpecialWeapon || Space[i+1][j] != KUltraBossSpecialWeapon) && Space[i+1][j] != KInsideMe)
                    Space[i][j] = KEmpty;
                //Disparition du missile à la case donnée (joueur)
                else if(Space[i][j] == KTorpedo && i == 0)
                    Space[i][j] = KEmpty;

            }

        //Et ici on parcous de bas en haut pour descendre les missile ennemie
        for(unsigned i (Space.size()); --i > 0;)
            for(unsigned j(0); j < Space[i].size(); ++j)
            {
                //Si c'est une munition provenant du boss
                if((Space[i][j] == KMissile || Space[i][j] == KBossWeapon || Space[i][j] == KBossSpecialWeapon || Space[i][j] == KUltraBossWeapon || Space[i][j] == KUltraBossSpecialWeapon) && i+1 < Space.size())
                {
                    if (Space[i+1][j] == KTorpedo)
                    {
                        Space[i][j] = KEmpty;
                        Space[i+1][j] = KEmpty;
                        Score += KScoreByWeapon*MultScore;
                        continue;
                    }
                    else if(Space[i+1][j] == KInsideMe)
                    {
                        MultScore = 1;
                        --NbLives;
                        #ifdef SOUND
                        JoueLeSon(4);
                        #endif
                        Remove(Space, i, j);
                        if(NbLives == 0)
                        {
                            Remove(Space, i+1, j);
                            if (!WhoExist(Space, Space[0].size()-1, KInsideMe)) Lost = true;
                        }
                    }
                    else if (Space[i+1][j] == KInsideShield)
                    {
                        Space[i][j] = KEmpty;
                        for(unsigned z(0); z < Shield.size(); ++z)
                        {
                            if (Shield[z].first == j) --Shield[z].second;
                            if (Shield[z].first == j && Shield[z].second == 0)
                                Space[i+1][j] = KEmpty;
                        }
                    }
                    else
                        swap(Space[i][j],Space[i+1][j]);
                }

            }
    }

    //Version 2 du tire, le tire spécial du boss
    void Shoot3(CVString & Space,unsigned ColumnA, unsigned ColumnB)
    {

        for(unsigned i(0); i < Space.size(); ++i)
            //Résolution du bug de disparition du boss lorsque attaque spécial au dessus de lui
            if (Space[i][ColumnA] != KInsideUltraBoss && Space[i][ColumnB] != KInsideUltraBoss && Space[i][ColumnA] != KInsideMe && Space[i][ColumnB] != KInsideMe)
            {
                Space[i][ColumnB] = KUltraBossSpecialWeapon;
                Space[i][ColumnA] = KUltraBossSpecialWeapon;
            }


    }

    //Version 2 du tire, le tire spécial du boss
    void Shoot2(CVString & Space,unsigned Line, unsigned Column)
    {

        for(unsigned i(Line); i < Space.size(); ++i)
            //Résolution du bug de disparition du boss lorsque attaque spécial au dessus de lui
            if (Space[i][Column] != KInsideBoss && Space[i][Column] != KInsideUltraBoss && Space[i][Column] != KInsideMe )
                Space[i][Column] = KBossSpecialWeapon;


    }




        //Manage Generique !!!
        void ManageInvaders (unsigned Who, int & Increment, unsigned & CurrentLine, unsigned & Beg, bool & Win, bool & Lost, CVString & Space, unsigned & End,
                             bool & IncomingBossAttack, bool & BossShoot, unsigned & CptShoot, pair <unsigned, unsigned> & PosShoot,
                             pair <unsigned, unsigned> & PosUltraShoot, unsigned HowMany, const unsigned & Level)
        {
            char Invader;
            char Weapon;
            //On gère les powersups dans le menage invaders
            if(CurrentLine > 0 && rand()%5 == 1) Space[0][Space[0].size()-1] = PowerUps[rand()%PowerUps.size()-1];
            //On vérifie quel type d'envahisseur on menage
            if (Who == 1)
            {
                Invader = KInsideInvader;
                Weapon = KMissile;


            }
            else if (Who == 2)
            {
                Invader = KInsideBoss;
                Weapon = KBossWeapon;

            }
            else if (Who == 3)
            {

                Invader = KInsideUltraBoss;
                Weapon = KUltraBossWeapon;

            }
            //Si on est en bout de ligne on descent et on va dans l'autre sens !

            if((Space[CurrentLine][Space[0].size()-1] == Invader && Increment == 1) || (Space[CurrentLine][0] == Invader && Increment == -1))
            {
                DownShift(Space, CurrentLine, Lost, Win);
                ++CurrentLine;
                Increment = Increment * (-1);
            }
            //Sinon on continue le chemin sur la ligne
            else
            {
                if (Increment == 1)
                    for(unsigned j (Beg+1); --j > 0;)
                    {
                        swap(Space[CurrentLine][j], Space[CurrentLine][j-1]);
                    }
                else
                    for(unsigned j (End-1); j < Space[0].size() -1; ++j)
                        swap(Space[CurrentLine][j], Space[CurrentLine][j+1]);
                Beg += Increment;
                End += Increment;
            }
            //Quoi qu'il arrive on tire, pûis on a 1 chance sur 3 pour tiré une deuxieme munition
            if(Who != 1 && rand()%3 == 1) Shoot(Space, CurrentLine+1, End+rand()%(Beg-End), Weapon, Invader);
            Shoot(Space, CurrentLine+2, End+rand()%(Beg-End), Weapon, Invader);

            //L'attaque spéciale, si elle a n'a pas été activé
            if(Who != 1 && !BossShoot)
            {
                //On lance un dé ! 1 chance sur 7 pour que le tire s'active
                if(rand()%5 == 1)
                {
                    BossShoot = true;
                    PosShoot.first = rand()%(Space[0].size()-1);
                    PosShoot.second = CurrentLine - 1;
                    IncomingBossAttack = true;
                }
            }
            //Sinon si le compteur descent à 0 (compteur avant l'attaque) on tire !!!
            else if( Who != 1 && CptShoot == 0)
            {
                Shoot2(Space, PosShoot.second, PosShoot.first);
                CptShoot = KBossShoot;
                BossShoot = false;
            }
            //Sinon bah on descent le compteur :)
            else if (Who != 1)
            {
                IncomingBossAttack = false;
                --CptShoot;
            }



            //Sinon si le compteur descent à 0 (compteur avant l'attaque) on tire !!!
            if( Who > 2 && HowMany%50 == 0)
            {
                Shoot3(Space, PosUltraShoot.second, PosUltraShoot.first);
                ++PosUltraShoot.first;
                --PosUltraShoot.second;
            }



        }

    //Fonction Konami qui test si le Konami code a été rentré !
    void Konami(vector <char> & Konami, char c, bool & IsKonami)
    {
        if(c != '\0')
        {
            Konami.erase(Konami.begin());
            Konami.push_back(char(c));
        }
        vector <char> KonamiCode = {'z', 'z', 's', 's', 'q', 'd', 'q', 'd', 'b', 'a'};
        if(Konami == KonamiCode) IsKonami = true;
    }

    //Fonction qui gére le joueur
    void ManageMe (CVString & Space, unsigned & Pos, unsigned & Bullet, vector <char> & KonamiTab, bool & IsKonami, unsigned Time)
    {
        // Lit la structure "termios" de l'entrée standard
        struct termios tios;
        tcgetattr(STDIN_FILENO, &tios);

        //Sauve l'ancien flag "c_lflag"
        tcflag_t old_c_lflag = tios.c_lflag;



        // Passe en mode de saisie non canonique
        // VMIN = 0 donc au min 0 carac et VTIME = 3 donc toute les 3/10s ça valide
        tios.c_lflag &= ~(ICANON|ECHO);
        tios.c_cc[VTIME] = Time;
        tios.c_cc[VMIN] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &tios);
        // FIN DE LA MODIFICATION DU FONCTIONNEMENT PAR DEFAUT DU TERMINAL */

        char c;
        bool Action = false;
        bool Quit = false;

            read(STDIN_FILENO, &c, 1); // Lit un caractére sur l'entrée standard

            //ToLower(c);
           if(c == KShoot) {
               if (Bullet > 0) {
                    #ifdef SOUND
                    JoueLeSon(0);
                    #endif
                   Shoot(Space, Space.size() - 2, Pos, KTorpedo, KInsideMe);
                   --Bullet;
               }
               Action = true;

           }
            else if (c == KLeft) {
               if (Pos > 0) {
                   swap(Space[Space.size() - 1][Pos], Space[Space.size() - 1][Pos - 1]);
                   Pos -= 1;
               }
               Action = true;

           }
            else if (c == KRight) {
               if (Pos < Space[0].size() - 1) {
                   swap(Space[Space.size() - 1][Pos], Space[Space.size() - 1][Pos + 1]);
                   Pos += 1;
               }
               Action = true;

           }
           /*     case 27:
                    Quit = true;
                    Action = true;
                    break;
                default:
                    Action = true;
                    break;
            }*/

        tios.c_lflag = old_c_lflag;
        tcsetattr(STDIN_FILENO, TCSANOW, &tios);
        if(Quit) exit(0);
        Konami(KonamiTab, c, IsKonami);
    }
    void Menu ();
    void SpaceInvaders ();
    char Read ();
    void BonusChoise();

    //Menuaprès avoir fini !
    void DisplayScore(const bool & Win, const bool & Lost, unsigned & NbLives, unsigned & Bullet, float & Score, float & MultScore)
    {
        char ChoixMenu;
        cout << "You ";
        if (Win)
        {
            cout << "win ! :)" << endl;
            cout << endl;
            Score = Score + (Bullet*100*MultScore) + (NbLives*1000*MultScore);
            cout << "Score : " << Score << endl;
        }

        else if (Lost)
        {
            cout << "lost ! :(" << endl;
            #ifdef SOUND
            JoueLeSon(3);
            #endif
            Score = Score + (Bullet*100*MultScore) + (NbLives*1000*MultScore);
            cout << "Score : " << Score << endl;
        }
        else
            cerr << "Something went wrong..." << endl;

        cout << endl;
        cout << endl;

        cout << "r : Replay" << endl;
        cout << "m : Menu" << endl;
        cout << "e : Exit" << endl;

        ChoixMenu = Read();
        cout << endl;

        switch (ChoixMenu)
        {
            case 'r' :
                SpaceInvaders();
                break;
            case 'm' :
                Menu();
                break;
            default :
                ClearScreen();
                DisplayScore(Win, Lost, NbLives, Bullet, Score, MultScore);
                break;
        }


    }

    void MajKeybind ()
    {
        char key;
        unsigned line = 1;
        ifstream keybindread("bind.key", ios::in);
        if(!keybindread)
        {

            keybindread.close();
            ofstream keybindwrite("bind.key", ios::out | ios::trunc);
            KRight = 'd';  // déplacement vers la droite
            KLeft = 'q';  // Déplacement vers la gauche
            KShoot = 'z'; // tirer
            keybindwrite << KRight << KLeft << KShoot;
        }


        else
        {
            while(keybindread.get(key))
            {
                if(line == 1) KRight = key;
                else if(line == 2) KLeft = key;
                else if(line == 3) KShoot = key;
                ++line;
            }
        }


    }    //Menu général

    string Espaces (unsigned NbEspace = 13)
    {
        string Espaces;
        for (unsigned i (0); i < NbEspace; ++i)
            Espaces += " ";
        return Espaces;
    }

    void Separateur (unsigned NbSep = 1)
    {
        for(unsigned i (0); i < NbSep; ++i)
            cout << Espaces() << "║" << setw(47) << "║" << endl;

    }

    void OptionsMenu (vector<string> Option)
    {
        for(unsigned i (0); i < Option.size(); ++i)
        {
            cout << Espaces() << "║" << Option[i] << setw(47 - Option[i].size()) << "║" << endl;
            Separateur();
        }
    }

    void MenuHeader ()
    {
        cout << " ____                          ___                     _             " << endl;
        cout << "/ ___| _ __   __ _  ___ ___   |_ _|_ ____   ____ _  __| | ___ _ __ ___ " << endl;
        cout << "\\___ \\| '_ \\ / _` |/ __/ _ \\   | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __|" << endl;
        cout << " ___) | |_) | (_| | (_|  __/   | || | | \\ V / (_| | (_| |  __/ |  \\__ \\ " << endl;
        cout << "|____/| .__/ \\__,_|\\___\\___|  |___|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/" << endl;
        cout << "      |_|    " << endl;
    }

    void DisplayMenu ()
    {
        vector<string> Options = {" p : Play", " c : Commands", " h : Help", " m : Credit", " e : Exit"};

        //Affiche la structure du mnenu ainsi que le contenu
        cout << Espaces() << "╔";
        for(unsigned i (1); i < 20; ++i)
            cout << "═";
        cout << " MENU ";
        for(unsigned i (0); i < 19; ++i)
            cout << "═";
        cout << "╗" << endl;

        Separateur();
        OptionsMenu(Options);

        cout << Espaces() << "╚";
        for(unsigned i (1); i < 45; ++i)
            cout  << "═";
        cout << "╝" << endl;
    }

    char Read ()
    {
        char Var;
        // Lit la structure "termios" de l'entrée standard
        struct termios tios;
        tcgetattr(STDIN_FILENO, &tios);

        //Sauve l'ancien flag "c_lflag"
        tcflag_t old_c_lflag = tios.c_lflag;

        // Passe en mode de saisie non canonique
        // VMIN = 0 donc au min 0 carac et VTIME = 3 donc toute les 3/10s ça valide
        tios.c_lflag &= ~(ICANON|ECHO);
        tios.c_cc[VTIME] = 0;
        tios.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &tios);
        // FIN DE LA MODIFICATION DU FONCTIONNEMENT PAR DEFAUT DU TERMINAL */

        read(STDIN_FILENO, &Var, 1); // Lit un caractére sur l'entrée standard

        tios.c_lflag = old_c_lflag;
        tcsetattr(STDIN_FILENO, TCSANOW, &tios);
        return Var;
    }

    void Menu ()
    {
        char ChoixMenu;

        #ifdef SOUND
        JoueLeSon(5);
        #endif

        ClearScreen();
        MenuHeader();
        DisplayMenu();

        ChoixMenu = Read ();

        char KeyLeft;
        char KeyRight;
        char KeyShoot;

        switch (ChoixMenu)
        {
            case 'p' :
                ClearScreen();
                SpaceInvaders();
                break;
            case 'c' :
            {
                ClearScreen();
                ofstream keybindwrite("bind.key", ios::out | ios::trunc);
                cout << "Key to Move to the left : ";
                cin >> KeyLeft;
                cout << endl;
                cout << "Key to Move to the right : ";
                cin >> KeyRight;
                cout << endl;
                cout << "Key to shoot : ";
                cin >> KeyShoot;
                keybindwrite << KeyRight << KeyLeft << KeyShoot;
                keybindwrite.close();
                MajKeybind();
                Menu();
                break;
            }
            case 'h' :
            {
                ClearScreen();
                cout << KLeft << " : Move to the left." << endl;
                cout << KRight << " : Move to the right." << endl;
                cout << KShoot << " : Shoot." << endl;
                cout << endl;
                cout << "(Press any case to go back)";
                cout << endl;
                ChoixMenu = Read ();
                Menu();
                break;
            }

            case 'm' :
            {
                ClearScreen();
                cout << "programmers :" << endl;
                cout << endl;
                cout << "Diogo DE ALMEIDA" << endl;
                cout << "Tristan DIETZ" << endl;
                cout << "Romain COLONNA D'ISTRIA" << endl;
                cout << "Alexandre CARON" << endl;
                cout << endl;
                cout << endl;
                cout << "(Press any case to go back)";
                cout << endl;
                ChoixMenu = Read ();
                Menu();
                break;
            }

            case 'e' :
                break;
            default :
                ClearScreen();
                Menu();
        }
    }

    inline
    void InitShield (vector <pair<unsigned, unsigned>> & Shield, unsigned Column)
    {
        Shield.resize(0);
        Shield.push_back (make_pair(0, 3));
        Shield.push_back (make_pair((Column-1)/2+((Column-1)/2)/2, 3));
        Shield.push_back (make_pair((Column-1)/2, 3));
        Shield.push_back (make_pair(((Column-1)/2)/2, 3));
        Shield.push_back (make_pair(Column -1, 3));


    }

    void RouletteGame(unsigned & LivesMax, unsigned & BulletMax)
    {


        const vector <char> Lots = {'V', 'V', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'V', 'V', 'V', 'B', 'B', 'B', 'B', 'B', 'B', 'A', 'A'};
        const vector <unsigned> NbLots = {1,2,0,0,0,0,0,0,0,0,0,1,2,1,3,1,1,2,2,1,3,1,2};
        char Wait;
        unsigned Bonus = rand()%Lots.size()-1;
        ClearScreen();
        if(Lots[Bonus] == 'V') {
            cout << "Vous avez remporté " << NbLots[Bonus] << " vie(s) max.";
            LivesMax += NbLots[Bonus];
        }
        else if(Lots[Bonus] == 'B') {
            cout << "Vous avez remporté " << NbLots[Bonus] << " balle(s) max.";
            BulletMax += NbLots[Bonus];

        }

        else if(Lots[Bonus] == 'A') {
            cout << "Vous avez remporté " << NbLots[Bonus] << " vie(s) max et balle(s) max !!!";
            LivesMax += NbLots[Bonus];
            BulletMax += NbLots[Bonus];

        }
        else if(Lots[Bonus] == 'X') {
            cout << "Vous n'avez rien remporté, désolé.";
        }

        cout << endl << "(appuiez sur une touche pour reprendre)";
        Wait = Read ();

    }

    void BonusChoise(unsigned & LivesMax,unsigned & BulletMax, unsigned & Jeton)
    {
        ClearScreen();

        vector<string> Options = {" v : Vie", " b : Balle", " j : Jeton"};

        //Affiche la structure du mnenu ainsi que le contenu
        cout << Espaces() << "╔";
        for(unsigned i (1); i < 17; ++i)
            cout << "═";
        cout << " BONUS TIME ";
        for(unsigned i (0); i < 16; ++i)
            cout << "═";
        cout << "╗" << endl;

        Separateur();
        OptionsMenu(Options);

        cout << Espaces() << "╚";
        for(unsigned i (1); i < 45; ++i)
            cout  << "═";
        cout << "╝" << endl;

        char Choix;
        cin >> Choix;
        switch(Choix)
        {
            case 'z' :
                    ++LivesMax;
                break;
            case 's' :
                    ++BulletMax;
                break;
            case 'j' :
                    if(Jeton > 0) {
                        RouletteGame(LivesMax, BulletMax);
                        --Jeton;
                    }
                    else BonusChoise(LivesMax, BulletMax, Jeton);
                break;
            default :
                BonusChoise(LivesMax, BulletMax, Jeton);
                break;
        }


    }
    void SpaceInvaders ()
    {

        //Les valeurs général initialisé
        CVString Space;
        vector <pair<unsigned, unsigned>> Shield;
        float Score = 0.0;
        float MultScore = 1.0;
        unsigned Jeton = 1;
        unsigned Line = 21;
        unsigned Column = 10;
        InitSpace(Space, Line, Column);
        InitShield(Shield, Column);
        unsigned Time = 6;
        int Increment = 1;
        unsigned CurrentLine = 0;
        unsigned HowMany = 0;
        unsigned Beg = KInvadersSize;
        unsigned End = 0;
        unsigned Pos = ((Space[0].size()-1)/2);
        bool Win = false;
        bool Lost = false;
        bool ToShoot = false;
        unsigned NbLives = KMyLives;
        unsigned Bullet = KMyBullet;
        unsigned LivesMax = KMyLives;
        unsigned BulletMax = KMyBullet;
        ms TimeElapsedMS;
        fsec TimeElapsed;


        //varBoss
        pair <unsigned, unsigned>PosShoot = make_pair(0,0);
        bool IncomingBossAttack = false;
        bool BossShoot = false;
        unsigned CptShoot = KBossShoot;
        unsigned BossLife = 0;


        //varUltraBoss
        pair <unsigned, unsigned>PosUltraShoot = make_pair(0,0);
        bool IncomingUltraBossAttack = false;
        bool BossUltraShoot = false;
        unsigned CptUltraShoot = KUltraBossShoot;
        unsigned UltraBossLife = 0;

        //Konami code def variables
        bool IsKonami = false;
        vector <char> Konami;
        Konami.resize(10);


        unsigned Level = 10;
        unsigned Ratio;
        unsigned Who;
        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsedMS, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife, Level, Score, MultScore, Shield, LivesMax, BulletMax);


        while(Level != 51)
        {
            //Recharge des munitions du mec, le pauvre, il va douiller sinon x)
            Bullet = KMyBullet;
            if(Level%5 == 0) Line -= 1;
            if(Level%4 == 0) Column += 1;
            if(Level%10 == 0) Time -= 1;
            if(Level%10 == 0)
            {
                InitBossSpace(Space, Line, Column);
                InitShield(Shield, Column);
                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KBossSize;
                End = 0;
                Pos = ((Space[0].size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                BossLife = KBossLife;
                Ratio = KRatioMeBoss;
                Who = 2;
                IncomingBossAttack = false;

            }
            else if(Level%50 == 0)
            {
                InitUltraBossSpace(Space, Line, Column);
                InitShield(Shield, Column);
                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KUltraBossSize;
                End = 0;
                Pos = ((Space[0].size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                PosUltraShoot.first = 0;
                PosUltraShoot.second = Space[0].size()-1;
                HowMany = 0;
                UltraBossLife = KUltraBossLife;
                Ratio = KRatioMeUltraBoss;
                Who = 3;
                IncomingBossAttack = false;
            }
            else
            {
               InitSpace(Space, Line, Column);
                InitShield(Shield, Column);

                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KInvadersSize;
                End = 0;
                Pos = ((Space[0].size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                Ratio = KRatioMeInvaders;
                Who = 1;
                IncomingBossAttack = false;
            }

            #ifdef SOUND
            JoueLeSon(6);
            #endif

            while(!Win && !Lost)
            {
                auto Time1 = Time::now();
                //if(TimeElapsedMS >= ms(10000))
                //{
                    TimeElapsed = fsec(0);
                    TimeElapsedMS = ms(0);
                    if(Bullet < BulletMax) {
                        ++Bullet;
                        #ifdef SOUND
                        JoueLeSon(1);
                        #endif
                    }
                //}
                ManageMe(Space, Pos, Bullet, Konami, IsKonami, Time);
                ++HowMany;
                if(HowMany%Ratio == 0)
                    ManageInvaders(Who, Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot,PosUltraShoot, HowMany, Level);
                DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsedMS, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife, Level, Score, MultScore, Shield, LivesMax, BulletMax);
                RecomputeSpace(Space, Win, Lost, NbLives, BossLife, UltraBossLife, Score, MultScore, Shield, LivesMax, Jeton);
                DetectBegEnd(Space, CurrentLine, Beg, End);
                //DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife, Level);
                auto Time2 = Time::now();
                if (Bullet < KMyBullet) TimeElapsed += Time2 - Time1;
                TimeElapsedMS += chrono::duration_cast<ms>(TimeElapsed);
            }
            if(Who == 1) MultScore += KMultScoreByInvader;
            else if (Who == 2 && !Lost && Level < 50) {
                BonusChoise(LivesMax, BulletMax, Jeton);
                MultScore += KMultScoreByBoss;
            }
            else if (Who == 3) MultScore += KMultScoreByUltraBoss;
            if(Lost)
                DisplayScore(Win, Lost, NbLives, Bullet, Score, MultScore);
            ++Level;


        }
        Win = true;
        ClearScreen();
        cout << Couleur(KReset);
        DisplayScore(Win, Lost, NbLives, Bullet, Score, MultScore);
    }



int main ()
{
    #ifdef SOUND
    ChargeLesSons();
    #endif
    ClearScreen();
    MajKeybind ();
    Menu ();

    return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif

#ifdef SOUND
#undef SOUND
#endif
