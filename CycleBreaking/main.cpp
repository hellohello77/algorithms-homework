#include<stdio.h>
#include<iostream>
#include<fstream>
using namespace std;
int const Minkey=-200;
struct EDGE
{
    int start;
    int end_;
    int weight;
};
struct vertex
{
    int key;
    int pi;
    int v;
};
bool DFS(int **dedge,int *color,int start,int vnum)
{
    bool cycle=0;
    color[start]=2;
    for(int i=0;i<vnum;i++)
    {
        if(dedge[start][i]==3 && color[i]==1)
        {
            cycle=DFS(dedge,color,i,vnum);
            if(cycle)
            {
                break;
            }
        }
        else if(dedge[start][i]==3 && color[i]==2)
        {
            cycle=1;
            break;
        }
    }
    color[start]=3;
    return cycle;
}
int Partition(EDGE posedge[],int *sorting,int str,int ed)
{
    int x=posedge[sorting[ed]].weight;
    int i=str-1;
    int tmp;
    for(int j=str;j<ed;j++)
    {
        if(posedge[sorting[j]].weight>=x)
        {
            i++;
            tmp=sorting[i];
            sorting[i]=sorting[j];
            sorting[j]=tmp;
        }
    }
    tmp=sorting[i+1];
    sorting[i+1]=sorting[ed];
    sorting[ed]=tmp;
    return i+1;
}
void QuickSort(EDGE posedge[],int *sorting,int str,int ed)
{
    if(str<ed)
    {
        int mid=Partition(posedge,sorting,str,ed);
        QuickSort(posedge,sorting,str,mid-1);
        QuickSort(posedge,sorting,mid+1,ed);
    }
}
int main(int argc,char *argv[])
{
        //////////// read the input file /////////////
    fstream fin;
    fstream fout;
    fin.open(argv[1],ios::in);
    fout.open(argv[2],ios::out);
    char categ='\0';
    int vnum=0,ednum=0;
    fin>>categ;
    fin>>vnum>>ednum;
    int totalweight=0;
    vertex vertex_[vnum];
    for(int i=0;i<vnum;i++)
    {
        vertex_[i].key=Minkey;
        vertex_[i].pi=-1;
        vertex_[i].v=i;
    }
    int eds,ede,edw;
    int edge[vnum][vnum]={};
    int **dedge;
    dedge=new int*[vnum];
    for(int i=0;i<vnum;i++)
    {
        dedge[i]=new int [vnum];
    }
    int edgeweight[vnum][vnum];
    for(int i=0;i<vnum;i++)
    {
        for(int j=0;j<vnum;j++)
        {
            edgeweight[i][j]=200;
        }
    }
    for(int i=0;i<ednum;i++)
    {
        fin>>eds>>ede>>edw;
        edge[eds][ede]=1;
        dedge[eds][ede]=1;
        edgeweight[eds][ede]=edw;
        edge[ede][eds]=1;
        edgeweight[ede][eds]=edw;
        totalweight+=edw;
    }
    /////MST/////
    int y=totalweight;
    int maxi=0;
    vertex_[0].key=0;
    int u;
    for(int i=0;i<vnum;i++)
    {
        u=maxi;
        for(int j=0;j<vnum;j++)
        {
            if(edge[u][j])
            {
                if(vertex_[j].key<edgeweight[u][j] && vertex_[j].key>=Minkey)
                {
                    vertex_[j].pi=u;
                    vertex_[j].key=edgeweight[u][j];
                }
            }
        }
        vertex_[u].key=-201;
        maxi=0;
        for(int j=0;j<vnum;j++)
        {
            if(vertex_[j].key>=vertex_[maxi].key)
            {
                maxi=j;
            }
        }
        if(i!=vnum-1)
        {
            edge[maxi][vertex_[maxi].pi]=3;
            edge[vertex_[maxi].pi][maxi]=3;
            if(dedge[maxi][vertex_[maxi].pi])
            {
                dedge[maxi][vertex_[maxi].pi]=3;
            }
            else
            {
                dedge[vertex_[maxi].pi][maxi]=3;
            }
            y-=edgeweight[maxi][vertex_[maxi].pi];
        }
    }
    if(categ=='u')
    {
        fout<<y<<endl;
        for(int i=0;i<vnum;i++)
        {
            for(int j=0;j<i;j++)
            {
                if(edge[i][j]==1)
                {
                    fout<<i<<" "<<j<<" "<<edgeweight[i][j]<<endl;
                }
            }
        }
    }
    else if(categ=='d')
    {
        EDGE posedge[ednum];
        int possible=0;
        for(int i=0;i<vnum;i++)
        {
            for(int j=0;j<vnum;j++)
            {
                if(dedge[i][j]==1 && edgeweight[i][j]>0)
                {
                    posedge[possible].start=i;
                    posedge[possible].end_=j;
                    posedge[possible].weight=edgeweight[i][j];
                    possible++;
                }
            }
        }
        int sorting[possible];
        for(int i=0;i<possible;i++)
        {
            sorting[i]=i;
        }
        QuickSort(posedge,sorting,0,possible-1);
        int color[vnum];
        for(int i=0;i<vnum;i++)
        {
            color[i]=1;
        }
        for(int i=0;i<possible;i++)
        {
            dedge[posedge[sorting[i]].start][posedge[sorting[i]].end_]=3;
            if(DFS(dedge,color,posedge[sorting[i]].start,vnum))
            {
                dedge[posedge[sorting[i]].start][posedge[sorting[i]].end_]=1;
            }
            else
            {
                y-=posedge[sorting[i]].weight;
            }
            for(int j=0;j<vnum;j++)
            {
            color[j]=1;
            }
        }
        fout<<y<<endl;
        for(int i=0;i<vnum;i++)
        {
            for(int j=0;j<vnum;j++)
            {
                if(dedge[i][j]==1)
                {
                    fout<<i<<" "<<j<<" "<<edgeweight[i][j]<<endl;
                }
            }
        }
    }
}
