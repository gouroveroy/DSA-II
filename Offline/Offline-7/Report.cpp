#include <bits/stdc++.h>
using namespace std;

class Report
{
    map<long long, map<char, vector<pair<long long, double>>>> report;

public:
    Report(map<long long, map<char, vector<pair<long long, double>>>> &report)
    {
        this->report = report;
    }

    void createReport()
    {
        vector<int> size = {5000, 10000, 20000};
        ofstream file("report.txt");
        if (!file.is_open())
        {
            cerr << "Error opening file: report.txt" << endl;
            return;
        }

        file << " " << setw(69) << setfill('_') << "" << endl;
        file << setfill(' ');
        file << "|            |                   | Hash Function 1 | Hash Function 2 |" << endl;
        file << "|            |                   |___________________________________|" << endl;
        file << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
        file << "|" << setw(69) << setfill('_') << "|" << endl;
        file << setfill(' ');
        char ch;

        // Assuming size, report are properly defined
        for (size_t i = 0; i < size.size(); ++i)
        {
            file << "| N = " << setw(7) << setfill(' ') << size[i];

            for (size_t j = 0; j < 3; ++j)
            {
                if (j == 0)
                {
                    ch = 's';
                    file << "| Separate Chaining | ";
                }

                else if (j == 1)
                {
                    ch = 'd';
                    file << "|            | Double Hashing    | ";
                }

                else
                {
                    ch = 'c';
                    file << "|            | Custom Probing    | ";
                }

                file << setw(7) << setfill(' ') << report[size[i]][ch][0].first << " " << fixed << setprecision(3) << report[size[i]][ch][0].second << " | " << setw(7) << setfill(' ') << report[size[i]][ch][1].first << " " << fixed << setprecision(3) << report[size[i]][ch][1].second << endl;
                // for (size_t k = 0; k < 2; ++k)
                // {
                //     for (size_t m = 0; m < 2; ++m)
                //     {
                //         file << setw(7) << setfill(' ') << 123 << " ";
                //     }
                    // file << "| ";
                // }
                // file << endl;
            }
            file << "|" << setw(69) << setfill('_') << "|" << endl;
        }
        file.close();
    }
};
