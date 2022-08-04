#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include <chrono>
using namespace std;
map<string, string> symbolTable;
void loadfile()
{
    string line;
    ifstream file("test.txt");
    while (getline(file, line))
    {
        symbolTable.insert(pair<string, string>(to_string(rand()), line));
    }
    file.close();
}
void savefile()
{
    ofstream test("test.txt");
    test << "hej" << endl;
    test.close();
}
void ccc()
{
    cout << "hi" << endl;
}
void fx(int a){
    this_thread::sleep_for(10s);
    cout << "ok" <<endl;
}
int main()
{
    srand(time(0));
    loadfile();
    symbolTable["hi"] =  "hello";
    symbolTable["hsi"] = "hellsso";
    map<string, string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); it++)
    {
        cout << it->first // string (klucz)
             << ':'
             << it->second // string wartość
             << endl;
    }
    string am = "pycha";
    string *ptr;
    ptr = &am;
    cout << *ptr << endl;
    map<int, int> m;
    m[2] = 4;
    cout << m[2] << endl;
    return 0;
}