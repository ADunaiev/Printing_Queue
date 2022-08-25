#include <iostream>
#include <string.h>
#include <time.h>

//������� 3.
//����������� ����������, ����������� ������� ������
//��������.������ ���� �������, ���������� �������
//�� �������, � ������� �� ������� ���� ���� ���������.
//������ ����� ������ �������� � ������� � �����������
//�� ������ ����������.���������� ��������� ���������� ������(������������, �����) 
//� ��������� �������.
//������������� ����� ���������� �� �����.

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
    void Set_Name(std::string nampeP);
    void Set_Surname(std::string surnameP);
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
    std::cout << name << " " << surname << " priority " << priority;
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
void Customer::Set_Name(std::string nameP)
{
    name = nameP;
}
void Customer::Set_Surname(std::string surnameP)
{
    surname = surnameP;
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
    return *this;
}

class QueuePriority
{
    //�������
    Print_Request* Wait;
    //������������ ������ �������
    int MaxQueueLength;
    //������� ������ �������
    int QueueLength;
public:
    //�����������
    QueuePriority(int m);
    //����������
    ~QueuePriority();
    //���������� ��������
    void Add(Print_Request c, int p);
    //���������� ��������
    Print_Request Extract();
    //������� �������
    void Clear();
    //�������� ������������� ��������� � �������
    bool IsEmpty();
    //�������� �� ������������ �������
    bool IsFull();
    //���������� ��������� � �������
    int GetCount();
    //������������ �������
    void Show();
};

void QueuePriority::Show() {
    std::cout << "\n-----------------------------------\n"; //������������ �������
    for (int i = 0; i < QueueLength; i++)
    {
        Wait[i].show();
    }
    std::cout << "\n-----------------------------------\n";
 }
QueuePriority::~QueuePriority()
{
    //�������� �������
    delete[]Wait;
}
QueuePriority::QueuePriority(int m)
{
    //�������� ������
    MaxQueueLength = m;
    //������� �������
    Wait = new Print_Request[MaxQueueLength];
    //���������� ������� �����
    QueueLength = 0;
}
void QueuePriority::Clear()
{
    //����������� "�������" �������
    QueueLength = 0;
}
bool QueuePriority::IsEmpty()
{
    //����?
    return QueueLength == 0;
}
bool QueuePriority::IsFull()
{
    //�����?
    return QueueLength == MaxQueueLength;
}
int QueuePriority::GetCount()
{
    //���������� �������������� � ����� ���������
    return QueueLength;
}
void QueuePriority::Add(Print_Request c, int p)
{
    //���� � ������� ���� ��������� �����,
    //�� ����������� ����������
    //�������� � ��������� ����� �������
    if (!IsFull()) {
        Wait[QueueLength] = c;
        Wait[QueueLength].Get_Customer().Set_Priority(p);
        QueueLength++;
    }
}
Print_Request QueuePriority::Extract()
{
    //���� � ������� ���� ��������, �� ���������� ���, //� �������� ��������� ��������� � �������� ������� 
    if(!IsEmpty()){
        //����� ������������ ������� - �������
        int max_pri = Wait[0].Get_Customer().Get_priority();
        //� ������������ ������ = 0
        int pos_max_pri = 0;
        //���� ���������
         for (int i = 1; i < QueueLength; i++)    
        //���� �������� ����� ������������ ������� 
            if(max_pri < Wait[i].Get_Customer().Get_priority()) {
                max_pri = Wait[i].Get_Customer().Get_priority();
                pos_max_pri = i;
            }
        //����������� ������������ �������
        Print_Request temp1 = Wait[pos_max_pri];
        int temp2 = Wait[pos_max_pri].Get_Customer().Get_priority();
        //�������� ��� ��������
        for (int i = pos_max_pri; i < QueueLength - 1; i++) {
            Wait[i] = Wait[i + 1];
            Wait[i].Get_Customer().Set_Priority(Wait[i + 1].Get_Customer().Get_priority());
        }
        //��������� ����������
        QueueLength--;
        //������� ������������ ��������
        return temp1;
    }
    else return Print_Request();
}

void main()
{
    srand(time(NULL));
    Customer Group[]{ {"Ivan", "Ivanov", 5},
            { "Vasilii", "Petrov", 1 },
            { "John", "Smith", 2 },
            { "Maria", "Ivanovna", 3 },
            { "Fedor", "Arbuzov", 2 } };

    QueuePriority Waiting(100);
    QueuePriority Printed(100);

    Print_Request PR[20];

    for (int i = 0; i < 20; i++)
    {
        int temp = rand() % 5;
        PR[i] = Print_Request(Group[temp], i);
        Waiting.Add(PR[i], PR[i].Get_Customer().Get_priority());
    }

    std::cout << "Queue of printing requests:";
    Waiting.Show();

    for (int i = 20; i < 30; i++)
    {
        Print_Request temp = Waiting.Extract();
        Printed.Add(temp, temp.Get_Customer().Get_priority());
    }

    std::cout << "Queue of printing requests:";
    Waiting.Show();

    std::cout << "Statistic of rinted requests:";
    Printed.Show();

}