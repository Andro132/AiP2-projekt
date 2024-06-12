#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <string.h>
#include <chrono>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
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

bool rijeseno(int polje[][12])
{
    int provjera = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (j > 2 && j < 6 && i < 3)
            {
                if (polje[i][j] == 2)
                    provjera++;
            }
            else if (j < 3 && i > 2 && i < 6)
            {
                if (polje[i][j] == 1)
                    provjera++;
            }
            else if (j > 2 && j < 6 && i > 2 && i < 6)
            {
                if (polje[i][j] == 3)
                    provjera++;
            }
            else if (j > 2 && j < 6 && i > 5)
            {
                if (polje[i][j] == 4)
                    provjera++;
            }
            else if (j > 5 && j < 9 && i > 2 && i < 6)
            {
                if (polje[i][j] == 5)
                    provjera++;
            }
            else if (j > 8 && i > 2 && i < 6)
            {
                if (polje[i][j] == 6)
                    provjera++;
            }
        }
    }
    if (provjera == 54)
        return 1;
    else
        return 0;
}

void f(int polje[][12])
{
    int t[3], t2[3];
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
}

void r(int polje[][12])
{
    int t[3], t2[3];
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
}

void u(int polje[][12])
{
    int t[3], t2[3];
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
}

void b(int polje[][12])
{
    int t[3], t2[3];
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
}

void l(int polje[][12])
{
    int t[3], t2[3];
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
}

void d(int polje[][12])
{
    int t[3], t2[3];
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
}

void F(int polje[][12])
{
    int t[3], t2[3];
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
}

void R(int polje[][12])
{
    int t[3], t2[3];
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
}

void U(int polje[][12])
{
    int t[3], t2[3];
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
}

void B(int polje[][12])
{
    int t[3], t2[3];
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
}

void L(int polje[][12])
{
    int t[3], t2[3];
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
}

void D(int polje[][12])
{
    int t[3], t2[3];
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
}

void random(int polje[][12])
{
    srand(time(0));
    int izvuceni[20], t[3], t2[3];
    for (int i = 0; i < 20; i++)
        izvuceni[i] = rand() % 6 + 1;
    for (int i = 0; i < 20; i++)
    {
        if (izvuceni[i] == 1)
            f(polje);
        else if (izvuceni[i] == 2)
            r(polje);
        else if (izvuceni[i] == 3)
            u(polje);
        else if (izvuceni[i] == 4)
            b(polje);
        else if (izvuceni[i] == 5)
            l(polje);
        else
            d(polje);
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

void initialize_openssl()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl()
{
    EVP_cleanup();
    ERR_free_strings();
}

void hashaj(const char *data, unsigned char *hash, unsigned int &lengthOfHash)
{
    const EVP_MD *md = EVP_sha256();
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, data, strlen(data));
    EVP_DigestFinal_ex(mdctx, hash, &lengthOfHash);
    EVP_MD_CTX_free(mdctx);
}

int main()
{
    int pok = 0;
    char loz[30];
    cout << "\t2d rubikova\n\n";
    cout << "Upisite lozinku: ";
start:
    cin >> loz;
    initialize_openssl();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    hashaj(loz, hash, lengthOfHash);
    char prov[2 * lengthOfHash + 1];
    for (unsigned int i = 0; i < lengthOfHash; i++)
        sprintf(&prov[2 * i], "%02x", hash[i]);
    cleanup_openssl();
    ifstream lozinka("lozinka.txt");
    char hash_loz[2 * lengthOfHash + 1];
    lozinka.read(hash_loz, 2 * lengthOfHash);
    hash_loz[2 * lengthOfHash] = '\0';
    lozinka.close();
    if (strcmp(hash_loz, prov) == 0)
    {
        cout << "\nLozinka je tocna, pristup odobren\n\n";
        char potez;
        int polje[9][12] = {0}, menu, izbor; // deklaracija polja
    label:
        cout << "Upute:\nUpisite jedno od ovih slova: f, r, u, b, l, d\nNavedena slova mogu biti upisana sa ili bez caps lock-a\n\nNapomena: ako upisete malu verziju slova, \nvelika verzija ce napraviti isti potez samo u drugom smijeru\n\nNapomena 2: u bilo kojem trenutku možete upisati slovo 'o' kako bi obnovili kocku, slovo 'e' kako bi izasli iz programa,\nslovo 'M' kako be se vratili na meni, slovo 's' kako bi spremili kocku ili slovo 'p' kako bi preslozili kocku\n\nZelite li igrati normalno ili vremenski, za normalno upišite 1 a za vremenski 2" << endl;
        while (1)
        {
            cin >> izbor;
            cout << "\033[2J\033[1;1H";
            if (izbor == 1)
            {
                while (1)
                {
                meni:
                    cout << "\nMeni:\nUpisite 1 za pocetak sa slozenom kockom\nUpisite 2 za pocetak sa pomjesanom kockom\nUpisite 3 za ucitavanje save slot-a\nUpisite 4 za brisanje save slot-a\nUpisite 5 za odlazak nazad na pocetni odabir\nUpisite 6 za mijenjanje lozinke\nUpisite 7 za hall of fame\n\n";
                    cin >> menu;
                    if (menu == 1)
                    {
                        cout << "\033[2J\033[1;1H";
                        reset(polje);
                        ispis(polje);
                        break;
                    }

                    else if (menu == 2)
                    {
                        cout << "\033[2J\033[1;1H";
                        reset(polje);
                        random(polje);
                        ispis(polje);
                        break;
                    }

                    else if (menu == 3)
                    {
                        cout << "Ako ipak ne zelite ucitati save slot unesite broj 4." << endl;
                        cout << "Koji save slot zelite ucitati? ";
                        int slot;
                        while (1)
                        {
                            cin >> slot;
                            if (slot == 1)
                            {
                                fstream save1("save1.bin", ios::binary | ios::in);
                                save1.read(reinterpret_cast<char *>(polje), sizeof(polje));
                                save1.close();
                                if (polje[3][3] != 0)
                                {
                                    cout << "\033[2J\033[1;1H";
                                    ispis(polje);
                                    break;
                                }
                                else
                                    cout << "Taj save slot je prazan, unesite neki drugi: ";
                            }
                            else if (slot == 2)
                            {
                                fstream save2("save2.bin", ios::binary | ios::in);
                                save2.read(reinterpret_cast<char *>(polje), sizeof(polje));
                                save2.close();
                                if (polje[3][3] != 0)
                                {
                                    cout << "\033[2J\033[1;1H";
                                    ispis(polje);
                                    break;
                                }
                                else
                                    cout << "Taj save slot je prazan, unesite neki drugi: ";
                            }
                            else if (slot == 3)
                            {
                                fstream save3("save3.bin", ios::binary | ios::in);
                                save3.read(reinterpret_cast<char *>(polje), sizeof(polje));
                                save3.close();
                                if (polje[3][3] != 0)
                                {
                                    cout << "\033[2J\033[1;1H";
                                    ispis(polje);
                                    break;
                                }
                                else
                                    cout << "Taj save slot je prazan, unesite neki drugi: ";
                            }
                            else if (slot == 4)
                            {
                                cout << "\033[2J\033[1;1H";
                                goto meni;
                            }
                            else
                                cout << "Slot koji ste unjeli ne postoji, pokusajte ponovno: ";
                        }
                        break;
                    }

                    else if (menu == 4)
                    {
                        cout << "Ako ipak ne zelite izbrisati save slot unesite broj 4." << endl;
                        cout << "Koji slot želite izbrisati? ";
                        int slot;
                        while (1)
                        {
                            cin >> slot;
                            if (slot == 1)
                            {
                                ofstream save1("save1.bin", ios::binary | ios::trunc);
                                save1.close();
                                cout << "\033[2J\033[1;1H";
                                cout << "\nSlot je uspjesno izbrisan\n\n";
                                break;
                            }
                            else if (slot == 2)
                            {
                                ofstream save2("save2.bin", ios::binary | ios::trunc);
                                save2.close();
                                cout << "\033[2J\033[1;1H";
                                cout << "\nSlot je uspjesno izbrisan\n\n";
                                break;
                            }
                            else if (slot == 3)
                            {
                                ofstream save3("save3.bin", ios::binary | ios::trunc);
                                save3.close();
                                cout << "\033[2J\033[1;1H";
                                cout << "\nSlot je uspjesno izbrisan\n\n";
                                break;
                            }
                            else if (slot == 4)
                            {
                                cout << "\033[2J\033[1;1H";
                                goto meni;
                            }
                            else
                                cout << "Slot koji ste unjeli ne postoji, pokusajte ponovno: ";
                        }
                    }

                    else if (menu == 5)
                    {
                        cout << "\033[2J\033[1;1H";
                        goto label;
                    }

                    else if (menu == 6)
                    {
                        char nov_loz[30];
                        cout << "Upisite novu lozinku: ";
                        cin >> nov_loz;
                        const char *data = loz;
                        initialize_openssl();
                        lengthOfHash = 0;
                        hashaj(nov_loz, hash, lengthOfHash);
                        ofstream lozinka("lozinka.txt");
                        for (unsigned int i = 0; i < lengthOfHash; i++)
                            sprintf(&prov[2 * i], "%02x", hash[i]);
                        lozinka << prov;
                        lozinka.close();
                        cout << "\033[2J\033[1;1H";
                        cout << "\nLozinka je uspjesno promijenjena\n";
                        cleanup_openssl();
                    }

                    else if (menu == 7)
                    {
                        cout << "\033[2J\033[1;1H";
                        string ispis;
                        fstream hall_of_fame("hall_of_fame.txt", ios::in);
                        getline(hall_of_fame, ispis);
                        cout << "\nHall of fame:\n";
                        cout << ispis << endl;
                        hall_of_fame.close();
                    }

                    else
                        cout << "Neispravan unos, pokusajte ponovno: ";
                }

                while (1)
                {
                    cout << "\nUpisite jedno od ovih slova: f, r, u, b, l, d\nNavedena slova mogu biti upisana sa ili bez caps lock-a\n";
                    cin >> potez;
                    if (potez == 'f')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        f(polje);
                        ispis(polje);
                    }

                    else if (potez == 'r')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        r(polje);
                        ispis(polje);
                    }

                    else if (potez == 'u')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        u(polje);
                        ispis(polje);
                    }

                    else if (potez == 'b')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        b(polje);
                        ispis(polje);
                    }

                    else if (potez == 'l')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        l(polje);
                        ispis(polje);
                    }

                    else if (potez == 'd')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        d(polje);
                        ispis(polje);
                    }

                    else if (potez == 'F')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        F(polje);
                        ispis(polje);
                    }

                    else if (potez == 'R')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        R(polje);
                        ispis(polje);
                    }

                    else if (potez == 'U')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        U(polje);
                        ispis(polje);
                    }

                    else if (potez == 'B')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        B(polje);
                        ispis(polje);
                    }

                    else if (potez == 'L')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        L(polje);
                        ispis(polje);
                    }

                    else if (potez == 'D')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        D(polje);
                        ispis(polje);
                    }

                    else if (potez == 'o')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        reset(polje);
                        ispis(polje);
                    }

                    else if (potez == 'p')
                    {
                        cout << "\033[2J\033[1;1H";
                        cout << "\n";
                        random(polje);
                        ispis(polje);
                    }

                    else if (potez == 's')
                    {
                        cout << "Ako ipak ne zelite spremiti kocku unesite broj 4." << endl;
                        cout << "Koji save slot zelite zauzeti? ";
                        int slot;
                        while (1)
                        {
                            cin >> slot;
                            if (slot == 1)
                            {
                                fstream save1("save1.bin", ios::binary | ios::out);
                                save1.write(reinterpret_cast<char *>(polje), sizeof(polje));
                                save1.close();
                                break;
                            }
                            else if (slot == 2)
                            {
                                fstream save2("save2.bin", ios::binary | ios::out);
                                save2.write(reinterpret_cast<char *>(polje), sizeof(polje));
                                save2.close();
                                break;
                            }
                            else if (slot == 3)
                            {
                                fstream save3("save3.bin", ios::binary | ios::out);
                                save3.write(reinterpret_cast<char *>(polje), sizeof(polje));
                                save3.close();
                                break;
                            }
                            else if (slot == 4)
                                break;
                            else
                                cout << "Slot koji ste unjeli ne postoji, pokusajte ponovno: ";
                        }
                    }

                    else if (potez == 'e')
                    {
                        cout << "Izlaz iz programa.";
                        goto exit;
                    }

                    else if (potez == 'M')
                    {
                        cout << "\033[2J\033[1;1H";
                        goto meni;
                    }

                    else
                        cout << "\nPotez koji ste unjeli ne postoji, molim da unesete jedan od postojecih poteza." << endl;
                }
            }

            else if (izbor == 2)
            {
                string ime;
                reset(polje);
                random(polje);
                cout << "\nVrijeme je zapocelo\n";
                ispis(polje);
                auto start = chrono::high_resolution_clock::now();
                cout << "\n";
                while (1)
                {
                    if (rijeseno(polje))
                    {
                        auto end = chrono::high_resolution_clock::now();
                        auto duration = chrono::duration_cast<chrono::seconds>(end - start);
                        cout << "Kocka je rijesena, bravo!\n";
                        cout << "Rijesili ste kocku za: " << duration.count() << " sekundi" << endl;
                        fstream hall_of_fame("hall_of_fame.txt", ios::app);
                        cout << "Upisite svoje ime: ";
                        cin >> ime;
                        hall_of_fame << ime << " - " << duration.count() << " sekundi" << endl;
                        hall_of_fame.close();
                        cout << "Vase ime i vrijeme je pohranjeno u hall of fame-u" << endl;
                        goto exit;
                    }
                    else
                    {
                        cin >> potez;
                        if (potez == 'f')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            f(polje);
                            ispis(polje);
                        }

                        else if (potez == 'r')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            r(polje);
                            ispis(polje);
                        }

                        else if (potez == 'u')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            u(polje);
                            ispis(polje);
                        }

                        else if (potez == 'b')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            b(polje);
                            ispis(polje);
                        }

                        else if (potez == 'l')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            l(polje);
                            ispis(polje);
                        }

                        else if (potez == 'd')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            d(polje);
                            ispis(polje);
                        }

                        else if (potez == 'F')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            F(polje);
                            ispis(polje);
                        }

                        else if (potez == 'R')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            R(polje);
                            ispis(polje);
                        }

                        else if (potez == 'U')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            U(polje);
                            ispis(polje);
                        }

                        else if (potez == 'B')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            B(polje);
                            ispis(polje);
                        }

                        else if (potez == 'L')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            L(polje);
                            ispis(polje);
                        }

                        else if (potez == 'D')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            D(polje);
                            ispis(polje);
                        }

                        else if (potez == 'o')
                        {
                            cout << "\033[2J\033[1;1H";
                            cout << "\n";
                            reset(polje);
                            ispis(polje);
                        }

                        else if (potez == 'e')
                        {
                            auto end = chrono::high_resolution_clock::now();
                            auto duration = chrono::duration_cast<chrono::seconds>(end - start);
                            cout << "Rjesavate kocku vec: " << duration.count() << " sekundi" << endl;
                            cout << "Izlaz iz programa.";
                            goto exit;
                        }
                        else
                            cout << "\nPotez koji ste unjeli ne postoji, molim da unesete jedan od postojecih poteza." << endl;
                    }
                }
            }

            else
                cout << "Krivi unos, molimo pokusajte ponovno: ";
        }
    }
    else
    {
        pok++;
        if (pok >= 3)
        {
            cout << "\nPrevise netocnih pokusaja, pristup odbijen";
            goto exit;
        }
        else
        {
            cout << "\nLozinka nije tocna, pokusajte ponovno: ";
            goto start;
        }
    }
exit:
    return 0;
}