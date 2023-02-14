#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAXSNAKESIZE 100
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Point{
	private:
		int x;
		int y;
	public:
		Point(){
			x = y = 10;
		}
		Point(int x, int y){
			this->x = x;
			this->y = y;
		}
		void SetPoint(int x, int y){
			this->x = x;
			this->y = y;
		}
		int GetX(){
			return x;
		}
		int GetY(){
			return y;
		}
		void MoveUp(){
			y--;
		}
		void MoveDown(){
			y++;
		}
		void MoveLeft(){
			x--;
		}
		void MoveRight(){
			x++;
		}
		void Draw(){
			gotoxy(x,y);
			cout << "*";
		}
		void Erase(){
			gotoxy(x,y);
			cout << " ";
		}
		void CopyPosition(Point *p){
			p->x = x;
			p->y = y;
		}
		void Debug(){
			cout << "(" << x << "," << y << ")";
		}
};

class Snake{
	private:
		Point *cell[MAXSNAKESIZE]; // array of points to represent snake
		int size; // current size of snake
		char dir; // current direction of snake
		Point fruit;
	public:
		Snake(){
			size = 1; // default size
			cell[0] = new Point(20, 20); // default position
			for(int i = 1; i<MAXSNAKESIZE; i++){
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%50, rand()%25);
		}
		void TurnUp(){
			dir = 'w';
		}
		void TurnDown(){
			dir = 's';
		}
		void TurnLeft(){
			dir = 'a';
		}
		void TurnRight(){
			dir = 'd';
		}
		void AddCell(int x, int y){
			cell[size++] = new Point(x,y);
		}
		void Move(){
			// clear screen
			system("cls");
			
			// the snake body follow its head
			for(int i=size-1; i > 0; i--){
				cell[i-1]->CopyPosition(cell[i]);
			}
			
			// create the new snake head
			switch(dir){
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
			}
			
			// when snake eat fruit
			if(fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()){
				AddCell(0,0);
				fruit.SetPoint(rand()%50, rand()%25);
			}
			
			// drawwing snake in console monitor
			for(int i = 0; i<size; i++){
				cell[i]->Draw();
			}
			// drawwing fruit
			fruit.Draw();
			
			Sleep(100);	
		}
		/*void Debug(){
			for(int i = 0; i<size; i++){
				cell[i]
			}
		}*/
};
int main(){
	// create title for console
	//SetConsoleTitle("Snake Game");
	
	// initialize the random number generator
	srand((unsigned)time(NULL));
	
	//Snake object
	Snake snake_01;
	char keyboard = 'g';
	do{
		if(kbhit()){
			keyboard = getch();
		}
		switch(keyboard){
			case 'w':
			case 'W':
				snake_01.TurnUp();
				break;
			case 's':
			case 'S':
				snake_01.TurnDown();
				break;
			case 'a':
			case 'A':
				snake_01.TurnLeft();
				break;
			case 'd':
			case 'D':
				snake_01.TurnRight();
				break;
		}
		snake_01.Move();
	}while(keyboard != 'e');
	return 0;
}
