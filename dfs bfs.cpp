#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;
#define SIZE 5

int bfs(int graph[SIZE][SIZE],int start,int end)
{
  int visited[SIZE];
  for(int i=0;i<SIZE;i++)
  {
      visited[i]=-1;
  }

  queue<int> q;
  q.push(start);
  visited[start]=1;
  int level=0;
  while(!q.empty())
  {
      level++;
      cout<<endl<<"level:"<<level<<endl;
      #pragma omp paraller for
      for(int f=0;f<q.size();f++)
      {
          int node=q.front();
          
          cout<<node<<",";
          q.pop();
          for(int i=0;i<SIZE;i++)
          {
              #pragma omp critical
              {
                 if(graph[node][i]==1&&visited[i]==-1)
                 {
                     visited[i]=1;
                     q.push(i);
                 }
              }
              
          }
      }
  }
  
  return -1;
  
}

void dfs(int graph[SIZE][SIZE],int node)
{
  int visited[SIZE];
  for(int i=0;i<SIZE;i++)
  {
      visited[i]=-1;
  }
  stack<int> s ;
  s.push(node);
  visited[node]=1;
  while(!s.empty())
  {
      #pragma omp paraller for
      for(int j=0;j<s.size();j++)
      {
         int front=s.top();
         s.pop();
         cout<<front<<" ";
         for(int i=0;i<SIZE;i++)
         {
             #pragma omp critical
             if(graph[front][i]==1&&visited[i]==-1)
            {
                s.push(i);
                
                visited[i]=1;
             }
         } 
      }
    
  }
}

int main()
{
    
    int graph[SIZE][SIZE];
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            graph[i][j]=0;
        }
    }
    graph[0][1]=1;
    graph[1][2]=1;
    graph[1][3]=1;
    graph[3][4]=1;
    graph[2][3]=1;
    
  bfs(graph,0,4);

   
   cout<<endl<<"dfs"<<endl;
    dfs(graph,0);
    
    return 0;
}

