#include "header.h"

int countStringHtml = 100;   //кол-во строк в выходном файле HTML

//Программа ConvertHtml
int main(int argc, char* argv[]) {
    try {
        Check ch(argc, argv);   //проверка введенных аргументов с консоли
    }
    catch (int e) {
        if (e==0) { cout << "Ошибка: в командной строке должно быть 2 или 3 аргумента, читайте документацию" << endl;  return -1; }
        if (e==1) { cout << "Ошибка: первый и второй файл д.б. с расширением .txt" << endl; return -1; }
        if (e==2) { cout << "3-й аргумент д.б. числом" << endl; return -1; }
    }
    set<string> setDictionary;  //множество для хранения словаря
    try {
        LoadDictionary dictionary(argv[1]);   //создаем объект словарь, передавая ссылку по аргументу
        setDictionary = dictionary.getDictionary(); //загружаем словарь
    }
    catch (int e) {
        if (e==0) { cout << "Ошибка, файл больше 2 Mb";  return -1; }
        if (e==1) { cout << "Ошибка, в словаре больше 100 000 строк"; return -1; }
    }
    catch (...) {
        cout << "Что-то пошло не так" ; return -1;
    }
    try {
        ConvertToHtml convert(setDictionary, argv[2]); //создаем объект convert, передавая ссылку по аргументу
        convert.modifyText();  //изменям текст из файла
        convert.buildHtml();   //генерируем HTML файлы
    }
    catch (int e) {
         if (e==0) { cout << "Ошибка, файл больше 2 Mb";  return -1; }
    }
     catch (...) {
        cout << "Что-то пошло не так" ; return -1;
    }
    cout << "Файлы HTML успешно сгенерированы" << endl;
    return 0;
}
