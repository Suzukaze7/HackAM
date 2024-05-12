#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
#define lowbit(x) ((x)&(-(x)))
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define maxheap(x) priority_queue<x,vector<x>,less<x> > 
#define minheap(x) priority_queue<x,vector<x>,greater<x> > 
#define endl '\n'
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef long long ll;
typedef unsigned long long ull;
//#define mod 1000000009
//#define mod 1000000007
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
vector<int> find_occurrences(string text, string pattern) {
  string cur = pattern + '#' + text;
  int sz1 = text.size(), sz2 = pattern.size();
  vector<int> v;
  vector<int> lps = prefix_function(cur);
  for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
    if (lps[i] == sz2) v.push_back(i - 2 * sz2);
  }
  return v;
}
string s[200005];
string t[200005];
bool yes[200005];
int cnt[200005];
set<int> st;
int main()
{
    int n,m;
    IOS;
    cin>>n>>m;
    int i;
    for(i=1;i<=n;i++) cin>>s[i];
    for(i=1;i<=m;i++) cin>>t[i];
    for(i=1;i<=n;i++) st.insert(i);
    auto now=st.begin();
    for(i=1;i<=m;i++)
    {   
        vector<int> tmp=find_occurrences(s[*now],t[i]);
        if(tmp.empty())
        {
            cnt[*now]++;
            continue;
        }
        else
        {
            if(cnt[*now]==0)
            {
                yes[*now]=1;
                int temp=*now;
                now=next(now);
                if(now==st.end()) now=st.begin();
                st.erase(temp);
            }
            else
            {
                cnt[*now]=0;
                int temp=*now;
                now=next(now);
                if(now==st.end()) now=st.begin();
              //  st.erase(temp);
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        if(yes[i]) cout<<s[i]<<endl;
    }
    return 0;
}