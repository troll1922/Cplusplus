#ifndef HEADER_H
#define HEADER_H

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>   // для функции isdigit
#include <cstdlib>  // для функции atoi
#include <sstream>

using namespace std;

const int LENGTH_FILE = 2097152;  //размер файла 2Mb в байтах

//Класс для загрузки словаря
class LoadDictionary {
    const static int LENGTH_STRING = 100000; //кол-во заданных строк, не более
    const char* fileName;   //имя файла словаря
public:
     LoadDictionary (const char* fileName);
     void chekMemorySize();
     set<string> getDictionary();
};

//Класс для генерации HTML файлов
class ConvertToHtml {
    set<string> setDict;
    vector<string> modText;
    const char* dict;
    const char* text;
public:
    ConvertToHtml(set<string> setDictionary, const char* text);
    void modifyText();
    void buildHtml();
    string Replace(string a,string b,string c);
    void chekMemorySize();
};

//Класс проверки введенных аргументов с консоли
class Check {
    const char* dict;
    const char* text;
    const char* valueHtml;
public:
    Check(int argc, char* argv[]);
    void checking();
};
#endif
