#include <bits/stdc++.h>
using namespace std;
#define MAX 13

int node,edge;
vector<int>graph[MAX];
int source, destination,constraint,direction_idea;
int parent[MAX];
map<int,pair<int,int>>position_constraint;
vector<pair<int,int>>move_direction[MAX];

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

bool bit_check(int value, int bit_num){
    int result = value & (1<<(bit_num));
    if(result>0) return true;
    return false;
}

int set_bit(int value, int bit_num){
    return (value | (1<<bit_num));
}

bool check(int destination,vector<pair<int,int>>saved_moves){
    vector<int>idx;
    while(destination != -1){
        //cout<<destination<<endl;
        idx.push_back(destination);
        destination = parent[destination];
    }
    int ct=0;
    for(int i=0;i<idx.size();i++){
        if(idx[i] == 0){
            if(saved_moves[i].first==0 && saved_moves[i].second == 0) ct++;
        }
        if(idx[i] == 7){
             if(saved_moves[i].first==0 && saved_moves[i].second == 3) continue;
             else return false;
        }
        if(idx[i] == 8){
             if(saved_moves[i].first==3 && saved_moves[i].second == 3) continue;
             else return false;
        }
        if(idx[i] == 12){
             if(saved_moves[i].first==1 && saved_moves[i].second == 0) ct++;
        }
    }
    if(saved_moves[saved_moves.size()-2].first != 2 || saved_moves[saved_moves.size()-2].second != 0){
        return false;
    }
    return true;
}

void print(int destination){
    vector<int>idx;
    while(destination != -1){
        cout<<destination<<endl;
        idx.push_back(destination);
        destination = parent[destination];
    }
    return;
}


bool ans=false;
int guni=0;
int visited[3][3];
void backtrack(int state, int destination, int prev, int x, int y,vector<pair<int,int>>saved_moves){
    //cerr<<state<<endl;
    guni++;
    if(guni%1000 == 0) {
        cerr<<guni<<" "<<state<<endl;
    }
    if(bit_check(state,destination) == true){
        cerr<<"YES = "<<state<<" "<<x<<" "<<y<<endl;
        ans = check(destination,saved_moves);
        /*for(int i=0;i<saved_moves.size();i++){
            cerr<<saved_moves[i].first<<" "<<saved_moves[i].second<<endl;
        }*/
        if(ans==true){
            print(destination);
        }
        return;
    }
    int v;
    int x1,y1;
    for(int i=0;i<graph[prev].size();i++){
        v=graph[prev][i];
        if(bit_check(state,v) == false){
            for(int j=0;j<move_direction[prev].size();j++){
                if(move_direction[prev][j].first == v){
                    x1 = x+ dx[move_direction[prev][j].second];
                    y1 = y + dy[move_direction[prev][j].second];
                    if(((abs(x1-x)+abs(y1-y))== 1) && x1>=0 && x1<=3 && y1>=0 && y1<=3 && visited[x1][y1] == 0){
                        parent[v]=prev;
                        visited[x1][y1]=1;
                        if(x==0 && y==0 && v == 9) {
                            cerr<<"x1,y1 "<<x1<<" "<<y1<<endl;
                        }
                        saved_moves.push_back({x1,y1});
                        backtrack(set_bit(state,v),destination,v,x1,y1,saved_moves);
                        parent[v]=-1;
                        visited[x1][y1]=0;
                        saved_moves.pop_back();
                        if(ans==true) break;
                    }
                }
            }
        }
        if(ans==true) break;
    }
    return;
}

void solution(int source, int destination){
    visited[0][0]=1;
    vector<pair<int,int>>saved_moves;
    saved_moves.push_back({0,0});
    backtrack(1,destination,source,0,0,saved_moves);
}

void input(){
    cin>>node>>edge>>constraint>>direction_idea;
    int a,b,c;
    int ct=1;
    for(int i=0;i<edge;i++){
        cin>>a>>b;
        graph[a].push_back(b);
        ct++;
    }
    cin>>source>>destination;
    cerr<<source<<destination<<endl;
    ct++;
    for(int i=0;i<constraint;i++){
        cin>>a>>b>>c;
        position_constraint[a]={b,c};
        ct++;
    }
    cerr<<source<<" "<<destination<<endl;
    for(int i=0;i<direction_idea;i++){
        cin>>a>>b>>c;
        move_direction[a].push_back({b,c});
        ct++;
    }
    cerr<<"count = "<<ct<<endl;

}

void init(){
    memset(parent,-1,sizeof(parent));
    memset(visited,0,sizeof(visited));
}

int main(void){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    input();
    init();
    solution(source,destination);
}
