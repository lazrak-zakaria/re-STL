#include <stdio.h>
#include <iostream>
#include <deque>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <utility>

using namespace std;

int main(void)
{

  int n;
  cin >> n;

  while (n--)
  {

    map<int, int> mp;
    vector<pair<int, int>> v;

    int m;
    cin >> m;

    while (true)
    {
      int r, c;
      cin >> r >> c;

      if (!r && !c)
        break;
      mp[r] = c;
    }

    int s = 0;
    bool f = false;
    for (auto &p : mp)
    {
        int rr = p.first;
        int cc = p.second;

        if (s < rr)
        {
          f = true;
          break;
        }
        

        bool push = false;
        if (s >= rr && s <= cc)
          push = true;
        if (!v.empty())
        {
          auto& pr = v.back();
          if (pr.first == rr)
          {
            pr.second = max(pr.second, rr);
            push = false;
          }
        }
        if (push)
          v.push_back({rr, cc});
        
        s = cc + 1;
        if (m <= cc)
          break;
    }
    
    if (f)
      cout << 0 << "\n";
    else
    {
      cout << v.size() << "\n";
      for (auto &p : mp)
      {
        cout << p.first << " " << p.second << "\n";
      }
    }

    if (n)
      cout << "\n";
  }
}