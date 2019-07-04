#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music *music = nullptr;

WINDOW *win, *win2;
bool flag = true;
void input();
void update();
void render();
int x=0,y=3;
std::string dragon = "\
(\"\"￣``-,　　　　 __／|\n\
ヽ;（￣ヽ `､　　　/ヾヽ|　 ＿\n\
　ヽ`'-､_ゝヽ..　　(\"＼ヽ＜。>-.,--､､___\n\
　　\"~ヾ-~``-`'-　＼.＼　,,\",,ヽ,)___,,..,,__＼\n\
　　　　　　　　　⊂二　／　,.-)|　／＼　`'-ゝ\n\
　　　┐┐__ 　　　（_／,,..-''\"-``/￣￣\n\
　／\"二\"＼i┐,,..,　　　　/.i ￣.i.|　　　／⌒ヽ\n\
　￣　＼ ＼-''\")＼　__./ .i\"￣`iヽ　／／\"i\".＼\n\
　　　,,..-''\"　.／　＼ヽ　 /----i　＼/　　　i　　＼\n\
,,..-''\"　　 ／ι］___/ .., /-─--i　 　）　rゝ　i　　　＼\n\
＼　　 ／⊂ゝ__　ヽヽ |i　　　　 i|　\"⌒丿ヽ　 i　　　 ＼\n\
　　|／　　＿　ヾ⊃--i\"\"￣￣\"＼__,.⊂-ヾ⊃　i　　／\n\
　　　￣￣i-　＼ ／　i\"-__＿___-\"ヽ＼_,.----.,,_i/\n\
　　　　　　i／　/　　 i_　　　　　　　i　| ヽ\n\
　　　　　　＼i i　　　 i `-──--`\"i .|　 |\n\
　　　　　　　ヽ|　　 i i_-__＿＿＿,-i /　　|\n\
　　　　　　　　＼　 ＼i-__　　　__／/　　/\n\
　　　　　　　　　＼＿,ゝ.二二--／　　 /\n\
　　　　　　　　　　/　　i　　　　<　　 ／\n\
　　　　　　　∠二_/ ./ ＼　　　.＼　＼\n\
　　　　　　　　　 ./／　ヽ...ゝ　　 ノ　　`'-､,_\n\
　　　　　　　　　　　　　　　　＜__,,.--,　＼--ゝ\n\
　　　　　　　　　　　　　　　　　　　　　 ＼|\n";
std::string magic = "\
		     　　　　　　　　　　　　　　　　　　　　　　　　　　 __,,:::========:::,,__\n\
　　　　　　　　　　　　　　　　　　　　　　　 ...‐''ﾞ .　　｀　´　´､ ゝ 　 ''‐...\n\
　　　　　　　　　　　　　　　　　　　　　 ..‐´　　　　　　ﾞ 　　　　　　　　 ｀‐..\n\
　　　　　　　　　　　　　　　　　　　　／　　　　　　　　　　　　　　　　　 　　＼\n\
　　　　　　　　.................;;;;;;;;;;;;;;;;;;;;;;::´　　　　　　　　　　　　　　　　　　　　　　 ヽ.:;;;;;;;;;;;;;;;;;;;;;;.................\n\
　　　.......;;;;;;;;;;ﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞ　　 　 　 .'　　　　　　　　　　　　　　　　　　 　 　 　 　 　ヽ　　　　　 ﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞ;;;;;;;;;;......\n\
　 ;;;;;;ﾞﾞﾞﾞﾞ　　　　　　　　　　　　/　　　　　　　　　　　　　　　　　　　　　　　　　　ﾞ:　　　 　 　 　　 　 　 　 ﾞﾞﾞﾞﾞ;;;;;;\n\
　　ﾞﾞﾞﾞﾞ;;;;;;;;............　 　　　　　 ;ﾞ　　　　　　　　　　　　　　　　　　　　　 　 　　　 　　ﾞ;　　　　　　　.............;;;;;;;;ﾞﾞﾞﾞﾞ\n\
　　　　　　ﾞﾞﾞﾞﾞﾞﾞﾞﾞ;;;;;;;;;;;;;;;;;.......;.............................　　　　　　　　　　　　　 ................................;.......;;;;;;;;;;;;;;;;;ﾞﾞﾞﾞﾞﾞﾞﾞﾞ\n\
　　　　　　　　 　 　 　 　ﾞﾞﾞﾞi;ﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;ﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞﾞ;lﾞﾞﾞﾞﾞ\n\
　　　　　　　　　　　　　　ﾉi|lli;　i　. .;,　､ 　　 .,,　　　　　　　　　　　　` ;　､　　.;　´ ;,il||iγ\n\
　　　　　　 　 　 　 　 　 /ﾞ||lii|li||,;,.il|i;,　; . ., ,li　　　'　;　　 .`　.;　　　　il,.;;.:||i　.i| :;il|l||;(ﾞ\n\
　　　　　 　　　　　　　 　　｀;;i|l|li||lｌｌ|||il;i:ii,..,.i||l´i,,.;,..　.il　｀,　　,i|;.,l;;:`ii||iil||il||il||l||i|liiﾞゝ\n\
　　　　　　　　　　　 　　　　 ﾞﾞ´`´ﾞ-;il||||il|||li||i||iiii;ilii;lili;||i;;;,,|i;,:,i|liil||ill|||ilill|||ii||lliﾞ/｀ﾞ\n\
　　　　　　　　　　　　　　　 　　　　´ﾞ｀ﾞ⌒ゞ;iill|||lli|llii:;|lii|||||l||ilil||i|llii;|;_ﾞι\n";

void input()
{
	switch(getch())
	{
		case 'q':
		flag = false;
		break;
		case 'c':
		{wclear(win);
		 	
		}
		break;
		case 'w':
		{
		 wclear(win);
		 if(y>3){
		 wmove(win,y--,2);
		 mvwaddstr(win,y,1,">");
		 }
		 else {
		 wmove(win,y=3,2);
		 mvwaddstr(win,y,1,">");
		 }
		 wrefresh(win);
		}
		break;
		case 's':
		{
		 wclear(win);
	 	 if(y<5)
		 {	 
		 wmove(win,y++,2);
		 mvwaddstr(win,y,1,">");
		 }
		 else {
		 wmove(win,y=5,2);
		 mvwaddstr(win,y,1,">");
		 }
		 wrefresh(win);
		}
		break;
		case '\n':
		{
		  //wclear(win2);
		  if(y == 3)
		  {
			  mvwaddstr(win2,3,3,"        ");
			  
			  mvwaddstr(win2,3,3,"attack");
		  }
		  if(y == 4)
		  {
			  mvwaddstr(win2,3,3,"         ");
			  mvwaddstr(win2,3,3, "run away!!");
		  }
		  if(y == 5)
		  {
			  mvwaddstr(win2,3,3,"         ");
			  mvwaddstr(win2,3,3,"BigBan!! Attack!!");
			  wrefresh(win2);
			  mvaddstr(10,1,magic.c_str());
			  refresh();
			  sleep(1);
			  mvaddstr(10,1,dragon.c_str());
			  refresh();

		  }
		  wrefresh(win2);
		  sleep(1);
		  wclear(win2);
		  wrefresh(win2);
		  
		}
		default:
		{
		wclear(win);	
		update();
		}
		break;
	}
}

void update()
{
	//mvwaddstr(win,3,3,"Fight");
	//wrefresh(win);
	/*
	clear();
	mvaddstr(10,1,dragon.c_str());
	refresh();
	box(win,0,0);
	box(win2,0,0);
	mvwaddstr(win,3,3,"たたかう");
	mvwaddstr(win,4,3,"にげる");
	mvwaddstr(win,5,3,"じゅもん");
	mvwaddstr(win2,3,3,"command?");
	
	wrefresh(win);
	wrefresh(win2);
	*/
}

void render()
{
	clear();
	mvaddstr(10,1,dragon.c_str());
	refresh();
	box(win,0,0);
	box(win2,0,0);
	mvwaddstr(win,3,3,"たたかう");
	mvwaddstr(win,4,3,"にげる");
	mvwaddstr(win,5,3,"じゅもん");
	mvwaddstr(win2,3,3,"command?");
	
	wrefresh(win);
	wrefresh(win2);

	
	
}


int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return -1;
			
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		return -1; 
	music = Mix_LoadMUS("SetAudioFile...");

	if(Mix_PlayMusic(music, -1) == -1)
	{
			Mix_FreeMusic(music);
			Mix_CloseAudio();
				
			//return -1;
	}

	win = newwin(10,20,0,0);
	//wborder(win, '#','#','#','#','#','#','#','#');
	box(win,0,0);
	win2 = newwin(10,50,30,0);
	box(win2,0,0);
	//mvwaddstr(win,1,0,"test");
	while(flag)
	{
		render();
		input();
		update();
		render();
		if(Mix_PlayingMusic());

		//wrefresh(win);
		//usleep(1000000);
	}	
	
	usleep(1000000);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	endwin();
	return 0;
}






