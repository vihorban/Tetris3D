#include <cstdlib>
#include <ctime>
#include "GL\glut.h"
#include "methods.h"
Cube::Cube():X(3),Y(TOP_BORDER-BOTTON_BORDER-1),Z(3)
{
}
Cube::Cube(int x,int y,int z):X(x),Y(y),Z(z)
{
}
void Cube::move(int x,int y,int z)
{
	X=x;
	Y=y;
	Z=z;
}
void Cube::draw()
{
	glPushMatrix();
	glTranslated(X-WIDTH_BORDER+0.5,Y+BOTTON_BORDER+0.5,Z-WIDTH_BORDER+0.5);
    glColor3f(0, 1, 0);                        
	glutSolidCube(1); 
	glColor3f(0, 0, 0); 
	glutWireCube(1);
    glPopMatrix();  
}
void Cube::movedown(int step)
{
	if(Y)
		Y-=step;
}
void drawCube()
{
	glPushMatrix();                                     
    glColor3f(0, 0.5, 0.9);                        
	glBegin(GL_LINES);
	for(int i=-WIDTH_BORDER;i<=WIDTH_BORDER;i++)
	{
		glVertex3i(i,BOTTON_BORDER,-WIDTH_BORDER);
		glVertex3i(i,BOTTON_BORDER,WIDTH_BORDER);
		glVertex3i(-WIDTH_BORDER,BOTTON_BORDER,i);
		glVertex3i(WIDTH_BORDER,BOTTON_BORDER,i);
	}
	glVertex3i(-WIDTH_BORDER,BOTTON_BORDER,-WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,BOTTON_BORDER,WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,BOTTON_BORDER,-WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,BOTTON_BORDER,WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(-WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,WIDTH_BORDER);
	glVertex3i(WIDTH_BORDER,TOP_BORDER,-WIDTH_BORDER);
	glEnd();
    glPopMatrix();     
}
void Cube::move_front()
{
	if(Z>0)
		Z-=1;
}
void Cube::move_back()
{
	if(Z<5)
		Z+=1;
}
void Cube::move_right()
{
	if(X<5)
		X+=1;
}
void Cube::move_left()
{
	if(X>0)
		X-=1;
}
Figure::Figure()
{
}
void Figure::renew(Game& a)
{
	Items.clear();
	type=rand()%2+1;
	if(type==1)
	{
		int size=rand()%3+1;
		height=width=length=size;
	}
	else
	{
		height=width=length=1;
		int size=rand()%3+2;
		int pos=rand()%3;
		if(pos==2)
			height=size;
		else if(pos==1)
			length=size;
		else
			width=size;
	}
	maxy=TOP_BORDER-BOTTON_BORDER-1;
	miny=maxy-height+1;
	minx=2;
	maxx=minx+width-1;
	minz=2;
	maxz=minz+length-1;
	int t=a.maxofarea(minx,maxx,minz,maxz);
	if(miny<t)
	{
		a.gameover=true;
		return;
	}
	for(int i=minx;i<=maxx;i++)
		for(int j=miny;j<=maxy;j++)
			for(int k=minz;k<=maxz;k++)
				Items.push_back(Cube(i,j,k));
}
void Figure::draw()
{
	for(unsigned int i=0;i<Items.size();i++)
		Items[i].draw();
}
void Figure::movedown(Game a)
{
	if(!nomove(a))
	{
		for(unsigned int i=0;i<Items.size();i++)
			Items[i].movedown();
		miny--;
		maxy--;
	}
}
void Figure::finalize(Game a)
{
	int border=a.maxofarea(minx,maxx,minz,maxz);
	for(unsigned int i=0;i<Items.size();i++)
		Items[i].movedown(miny-border);
	maxy=border+height;
	miny=border;
}
void Figure::move_front(Game a)
{
	if(!intersect(a,0,0,-1))
	{
		for(unsigned int i=0;i<Items.size();i++)
			Items[i].move_front();
		minz--;
		maxz--;
	}
}
void Figure::move_back(Game a)
{
	if(!intersect(a,0,0,1))
	{
		for(unsigned int i=0;i<Items.size();i++)
			Items[i].move_back();
		minz++;
		maxz++;
	}
}
void Figure::move_right(Game a)
{
	if(!intersect(a,1,0,0))
	{
		for(unsigned int i=0;i<Items.size();i++)
			Items[i].move_right();
		minx++;
		maxx++;
	}
}
void Figure::move_left(Game a)
{
	if(!intersect(a,-1,0,0))
	{
		for(unsigned int i=0;i<Items.size();i++)
			Items[i].move_left();
		minx--;
		maxx--;
	}
}
void Cube::showcoord(int& x,int& y,int& z)
{
	x=X;
	y=Y;
	z=Z;
}
Game::Game()
{
	score=0;
	gameover=false;
	Field.resize(TOP_BORDER-BOTTON_BORDER);
	for(unsigned int i=0;i<Field.size();i++)
	{
		Field[i].resize(2*WIDTH_BORDER);
		for(unsigned int j=0;j<Field[i].size();j++)
			Field[i][j].resize(2*WIDTH_BORDER,false);
	}
}
void Game::newgame()
{
	Field.clear();
	score=0;
	gameover=false;
	Field.resize(TOP_BORDER-BOTTON_BORDER);
	for(unsigned int i=0;i<Field.size();i++)
	{
		Field[i].resize(2*WIDTH_BORDER);
		for(unsigned int j=0;j<Field[i].size();j++)
			Field[i][j].resize(2*WIDTH_BORDER,false);
	}
}
void Game::add(Figure a)
{
	int x,y,z;
	for(unsigned int i=0;i<a.Items.size();i++)
	{
		a.Items[i].showcoord(x,y,z);
		if(y<TOP_BORDER-BOTTON_BORDER)
			Field[y][x][z]=true;
	}
}
int Game::maxofcol(int x,int z)
{
	int max=0;
	for(int i=Field.size()-1;(i>=0)&&(max==0);i--)
		if(Field[i][x][z])
			max=i+1;
	return max;
}
int Game::maxofarea(int minx,int maxx,int minz,int maxz)
{
  	int max=0;
	for(unsigned int i=minx;i<=maxx;i++)
		for(unsigned int j=minz;j<=maxz;j++)
		{
			int temp=maxofcol(i,j);
			if(temp>max)
				max=temp;
		}
	return max;
}
bool Game::check()
{	bool res=false;
	int deletes=0;
	for(unsigned int i=0;i<Field.size();i++)
	{
		bool needdelete=true;
		for(unsigned int j=0;(j<Field[i].size())&&needdelete;j++)
			for(unsigned int k=0;(k<Field[i][j].size())&&needdelete;k++)
				if(!Field[i][j][k])
					needdelete=false;
		if(needdelete)
		{
			Field.erase(Field.begin()+i);
			i--;
			deletes++;
			res=true;
			score++;
		}
	}
	for(int i=0;i<deletes;i++)
	{
		vector<vector<bool>> w;
		w.resize(2*WIDTH_BORDER);
		for(unsigned int j=0;j<w.size();j++)
			w[j].resize(2*WIDTH_BORDER,false);
		Field.push_back(w);
	}
	return res;
}
void Game::draw()
{
	for(unsigned int i=0;i<Field.size();i++)
		for(unsigned int j=0;j<Field[i].size();j++)
			for(unsigned int k=0;k<Field[i][j].size();k++)
				if(Field[i][j][k])
					Cube(j,i,k).draw();
}
bool Figure::nomove(Game a)
{
	return intersect(a,0,-1,0);
}
bool Figure::intersect(Game a,int dx,int dy,int dz)
{
	for(int i=minx;i<=maxx;i++)
		for(int j=miny;j<=maxy;j++)
			for(int k=minz;k<=maxz;k++)
				if(j+dy<0||j+dy>=TOP_BORDER-BOTTON_BORDER||i+dx<0||i+dx>=2*WIDTH_BORDER||k+dz<0||k+dz>=2*WIDTH_BORDER||a.value(j+dy,i+dx,k+dz)) 
					return true;
	return false;
}
bool Game::value(int x,int y,int z)
{
	return Field[x][y][z];
}
void glWrite(double x, double y, int *font,const char text[256], int kls)
{
    int i;
    glRasterPos2d(x, y);
    for (i=0; i<kls; i++)
            glutBitmapCharacter(font, (int)text[i]);
}
void Figure::rotate_left(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=width;
		Temp.width=height;
		Temp.minz=minz;
		Temp.length=length;
		if(height>width)
		{
			Temp.miny=miny+(height-1)/2;
			Temp.minx=minx-height/2;
		}
		else
		{
			Temp.miny=miny-(width-1)/2;
			Temp.minx=minx+width/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,-1,0,0))
		{
			Temp.move_left(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,1,0,0))
		{
			Temp.move_right(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-2,0,0))
		{
			Temp.move_doubleleft(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,2,0,0))
		{
			Temp.move_doubleright(a);
			*this=Temp;
		}
	}
}
void write_text_big(double R, double G, double B, double x, double y,const char str[255])
{
    glColor3d(R,G,B);
    glWrite(x, y, (int*)GLUT_BITMAP_TIMES_ROMAN_24, str, strlen(str));
}
void write_text_small(double R, double G, double B, double x, double y,const char str[255])
{
    glColor3d(R,G,B);
    glWrite(x, y, (int*)GLUT_BITMAP_TIMES_ROMAN_10, str, strlen(str));
}
void Figure::rotate_right(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=width;
		Temp.width=height;
		Temp.minz=minz;
		Temp.length=length;
		if(height>width)
		{
			Temp.miny=miny+(height-1)/2;
			Temp.minx=minx-height/2;
		}
		else
		{
			Temp.miny=miny-(width-1)/2;
			Temp.minx=minx+width/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,-1,0,0))
		{
			Temp.move_left(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,1,0,0))
		{
			Temp.move_right(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-2,0,0))
		{
			Temp.move_doubleleft(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,2,0,0))
		{
			Temp.move_doubleright(a);
			*this=Temp;
		}
	}
}
void Figure::rotate_front(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=length;
		Temp.width=width;
		Temp.length=height;
		Temp.minx=minx;
		if(height>length)
		{
			Temp.miny=miny+(height-1)/2;
			Temp.minz=minz-height/2;
		}
		else
		{
			Temp.miny=miny-(length-1)/2;
			Temp.minz=minz+length/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,0,0,-1))
		{
			Temp.move_front(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,1))
		{
			Temp.move_back(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,-2))
		{
			Temp.move_doublefront(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,2))
		{
			Temp.move_doubleback(a);
			*this=Temp;
		}
	}
}
void Figure::rotate_back(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=length;
		Temp.width=width;
		Temp.length=height;
		Temp.minx=minx;
		if(height>length)
		{
			Temp.miny=miny+(height-1)/2;
			Temp.minz=minz-height/2;
		}
		else
		{
			Temp.miny=miny-(length-1)/2;
			Temp.minz=minz+length/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,0,0,-1))
		{
			Temp.move_front(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,1))
		{
			Temp.move_back(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,-2))
		{
			Temp.move_doublefront(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,2))
		{
			Temp.move_doubleback(a);
			*this=Temp;
		}
	}
}
void Figure::turn_left(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=height;
		Temp.width=length;
		Temp.length=width;
		Temp.miny=miny;
		if(width>length)
		{
			Temp.minz=minz-(width-1)/2;
			Temp.minx=minx+width/2;
		}
		else
		{
			Temp.minz=minz+(length-1)/2;
			Temp.minx=minx-length/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,0,0,-1))
		{
			Temp.move_front(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,1))
		{
			Temp.move_back(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,-2))
		{
			Temp.move_doublefront(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,2))
		{
			Temp.move_doubleback(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-1,0,0))
		{
			Temp.move_left(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,1,0,0))
		{
			Temp.move_right(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-2,0,0))
		{
			Temp.move_doubleleft(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,2,0,0))
		{
			Temp.move_doubleright(a);
			*this=Temp;
		}
	}
}
void Figure::turn_right(Game a)
{
	if(type==2)
	{
		Figure Temp;
		Temp.type=2;
		Temp.height=height;
		Temp.width=length;
		Temp.length=width;
		Temp.miny=miny;
		if(width>length)
		{
			Temp.minz=minz-(width-1)/2;
			Temp.minx=minx+width/2;
		}
		else
		{
			Temp.minz=minz+(length-1)/2;
			Temp.minx=minx-length/2;
		}
		Temp.maxy=Temp.miny+Temp.height-1;
		Temp.maxz=Temp.minz+Temp.length-1;
		Temp.maxx=Temp.minx+Temp.width-1;
		for(int i=Temp.minx;i<=Temp.maxx;i++)
				for(int j=Temp.miny;j<=Temp.maxy;j++)
					for(int k=Temp.minz;k<=Temp.maxz;k++)
						Temp.Items.push_back(Cube(i,j,k));
		if(!Temp.intersect(a))
			*this=Temp;
		else if(!Temp.intersect(a,0,0,-1))
		{
			Temp.move_front(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,1))
		{
			Temp.move_back(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,-2))
		{
			Temp.move_doublefront(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,0,0,2))
		{
			Temp.move_doubleback(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-1,0,0))
		{
			Temp.move_left(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,1,0,0))
		{
			Temp.move_right(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,-2,0,0))
		{
			Temp.move_doubleleft(a);
			*this=Temp;
		}
		else if(!Temp.intersect(a,2,0,0))
		{
			Temp.move_doubleright(a);
			*this=Temp;
		}
	}
}
void Figure::move_doublefront(Game a)
{
	if(!intersect(a,0,0,-2))
	{
		for(unsigned int i=0;i<Items.size();i++)
		{
			Items[i].move_front();
			Items[i].move_front();
		}
		minz-=2;
		maxz-=2;
	}
}
void Figure::move_doubleback(Game a)
{
	if(!intersect(a,0,0,2))
	{
		for(unsigned int i=0;i<Items.size();i++)
		{
			Items[i].move_back();
			Items[i].move_back();
		}
		minz+=2;
		maxz+=2;
	}
}
void Figure::move_doubleright(Game a)
{
	if(!intersect(a,2,0,0))
	{
		for(unsigned int i=0;i<Items.size();i++)
		{
			Items[i].move_right();
			Items[i].move_right();
		}
		minx+=2;
		maxx+=2;
	}
}
void Figure::move_doubleleft(Game a)
{
	if(!intersect(a,-2,0,0))
	{
		for(unsigned int i=0;i<Items.size();i++)
		{
			Items[i].move_left();
			Items[i].move_left();
		}
		minx-=2;
		maxx-=2;
	}
}
void Figure::drawshadow(Game a)
{
	for(int i=minx;i<=maxx;i++)
		for(int j=minz;j<=maxz;j++)
		{
			int level=a.maxofcol(i,j)+BOTTON_BORDER;
			glColor3f(0,0,0);
			glBegin(GL_POLYGON);
			glVertex3f (i-3, level+0.01, j-3); 
			glVertex3f (i-3, level+0.01, j-2); 
			glVertex3f (i-2, level+0.01, j-2); 
			glVertex3f (i-2, level+0.01, j-3); 
			glEnd();
		}
}