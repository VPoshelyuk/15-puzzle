//"15-puzzle game" by Viachaslau Pashaliuk
//Honors project for CS13A

#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<windows.h> 
#include<conio.h> 

using namespace std;

HANDLE hConsole;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//Setting cursor position

void CoordXY(int X, int Y)
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}

enum direction {LEFT, UP, RIGHT, DOWN};//directions

int margin[4][4];
int empX, empY;
int moves=0;
string name;

int intro();
void crtmargin();
void drwmarginANDinfo(); 
void move(direction dir);
bool marginIC();
void finalization();


int main(){
intro();	
crtmargin();
drwmarginANDinfo();
char ch;
while(!marginIC()){//Game cycle
ch=getch();
switch(ch){
case 75: move(RIGHT); break;
case 72: move(DOWN); break;
case 77: move(LEFT); break;
case 80: move(UP); break;
case 27: return 0;}
drwmarginANDinfo();}
finalization();}

int intro(){//Introductionary screen
  CoordXY(20,10);
  printf("Welcome to my simple 15-puzzle game");
  CoordXY(18,11);
  printf("CS13A project by Viachaslau Pashaliuk");
  CoordXY(22,15);
  printf("Press 'Enter' to start the game");
  getch();
} 

void crtmargin(){	
 bool NumPicked[15]; //Check the position of 1-15 num.sq
 int Nums[15]; 
 for (int i=0; i<15;i++) //Shows that all num.sq tiles are free from the begining
 NumPicked[i]=true;
 srand(time(NULL));
 bool check; //Checks if the one or another numbered square can be placed to some position
 int rNum; 
 for (int i=0;i<15;i++){ //Defines the number of each num.sq in positions 1-15
  check=false; 
  while(!check){
   rNum=rand()%15+1; 
   if(NumPicked[rNum-1]) 
   check=true; //Assigning the right number for the num.sq(to exclude repetitions)
  }
  Nums[i]=rNum; //Assigning this number to an i th position in the Array
  NumPicked[rNum-1]=false; 
 }
 int disord=0; //# of disordered items
 int cNum; //Current num.sq
 for(int i=0;i<14;i++) { 
  cNum=Nums[i];
  for(int j=i+1;j<15;j++)
   if(cNum>Nums[j])
    disord++;
  }
 if(disord%2==1) //If sum of disordered items is odd,swap num.sq 14 with 15
  { 
  int temp=Nums[13];
  Nums[13]=Nums[14];
  Nums[14]=temp;
  }
 for (int i=0;i<15;i++)
  margin[i%4][i/4]=Nums[i]; 
  margin[3][3]=0;
  empX=3;
  empY=3;
 };
 
void drwmarginANDinfo(){//Draws margins and shows all needed info for a user during the game
 system("cls");
 for(int j=0;j<4;j++){
   CoordXY(12,2+3*j);
   for(int i=0;i<4;i++){
   	if(margin[i][j])
    cout<<"++++";
    else
    cout<<"    ";
    }
    cout<<"\n";
   CoordXY(12,3+3*j);
   for(int i=0;i<4;i++){
    if(margin[i][j]){
    cout<<"+";
    cout.width(2);
    cout<<margin[i][j]<<"+";
    }
    else
    cout<<"    ";
   	}
    cout<< "\n";
   CoordXY(12,4+3*j); 
   for(int i=0;i<4;i++){
    if(margin[i][j])
    cout<<"++++";
    else
    cout<<"    " ;
    }
    cout<<"\n";
  }
	 CoordXY(20,0);cout<<"15-puzzle game by Viachaslau Pashaliuk"<<endl;
	 CoordXY(50,2);cout<<"Summary:"<<endl ;
	 CoordXY(50,3);cout<<"# of Moves:"<<moves <<endl ;
	 CoordXY(50,7);cout<<"Control:"<<endl;
	 CoordXY(50,8);cout<<"Esc:Exit"<<endl;
	 CoordXY(50,10);printf("%c",24);cout<<":Up"<<endl;
	 CoordXY(50,11);printf("%c",25);cout<<":Down"<<endl;
	 CoordXY(50,12);printf("%c",27);cout<<":Left"<<endl;
	 CoordXY(50,13);printf("%c",26);cout<<":Right"<<endl; 
     CoordXY(30,16);cout<<"Last Winner:"<<endl;
  string line;//File I/O thing
  ifstream lwinner ("winner.txt");
  if(lwinner.is_open()){
  CoordXY(21,17);
  while ( getline (lwinner,line) ){//Reads the name and score of last winner from a file
  cout << line << '\n';}
  lwinner.close();}
  else{CoordXY(21,17);cout<<"No winners on this device yet!"<<endl;}   //If there are no winners yet,shows standard text
 }
 
void move(direction dir){
 switch (dir)
  {
  case LEFT:
   {
   if(empX<3)
    {
    margin[empX][empY]=margin[empX+1][empY];
    margin[empX+1][empY]=0;
    empX++;
    moves++;
    }
   } break;
  case UP:
   {
   if(empY<3)
    {
    margin[empX][empY]=margin[empX][empY+1];
    margin[empX][empY+1]=0;
    empY++;
    moves++;
    }
   } break;
  case RIGHT:
   {
   if(empX>0)
    {
    margin[empX][empY]=margin[empX-1][empY];
    margin[empX-1][empY]=0;
    empX--;
    moves++;
    }
   } break;
  case DOWN:
   {
   if(empY>0)
    {
    margin[empX][empY]=margin[empX][empY-1];
    margin[empX][empY-1]=0;
    empY--;
    moves++;
    }
   } break;
  }
 }

bool marginIC(){//Check for inconsistencies in game margins
 for (int i=0;i<15;i++)
  if (margin[i%4][i/4]!=i+1)return false;
 return true;
 }

void finalization(){
  CoordXY(0,18);cout<<"\nCongratulations!You just won the game!Today is your lucky day!";
  CoordXY(0,19);cout<<"\nPlease enter your name for the scoreboard:";
  cin>>name;
  ofstream lwinner;
  lwinner.open ("winner.txt");//Writes the name and scores of the last winner to the file
  lwinner<<"     Name: "<<name<<"||# of moves- "<<moves<<"                           \n";
  lwinner.close();
  cin.get();
}

