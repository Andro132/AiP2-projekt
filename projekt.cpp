#include <iostream>
#include <time.h>
using namespace std;

void ispis(int polje[][12])
{
    for (int i = 0; i < 9; i++) // ispis polja
    {
        for (int j = 0; j < 12; j++)
        {
            if (polje[i][j] == 0)
                cout << "  ";
            else if (polje[i][j] == 1)
                cout << " \033[38;5;208m\u25A0\033[0m", polje[i][j];
            else if (polje[i][j] == 2)
                cout << " \033[1;37m\u25A0\033[0m", polje[i][j];
            else if (polje[i][j] == 3)
                cout << " \033[1;32m\u25A0\033[0m", polje[i][j];
            else if (polje[i][j] == 4)
                cout << " \033[38;5;226m\u25A0\033[0m", polje[i][j];
            else if (polje[i][j] == 5)
                cout << " \033[1;31m\u25A0\033[0m", polje[i][j];
            else if (polje[i][j] == 6)
                cout << " \033[1;34m\u25A0\033[0m", polje[i][j];
        }
        cout << "\n";
    }
}

void random(int polje[][12])
{
    srand(time(0));
    int izvuceni[20], t[3], t2[3];
    for (int i = 0; i < 20; i++)
    {
        izvuceni[i] = rand() % 6 + 1;
    }
    for (int i = 0; i < 20; i++)
    {
        if (izvuceni[i] == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5 - i][2];
                t2[i] = polje[5 - i][6];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 3][2] = polje[6][i + 3];
                polje[i + 3][6] = polje[2][i + 3];
                polje[2][i + 3] = t[i];
                polje[6][i + 3] = t2[i];
            }
        }
        else if (izvuceni[i] == 2)
        {
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[2 - i][5];
                t2[i] = polje[5 - i][9];
            }
            for (int i = 0; i < 3; i++) // random shuffle
            {
                polje[i][5] = polje[i + 3][5];
                polje[i + 3][5] = polje[i + 6][5];
                polje[i + 6][5] = t2[i];
                polje[i + 3][9] = t[i];
            }
        }
        else if (izvuceni[i] == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[3][i + 9];
                polje[3][i + 9] = polje[3][i];
                polje[3][i] = polje[3][i + 3];
                polje[3][i + 3] = polje[3][i + 6];
                polje[3][i + 6] = t[i];
            }
        }
        else if (izvuceni[i] == 4)
        {
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[0][5 - i];
                t2[i] = polje[8][5 - i];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[8][i + 3] = polje[i + 3][0];
                polje[0][i + 3] = polje[i + 3][8];
                polje[i + 3][0] = t[i];
                polje[i + 3][8] = t2[i];
            }
        }
        else if (izvuceni[i] == 5)
        {
            for (int i = 0; i < 3; i++)
            {
                t2[i] = polje[5 - i][11];
                t[i] = polje[8 - i][3];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 6][3] = polje[i + 3][3];
                polje[i + 3][3] = polje[i][3];
                polje[i][3] = t2[i];
                polje[i + 3][11] = t[1];
            }
        }
        else if (izvuceni[i] == 6)
        {
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5][i + 9];
                polje[5][i + 9] = polje[5][i + 6];
                polje[5][i + 6] = polje[5][i + 3];
                polje[5][i + 3] = polje[5][i];
                polje[5][i] = t[i];
            }
        }
    }
}

void reset(int polje[][12])
{
    for (int i = 0; i < 9; i++) // inicijalizacija polja
    {
        for (int j = 0; j < 12; j++)
        {
            if (j > 2 && j < 6 && i < 3)
                polje[i][j] = 2;
            else if (j < 3 && i > 2 && i < 6)
                polje[i][j] = 1;
            else if (j > 2 && j < 6 && i > 2 && i < 6)
                polje[i][j] = 3;
            else if (j > 2 && j < 6 && i > 5)
                polje[i][j] = 4;
            else if (j > 5 && j < 9 && i > 2 && i < 6)
                polje[i][j] = 5;
            else if (j > 8 && i > 2 && i < 6)
                polje[i][j] = 6;
        }
    }
}

int main()
{
    char potez;
    int t[3], t2[3];
    int polje[9][12] = {0}, menu; // deklaracija polja
    cout << "Upute:\nUpisite jedno od ovih slova: f, r, u, b, l, d\nNavedena slova mogu biti upisana sa ili bez caps lock-a\n\nNapomena: ako upisete malu verziju slova, \nvelika verzija ce napraviti isti potez samo u drugom smijeru\n\nNapomena 2: u bilo kojem trenutku možete upisati slovo 'o' kako bi obnovili kocku ili slovo 'p' kako bi preslozili kocku\n\n"
         << endl;
    cout << "Zelite li zapoceti igru sa slozenom ili pomijesanom kockom?\nZa slozenu upisite 1 a za pomijesanu upisite 2\n"
         << endl;
    cin >> menu;
    if (menu == 1)
    {
        reset(polje);
        ispis(polje);
    }
    else
    {
        random(polje);
        ispis(polje);
    }
    while (1)
    {
        cin >> potez;
        if (potez == 'f')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[2][5 - i];
                t2[i] = polje[6][5 - i];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[2][i + 3] = polje[i + 3][6];
                polje[6][i + 3] = polje[i + 3][2];
                polje[i + 3][2] = t[i];
                polje[i + 3][6] = t2[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 3];
                polje[3][i + 3] = polje[i + 3][5];
                t2[i] = polje[5 - i][3];
                polje[5 - i][3] = t[i];
                t[i] = polje[5][5 - i];
                polje[5][5 - i] = t2[i];
                polje[i + 3][5] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'r')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[8 - i][5];
                t2[i] = polje[5 - i][9];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 6][5] = polje[i + 3][5];
                polje[i + 3][5] = polje[i][5];
                polje[i][5] = t2[i];
                polje[i + 3][9] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 6];
                polje[3][i + 6] = polje[i + 3][8];
                t2[i] = polje[5 - i][6];
                polje[5 - i][6] = t[i];
                t[i] = polje[5][8 - i];
                polje[5][8 - i] = t2[i];
                polje[i + 3][8] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'u')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[3][i + 6];
                polje[3][i + 6] = polje[3][i + 3];
                polje[3][i + 3] = polje[3][i];
                polje[3][i] = polje[3][i + 9];
                polje[3][i + 9] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[0][i + 3];
                polje[0][i + 3] = polje[i][5];
                t2[i] = polje[2 - i][3];
                polje[2 - i][3] = t[i];
                t[i] = polje[2][5 - i];
                polje[2][5 - i] = t2[i];
                polje[i][5] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'b')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5 - i][0];
                t2[i] = polje[5 - i][8];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 3][0] = polje[8][i + 3];
                polje[i + 3][8] = polje[0][i + 3];
                polje[8][i + 3] = t2[i];
                polje[0][i + 3] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 9];
                polje[3][i + 9] = polje[i + 3][11];
                t2[i] = polje[5 - i][9];
                polje[5 - i][9] = t[i];
                t[i] = polje[5][11 - i];
                polje[5][11 - i] = t2[i];
                polje[i + 3][11] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'l')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[2 - i][3];
                t2[i] = polje[5 - i][11];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i][3] = polje[i + 3][3];
                polje[i + 3][3] = polje[i + 6][3];
                polje[i + 6][3] = t2[i];
                polje[i + 3][11] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i];
                polje[3][i] = polje[i + 3][2];
                t2[i] = polje[5 - i][0];
                polje[5 - i][0] = t[i];
                t[i] = polje[5][2 - i];
                polje[5][2 - i] = t2[i];
                polje[i + 3][2] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'd')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5][i];
                polje[5][i] = polje[5][i + 3];
                polje[5][i + 3] = polje[5][i + 6];
                polje[5][i + 6] = polje[5][i + 9];
                polje[5][i + 9] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[6][i + 3];
                polje[6][i + 3] = polje[i + 6][5];
                t2[i] = polje[8 - i][3];
                polje[8 - i][3] = t[i];
                t[i] = polje[8][5 - i];
                polje[8][5 - i] = t2[i];
                polje[i + 6][5] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'F')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5 - i][2];
                t2[i] = polje[5 - i][6];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 3][2] = polje[6][i + 3];
                polje[i + 3][6] = polje[2][i + 3];
                polje[2][i + 3] = t[i];
                polje[6][i + 3] = t2[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 3];
                polje[3][i + 3] = polje[5 - i][3];
                t2[i] = polje[i + 3][5];
                polje[i + 3][5] = t[i];
                t[i] = polje[5][5 - i];
                polje[5][5 - i] = t2[i];
                polje[5 - i][3] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'R')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[2 - i][5];
                t2[i] = polje[5 - i][9];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i][5] = polje[i + 3][5];
                polje[i + 3][5] = polje[i + 6][5];
                polje[i + 6][5] = t2[i];
                polje[i + 3][9] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 6];
                polje[3][i + 6] = polje[5 - i][6];
                t2[i] = polje[i + 3][8];
                polje[i + 3][8] = t[i];
                t[i] = polje[5][8 - i];
                polje[5][8 - i] = t2[i];
                polje[5 - i][6] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'U')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[3][i + 9];
                polje[3][i + 9] = polje[3][i];
                polje[3][i] = polje[3][i + 3];
                polje[3][i + 3] = polje[3][i + 6];
                polje[3][i + 6] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[0][i + 3];
                polje[0][i + 3] = polje[2 - i][3];
                t2[i] = polje[i][5];
                polje[i][5] = t[i];
                t[i] = polje[2][5 - i];
                polje[2][5 - i] = t2[i];
                polje[2 - i][3] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'B')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[0][5 - i];
                t2[i] = polje[8][5 - i];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[8][i + 3] = polje[i + 3][0];
                polje[0][i + 3] = polje[i + 3][8];
                polje[i + 3][0] = t[i];
                polje[i + 3][8] = t2[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i + 9];
                polje[3][i + 9] = polje[5 - i][9];
                t2[i] = polje[i + 3][11];
                polje[i + 3][11] = t[i];
                t[i] = polje[5][11 - i];
                polje[5][11 - i] = t2[i];
                polje[5 - i][9] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'L')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t2[i] = polje[5 - i][11];
                t[i] = polje[8 - i][3];
            }
            for (int i = 0; i < 3; i++)
            {
                polje[i + 6][3] = polje[i + 3][3];
                polje[i + 3][3] = polje[i][3];
                polje[i][3] = t2[i];
                polje[i + 3][11] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[3][i];
                polje[3][i] = polje[5 - i][0];
                t2[i] = polje[i + 3][2];
                polje[i + 3][2] = t[i];
                t[i] = polje[5][2 - i];
                polje[5][2 - i] = t2[i];
                polje[5 - i][0] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'D')
        {
            cout << "\n";
            for (int i = 0; i < 3; i++)
            {
                t[i] = polje[5][i + 9];
                polje[5][i + 9] = polje[5][i + 6];
                polje[5][i + 6] = polje[5][i + 3];
                polje[5][i + 3] = polje[5][i];
                polje[5][i] = t[i];
            }
            for (int i = 0; i < 2; i++)
            {
                t[i] = polje[6][i + 3];
                polje[6][i + 3] = polje[8 - i][3];
                t2[i] = polje[i + 6][5];
                polje[i + 6][5] = t[i];
                t[i] = polje[8][5 - i];
                polje[8][5 - i] = t2[i];
                polje[8 - i][3] = t[i];
            }
            ispis(polje);
        }

        else if (potez == 'o')
        {
            cout << "\n";
            reset(polje);
            ispis(polje);
        }

        else if (potez == 'p')
        {
            cout << "\n";
            random(polje);
            ispis(polje);
        }
        else
        {
            cout << "\n";
            cout << "Potez koji ste unjeli ne postoji, molim da unesete jedan od postojecih poteza.";
            cout << "\n";
        }
    }
    return 0;
}