#include<iostream>
#include<ctime>
#include<graphics.h>
#include"Tournament.h"
#include"Team.h"

using namespace std;
void Introduction();
void Graphics()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");

    int maxX=getmaxx();
    /**road*/

    for(int i=0,color=10;i<maxX;i++,color++)
    {
        setcolor(DARKGRAY);
        line(0,400,maxX,400);

        /**board*/
        setcolor(LIGHTBLUE);
        rectangle(400,300,425,400);
        setcolor(RED);
        rectangle(325,200,520,300);
        settextstyle(BOLD_FONT,HORIZ_DIR,1);
        outtextxy(330,225,"Domestic Premier");
        outtextxy(385,255,"League");
        /**bus*/
        setcolor(BLUE);
        rectangle(100+i,350,200+i,380);
        setcolor(CYAN);
        circle(120+i,390,10);
        circle(180+i,390,10);
        /**names*/
        outtextxy(50,180,"Made By:");
        outtextxy(50,210,"Aakash(2016UCO1559)");
        outtextxy(50,240,"Anshuman(2016UCO1558)");
        outtextxy(50,270,"Abhishek(2016UCO1563)");

        /**sun*/
        setcolor(YELLOW);
        circle(80+i,100,30);

        if(color>15)
            color=0;
        setcolor(color);
        //
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        setcolor(color+1);
        outtextxy(100,20,"MISSION FIXTURES");

        /**front*/
        line(475-i,130,490-i,120);
        line(475-i,130,490-i,140);
        line(490-i,120,520-i,120);
        line(490-i,140,520-i,140);

        /**side wings*/
        line(520-i,120,540-i,60);
        line(520-i,140,540-i,200);
        line(540-i,60,540-i,120);
        line(540-i,200,540-i,140);

        /**middle part*/
        line(540-i,120,580-i,120);
        line(540-i,140,580-i,140);

        line(580-i,120,590-i,80);
        line(580-i,140,590-i,180);
        line(590-i,80,590-i,125);
        line(590-i,180,590-i,135);

        /**end part*/
        line(590-i,125,600-i,125);
        line(590-i,135,600-i,135);
        line(600-i,125,600-i,135);

        if(i==0)
        {
            settextstyle(1,HORIZ_DIR,1);
            outtextxy(200,100,"Press Any Key");
            getch();
        }
        delay(1);
        cleardevice();
    }
    cleardevice();
    settextstyle(10,HORIZ_DIR,6);
    setcolor(YELLOW);
    outtextxy(225,30,"SPONSERS");
    setcolor(LIGHTGREEN);
    line(225,75,475,75);
    setcolor(LIGHTBLUE);
    circle(100,200,50);
    setcolor(LIGHTRED);
    bar(51,195,149,205);
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    setcolor(LIGHTGREEN);
    setbkcolor(CYAN);
    outtextxy(70,215,"PEPSI");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(LIGHTBLUE);
    setbkcolor(CYAN);
    rectangle(200,175,400,225);
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(LIGHTGREEN);
    outtextxy(235,190,"PAYTM");
    bar(450,175,625,225);
    setcolor(BLACK);
    settextstyle(BOLD_FONT,HORIZ_DIR,6);
    outtextxy(450,175,"F");
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    outtextxy(470,200,"reecharge");
    setcolor(GREEN);
    setbkcolor(BLACK);
    outtextxy(100,300,"Press Any Key to Continue...");
    getch();
    closegraph();
}

int main()
{
	Team t;
	Tournament Tment;
	int ch;
	Graphics();
    Introduction();
	START:
	cout<<"--------------MENU-------------"<<endl
        <<"|    1. DISPLAY TEAMS         |"<<endl
        <<"|    2. AVAILABLE TEAMS       |"<<endl
        <<"|    3. UPDATE TEAMS          |"<<endl
        <<"|    4. TOURNAMENT ORGANISE   |"<<endl
        <<"|    5. ADD TEAMS             |"<<endl
        <<"|    6. DELETE TEAMS          |"<<endl
        <<"|    7. EXIT                  |"<<endl
        <<"-------------------------------"<<endl
        <<"\nENTER YOUR CHOICE: ";
	cin>>ch;
	bool bad = false;
	cout<<"\a";
	bad=cin.fail();
    if (bad)
    {
        system("cls");
        cout<<"\n\n\t\tWORNG ENTRY"<<endl<<endl;
        system("pause");
        system("cls");
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        goto START;
    }
	srand(time(0));  /**Seed random generator(rand())*/
	switch(ch)
	{
	    case 1: system("cls");
                t.displayT();
                system("pause");
                system("cls");
                goto START;
                break;
        case 2: system("cls");
                cout<<"Available Teams for MATCHES"<<endl;
                Tment.readteams();
                Tment.display();
                system("pause");
                system("cls");
                goto START;
                break;
        case 3: system("cls");
                t.updateT();
                system("pause");
                system("cls");
                goto START;
                break;
        case 4: {   system("cls");
                    char day[3],month[3],year[5];
                    vector <string> Date;       /**to store match dates*/
                    vector <string> away;       /**to store all away teams*/
                    vector <string> home;       /**to store all home teams*/
                    Tment.readteams();
                    if(Tment.getNoOfTeams()>=4)
                    {
                        struct tm OpnDate = {0,0,12};
                        cout<<"Please input the Organize date in (DD/MM/YYYY) format: ";
                        cin.get(day,3,'/');
                        cin.ignore(100,'/');
                        cin.get(month,3,'/');
                        cin.ignore(100,'/');
                        cin.get(year,5);
                        /**convert them to int*/
                        OpnDate.tm_mday=atoi(day);
                        OpnDate.tm_mon=atoi(month);
                        OpnDate.tm_year=atoi(year);
                        OpnDate.tm_mon--;
                        OpnDate.tm_year=OpnDate.tm_year-1900;
                        system("cls");


                        Tment.displayrounds(&OpnDate);
                        system("pause");
                        system("cls");
                        Tment.points();
                        Datecounter=0;
                    }
                    else
                    {
                        cout<<"1.Insufficient Teams available"<<endl<<endl;
                        cout<<"2.Minimum 4 Teams required"<<endl<<endl;
                    }
                }
                system("pause");
                system("cls");
                goto START;
                break;
        case 5: system("cls");
                t.addT();
                system("pause");
                system("cls");
                goto START;
                break;
        case 6: system("cls");
                t.delT();
                system("pause");
                system("cls");
                goto START;
                break;
        case 7: system("cls");
                cout<<"\n\n\n\t\t\t\t T.";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t .H..";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t ..A...";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t ...N....";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t ....K.....";
                Sleep(1000);
                cout<<"\n\n\n\t\t\t\t Y.";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t .O..";
                Sleep(1000);
                cout<<"\n\n\t\t\t\t ..U...\n";
                system("pause");
                break;
       default: system("cls");
                cout<<"\n\n\t\tWORNG ENTRY"<<endl<<endl;
                system("pause");
                system("cls");
                goto START;
                break;
	}
	return 0;

}
void Introduction()
{
    system("pause");
    cout<<endl<<endl;
    cout<<" CODERS OF N.S.I.T "<<endl;
    cout<<" 1.AAKASH KUMAR GORYAN (2016UCO1559)"<<endl
        <<" 2.ABHISHEK DAS        (2016UCO1563)"<<endl
        <<" 3.ANSHUMAN DIWAKAR    (2016UCO1558)"<<endl<<endl;
    system("pause");
    system("cls");
    cout<<"\n\n\t\t"<<endl
        <<" IN ASSOCIATION WITH N.S.I.T"<<endl
        <<" UNDER THE GUIDANCE OF Mrs. SHAMPA CHAKARAVERTY"<<endl<<endl;
    system("pause");
    system("cls");
    cout<<"\n\n\t\t"
        <<" Presents...."<<endl
        <<" GAME FOR BETTING ON CRICKET"<<endl;
    system("pause");
    system("cls");
    cout<<"\n\n\t\t"
        <<" DETAILS OF GAME are as Follow:"<<endl
        <<" 1.Minimum Four Players Needed"<<endl
        <<" 2.Each player need to buy a team"<<endl
        <<" 3.Only one player can buy a team"<<endl
        <<" 4.Wining team owner will get all the money on BET"<<endl
        <<" 5.New teams can be added or removed as according to no. of players"<<endl
        <<" 6.TEams can be updated also later"<<endl<<endl;
    system("pause");
    system("cls");

}





