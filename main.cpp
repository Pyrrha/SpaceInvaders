#include <termios.h> //FLAG
#include <iostream>
#include <vector>
#include <iomanip> //setw
#include <stdio.h>
#include <unistd.h> //sleep
#include <chrono> //AVEC CTIME, pour un chrono pour le rechargement des bullets
#include <ctime>
#include <fstream>

//#define DEBUG



using namespace std;

namespace {

    // Constantes couleurs

    const string KReset   ("0");
    const string KBlack    ("30");
    const string KRed   ("31");
    const string KGreen    ("32");
    const string KYellow   ("33");
    const string KBlue    ("34");
    const string KMAgenta ("35");
    const string KCyan    ("36");

    // Constantes Deplacement

    const char KEmpty               = ' ';  // case vide de l'écran
    char KRight;  // déplacement vers la droite
    char KLeft;  // Déplacement vers la gauche
    char KShoot;  // Lancé de torpille

    //  Constantes liées à l'envahisseur

    const string KInvadersColor (KYellow);  // Couleur de l'envahisseur
    const char KInsideInvader       = 'W';  // caractèrere formant l'envahisseur
    const char KMissile             = 'T';  // missile
    const unsigned KInvadersSize    =  5;   // nombre de caractères qui forment l'envahisseur
    const unsigned KInvadersMiddle  = KInvadersSize / 2;
    const string KInvadersForm (KInvadersSize, KInsideInvader);  // forme de l'envahisseur

    //Constantes liées au boss
    const char KInsideBoss          = 'M';  // caractèrere formant le boss
    const char KBossWeapon          = 'I';  // missile
    const char KBossSpecialWeapon   = 'V';  // Missiles de l'attaque spéciale croix-bleue
    const unsigned KBossShoot       = 2;
    const unsigned KBossSize        = 3;
    const unsigned KRatioMeBoss     = 2;
    const string KBossColor         = KRed;
    const string KBossSpecialColor  = KCyan;


    // Constantes liées au joueur

    const string KMyColor (KGreen);
    const char KInsideMe            = 'A';
    const char KTorpedo             = '|';
    const unsigned KMySize          = 1;
    const unsigned KMyMiddle        = KMySize / 2;
    const string KMyForm (KMySize, KInsideMe);
    const unsigned KMyLives			= 4; // Vie du joueur
    const unsigned KMyBullet        = 3; //Nombre de munition
    const unsigned KReloadBullet	= 7; //temps de rechargement

    // Constantes liées à l'eapace (l'écran)

    const unsigned KSizeLine   = 20;   // Nombre de caractères par ligne
    const unsigned KSizeSpace  = 12;   // Nombre de lignes de l'écran (de l'espace)

    const unsigned KBegInvader = 0;    // Numéro de colonne où commence l'envahisseur
    const unsigned KBegMe      = KSizeLine / 2;  // Numéro de colonne où commence le joueur

    typedef vector<string> CVString;    // c'est le type de l'écran (l'espace, la matrice)

    const string KEmptyLine (KSizeLine, KEmpty);  // Une ligne vide de la matrice

    const unsigned KRatioMeInvaders = 4;    // Nombre de fois où c'est le tour du joueur pour un tour de l'envahisseur


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
                       unsigned End, unsigned Beg, unsigned TimeElapsed, bool IsKonami, bool & IncomingAttack, pair <unsigned, unsigned> PosShoot)
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
                    else if (Space[i][j] == KMissile) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KTorpedo) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KBossWeapon) cout << Couleur(KonamiColor[rand()%6]) << setw(2) << char(rand()%(33-126)+33);
                    else if (Space[i][j] == KBossSpecialWeapon) cout << Couleur(KonamiColor[rand()%2]) << setw(2) << KBossSpecialWeapon; //char(rand()%(33-126)+33);

                    else cout << Couleur(KReset) << setw(2) << KEmpty;
                }
                else
                {
                    if (Space[i][j] == KInsideMe) cout << Couleur(KMyColor) << setw(2) << KInsideMe;
                    else if (Space[i][j] == KInsideInvader) cout << Couleur(KInvadersColor) << setw(2) << KInsideInvader;
                    else if (Space[i][j] == KInsideBoss) cout << Couleur(KBossColor) << setw(2) << KInsideBoss;
                    else if (Space[i][j] == KMissile) cout << Couleur(KInvadersColor) << setw(2) << KMissile;
                    else if (Space[i][j] == KTorpedo) cout << Couleur(KMyColor) << setw(2) << KTorpedo;
                    else if (Space[i][j] == KBossWeapon) cout << Couleur(KBossColor) << setw(2) << KBossWeapon;
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
            Space[i].resize(Size);
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
    void RecomputeSpace (CVString & Space, bool & Win, bool & Lost, unsigned & NbLives)
    {

        //On parcous de haut en bas pour faire remonté les missile allié
        for(unsigned i (0); i < Space.size(); ++i)
            for(unsigned j(0); j < Space[i].size(); ++j)
            {

                if(Space[i][j] == KTorpedo && i > 0)
                {
                    if (Space[i-1][j] == KMissile)
                    {
                        Space[i][j] = KEmpty;
                        Space[i-1][j] = KEmpty;
                        continue;
                    }
                    if(Space[i-1][j] == KInsideInvader || Space[i-1][j] == KInsideBoss)
                    {
                        Remove(Space, i-1, j);

                        if (!WhoExist(Space, i-1, KInsideInvader)) Win = true;
                    }
                    else
                        swap(Space[i][j],Space[i-1][j]);
                }
                //Disparition du missile à la case donnée (envahisseur)
                if((Space[i][j] == KMissile || Space[i][j] == KBossWeapon || Space[i][j] == KBossSpecialWeapon) && i == Space.size()-1)
                    Space[i][j] = KEmpty;
                //Bug fixed : rendu du missile spécial bugué
                //Si la case du dessous (si existante) n'est pas un missile spécial alors bug alors efface
                else if ((Space[i][j] == KBossSpecialWeapon) && i < Space.size() && Space[i+1][j] != KBossSpecialWeapon && Space[i+1][j] != KInsideMe)
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
                if((Space[i][j] == KMissile || Space[i][j] == KBossWeapon || Space[i][j] == KBossSpecialWeapon) && i+1 < Space.size())
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
    void Shoot2(CVString & Space,unsigned Line, unsigned Column)
    {

        for(unsigned i(Line); i < Space.size(); ++i)
            //Résolution du bug de disparition du boss lorsque attaque spécial au dessus de lui
            if (Space[i][Column] != KInsideBoss)
                Space[i][Column] = KBossSpecialWeapon;


    }

    //L'"IA" du boss
    void ManageBoss (int & Increment, unsigned & CurrentLine, unsigned & Beg, bool & Win, bool & Lost, CVString & Space, unsigned & End,bool & IncomingBossAttack, bool & BossShoot, unsigned & CptShoot, pair <unsigned, unsigned> & PosShoot)
    {
    //Si on est en bout de ligne on descent et on va dans l'autre sens !
        if((Space[CurrentLine][Space.size()-1] == KInsideBoss && Increment == 1) || (Space[CurrentLine][0] == KInsideBoss && Increment == -1))
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
        if(rand()%3 == 1) Shoot(Space, CurrentLine+1, End+rand()%(Beg-End), KBossWeapon, KInsideBoss);
        Shoot(Space, CurrentLine+2, End+rand()%(Beg-End), KBossWeapon, KInsideBoss);

        //L'attaque spéciale, si elle a n'a pas été activé
        if(!BossShoot)
        {
            //On lance un dé ! 1 chance sur 7 pour que le tire s'active
            if(rand()%7 == 1)
            {
                BossShoot = true;
                PosShoot.first = rand()%(Space.size()-1);
                PosShoot.second = CurrentLine - 1;
                IncomingBossAttack = true;
            }
        }
        //Sinon si le compteur descent à 0 (compteur avant l'attaque) on tire !!!
        else if(CptShoot == 0)
        {
            Shoot2(Space, PosShoot.second, PosShoot.first);
            CptShoot = KBossShoot;
            BossShoot = false;
        }
        //Sinon bah on descent le compteur :)
        else
        {
            IncomingBossAttack = false;
            --CptShoot;
        }


    }

    //Fonction qui gére les invader "normaux", cf ManageBoss sans la spécial attaque
    void ManageInvader (int & Increment, unsigned & CurrentLine, unsigned & Beg, bool & ToShoot, bool & Win, bool & Lost, CVString & Space, unsigned & End)
    {

        if((Space[CurrentLine][Space.size()-1] == KInsideInvader && Increment == 1) || (Space[CurrentLine][0] == KInsideInvader && Increment == -1))
        {
            DownShift(Space, CurrentLine, Lost, Win);
            ++CurrentLine;
            Increment = Increment * (-1);
        }
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

        if(ToShoot)
        {
            if(CurrentLine+1 < Space.size())
                Shoot(Space, CurrentLine+1, End+(Beg-End)/2, KMissile, KInsideInvader);
            ToShoot = false;
        }
        else
            ToShoot = true;

    }

    void ToLower(char & c)
    {

        if(c < 'a' || c > 'z')
            c += 'Z'-'z';

    }

    //Fonction Konami qui test si le konami code a été rentré !
    void Konami(vector <char> & Konami, char c, bool & IsKonami)
    {
        if(c != '\0')
        {
            Konami.erase(Konami.begin());
            Konami.push_back(char(c));
        }
        vector <char> KonamiCode = {'z', 'z', 's', 's', 'q', 'd', 'q', 'd', 'a', 'b'};
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
        unsigned Size = 19;
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

        //Konami code def variables
        bool IsKonami = false;
        vector <char> Konami;
        Konami.resize(10);

        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot);
        start = std::chrono::system_clock::now();
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
            if(HowMany%KRatioMeInvaders == 0)
                ManageInvader(Increment, CurrentLine, Beg, ToShoot, Win, Lost, Space, End);
            RecomputeSpace(Space, Win, Lost, NbLives);
            DetectBegEnd(Space, CurrentLine, Beg, End);
            DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot);
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
        DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot);
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
                ManageBoss(Increment,CurrentLine,Beg,Win,Lost,Space,End,IncomingBossAttack,BossShoot,CptShoot,PosShoot);
            RecomputeSpace(Space, Win, Lost, NbLives);
            DetectBegEnd(Space, CurrentLine, Beg, End);
            DisplaySpace(Space, Win, Lost, NbLives, Bullet, KSizeSpace, End, Beg, TimeElapsed, IsKonami, IncomingBossAttack, PosShoot);
            end = std::chrono::system_clock::now();
        }

        ClearScreen();
        DisplayScore(Win, Lost);

        Couleur(KReset);
    }
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

