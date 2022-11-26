#pragma once
#include "Dir.h"

class File : public Dir
{
public:
	File() = default;

	void copy_file(fs::path from, fs::path to); // копирование файла (from, to). передаются неиспользуемые значения!!!
	void show_file(fs::path path); // вывод содержимого файла при его обнаружении по переданному пути path
	void create_file(fs::path path); // создание файла
	void reMove(fs::path path);
	string search(const string current_path,string reqiured_path);
};



