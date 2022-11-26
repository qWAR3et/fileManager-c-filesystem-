#include "Dir.h"

// �������� ��������
void Dir::create_directory(fs::path path)
{
    fs::create_directory(path);
}
// ����� (� ������������� ����������) ����������� ��������
void Dir::print(fs::path path)
{
    get_dir(DirPaths, root);
    fs::path textPath = path;
    auto current = fs::current_path();
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_directory()) //���� ����������, �� ������� ������ �������� ��� ������ � ����
        {
            std::cout << entry.path().filename() << " - DIR " << textPath << endl;
        }
        if (entry.is_regular_file()) //���� ����, �� ������� ������ �������� ���� � ������ ��� ������ � ����
        {
            std::cout << entry.path().filename() << " - FILE " << textPath << endl;
        }
    }
}
// �������� �������� 
void Dir::reMove(fs::path path)
{
    fs::remove_all(path);
}
// �������������� ��������                                      
void Dir::reName(fs::path from, fs::path to)
{
    error_code e;
    try
    {
        fs::rename(from, to, e);
        throw e;
    }
    catch (std::error_code& exception)
    {
        std::cout << exception.message() << endl;
    }
}
// ����������� ��������                                         
void Dir::copy(fs::path from, fs::path to)
{
    try
    {
        fs::copy(from, to, fs::copy_options::recursive);
        cout << "������� �����������\n";
    }
    catch (fs::filesystem_error& exception)
    {
        std::cout
            << "������ ����������� " << from << endl
            << exception.what() << endl;
    }
}
// ����� ����� (����, ���������� � ����� ( = _��__���������))
void Dir::search(fs::path path, fs::file_status s)
{
    cout << path;
    if (fs::status_known(s) ? fs::exists(s) : fs::exists(path)) // ���� ��� ����� ��������, ������������ True
        cout << "\n����������\n";
    else
        cout << "\n�� ����������\n";
}
// ������ � ������ ��� ��������������
void Dir::get_dir(vector<string>& vect_paths, const string& current_path)
{
    // ����� �������� �� ���������� ������� filesystem, ������������ ��� � ��������� �����. �������� �� ����� ��������
    for (const auto& file : fs::directory_iterator(current_path))
    {
        // ���� ������� ���� - �������, ����� ������ �������� ��� ���� ��� ����������� �������
        if (fs::is_directory(file))
        { // ������ � ����� ������� ������, ���������������� �� ���� �����. 
            vect_paths.push_back(file.path().string());
            get_dir(vect_paths, file.path().string());
        }
    }
}
// ���������� ���� � ������ � vector
void Dir::get_files(vector<string>& paths, const string& current_path) //����� ���� ������ � ������
{
    for (const auto& file : fs::directory_iterator(current_path))
    {
        if (fs::is_directory(file))
        {
            get_files(paths, file.path().string());
        }
        else
        {
            paths.push_back(file.path().string());
        }
    }
}
// ����� ��������� ����������� �� �������
void Dir::vect(vector<string>vect_paths)
{
    for (int i = 0; i < vect_paths.size(); i++)
    {
        if (i < 9)
        {
            cout << " " << i + 1 << "---" << vect_paths[i] << endl;
        }
        else
        {
            cout << i + 1 << "---" << vect_paths[i] << endl;
        }
    }
}
// ������ ����������� ��������
void Dir::replace(fs::path from, fs::path to)
{
    if (from == to)
    {
        copy(from, to);
        std::cout << "���������� ����� �������\n";
        reMove(from);
    }
    else
    {
        cout << "�������� � �������\n";
    }
}
// ���������� ������� ��������
intmax_t Dir::get_size(const string& current_path) 
{
    intmax_t size = 0;
    for (const auto& file : fs::directory_iterator(current_path))
    {
        if (!fs::is_directory(file))
        {
            size += file_size(file);
        }
    }
    return size;
}
//����� ��������
string Dir::search(const string current_path, string required_path)
{
    for (const auto& file : fs::directory_iterator(current_path))
    {
        if (fs::is_directory(file) && 
            strcmp(fs::path(file).filename().generic_string().c_str(), required_path.c_str()) == 0)
        {
            return "���� � ����������: \n >> " + fs::path(file).string();
        }
    }
    return "���������� �� �������\n";
}