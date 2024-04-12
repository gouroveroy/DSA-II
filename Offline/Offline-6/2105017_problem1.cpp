#include <bits/stdc++.h>
#include "Priority_queue.cpp"
using namespace std;

/**
 * The function `test` reads commands from a file, performs operations on a priority queue, and outputs
 * results accordingly.
 */
void test()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    Priority_queue<int, int> pq;
    string s;
    int key, value;
    while(cin >> s)
    {
        if(s == "I")
        {
            cin >> key >> value;
            pq.insert(key, value);
        }

        else if(s == "E")
        {
            pair<int, int> eMax = pq.extract_max();
            if(eMax.first == numeric_limits<int>::min())
            {
                cout << "Priority queue is empty" << endl;
                continue;
            }
            cout << eMax.first << " " << eMax.second << endl;
        }

        else if(s == "F")
        {
            pair<int, int> fmax = pq.find_max();
            cout << fmax.first << " " << fmax.second << endl;
        }

        else if(s == "In")
        {
            cin >> value >> key;
            pq.increase_key(value, key);
        }

        else if(s == "D")
        {
            cin >> value;
            pq.Delete(value);
        }

        else if(s == "Em")
        {
            if(pq.is_empty())
            {
                cout << "Empty" << endl;
            }

            else
            {
                cout << "Not empty" << endl;
            }
        }

        else if(s == "S")
        {
            cout << pq.size() << endl;
        }

        else
        {
            pq.print();
        }
    }
    fclose(stdin);
    fclose(stdout);
}

int main()
{
    test();
    return 0;
}
