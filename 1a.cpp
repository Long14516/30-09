#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

void task1()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned int> dist(0, 4294967295u);

    while (true)
    {
        unsigned int so = dist(gen);

        // Nếu chia hết cho 2021 thì dừng
        if (so % 2021 == 0)
        {
            ofstream file("dulieu.dat", ios::out);

            if (file.is_open())
            {
                file << so;
                file.close();
            }

            cout << "CT1: Gap so chia het cho 2021: " << so << endl;
            break;
        }

        // Ghi đè file
        ofstream file("dulieu.dat", ios::out);

        if (file.is_open())
        {
            file << so;
            file.close();

            cout << "CT1 ghi: " << so << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main()
{
    thread t1(task1);

    t1.join();

    return 0;
}