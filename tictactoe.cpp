#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;

set<string> states;
vector<string> valid_states;
vector<vector<int> > move;
set<pair<string,string> > edges;
map<string,int> m;
int rec_count=0;

void print_state(string s)
{

/*
    |   |
  x | x | x
-------------
    |   |
  x | 0 | x
-------------
    |   |
  x | ~ | 0
*/
   
cout<<"    |   |"<<endl;
cout<<"  "<<s[0]<<" | "<<s[1]<<" | "<<s[2]<<endl;
cout<<"-------------"<<endl;
cout<<"    |   |"<<endl;
cout<<"  "<<s[3]<<" | "<<s[4]<<" | "<<s[5]<<endl;
cout<<"-------------"<<endl;
cout<<"    |   |"<<endl;
cout<<"  "<<s[6]<<" | "<<s[7]<<" | "<<s[8]<<endl;
}

char game_status(string s)
{
    for(int i=0;i<=6;i+=3) // row wise
        if(s[i]==s[i+1]&&s[i+1]==s[i+2])
            return s[i];
    for(int j=0;j<3;j++) // column wise
        if(s[j]==s[j+3]&&s[j+3]==s[j+6])
            return s[j];
    if((s[0]==s[4]&&s[4]==s[8])||(s[2]==s[4]&&s[4]==s[6])) // diagonal wise
        return s[4];
    for(int i=0;i<9;i++) // any move left
        if(s[i]=='~')
            return '~';
    return 'd'; //  game is a draw
}

void recursive_add_states(string state,bool turn)
{
    //cout<<"\n we are at state: \n";
    //print_state(state);
    rec_count++;
    char c=game_status(state);
    if(c=='~')
    {
        string temp;
        if(turn)
        {
            for(int i=0;i<9;i++)
                if(state[i]=='~')
                    {
                        temp=state;
                        temp[i]='x';
                        temp+="1";
                        if(states.find(temp)==states.end())
                        {
                            states.insert(temp);
                            edges.insert(pair<string,string>(state,temp));
                            recursive_add_states(temp,!turn);
                        }
                    }
        }
        else
        {
            for(int i=0;i<9;i++)
                if(state[i]=='~')
                    {
                        temp=state;
                        temp[i]='0';
                        temp+="0";
                        if(states.find(temp)==states.end())
                        {
                            states.insert(temp);
                            edges.insert(pair<string,string>(state,temp));
                            recursive_add_states(temp,!turn);
                        }
                    }
        }
    }
    else
        {
            string oc="0";
            oc[0]=c;
            edges.insert(pair<string,string>(state,oc));
        }
    
}

int main()
{
    string start="~~~~~~~~~";
    
    m.insert(pair<string,int>("x",1));
    m.insert(pair<string,int>("0",2));
    m.insert(pair<string,int>("d",3));
    
    recursive_add_states(start,1);
    recursive_add_states(start,0);
    cout<<"Recursion count: "<<rec_count<<endl;
    cout<<"\n\n\n\n post computation states set size is: "<<states.size()<<endl;
    cout<<" edges size is: "<<edges.size()<<endl;
    int j=4;
    
    //m.insert(pair<string,int>("~",3));
    
    for(set<string>::iterator i=states.begin();i!=states.end();++i,j++)
        {
            //cout<<(*i).substr(0,9)<<" "<<(*i)[9]<<"    "<<game_status(*i)<<endl;
            //valid_states.push_back(*i);
            m.insert(pair<string,int>(*i,j));
        }
    for(set<pair<string,string> >::iterator it=edges.begin();it!=edges.end();it++)
        {
            cout<<(*it).first.substr(0,9)<<"|"<<(*it).first[9]<<"    ->     "<<(*it).second.substr(0,9)<<"|"<<(*it).second[9]<<endl;
            cout<<m.find((*it).first)->second<<"    ->     "<<m.find((*it).second)->second<<endl;
        }
    cout<<"\n valid states size is: "<<valid_states.size()<<endl;
    return 0;

}