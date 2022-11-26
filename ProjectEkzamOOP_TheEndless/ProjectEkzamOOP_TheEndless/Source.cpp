#include "File.h"
#include "Dir.h"
#include <iostream>
#include <stdio.h> // подключаем потоки
#include <conio.h> // подключаем getch
#include <fstream> //подключаем чтение и запись файлов
#include <filesystem> //подключаем однопоточную бибилиотеку по работе с файлами
#include <cassert> 
#include <string>
#include <windows.h>
#include <direct.h>
#include <stdint.h> // подключаем дополнительные типы данных и макросы


namespace fs = std::filesystem;
using namespace std;
namespace str
{
    std::string root = "root";
    std::string rootSlash = "root/";
    vector<string> pathway_dir;
    vector<string> pathway_files;
}
using namespace str;
void del()
{
    pathway_dir.clear();
    pathway_files.clear();
}
void DirectoriesWereChosen(int& var)
{
    std::cout << "------------Работа с каталогами----------------\n";
    std::cout << "1. Показать содержимое " << endl;
    std::cout << "2. Создать " << endl;
    std::cout << "3. Удалить " << endl;
    std::cout << "4. Переименовать " << endl;
    std::cout << "5. Копировать " << endl;
    std::cout << "6. Переместить " << endl;
    std::cout << "7. Вычислить размер " << endl;
    std::cout << "8. Поиск директории" << endl;
    std::cout << "Важно, все каталоги должны находиться в директории root, созданной в самом проекте\n";
    std::cout << "-> ";
    std::cin >> var;
    std::system("cls");
}
void FilesWereChosen(int& var)
{
    std::cout << "------------Работа с файлами----------------\n";
    std::cout << "1. Создать файл " << endl;
    std::cout << "2. Показать информацию о файле (содержимое)" << endl;
    std::cout << "3. Копировать файл " << endl;
    std::cout << "4. Переименовать/переместить файл" << endl;   
    std::cout << "5. Поиск файла" << endl;
    std::cout << "6. Удалить файл" << endl;
    std::cout << "Важно, все файлы должны находиться в директории root, созданной в самом проекте\n";
    std::cout << "-> ";
    std::cin >> var;
    std::system("cls");
}
void FileInVectNum(int& num, string& dir)
{
    do
    {
        std::cout << "Введите номер папки с файлом: " << endl << "->";
        cin >> num;
    } while (num > pathway_files.size());
    dir = pathway_files[num - 1];
}
void DirInVectNum(int& num, string& dir)
{
    do
    {
        std::cout << "Введите номер пути к папке: " << endl;
        std::cin >> num;
    } while (num > pathway_dir.size());
    dir = pathway_dir[num - 1];
}
void DirChoising(int& num, string& dir)
{
    do
    {
        std::cin >> num;
    } while (num > pathway_dir.size());
    dir = pathway_dir[num - 1];
}


int main()
{
    setlocale(0, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string dir, dir1;
    int var, temp;
    Dir go{ };
    Dir go1{ };
    File fgo{ };
string dirc;
    do {

        go.get_files(pathway_files, root);
        go.get_dir(pathway_dir, root);
        std::cout << "Выберите с чем хотите работать?\nДиректория(1)\tФайл(2)\n-> ";
        std::cin >> var;
        std::system("cls");
        switch (var)
        {

        case 1:
            go.vect(pathway_dir);
            DirectoriesWereChosen(var);
            go.vect(pathway_dir);
            //РАБОТА С ДИРЕКТОРИЯМИ
            switch (var)
            {
            case 1: //показать содержимое каталога
                DirInVectNum(temp, dir);
                go.print(dir);
                break;
            case 2: //создать каталог
                std::cout << "Создать папку в корневой root (1)" << endl << "Создать директорию в другой папке (2)" << endl << "-> ";
                do
                {
                    std::cin >> temp;
                } while (temp != 1 && temp != 2);
                if (temp == 1)
                {
                    std::cout << "Введите название папки: " << endl << "-> ";
                    std::cin >> dir;
                    dir = rootSlash + dir;
                }
                else
                {
                    DirInVectNum(temp, dir);
                    std::cout << "Введите название папки: " << endl << "-> ";
                    std::cin >> dir1;
                    dir += "/" + dir1;
                }
                go.create_directory(dir);
                break;
            case 3: //удалить каталог 
                DirInVectNum(temp, dir);
                go.reMove(dir);
                break;
            case 4: //переименовать каталог
                DirInVectNum(temp, dir);
                std::cout << "Введите новое имя каталога: " << endl << "-> ";
                cin >> dir1;
                go.reName(dir, rootSlash + dir1);
                break;
            case 5: //копировать каталог
                std::cout << "Введите номер пути папки, которую хотите копировать: " << endl << "-> ";
                DirChoising(temp, dir);
                std::cout << "Введите номер пути папки для копирования: " << endl << "-> ";
                DirChoising(temp, dir1);
                go.copy(dir, dir1);
                break;
            case 6: //переместить директорию
                std::cout << "Введите номер пути перемещаемой папки: " << endl << "-> ";
                DirChoising(temp, dir);
                std::cout << "Укажите номер папки для перемещения: " << endl << "-> ";               
                DirChoising(temp, dir);
                go.replace(dir, dir1);
                break;
            case 7: //вычислить размер каталога
                DirInVectNum(temp, dir);
                std::cout << go.get_size(dir) << " байт(a)";
                break;
            case 8: //поиск директории
                cout << "Введите название директории:" << endl << "-> ";
                std::cin >> dir;
                cout << go.search(root, dir) << endl;
                break;
            }
            break;
        case 2:
            go.vect(pathway_files);
            FilesWereChosen(var);
            go.vect(pathway_files);
            //РАБОТА С ФАЙЛАМИ
            switch (var)
            {
            case 1: //создать файл
                std::cout << "Введите название нового файла : " << endl << "-> ";
                std::cin >> dir;
                fgo.create_file(rootSlash + dir);
                break;
            case 2: //показать содержимое и информацию о файле
                FileInVectNum(temp, dir);
                fgo.show_file(dir);
                break;
            case 3: //копировать файл
                FileInVectNum(temp, dir);
                std::cout << "Введите новый путь/новое имя файла: " << endl << "-> ";
                cin >> dir1;
                fgo.copy_file(dir, rootSlash + dir1);
                break;
            case 4: //переименовать/переместить файл
                FileInVectNum(temp, dir);
                std::cout << "Введите имя файла: " << endl << "-> ";
                std::cin >> dir1;
                fgo.reName(dir, rootSlash + dir1);
                break;
            case 5: //поиск файла
                cout << "Введите имя файла с расширением:" << endl << "-> ";
                std::cin >> dir;
                cout << fgo.search(root, dir) << endl;
                break;
            case 6: //удалить файл
                FileInVectNum(temp, dir);
                fgo.reMove(dir);
                break;
            }
            break;
        }
        del();
        do
        {
            std::cout << "\nП р о д о л ж и т ь ?\n\t1.ДА\t2.НЕТ" << endl << "-> ";
            cin >> var;
        } while (var != 1 && var != 2);
        std::system("CLS");
    } while (var == 1);
    std::cout << "\nК о н е ц\n";
    Sleep(100000);
    return 0;
}