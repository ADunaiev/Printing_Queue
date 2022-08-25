#include <iostream>
#include <string.h>
#include <time.h>

//Задание 3.
//Разработать приложение, имитирующее очередь печати
//принтера.Должны быть клиенты, посылающие запросы
//на принтер, у каждого из которых есть свой приоритет.
//Каждый новый клиент попадает в очередь в зависимости
//от своего приоритета.Необходимо сохранять статистику печати(пользователь, время) 
//в отдельной очереди.
//Предусмотреть вывод статистики на экран.

class Customer
{
    std::string name;
    std::string surname;
    int priority;
public:
    Customer(std::string nameP, std::string surnameP, int priorityP);
    Customer();
    std::string Get_Name() const;
    std::string Get_Surname() const;
    int Get_priority() const;
    void show() const;
    Customer& operator=(const Customer& object);
    void Set_Priority(int c);
};

Customer::Customer(std::string nameP, std::string surnameP, int priorityP) :
 name{ nameP }, surname{ surnameP }, priority{ priorityP } {}
Customer::Customer() : Customer("", "", 0){}
std::string Customer::Get_Name() const
{
    return name;
}
std::string Customer::Get_Surname() const
{
    return surname;
}
int Customer::Get_priority() const
{
    return priority;
}
void Customer::show() const
{
    std::cout << name << " " << surname << " priority " << priority << std::endl;
}
Customer& Customer::operator=(const Customer& object)
{
    if (!(this == &object))
    {
        name = object.name;
        surname = object.surname;
        priority = object.priority;
    }
    return *this;
}
void Customer::Set_Priority(int c)
{
    priority = c;
}

class Print_Request
{
    int time;
    Customer customer;
public:
    Print_Request(Customer customerP, int timeP);
    Print_Request();
    int Get_time() const;
    Customer Get_Customer() const;
    void show() const;
    Print_Request& operator=(const Print_Request& object);
};
Print_Request::Print_Request(Customer customerP, int timeP) :
    time{ timeP }
{
    customer = Customer(customerP.Get_Name(), customerP.Get_Surname(),
        customerP.Get_priority());
}
Print_Request::Print_Request() : Print_Request(Customer(), 0){}
int Print_Request::Get_time() const
{
    return time;
}
Customer Print_Request::Get_Customer() const
{
    return customer;
}
void Print_Request::show() const
{
    std::cout << "Print Reuqest sent by ";
    customer.show();
    std::cout << " at " << time << std::endl;       
}
Print_Request& Print_Request::operator=(const Print_Request& object)
{
    time = object.time;
    customer = object.customer;
}

class QueuePriority
{
    //Очередь
    Print_Request* Wait;
    //Максимальный размер очереди
    int MaxQueueLength;
    //Текущий размер очереди
    int QueueLength;
public:
    //Конструктор
    QueuePriority(int m);
    //Деструктор
    ~QueuePriority();
    //Добавление элемента
    void Add(Print_Request c, int p);
    //Извлечение элемента
    Print_Request Extract();
    //Очистка очереди
    void Clear();
    //Проверка существования элементов в очереди
    bool IsEmpty();
    //Проверка на переполнение очереди
    bool IsFull();
    //Количество элементов в очереди
    int GetCount();
    //демонстрация очереди
    void Show();
};

void QueuePriority::Show() {
    std::cout << "\n-----------------------------------\n"; //демонстрация очереди
    for (int i = 0; i < QueueLength; i++)
    {
        Wait[i].show();
        std::cout << "\n";
    }
    std::cout << "\n-----------------------------------\n";
 }
QueuePriority::~QueuePriority()
{
    //удаление очереди
    delete[]Wait;
}
QueuePriority::QueuePriority(int m)
{
    //получаем размер
    MaxQueueLength = m;
    //создаем очередь
    Wait = new Print_Request[MaxQueueLength];
    //Изначально очередь пуста
    QueueLength = 0;
}
void QueuePriority::Clear()
{
    //Эффективная "очистка" очереди
    QueueLength = 0;
}
bool QueuePriority::IsEmpty()
{
    //Пуст?
    return QueueLength == 0;
}
bool QueuePriority::IsFull()
{
    //Полон?
    return QueueLength == MaxQueueLength;
}
int QueuePriority::GetCount()
{
    //Количество присутствующих в стеке элементов
    return QueueLength;
}
void QueuePriority::Add(Print_Request c, int p)
{
    //Если в очереди есть свободное место,
    //то увеличиваем количество
    //значений и вставляем новый элемент
    if (!IsFull()) {
        Wait[QueueLength] = c;
        Wait[QueueLength].Get_Customer().Set_Priority(p);
        QueueLength++;
    }
}
Print_Request QueuePriority::Extract()
{
    //Если в очереди есть элементы, то возвращаем тот, //у которого наивысший приоритет и сдвигаем очередь 
    if(!IsEmpty()){
        //пусть приоритетный элемент - нулевой
        int max_pri = Wait[0].Get_Customer().Get_priority();
        //а приоритетный индекс = 0
        int pos_max_pri = 0;
        //ищем приоритет
         for (int i = 1; i < QueueLength; i++)    
        //если встречен более приоритетный элемент 
            if(max_pri < Wait[i].Get_Customer().Get_priority()) {
                max_pri = Wait[i].Get_Customer().Get_priority();
                pos_max_pri = i;
            }
        //вытаскиваем приоритетный элемент
        Print_Request temp1 = Wait[pos_max_pri];
        int temp2 = Wait[pos_max_pri].Get_Customer().Get_priority();
        //сдвинуть все элементы
        for (int i = pos_max_pri; i < QueueLength - 1; i++) {
            Wait[i] = Wait[i + 1];
            Wait[i].Get_Customer().Set_Priority(Wait[i + 1].Get_Customer().Get_priority());
        }
        //уменьшаем количество
        QueueLength--;
        //возврат извлеченного элемента
        return temp1;
    }
    else return Print_Request();
}

void main()
{
    srand(time(0));
    //создание очереди
    QueuePriority QUP(25);
    //заполнение части элементов
    for (int i = 0; i < 5; i++) {
        //значения от 0 до 99 (включительно)
        //и приоритет от 0 до 11 (включительно)
        QUP.Add(rand() % 100, rand() % 12);
    }

    //показ очереди
    QUP.Show();
    //извлечение элемента
    QUP.Extract();
    //показ очереди
    QUP.Show();
}