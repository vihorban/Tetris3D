#include <vector>
#include <string>
using namespace std;
#define Esc 27
#define Tab 9
#define Del 127
#define Enter 13
#define Backspace 8
#define PI 3.14159265358979323846264338332795
#define INF 1000000000
#define SMALL 1
#define TOP_BORDER 8
#define BOTTON_BORDER -5
#define WIDTH_BORDER 3
#define POSBETA 32
#define POSALPHA -20
class Game;
class Cube
{
	int X,Y,Z;
public:
	Cube();
	Cube(int,int,int);
	void move(int,int,int);
	void movedown(int step=1);
	void draw();
	void move_left();
	void move_right();
	void move_front();
	void move_back();
	void showcoord(int&,int&,int&);
};
class Figure
{
	vector<Cube> Items;
	int type,height,width,length,minx,maxx,miny,maxy,minz,maxz;//type: 1-cube,2-line
public:
	friend class Game;
	Figure();
	void rotate_right(Game);
	void rotate_left(Game);
	void turn_left(Game);
	void turn_right(Game);
	void rotate_front(Game);
	void rotate_back(Game);
	void move_left(Game);
	void move_right(Game);
	void move_front(Game);
	void move_back(Game);
	void move_doubleleft(Game);
	void move_doubleright(Game);
	void move_doublefront(Game);
	void move_doubleback(Game);
	void movedown(Game);
	void finalize(Game);
	void draw();
	void drawshadow(Game);
	bool nomove(Game);
	void renew(Game&);
	bool intersect(Game,int dx=0,int dy=0,int dz=0);
};
class Game
{
	vector<vector<vector<bool>>> Field;
public:
	int score;
	bool gameover;
	Game();
	void add(Figure);
	int maxofcol(int,int);
	int maxofarea(int,int,int,int);
	bool check();
	bool value(int,int,int);
	void draw();
	void newgame();
};
void drawCube();
void write_text_big(double R, double G, double B, double x, double y, const char str[255]);
void write_text_small(double R, double G, double B, double x, double y, const char str[255]);
void glWrite(double x, double y, int *font,const char text[256], int kls);