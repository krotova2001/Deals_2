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

struct Date // встроенная структура даты в структуре дела
{
    int day;
    int month;
    int year;
};

struct Time // встроенная структура времени в структуре дела
{
    int hour;
    int minutes;
};

struct deal // структура одного экземпляра дела 
{
    int id; //уникальный порядковый номер
    int priority; // важность
    char name[50]; // имя
    char information[250]; // описание 
    struct Date date; // дата исполнения 
    struct Time time; // время исполнения
    long int time_id;//метка времени для быстрого поиска по времени
};

deal* Create_deal(deal* Deals_all, int* size) // функция создания экземпляра дела. Принимает указатель на 
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
        cout << "день\n";
        cin >> new_deal.date.day;
        cout << "месяц\n";
        cin >> new_deal.date.month;
        cout << "год\n";
        cin >> new_deal.date.year;
    cout << "Время исполнения\n";
        cout << "часы\n";
        cin >> new_deal.time.hour;
        cout << "минуты\n";
        cin >> new_deal.time.minutes;
        //формируем индекс времени
        new_deal.time_id = new_deal.time.minutes * 525600 + new_deal.time.hour * 8760 + new_deal.date.day * 365 + new_deal.date.month * 12 + new_deal.date.year;
    new_deal.id = (*size)+1; // назначим порядковый номер

    deal* Deals_new = new deal[(*size) + 1]; // создаем новую базу дел, на 1 дело больше чем было
    for (int i = 0; i < *size; i++)
    {
        Deals_new[i] = Deals_all[i]; // скопируем всё туда
    }
    Deals_new[(*size)] = new_deal; // дописываем новое дело в базу
    delete[]Deals_all; // удалим старую массив - базу
    (*size)++; // размер увеличился
    return Deals_new;
}

void Show_deal_all(deal* a, int size) // функция отображения списка всех дел
{
    system("cls"); // очистим экран и выведем подменю
    int choise;
    cout << "Отображаем:\n";
    cout << "Порядку - 1 (время добавления)\n";
    cout << "По приоритету - 2\n";
    cout << "По времени выполнения - 3 \n";
    cout << "Выход в меню - 0\n";
    cin >> choise;
    switch (choise) // выбор отображения
    {
    case 1: // по порядку
        for (int i = 0; i < size; i++)
        {
            cout << "\n";
            cout << "Порядковый номер - " << a[i].id << "\n";
            cout << "Название - " << a[i].name << "\n";
            cout << "Приоритет - " << a[i].priority << "\n";
            cout << "Описание - " << a[i].information << "\n";
            cout << "Срок - " << a[i].date.day <<"/"<< a[i].date.month<<"/"<<a[i].date.year<<"\n";
            cout << "Время - " << a[i].time.hour << ":"<< a[i].time.hour<<"\n";
            cout << "-------------------------------------\n";
        }
        break;
    case 2: // по приоритету
        for (int j=1; j<=4; j++) //перебираем приоритет
        {
            for (int i = 0; i < size; i++)
            {
                if (a[i].priority == j) // выводим в соответствии с приоритетами
                {           
                    cout << "\n";
                    cout << "Приоритет - " << a[i].priority << "\n";
                    cout << "Порядковый номер - " << a[i].id << "\n";
                    cout << "Название - " << a[i].name << "\n";
                    cout << "Описание - " << a[i].information << "\n";
                    cout << "Срок - " << a[i].date.day << "/" << a[i].date.month << "/" << a[i].date.year << "\n";
                    cout << "Время - " << a[i].time.hour << ":" << a[i].time.hour << "\n";
                    cout << "-------------------------------------\n";
                }
            }
        }
        break;
    case 3: //По дате
            {
                int i_min = 0; // будем искать индекс элемента с минимальным индексом времени
                for (int i = 0; i < size; i++)
                {
                    for (int j = 0; j < size - 1; j++)
                        {
                            if (a[i].time_id < a[j].time_id)
                            i_min = i; // пузырьковой сортировко находим
                        }
                    // и выводим
                    cout << "\n";
                    cout << "Приоритет - " << a[i_min].priority << "\n";
                    cout << "Порядковый номер - " << a[i_min].id << "\n";
                    cout << "Название - " << a[i_min].name << "\n";
                    cout << "Описание - " << a[i_min].information << "\n";
                    cout << "Срок - " << a[i_min].date.day << "/" << a[i_min].date.month << "/" << a[i_min].date.year << "\n";
                    cout << "Время - " << a[i_min].time.hour << ":" << a[i_min].time.hour << "\n";
                    cout << "-------------------------------------\n";
                }
                break; 
            }
    case 0:
        return;
    default: // на всякий случай
        return;
        break;
    }

   

}

void Search_deal(deal* a, int size) // функция посика дел
{
    system("cls"); // очистим экран и выведем подменю
    int choise;
    cout << "Поиск по:\n";
    cout << "По названию 1\n";
    cout << "По описанию - 2\n";
    cout << "По времени выполнения - 3 \n";
    cout << "По приоритету - 4 \n";
    cout << "Выход в меню - 0\n";
    cin >> choise;
    switch (choise) // выбор отображения
    {
    case 1:
    {
        char name[50];
        int equal = 0;
        cout << "Введите имя\n";
        cin >> name;
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int l = i; l < 50; l++)
                {
                    if (name[i] != (a[j].name)[i]) { break; }
                    else if (name[i] == (a[j].name)[l]) { equal++; }
                    if (equal > 3)
                    {
                        cout << "\n";
                        cout << "Приоритет - " << a[l].priority << "\n";
                        cout << "Порядковый номер - " << a[l].id << "\n";
                        cout << "Название - " << a[l].name << "\n";
                        cout << "Описание - " << a[l].information << "\n";
                        cout << "Срок - " << a[l].date.day << "/" << a[l].date.month << "/" << a[l].date.year << "\n";
                        cout << "Время - " << a[l].time.hour << ":" << a[l].time.hour << "\n";
                        cout << "-------------------------------------\n";
                        break;
                    }

                }

            }


            cout << "Совпадений не найдено\n";
        }
        break; }
    case 2:
        break;
    case 3:
        break;
    case 4:
    {
        int prior;
        cout << "Введите приоритет";
        cin >> prior;


            break; 
    }
    case 0:
        return;
    

    }
}
deal* Delete_deal(deal* Deals_all, int* size, int id) //функция удаления дела. Принимает массив дел, размер и ID дела
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
    (*size)--;
    delete[]Deals_all;
    return Deals_new;
}

int main()
{
    setlocale(LC_ALL, "Russian");
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
            Deals_all=Create_deal(Deals_all, &size);
            break;
        case 2:
            Search_deal(Deals_all, size);
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
            Deals_all=Delete_deal(Deals_all, &size, choise2);
            break;
        default:
            break;
        }
    } while (choise != 0);
}