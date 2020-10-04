//header files
#include <iostream>
#include <set>
#include <vector>
#include <map>

using namespace std;

set<string> states; // all possible states along with the turn appended.
//vector<string> valid_states;
//vector<vector<int> > move;
set<pair<string,string> > edges; //store all possible edges
map<string,int> m;
vector<vector<int> > graph; 
int rec_count=0;

// printing of state
void print_state(string s) 
{

/*
Example of printout of the matrix: 
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

// evaluation of state if Won by X or 0 or gameplay pending, i.e ~ or draw
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

void initialize_graph()
{
    int n=m.size();
    vector<int> x;
    //graph.insert(graph.end(),n+1,x);
    for(int i=0;i<=n;i++)
        graph.push_back(x);
    cout<<"graph vector has been initialized with outer size: "<<graph.size()<<endl;
}

//printing every edge by new format. 0 if anywhere is an error
void print_edges_mapped()
{
    initialize_graph();
    int count=0;
    cout<<"\nnumber of edges are: "<<edges.size()<<"\n0 is an error.\nedges in a mapped manner: "<<endl;
    cout<<"\n printing has been suspended temporarily\n";
    for(set<pair<string,string> >::iterator i=edges.begin();i!=edges.end();i++)
        {
            //cout<<m.find((*i).first)->second<<"   ->   "<<m.find((*i).second)->second<<endl;
            graph[m.find((*i).first)->second].push_back(m.find((*i).second)->second);
            if(m.find((*i).first)==m.end())//||m.find((*i).second)==m.end())
                cout<<"there is an error 1"<<endl;
            if(m.find((*i).second)==m.end())//||m.find((*i).second)==m.end())
                cout<<"there is an error 2"<<endl;
            
            count++;
        }
    cout<<count<<" traversals of edges have occured"<<endl;
}

// mapping every outcome state to a number
void map_initialize_with_outcomes()
{
    m.insert(pair<string,int>("x",1));
    m.insert(pair<string,int>("0",2));
    m.insert(pair<string,int>("d",3));
    cout<<"map initiliazed with outcomes"<<endl;
    // we assume 0 will be an error so we don't explicitly assign it to anything
}

// map each state in States to a specific integer value starting from 4
void map_states()
{
    int j=4;
    for(set<string>::iterator i=states.begin();i!=states.end();++i,j++)
        {
            //cout<<(*i).substr(0,9)<<" "<<(*i)[9]<<"    "<<game_status(*i)<<endl;
            //valid_states.push_back(*i);
            m.insert(pair<string,int>(*i,j));
        }
    
    cout<<"the map size after mapping of states with id is: "<<m.size()<<endl;

    print_edges_mapped();
    
}

// recursive traversal of all states
void recursive_add_states(string state)
{
    //cout<<"\n we are at state: \n";
    //print_state(state);
    rec_count++; // to keep a track of number of recursive calls made
    char c=game_status(state); // only first 9 characters are cared about

    states.insert(state);
    if(c=='~') //if turns are left
    {
        string temp;
        if(state[11]=='x') // x's turn
        {
            for(int i=0;i<9;i++)
                if(state[i]=='~')
                    {
                        temp=state;
                        temp[i]='x';
                        temp[11]='0'; // opposite turn
                        if(states.find(temp)==states.end()) // this state with turn hasn't been encountered before
                        {
                            //states.insert(temp);
                            recursive_add_states(temp);
                            edges.insert(pair<string,string>(state,temp));
                        }
                    }
        }
        else // 0's turn
        {
            for(int i=0;i<9;i++)
                if(state[i]=='~')
                    {
                        temp=state;
                        temp[i]='0';
                        temp[11]='x'; // opposite turn
                        if(states.find(temp)==states.end()) // this state with turn hasn't been encountered before
                        {
                            //states.insert(temp);
                            recursive_add_states(temp);
                            edges.insert(pair<string,string>(state,temp));
                        }
                    }
        }
    }
    else // no more turns left
        {
            string oc="0";
            oc[0]=c; // winner or loser or draw
            edges.insert(pair<string,string>(state,oc));
        }
    
}

// build all the nodes and complete relevant simplifying
void build_nodes()
{
    map_initialize_with_outcomes();

    string start="~~~~~~~~~";
    recursive_add_states(start+"|x"); // x starts first
    recursive_add_states(start+"|0"); // 0 starts first

    cout<<"Recursion count: "<<rec_count<<endl;
    cout<<"\n\n\n\n post computation states set size is: "<<states.size()<<endl;
    cout<<" edges size is: "<<edges.size()<<endl;

    map_states();
    cout<<"nodes have been built"<<endl;
}

// return the corresponding node index details from a string
int node_index(string state)
{
    return m.find(state)->second;
}

void check_graph_size()
{
    int total=0;
    for(int i=0;i<graph.size();i++)
        total+=graph[i].size();
    cout<<"the total size(number of edges) of the graph is: "<<total<<endl;
}

void build_graph()
{
    
    build_nodes();
    
    check_graph_size();
}


int main()
{
    
    build_graph();
    
    return 0;
    
    int j=4;
    
    //m.insert(pair<string,int>("~",3));

    for(set<pair<string,string> >::iterator it=edges.begin();it!=edges.end();it++)
        {
            cout<<(*it).first.substr(0,9)<<"|"<<(*it).first[9]<<"    ->     "<<(*it).second.substr(0,9)<<"|"<<(*it).second[9]<<endl;
            cout<<m.find((*it).first)->second<<"    ->     "<<m.find((*it).second)->second<<endl;
        }
    //cout<<"\n valid states size is: "<<valid_states.size()<<endl;
    
    
    
    return 0;

}