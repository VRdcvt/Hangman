#include <iostream>
#include <vector>
#include <set>
#include <windows.h>
#include <string>
#include <fstream>
#include <ostream>
#include <conio.h>
#include <mmsystem.h>
#include <time.h>
#include <bitset>
#pragma comment(lib, "Winmm.lib")
using namespace std;


////функция и переменные класса использовалась для перевода списка слов в двоичный вид. более не нужны.
//ifstream in2("answers.txt"); //откуда считываем слова
//ofstream out2("secret.txt"); //куда сохраняем слова
//void Resafe(string answer) {
//    for (size_t k = 0; k < 101; k++) {
//        while (getline(in2, answer)) {
//            for (size_t i = 0; i < answer.size(); i++)
//            {
//                out2 << bitset<8>(answer[i]);
//            }
//             out2 << endl;
//        }
//    }
//}

ifstream in("secret.txt");
int main();

class Game {
    string Key_Word;
    char Your_Letter;
    vector<char> Visible_Letters;
    set<char> Used_Letters;
    int Errors_Count;
    bool Test_for_Error;
    bool Test_For_Victory;
    clock_t Start_Time, End_Time;
public:
    Game() {
        Start_Time = clock();
        Your_Letter = ' ';
        Errors_Count = 0;
        Test_for_Error = 0;
        Test_For_Victory = 0;
        for (size_t i = 0; i < rand() % 101; i++)
            getline(in, Key_Word);
        Key_Word = Decoding_Keyword();
        for (size_t i = 0; i < Key_Word.size(); i++)
            Visible_Letters.insert(Visible_Letters.end(), '_');
    }
    string Decoding_Keyword() {
        string result_str;
        for (int i = 0; i < Key_Word.size(); i += 8) {
            string byte = Key_Word.substr(i, 8);
            char c = bitset<8>(byte).to_ulong();
            result_str.push_back(toupper(c));
        }
        return result_str;
    }
    void Visible_Table() {
        cout << "\t";
        for (size_t i = 0; i < Key_Word.size(); i++)
            cout << Visible_Letters[i] << " ";
        cout << endl;
        Draw_Hangman(Errors_Count);
        cout << "\nиспользованные буквы: ";
        for (auto i: Used_Letters)
            cout << i << " ";
        cout << endl;
    }



    void Try_Answer() {
        while (1) {
            Test_For_Victory = 0;
            system("cls");
            Visible_Table();
            cout << "\n\tвведите букву: " << endl;
            cin >> Your_Letter;
            Your_Letter = toupper((unsigned char)Your_Letter);
            if (Used_Letters.count(Your_Letter)) {
                cout << "эту букву уже искали.\n";
                Sleep(2000);
                continue;
            }
            Used_Letters.insert(Your_Letter);
            break;
        }
        Test_for_Error = 0;
        for (size_t i = 0; i < Key_Word.size(); i++)
        {
            if (Your_Letter == Key_Word[i]) {
                Visible_Letters[i] = Your_Letter;
                PlaySound(TEXT("answer.wav"), NULL, SND_FILENAME | SND_ASYNC);
                Test_for_Error = 1;
            }
        }
        if (Test_for_Error == 0) {
            cout << "\nтакой буквы в слове нет." << endl;
            Sleep(2000);
            PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Errors_Count++;
            if (Errors_Count == 6) {
                system("cls");
                Visible_Table();
                cout << "вы проиграли.\n";
                cout << "количество используемых букв: "<< Used_Letters.size()<<endl;
                cout << "это слово было: " << Key_Word << endl;
                PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
                End_Time = clock();
                cout<<"Время на поиск нужного слова составило: "<< ((double)End_Time - Start_Time)/1000<<" секунд"<<endl;
                End_Game();
            }
        }
        for (int i = 0;i < Visible_Letters.size();i++) {
            if (Visible_Letters[i] == '_')
                Test_For_Victory = 1;
        }
        if (Test_For_Victory == 0) {
            system("cls");
            Visible_Table();
            cout << "вы отгадали слово\n";
            PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "количество используемых букв: " << Used_Letters.size() << endl;
            End_Time = clock();
            cout << "Время на поиск нужного слова составило: " << ((double)End_Time - Start_Time) / 1000 << " секунд" << endl;
            End_Game();
        }
    }



    void End_Game() {
        for (size_t i = 0; i < rand() % 101; i++)
            getline(in, Key_Word);
        Key_Word = Decoding_Keyword();
        Visible_Letters.clear();
        for (size_t i = 0; i < Key_Word.size(); i++)
            Visible_Letters.insert(Visible_Letters.end(), '_');
        Start_Time = 0;
        End_Time = 0;
        Your_Letter = ' ';
        Used_Letters.clear();
        Errors_Count = 0;
        Test_for_Error = 0;
        Test_For_Victory = 0;
        system("pause");
        main();
    }



    void Draw_Hangman(int errors) {
        if (errors == 0) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 1) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 2) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "       /               |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 3) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "       / \\             |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 4) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "       /|\\             |\n";
            cout << "        |              |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 5) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "       /|\\             |\n";
            cout << "        |              |\n";
            cout << "       /               |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
        if (errors == 6) {
            cout << endl;
            cout << "        _______________\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        |              |\n";
            cout << "        O              |\n";
            cout << "       /|\\             |\n";
            cout << "        |              |\n";
            cout << "       / \\             |\n";
            cout << "                       |\n";
            cout << "                       |\n";
            cout << "  _____________________|______\n";
            cout << " |                           |\n";
        }
    }
};



void menu() {
    system("cls");
    cout << "\t\t     Игра Виселица" << endl;
    cout << "\n\t\t    > start";
    cout << "\n\t\t      exit";
    cout << "\n\n\n\n\tPress arrows for move up/down / Press space to select an option";
    COORD c = { 20, 5 };
    int choise = 0;
    while (choise != 32)
    {
        choise = _getch();
        switch (choise)
        {
        case 72:
            PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
            system("cls");
            cout << "\t\t     Игра Виселица" << endl;
            cout << "\n\t\t    > start";
            cout << "\n\t\t      exit";
            cout << "\n\n\n\n\tPress arrows for move up/down / Press space to select an option";
            if (c.Y == 6)
            {
                c.Y--;
                system("cls");
                cout << "\t\t     Игра Виселица" << endl;
                cout << "\n\t\t    > start";
                cout << "\n\t\t      exit";
                cout << "\n\n\n\n\tPress arrows for move up/down / Press space to select an option";
                break;
            }
            break;
        case 80:
            PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (c.Y == 5)
            {
                c.Y++;
                system("cls");
                cout << "\t\t     Игра Виселица" << endl;
                cout << "\n\t\t      start";
                cout << "\n\t\t    > exit";
                cout << "\n\n\n\n\tPress arrows for move up/down / Press space to select an option";
                break;
            }
            break;
        case 32:
            PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
            if (c.Y == 5)
                break;
            if (c.Y == 6)
                exit(1);
            break;
        }
    }
}



int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    //для создания файла со списком слов в двоичной форме
    //string answer;
    //Resafe(answer);

    menu();
    Game Game1;
    while (1) {
        Game1.Try_Answer();
    }
}

