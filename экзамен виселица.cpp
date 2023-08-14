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
ifstream in("secret.txt");
int main();
//функция использовалась для перевода списка слов в двоичный вид. более не нужна.
//void resafe(string answer) {
//    for (size_t k = 0; k < 101; k++) {
//        getline(in, answer);
//        while (getline(in, answer)) {
//            for (size_t i = 0; i < answer.size(); i++)
//            {
//                out << bitset<8>(answer[i]);
//            }
//            out << endl;
//        }
//    }
//}
class game {
    string answer;
    char symbol;
    vector<char> visible;
    set<char> used;
    int errors;
    bool flag;
    bool victory;
    clock_t start, end;
public:
    game() {
        start = clock();
        symbol = ' ';
        errors = 0;
        flag = 0;
        victory = 0;
        for (size_t i = 0; i < rand() % 101; i++)
            getline(in, answer);
        answer = morph();
        for (size_t i = 0; i < answer.size(); i++)
            visible.insert(visible.end(), '_');
    }
    string morph() {
        string result_str;
        for (int i = 0; i < answer.size(); i += 8) {
            string byte = answer.substr(i, 8);
            char c = static_cast<char>(bitset<8>(byte).to_ulong());
            result_str.push_back(c);
        }
        return result_str;
    }
    void VisibleTable() {
        cout << "\t";
        for (size_t i = 0; i < answer.size(); i++)
            cout << visible[i] << " ";
        cout << endl;
        step(errors);
    }
    void TryAnswer() {
        while (1) {
            victory = 0;
            system("cls");
            VisibleTable();
            cout << "\n\tвведите букву: " << endl;
            cin >> symbol;
            if (used.count(symbol)) {
                cout << "эту букву уже искали.\n";
                Sleep(2000);
                continue;
            }
            used.insert(symbol);
            break;
        }
        flag = 0;
        for (size_t i = 0; i < answer.size(); i++)
        {
            if (symbol == answer[i]) {
                visible[i] = symbol;
                PlaySound(TEXT("answer.wav"), NULL, SND_FILENAME | SND_ASYNC);
                flag = 1;
            }
        }
        if (flag == 0) {
            cout << "\nтакой буквы в слове нет." << endl;
            Sleep(2000);
            PlaySound(TEXT("error.wav"), NULL, SND_FILENAME | SND_ASYNC);
            errors++;
            if (errors == 6) {
                system("cls");
                VisibleTable();
                cout << "вы проиграли.\n";
                cout << "количество используемых букв: "<<used.size()<<endl;
                cout << "это слово было: " << answer << endl;
                PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
                end = clock();
                cout<<"Время на поиск нужного слова составило: "<< ((double)end - start)/1000<<" секунд"<<endl;
                endgame();
            }
        }
        for (int i = 0;i < visible.size();i++) {
            if (visible[i] == '_')
                victory = 1;
        }
        if (victory == 0) {
            system("cls");
            VisibleTable();
            cout << "вы отгадали слово\n";
            PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "количество используемых букв: " << used.size() << endl;
            end = clock();
            cout << "Время на поиск нужного слова составило: " << ((double)end - start) / 1000 << " секунд" << endl;
            endgame();
        }
    }
    void endgame() {
        for (size_t i = 0; i < rand() % 101; i++)
            getline(in, answer);
        answer = morph();
        visible.clear();
        for (size_t i = 0; i < answer.size(); i++)
            visible.insert(visible.end(), '_');
        start = 0;
        end = 0;
        symbol = ' ';
        used.clear();
        errors = 0;
        flag = 0;
        victory = 0;
        system("pause");
        main();
    }
    void step(int errors) {
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
    int menu11 = 0;
    while (menu11 != 32)
    {
        menu11 = _getch();
        switch (menu11)
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
            {
                break;
            }
            if (c.Y == 6)
            {
                exit(1);
            }
            break;
        }
    }
}
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));
    menu();
    game game1;
    while (1) {
        game1.TryAnswer();
    }
}

