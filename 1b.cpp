#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

void task2()
{
    while (true)
    {
        ifstream file("dulieu.dat");

        if (file.is_open())
        {
            unsigned int so;

            if (file >> so)
            {
                file.close();

                cout << "CT2 doc: " << so << endl;

                if (so % 2021 == 0)
                {
                    cout << "CT2: Gap so chia het cho 2021!" << endl;
                    break;
                }
            }
            else
            {
                file.close();
            }
        }

        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

int main()
{
    thread t2(task2);

    t2.join();

    return 0;
}