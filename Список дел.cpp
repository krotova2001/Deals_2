/*
Создайте приложение «Список дел».
Приложение должно позволять:
¦ Добавление дел. У дела есть:
• название;
• приоритет;
• описание;
• дата, время исполнения.
¦ Удаление дел.
¦ Редактирование дел.
¦ Поиск дел по:
• названию;
• приоритету;
• описанию;
• дате и времени исполнения.
¦ Отображение списка дел:
• на день;
• на неделю;
• на месяц.
¦ При отображении должна быть возможность сортировки:
• по приоритету;
• по дате и времени исполнения
*/

#include <iostream>
#include <cstdlib>
using namespace std;

struct deal // структура одного экземпляра дела 
{
    int id; //уникальный порядковый номер
    char priority; // важность
    char name[50]; // имя
    char information[250]; // описание 
    char date[10]; // дата исполнения 
    char time[10]; // срок
};

void Create_deal(deal* Deals_all, int* size) // функция создания экземпляра дела. Принимает указатель на 
//базу данных всех дел. Создает новый массив на 1 элемент больше принятого и записывает в новый элемент новый экземпляр
{
    deal new_deal; //создадим и заполним новое дело
    cout << "Важность дела (1-4)\n";
    cin >> new_deal.priority;
    cout << "Название дела\n";
    cin >> new_deal.name;
    cout << "Описание\n";
    cin >> new_deal.information;
    cout << "Дата\n";
    cin >> new_deal.date;
    cout << "Время исполнения\n";
    cin >> new_deal.time;
    new_deal.id = *(size)+1; // назначим порядковый номер

    deal* Deals_new = new deal[(*size) + 1]; // создаем новую базу дел, на 1 дело больше чем было
    for (int i = 0; i < *size; i++)
    {
        Deals_new[i] = Deals_all[i]; // скопируем всё туда
    }
    Deals_new[(*size)] = new_deal; // дописываем новое дело в базу
    Deals_all = Deals_new; //перезапишем указатели
    //delete[]Deals_new; // удалим временный массив - базу
    (*size)++; // размер увеличился

}

void Show_deal_all(deal* a, int size) // функция отображения списка всех дел
{
    for (int i = 0; i < size; i++)
    {
        cout << "\n";
        cout << "Порядковый номер - " << a[i].id << "\n";
        cout << "Название - " << a[i].name << "\n";
        cout << "Приоритет - " << a[i].priority << "\n";
        cout << "Описание - " << a[i].information << "\n";
        cout << "Срок - " << a[i].date << "\n";
        cout << "Время - " << a[i].time << "\n";
        cout << "-------------------------------------\n";
    }
}

void Delete_deal(deal* Deals_all, int* size, int id) //функция удаления дела. Принимает массив дел, размер и ID дела
{
    deal* Deals_new = new deal[(*size) - 1]; // создаем новую базу дел, на 1 дело меньше чем было
    //скопируем в чать нового массива чать до удаляемого элемента
    for (int i = 0; i < (id - 1); i++)
    {
        Deals_new[i] = Deals_all[i]; // скопируем всё туда
    }
    //и после удаляемого элемента
    for (int i = (id - 1); i < (*size) - 1; i++)
    {
        Deals_new[i] = Deals_all[i + 1]; // 
    }
    Deals_all = Deals_new; //перезапишем указатели
    (*size)--;
}

int main()
{
    cout << "Привет, мой юный друг!\n\n";
    int size = 0; // создадим начальный размер массива дел
    int* psize = &size; // указатель на него, чтоб менять из функции
    setlocale(LC_ALL, "Russian");
    deal* Deals_all = new deal[size]; // создадим массив переменной длины для хранения дел - наша база данных
    int choise;
    do {
        //выводим постоянное меню
        cout << "****************************\n";
        cout << "Добавление дел..............1\n";
        cout << "Поиск дел...................2\n";
        cout << "Отображение списка дел......3\n";
        cout << "Редактирование дел..........4\n";
        cout << "Удаление дел................5\n";
        cout << "Выход.......................0\n";
        cout << "****************************\n";
        cin >> choise; // берем выбор
        switch (choise)
        {
        case 1:
            Create_deal(Deals_all, &size);
            break;
        case 2:
            break;
        case 3:
            Show_deal_all(Deals_all, size);
            break;
        case 4:
            break;
        case 5:
            int choise2;
            cout << "Введите ID дела";
            cin >> choise2;
            Delete_deal(Deals_all, &size, choise2);
            break;
        default:
            break;
        }
    } while (choise != 0);


}

