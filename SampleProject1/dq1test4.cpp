#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "dragon.txt"
std::string str;
std::string str2;
std::string aa = dragon;
Mix_Music *music = nullptr;
bool enemy_hide = false;

WINDOW *win;
WINDOW *win_if1, *win_if2;
WINDOW *win_if3;
WINDOW *win_flash;
void uirender();
void input();
void render();
void update();

void input()
{
	switch (getch())
	{
		case 'q':
		{
		endwin();
		exit(0);
		}
		break;
		case 'w':
		break;
		case 's':
		break;
		case 'j':
		{
			str = "ベギラマ";
			str2 = "のダメージ";
		/*	
		mvwaddstr(win_if1,5,5,str.c_str());
		*/
		mvwprintw(win_if1,5,5,"%s",str.c_str());
		wrefresh(win_if1);
		usleep(100000);
		mvwprintw(win_if1,5,5,"%s","");
		usleep(100000);
		wrefresh(win_if1);
		mvwprintw(win_if1,6,5,"%d %s",0,str2.c_str());
		str2 = "";
		wrefresh(win_if1);
		usleep(100000);
		mvwprintw(win_if1,6,5,"%s","");
		wrefresh(win_if1);
		}	

		break;
		case 'k':
		{
		str = "ヒャダルコ";
		mvwaddstr(win_if1,5,5,str.c_str());
		std::string flash = "■";
		for(int i=0;i<40*COLS;i++)
		{
		mvwaddstr(win_flash,0,0, flash.c_str());
		
		wrefresh(win_flash);
		flash += "■";
		}
		wclear(win_flash);
		wrefresh(win_flash);
		uirender();		
		wrefresh(win_if1);
		usleep(100000);
		mvwaddstr(win_if1,5,5,"                         ");
		usleep(100000);
		wrefresh(win_if1);
		mvwaddstr(win_if1,6,5,"きかなかった。");
			
		wrefresh(win_if1);
		uirender();
		}
		break;
		case 'c':
		if(!enemy_hide)
		{
			//aa = dragon.c_str();

			int count = dragon.length();
			std::string temp;
			aa ="";
		for(int i=0;i<count;i++)
		{
			//aa.resize(i,'\n');
			temp += ' ';
			mvwaddstr(win,2,2,temp.c_str());
			usleep(10000);
			wrefresh(win);
			
			
		}
		enemy_hide = true;
		}
		break;
		case 'p':
		if(enemy_hide)
		{
		aa = dragon.c_str();;
		std::string temp;
		for (int i =0;i<aa.length();i++)
		{
			temp += aa[i]; 
			mvwaddstr(win,2,2,temp.c_str());
			usleep(10000);
			wrefresh(win);
		}
		enemy_hide=false;
		}
		break;
		default:
		break;
	}
}
void uirender()
{
	box(win_if1,0,0);
	box(win_if2,0,0);
	box(win_if3,0,0);

	mvwaddstr(win_if1,1,1,"りゅうおうがあらわれた。");
		mvwaddstr(win_if1,2,1,"コマンド？");
		mvwaddstr(win_if2,0,1,"ゆうしゃ");
		mvwaddstr(win_if2,1,1,"HP");
		mvwaddstr(win_if2,2,1,"MP");
		mvwaddstr(win_if2,3,1,"Lv.99");
		mvwaddstr(win_if3,1,3,"たたかう");
		wrefresh(win_if1);
		wrefresh(win_if2);
		wrefresh(win_if3);
		mvwaddstr(win,2,2,aa.c_str());
		wrefresh(win);

	mvwaddstr(win_if1,5,5,"\n");	
	mvwaddstr(win_if1,5,5,str.c_str());
	//mvwaddstr(win_if1,6,5,str2.c_str());
	wrefresh(win_if1);

}
void update()
{
		str = "";
		str2 = "";
	/*	
	usleep(100000);
	mvaddstr(5,5,"\n");
	mvaddstr(6,5,"効果がなかった");
	*/
	wrefresh(win_if1);
	
	mvwprintw(win_if1,5,5,"%s","                         ");
	
	wrefresh(win_if1);
	mvwprintw(win_if1,6,5,"%s","                         ");
	usleep(100000);
	wrefresh(win_if1);
	//refresh();
}

void render()
{
	refresh();
	
}
int main()
{
	setlocale(LC_ALL,"");
	initscr();
	keypad(stdscr,TRUE);
	noecho();
	if (SDL_Init(SDL_INIT_AUDIO) <0)
		return -1;
	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2, 4096) == -1)
		return -1;

	music = Mix_LoadMUS("dq1_finalboss.opus");
	
	if(Mix_PlayMusic(music, -1) == -1)
	{
	
		Mix_FreeMusic(music);
		Mix_CloseAudio();
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME/16);

	win = newwin(26,58,2,10);
	win_if1 = newwin(10,60,28,20);
	win_if2 = newwin(5,20,0,0);
	win_if3 = newwin(10,20,28,0);
	win_flash = newwin(LINES,COLS,0,0);
	/*
	box(win_if1,0,0);
	box(win_if2,0,0);
	box(win_if3,0,0);
	*/
	//mvaddstr(2,2,aa.c_str());
	while(true)
	{
		refresh();
	/*	
		mvwaddstr(win_if1,1,1,"りゅうおうがあらわれた。");
		mvwaddstr(win_if1,2,1,"コマンド？");
		mvwaddstr(win_if2,0,1,"ロト");
		mvwaddstr(win_if2,1,1,"HP");
		mvwaddstr(win_if2,2,1,"MP");
		mvwaddstr(win_if2,3,1,"Lv.99");
		mvwaddstr(win_if3,1,3,"たたかう");
		wrefresh(win_if1);
		wrefresh(win_if2);
		wrefresh(win_if3);
		mvwaddstr(win,2,2,aa.c_str());
		wrefresh(win);
		*/
		uirender();
		input();
		update();
		if(Mix_PlayingMusic())
		//mvwaddstr(win,2,2,aa.c_str());
		//wrefresh(win);
		usleep(100000);
		render();

		usleep(100000);
	}
	Mix_FreeMusic(music);
	Mix_CloseAudio();

	endwin();
	return 0;
}

	
