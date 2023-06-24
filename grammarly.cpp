#include<bits/stdc++.h>
#include<fstream>
using namespace std;

vector<string> readCSV(string filename, int i)
{
    vector<string> data;
    // cout<<filename<<" ";
    ifstream file(filename);

    if (!file.is_open()) 
    {
        cout<<"file "<<i<<" couldn't be opened"<<endl;
        return data;
    }
    string line;
    while(getline(file, line))
    {
        if (data.size()>0 && data.back()!=line) data.push_back(line);
    }
    file.close();
    return data;
}

int thresh1 = 1; //for letters of len 3 or less.
int thresh2 = 2; //for letters of len b/w 4-7.
int thresh3 = 3; // for letters of len >7

int dist(string txt, string pat, int n, int m, vector<vector<int>> &dp)
{
    for(int i=0; i<=n; i++) dp[i][0]=i;
    for(int j=0; j<=m; j++) dp[0][j]=j;

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if (txt[i-1]==pat[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i][j-1],dp[i-1][j], dp[i-1][j-1]});
        }
    }
return dp[n][m];
}

string edit(string word, vector<vector<string>>data, int len)
{
    // cout<<word<<" ";
    string res=word;
    int thresh;
    if (len<=3) thresh = 1;
    if (len<=7 && len>=4) thresh = 2;
    if (len>7) thresh = 3;
    for(int i=0; i<26; i++)
    {
        for(auto txt: data[i])
        {
            if (txt=="mellow") cout<<"-------";
            int n = txt.size();
            int m = word.size();
            vector<vector<int>> dp(n+1, vector<int> (m+1,0));
            int distance = dist(txt, word, n, m, dp);
            int mind = m;
            if (distance<=thresh && distance<mind)
            {
                res = txt;
                mind = distance;
                // cout<<txt<<" ";
            }
            if (distance==0) return word;
        }
    }
    cout<<res;
    return res;
}

int main()
{
    vector <string> filename;
    unordered_set<char> punc;
    punc.insert('.');punc.insert(',');punc.insert('?');punc.insert('!');
    for(char ch ='A'; ch<='Z'; ch++)
    {
        string s;
        s=ch;
        s += "word.csv";
        filename.push_back(s);
        // cout<<s;
    }

    vector<vector<string>>data(26); //data is dictionary
    for(int i=0; i<26; i++)
    {
        data[i] = readCSV(filename[i], i); 
        // cout<<data[i].size()<<" ";
        // cout<<filename[i]<<" ";
    }
    // for(auto x: data[0]) cout<<x<<endl;

    cout<<"input your paragraph here: "<<endl;
    vector<vector<string>> para;
    string line;
    while(getline(cin, line) && !line.empty())
    {
        vector<string> v;
        string s="";
        for(auto x: line)
        {
            if (x==32)
            {
                v.push_back(s);
                s="";
            }
            s=s+x;
        }
        v.push_back(s);
        para.push_back(v);
    }

    // for(auto x: para)
    // {
    //     for(auto words: x)
    //     {
    //         int l = words.size();
    //         // cout<<1<<" ";
    //         edit(words, data, l);
    //     }
    //     cout<<endl;
    // }
    edit("mellou", data, 6);
}