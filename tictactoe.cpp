#include <iostream>
#include <set>
using namespace std;

set<pair<string,int> > states;
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
    if(game_status(state)=='~')
    {
        string temp;
        if(turn)
        {
            for(int i=0;i<9;i++)
                if(state[i]=='~')
                    {
                        temp=state;
                        temp[i]='x';
                        if(states.find(pair<string,int>(temp,turn))==states.end())
                        {
                            states.insert(pair<string,int>(temp,turn));
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
                        if(states.find(pair<string,int>(temp,turn))==states.end())
                        {
                            states.insert(pair<string,int>(temp,turn));
                            recursive_add_states(temp,!turn);
                        }
                    }
        }
    }
    
}

int main()
{
    string start="~~~~~~~~~";
    recursive_add_states(start,1);
    recursive_add_states(start,0);
    cout<<"Recursion count: "<<rec_count<<endl;
    cout<<"\n\n\n\n post computation states size is: "<<states.size()<<endl;
    for(set<pair<string,int> >::iterator i=states.begin();i!=states.end();++i)
        cout<<(*i).first<<" "<<(*i).second<<"   "<<game_status((*i).first)<<endl;
    return 0;

}