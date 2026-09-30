#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

string st = "";
bool running = true;

mutex mtx;

// Xóa dấu cách đầu và cuối chuỗi
string trim(string s)
{
    int start = 0;
    int end = s.length() - 1;

    while (start <= end && s[start] == ' ')
        start++;

    while (end >= start && s[end] == ' ')
        end--;

    if (start > end)
        return "";

    return s.substr(start, end - start + 1);
}

// Task1
void task1()
{
    while (running)
    {
        string temp;

        cout << "Nhap chuoi: ";
        getline(cin, temp);

        temp = trim(temp);

        {
            lock_guard<mutex> lock(mtx);
            st = temp;
        }

        if (temp == "bye")
        {
            running = false;
            break;
        }
    }
}

// Task2
void task2()
{
    string last = "";

    while (running)
    {
        {
            lock_guard<mutex> lock(mtx);

            if (st != "" && st != last)
            {
                cout << "Task2 hien thi: " << st << endl;
                last = st;
            }

            if (st == "bye")
            {
                break;
            }
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    thread t1(task1);
    thread t2(task2);

    t1.join();
    t2.join();

    cout << "Chuong trinh ket thuc." << endl;

    return 0;
}