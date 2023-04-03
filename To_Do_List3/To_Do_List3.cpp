// To_Do_List3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include<string>
#include <cstdlib>

using namespace std;
int ID;
//пользовательский тип todo, который содержит два поля id и task
struct todo
{
    int id;
    string task;
};

//этот метод используется для добавления нового дела в список дел
void addtodo()
{
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                        Список дел                                     " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    todo todo;
    cout << "\n\tВведите новое дело: ";
    cin.get();
    getline(cin, todo.task); //получить пользовательский ввод
    ID++; //увеличить идентификатор для текущей задачи

    //теперь запишите эту задачу в todo.txt файл
    ofstream write;
    write.open("todo.txt", ios::app);
    write << "\n" << ID;
    write << "\n" << todo.task;
    write.close();

    //запишите идентификатор в новый файл, чтобы мы могли использовать этот идентификатор позже для добавления нового дела
    write.open("id.txt");
    write << ID;
    write.close();

    char ch;
    cout << "Вы хотите добавить больше дел? y/n" << endl;
    cin >> ch;

    //если пользователь хочет снова добавить новую задачу, то вызовите ту же функцию else return
    if (ch == 'y')
    {
        addtodo();
    }
    else
    {
        cout << "\n\tДело успошно добавлена";
        return;
    }
}

// этот метод используется для вывода дела на экран
void print(todo s)
{
    cout << "\n\tID is : " << s.id;
    cout << "\n\tTask is : " << s.task;
}

//Этот метод используется для считывания данных из todo.txt сохраните и распечатайте его на экране
void readData()
{
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                        Список дел                                     " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    todo todo;
    ifstream read;
    read.open("todo.txt");
    cout << "\n\t------------------Ваш список дел--------------------";
    while (!read.eof())
    {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }
    read.close();
}

//этот метод используется для поиска конкретного дела из todo.txt файл
int searchData()
{
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                        Список дел                                     " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id;
    cout << "\n\tВведите номер дела: ";
    cin >> id;
    todo todo;
    ifstream read;
    read.open("todo.txt");
    while (!read.eof())
    {
        read >> todo.id;
        read.ignore();
        getline(read, todo.task);
        if (todo.id == id)
        {
            print(todo);
            return id;
        }
    }
}

// этот метод используется для удаления дела из todo.txt файл
void deleteData()
{
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                       Список дел                                      " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id = searchData();
    cout << "\n\tВы действительно хотите удалить дело (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y') {
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        //пока мы не дойдем до конца файла, продолжайте искать идентификатор для удаления дела
        while (!read.eof()) {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tДело успешно удалено";
    }
    else {
        cout << "\n\tЗапись не удалена";
    }
}

//этот метод используется для обновления дела
//здесь мы создаем новый temp.txt файл и добавьте все обновленные данные в этот файл
//после обновления мы затем удаляем оригинал todo.txt а затем переименуйте этот файл в todo.txt
void updateData()
{
    system("cls");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t                        Список дел                                     " << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl;
    int id = searchData();
    cout << "\n\tВы действительно хотите выполнить действие (y/n) : ";
    char choice;
    cin >> choice;
    if (choice == 'y')
    {
        todo newData;
        cout << "\n\tВведите содержание дела : ";
        cin.get();
        getline(cin, newData.task);
        todo todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("todo.txt");
        //пока мы не дойдем до конца файла, продолжайте поиск идентификатора и, как только найдем, обновите его новыми данными
        while (!read.eof())
        {
            read >> todo.id;
            read.ignore();
            getline(read, todo.task);
            if (todo.id != id) {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << todo.task;
            }
            else {
                tempFile << "\n" << todo.id;
                tempFile << "\n" << newData.task;
            }
        }
        read.close();
        tempFile.close();
        remove("todo.txt");
        rename("temp.txt", "todo.txt");
        cout << "\n\tДело успешно обновленно";
    }
    else
    {
        cout << "\n\tЗапись не ударена";
    }
}
int main()
{
    setlocale(0, "");
    system("cls");
    system("Color B5"); // "Color B5", B - цвет фона, 5 - цвет текста
    system("title todoapp @copyassignment");
    cout << "\t\t\t***********************************************************************" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t*                      Список дел                                     *" << endl;
    cout << "\t\t\t*                                                                     *" << endl;
    cout << "\t\t\t***********************************************************************" << endl << endl << endl << endl;
    ifstream read;
    read.open("id.txt");
    if (!read.fail())
    {
        read >> ID;
    }
    else
    {
        ID = 0;
    }
    read.close();

    while (true)
    {
        cout << endl << endl;
        cout << "\n\t1.Добавить дело";
        cout << "\n\t2.Просмотр дел";
        cout << "\n\t3.Поиск дела";
        cout << "\n\t4.Удалить дело";
        cout << "\n\t5.Изменить дело";

        int choice;
        cout << "\n\tВыберите действие : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addtodo();
            break;
        case 2:
            readData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            updateData();
            break;
        }
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
