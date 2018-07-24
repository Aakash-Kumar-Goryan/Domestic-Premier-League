#include "Team.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<conio.h>
#define MAX 11
using namespace std;
class player
{
    string name;
	int age;
	float avg;
	string Ntion;
public:
    void AddPlayer();                     /**to Get player data*/
    void WritePlayer(ofstream &fout);     /**to write in file using fout*/
};

class Team:public player
{
	string Tname;
	public:
	void displayT();
	bool fileExists(const char *fileName);
	void addT();
	void delT();
	void updateT();
};
void player::AddPlayer()
{
    cout<<"\nEnter name: ";
    getline(cin,name);
    cout<<"Enter age: ";
    cin>>age;
    cout<<"Enter bating avg: ";
    cin>>avg;
    cout<<"Enter Nationality: ";
    cin.ignore(INT_MAX,'\n');
    getline(cin,Ntion);
}

void player::WritePlayer(ofstream &fout)
{
    fout.setf(ios::left,ios::adjustfield);
    fout.width(10);
    fout<<name<<"\t\t\t";
    fout.width(3);
    fout<<age<<"\t";
    fout.width(3);
    fout<<avg<<"\t"<<Ntion<<endl;
}

void Team::displayT()
{
	ifstream fin("Teams.txt");
	string str;
	if(fin.fail()==1)
    {
        cout<<"FILE NOT FOUND!\n\nUse \"ADD TEAMS\" to Create New File"<<endl<<endl;
    }
    else
    {
        while(fin.eof()==0)
        {
            getline(fin,str);
            cout<<str<<endl;
        }
        fin.close();
    }
}

bool Team::fileExists(const char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

void Team::addT()
{
	cout<<endl;
	cout<<"Enter New Team name: ";
	cin.ignore(INT_MAX,'\n');
    getline(cin,Tname);
    transform(Tname.begin(), Tname.end(), Tname.begin(), ::toupper);
    bool file_status=fileExists("Teams.txt");
    ofstream fout("Teams.txt",ios::app);
    if(file_status==true)     /**i.e file not empty*/
    {
        fout<<endl<<Tname<<endl;
    }
    else
    if(file_status==false)
    {
        fout<<Tname<<endl;
    }
    fout<<"PlayerName"<<"\t\t\t"<<"Age"<<"\t"<<"Avg"<<"\t"<<"Nationality"<<endl;
    for(int i=1;i<=MAX;i++)
    {
        cout<<"\nPlayer "<<i<<endl;
        AddPlayer();
        WritePlayer(fout);
    }
    fout.close();
    cout<<endl;
}

void Team::delT()       /**Function to delete teams from "Teams.txt" File*/
{
    int Check=0;
	string str;
	ifstream fin("Teams.txt",ios::in);
	if(fin.fail()==1)
    {
        cout<<"\nFILE NOT FOUND\n\nUse \"ADD TEAMS\" to Create New File"<<endl<<endl;
    }
    else
    {
        cout<<"Enter name of the team to be Deleted: ";
        cin.ignore(INT_MAX,'\n');
        getline(cin,Tname);
        transform(Tname.begin(), Tname.end(), Tname.begin(), ::toupper);
        ofstream fout("Temp.txt",ios::out);
        getline(fin,str);
        if(str==Tname)
        {
            Check++;
            for(int i=0;i<MAX+2;i++)        /** MAX = Total no. of players in team i.e 11*/
            {
                fin.ignore(INT_MAX,'\n');
            }
        }
        else
            fout<<str<<endl;
        while(fin.eof()==0)
        {
            getline(fin,str);
            if(str!="")
            {
                fout<<str<<endl;
            }
            else
            if(str=="")
            {
                getline(fin,str);
                if(str==Tname)
                {
                    Check++;
                    for(int i=0;i<MAX+2;i++)        //13 times
                    {
                        fin.ignore(INT_MAX,'\n');
                    }
                }
                if(fin.eof()==0)
                {
                    fout<<endl;
                }
                if(str!=""&&str!=Tname)
                {
                    fout<<str<<endl;
                }
            }
        }
        if(fout.tellp()==0)     /**if file is empty then remove files*/
        {
            fin.close();
            fout.close();
            remove("Teams.txt");
            remove("Temp.txt");
        }
        else
        {
            fin.close();
            fout.close();
            remove("Teams.txt");
            rename("Temp.txt","Teams.txt");
        }
        if(Check!=0)
        {
            cout<<endl<<"SUCESSFULLY DELETED"<<endl<<endl;
        }
        if(Check==0)
        {
            cout<<endl<<"!!!!TEAM NOT FOUND!!!!"<<endl<<endl;
        }
    }
}

void Team::updateT()
{
    static int check;
    int count=0;
    string str;
    string tempPname;
    int ch;
    ifstream fin("Teams.txt",ios::in);
	if(fin.fail()==1)
    {
        cout<<"FILE NOT FOUND!\n\nUse \"ADD TEAMS\" to Create New File"<<endl<<endl;
    }
    else
    {
        ofstream fout("Temp.txt",ios::out);
        cout<<"Enter Name of Team to be Updated: ";
        cin.ignore(INT_MAX,'\n');
        getline(cin,Tname);
        transform(Tname.begin(), Tname.end(), Tname.begin(), ::toupper);
        while(fin.eof()==0)
        {
            getline(fin,str);
            if(str!=Tname)
            {
                if(fin.eof()==0)
                {
                    fout<<str<<endl;
                }
                else
                    fout<<str;
            }
            else
            {
                check++;
                cout<<endl
                    <<"--------------MENU-------------"<<endl
                    <<"|    1. Team name             |"<<endl
                    <<"|    2. player details        |"<<endl
                    <<"-------------------------------"<<endl
                    <<"Enter what you want to UPDATE: ";
                    cin>>ch;
                lable:
                check=ch;
                switch(ch)
                {
                    case 1: cout<<"\nEnter New Name for Team: ";
                            cin.ignore(INT_MAX,'\n');
                            getline(cin,Tname);
                            transform(Tname.begin(), Tname.end(), Tname.begin(), ::toupper);
                            fout<<Tname<<endl;
                            for(int i=0;i<MAX+1;i++)
                            {
                                getline(fin,str);
                                fout<<str<<endl;
                            }
                            break;

                    case 2: fout<<str<<endl;
                            getline(fin,str);
                            fout<<str<<endl;
                            cout<<"\nEnter Name of Player to be Edited: ";
                            cin>>tempPname;
                            while(fin.eof()==0)     //until file end not reached
                            {
                                count++;
                                fin>>str;
                                if(str==tempPname)
                                {
                                    check++;
                                    fin.ignore(50,'\n');
                                    cin.ignore(INT_MAX,'\n');
                                    AddPlayer();
                                    WritePlayer(fout);
                                }
                                else
                                {
                                    fout<<str;
                                    getline(fin,str);
                                    if(fin.eof()==0)
                                    {
                                        fout<<str<<endl;
                                    }
                                    else
                                    {
                                        fout<<str;
                                    }
                                }
                                if(count==MAX)
                                {
                                    break;
                                }
                            }
                            break;

                    default: cin.clear();
                             cin.ignore(INT_MAX,'\n');
                             cout<<"\nWorng Entry\nENTRY Again: ";
                             cin>>ch;
                             goto lable;
                             break;
                }
            }
		}
		fin.close();
        if(check==0)
        {
            cout<<"\n**TEAM NOT FOUND**"<<endl<<endl;
        }
        if(check==2)
        {
            cout<<"\n**PLAYER NOT FOUND**"<<endl<<endl;
        }
        if(check==1||check==3)
        {
            cout<<"\nSUCESSFULL CHANGED"<<endl<<endl;
        }
        fin.close();
        fout.close();
        remove("Teams.txt");
        rename("Temp.txt","Teams.txt");
    }
}
