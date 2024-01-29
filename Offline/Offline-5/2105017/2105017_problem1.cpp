#include <bits/stdc++.h>
#include "Map.cpp"
using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    Map<int, string> map;
    string line, value;
    int key;

    while (cin >> line)
    {
        if (line == "I")
        {
            cin >> key >> value;
            pair<int, string> p = {key, value};
            map.Insert(p);
            map.print();
        }

        else if (line == "E")
        {
            cin >> key;
            if (!map.Find(key))
            {
                cout << key << " not found" << endl;
            }

            else
            {
                map.Erase(key);
                map.print();
            }
        }

        else if (line == "Clr")
        {
            if (map.Clear())
            {
                cout << "successful" << endl;
            }

            else
            {
                cout << "unsuccessful" << endl;
            }
        }

        else if (line == "F")
        {
            cin >> key;
            if (map.Find(key))
            {
                cout << key << " found" << endl;
            }

            else
            {
                cout << key << " not found" << endl;
            }
        }

        else if (line == "Em")
        {
            if (map.Empty())
            {
                cout << "yes" << endl;
            }

            else
            {
                cout << "no" << endl;
            }
        }

        else if (line == "S")
        {
            cout << map.Size() << endl;
        }

        else if (line == "Itr")
        {
            map.Iteration();
        }
    }

    fclose(stdin);
    // fclose(stdout);
    return 0;
}
