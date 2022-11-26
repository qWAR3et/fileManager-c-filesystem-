#include "File.h"
#include "Dir.h"
#include <iostream>
#include <stdio.h> // ���������� ������
#include <conio.h> // ���������� getch
#include <fstream> //���������� ������ � ������ ������
#include <filesystem> //���������� ������������ ����������� �� ������ � �������
#include <cassert> 
#include <string>
#include <windows.h>
#include <direct.h>
#include <stdint.h> // ���������� �������������� ���� ������ � �������


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
    std::cout << "------------������ � ����������----------------\n";
    std::cout << "1. �������� ���������� " << endl;
    std::cout << "2. ������� " << endl;
    std::cout << "3. ������� " << endl;
    std::cout << "4. ������������� " << endl;
    std::cout << "5. ���������� " << endl;
    std::cout << "6. ����������� " << endl;
    std::cout << "7. ��������� ������ " << endl;
    std::cout << "8. ����� ����������" << endl;
    std::cout << "�����, ��� �������� ������ ���������� � ���������� root, ��������� � ����� �������\n";
    std::cout << "-> ";
    std::cin >> var;
    std::system("cls");
}
void FilesWereChosen(int& var)
{
    std::cout << "------------������ � �������----------------\n";
    std::cout << "1. ������� ���� " << endl;
    std::cout << "2. �������� ���������� � ����� (����������)" << endl;
    std::cout << "3. ���������� ���� " << endl;
    std::cout << "4. �������������/����������� ����" << endl;   
    std::cout << "5. ����� �����" << endl;
    std::cout << "6. ������� ����" << endl;
    std::cout << "�����, ��� ����� ������ ���������� � ���������� root, ��������� � ����� �������\n";
    std::cout << "-> ";
    std::cin >> var;
    std::system("cls");
}
void FileInVectNum(int& num, string& dir)
{
    do
    {
        std::cout << "������� ����� ����� � ������: " << endl << "->";
        cin >> num;
    } while (num > pathway_files.size());
    dir = pathway_files[num - 1];
}
void DirInVectNum(int& num, string& dir)
{
    do
    {
        std::cout << "������� ����� ���� � �����: " << endl;
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
        std::cout << "�������� � ��� ������ ��������?\n����������(1)\t����(2)\n-> ";
        std::cin >> var;
        std::system("cls");
        switch (var)
        {

        case 1:
            go.vect(pathway_dir);
            DirectoriesWereChosen(var);
            go.vect(pathway_dir);
            //������ � ������������
            switch (var)
            {
            case 1: //�������� ���������� ��������
                DirInVectNum(temp, dir);
                go.print(dir);
                break;
            case 2: //������� �������
                std::cout << "������� ����� � �������� root (1)" << endl << "������� ���������� � ������ ����� (2)" << endl << "-> ";
                do
                {
                    std::cin >> temp;
                } while (temp != 1 && temp != 2);
                if (temp == 1)
                {
                    std::cout << "������� �������� �����: " << endl << "-> ";
                    std::cin >> dir;
                    dir = rootSlash + dir;
                }
                else
                {
                    DirInVectNum(temp, dir);
                    std::cout << "������� �������� �����: " << endl << "-> ";
                    std::cin >> dir1;
                    dir += "/" + dir1;
                }
                go.create_directory(dir);
                break;
            case 3: //������� ������� 
                DirInVectNum(temp, dir);
                go.reMove(dir);
                break;
            case 4: //������������� �������
                DirInVectNum(temp, dir);
                std::cout << "������� ����� ��� ��������: " << endl << "-> ";
                cin >> dir1;
                go.reName(dir, rootSlash + dir1);
                break;
            case 5: //���������� �������
                std::cout << "������� ����� ���� �����, ������� ������ ����������: " << endl << "-> ";
                DirChoising(temp, dir);
                std::cout << "������� ����� ���� ����� ��� �����������: " << endl << "-> ";
                DirChoising(temp, dir1);
                go.copy(dir, dir1);
                break;
            case 6: //����������� ����������
                std::cout << "������� ����� ���� ������������ �����: " << endl << "-> ";
                DirChoising(temp, dir);
                std::cout << "������� ����� ����� ��� �����������: " << endl << "-> ";               
                DirChoising(temp, dir);
                go.replace(dir, dir1);
                break;
            case 7: //��������� ������ ��������
                DirInVectNum(temp, dir);
                std::cout << go.get_size(dir) << " ����(a)";
                break;
            case 8: //����� ����������
                cout << "������� �������� ����������:" << endl << "-> ";
                std::cin >> dir;
                cout << go.search(root, dir) << endl;
                break;
            }
            break;
        case 2:
            go.vect(pathway_files);
            FilesWereChosen(var);
            go.vect(pathway_files);
            //������ � �������
            switch (var)
            {
            case 1: //������� ����
                std::cout << "������� �������� ������ ����� : " << endl << "-> ";
                std::cin >> dir;
                fgo.create_file(rootSlash + dir);
                break;
            case 2: //�������� ���������� � ���������� � �����
                FileInVectNum(temp, dir);
                fgo.show_file(dir);
                break;
            case 3: //���������� ����
                FileInVectNum(temp, dir);
                std::cout << "������� ����� ����/����� ��� �����: " << endl << "-> ";
                cin >> dir1;
                fgo.copy_file(dir, rootSlash + dir1);
                break;
            case 4: //�������������/����������� ����
                FileInVectNum(temp, dir);
                std::cout << "������� ��� �����: " << endl << "-> ";
                std::cin >> dir1;
                fgo.reName(dir, rootSlash + dir1);
                break;
            case 5: //����� �����
                cout << "������� ��� ����� � �����������:" << endl << "-> ";
                std::cin >> dir;
                cout << fgo.search(root, dir) << endl;
                break;
            case 6: //������� ����
                FileInVectNum(temp, dir);
                fgo.reMove(dir);
                break;
            }
            break;
        }
        del();
        do
        {
            std::cout << "\n� � � � � � � � � � ?\n\t1.��\t2.���" << endl << "-> ";
            cin >> var;
        } while (var != 1 && var != 2);
        std::system("CLS");
    } while (var == 1);
    std::cout << "\n� � � � �\n";
    Sleep(100000);
    return 0;
}