#include <iostream>
#include <fstream>
using namespace std;
void opt_line(int CH[],int C_TO_C[],bool* r,int sp,int tp,int help[])
{
    help[sp]=0;
    for(int cnp=sp+1;cnp<tp;cnp++)
    {
        if(CH[cnp]<cnp && CH[cnp]>sp)
        {
            if(help[CH[cnp]]+C_TO_C[cnp]>help[cnp-1])
            {
                help[cnp]=help[CH[cnp]]+C_TO_C[cnp];
            }
            else
            {
                help[cnp]=help[cnp-1];
            }
        }
        else
        {
            help[cnp]=help[cnp-1];
        }
    }
    int k=tp-1;
    while(k>sp)
    {
        if(help[k]>help[k-1])
        {
            r[CH[k]]=1;
            opt_line(CH,C_TO_C,r,CH[k],k,help);
            k=CH[k]-1;
        }
        else
        {
            k--;
        }
    }
    return;
}
int main (int argc,char* argv[])
{
    //////////// read the input file /////////////
    fstream fin;
    fstream fout;
    fin.open(argv[1],ios::in);
    fout.open(argv[2],ios::out);
    int num,i,j,ans;
    fin>>num;
    int CH[num]={},S_TO_N[num]={},C_TO_C[num]={},help[num]={};
    bool r[num]={};
    for(int k=0;k<num/2;k++)
    {
        fin>>i>>j;
        CH[i]=j;
        CH[j]=i;
    }
    //////////// the sorting part ////////////////
    for(int np=1;np<num;np++)
    {
        if(CH[np]<np)
        {
            help[CH[np]]=0;
            for(int cnp=CH[np]+1;cnp<np;cnp++)
            {
                if(CH[cnp]<cnp && CH[cnp]>CH[np])
                {
                    if(help[CH[cnp]]+C_TO_C[cnp]>help[cnp-1])
                    {
                        help[cnp]=help[CH[cnp]]+C_TO_C[cnp];
                    }
                    else
                    {
                        help[cnp]=help[cnp-1];
                    }
                }
                else
                {
                    help[cnp]=help[cnp-1];
                }
            }
            C_TO_C[np]=help[np-1]+1;
            C_TO_C[CH[np]]=help[np-1]+1;
        }
    }
    for(int fp=1;fp<num;fp++)
    {
        if(CH[fp]<fp)
        {
            if(C_TO_C[fp]+S_TO_N[CH[fp]]>S_TO_N[fp-1])
            {
                S_TO_N[fp]=C_TO_C[fp]+S_TO_N[CH[fp]];
            }
            else
            {
                S_TO_N[fp]=S_TO_N[fp-1];
            }
        }
        else
        {
            S_TO_N[fp]=S_TO_N[fp-1];
        }
    }
    int k=num-1;
    while(k>0)
    {
        if(S_TO_N[k]>S_TO_N[k-1])
        {
            r[CH[k]]=1;
            opt_line(CH,C_TO_C,r,CH[k],k,help);
            k=CH[k]-1;
        }
        else
        {
            k--;
        }
    }
    //////////// write the output file ///////////
    fout << S_TO_N[num-1] << endl;
    for(int z=0;z<num;z++)
    {
        if(r[z])
            fout<<z<<" "<<CH[z]<<endl;
    }
    fin.close();
    fout.close();
    return 0;
}
