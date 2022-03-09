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

--доработать поиск
--заменить функции на безопасные, с обработкой ввода
--сохраняться в файл и считываться из него
--статусы завершения операций и красота
*/

#include <iostream>
#include <cstdlib>
using namespace std;

char weeks[7][12]{ "Понедельник", "Вторник", "Среда", "Четверг","Пятница", "Суббота", "Воскресенье" };
// в глобальной области видимости нам понадобяться длни недели. Массив с названиями

struct Date // встроенная структура даты в структуре дела
{
    int day;
    int month;
    int year=2022;
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

char Week_auto(char weeks, deal a) //функция автоматического определения дня недели в пределах года
{
    char week[12]; //здесь определим название дня недели
    int week_int=0; // порядковый день недели
    int temp_day=0; // порядковый номер дня в 2022 году
    const int days_in_month_2022[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // кол-во дней в месяцах по порядку
    for (int i = 0; i < (a.date.month); i++) // считаем дни в прошедших месяцах
    {
        temp_day += days_in_month_2022[i];
    }
    temp_day += a.date.day; // добавляем прошедние дни в месяце
    while (temp_day>7) // определяем день недели, если бы 1.01 был бы понедельником (цифра 1)
    {
        temp_day -= 7;
    }
    if (temp_day < 3)temp_day += 5;  // сдвигаем на 5 вправо, либо на 1 влево, так как 1.01.2022 было субботой
    else temp_day += 1;
    strcpy(week, weeks[temp_day-1]);
    return *week; 
}

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
        cout << "Введите часы\n";
        break;
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

deal* Edit_deal(deal* Deals_all, int* size, int id) // редактирование дел. Принимает массив дел, размер и ID дела
{
    deal* Deals_new = new deal[(*size)];

    delete[]Deals_all; //очищаем память
    return Deals_new; // возвращаем указатель на очищенную БД
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