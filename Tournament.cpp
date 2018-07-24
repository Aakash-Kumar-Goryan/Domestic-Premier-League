#include<iostream>
#include<windows.h>
#include<algorithm>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<string>
#include<conio.h>
#include<vector>
#define League " INDIAN PREMIER LEAGUE "
using namespace std;
static int Datecounter=0;
class Tournament
{
    vector<string> TeamsName;
    vector<string> away;
    vector<string> home;
    vector<string> Date;
    int NoOfRound;
    int NoOfTeams;
public:
    int getNoOfTeams()
    {
        return NoOfTeams;
    }
    friend void Loading();
    void readteams();
    void arrange();
    void DatePlusDays( struct tm* date, int days );
    void displayrounds(struct tm *OpnDate);
    void count(string winner,string loser,vector<int> &WIN,vector<int> &LOST);
    string ManOfTournament(string);
    void Final(vector <string> Finalist,string finaldate);
    void knockout(vector<int>&points);
    void points();
    void display();
    void Scorecard(vector <int> &WIN,vector <int> &LOST);
};

void Tournament::DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;
    /** Seconds since start of epoch*/
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;
    /** Update caller's date*/
    /** Use localtime because mktime converts to UTC so may change date*/
    *date = *localtime( &date_seconds ) ; ;
}

void Tournament::display()     //to display any vector
{
    int i,count=1;
    switch(NoOfTeams%2)
    {
        case 0: i=0;
                break;
        case 1: i=1;
                break;
    }
    if(TeamsName.size()!=0)
    {
        cout<<endl<<"* * * * * * * * * * * * * * * * * * * * *"
            <<endl<<"*                                       *"<<endl;
        while(i<TeamsName.size())
        {
            cout<<"*    "<<count++<<".";
            cout.setf(ios::left,ios::adjustfield);
            cout.width(29);
            cout<<TeamsName[i]<<"    *"<<endl;
            i++;
        }
        cout<<"*                                       *";
        cout<<endl<<"* * * * * * * * * * * * * * * * * * * * *"<<endl;
        cout.setf(ios::right,ios::adjustfield);
    }
    cout<<endl<<endl;
    TeamsName.clear();
}

void Tournament::displayrounds(struct tm *OpnDate)
{
    for(int n=0;n<NoOfRound;n++)
    {
        char tempdate[11];
        cout<<"Round  "<<n+1;
        cout<<endl;
        int i=0,k=TeamsName.size()/2;
        for(i=0;i<TeamsName.size()/2;i++,k++)
        {
            if(TeamsName[i]!="BYE")
            {
                cout.setf(ios::left,ios::adjustfield);
                cout.width(27);
                cout<<TeamsName[i]<<"   vs   ";
                home.push_back(TeamsName[i]);
                cout.width(27);
                cout<<TeamsName[k];
                away.push_back(TeamsName[k]);
                DatePlusDays(OpnDate,+1);
                strftime(tempdate,11,"%d %m %Y",OpnDate);
                Date.push_back(tempdate);
                cout<<"\t"<<Date[Datecounter++]<<endl;
            }
        }
        for(i=0;i<3;i++)        //Add 3 dates for semi finals
        {
            DatePlusDays(OpnDate,+1);
            strftime(tempdate,11,"%d %m %Y",OpnDate);
            Date.push_back(tempdate);
        }
        cout<<endl;
        arrange();
    }
}

void Tournament::arrange()       //To arrange v2 for next round
{
	string temp1,temp2;
	int i,j,siz;
	siz=TeamsName.size();
	i=(siz/2)-1;
	j=(siz/2);
	temp1=TeamsName[i];
	temp2=TeamsName[j];
	for(;i>=2;i--)   //i=3,2
	{
		TeamsName[i]=TeamsName[i-1];
	}
	for(;j<(siz-1);j++)       //j=5,6,7,8
	{
		TeamsName[j]=TeamsName[j+1];
	}
	TeamsName[1]=temp2;
	TeamsName[siz-1]=temp1;
}

void Tournament::points()
{
	vector <int> WIN;
	vector <int> LOST;
	int i;
	int TotalMatches =(NoOfTeams*(NoOfTeams-1))/2;
	int MatchesPerRound;
    MatchesPerRound=TotalMatches/NoOfRound;
	for(int i=0;i<TeamsName.size();i++)
    {
        WIN.push_back(0);
        LOST.push_back(0);
    }
	for(int i=0,j=1;i<TotalMatches;i++)
	{
        cout<<" ----------------------------------------------------------------"<<endl;
	    cout<<" |ROUND "<<j<<"\t\t\t\t\t\t\t|"<<endl;
        if((i+1)%MatchesPerRound==0)
        {
            j++;
        }
	    cout.setf(ios::left,ios::adjustfield);
	    cout<<" |DAY: "<<i+1<<"\t\t\t\t       "<<"DATE : "<<Date[i]<<"|"<<endl;
	    cout<<" ----------------------------------------------------------------"<<endl;
		cout<<" |";
        cout.setf(ios::left,ios::adjustfield);
	    cout.width(27);
		cout<<home[i]<<"  VS  ";
		cout.setf(ios::right,ios::adjustfield);
		cout.width(27);
		cout<<away[i]<<"\t|"<<endl;
		cout<<" |\t\t\t\t\t\t\t\t|"<<endl;
		cout<<" ----------------------------------------------------------------"<<endl;
        cout<<"  FINAL CONCLUSION OF THE MATCH "<<endl;
        Sleep(100);
        srand(time(NULL));
        int z=rand()%2;
        int wonby=(rand()%80)+1;
        int nwickets=(rand()%10)+1;
		int x=rand()%2;
		if(z==1)
        {
        if(x==0)
		{
			cout<<"	"<<endl<<"  ";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(27);
			cout<<home[i]<<" WON BY "<<wonby<<" RUNS "<<endl;
		    count(home[i],away[i],WIN,LOST);
		}
		else
		{
			cout<<"	"<<endl<<"  ";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(27);
			cout<<away[i]<<"\tWON BY "<<wonby<<" RUNS "<<endl;
		    count(away[i],home[i],WIN,LOST);
		}
        cout<<" ----------------------------------------------------------------"<<endl;
		Sleep(1000);
		system("cls");
	}
	if(z==0)
    {
        if(x==0)
		{
			cout<<"	"<<endl<<"  ";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(27);
			cout<<home[i]<<" WON BY "<<nwickets<<" WICKETS "<<endl;
		    count(home[i],away[i],WIN,LOST);
		}
		else
		{
			cout<<"	"<<endl<<"  ";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(27);
			cout<<away[i]<<"\tWON BY "<<nwickets<<" WICKETS "<<endl;
		    count(away[i],home[i],WIN,LOST);
		}
        cout<<" ----------------------------------------------------------------"<<endl;
		Sleep(1000);
		system("cls");
    }

	}
cout<<endl;
Scorecard(WIN,LOST);
system("PAUSE");
system("cls");
LOST.clear();
knockout(WIN);
}

void Tournament::count(string winner,string loser,vector<int> &WIN,vector<int> &LOST)
{
    for(int i=0;i<TeamsName.size();i++)		//8 times
	{
		if(TeamsName[i]==winner)
		{
			WIN[i]++;
		}
		if(TeamsName[i]==loser)
        {
            LOST[i]++;
        }
	}
}

void Tournament::knockout(vector<int>&points)
{
	int max=0;
	int i,j,pos;
	Datecounter=Datecounter-4;
	vector <string> SemiQuli;
	vector <string> Finalist;
	cout<<endl;
	cout<<" Teams Qualified for semi-finals"<<endl;
	for(j=0;j<4;j++)		//Displaying Qualified teams for Semi Final
	{
	    cout<<endl;
	    for(i=0;i<TeamsName.size();i++)		//8 times
        {
            if(points[i]>max)
            {
                pos=i;
                max=points[i];
            }
        }
        cout<<" "<<j+1<<".";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(27);
        cout<<TeamsName[pos]<<":    "<<max<<" points"<<endl;
        points[pos]=-1;
        SemiQuli.push_back(TeamsName[pos]);
        max=-1;
    }
    cout<<endl;
    random_shuffle(SemiQuli.begin(),SemiQuli.end());
    system("pause");
    system("cls");
    cout<<"\t\t\t KNOCKOUT"<<endl;
    for(i=1;i<=2;i++)       //Displaying Semi final match
    {
        cout<<" ----------------------------------------------------------------"<<endl;
	    cout<<" |SEMI FINAL "<<i<<"\t\t\t\t\t\t\t|"<<endl;
	    cout.setf(ios::left,ios::adjustfield);
	    cout<<" |DAY: "<<i<<"\t\t\t\t       "<<"DATE : "<<Date[Datecounter++]<<"|"<<endl;
	    cout<<" |";
        cout.setf(ios::left,ios::adjustfield);
	    cout.width(27);
		cout<<SemiQuli[i==1?0:2]<<"  VS  ";
		cout.setf(ios::right,ios::adjustfield);
		cout.width(29);
		cout<<SemiQuli[i==1?1:3]<<"|"<<endl;
        cout<<" ----------------------------------------------------------------"<<endl;
        cout<<"  FINAL CONCLUSION OF THE MATCH "<<endl;
        Sleep(100);
        srand(time(NULL));
        int z=rand()%2;
        int wonby=(rand()%80)+1;
        int nwickets=(rand()%10)+1;
		int x=rand()%2;
		if(z==1)        //Defending team won
        {
            if(x==0)
            {
                cout<<"	"<<endl<<"  ";
                cout.setf(ios::left,ios::adjustfield);
                cout.width(27);
                cout<<SemiQuli[i==1?0:2]<<" WON BY "<<wonby<<" RUNS "<<endl;
                cout<<" ----------------------------------------------------------------"<<endl<<endl;
                Finalist.push_back(SemiQuli[i==1?0:2]);
            }
            else
            {
                cout<<"	"<<endl<<"  ";
                cout.setf(ios::left,ios::adjustfield);
                cout.width(27);
                cout<<SemiQuli[i==1?1:3]<<"\tWON BY "<<wonby<<" RUNS "<<endl;
                cout<<" ----------------------------------------------------------------"<<endl<<endl;
                Finalist.push_back(SemiQuli[i==1?1:3]);
            }
        }
        if(z==0)        //chasing team won
        {
            if(x==0)
            {
                cout<<"	"<<endl<<"  ";
                cout.setf(ios::left,ios::adjustfield);
                cout.width(27);
                cout<<SemiQuli[i==1?0:2]<<" WON BY "<<nwickets<<" WICKETS"<<endl;
                cout<<" ----------------------------------------------------------------"<<endl<<endl;
                Finalist.push_back(SemiQuli[i==1?0:2]);
            }
            else
            {
                cout<<"	"<<endl<<"  ";
                cout.setf(ios::left,ios::adjustfield);
                cout.width(27);
                cout<<SemiQuli[i==1?1:3]<<"\tWON BY "<<nwickets<<" WICKETS"<<endl;
                cout<<" ----------------------------------------------------------------"<<endl<<endl;
                Finalist.push_back(SemiQuli[i==1?1:3]);
            }

        }
		if(i==1)
		cout<<endl<<endl<<"\t\t\tNEXT SEMI FINAL"<<endl;
    }
    cout<<endl;
    system("pause");
    system("cls");
    Final(Finalist,Date[Datecounter]);
    Finalist.clear();
    SemiQuli.clear();
    points.clear();
    TeamsName.clear();
}

void Tournament::readteams()
{
    TeamsName.clear();
    ifstream fin("Teams.txt");      //read and put data of "Teams" in vector v
    string ch;
    if(fin.fail()==1)          //if file not found
    {
        cout<<"\nFILE NOT FOUND!\n\nUse \"ADD TEAM\" to Create New File"<<endl<<endl;
    }
    else                //if file found
    {
        while(fin.eof()==0)
        {
            getline(fin,ch);
            TeamsName.push_back(ch);
            for(int i=0;i<13;i++)
            {
                fin.ignore(INT_MAX,'\n');
            }
        }
        NoOfTeams=TeamsName.size();
        NoOfRound=NoOfTeams%2 ? NoOfTeams : NoOfTeams-1;
        int Random=rand()%10;
        if(NoOfTeams>1)
        {
            /**Randomize team order to generate different result always*/
            for(int j=0;j<Random;j++)
            {
                rotate(TeamsName.begin(),TeamsName.begin()+NoOfTeams-2,TeamsName.end());
                random_shuffle(TeamsName.begin(),TeamsName.end());
            }
        }
        if((TeamsName.size()%2)!=0)
        {
            TeamsName.insert(TeamsName.begin(),"BYE");
        }
    }
    fin.close();    //read over
}
void Tournament::Scorecard(vector <int> &WIN,vector <int> &LOST)
{
    cout<<endl<<"  SCORE CARD: "<<endl;
    cout<<" -----------------------------------------------"<<endl;
    cout.setf(ios::left,ios::adjustfield);
    cout.width(30);
    cout<<" |TEAMS";
    cout.setf(ios::right,ios::adjustfield);
    cout<<"| WINs  |";
    cout<<"  LOST  |"<<endl;
    int i;
    switch(NoOfTeams%2)
    {
        case 0: i=0;
                break;
        case 1: i=1;
                break;
    }
    while(i<TeamsName.size())
    {
        cout<<" |\t\t\t      |\t      |\t       |"<<endl;
        cout<<" |";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(28);
        cout<<TeamsName[i]<<"|";
        cout.setf(ios::right,ios::adjustfield);
        cout.width(6);
        cout<<WIN[i]<<" | ";
        cout.width(6);
        cout<<LOST[i]<<" |";
        cout<<endl;
        i++;
    }
    cout<<" -----------------------------------------------"<<endl;
}

void Tournament::Final(vector <string> Finalist,string finaldate)
{
    cout<<" FINAL MATCH Of"<<League<<"\t\t\t\t"<<"Date: "<<finaldate<<endl<<endl;
    cout<<" Finalist 1: "<<Finalist[0]<<endl
        <<" Finalist 2: "<<Finalist[1]<<endl<<endl;
    cin.ignore(INT_MAX,'\n');
    //Loading();
    cout<<"  FINAL CONCLUSION OF THE MATCH "<<endl;
    Sleep(100);
    int wonby=(rand()%80)+1;
    int nwickets=(rand()%10)+1;
    int x=rand()%2;
    int z=rand()%2;
    if(z==0)
    {
    if(x==0)
    {
        cout<<"	"<<endl<<"  ";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(27);
        cout<<Finalist[0]<<" WON BY "<<wonby<<" RUNS"<<endl;
        cout<<" ----------------------------------------------------------------"<<endl<<endl;
        cout<<" MAN OF TOURNAMENT AWARD GOES TO -> "<<ManOfTournament(Finalist[0])<<" <-"<<endl;
    }
    else
    {
        cout<<"	"<<endl<<"  ";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(27);
        cout<<Finalist[1]<<"\tWON BY "<<wonby<<" RUNS "<<endl;
        cout<<" ----------------------------------------------------------------"<<endl<<endl;
        cout<<" MAN OF TOURNAMENT AWARD GOES TO -> "<<ManOfTournament(Finalist[1])<<" <-"<<endl;
    }
    cout<<"\n * * * * * THANKS FOR USING OUR AUTO CRICKET TOURNAMENT PROGRAM * * * * *"<<endl<<endl;
}
else
{
    if(x==0)
    {
        cout<<"	"<<endl<<"  ";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(27);
        cout<<Finalist[0]<<" WON BY "<<nwickets<<" WICKETS\a"<<endl;
        cout<<" ----------------------------------------------------------------"<<endl<<endl;
        cout<<" MAN OF TOURNAMENT AWARD GOES TO -> "<<ManOfTournament(Finalist[0])<<" <-"<<endl;
    }
    else
    {
        cout<<"	"<<endl<<"  ";
        cout.setf(ios::left,ios::adjustfield);
        cout.width(27);
        cout<<Finalist[1]<<"\tWON BY "<<nwickets<<" WICKETS\a"<<endl;
        cout<<" ----------------------------------------------------------------"<<endl<<endl;
        cout<<" MAN OF TOURNAMENT AWARD GOES TO -> "<<ManOfTournament(Finalist[1])<<" <-"<<endl;
    }
    cout<<"\n * * * * * THANKS FOR USING OUR AUTO CRICKET TOURNAMENT PROGRAM * * * * *"<<endl<<endl;
}

}

string Tournament::ManOfTournament(string Tname)
{
    string str;
    int x=(rand()%11)+1;
    ifstream fin("Teams.txt",ios::in);
	while(fin.eof()==0)
	{
		getline(fin,str);
		if(str==Tname)
		{
		    getline(fin,str);
		    for(int i=1;i<=x;i++)
            {
                fin>>str;
                fin.ignore(INT_MAX,'\n');
            }
            return str;

		}
    }
}

void Loading()
{
    int i;
    cout<<"Press Any key to Know the Conclusion of Final...";
    _getch();
    cout<<endl;
    // ARRIVAL
    cout.setf(ios::right,ios::adjustfield);
    for(i=1;i<=21;i=i+2)
    {
        cout<<"\r";
        cout<<setw(i)<<".";
        Sleep(40);
    }
    for(i=1;i<=19;i=i+2)
    {
        cout<<"\r";
        cout<<setw(i)<<"."<<setw(21-i)<<".";
        Sleep(40);
    }
    for(i=1;i<=17;i=i+2)
    {
        cout<<"\r";
        cout<<setw(i)<<"."<<setw(19-i)<<"."<<setw(2)<<".";
        Sleep(40);
    }
    // DEPARTURE
    for(i=1;i<=25;i=i+2)
    {
        cout<<"\r";
        cout<<setw(17)<<"."<<setw(2)<<"."<<setw(i+1)<<"."<<setw(26);
        Sleep(40);
    }
    for(i=1;i<=27;i=i+2)
    {
        cout<<"\r";
        cout<<setw(17)<<"."<<setw(i+1)<<"."<<setw(28);
        Sleep(40);
    }
    for(i=1;i<=28;i=i+2)
    {
        cout<<"\r";
        cout<<setw(17+i)<<"."<<setw(30);
        Sleep(40);
    }
    cout<<"\r                                                                 \r"<<endl;
}

