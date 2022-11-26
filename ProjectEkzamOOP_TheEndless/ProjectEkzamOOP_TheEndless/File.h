#pragma once
#include "Dir.h"

class File : public Dir
{
public:
	File() = default;

	void copy_file(fs::path from, fs::path to); // ����������� ����� (from, to). ���������� �������������� ��������!!!
	void show_file(fs::path path); // ����� ����������� ����� ��� ��� ����������� �� ����������� ���� path
	void create_file(fs::path path); // �������� �����
	void reMove(fs::path path);
	string search(const string current_path,string reqiured_path);
};



