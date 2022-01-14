//***************************************************************
//HEADERS
//***************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>


using namespace std;
//***************************************************************
//ACCOUNT STRUCTURE
//***************************************************************
struct account
{
    int number;
    char bank[100];
    char name[100];
    char nationalCode[10];
    double balance;

	void create_account();
	void show_account() const;
	void dep(int);
	void draw(int);
	int retacno() const;
	int retdeposit() const;
}acnt[100];

//***************************************************************
//FUNCTIONS
//***************************************************************

void account::create_account()
{
    system("cls");
    printf("\x1B[34m\n\n\n\tACCOUNT CREATION\033[0m");
	cout<<"\n\n\tEnter The account Number. :";
	cin>>number;
	cout<<"\n\n\tEnter The Name : ";
	cin.ignore();
	cin.getline(name,100);
	cout<<"\n\n\tEnter The National Code : ";
	cin.ignore();
	cin.getline(nationalCode,10);
	cout<<"\n\n\tEnter The Name of The Bank : ";
	cin.ignore();
	cin.getline(bank,100);
	balance=0;
	printf("\x1B[32m\n\n\n\tYOUR ACCOUNT HAS BEEN CREATED SUCCESSFULY !\033[0m");
	cout<<"\n\tFor Adding Credits,Go to The Main Menu And Choose Deposit . ";
    cout<<"\n\n\tPress any key two times to proceed";
    getch();
    getch();
}

void account::show_account() const
{
    system("cls");
    printf("\x1B[34m\n\n\n\tACCOUNT INFORMATION\033[0m");
	cout<<"\n\n\tAccount's Num. : "<<number<<endl;
	cout<<"\n\n\tAccount's Holder Name : "<<name<<endl;
	cout<<"\n\n\tNational Code of Account Holder : "<<nationalCode<<endl;
	cout<<"\n\n\tAccount's Bank : "<<bank<<endl;
	cout<<"\n\n\tBalance amount : "<<balance<<endl;
}

void account::dep(int x)
{
	balance+=x;
}

void account::draw(int x)
{
	balance-=x;
}

int account::retacno() const
{
	return number;
}

int account::retdeposit() const
{
	return balance;
}

//MAIN MENU
void displayMenu()
{
    system("cls");
    printf("\x1B[34m\n\n\n\tMAIN MENU\033[0m");
        cout<<"\n\n\t01. CREATE NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. DISPLAY ACCOUNT INFORMATION";
        cout<<"\n\n\t05. EXIT";
        cout<<"\n\n\tSelect Your Option (1-5) ";
}

//DEPOSIT AMOUNT
double deposit(double a,double b)
{
    a+=b;
    return a;
}

//WITHDRAW AMOUNT
double withdraw(double a,double b)
{
    a-=b;
    return a;
}

//***************************************************************
//FUNCTION PROTOTYOE
//***************************************************************
void write_account();
void deposit_withdraw(int, int);

//***************************************************************
//MAIN FUNCTION
//***************************************************************
int main()
{
    double amount;
    char choice;
    int num;
    do
    {
        displayMenu();
        cin>>choice;
        switch(choice)
        {
        case '1':
            {
                write_account();
                break;
            }
        case '2':
            {
                cout<<"\n\n\tEnter The account No. : ";
                cin>>num;
                deposit_withdraw(num, 1);
                break;
            }
        case '3':
            {
                cout<<"\n\n\tEnter The account No. : ";
                cin>>num;
                deposit_withdraw(num, 2);
                break;
            }
        case '4':
            {
                cout<<"\n\n\tEnter The account No. : ";
                cin>>num;
                deposit_withdraw(num, 3);
                break;
            }


        case '5':
            {
                system("cls");
                printf("\x1B[32m\n\n\n\tThanks for using bank managemnt system !\033[0m");
                getch();
                return 0;
                break;
                default:cout<<"\a";
            }
            cin.ignore();
            cin.get();
        }


    }while(choice!='5');


}
//***************************************************************
//WRITE FUNCTION
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
//***************************************************************
//DEPOSIT,WITHDRAW AND SHOW INFO. FUNCTION
//***************************************************************
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\n\n\tFile could not be open !!";
        cout<<"\n\n\tPress any key to proceed";
        getch();
        getch();
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			if(option==1)
			{
			    system("cls");
			    ac.show_account();
				printf("\x1B[34m\n\n\n\tDEPOSIT AMOUNT\033[0m");
				cout<<"\n\n\tEnter The amount to be deposited"<<endl;
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
			    system("cls");
			    ac.show_account();
				printf("\x1B[34m\n\n\n\tWITHDRAW AMOUNT\033[0m");
				cout<<"\n\n\tEnter The amount to be withdrawed"<<endl;
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				ac.draw(amt);
			}
			if(option==3)
            {
                system("cls");
                ac.show_account();
                cout<<"\n\n\tPress any key to proceed";
                getch();
                getch();
                break;
            }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			system("cls");
			printf("\x1B[32m\n\n\n\tYour Current Balance Has Updated!\033[0m");
			cout<<"\n\n\tPress any key two times to proceed";
			getch();
			getch();

			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
        cout<<"\n\n\tPress any key to proceed";
        getch();
        getch();
}

