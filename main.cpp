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

//#define DEBUG


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

    //Le display qui s'adapte à la taille de la grille et affiche divers élements (vie/minition) --> Bouclier, KMeSpecialWeapon, KUltraBossSpecialWeapon ??
    void DisplaySpace (const CVString & Space, const bool & Win, const bool & Lost, const unsigned & NbLives, const unsigned & Bullet,const unsigned & Size,
                       unsigned End, unsigned Beg, unsigned TimeElapsed, bool IsKonami, bool & IncomingAttack, pair <unsigned, unsigned> PosShoot,
                       const unsigned & BossLife,const unsigned & UltraBossLife, const unsigned & Level)
    {

        //Merci au beau goss de Cedric qui a participé à 200% à la conception du display :)
        ClearScreen();
        string ColBord;
        vector <string> KonamiColor = {KBlue, KCyan, KRed, KGreen, KYellow, KMAgenta};
        srand(time(0));
#ifdef DEBUG
        cout << "Beg : " << Beg << "   End : " << End << "    Shot : " << End+(Beg-End)/2 << "   Temps : " << TimeElapsed << endl;
        cout << "Konami : " << IsKonami << endl;
#endif // define

        //On adapte la couleur de la bordure (soit avec le KonamiCode activé soit en fonction de la vie)
        if (IsKonami)
        {
            ColBord = KonamiColor[rand()%5];
        }
        else
        {
            if(NbLives >= (KMyLives/2)+1) ColBord = KGreen;
            else if(NbLives > 1) ColBord = KYellow;
            else ColBord = KRed;
        }
        cout << "NIVEAU " << Level << endl;
        //On affiche les points de vie restant
        cout << Couleur(KReset) << "Vie : ";
        for(unsigned i(0); i < KMyLives; ++i)
        {
            if(NbLives > i) cout << Couleur(KRed) << " ♥";
            else cout << Couleur(KBlack) << " ♥";
        }
        //On affiche les munitions actuel
        cout << "   " << Couleur(KReset) << "Munitions : ";
        for(unsigned i(0); i < KMyBullet; ++i)
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
        for(unsigned i(1); i < (Space.size()*2)+1/*(Size*2)+1*/; ++i)
            cout << setw(2) << "═";
        cout << setw(2) << "╗" << endl;

        //Et on affiche la grille (En fonction de si le Konami code est activé ou pas) (en placant les colonnes de gauche et de droite)
        for(unsigned i(0); i < Space.size(); ++i)
        {
            cout << setw(2)<< Couleur(ColBord) << "║";
            for(unsigned j(0); j < Space.size(); ++j)
            {

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

                    else cout << Couleur(KReset) << setw(2) << KEmpty;
                }


            }
            cout << Couleur(ColBord)<< setw(2) << "║";
            cout << endl;
        }
        //Puis on affiche le bas du cadre
        cout << setw(2) << Couleur(ColBord) << "╚";
        for(unsigned i(1); i < (Space.size()*2)+1/*(Size*2)+1*/; ++i)
            cout << setw(2) << "═";
        cout << setw(2) << "╝" << endl;


    }

    void InitUltraBossSpace(CVString & Space, unsigned Size)
    {
        Space.resize(0);
        Space.resize(Size);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Size);
        }
        for(unsigned i(0); i < KUltraBossSize; ++i)
            Space[0][i] = KInsideUltraBoss;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Size-1][((Size-1)/2)+i] = KInsideMe;

    }


    //Fonction pour initié la grille en mode "Boss"
    void InitBossSpace(CVString & Space, unsigned Size)
    {


        Space.resize(0);
        Space.resize(Size);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Size);
        }
        for(unsigned i(0); i < KBossSize; ++i)
            Space[0][i] = KInsideBoss;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Size-1][((Size-1)/2)+i] = KInsideMe;




    }

    //Fonction pour inité la grille en mode standard
    void InitSpace (CVString & Space, unsigned Size)
    {

        Space.resize(Size);
        for(unsigned i(0); i < Space.size(); ++i)
        {
            Space[i].resize(0);
            Space[i].resize(Size);
        }
        for(unsigned i(0); i < KInvadersSize; ++i)
            Space[0][i] = KInsideInvader;
        for(unsigned i(0); i < KMySize; ++i)
            Space[Size-1][((Size-1)/2)+i] = KInsideMe;

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
        for(unsigned j(0); j < Space.size(); ++j)
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

    //Fonction qui recalcule la grille en bougeant les missile (allié et ennemie)
    void RecomputeSpace (CVString & Space, bool & Win, bool & Lost, unsigned & NbLives, unsigned & BossLife, unsigned & UltraBossLife)
    {


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
                        continue;
                    }
                    if(Space[i-1][j] == KInsideInvader)
                    {
                        Remove(Space, i-1, j);

                        if (!WhoExist(Space, i-1, KInsideInvader)) Win = true;


                    }
                    else if (Space[i-1][j] == KInsideBoss)
                    {
                        --BossLife;
                        if(BossLife == 0)
                            Win = true;

                    }
                    else if (Space[i-1][j] == KInsideUltraBoss)
                    {
                        --UltraBossLife;
                        if(UltraBossLife == 0)
                            Win = true;
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
                ////Disparition du missile à la case donnée (joueur)
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
                        continue;
                    }
                    else if(Space[i+1][j] == KInsideMe)
                    {
                        --NbLives;
                        Remove(Space, i, j);
                        if(NbLives == 0)
                        {
                            Remove(Space, i+1, j);
                            if (!WhoExist(Space, Space.size()-1, KInsideMe)) Lost = true;
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
            if (Space[i][ColumnA] != KInsideUltraBoss && Space[i][ColumnB] != KInsideUltraBoss)
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
            if (Space[i][Column] != KInsideBoss)
                Space[i][Column] = KBossSpecialWeapon;


    }




        //Manage Generique !!!
        void ManageInvaders (unsigned Who, int & Increment, unsigned & CurrentLine, unsigned & Beg, bool & Win, bool & Lost, CVString & Space, unsigned & End,
                             bool & IncomingBossAttack, bool & BossShoot, unsigned & CptShoot, pair <unsigned, unsigned> & PosShoot,
                             pair <unsigned, unsigned> & PosUltraShoot, unsigned HowMany, const unsigned & Level)
        {
        //Si on est en bout de ligne on descent et on va dans l'autre sens !
            char Invader;
            char Weapon;

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

            if((Space[CurrentLine][Space.size()-1] == Invader && Increment == 1) || (Space[CurrentLine][0] == Invader && Increment == -1))
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
                    for(unsigned j (End-1); j < Space.size() -1; ++j)
                        swap(Space[CurrentLine][j], Space[CurrentLine][j+1]);
                Beg += Increment;
                End += Increment;
            }
            //Quoi qu'il arrive on tire, pûis on a 1 chance sur 3 pour tiré une deuxieme munition
            if(Who != 1 && rand()%3 == 1) Shoot(Space, CurrentLine+1, End+rand()%(Beg-End), Weapon, KInsideBoss);
            Shoot(Space, CurrentLine+2, End+rand()%(Beg-End), Weapon, Invader);

            //L'attaque spéciale, si elle a n'a pas été activé
            if(Who != 1 && !BossShoot)
            {
                //On lance un dé ! 1 chance sur 7 pour que le tire s'active
                if(rand()%5 == 1)
                {
                    BossShoot = true;
                    PosShoot.first = rand()%(Space.size()-1);
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

    //Fonction Konami qui test si le konami code a été rentré !
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
    void ManageMe (CVString & Space, unsigned & Pos, unsigned & Bullet, vector <char> & KonamiTab, bool & IsKonami)
    {
        // Lit la structure "termios" de l'entrée standard
        struct termios tios;
        tcgetattr(STDIN_FILENO, &tios);

        //Sauve l'ancien flag "c_lflag"
        tcflag_t old_c_lflag = tios.c_lflag;



        // Passe en mode de saisie non canonique
        // VMIN = 0 donc au min 0 carac et VTIME = 3 donc toute les 3/10s ça valide
        tios.c_lflag &= ~(ICANON|ECHO);
        tios.c_cc[VTIME] = 3;
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
               if (Pos < Space.size() - 1) {
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

    //Menuaprès avoir fini !
    void DisplayScore(const bool & Win, const bool & Lost)
    {
        unsigned ChoixMenu;
        cout << "Vous venez de terminé la partie et vous avez ";
        if (Win) cout << "gagné ! Félicitation :)" << endl;
        else if (Lost) cout << "perdu ! Dommage, vous ferez mieux la prochaine fois ! :)" << endl;
        else cerr << "euh.. Il semble y avoir un probleme..." << endl;

        cout << "1 : Rejouer" << endl;
        cout << "2 : Menu" << endl;
        cout << "0 : Quitter" << endl;
        cout << endl;
        cout << "Choix : ";
        cin >> ChoixMenu;
        cout << endl;

        switch (ChoixMenu)
        {
            case 1 :
                SpaceInvaders();
                break;
            case 2 :
                Menu();
                break;
            case 0 :
                break;
            default :
                cerr << ChoixMenu << " ne fais pas partis des choix." << endl;
        }

    }

    void MajKeybind ()
    {
        char key;
        unsigned line = 1;
        ifstream keybindread("bind.key", ios::in);
        /*if(!keybindread)
        {*/

            keybindread.close();
            ofstream keybindwrite("bind.key", ios::out | ios::trunc);
            KRight = 'd';  // déplacement vers la droite
            KLeft = 'q';  // Déplacement vers la gauche
            KShoot = 'z'; // tirer
            keybindwrite << KRight << KLeft << KShoot;
        //}

        //FONCTION WORK IN PROGRESS -- By Diogo
        /*else
        {
            while(keybindread.get(key))
            {
                if(line == 1) KRight = key;
                else if(line == 2) KLeft = key;
                else if(line == 3) KShoot = key;
            }
        }*/


    }    //Menu général


/*  _____  ___________ _______   ____ ___
    /     \ \_   _____/ \      \ |    |   \
    /  \ /  \ |    __)_  /   |   \|    |   /
    /    Y    \|        \/    |    \    |  /
    \____|__  /_______  /\____|__  /______/
    \/        \/         \/
*/

void Menu ()
    {
        unsigned ChoixMenu;

        cout << "╔";
        for(unsigned i (1); i < 20; ++i)
            cout << "═";
        cout << " MENU ";

        for(unsigned i (0); i < 19; ++i)
            cout << "═";

        cout << "╗" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "║" << " 1 : jouer" << setw(37) << "║" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "║" << " 2 : Commandes" << setw(33) << "║" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "║" << " 3 : Aide" << setw(38) << "║" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "║" << " 4 : Credit" << setw(36) << "║" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "║" << " 0 : Quitter" << setw(35) << "║" << endl;
        cout << "║" << setw(47) << "║" << endl;
        cout << "╚";

        for(unsigned i (1); i < 45; ++i)
            cout << "═";
        cout << "╝" << endl;
        cout << "Choix : ";
        cin >> ChoixMenu;
        cout << endl;

        switch (ChoixMenu)
        {
            case 1 :
                SpaceInvaders();
                break;
            case 2 : {
                char KeyLeft;
                char KeyRight;
                char KeyShoot;


                ChoixMenu = 2;
                while (ChoixMenu == 2) {
                    // Lit la structure "termios" de l'entrée standard
                    struct termios tios;
                    tcgetattr(STDIN_FILENO, &tios);

                    //Sauve l'ancien flag "c_lflag"
                    tcflag_t old_c_lflag = tios.c_lflag;



                    // Passe en mode de saisie non canonique
                    // VMIN = 0 donc au min 0 carac et VTIME = 3 donc toute les 3/10s ça valide
                    tios.c_lflag &= ~(ICANON);
                    tios.c_cc[VTIME] = 0;
                    tios.c_cc[VMIN] = 1;
                    tcsetattr(STDIN_FILENO, TCSANOW, &tios);
                    // FIN DE LA MODIFICATION DU FONCTIONNEMENT PAR DEFAUT DU TERMINAL */
                    ofstream keybindwrite("bind.key", ios::out | ios::trunc);
                    cout << "Touche pour le déplacement vers la gauche : ";
                    sleep(1);
                    read(STDIN_FILENO, &KeyLeft, 1);
                    cout << endl;
                    cout << "Touche pour le déplacement vers la droite : ";
                    sleep(1);
                    read(STDIN_FILENO, &KeyRight, 1);
                    cout << endl;
                    cout << "Touche pour lancer un missile : ";
                    sleep(1);
                    read(STDIN_FILENO, &KeyShoot, 1);
                    keybindwrite << KeyRight << KeyLeft << KeyShoot;
                    keybindwrite.close();
                    tios.c_lflag = old_c_lflag;
                    tcsetattr(STDIN_FILENO, TCSANOW, &tios);
                    cout << endl;
                    cout << endl;
                    cout << "1 : Retour" << endl;
                    cout << "2 : Recommencer" << endl;
                    cout << endl;
                    cout << "Choix : ";
                    cin >> ChoixMenu;
                    if(ChoixMenu == 1) Menu();
                }
                MajKeybind();
                break;
            }
            case 3 :
                cout << KLeft << " : Se déplacer a gauche." << endl;
                cout << KRight << " : Se déplacer a droite." << endl;
                cout << KShoot << " : Lancer un missile." << endl;
                cout << endl;
                cout << endl;
                cout << "1 : Retour" << endl;
                cout << endl;
                cout << "Choix : ";
                cin >> ChoixMenu;
                switch (ChoixMenu)
                {
                    case 1 :
                        Menu();
                        break;
                    default :
                        cerr << ChoixMenu << " ne fait pas partit des choix." << endl;
                }
                break;
            case 4 :
                cout << "Programmeurs :" << endl;
                cout << endl;
                cout << "Diogo DE ALMEIDA" << endl;
                cout << "Tristan DIETZ" << endl;
                cout << "Romain COLONNA D'ISTRIA" << endl;
                cout << "Alexandre CARON" << endl;
                cout << endl;
                cout << endl;
                cout << "1 : Retour" << endl;
                cout << endl;
                cout << "Choix : ";
                cin >> ChoixMenu;
                switch (ChoixMenu)
                {
                    case 1 :
                        Menu();
                        break;
                    default :
                        cerr << ChoixMenu << " ne fait pas partit des choix." << endl;
                }
                break;
            case 0 :
                break;
            default :
                cerr << ChoixMenu << " n'est pas un choix." << endl;
                break;
        }
    }
    void SpaceInvaders ()
    {

        //Les valeurs général initialisé
        CVString Space;
        unsigned Size = 21;
        InitSpace(Space, Size);
        int Increment = 1;
        unsigned CurrentLine = 0;
        unsigned HowMany = 0;
        unsigned Beg = KInvadersSize;
        unsigned End = 0;
        unsigned Pos = ((Space.size()-1)/2);
        bool Win = false;
        bool Lost = false;
        bool ToShoot = false;
        unsigned NbLives = KMyLives;
        unsigned Bullet = KMyBullet;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        unsigned TimeElapsed = 0;

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


        unsigned Level = 1;
        unsigned Ratio;
        unsigned Who;
        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife, Level);
        start = std::chrono::system_clock::now();


        while(Level != 50)
        {
            //Recharge des munitions du mec, le pauvre, il va douiller sinon x)
            Bullet = KMyBullet;
            if(Level%5 == 0)
            {
                InitBossSpace(Space, Size);
                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KBossSize;
                End = 0;
                Pos = ((Space.size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                BossLife = KBossLife;
                Ratio = KRatioMeBoss;
                Who = 2;

            }
            else if(Level%16 == 0)
            {
                InitUltraBossSpace(Space, Size);
                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KUltraBossSize;
                End = 0;
                Pos = ((Space.size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                PosUltraShoot.first = 0;
                PosUltraShoot.second = Space.size()-1;
                HowMany = 0;
                UltraBossLife = KUltraBossLife;
                Ratio = KRatioMeUltraBoss;
                Who = 3;
            }
            else
            {
                InitSpace(Space, Size);
                Increment = 1;
                CurrentLine = 0;
                HowMany = 0;
                Beg = KInvadersSize;
                End = 0;
                Pos = ((Space.size()-1)/2);
                Win = false;
                Lost = false;
                ToShoot = false;
                Ratio = KRatioMeInvaders;
                Who = 1;

            }

            while(!Win && !Lost)
            {
                TimeElapsed += std::chrono::duration_cast<std::chrono::seconds>
                        (end-start).count();
                //if(TimeElapsed%KReloadBullet == 0)
                //{
                    if(Bullet < KMyBullet)
                        ++Bullet;
                //}
                ManageMe(Space, Pos, Bullet, Konami, IsKonami);
                ++HowMany;
                if(HowMany%Ratio == 0)
                    ManageInvaders(Who, Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot,PosUltraShoot, HowMany, Level);
                RecomputeSpace(Space, Win, Lost, NbLives, BossLife, UltraBossLife);
                DetectBegEnd(Space, CurrentLine, Beg, End);
                DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife, Level);
                end = std::chrono::system_clock::now();
            }
            if(Lost)
                DisplayScore(Win, Lost);
            ++Level;


        }
        Win = true;
        ClearScreen();
        cout << Couleur(KReset);
        DisplayScore(Win, Lost);
        /*while(!Win && !Lost)
        {
            TimeElapsed += std::chrono::duration_cast<std::chrono::seconds>
                    (end-start).count();
            if(TimeElapsed%KReloadBullet == 0)
            {
                if(Bullet < KMyBullet)
                    ++Bullet;
            }
            ManageMe(Space, Pos, Bullet, Konami, IsKonami);
            ++HowMany;
            if(HowMany%KRatioMeInvaders == 0)
                ManageInvaders(1, Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot,PosUltraShoot, HowMany);
            RecomputeSpace(Space, Win, Lost, NbLives, BossLife, UltraBossLife);
            DetectBegEnd(Space, CurrentLine, Beg, End);
            DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife);
            end = std::chrono::system_clock::now();
        }

        if(Lost)
            DisplayScore(Win, Lost);

        //Recharge des munitions du mec, le pauvre, il va douiller sinon x)
        Bullet = KMyBullet;

        InitBossSpace(Space, Size);
        Increment = 1;
        CurrentLine = 0;
        HowMany = 0;
        Beg = KBossSize;
        End = 0;
        Pos = ((Space.size()-1)/2);
        Win = false;
        Lost = false;
        ToShoot = false;
        BossLife = KBossLife;
        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife);
        while(!Win && !Lost)
        {
            TimeElapsed += std::chrono::duration_cast<std::chrono::seconds>
                    (end-start).count();
            if(TimeElapsed%KReloadBullet == 0)
            {
                if(Bullet < KMyBullet)
                    ++Bullet;
            }
            ManageMe(Space, Pos, Bullet, Konami, IsKonami);
            ++HowMany;
            if(HowMany%KRatioMeBoss == 0)
                ManageInvaders(2, Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot,PosUltraShoot, HowMany);
            RecomputeSpace(Space, Win, Lost, NbLives, BossLife, UltraBossLife);
            DetectBegEnd(Space, CurrentLine, Beg, End);
            DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife);
            end = std::chrono::system_clock::now();
        }

        if(Lost)
            DisplayScore(Win, Lost);
*/
        //Recharge des munitions du mec, le pauvre, il va douiller sinon x)
        /*Bullet = KMyBullet;

        InitUltraBossSpace(Space, Size);
        Increment = 1;
        CurrentLine = 0;
        HowMany = 0;
        Beg = KUltraBossSize;
        End = 0;
        Pos = ((Space.size()-1)/2);
        Win = false;
        Lost = false;
        ToShoot = false;
        PosUltraShoot.first = 0;
        PosUltraShoot.second = Space.size()-1;
        HowMany = 0;
        UltraBossLife = KUltraBossLife;
        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife);
        while(!Win && !Lost)
        {
            TimeElapsed += std::chrono::duration_cast<std::chrono::seconds>
                    (end-start).count();
            if(TimeElapsed%KReloadBullet == 0)
            {
                if(Bullet < KMyBullet)
                    ++Bullet;
            }
            ManageMe(Space, Pos, Bullet, Konami, IsKonami);
            ++HowMany;
            if(HowMany%KRatioMeBoss == 0)
                ManageInvaders(3, Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot,PosUltraShoot, HowMany);
            RecomputeSpace(Space, Win, Lost, NbLives, BossLife, UltraBossLife);
            DetectBegEnd(Space, CurrentLine, Beg, End);
            DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot, BossLife, UltraBossLife);
            end = std::chrono::system_clock::now();
        }*/

        //ClearScreen();
        //DisplayScore(Win, Lost);

        //Couleur(KReset);
    }




int main ()
{
    MajKeybind ();
    Menu ();

    return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif

