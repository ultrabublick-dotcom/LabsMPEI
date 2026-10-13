#pragma once

extern "C" __declspec(dllexport) int IsElementLetter(char element);

extern "C" __declspec(dllexport) int LenghOfWord(char Word[]);

extern "C" __declspec(dllexport) int WordMaking(char in[], char*& out);

extern "C" __declspec(dllexport) int DeleteRepeatingLetter(char in[], char*& out);

extern "C" __declspec(dllexport) int StringInput(char*& in, char* fname);

extern "C" __declspec(dllexport) int StringOutput(char out[], char* fname);