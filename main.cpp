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
#include <locale>         // std::wstring_convert
#include <codecvt>        // std::codecvt_utf8
#include <CString>
#include <windows.h>
#include "json/json.h"
#include "Pinyin.h"

using namespace std;
using namespace Json;
typedef char Tone[8];
const unsigned int num = 31648;

wstring UTF82WCS(const char* szU8)
{
    //该函数来自https://blog.csdn.net/GoForwardToStep/article/details/53207804
    //预转换，得到所需空间的大小;
    int wcsLen = ::MultiByteToWideChar(65001, NULL, szU8, strlen(szU8), NULL, 0);
 
    //分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
    wchar_t* wszString = new wchar_t[wcsLen + 1];
 
    //转换
    ::MultiByteToWideChar(65001, NULL, szU8, strlen(szU8), wszString, wcsLen);
 
    //最后加上'\0'
    wszString[wcsLen] = '\0';
 
    wstring unicodeString(wszString);
 
    delete[] wszString;
    wszString = NULL;
 
    return unicodeString;
}

//②这个程序从output.txt中取出成语，并转化为拼音，添加进map中 （需要根据运行得出的结果手动修正output中它无法识别的汉字）
int main()
{
    map<string, bool> Tones;
    //wifstream file;
    ifstream file;
    file.open("C:\\Users\\ASUS\\Documents\\VSCode\\17\\output.txt");
    while (!file.eof())
    {
        char cary[16];
        wchar_t wc;
        file.getline(cary,16);//读出一个成语
        auto ws = UTF82WCS(cary);//转为wstring
        wc = ws[0];
        vector<string> A;
        vector<string> B;
        try
        {
            A = Tonetranser.GetPinyins(wc);
        }catch(std::out_of_range e)
        {
            cerr<<e.what()<<endl;
            string errorsitu(cary);
            cerr<<errorsitu<<endl;
            continue;
        }
        wc = *(ws.end()-1);
        try
        {
            B = Tonetranser.GetPinyins(wc);
        }catch(std::out_of_range e)
        {
            cerr<<e.what()<<endl;
            string errorsitu(cary);
            cerr<<errorsitu<<endl;
            continue;
        }
        for (auto &&i : A)
        {
            if (!Tones.emplace(i, 1).second)
                Tones[i] = 1;
            //加入map，已经存在则flag置0
        }
        for (auto &&i : B)
        {
            Tones.emplace(i, 0).second;
            //加入map，已经存在则无效，不用管
        }
    }
    for (auto &&i : Tones)
    {
        if (i.second == false)
        {
            cout<< i.first << endl;
        }
    }
    system("pause");
    return 0;
}

/*
//①这个程序用来从json文件中读取成语列表，以Unicode的形式输出到output.txt中
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
        auto t = idioms[i]["word"].asString(); //读出一个成语
        auto sz = t.size();
        if (sz != 12)
            continue; //不写入非四字的成语
        if (t == "null")
            break;
        output << t << endl; //写入文件
    }
    return 0;
}
*/

/*
//〇依据kqwyf整理的pinyin
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