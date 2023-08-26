#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define HEIGHT 10
#define WIDTH 10

using namespace std;
bool check=false;
bool stan=true;
int next=0;
int how=10;
string Convert(int y, char word);
int draw[10] = {10,11,24,34,35,42,46,57,68,79};


class Gra_w_Statki{		
	class Board{
		public:
			void Create(int width, int height);
			void Show();
			int Check(string posytion, int length, bool unright, int myWidth, int myHeight, string **board);
			int GetMyWidth(){return myWidth;}
			int GetMyHeight(){return myHeight;}
			void SetSize(int width, int height);
			string** GetMyBoard(){return myBoard;}
			void Winer(int who, int lenght, string **board);
			void RemoveDynamic(){ delete [] myBoard;}
			~Board(){delete this;};  
			
		private:
			string **myBoard;
			int myWidth;
			int myHeight;
			char myChar;
			int myWin;
			int BoardAktyw;
	};
	
	class Ship : public Board{
		public:
			void Create(string posytion ,int lenght, bool unright,int xhelp, int yhelp, string **board );
			void Check(string posytion,int width,int height, string **board, string **boardhelp);
			void RemoveDynamic(){ delete [] myAccept; };
			~Ship(){delete this;};
		private:
			string myPosition;
			bool myUpright;
			bool *myAccept;
			bool myCheck;
			bool myOk;
	};
	
	public:
		void Uruchom();
	
};
//---------------------------------------------------------------------BOARD BOARD BOARD BOARD

void Gra_w_Statki::Board::SetSize(int width, int height){
    myWidth=width;
    myHeight=height;
}

void Gra_w_Statki::Board::Create(int width,int height){
	myChar='A';
	myBoard=new string*[width];
    for (int x=0; x<width; x++)
    	myBoard[x]=new string[height];

    for (int x=0; x<width; x++){
       for (int y=0; y<height; y++){

    	   myBoard[x][y]=Convert(y, myChar);
       }
        ++myChar;
    }
}
void Gra_w_Statki::Board::Show(){
    for (int x=0; x<myWidth; x++){
    	cout<<endl;
    	for (int y=0; y<myHeight; y++){
    		cout<<myBoard[x][y]<<" ";
    	}
    }
}

int Gra_w_Statki::Board::Check(string posytion, int length, bool unright, int myWidth, int myHeight, string **boardhelp){
	int y;
	istringstream iss(posytion);
    iss >> y;
	unsigned int x = posytion[posytion.length()-1];
	x=x-65;
	//cout<<"X: "<<x<<" Y: "<<y<<endl;
	//cout<<"Length: "<<length<<endl;
	int err=-5;
	int x_u,x_d, y_l, y_r;
	if(unright == true){
		if(x+length-1<myHeight){
			for(int i=x;i<(x+length);i++){
				if(boardhelp[i][y] == "||")err++;
			}
			if(err == -5){
				boardhelp[x][y] = "||";
				x_u=(x>=1?x-1:0);
				x_d=(x+length+1>myHeight?myHeight:x+length+1);
				y_l=(y-1>=0?y-1:0);		
				y_r=(y+2>myHeight?myHeight:y+2);
				//cout<<"True: XU: "<<x_u<<" XD: "<<x_d<<" YL: "<<y_l<<" YR: "<<y_r<<endl;
				for(int i=x_u;i<x_d;i++){
					for(int j=y_l;j<y_r;j++){
						boardhelp[i][j] = "||";
					}
				}
				err = 0;	
			}
		}else{
			err=1;
		}	
	}else{
		if(y+length-1<myWidth){
			for(int j=y;j<(y+length);j++){
				if(boardhelp[x][j] == "||")err++; 	
			}
			if(err == -5){
				boardhelp[x][y] = "||";
				y_l=(y>=1?y-1:0);		
				y_r=(y+length+1>myWidth?myWidth:y+length+1);
				x_u=(x>=1?x-1:0);
				x_d=(x+2>myWidth?myWidth:x+2);
				//cout<<"False: XU: "<<x_u<<" XD: "<<x_d<<" YL: "<<y_l<<" YR: "<<y_r<<endl;
				for(int i=x_u;i<x_d;i++){
					for(int j=y_l;j<y_r;j++){
						boardhelp[i][j] = "||";
					}
				}
				err = 0;
			}
		}else{
			err=1;
		}
 	}
	return err;
}

void Gra_w_Statki::Board::Winer(int who, int lenght, string ** board){
	myWin=0;
    for(int a=0;a<myWidth;a++)
        for(int b=0;b<myHeight;b++){
        	if(board[a][b]=="++"){
        		myWin++;
        	}
        }
        if(myWin==lenght){
                if(who==1){
                   for(int i =0;i<lenght;i++){
                   	cout<<"Wygra³es!!"<<endl;
                   }
                   stan=false;
                }else if(who == 2){
                	for(int i =0;i<lenght;i++){
                   	cout<<"Wygra³ Komputer!!"<<endl;
                   }
                   stan=false;
                }
        }
        
}

//-----------------------------------------------------------------------SHIP SHIP SHIP SHIP SHIP

void Gra_w_Statki::Ship::Create(string posytion ,int lenght, bool unright, int xhelp, int yhelp, string **board){
	myAccept=new bool[lenght];
	//myLength=0;
	myOk=true;
	for(int x=0; x<xhelp; x++){
		for(int y=0; y<yhelp; y++){
			if(posytion==board[x][y]){
				if(unright==true){
					if((x+lenght)<=xhelp){
						for(int a=0;a<lenght;a++){
							if(board[x+a][y]=="--"){
								myAccept[a]=false;
							}else
								myAccept[a]=true;
						}
					}else
					myOk=false;
				}else{
					if((y+lenght)<=yhelp){
						for(int a=0;a<lenght;a++){
							if(board[x][y+a]=="--"){
								myAccept[a]=false;
							}else
								myAccept[a]=true;
						}
					}else
					myOk=false;

				}
			}
		}
	}
	for(int a=0;a<lenght;a++){
			if(myAccept[a]==true&& myOk!=false){
				myOk=true;


			}else
			if(myOk==false&& myAccept[a]==true){
				myOk=false;
				cout<<"Loading..."<<endl;
			}else
			if(myAccept[a]==false){
				myOk=false;
				cout<<"Loading..."<<endl;
			}
	}
	for(int x=0; x<xhelp; x++){
		for(int y=0; y<yhelp; y++){
			if(posytion==board[x][y]){
				if(unright==true && myOk==true){
					for(int a=0;a<lenght;a++)
						board[x+a][y]="--";
						next++;
				}
				if(unright==false && myOk==true){
					for(int a=0;a<lenght;a++)
						board[x][y+a]="--";
						next++;

				}
			}
		}
	}
}
void Gra_w_Statki::Ship::Check(string posytion,int width,int height, string **board,string **boardhelp ){
    int y;

    istringstream iss(posytion);
    iss >> y;
	unsigned int x = posytion[posytion.length()-1];

	x=x-65;

	if(x <= width && y <= height){
	    if(boardhelp[x][y]!="()"){
            if(boardhelp[x][y]!="++"){
                if(board[x][y]=="--"&&check!=true){
                    boardhelp[x][y]="++";
                    board[x][y]="++";
                    check=true;
                }
                if(board[x][y]!="--"&&check!=true){
                    boardhelp[x][y]="()";
                    board[x][y]="()";
                    check=true;
                }
            }
	    }
	}else
	check=false;
}


string Random(){
	srand (how);
	how++;
	int zz,n;
	char z = 'A';
	n = (rand()%9);
	zz = (rand()%9);
	z +=zz;
	ostringstream ss;
	return Convert(n,z);
}

string Convert(int y, char word){
	   ostringstream ss;
	   ss << y;
	   string strNumber = ss.str();
	   string strSign(1, word);
	   return strNumber+strSign;
}

string UpperCase(string& word){
	for (int i=0; i<word.length(); i++){
		if (word[i]>96 && word[i]<123)//form small on big
	    word[i]=word[i]-32;
	}
	return word;
}

int CheckSymbol(string& positionShip, int unright){
	int error=0;
	UpperCase(positionShip);
	if(positionShip.length() == 2){
		if(!(positionShip[1]>64 && positionShip[1]<75)){//!error A-J
	    	error++;
	    }
	    
	    if(!(positionShip[0]>47 && positionShip[0]<58)){//!error 0-9
	    	error++;
	    }
	}else{//error ilosc znakow
		error++;
	}
	
	if(!(unright == 1 || unright == 2)){
		error++;
	}
	return error;
}

void Gra_w_Statki::Uruchom(){
	string Sboot;
    string posytion;
    string posytionShip;
    int unright;
    int error=0;
    const int Height = HEIGHT;
    const int Width = WIDTH;
	//Board User, Computer, UserHelp, ComputerHelp, ComputerUser;
	Board *User = new Board();
	Board *Computer = new Board();
	Board *UserHelp = new Board();
	Board *ComputerHelp = new Board();
	Board *ComputerUser = new Board();
	//Ship OneUs,TwoUs,ThreeUs, FourUs, OneCo,TwoCo,ThreeCo, FourCo;
	Ship *OneUs = new Ship();
	Ship *TwoUs = new Ship();
	Ship *ThreeUs = new Ship();
	Ship *FourUs = new Ship();
	Ship *OneCo = new Ship();
	Ship *TwoCo = new Ship();
	Ship *ThreeCo = new Ship();
	Ship *FourCo = new Ship();
	User->SetSize(Width,Height);
	User->Create(Width,Height);
	UserHelp->SetSize(Width,Height);
	UserHelp->Create(Width,Height);
	Computer->SetSize(Width,Height);
	Computer->Create(Width,Height);
	ComputerHelp->SetSize(Width,Height);
	ComputerHelp->Create(Width,Height);
	ComputerUser->SetSize(Width,Height);
	ComputerUser->Create(Width,Height);
	Board KUser(*User);
	Board KComputer(*ComputerUser);
		
	how = rand()&10;
	how = draw[how];
	
	do{
		error=0;
		KUser.Show();
		cout<<endl<<endl;
		cout<<"Podaj wspolrzedny na pierwszy rzedu statki: [0A-9J]  "<<endl;
		cin>>posytionShip;
		cout<<"Ulozenia Pionowo-1 czy Poziomo-2 "<<endl;
		cin>>unright;
		error = CheckSymbol(posytionShip,unright);
		if(error == 0){
			if(unright==1){ //Pionowo
				if(UserHelp->Check(posytionShip,1,true,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					OneUs->Create(posytionShip,1,true,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"Blad podany wspolrzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}else{
				if(UserHelp->Check(posytionShip,1,false,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					OneUs->Create(posytionShip,1,false,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"Blad podany wspolrzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}
		}else{
			cout<<"Blad podano wartosc wspolrzedny albo ulozenia"<<endl;
	}
	}while(error!=0);
	

	do{
		error=0;
		KUser.Show();
		cout<<endl<<endl;
		cout<<"Podaj wspolrzedny na drugiego rzedu statki: [0A-9J]  "<<endl;
		cin>>posytionShip;
		cout<<"Ulozenia Pionowo-1 czy Poziomo-2 "<<endl;
		cin>>unright;
		
		error = CheckSymbol(posytionShip,unright);
		
		if(error == 0){
			if(unright==1){ //Pionowo
				if(UserHelp->Check(posytionShip,2,true,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					TwoUs->Create(posytionShip,2,true,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"Blad podany wspolrzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}else{
				if(UserHelp->Check(posytionShip,2,false,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					TwoUs->Create(posytionShip,2,false,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"B³ad podany wsporzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}
		}else{
			cout<<"Blad podano wartosc wspolrzedny albo ulozenia"<<endl;
	}
	}while(error!=0);
	
	do{
		error=0;
		KUser.Show();
		cout<<endl<<endl;
		cout<<"Podaj wspolrzedny na trzeci rzedu statki: [0A-9J]  "<<endl;
		cin>>posytionShip;
		cout<<"Ulozenia Pionowo-1 czy Poziomo-2 "<<endl;
		cin>>unright;
		
		error = CheckSymbol(posytionShip,unright);
		
		if(error == 0){
			if(unright==1){ //Pionowo
				if(UserHelp->Check(posytionShip,3,true,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					ThreeUs->Create(posytionShip,3,true,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"Blad podany wspolrzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}else{
				if(UserHelp->Check(posytionShip,3,false,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					ThreeUs->Create(posytionShip,3,false,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"Blad podany wspolrzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}
		}else{
			cout<<"Blad podano wartosc wspolrzedny albo ulozenia"<<endl;
	}
	}while(error!=0);
	
	do{
		error=0;
		KUser.Show();
		cout<<endl<<endl;
		cout<<"Podaj wspolrzedny na czwarty rzedu statki: [0A-9J]  "<<endl;
		cin>>posytionShip;
		cout<<"Ulozenia Pionowo-1 czy Poziomo-2 "<<endl;
		cin>>unright;
		
		error = CheckSymbol(posytionShip,unright);
		
		if(error == 0){
			if(unright==1){ //Pionowo
				if(UserHelp->Check(posytionShip,4,true,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					FourUs->Create(posytionShip,4,true,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"B³ad podany wsporzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}else{
				if(UserHelp->Check(posytionShip,4,false,UserHelp->GetMyWidth(),UserHelp->GetMyHeight(),UserHelp->GetMyBoard())==0){
					FourUs->Create(posytionShip,4,false,User->GetMyWidth(),User->GetMyHeight(),User->GetMyBoard());
				}else{
					error++;
					cout<<"B³ad podany wsporzedny, jaki korozje statki albo poza granice pola"<<endl;
				}
			}
		}else{
			cout<<"B³ad podano wartosc wspolrzedna albo ulozenia"<<endl;
	}
	}while(error!=0);
	
    check=false;
    next =0;
    string tab[4];
    
	while(check==false){
		Sboot=Random();
		switch(next){
			case 0:{
				error=0;
				do{
					if(ComputerHelp->Check(Sboot,1,true,ComputerHelp->GetMyWidth(),ComputerHelp->GetMyHeight(), ComputerHelp->GetMyBoard())==0){
						OneCo->Create(Sboot,1,true,Computer->GetMyWidth(),Computer->GetMyHeight(),Computer->GetMyBoard());
						tab[0]=Sboot;
					}else{
						error++;
						Sboot=Random();
					}
					
				}while(error!=0);
			}break;
			case 1:{
				error=0;
				do{
					if(ComputerHelp->Check(Sboot,2,true,ComputerHelp->GetMyWidth(),ComputerHelp->GetMyHeight(),ComputerHelp->GetMyBoard())==0){
						TwoCo->Create(Sboot,2,true,Computer->GetMyWidth(),Computer->GetMyHeight(),Computer->GetMyBoard());
						tab[1]=Sboot;		
					}else{
						error++;
						Sboot=Random();
					}
				}while(error!=0);
			}break;
			case 2:{
				error=0;
				do{
					if(ComputerHelp->Check(Sboot,3,false,ComputerHelp->GetMyWidth(),ComputerHelp->GetMyHeight(),ComputerHelp->GetMyBoard())==0){
						ThreeCo->Create(Sboot,3,false,Computer->GetMyWidth(),Computer->GetMyHeight(),Computer->GetMyBoard());
						tab[2]=Sboot;
					}else{
						error++;
						Sboot=Random();
					}	
				}while(error!=0);         	
			}break;
			case 3:{
				error=0;
				do{
					if(ComputerHelp->Check(Sboot,4,false,ComputerHelp->GetMyWidth(),ComputerHelp->GetMyHeight(),ComputerHelp->GetMyBoard())==0){
						FourCo->Create(Sboot,4,false,Computer->GetMyWidth(),Computer->GetMyHeight(),Computer->GetMyBoard());
						tab[3]=Sboot;
					}else{
						error++;
						Sboot=Random();
					}
				}while(error!=0);
			}break;
			default:
			check=true;
			break;
		}
	}
	//for(int i=0;i<4;i++) cout<<tab[i]<<" ";
	cout<<endl;
	cout<<endl;

	do{
		system("cls");
        cout<<"USER"<<endl;
        KUser.Show();
        cout<<endl<<endl;
        cout<<"COMPUTER"<<endl;
		KComputer.Show();
        cout<<endl<<endl;
		check=false;
		while(check==false){
			cout<<"podaj pozycje statku :";
			cin>>posytion;
			UpperCase(posytion);
        	OneCo->Check(posytion,Computer->GetMyWidth(),Computer->GetMyHeight(), Computer->GetMyBoard(),ComputerUser->GetMyBoard());
        	TwoCo->Check(posytion,Computer->GetMyWidth(),Computer->GetMyHeight(), Computer->GetMyBoard(),ComputerUser->GetMyBoard());
        	FourCo->Check(posytion,Computer->GetMyWidth(),Computer->GetMyHeight(), Computer->GetMyBoard(),ComputerUser->GetMyBoard());
        	ThreeCo->Check(posytion,Computer->GetMyWidth(),Computer->GetMyHeight(), Computer->GetMyBoard(),ComputerUser->GetMyBoard());
		}
		check=false;
        while(check==false){
            Sboot=Random(); 
            OneUs->Check(Sboot,User->GetMyWidth(),User->GetMyHeight(), User->GetMyBoard(),User->GetMyBoard());
            TwoUs->Check(Sboot,User->GetMyWidth(),User->GetMyHeight(), User->GetMyBoard(),User->GetMyBoard());
            ThreeUs->Check(Sboot,User->GetMyWidth(),User->GetMyHeight(), User->GetMyBoard(),User->GetMyBoard());
            FourUs->Check(Sboot,User->GetMyWidth(),User->GetMyHeight(), User->GetMyBoard(),User->GetMyBoard());
   		}
   		
    	Computer->Winer(1,10,Computer->GetMyBoard());
    	User->Winer(2,10,User->GetMyBoard());
       
       
	}while(stan);
	
	system("Pause");
	
	User->RemoveDynamic();
	UserHelp->RemoveDynamic();
	Computer->RemoveDynamic();
	ComputerHelp->RemoveDynamic();
	OneUs->RemoveDynamic();
	TwoUs->RemoveDynamic();
	ThreeUs->RemoveDynamic();
	FourUs->RemoveDynamic();
	OneCo->RemoveDynamic();
	TwoCo->RemoveDynamic();
	ThreeCo->RemoveDynamic();
	FourCo->RemoveDynamic();	

	delete User;
	delete Computer;
	delete UserHelp;
	delete ComputerHelp;
	delete ComputerUser;
	delete OneUs;
	delete TwoUs;
	delete ThreeUs;
	delete FourUs;
	delete OneCo;
	delete TwoCo;
	delete ThreeCo;
	delete FourCo;

}

int main(){
	Gra_w_Statki * sProj = new Gra_w_Statki();
	sProj->Uruchom();
	delete sProj;
	
    return 0;
}

