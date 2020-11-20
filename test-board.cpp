#include "board.cpp"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include<conio.h>
#include<windows.h>
Board b,tmp;
using namespace std;
COORD pos{0,0},pos2{0,6};
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
void cls(){
	SetConsoleCursorPosition(hOut,pos);
}
void resetinfo(){
	SetConsoleCursorPosition(hOut,pos2);
}
//0上
//1右
//2下
//3左
bool getmove(){
	char w=_getch();
	        while(w!='w'&&w!='a'&&w!='s'&&w!='d'){
	        	resetinfo(),fputs("unknown",stderr);
	        	w=_getch();
			}
	        switch(w){
	        	case 'w':
	        		if(!b.apply_move(0))return false;
	        		break;
				case 'a':
	        		if(!b.apply_move(3))return false;
	        		break;
			 	case 's':
	        		if(!b.apply_move(2))return false;
	        		break;
			 	case 'd':
	        		if(!b.apply_move(1))return false;
	        		break;
			}
			b.random_gennum();
			resetinfo(),fputs("       ",stderr);
			return true;
}
void test_state(){
    b.reset();
    while(1){
		cls(),b.print_board();
		while(!getmove())resetinfo(),fputs("invalid",stderr);

		//system("cls");
    }
}

int main(){
    srand(time(0));
    CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(hOut,&cursor_info);
    test_state();
    return 0;
}
