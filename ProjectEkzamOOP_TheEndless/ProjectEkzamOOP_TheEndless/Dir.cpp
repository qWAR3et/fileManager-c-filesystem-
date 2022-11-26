#include "Dir.h"

// Создание каталога
void Dir::create_directory(fs::path path)
{
    fs::create_directory(path);
}
// вывод (с поверхностным вхождением) переданного каталога
void Dir::print(fs::path path)
{
    get_dir(DirPaths, root);
    fs::path textPath = path;
    auto current = fs::current_path();
    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_directory()) //если директория, то выводим только каталоги для работы с ними
        {
            std::cout << entry.path().filename() << " - DIR " << textPath << endl;
        }
        if (entry.is_regular_file()) //если файл, то выводим только каталоги пути к файлам для работы с ними
        {
            std::cout << entry.path().filename() << " - FILE " << textPath << endl;
        }
    }
}
// удаление каталога 
void Dir::reMove(fs::path path)
{
    fs::remove_all(path);
}
// переименование каталога                                      
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
// копирование каталога                                         
void Dir::copy(fs::path from, fs::path to)
{
    try
    {
        fs::copy(from, to, fs::copy_options::recursive);
        cout << "Успешно скопировано\n";
    }
    catch (fs::filesystem_error& exception)
    {
        std::cout
            << "Ошибка копирования " << from << endl
            << exception.what() << endl;
    }
}
// поиск файла (путь, информация о файле ( = _по__умолчанию))
void Dir::search(fs::path path, fs::file_status s)
{
    cout << path;
    if (fs::status_known(s) ? fs::exists(s) : fs::exists(path)) // если тип файла известен, возвращается True
        cout << "\nСуществует\n";
    else
        cout << "\nНе существует\n";
}
// файлов в вектор для систематизации
void Dir::get_dir(vector<string>& vect_paths, const string& current_path)
{
    // обход каталога по встроенной функции filesystem, возвращающей имя и состояние файла. Проходит по всему каталогу
    for (const auto& file : fs::directory_iterator(current_path))
    {
        // Если текущий путь - каталог, после записи вызывает сам себя для дальнейшего прохода
        if (fs::is_directory(file))
        { // ставит в конец вектора строку, конвертированную из пути файла. 
            vect_paths.push_back(file.path().string());
            get_dir(vect_paths, file.path().string());
        }
    }
}
// записывает пути к файлам в vector
void Dir::get_files(vector<string>& paths, const string& current_path) //видим пути только к файлам
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
// вывод доступных директориев из вектора
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
// полное перемещение каталога
void Dir::replace(fs::path from, fs::path to)
{
    if (from == to)
    {
        copy(from, to);
        std::cout << "Предыдущая папка удалена\n";
        reMove(from);
    }
    else
    {
        cout << "Отказано в доступе\n";
    }
}
// вычисление размера каталога
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
//поиск каталога
string Dir::search(const string current_path, string required_path)
{
    for (const auto& file : fs::directory_iterator(current_path))
    {
        if (fs::is_directory(file) && 
            strcmp(fs::path(file).filename().generic_string().c_str(), required_path.c_str()) == 0)
        {
            return "Путь к директории: \n >> " + fs::path(file).string();
        }
    }
    return "Директория не найдена\n";
}