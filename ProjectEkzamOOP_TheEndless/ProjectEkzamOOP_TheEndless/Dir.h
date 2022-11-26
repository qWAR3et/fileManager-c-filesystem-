#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <cstdint>

namespace fs = std::filesystem;
using namespace std;
namespace str
{
	extern std::string root; // определёны в Source.cpp
	extern std::vector<std::string> pathway;
	extern vector<string> pathway_dir;
	extern vector<string> pathway_files;   
}
using namespace str;

class Dir
{
protected:
	vector <string> DirPaths;
public:
	Dir() = default;

	void create_directory(fs::path path);
	void print(fs::path path); // поверхностное вхождение и вывод
	virtual void reMove(fs::path path); // удаление файлов
	void reName(fs::path from, fs::path to);
	void copy(fs::path from, fs::path to);
	void search(fs::path path, fs::file_status s = fs::file_status{});
	void get_dir(vector<string>& paths, const string& current_path); // записывает пути к каталогам в vector
	void get_files(vector<string>& paths, const string& current_path); // записывает пути к файлам в vector
	void vect(vector<string> paths);
	void replace(fs::path from, fs::path to);
	virtual string search(const string current_path,string reqiured_path);
	intmax_t get_size(const string& current_path);
};




