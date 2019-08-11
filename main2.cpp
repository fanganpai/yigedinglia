#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#include <utility> //结构pair
#include <queue>
#include <windows.h>
#include "json/json.h"//jsoncpp
#include "Pinyin.h"

using namespace std;
using namespace Json;
typedef char Tone[8];
const unsigned int num = 31648;

int main()
{
    ifstream file;
    ofstream output;
    Value idioms;
    Reader reader;
    file.open("C:\\Users\\ASUS\\Documents\\VSCode\\17\\idiom.json");
    output.open("C:\\Users\\ASUS\\Documents\\VSCode\\17\\output.txt");
    reader.parse(file, idioms);
    for (unsigned int i = 0; i < num; i++)
    {
        String t = idioms[i]["word"].asString(); //读出一个成语
        //auto t2 = idioms[i]["word"].toStyledString(); //读出一个成语
        auto sz = t.size();
        if (sz != 12)
            continue; //不写入非四字的成语
        if (t == "null")
            break;
        output << t << endl; //写入文件
        wchar_t str;
    }
    return 0;
}

/*
//〇依据整理的pinyin
int main()
{
    ifstream file;
    file.open("C:\\Users\\ASUS\\Documents\\VSCode\\17\\output2.txt");
    map<string, bool> Tones;
    while (1)
    {
        Tone a = {0};
        file >> a;
        if (a[0] == 'e' && a[1] == 'n' && a[2] == 'd')
            break;
        Tone b = {0};
        file >> b;
        if (b[0] == 'e' && b[1] == 'n' && b[2] == 'd')
            break;
        Tone c = {0};
        for (size_t i = 0; i < 8; i++)
        {
            if (b[i] == ',')
            {
                b[i] = 0;
                file >> c;
                Tones.emplace(c, 0);
            }
        }
        if (!Tones.emplace(a, 1).second)
            Tones[a] = 1;
        Tones.emplace(b, 0);
    }
    for (auto &&i : Tones)
    {
        if (i.second == false)
        {
            cout << i.first << endl;
        }
    }
    return 0;
}
*/