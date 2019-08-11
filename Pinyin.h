#pragma once
#include <stdexcept>
#include <vector>
#include <string>
//在https://github.com/wzhe/GetPinyin上稍作修改
typedef short Int16;
typedef int Int32;
typedef long long int Int64;
class myPinyin_t
{
public:
    static bool IsChinese(wchar_t chr);
    static std::vector<std::string> GetPinyins(wchar_t chr);

private:
    static const Int32 MinValue = 12295;
    static const Int32 Part1MinValue = 19968;
    static const Int32 Part1MaxValue = 40869;
    static const Int32 Part2MinValue = 59418;
    static const Int32 Part2MaxValue = 59491;

    static const char *PinyinTable[];
    static const Int64 PinyinCodes[];
    static const Int64 PinyinPart1[];
    static const Int64 PinyinPart2[];

    static const Int64 ling = 175;

    static std::vector<std::string> DecodePinyins(Int64 pinyinCode);
};

extern myPinyin_t Tonetranser;