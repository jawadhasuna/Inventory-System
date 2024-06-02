#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<cstdlib>
#include<iomanip>
using namespace std;
struct employee {
    string name;
    int id, age;
    employee(int ID, string NAME, int AGE)
    {
        id = ID;
        age = AGE;
        name = NAME;
    }
    void display()
    {
        cout << left << setw(10) << id << setw(10) << name << setw(10) << right << age << endl;
    }
};
 int main()
{
    ifstream file("employee.csv", ios::in);
    vector<employee>emp;
    if (!file)
    {
        cout << "file not created";
        exit(1);
    }
    string line = "";
    while (getline(file, line))
    {
        int id;
        int age;
        string name;
        string temp = "";
        stringstream str(line);
        getline(str, temp, ',');
        id = atoi(temp.c_str());
        getline(str, name, ',');
        getline(str, temp, ',');
        age = atoi(temp.c_str());
        employee e(id, name, age);
        emp.push_back(e);
    }
    cout << left << setw(10) << "id" << setw(10) << "name" << setw(10) << right << "age" << endl;
    for (auto e : emp)
    {
        e.display();
    }
    file.close();
    return 0;
}