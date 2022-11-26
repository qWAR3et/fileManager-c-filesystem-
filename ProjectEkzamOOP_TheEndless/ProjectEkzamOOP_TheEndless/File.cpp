#include "File.h"
#include "Dir.h"

std::string UTF8to1251(std::string const& utf8)
{
    std::string s1251;
    for (int i = 0; i < utf8.size(); ++i)
    {
        int b1 = (unsigned char)utf8[i];
        if ((b1 >> 5) == 6)
        {
            int b2 = (unsigned char)utf8[i + 1];
            if ((b1 == 208) && (b2 >= 144 && b2 <= 191))
            {
                s1251 += (char)(b2 + 48);
            }
            else if ((b1 == 209) && (b2 >= 128 && b2 <= 143))
            {
                s1251 += (char)(b2 + 112);
            }
            else if ((b1 == 208) && (b2 == 129))
            {
                s1251 += (char)(b2 + 39);
            }
            else if ((b1 == 209) && (b2 == 145))
            {
                s1251 += (char)(b2 + 39);
            }
            ++i;
        }
        else if ((b1 >> 7) == 0)
        {
            s1251 += b1;
        }
    }
    return s1251;
}
// вывод информации о файле 
void File::show_file(fs::path path)
{
    ifstream file(path);
    auto cur_path = fs::current_path();
    std::string result;
    /*string result;*/
    if (exists(path))
    {
        cout << "\nФайл открыт:\n"
            << "Имя файла: " << path.filename().stem() << endl
            << "Тип файла: " << path.extension() << endl
            << "Путь к проекту с файлом: " << fs::current_path() << endl
            << "Размер файла: " << file_size(path) << " байт\n";  
        if (getline(file, result))
        {
            std::string s1251 = UTF8to1251(result);
            cout << "Содержимое файла: \n" << s1251 << endl;
            while (getline(file, result))
            {
                std::string s1251 = UTF8to1251(result);
                cout << s1251 << endl;
            }
        }
        else cout << "Файл пуст\n";
    }
    else cout << "\nФайл не найден\n";
    file.close();
}
// копирование файла
void File::copy_file(fs::path from, fs::path to)
{
    error_code e;
    try
    {
        if (fs::copy_file(from, to, fs::copy_options::overwrite_existing) == false)
            throw (e);
        cout << "Файл скопирован\n";
    }
    catch (fs::filesystem_error& exception)
    {
        std::cout
            << "Could not copy " << from << endl
            << exception.what() << endl;
    }
}
// создание файла
void File::create_file(fs::path path)
{
    fstream file;
    file.open(path, fstream::out);
    file.close();
}
//удаление файла
void File::reMove(fs::path path)
{
    remove(path);
}
//поиск файла в root
string File::search(const string current_path, string required_path)
{
    for (const auto& file : fs::directory_iterator(current_path))
    {
        if (fs::is_directory(file))
        {
            search(file.path().string(), required_path);
        }                // path -> только имя файла -> в строку -> в char 
        else if (strcmp(fs::path(file).filename().generic_string().c_str(), required_path.c_str()) == 0)
        {
            return "Путь к файлу: \n >> " + fs::path(file).string();
        }
    }
    return "Файл не найден\n";
}
