// dllmain.cpp : Определяет точку входа для приложения DLL.

#include <iostream>
#include <fstream>
#include <windows.h>
#include "StringLib.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// ExampleDll.cpp: Defines the exported functions for the DLL application
extern "C" __declspec(dllexport) int IsElementLetter(char element)
{
    return (('a' <= element) && (element <= 'z') || ('A' <= element) && (element <= 'Z') || ('0' <= element) && (element <= '9'));
}

extern "C" __declspec(dllexport) int LenghOfWord(char Word[])
{
    int Length = 0;
    for (; Word[Length] != '\0'; Length++);
    return Length;
}

extern "C" __declspec(dllexport) int WordMaking(char in[], char*& out)  
{
    char* sup1, * sup2;
    bool IsWord = 0;
    int InIndex = 0;
    int OutIndex = 0;

    sup1 = new char[1];

    while (in[InIndex] != '\0')
    {
        if (IsElementLetter(in[InIndex]))
        {
            if (OutIndex % 10 == 0)
            {
                sup2 = new char[OutIndex + 10];
                for (int i = 0; i < OutIndex; i++)
                    *(sup2 + i) = *(sup1 + i);
                delete[] sup1;
                sup1 = sup2;
            }

            *(sup1 + OutIndex) = in[InIndex];
            OutIndex++;

            if (!IsWord)
                IsWord = 1;
        }
        else
        {
            if (IsWord)
            {
                IsWord = 0;

                if (OutIndex % 10 == 0)
                {
                    sup2 = new char[OutIndex + 10];
                    for (int i = 0; i < OutIndex; i++)
                        *(sup2 + i) = *(sup1 + i);
                    delete[] sup1;
                    sup1 = sup2;
                }

                *(sup1 + OutIndex) = ' ';
                OutIndex++;
            }
        }
        InIndex++;
    }

    *(sup1 + OutIndex) = '\0';
    OutIndex++;

    out = sup1;

    return 0;
}

extern "C" __declspec(dllexport) int DeleteRepeatingLetter(char in[], char*& out)
{
    int IsLetterInWord[100] = { 0 };
    int Lengh = 0;
    int InIndex = 0;
    int OutIndex = 0;
    char* sup1, * sup2;

    sup1 = new char[1];

    while (in[InIndex] != '\0')
    {
        if (OutIndex % 10 == 0)
        {
            sup2 = new char[OutIndex + 10];
            for (int i = 0; i < OutIndex; i++)
                *(sup2 + i) = *(sup1 + i);
            delete[] sup1;
            sup1 = sup2;
        }

        if (in[InIndex] != ' ')
        {
            if (IsLetterInWord[((int)in[InIndex]) - 65] == 0)
            {
                IsLetterInWord[((int)in[InIndex]) - 65] = 1;

                *(sup1 + OutIndex) = in[InIndex];
                OutIndex++;
            }
        }
        else
        {
            Lengh = LenghOfWord(sup1);
            for (int i = 0; i < Lengh; i++)
                IsLetterInWord[((int)sup1[i]) - 65] = 0;

            *(sup1 + OutIndex) = ' ';
            OutIndex++;
        }
        InIndex++;
    }

    *(sup1 + OutIndex) = '\0';
    OutIndex++;

    out = sup1;

    return 0;
}

extern "C" __declspec(dllexport) int StringInput(char*& in, char* fname)
{
    char* sup1, *sup2;
    int InIndex = 0;

    std::ifstream TextFile(fname);

    if (!TextFile.is_open())
    {
        std::cout << "Невозможно открыть файл" << fname << std::endl;
        return 1;
    }

    sup1 = new char[1];

    while (!TextFile.eof())
    {
        if (InIndex % 10 == 0)
        {
            sup2 = new char[InIndex + 10];
            for (int i = 0; i < InIndex; i++)
                *(sup2 + i) = *(sup1 + i);
            delete[] sup1;
            sup1 = sup2;
        }

        TextFile.get(*(sup1 + InIndex));
        InIndex++;
    }

    *(sup1 + InIndex) = '\0';
    InIndex++;

    in = sup1;

    TextFile.close();

    return 0;
}

extern "C" __declspec(dllexport) int StringOutput(char out[], char* fname)
{
    std::ofstream TextFile(fname);

    if (!TextFile.is_open())
    {
        std::cout << "Невозможно открыть файл " << fname << std::endl;
        return 1;
    }

    TextFile << out << std::endl;

    TextFile.close();

    return 0;
}
