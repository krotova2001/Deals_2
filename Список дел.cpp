/*
Создайте приложение «Список дел».
Приложение должно позволять:
¦ Добавление дел. У дела есть:
• название;
• приоритет;
• описание;
• дата, время исполнения.
¦ Удаление дел.
 Редактирование дел.
 Поиск дел по:
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

--доработать поиск
--заменить функции на безопасные, с обработкой ввода
--сохраняться в файл и считываться из него
--статусы завершения операций и красота
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

// здесь мы создаем встроенную структуру С которая содержит текущее время
time_t now = time(0);
tm* time_now = localtime(&now);

char weekday[7][12] = { "Суббота","Воскресенье","Понедельник","Вторник", "Среда","Четверг","Пятница" };
// в глобальной области видимости нам понадобяться длни недели. Массив с названиями

char* zellersAlgorithm(int day, int month, int year) //это готовая фунция определения дня недели
{
    int mon;
    if (month > 2)
        mon = month; //for march to december month code is same as month
    else {
        mon = (12 + month); //for Jan and Feb, month code will be 13 and 14
        year--; //decrease year for month Jan and Feb
    }
    int y = year % 100; //last two digit
    int c = year / 100; //first two digit
    int w = (day + floor((13 * (mon + 1)) / 5) + y + floor(y / 4) + floor(c / 4) + (5 * c));
    w = w % 7;
    return weekday[w];
}

struct Date // встроенная структура даты в структуре дела
{
    int day;
    int month;
    int year=2022;
    int week_int;
    char week[12];
};

struct Time // встроенная структура времени в структуре дела
{
    int hour=9;
    int minutes=00;
};

struct deal // Основная - структура одного экземпляра дела 
{
    int id; //уникальный порядковый номер
    int priority; // важность
    char name[50]; // имя
    char information[250]; // описание 
    struct Date date; // дата исполнения 
    struct Time time; // время исполнения
    char week[12]; // день недели
    long int time_id;//метка времени для быстрого поиска по времени
};

void Show_deal(deal* a, int i) // простая функция показа одного дела. Принимает указатель на элемент массива и номер элемента
{
    cout << "\n";
    cout << "Порядковый номер - " << a[i].id << "\n";
    cout << "Название - " << a[i].name << "\n";
    cout << "Приоритет - " << a[i].priority << "\n";
    cout << "Описание - " << a[i].information << "\n";
    cout << "Срок - " << a[i].date.day << "/" << a[i].date.month << "/" << a[i].date.year << "\n";
    cout << "День недели - " << a[i].week << "\n";
    cout << "Время - " << a[i].time.hour << ":" << a[i].time.hour << "\n";
    cout << "-------------------------------------\n";
}

deal* Create_deal(deal* Deals_all, int* size) // функция создания экземпляра дела. Принимает указатель на 
//базу данных всех дел, возвращает узакатель на новую БД. Создает новый массив на 1 элемент больше принятого и записывает в новый элемент новый экземпляр
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
    //формируем индекс времени для удобства поиска и сортировки по времени
    new_deal.time_id = new_deal.time.minutes * 525600 + new_deal.time.hour * 8760 + new_deal.date.day * 365 + new_deal.date.month * 12 + new_deal.date.year;
    new_deal.id = (*size) + 1; // назначим порядковый номер
    char* week = zellersAlgorithm(new_deal.date.day, new_deal.date.month, new_deal.date.year); // вычисляем день недели
    strcpy(new_deal.week, week);

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
    cout << "Отображаем все дела:\n";
    cout << "Порядку - 1 (время добавления)\n";
    cout << "По приоритету - 2\n";
    cout << "По времени выполнения - 3 \n";
    cout << "На год - 4 \n";
    cout << "На месяц (текущий год) - 5 \n";
    cout << "На эту неделю - 6 \n";
    cout << "На сегодня - 7 \n";
    cout << "Выход в меню - 0\n";
    cin >> choise;
    switch (choise) // выбор отображения
    {
    case 1: // по порядку
        for (int i = 0; i < size; i++)
        {
            Show_deal(a, i);
        }
        break;
    case 2: // по приоритету
        for (int j = 1; j <= 4; j++) //перебираем приоритет
        {
            for (int i = 0; i < size; i++)
            {
                if (a[i].priority == j) Show_deal(a, i); // выводим в соответствии с приоритетами
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
            Show_deal(a, i_min);
        }
        break;
    }
    case 4: // на год
    {
        int year;
        cout << "Введите год";
        cin >> year;
        for (int i = 0; i < size; i++)
        {
            if (a[i].date.year == year) Show_deal(a, i);
        }
        break;
    }
    case 5: // на этот месяц
    {
        int month;
        cout << "Введите месяц";
        cin >> month;
        for (int i = 0; i < size; i++)
        {
            if (a[i].date.month == month) Show_deal(a, i);
        }
        break;
    }
    case 6: // на эту неделю
    {
        for (int i = 0; i < size; i++)
        {
            //сначала ищем какого числа был понедельник на этой неделе
            int monday; // здесь число, которое было в понедельник
            if (time_now->tm_wday!=2) // если сегодня не понедельник (инедкс 2)
            {
                monday = time_now->tm_mday - time_now->tm_wday + 2; // назнаяаем понедельник
            }
            int monday = time_now->tm_mday; // это если сегодня понедельник

            for (int i = 0; i < size; i++)
            {
                //если в этом году в этом месяце число дела находистя между числом воскресенья и понедельника - выводим
                if (a[i].date.day <= monday+7 && a[i].date.month == time_now->tm_mon && a[i].date.year == time_now->tm_year) Show_deal(a, i);
            }
        }
        break;
    }
    case 7: // на сегодня
    {
        for (int i = 0; i < size; i++)
        {
            if (a[i].date.day == time_now->tm_mday&&a[i].date.month == time_now->tm_mon&& a[i].date.year == time_now->tm_year) Show_deal(a, i);
        }
        break;
    }
    case 0:
        return;
    default: // на всякий случай
        return;
    }
}

void Search_deal(deal* a, int size) // функция поиска дел
{
    system("cls"); // очистим экран и выведем подменю
    int choise;
    cout << "Поиск по:\n";
    cout << "По названию - 1\n";
    cout << "По описанию - 2\n";
    cout << "По времени выполнения - 3 \n";
    cout << "По приоритету - 4 \n";
    cout << "Выход в меню - 0\n";
    cin >> choise;
    switch (choise) // выбор отображения
    {
    case 1: // по названию.Алгоритм поиска - не просто строгое сравнивание строк, а частичное. 
    {
        char name[50]; // принимаем название от пользователя
        int equal = 0;
        cout << "Введите имя\n";
        cin >> name;
        for (int i = 0; i < size; i++)
        {
            if (_strnicmp(name, a[i].name, 3)==0)//если хотя бы первые три символа в названии сопадают - выводим результат
            {
                Show_deal(a, i); 
                equal++; // увеличиваем счетчик результатов
            }
        }
        if (equal != 0) cout << "Найдено " <<equal<< " совпадений\n";
        if (equal ==0)  cout << "Совпадений не найдено\n";
        break; 
    }
    case 2: // по описанию
    {
        char information[250]; // принимаем название от пользователя
        int equal = 0;
        cout << "Введите описание\n";
        cin >> information;
        for (int i = 0; i < size; i++)
        {
            if (_strnicmp(information, a[i].information, 5) == 0)//если хотя бы первые три символа в названии сопадают - выводим результат
            {
                Show_deal(a, i);
                equal++; // увеличиваем счетчик результатов
            }
        }
        if (equal != 0) cout << "Найдено " << equal << " совпадений\n";
        if (equal == 0)  cout << "Совпадений не найдено\n";
        break;
    }
    case 3: // по времени выполненния
    {
        int year=NULL, month=NULL, day=NULL;
        cout << "Введите год (Enter - текущий год)\n";
        cin >> year;
        if (year!=NULL)
        {
            for (int i = 0; i < size; i++)
            {
                if (a[i].date.year == year) Show_deal(a, i);
            }
            break;
        }
        cout << "Введите месяц\n";
        cin >> month;
        if (month != NULL)
        {
            for (int i = 0; i < size; i++)
            {
                if (a[i].date.year==2022&&a[i].date.month == month) Show_deal(a, i);
            }
            break;
        }
        cout << "Введите день(число)\n";
        cin >> day;
        for (int i = 0; i < size; i++)
        {
            //при совпадении года, месяца и дня - показываем дела
            if (a[i].date.day == day && a[i].date.month == month && a[i].date.year == 2022) Show_deal(a, i);
            else cout << "Совпадений не найдено\n";
        }
            break;
    }
    case 4: // по приоритету
    {
        int prior; // временное хранение приоритета
        cout << "Введите приоритет";
        cin >> prior;
        for (int j = 0; j < size; j++) // перебираем все дела
        {
            if (a[j].priority == prior) Show_deal(a, j); // при совпадении приоритета вызваем функцию отображения дела
        }
        break;
    }
    case 0:
        return;
    default:
        return;
    }
}

deal* Edit_deal(deal* Deals_all, int* size) // редактирование дел. Принимает массив дел, размер
{
    int id; // ID дела которое надо отредактировать
    deal new_deal;
    deal* Deals_new = new deal[(*size)]; // создаем массив новой БД такого же размера
    for (int i = 0; i < *size; i++)
    {
        Deals_new[i] = Deals_all[i];
    }
    cout << "Введите ID дела";
    cin >> id;
    Show_deal(Deals_all, id-1); // покажем для наглядности

    cout << "Новая важность дела (1-4) (Enter - оставить без изменений) \n";
    cin >> new_deal.priority;
    if (new_deal.priority != NULL) Deals_new[id - 1].priority = new_deal.priority;
   
    cout << "Новое название дела (Enter - оставить без изменений)\n";
    cin >> new_deal.name;
    if (new_deal.name != NULL) strcpy(Deals_new[id - 1].name, new_deal.name);

    cout << "Новое описание  (Enter - оставить без изменений)\n";
    cin >> new_deal.information;
    if (new_deal.information != NULL) strcpy(Deals_new[id - 1].information, new_deal.information);

    cout << "Новая дата  (Enter - оставить без изменений)\n";
    cout << "Новый день  (Enter - оставить без изменений)\n";
    cin >> new_deal.date.day;
    if (new_deal.date.day != NULL) Deals_new[id - 1].date.day = new_deal.date.day;

    cout << "Новый месяц  (Enter - оставить без изменений)\n";
    cin >> new_deal.date.month;
    if (new_deal.date.month != NULL) Deals_new[id - 1].date.month = new_deal.date.month;

    cout << "Новый год  (Enter - оставить без изменений)\n";
    cin >> new_deal.date.year;
    if (new_deal.date.year != NULL) Deals_new[id - 1].date.year = new_deal.date.year;

    cout << "Новое Время исполнения\n";
    cout << "часы  (Enter - оставить без изменений)\n";
    cin >> new_deal.time.hour;
    if (new_deal.time.hour != NULL) Deals_new[id - 1].time.hour = new_deal.time.hour;
    
    cout << "минуты  (Enter - оставить без изменений)\n";
    cin >> new_deal.time.minutes;
    if (new_deal.time.minutes != NULL) Deals_new[id - 1].time.minutes = new_deal.time.minutes;

    delete[]Deals_all; //очищаем память
    return Deals_new; // возвращаем указатель на измененную БД
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
    (*size)--; // размер уменьшился
    delete[]Deals_all; //очищаем память
    return Deals_new; // возвращаем указатель на очищенную БД
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
            Deals_all = Create_deal(Deals_all, &size);
            break;
        case 2:
            Search_deal(Deals_all, size);
            break;
        case 3:
            Show_deal_all(Deals_all, size);
            break;
        case 4:
            Deals_all = Edit_deal(Deals_all, &size);
            break;
        case 5:
            int choise2;
            cout << "Введите ID дела";
            cin >> choise2;
            Deals_all = Delete_deal(Deals_all, &size, choise2);
            break;
        default:
            break;
        }
    } while (choise != 0);
}