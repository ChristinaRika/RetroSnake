#define U 1  //up
#define D 2  //down
#define L 3  //left
#define R 4  //right
#define MAP_WIDTH 56
#define MAP_HEIGHT 26
#define HIT 1
#define EAT 2
#define EXIT 3

typedef struct SNAKE //Snake's body node
{
	int x;
	int y;
	struct SNAKE *next;
}snake;

struct
{
	int x;
	int y;
}food;

int score, add;          //Total score and score when eat the food
int Direction, sleeptime;      //Time pause
snake *head;               //Snake's head and food pointer
int flag;            //Gameover: 1.hit the wall;2.eat it self;3.exit.

#ifndef GOTOXY
#define GOTOXY
void gotoxy(int x, int y);
#endif

#ifndef CREATE_MAP
#define CREATE_MAP
void createMap(void);
#endif 

#ifndef INIT_SNAKE
#define INIT_SNAKE
void initSnake(void);
#endif 

#ifndef EAT_ITSELF
#define EAT_ITSELF
int eatSelf(void);
#endif 

#ifndef CREATE_FOOD
#define CREATE_FOOD
void createFood(void);
#endif 

#ifndef IF_HIT_WALL
#define IF_HIT_WALL
void ifHitWall(void);
#endif 

#ifndef SNAKE_MOVE
#define SNAKE_MOVE
void snakeMove(void);
#endif

#ifndef PAUSE
#define PAUSE
void pause(void);
#endif 

#ifndef RUN_GAME
#define RUN_GAME
void runGame(void);
#endif 

#ifndef INIT_GAME
#define INIT_GAME
void initGame(void);
#endif 

#ifndef END_GAME
#define END_GAME
void endGame(void);
#endif 

#ifndef GAME_START
#define GAME_START
void gameStart(void);
#endif

#ifndef CHOOSE_HARD_LEVEL
#define CHOOSE_HARD_LEVEL
void chooseHardLevel(void);
#endif 

#ifndef CLICK_EVENT
#define CLICK_EVENT
void clickEvent(void);
#endif 
