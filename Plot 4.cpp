#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<strings.h>
#include<fstream>

using namespace std;

struct player
{
    int score;
    char name[10];
};

player pl[11];
char p[6][7];
char in[45];
int s,diff;

void new_game();
void high_scores();
void difficulty();
void rules();
void save();
void savedata();

void initialize()
{
    fstream f;
    int i;
    s=0;
    diff=1;
    f.open("high_scores.dat",ios::in|ios::binary);
    for(i=0;i<11;i++)
    {
        pl[i].score=0;
        strcpy(pl[i].name,"EMPTY");
    }
    i=0;
    while(f.read((char*)&pl[i],sizeof(pl[i])))
    {
        i++;
    }
    f.close();
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
            p[i][j]='-';
    }
    for(int i=0;i<45;i++)
    {
        if((i%6)==2)
            in[i]='|';
        else
            in[i]=' ';
    }
}

void d1()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\n1.New game <-";
    cout<<"\n2.High scores";
    cout<<"\n3.Difficulty";
    cout<<"\n4.Rules";
    cout<<"\n\nPress esc to exit.";
}

void d2()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\n1.New game";
    cout<<"\n2.High scores <-";
    cout<<"\n3.Difficulty";
    cout<<"\n4.Rules";
    cout<<"\n\nPress esc to exit.";
}

void d3()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\n1.New game";
    cout<<"\n2.High scores";
    cout<<"\n3.Difficulty <-";
    cout<<"\n4.Rules";
    cout<<"\n\nPress esc to exit.";
}

void d4()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\n1.New game";
    cout<<"\n2.High scores";
    cout<<"\n3.Difficulty";
    cout<<"\n4.Rules <-";
    cout<<"\n\nPress esc to exit.";
}

void menu()
{
    int k1,k2,k=1;
    d1();
    for(;;)
    {
        k1=_getch();
        if(k1==224)
        {
            k2=_getch();
            if(k2==80)
            {
                if(k==1)
                {
                    d2();
                    k=2;
                }
                else if(k==2)
                {
                    d3();
                    k=3;
                }
                else if(k==3)
                {
                    d4();
                    k=4;
                }
                else if(k==4)
                {
                    d1();
                    k=1;
                }
            }
            else if(k2==72)
            {
                if(k==1)
                {
                    d4();
                    k=4;
                }
                else if(k==2)
                {
                    d1();
                    k=1;
                }
                else if(k==3)
                {
                    d2();
                    k=2;
                }
                else if(k==4)
                {
                    d3();
                    k=3;
                }
            }
        }
        else if(k1==13)
        {
            if(k==1)
                new_game();
            else if(k==2)
                high_scores();
            else if(k==3)
                difficulty();
            else if(k==4)
                rules();
        }
        else if(k1==27)
        {
            cout<<endl;
            system("pause");
            exit(0);
        }
    }
}

void display()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<endl;
    for(int i=0;i<45;i++)
        cout<<in[i];
    cout<<"\n  -------------------------------------------\n"<<endl;
    for(int i=0;i<6;i++)
    {
        cout<<"  |  ";
        for(int j=0;j<7;j++)
            cout<<p[i][j]<<"  |  ";
        cout<<endl;
    }
    cout<<endl;
    if(diff==1)
        cout<<"Difficulty: Hard";
    else if(diff==2)
        cout<<"Difficulty: Easy";
}

void thinking()
{
    long long int y;
    srand(time(NULL));
    y=rand()%3;
    display();
    cout<<"\nThinking...";
    cout<<endl;
    y+=3;
    usleep(y*100000);
}

void fall(int i,int j,char c)
{
    if(c=='O')
        thinking();
    if(i==0)
        return;
    else
    {
        for(int a=0;a<i;a++)
        {
            p[a][j]=c;
            display();
            cout<<endl;
            usleep(70000);
            p[a][j]='-';
        }
    }
}

void input()
{
    int k1,k2,b,x,y;
    x=-1;
    b=5;
    y=0;
    for(;;)
    {
        in[b]='X';
        display();
        k1=_getch();
        if(k1==13)
        {
            for(int i=5;i>-1;i--)
            {
                if(p[i][y]=='-')
                {
                    x=i;
                    break;
                }
            }
            if(x==-1)
            {
                cout<<"\nInvalid.";
                continue;
            }
            else
            {
                y=((b+1)/6)-1;
                in[b]=' ';
                fall(x,y,'X');
                p[x][y]='X';
                return;
            }
        }
        if(k1==224)
        {
            k2=_getch();
            if(k2==75)
            {
                in[b]=' ';
                b-=6;
                y--;
                if(b<5)
                {
                    b=5;
                    y=0;
                }
                in[b]='X';
                display();
            }
            if(k2==77)
            {
                in[b]=' ';
                b+=6;
                y++;
                if(b>41)
                {
                    b=41;
                    y=6;
                }
                in[b]='X';
                display();
            }
        }
        if(k1==119)
            s=1;
        if(k1==108)
            s=2;
        if(k1==100)
            s=3;
    }
}

void input1()
{
    int x,y;
    Position:
    {
        cout<<"\nEnter position: ";cin>>y;
        y--;
        for(int i=5;i>-1;i--)
        {
            if(p[i][y]=='-')
            {
                x=i;
                break;
            }
        }
    }
    if((y<0)||(y>6))
        {
            cout<<"\nInvalid input.";
            goto Position;
        }
    fall(x,y,'X');
    p[x][y]='X';
    return;
}

void win_lose()
{
    if(s==1)
        cout<<"\nYou win!";
    else if(s==2)
        cout<<"\nYou lose!";
    else if(s==3)
        cout<<"\nIt's a draw!";
    if(s!=0)
        save();
}

bool anticipate_oppo(int i,int j)
{
    bool t=true;
    if((p[i-1][j-1]==p[i-1][j-2])&&(p[i-1][j-1]==p[i-1][j-3])&&(j-3>-1)&&(p[i-1][j-1]=='X'))        //Left end
    {
        t=false;
        return t;
    }
    if((p[i-1][j+1]==p[i-1][j+2])&&(p[i-1][j+1]==p[i-1][j+3])&&(j+3<7)&&(p[i-1][j+1]=='X'))         //Right end
    {
        t=false;
        return t;
    }
    if((p[i-1][j-1]==p[i-1][j+1])&&(p[i-1][j-1]==p[i-1][j+2])&&(j+2<7)&&(j-1>-1)&&(p[i-1][j-1]=='X'))   //Horizontal 1
    {
        t=false;
        return t;
    }
    if((p[i-1][j-2]==p[i-1][j-1])&&(p[i-1][j-2]==p[i-1][j+1])&&(j+1<7)&&(j-1>-1)&&(p[i-1][j-2]=='X'))   //Horizontal 2
    {
        t=false;
        return t;
    }
    if((p[i-2][j-1]==p[i-3][j-2])&&(p[i-2][j-1]==p[i-4][j-3])&&(i-4>-1)&&(j-3>-1)&&(p[i-2][j-1]=='X'))  //Up Left
    {
        t=false;
        return t;
    }
    if((p[i-2][j+1]==p[i-3][j+2])&&(p[i-2][j+1]==p[i-4][j+3])&&(i-4>-1)&&(j+3<7)&&(p[i-2][j+1]=='X'))   //Up Right
    {
        t=false;
        return t;
    }
    if((p[i][j+1]==p[i+1][j+2])&&(p[i][j+1]==p[i+2][j+3])&&(i+2<6)&&(j+3<7)&&(p[i][j+1]=='X'))          //Down Right
    {
        t=false;
        return t;
    }
    if((p[i][j-1]==p[i+1][j-2])&&(p[i][j-1]==p[i+2][j-3])&&(i+2<6)&&(j-3>-1)&&(p[i][j-1]=='X'))         //Down Left
    {
        t=false;
        return t;
    }
    if((p[i-2][j-1]==p[i][j+1])&&(p[i-2][j-1]==p[i+1][j+2])&&(i-2>-1)&&(i+1<6)&&(j-1>-1)&&(j+2<7)&&(p[i-2][j-1]=='X'))     //Diagonal A 1
    {
        t=false;
        return t;
    }
    if((p[i-3][j-2]==p[i-2][j-1])&&(p[i-3][j-2]==p[i][j+1])&&(i-3>-1)&&(i<6)&&(j-2>-1)&&(j+1<7)&&(p[i-3][j-2]=='X'))        //Diagonal A 2
    {
        t=false;
        return t;
    }
    if((p[i][j-1]==p[i-2][j+1])&&(p[i][j-1]==p[i-3][j+2])&&(i-3>-1)&&(i<6)&&(j-1>-1)&&(j+2<7)&&(p[i][j-1]=='X'))            //Diagonal B 1
    {
        t=false;
        return t;
    }
    if((p[i+1][j-2]==p[i][j-1])&&(p[i+1][j-2]==p[i-2][j+1])&&(i-2>-1)&&(i+1<6)&&(j-2>-1)&&(j+1<7)&&(p[i+1][j-2]=='X'))      //Diagonal B 2
    {
        t=false;
        return t;
    }
    return t;
}

bool anticipate_self(int i,int j)
{
    bool t=false;
    if((p[i-1][j-1]==p[i-1][j-2])&&(p[i-1][j-1]==p[i-1][j-3])&&(j-3>-1)&&(p[i-1][j-1]=='O'))        //Left end
    {
        t=true;
        return t;
    }
    if((p[i-1][j+1]==p[i-1][j+2])&&(p[i-1][j+1]==p[i-1][j+3])&&(j+3<7)&&(p[i-1][j+1]=='O'))         //Right end
    {
        t=true;
        return t;
    }
    if((p[i-1][j-1]==p[i-1][j+1])&&(p[i-1][j-1]==p[i-1][j+2])&&(j+2<7)&&(j-1>-1)&&(p[i-1][j-1]=='O'))   //Horizontal 1
    {
        t=true;
        return t;
    }
    if((p[i-1][j-2]==p[i-1][j-1])&&(p[i-1][j-2]==p[i-1][j+1])&&(j+1<7)&&(j-1>-1)&&(p[i-1][j-2]=='O'))   //Horizontal 2
    {
        t=true;
        return t;
    }
    if((p[i-2][j-1]==p[i-3][j-2])&&(p[i-2][j-1]==p[i-4][j-3])&&(i-4>-1)&&(j-3>-1)&&(p[i-2][j-1]=='O'))  //Up Left
    {
        t=true;
        return t;
    }
    if((p[i-2][j+1]==p[i-3][j+2])&&(p[i-2][j+1]==p[i-4][j+3])&&(i-4>-1)&&(j+3<7)&&(p[i-2][j+1]=='O'))   //Up Right
    {
        t=true;
        return t;
    }
    if((p[i][j+1]==p[i+1][j+2])&&(p[i][j+1]==p[i+2][j+3])&&(i+2<6)&&(j+3<7)&&(p[i][j+1]=='O'))          //Down Right
    {
        t=true;
        return t;
    }
    if((p[i][j-1]==p[i+1][j-2])&&(p[i][j-1]==p[i+2][j-3])&&(i+2<6)&&(j-3>-1)&&(p[i][j-1]=='O'))         //Down Left
    {
        t=true;
        return t;
    }
    if((p[i-2][j-1]==p[i][j+1])&&(p[i-2][j-1]==p[i+1][j+2])&&(i-2>-1)&&(i+1<6)&&(j-1>-1)&&(j+2<7)&&(p[i-2][j-1]=='O'))     //Diagonal A 1
    {
        t=true;
        return t;
    }
    if((p[i-3][j-2]==p[i-2][j-1])&&(p[i-3][j-2]==p[i][j+1])&&(i-3>-1)&&(i<6)&&(j-2>-1)&&(j+1<7)&&(p[i-3][j-2]=='O'))        //Diagonal A 2
    {
        t=true;
        return t;
    }
    if((p[i][j-1]==p[i-2][j+1])&&(p[i][j-1]==p[i-3][j+2])&&(i-3>-1)&&(i<6)&&(j-1>-1)&&(j+2<7)&&(p[i][j-1]=='O'))            //Diagonal B 1
    {
        t=true;
        return t;
    }
    if((p[i+1][j-2]==p[i][j-1])&&(p[i+1][j-2]==p[i-2][j+1])&&(i-2>-1)&&(i+1<6)&&(j-2>-1)&&(j+1<7)&&(p[i+1][j-2]=='O'))      //Diagonal B 2
    {
        t=true;
        return t;
    }
    return t;
}

void check()
{
    int v=0;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(((p[i][j]==p[i+1][j])&&(p[i][j]==p[i+2][j])&&(p[i][j]==p[i+3][j]))&&(i+3<6))  //Rows
            {
                if(p[i][j]=='X')
                    {s=1;break;}
                if(p[i][j]=='O')
                    {s=2;break;}
            }
            if(((p[i][j]==p[i][j+1])&&(p[i][j]==p[i][j+2])&&(p[i][j]==p[i][j+3]))&&(j+3<7))    //Columns
            {
                if(p[i][j]=='X')
                    {s=1;break;}
                if(p[i][j]=='O')
                    {s=2;break;}
            }
            if(((p[i][j]==p[i+1][j+1])&&(p[i][j]==p[i+2][j+2])&&(p[i][j]==p[i+3][j+3]))&&((i+3)<6)&&((j+3)<7))   //Diagonal 1
            {
                if(p[i][j]=='X')
                    {s=1;break;}
                if(p[i][j]=='O')
                    {s=2;break;}
            }
            if(((p[i][j]==p[i-1][j+1])&&(p[i][j]==p[i-2][j+2])&&(p[i][j]==p[i-3][j+3]))&&((i-3>-1)&&(j+3<7)))   //Diagonal 2
            {
                if(p[i][j]=='X')
                    {s=1;break;}
                if(p[i][j]=='O')
                    {s=2;break;}
            }
            if(p[i][j]=='-')
                v++;
        }
    }
    if(v==0)
        s=3;
    win_lose();
}

void easy()
{
    int y,x=-1;
    srand(time(NULL));
    Position:
        {
            y=rand()%7;
            for(int i=5;i>-1;i--)
            {
                if(p[i][y]=='-')
                {
                    x=i;
                    break;
                }
            }
        }
    if(x<0)
        goto Position;
    fall(x,y,'O');
    p[x][y]='O';
}

void play()
{
    int x,y,g=0;
    srand(time(NULL));
    Position:
        {
            y=rand()%7;
            for(int i=5;i>-1;i--)
            {
                if(p[i][y]=='-')
                {
                    x=i;
                    break;
                }
            }
        }
    if(x<0)
        goto Position;
    if((anticipate_oppo(x,y)==false)&&(g<21))
        {
            goto Position;
            g++;
        }
    fall(x,y,'O');
    p[x][y]='O';
}

void smart()
{
    srand(time(NULL));
    bool x,y;
    //Self
    for(int i=5;i>-1;i--)
    {
        for(int j=0;j<7;j++)
        {
            if((p[i][j]=='-')&&((p[i+1][j]!='-')||(i==5)))
            {
                //Ends
                if((p[i+1][j]==p[i+2][j])&&(p[i+1][j]==p[i+3][j])&&(p[i+1][j]!='-')&&(i+3<6)&&(p[i+1][j]=='O'))         //Columns
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j+1]==p[i][j+2])&&(p[i][j+1]==p[i][j+3])&&(p[i][j+1]!='-')&&(j+3<7)&&(p[i][j+1]=='O'))         //Right
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j-1]==p[i][j-2])&&(p[i][j-1]==p[i][j-3])&&(p[i][j-1]!='-')&&(j-3>-1)&&(p[i][j-1]=='O'))        //Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j+1]==p[i-2][j+2])&&(p[i-1][j+1]==p[i-3][j+3])&&(p[i-1][j+1]!='-')&&(i-3<-1)&&(j+3<7)&&(p[i-1][j+1]=='O'))        //Up Right
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j-1]==p[i-2][j-2])&&(p[i-1][j-1]==p[i-3][j-3])&&(p[i-1][j-1]!='-')&&(i-3>-1)&&(j-3>-1)&&(p[i-1][j-1]=='O'))      //Up Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j-1]==p[i+2][j-2])&&(p[i+1][j+1]==p[i+3][j-3])&&(p[i+1][j+1]!='-')&&(i+3<6)&&(j-3>-1)&&(p[i+1][j]=='O'))         //Down Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j+1]==p[i+2][j+2])&&(p[i+1][j+1]==p[i+3][j+3])&&(p[i+1][j+1]!='-')&&(i+3<6)&&(j+3<7)&&(p[i+1][j+1]=='O'))
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                //Middle
                if((p[i][j-1]==p[i][j+1])&&(p[i][j-1]==p[i][j+2])&&(p[i][j-1]!='-')&&(j-1>-1)&&(j+2<7)&&(p[i][j-1]=='O'))       //Horizontal 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j-2]==p[i][j-1])&&(p[i][j-2]==p[i][j+1])&&(p[i][j-2]!='-')&&(j-2>-1)&&(j+1<7)&&(p[i][j-2]=='O'))       //Horizontal 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j-1]==p[i+1][j+1])&&(p[i-1][j-1]==p[i+2][j+2])&&(p[i-1][j-1]!='-')&&(i-1>-1)&&(j-1>-1)&&(i+2<6)&&(j+2<7)&&(p[i-1][j-1]=='O'))    //Diagonal A 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-2][j-2]==p[i-1][j-1])&&(p[i-2][j-2]==p[i+1][j+1])&&(p[i-2][j-2]!='-')&&(i-2>-1)&&(j-2>-1)&&(i+1<6)&&(j+1<7)&&(p[i-2][j-2]=='O'))    //Diagonal A 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j-1]==p[i-1][j+1])&&(p[i+1][j-1]==p[i-2][j+2])&&(p[i+1][j-1]!='-')&&(i+1<6)&&(j-1>-1)&&(i-2>-1)&&(j+2<7)&&(p[i+1][j-1]=='O'))    //Diagonal B 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+2][j-2]==p[i+1][j-1])&&(p[i+2][j-2]==p[i-1][j+1])&&(p[i+2][j-2]!='-')&&(i+2<6)&&(j-2>-1)&&(i-1>-1)&&(j+1<7)&&(p[i+2][j-2]=='O'))    //Diagonal B 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
            }
        }
    }
    //Opponent
    for(int i=5;i>-1;i--)
    {
        for(int j=0;j<7;j++)
        {
            if((p[i][j]=='-')&&((p[i+1][j]!='-')||(i==5)))
            {
                //Ends
                if((p[i+1][j]==p[i+2][j])&&(p[i+1][j]==p[i+3][j])&&(p[i+1][j]!='-')&&(i+3<6)&&(p[i+1][j]=='X'))         //Columns
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j+1]==p[i][j+2])&&(p[i][j+1]==p[i][j+3])&&(p[i][j+1]!='-')&&(j+3<7)&&(p[i][j+1]=='X'))         //Right
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j-1]==p[i][j-2])&&(p[i][j-1]==p[i][j-3])&&(p[i][j-1]!='-')&&(j-3>-1)&&(p[i][j-1]=='X'))        //Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j+1]==p[i-2][j+2])&&(p[i-1][j+1]==p[i-3][j+3])&&(p[i-1][j+1]!='-')&&(i-3<-1)&&(j+3<7)&&(p[i-1][j+1]=='X'))        //Up Right
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j-1]==p[i-2][j-2])&&(p[i-1][j-1]==p[i-3][j-3])&&(p[i-1][j-1]!='-')&&(i-3>-1)&&(j-3>-1)&&(p[i-1][j-1]=='X'))      //Up Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j-1]==p[i+2][j-2])&&(p[i+1][j+1]==p[i+3][j-3])&&(p[i+1][j+1]!='-')&&(i+3<6)&&(j-3>-1)&&(p[i+1][j]=='X'))         //Down Left
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j+1]==p[i+2][j+2])&&(p[i+1][j+1]==p[i+3][j+3])&&(p[i+1][j+1]!='-')&&(i+3<6)&&(j+3<7)&&(p[i+1][j+1]=='X'))
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                //Middle
                if((p[i][j-1]==p[i][j+1])&&(p[i][j-1]==p[i][j+2])&&(p[i][j-1]!='-')&&(j-1>-1)&&(j+2<7)&&(p[i][j-1]=='X'))       //Horizontal 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i][j-2]==p[i][j-1])&&(p[i][j-2]==p[i][j+1])&&(p[i][j-2]!='-')&&(j-2>-1)&&(j+1<7)&&(p[i][j-2]=='X'))       //Horizontal 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-1][j-1]==p[i+1][j+1])&&(p[i-1][j-1]==p[i+2][j+2])&&(p[i-1][j-1]!='-')&&(i-1>-1)&&(j-1>-1)&&(i+2<6)&&(j+2<7)&&(p[i-1][j-1]=='X'))    //Diagonal A 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i-2][j-2]==p[i-1][j-1])&&(p[i-2][j-2]==p[i+1][j+1])&&(p[i-2][j-2]!='-')&&(i-2>-1)&&(j-2>-1)&&(i+1<6)&&(j+1<7)&&(p[i-2][j-2]=='X'))    //Diagonal A 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+1][j-1]==p[i-1][j+1])&&(p[i+1][j-1]==p[i-2][j+2])&&(p[i+1][j-1]!='-')&&(i+1<6)&&(j-1>-1)&&(i-2>-1)&&(j+2<7)&&(p[i+1][j-1]=='X'))    //Diagonal B 1
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if((p[i+2][j-2]==p[i+1][j-1])&&(p[i+2][j-2]==p[i-1][j+1])&&(p[i+2][j-2]!='-')&&(i+2<6)&&(j-2>-1)&&(i-1>-1)&&(j+1<7)&&(p[i+2][j-2]=='X'))    //Diagonal B 2
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
            }
        }
    }
    //Trick
    for(int i=5;i>-1;i--)
    {
        for(int j=0;j<7;j++)
        {
            if((p[i][j]==p[i][j+1])&&(p[i][j]!='-')&&(p[i][j-1]=='-')&&((p[i+1][j-1]!='-')||(i==5))&&(p[i][j+2]=='-')&&((p[i+1][j+2]!='-')||(i==5))&&(p[i][j]=='O'))
            {
                if((p[i][j-2]=='-')&&((p[i+1][j-2]!='-')||(i==5))&&(j-2>-1)&&(p[i][j+3]=='-')&&((p[i+1][j+3]!='-')||(i==5))&&(j+3<7))       //Both
                {
                    if(anticipate_oppo(i,j-1)==true)
                    {
                        fall(i,j-1,'O');
                        p[i][j-1]='O';
                        return;
                    }
                    if(anticipate_oppo(i,j+2)==true)
                    {
                        fall(i,j+2,'O');
                        p[i][j+2]='O';
                        return;
                    }
                    if(anticipate_self(i,j-1)==true)
                    {
                        fall(i,j-1,'O');
                        p[i][j-1]='O';
                        return;
                    }
                    if(anticipate_self(i,j+2)==true)
                    {
                        fall(i,j+2,'O');
                        p[i][j+2]='O';
                        return;
                    }
                    int l=rand()%2;
                    if(l==1)
                    {
                        fall(i,j-1,'O');
                        p[i][j-1]='O';
                        return;
                    }
                    if(l==0)
                    {
                        fall(i,j+2,'O');
                        p[i][j+2]='O';
                        return;
                    }
                }
                if((p[i][j-2]=='-')&&((p[i+1][j-2]!='-')||(i==5))&&(j-2>-1))        //Left
                {
                    if((anticipate_oppo(i,j-1)==true)&&(anticipate_self(i,j-1)==true))
                    {
                        fall(i,j-2,'O');
                        p[i][j-2]='O';
                        return;
                    }
                    if((anticipate_oppo(i,j-2)==true)&&(anticipate_self(i,j-2)==true))
                    {
                        fall(i,j-1,'O');
                        p[i][j-1]='O';
                        return;
                    }
                    if(anticipate_oppo(i,j-1)==true)
                    {
                        fall(i,j-2,'O');
                        p[i][j-2]='O';
                        return;
                    }
                    if(anticipate_oppo(i,j-2)==true)
                    {
                        fall(i,j-1,'O');
                        p[i][j-1]='O';
                        return;
                    }
                }
                if((p[i][j+3]=='-')&&((p[i+1][j+3]!='-')||(i==5))&&(j+3<7))         //Right
                {
                    if((anticipate_oppo(i,j+2)==true)&&(anticipate_self(i,j+2)==true))
                    {
                        fall(i,j+3,'O');
                        p[i][j+3]='O';
                        return;
                    }
                    if((anticipate_oppo(i,j+3)==true)&&(anticipate_self(i,j+3)==true))
                    {
                        fall(i,j+2,'O');
                        p[i][j+2]='O';
                        return;
                    }
                    if(anticipate_oppo(i,j+2)==true)
                    {
                        fall(i,j+3,'O');
                        p[i][j+3]='O';
                        return;
                    }
                    if(anticipate_oppo(i,j+3)==true)
                    {
                        fall(i,j+2,'O');
                        p[i][j+2]='O';
                        return;
                    }
                }
            }
        }
    }
    //Anticipate
    for(int i=5;i>-1;i--)
    {
        for(int j=0;j<7;j++)
        {
            if((p[i][j]=='-')&&((p[i+1][j]!='-')||(i==5)))
            {
                x=anticipate_self(i,j);
                y=anticipate_oppo(i,j);
                if((x==true)&&(y==true))
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
                if(x==true)
                {
                    fall(i,j,'O');
                    p[i][j]='O';
                    return;
                }
            }
        }
    }
    play();
    return;
}

void new_game()
{
    if(diff==1)
    {
        for(;;)
            {
            display();
            input();
            display();
            check();
            if(s!=0)
            {
                cout<<endl;
                system("pause");
                initialize();
                menu();
            }
            smart();
            display();
            check();
            if(s!=0)
            {
                cout<<endl;
                system("pause");
                initialize();
                menu();
            }
        }
    }
    else if(diff==2)
    {
        for(;;)
            {
            display();
            input();
            display();
            check();
            if(s!=0)
            {
                cout<<endl;
                system("pause");
                initialize();
                menu();
            }
            easy();
            display();
            check();
            if(s!=0)
            {
                cout<<endl;
                system("pause");
                initialize();
                menu();
            }
        }
    }
}

void diffi1()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\nDIFFICULTY";
    cout<<"\nEasy <-";
    cout<<"\nHard";
    cout<<"\n\nPress esc to go back.";
}

void diffi2()
{
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\nDIFFICULTY";
    cout<<"\nEasy";
    cout<<"\nHard <-";
    cout<<"\n\nPress esc to go back.";
}

void difficulty()
{
    int k1,k2,k=1;
    diffi1();
    for(;;)
    {
        k1=_getch();
        if(k1==224)
        {
            k2=_getch();
            if(k2==80)
            {
                diffi2();
                k=2;
            }
            else if(k2==72)
            {
                diffi1();
                k=1;
            }
        }
        else if(k1==13)
        {
            if(k==1)
            {
                diff=2;
                menu();
            }
            else if(k==2)
            {
                diff=1;
                menu();
            }
        }
        else if(k1==27)
            menu();
    }
}

void hsc()
{
    fstream f2;
    player temp;
    f2.open("high_scores.dat",ios::in|ios::binary);
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\nHIGH SCORES\n";
    for(int i=0;i<10;i++)
    {
        f2.read((char*)&temp,sizeof(temp));
        cout<<(i+1)<<". "<<temp.name<<"\t\t - "<<temp.score<<endl;
    }
    f2.close();
}

void hsc1()
{
    hsc();
    cout<<endl<<"\nReset scores <- \t\tBack";
}

void hsc2()
{
    hsc();
    cout<<endl<<"\nReset scores    \t\tBack <-";
}

void reset_scores()
{
    remove("high_scores.dat");
    fstream f1;
    player s;
    strcpy(s.name,"EMPTY");s.score=0;
    f1.open("high_scores.dat",ios::out|ios::binary);
    for(int i=0;i<10;i++)
    {
        f1.write((char*)&s,sizeof(s));
        pl[i].score=s.score;
        strcpy(pl[i].name,s.name);
    }
    f1.close();
    menu();
}

void warn1()
{
    hsc();
    cout<<"\nDo you really want to delete all records?\n";
    cout<<"Yes <- \t\t No";
}

void warn2()
{
    hsc();
    cout<<"\nDo you really want to delete all records?\n";
    cout<<"Yes    \t\t No <-";
}

void warning()
{
    int k1,k2,k=1;
    warn1();
    for(;;)
    {
        k1=_getch();
        if(k1==224)
        {
            k2=_getch();
            if(k2==75)
            {
                warn1();
                k=1;
            }
            else if(k2==77)
            {
                warn2();
                k=2;
            }
        }
        else if(k1==27)
        {
            high_scores();
        }
        else if(k1==13)
        {
            if(k==1)
                reset_scores();
            else if(k==2)
                high_scores();
        }
    }
}

void high_scores()
{
    int k,k1,k2;
    hsc1();
    k=1;
    for(;;)
    {
        k1=_getch();
        if(k1==27)
            menu();
        else if(k1==224)
        {
            k2=_getch();
            if(k2==75)
            {
                hsc1();
                k=1;
            }
            else if(k2==77)
            {
                hsc2();
                k=2;
            }
        }
        else if(k1==13)
        {
            if(k==2)
                menu();
            else if(k==1)
                warning();
        }
    }
}

void rules()
{
    int k;
    system("cls");
    cout<<"\n                   PLOT 4                    "<<endl;
    cout<<"\nRULES";
    cout<<"\nPress left and right arrow keys to move, and enter to drop token.";
    cout<<"\nFirst to make 4 in a row (horizontal, vertical, diagonal) wins.";
    cout<<"\n\nPress esc to go back.";
    k=_getch();
    if((k==27)||(k==13))
        menu();
}

void arrange(int n)
{
    bool flag=true;
    char temp1[10];
    int temp2;
    strcpy(temp1,pl[n].name);
    temp2=pl[n].score;
    for(int i=n;i<9;i++)
    {
        pl[i].score=pl[i+1].score;
        strcpy(pl[i].name,pl[i+1].name);
    }
    if(n!=10)
    {
        strcpy(pl[9].name,"EMPTY");
        pl[9].score=0;
    }
    for(int i=0;((i<10)&&(flag));i++)
    {
        if((temp2>pl[i].score)||(strcmp(pl[i].name,"EMPTY")==0))
        {
            for(int j=9;j>i;j--)
            {
                pl[j].score=pl[j-1].score;
                strcpy(pl[j].name,pl[j-1].name);
            }
            pl[i].score=temp2;
            strcpy(pl[i].name,temp1);
            flag=false;
        }
    }
}

void save()
{
    char str[10];
    bool f=true;
    cout<<"\nEnter name (upto 10 characters): ";
    cin>>str;
    strcpy(pl[10].name,str);
    if(s==1)
        pl[10].score=1;
    else if(s==2)
        pl[10].score=0;
    else
        pl[10].score=0;
    for(int i=0;((i<10)&&(f));i++)
    {
        if(strcmp(pl[10].name,pl[i].name)==0)
        {
            if(s==1)
            {
                pl[i].score++;
                arrange(i);
            }
            else if((s==2)&&(pl[i].score>0))
            {
                pl[i].score--;
                arrange(i);
            }
            f=false;
        }
    }
    if(!f)
    {
        savedata();
    }
    else
    {
        arrange(10);
        savedata();
    }
}

void savedata()
{
    fstream f1;
    f1.open("high_scores.dat",ios::out|ios::binary);
    for(int i=0;i<10;i++)
    {
        f1.write((char*)&pl[i],sizeof(pl[i]));
    }
    f1.close();
    return;
}

int main()
{
    initialize();
    menu();
    return 0;
}
