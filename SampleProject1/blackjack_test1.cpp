#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <algorithm>
#include <initializer_list>

using namespace std;
#define CARD_MAX 52
class card_rec{
	public:
	int no;
	int mark;
};
template <typename T>
bool is_in(const T& v, std::initializer_list<T> lst)
{
    return std::find(std::begin(lst), std::end(lst), v) != std::end(lst);
}
card_rec card[CARD_MAX];
void card_shuffle();
//山札定義
void card_input(){
	int i,tmp;
	for(i=0;i<CARD_MAX;i++){

		//数字を代入
		//if(i%13 == 0)
	        //		card[i].no=1;
		card[i].no=i%13;
		//card[i].no =card[i].no + 1;
		//マークを代入
		tmp=i/13;
		if(tmp == 0) card[i].mark=0;
		if(tmp == 1) card[i].mark=1;
		if(tmp == 2) card[i].mark=2;
		if(tmp == 3) card[i].mark=3;

	}
	//定義した山札をシャッフル
	card_shuffle();
}

void card_shuffle(){
	//一時変数
	int i,r,tmp_n;
	char tmp_m;

	//乱数の種に時間を設定
	srand((unsigned int)time(NULL));

	for(i=0;i<CARD_MAX;i++){

		//乱数取得
		r=rand()%CARD_MAX;

		//数値入れ替え
		tmp_n=card[i].no;
		card[i].no=card[r].no;
		card[r].no=tmp_n;

		//マーク入れ替え
		tmp_m=card[i].mark;
		card[i].mark=card[r].mark;
		card[r].mark=tmp_m;
	}
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	initscr();
	noecho();
			
	string suit[] = {"|♥    ♥ |","|♦    ♦ |","|♣    ♣ |","|♠    ♠ |"};
	string rank[] = {"|A    A |","|2    2 |","|3    3 |","|4    4 |",
	       		 "|5    5 |","|6    6 |","|7    7 |","|8    8 |",
			 "|9    9 |","|10   10|","|J    J |","|Q    Q |",
			 "|K    K |"};
        
		
	//test 2byte character...
	mvaddstr(0,1,"|♠　　♠ |\n");
	mvaddstr(1,1,"|A    A |\n");
	mvaddstr(0,5,"|♥　　♥ |\n");
	mvaddstr(1,5,"|10  10 |\n");
	mvaddstr(2,1,"Black Jack!!\n");
	mvaddstr(3,1,suit[0].c_str());
	mvaddstr(3,5,suit[3].c_str());
	mvaddstr(3,10,suit[1].c_str());
	mvaddstr(3,15,suit[2].c_str());
	card_input();
	for(int i = 0,j=0;i<52;i++,j=j+3){
        mvaddstr(5,j,rank[card[i].no].c_str());
	refresh();
	//mvaddstr(i+6,1,suit[card[i].mark].c_str());
	}
	int card1=0, card2=0;
	int card3=0, card4=0;
 	for(int i =0; i<52;i++){
	if(!is_in(card[i].no,{9,10,11,12}))
	{	card3 = card3 + card[i].no+1;
	}
	/*
	if(!is_in(card[17].no,{9,10,11,12}))
	{
		card4 = card[17].no+1;
	}
	*/
	}
	for(int i = 0,j=0;i<52;++i,j=j+3)
	{
		if(is_in(card[i].no,{9,10,11,12}))
			card1 = card1 +10;
	}
	
	mvaddstr(19,1,to_string(card1).c_str());

	int sum = card3 ;	
	//if((card1 != 10) || (card2 != 10))
	/*
	for(int i = 0;i<52;i++)
	{
		if(!is_in(card[i].no, {9,10,11,12}))
		sum = card[8].no+1 + card[17].no +1 ;
	}
	*/
	string ssum = to_string(sum);

	mvaddstr(20,1,ssum.c_str());
	refresh();
	usleep(1000000);
	getch();
	endwin();
	return 0;
}
