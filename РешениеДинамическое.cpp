#include <iostream>
#include <windows.h>

using namespace std;

typedef int (*WordMaking_t)(const char*, char*);
typedef int (*DeleteRepeatingLetter_t)(const char*, char*);
typedef int (*StringInput_t)(char*, const char*);
typedef int (*StringOutput_t)(const char*, const char*);

int main(int argc, char* argv[])
{
    char* Input = nullptr, * Words = nullptr, * Output = nullptr;
    HMODULE hDll;

    SetConsoleOutputCP(CP_UTF8);

    if (argc < 2)
    {
        cout << "Недостаточно параметров!" << endl;
        return 1;
    }

    hDll = LoadLibrary(TEXT("DLL1.dll"));
    
    if (hDll == nullptr) 
    {
        cout << "Проблемы с открытием модуля" << endl;
        return 2;
    }

    auto WordMaking = (WordMaking_t)GetProcAddress(hDll, "WordMaking");
    auto DeleteRepeatingLetter = (DeleteRepeatingLetter_t)GetProcAddress(hDll, "DeleteRepeatingLetter");
    auto StringInput = (StringInput_t)GetProcAddress(hDll, "StringInput");
    auto StringOutput = (StringOutput_t)GetProcAddress(hDll, "StringOutput");

    if (!WordMaking || !DeleteRepeatingLetter || !StringInput || !StringOutput) {
        cout << "Проблемы с функцией в библиотеке" << endl;
        return 2;
    }

    if (StringInput(Input, argv[1]))
        return 1;

    if (WordMaking(Input, Words))
        return 2;

    if (DeleteRepeatingLetter(Words, Output))
        return 3;

    if (StringOutput(Output, argv[2]))
        return 4;

    FreeLibrary(hDll);
    return 0;
}
