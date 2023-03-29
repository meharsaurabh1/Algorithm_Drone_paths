#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct Drones {
    int t,sx,sy,ex,ey;
    /*constructor of drone which takes intial coortinates, ending cordinates, starting time as parameters */
    Drones(int t, int sx, int sy, int ex, int ey){
        this->t = t;       /* start time */
        this->sx = sx;     /* x of initial coordinates */
        this->sy = sy;     /* y of initial coordinates */
        this->ex = ex;     /* x of ending coordinates */
        this->ey = ey;     /* y of ending coordinates */
    };
};

/* function which saves the path of drone in result */
bool helper(struct Drones* d,int current_x,int current_y,vector<vector<int> > visited,vector<vector<vector<int> >> results,vector<vector<int>  > curr){
    if(current_x == d->ex && current_y == d->ey){
        results.push_back(curr);
        return true;
    }
    
    /* to move in four possible directions initialize kx and ky */
    int kx[]={1,-1,0,0};
    int ky[]={0,0,1,-1};
    visited[current_x][current_y] = 2; 
    /* node which within the matrix and is also unvisited , 
    we are going to append that node in path and call helper function again for new current node 
    until we find the destination coordinates */
    for(int i=0;i<4;i++) {
        int nx=current_x + kx[i];
        int ny=current_y + ky[i];
        if(nx>=0 && nx<visited.size() && ny>=0 && ny<visited.size() && visited[nx][ny]==0){
            curr.push_back({nx,ny});
            visited[nx][ny] = 2;
            bool res=helper(d,nx,ny,visited,results,curr);
            visited[nx][ny] = 1;
            curr.pop_back();
        }
        
    }
    return true;
}

/* comparator function */
bool cmp(struct Drones* a,struct Drones* b)
    {
        // Compare on basis of roll number
        if (a->t < b->t) {
            return true;
        }
        return false;
    }


vector<vector<vector<int>>> solution(int m, int n,vector<Drones*> listDrones){
    vector<vector<int>> visited(m,vector<int> (n,0));
    sort(listDrones.begin(),listDrones.end(),cmp);
    int num_drones=listDrones.size();
    vector<vector<vector<int> >> result(num_drones);
    /* checking path for every drone by itterating through each drone */
    for(int i=0;i<num_drones;i++){
        int sx=listDrones[i]->sx;
        int sy=listDrones[i]->sy;
        int nx=listDrones[i]->ex;
        int ny=listDrones[i]->ey;
        visited[sx][sy]=2;
        vector<vector<int>> curr;
        helper(listDrones[i],sx,sy,visited,result,curr);
    }

    return result;


}

int main(){
    /* make drones */
    Drones *d1 = new Drones(1, 1, 10, 10, 0);
    Drones *d2 = new Drones(2, 2, 15, 15, 2);
    Drones *d3 = new Drones(3, 3, 8, 12, 4);
    vector<Drones*> listDrones;
    /* push drones into listDrones */
    listDrones.push_back(d1);
    listDrones.push_back(d2);
    listDrones.push_back(d3);
    int m=20;
    int n=20;

    vector<vector<vector<int> > > result=solution(m,n,listDrones);
    /* print the paths of all the drones */
    for(int i=0;i<result.size();i++){
        for(int j=0;j<result[i].size();j++){
            cout<<result[i][j][0]<<" "<<result[i][j][1]<<" ,";
        }
        cout<<endl;
    }


}