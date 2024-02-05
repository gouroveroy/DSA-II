#include <bits/stdc++.h>
#include "Priority_queue.cpp"
using namespace std;

void test(Priority_queue<int, int>& pq)
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
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
            pair<int, int> emax = pq.extract_max();
            if(emax.first == numeric_limits<int>::min())
            {
                cout << "Priority queue is empty" << endl;
                continue;
            }
            cout << emax.first << " " << emax.second << endl;
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
    Priority_queue<int, int> pq, pq1;
    // for (int i = 0, j = 0; i < 100 && j < 100; i++, j++)
    // {
    //     pq.insert(i, j);
    // }

    // // for (int i = 1, j = 1; i < 10 && j < 10; i++, j++)
    // // {
    // //     pq1.insert(i * 10, j * 10);
    // // }

    // pq.extract_max();
    // pq.extract_max();
    // // pq1.extract_max();

    // // Priority_queue<int, int> mergedPQ = pq.meld(pq1);
    // // pq = pq.meld(pq1);
    // // pq.print();
    // // pq.extract_max();
    // pq.print();
    test(pq);
    return 0;
}
