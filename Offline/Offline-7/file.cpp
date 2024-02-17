#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> size = {5000, 10000, 20000};
    ofstream file("report.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file: report.txt" << endl;
        return 1;
    }

    file << " " << setw(69) << setfill('_') << "" << endl;
    file << setfill(' ');
    file << "|            |                   | Hash Function 1 | Hash Function 2 |" << endl;
    file << "|            |                   |___________________________________|" << endl;
    // file << "|         |                                             Hash       | Collision         |                 |                 |" << endl;
    file << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    file << "|" << setw(69) << setfill('_') << "|" << endl;
    file << setfill(' ');

    // Assuming size, report are properly defined
    for (size_t i = 0; i < size.size(); ++i)
    {
        file << "| N = " << setw(7) << setfill(' ') << size[i];

        for (size_t j = 0; j < 3; ++j)
        {
            if (j == 0)
            {
                file << "| Separate Chaining | ";
            }

            else if (j == 1)
            {
                file << "|            | Double Hashing    | ";
            }

            else
            {
                file << "|            | Custom Probing    | ";
            }

            for (size_t k = 0; k < 2; ++k)
            {
                for (size_t m = 0; m < 2; ++m)
                {
                    file << setw(7) << setfill(' ') << 123 << " ";
                }
                file << "| ";
            }
            file << endl;
        }
        file << "|" << setw(69) << setfill('_') << "|" << endl;
    }
    file.close();
    return 0;
}
