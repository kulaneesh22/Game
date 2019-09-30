#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>

using namespace std;

char a[3][3]={{'-','-','-'},{'-','-','-'},{'-','-','-'}};

void input()
{
    int x,y;
    INPUT:
    {
        cout<<"\nEnter position:\n";
        cout<<"Row: ";cin>>x;
        cout<<"Column: ";cin>>y;
    }
    if(((x>3)||(x<1)||(y>3)||(y<0))||(a[x-1][y-1]!='-'))
    {
        cout<<"\nInvalid input.";
        goto INPUT;
    }
    else
        a[x-1][y-1]='X';
}

void display()
{
    system("cls");
    cout<<"\tTIC TAC TOE\n";
    cout<<"\t1\t2\t3\n";
    for(int i=0;i<3;i++)
    {
        cout<<i+1;
        for(int j=0;j<3;j++)
            cout<<'\t'<<a[i][j];
        cout<<endl;
    }
}

void win_lose(int f)
{
    if(f==1)
    {
        cout<<"\nYou win!";
        return;
    }
    else if(f==2)
    {
        cout<<"\nYou lose!";
        return;
    }
    else if(f==3)
    {
        cout<<"\nDraw.";
        return;
    }
}

int check()
{
    if((a[0][0]==a[1][1])&&(a[0][0]==a[2][2]))          //Diagonal 1
    {
        if(a[0][0]=='X')
            return 1;
        else if(a[0][0]=='O')
            return 2;
    }
    else if((a[0][2]==a[1][1])&&(a[0][2]==a[2][0]))     //Diagonal 2
    {
        if(a[0][2]=='X')
            return 1;
        else if(a[0][2]=='O')
            return 2;
    }
    for(int i=0;i<3;i++)
    {
        if((a[i][0]==a[i][1])&&(a[i][0]==a[i][2]))      //Row
        {
            if(a[i][0]=='X')
                return 1;
            else if(a[i][0]=='O')
                return 2;
        }
        if((a[0][i]==a[1][i])&&(a[0][i]==a[2][i]))      //Column
        {
            if(a[0][i]=='X')
                return 1;
            else if(a[0][i]=='O')
                return 2;
        }
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(a[i][j]=='-')
                return 0;
        }
    }
    return 3;
}

void play()
{
    srand(time(NULL));
    //Self
    if((a[0][0]==a[1][1])&&(a[2][2]=='-')&&(a[0][0]=='O'))        //Diagonal 1
    {
        a[2][2]='O';
        return;
    }
    else if((a[1][1]==a[2][2])&&(a[0][0]=='-')&&(a[1][1]=='O'))
    {
        a[0][0]='O';
        return;
    }
    else if((a[2][2]==a[0][0])&&(a[1][1]=='-')&&(a[2][2]=='O'))
    {
        a[1][1]='O';
        return;
    }
    if((a[0][2]==a[1][1])&&(a[2][0]=='-')&&(a[0][2]=='O'))          //Diagonal 2
    {
        a[2][0]='O';
        return;
    }
    else if((a[1][1]==a[2][0])&&(a[0][2]=='-')&&(a[1][1]=='O'))
    {
        a[0][2]='O';
        return;
    }
    else if((a[2][0]==a[0][2])&&(a[1][1]=='-')&&(a[2][0]=='O'))
    {
        a[1][1]='O';
        return;
    }
    for(int i=0;i<3;i++)
    {
        if((a[i][0]==a[i][1])&&(a[i][2]=='-')&&(a[i][0]=='O'))      //Row
        {
            a[i][2]='O';
            return;
        }
        else if((a[i][1]==a[i][2])&&(a[i][0]=='-')&&(a[i][1]=='O'))
        {
            a[i][0]='O';
            return;
        }
        else if((a[i][2]==a[i][0])&&(a[i][1]=='-')&&(a[i][2]=='O'))
        {
            a[i][1]='O';
            return;
        }
        if((a[0][i]==a[1][i])&&(a[2][i]=='-')&&(a[0][i]=='O'))      //Column
        {
            a[2][i]='O';
            return;
        }
        else if((a[1][i]==a[2][i])&&(a[0][i]=='-')&&(a[1][i]=='O'))
        {
            a[0][i]='O';
            return;
        }
        else if((a[2][i]==a[0][i])&&(a[1][i]=='-')&&(a[2][i]=='O'))
        {
            a[1][i]='O';
            return;
        }
    }
    //Opponent
    if((a[0][0]==a[1][1])&&(a[2][2]=='-')&&(a[0][0]=='X'))        //Diagonal 1
    {
        a[2][2]='O';
        return;
    }
    else if((a[1][1]==a[2][2])&&(a[0][0]=='-')&&(a[1][1]=='X'))
    {
        a[0][0]='O';
        return;
    }
    else if((a[2][2]==a[0][0])&&(a[1][1]=='-')&&(a[2][2]=='X'))
    {
        a[1][1]='O';
        return;
    }
    if((a[0][2]==a[1][1])&&(a[2][0]=='-')&&(a[0][2]=='X'))          //Diagonal 2
    {
        a[2][0]='O';
        return;
    }
    else if((a[1][1]==a[2][0])&&(a[0][2]=='-')&&(a[1][1]=='X'))
    {
        a[0][2]='O';
        return;
    }
    else if((a[2][0]==a[0][2])&&(a[1][1]=='-')&&(a[2][0]=='X'))
    {
        a[1][1]='O';
        return;
    }
    for(int i=0;i<3;i++)
    {
        if((a[i][0]==a[i][1])&&(a[i][2]=='-')&&(a[i][0]=='X'))      //Row
        {
            a[i][2]='O';
            return;
        }
        else if((a[i][1]==a[i][2])&&(a[i][0]=='-')&&(a[i][01]=='X'))
        {
            a[i][0]='O';
            return;
        }
        else if((a[i][2]==a[i][0])&&(a[i][1]=='-')&&(a[i][2]=='X'))
        {
            a[i][1]='O';
            return;
        }
        if((a[0][i]==a[1][i])&&(a[2][i]=='-')&&(a[0][i]=='X'))      //Column
        {
            a[2][i]='O';
            return;
        }
        else if((a[1][i]==a[2][i])&&(a[0][i]=='-')&&(a[1][i]=='X'))
        {
            a[0][i]='O';
            return;
        }
        else if((a[2][i]==a[0][i])&&(a[1][i]=='-')&&(a[2][i]=='X'))
        {
            a[1][i]='O';
            return;
        }
    }
    int x,y;
    VALUE:
    {
        x=rand()%3;
        y=rand()%3;
    }
    if(a[x][y]!='-')
        goto VALUE;
    else
        a[x][y]='O';
}

int main()
{
    int f=0;
    for(;;)
    {
        display();
        input();
        display();
        f=check();
        win_lose(f);
        if(f!=0)
            break;
        play();
        display();
        f=check();
        win_lose(f);
        if(f!=0)
            break;
    }
    return 0;
}

