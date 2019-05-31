#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
//#include <random.h>


int FPS=60;
int MS_PER_FRAME= 1000000/FPS;
int MS_PER_TICK = 1000000 / FPS;
float N = 60;
static int mStartTime;
static int mCount;
static float mFps;

double getCurrentTime() { return 0;}
//void sleep(double time){}


struct {
	int x=0,y=0;
	char* str = "\\(^o^)/";
}typedef Chara;

struct {
	int x=0,y=0;
	char* str = "==";
	int flag =0;

}typedef Laser;

struct {
	int x=0, y=0;
	char * str = "(x_x)";
	int flag = 1;
	int rflag = 1;
}typedef Enemy;



static struct timeval start;

void timeUtilsInit(){
  gettimeofday(&start, NULL);
}

unsigned int timeUtilsGetMilliSeconds(){
  struct timeval tv;
  gettimeofday(&tv, NULL);
  time_t diffsec = difftime(tv.tv_sec, start.tv_sec);
  suseconds_t diffusec = tv.tv_usec - start.tv_usec;
  return (unsigned int)diffsec * 1000 + (unsigned int)(diffusec / 1000);
}

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
void input(Chara *ch1,Laser *ls1,Enemy *enemy1)
{

	
	switch(getch())
	{
		case('d'):
		if(ch1->x < COLS-7)
		ch1->x = ch1->x +1 ; 
		break;
		case('a'):
		if(ch1->x > 0)
		ch1->x = ch1->x -1 ;
		break;
		case('w'):
		if(ch1->y > 0)
		ch1->y = ch1->y -1;
		break;
		case('s'):
		if(ch1->y < LINES-1)
		ch1->y = ch1->y +1;
		break;
		case('l'):
		{
			if(!ls1->flag){
			ls1->flag=1;
			ls1->x=ch1->x;
			}
			else
			ls1->flag=1;

		}
		break;
		case('q'):
		exit(0);
		break;

	}


		

}

void update(Chara *ch1, Laser *ls1, Enemy *enemy1, int *r)
{
	if(ls1->flag)
	{
	if(ls1->x == COLS-2){

		ls1->x = ch1->x;
		ls1->y = ch1->y;
		ls1->flag=0;
		
			
	}
	if(ls1->flag)
		++ls1->x;
			

		
	
	}
	

	int r1;
	


	if(enemy1->flag)
	{
		if(enemy1->x == 0){
			enemy1->x = COLS-2;
			


			
			enemy1->y = *r;

		}
		enemy1->x--;
		

	}
	
	

		
}

void render(Chara *ch1 , Laser *ls1, Enemy *enemy1, int *r )
{
	//system("clear");
	clear();
	mvaddstr(ch1->y, ch1->x, ch1->str);
	
	if(ls1->flag)
	mvaddstr(ls1->y, ls1->x, ls1->str);
	//refresh();

	if(enemy1->flag){	

	mvaddstr(enemy1->y ,enemy1->x, enemy1->str);
	}
	refresh();


	
}


int main()
{
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	Chara ch1;
        Laser ls1;
	Enemy enemy1;
	srand(time(NULL));
	int r;
	while(1)
	{
		//double start = getCurrentTime();
		
		

		r = (rand()%LINES)+3;
		timeval t1,t2;
		double elapsedTime ;
		gettimeofday(&t1,NULL);
		const int FRAMES_PER_SECOND = 60;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
    double next_game_tick = elapsedTime;
    int sleep_time = 0;
		

		input(&ch1,&ls1, &enemy1);
		update(&ch1 , &ls1, &enemy1,&r);
		
		render(&ch1,&ls1,&enemy1,&r);
		//sleep(start + MS_PER_FRAME - getCurrentTime());
		gettimeofday(&t2, NULL); // stop timer after one full loop
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // compute sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // compute us to ms

    next_game_tick += SKIP_TICKS;
    sleep_time = next_game_tick - elapsedTime;
    if( sleep_time >= 0 )
        {
        usleep( sleep_time*1000 );
        }
	mvprintw(2,2,"%f",elapsedTime);
	}
	return 0;


}

