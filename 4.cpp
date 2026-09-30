#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <chrono>
#include <windows.h>
using namespace std;
vector<int> arr;
bool running = true;
mutex mtx;
void task1()
{
    random_device rd;
    mt19937 gen(rd());

    // Sinh số từ 1 đến 50000
    uniform_int_distribution<int> dist(1, 50000);

    while (true)
    {
        // Sinh số
        int x = dist(gen);

        {
            lock_guard<mutex> lock(mtx);

            arr.push_back(x);

            cout << "Task1 sinh: " << x << endl;
        }
        if (x > 10000 && x % 2021 == 0)
        {
            lock_guard<mutex> lock(mtx);

            running = false;

            cout << "\nTask1 dung!" << endl;
            cout << "So thoa man: " << x << endl;

            break;
        }

        // Chu kỳ khoảng 1ms
        this_thread::sleep_for(
            chrono::milliseconds(1)
        );
    }
}

void task2()
{
    int lastMax = -1;
    int lastSecond = -1;

    while (true)
    {
        int max1 = -1;
        int max2 = -1;

        {
            lock_guard<mutex> lock(mtx);

            // Nếu chưa có dữ liệu
            if (arr.empty())
            {
                if (!running)
                {
                    break;
                }
            }
            else
            {
                for (int x : arr)
                {
                    if (x > max1)
                    {
                        max1 = x;
                    }
                }
                for (int x : arr)
                {
                    if (x < max1 && x > max2)
                    {
                        max2 = x;
                    }
                }
                if (max1 != lastMax ||
                    max2 != lastSecond)
                {
                    cout << endl;
                    cout << "============================"
                         << endl;

                    cout << "Task2" << endl;

                    cout << "So lon nhat: "
                         << max1 << endl;

                    if (max2 != -1)
                    {
                        cout << "So lon nhi: "
                             << max2 << endl;
                    }
                    else
                    {
                        cout << "So lon nhi: Chua co"
                             << endl;
                    }

                    cout << "============================"
                         << endl;

                    // Phat beep
                    Beep(800, 50);

                    lastMax = max1;
                    lastSecond = max2;
                }
            }
            if (!running)
            {
                break;
            }
        }

        // Task2 kiểm tra lại sau 10ms
        this_thread::sleep_for(
            chrono::milliseconds(10)
        );
    }

    cout << "\nTask2 dung!" << endl;
}
int main()
{
    cout << "============================" << endl;
    cout << "          BAI 04" << endl;
    cout << "============================" << endl;
    thread t1(task1);
    thread t2(task2);
    t1.join();
    t2.join();
    cout << endl;
    cout << "Chuong trinh ket thuc." << endl;
    return 0;
}