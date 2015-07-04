#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "binomial_heap.h"
using namespace std;

typedef pair<int, int> priority_id;
BinomialHeap< priority_id > bh [1100000]; //10^6

bool cmp(priority_id& a, priority_id& b)
{
    return a.second < b.second;
}
int main()
{
    unsigned int c = 1, w;

    scanf("%u%u", &c, &w);
    string command;
    while( cin >> command )
    {
        if(command == "assign")
        {
            int cm = -1, id = -1, p = -1;
            scanf("%d%d%d", &cm, &id, &p);
            priority_id tmp = make_pair(p, id);
            bh[cm].insert(tmp);
            printf("There are %d tasks on computer %d.\n",bh[cm].getSize() ,cm);
        }
        else if(command == "execute")
        {
            int cm = -1;
            scanf("%d", &cm);
            vector <priority_id> vec;
            priority_id tmp = bh[cm].getMax();
            while(bh[cm].getMax().first == tmp.first && bh[cm].getSize() > 1)
            {
                vec.push_back(bh[cm].pop());
            }
            if(bh[cm].getSize() == 1 && bh[cm].getMax().first == tmp.first )
                vec.push_back(bh[cm].pop());

            sort(vec.begin(), vec.end(), cmp);
            for(int i = 0; i < vec.size(); i++)
            {
                printf("Computer %d executed task %d.\n", cm, vec[i].second);
            }
        }
        else if(command == "merge")
        {
            int cm1 = -1, cm2 = -1;
            scanf("%d%d", &cm1, &cm2);
            if(bh[cm2].getSize() < w)
                printf("Merging request failed.\n");
            else
            {
                bh[cm1].merge(bh[cm2]);
                printf("The largest priority number is now %d on %d.\n", bh[cm1].getMax().first, cm1);
            }
        }
        else
        {
            printf("ERROR\n");
            return false;
        }
    }
    return 0;
}
