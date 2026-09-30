#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <windows.h>

using namespace std;

char c = '\0';
bool running = true;

mutex mtx;

// Timer1
void timer1()
{
    while (running)
    {
        char temp;

        cout << "\nNhap ky tu: ";
        cin >> temp;

        {
            lock_guard<mutex> lock(mtx);
            c = temp;
        }

        // Hiển thị HEX
        cout << "Ky tu: " << temp;
        cout << " - HEX: 0x"
             << hex
             << setw(2)
             << setfill('0')
             << (int)(unsigned char)temp
             << dec
             << endl;

        if (temp == '*')
        {
            running = false;
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

// Timer2
void timer2()
{
    while (running)
    {
        char current;

        {
            lock_guard<mutex> lock(mtx);
            current = c;
        }

        if (current == '*')
        {
            break;
        }

        Beep(1000, 100);

        this_thread::sleep_for(chrono::milliseconds(7));
    }
}

int main()
{
    thread t1(timer1);
    thread t2(timer2);

    t1.join();
    t2.join();

    cout << "\nChuong trinh ket thuc." << endl;

    return 0;
}