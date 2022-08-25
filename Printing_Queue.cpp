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
        std::cout << "\n";
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
    srand(time(0));
    //�������� �������
    QueuePriority QUP(25);
    //���������� ����� ���������
    for (int i = 0; i < 5; i++) {
        //�������� �� 0 �� 99 (������������)
        //� ��������� �� 0 �� 11 (������������)
        QUP.Add(rand() % 100, rand() % 12);
    }

    //����� �������
    QUP.Show();
    //���������� ��������
    QUP.Extract();
    //����� �������
    QUP.Show();
}