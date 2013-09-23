#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include "GL\glut.h"
#include "methods.h"
using namespace std;
int WindW, WindH;
GLfloat light_position0[] = { 100.0, 100.0, 100.0, 0.0 };
GLfloat light_diffuse0[] = {1.0, 1.0, 1.0, 0.0};
GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };
GLfloat light_diffuse1[] = {0.0, 1, 0, 1.0};
GLfloat light_position2[] = { -10.0, -10.0, -10.0, 0.0 };
GLfloat light_diffuse2[] = {0, 1, 0, 1.0};
bool light0=false,light1=false,light2=false,pause=false,mouseover=true;
int num=0,mover=0;
Figure Temp,Next;
Game MyGame;
double alpha=POSALPHA,beta=POSBETA;
void enable2D()
{
	glViewport(0, 0, WindW, WindH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1000, 1000, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void enable3D()
{
	glViewport(0, 0, WindW, WindH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, WindW/double(WindH), 1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void en_light()
{
	if(light0||light1||light2) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);
    if(light0) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
	if(light1) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);
	if(light2) glEnable(GL_LIGHT2);
	else glDisable(GL_LIGHT2);
}
void pos_light()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
}
void Controls(int key, int x, int y)
{
	if(!pause)
	{
	if(key==GLUT_KEY_UP)
  {
	  Temp.move_front(MyGame);
  }
	if(key==GLUT_KEY_DOWN)
  {
	  Temp.move_back(MyGame);
  }
	if(key==GLUT_KEY_RIGHT)
  {
	  Temp.move_right(MyGame);
  }
if(key==GLUT_KEY_LEFT)
  {
	  Temp.move_left(MyGame);
  }
	}
}
void NewGame()
{
	MyGame.newgame();
	Temp.renew(MyGame);
	Next.renew(MyGame);
}
void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  en_light();
  glPushMatrix();
  glTranslatef(0, 0,-25);
  glRotatef(beta, 1, 0, 0);
  glRotatef(alpha, 0, 1, 0);
  drawCube();
  Temp.draw();
  Temp.drawshadow(MyGame);
  MyGame.draw();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(26, 6,-65);
  glRotatef(30, 1, 0, 0);
  glRotatef(30, 0, 1, 0);
  Next.draw();
  glPopMatrix();
  enable2D();
  if(MyGame.gameover)
  {
	write_text_big(1,0,0,-125,0,"Game Over!"); 
	if(mover%6<3)
		write_text_small(0,0,0,-100,-175,"Press Space to play again"); 
  }
  string Score;
  for(int temp=MyGame.score;temp;temp/=10)
	  Score.insert(Score.begin(),temp%10+48);
  if(MyGame.score==0) Score.push_back('0');
  Score=string("Score: ")+Score;
  write_text_small(0,0,0,850,900,Score.c_str());
  write_text_small(0,0,0,850,875,"Next:"); 
  write_text_small(0,0,0,810,475,"Arrows - move figure"); 
  write_text_small(0,0,0,810,450,"Space - instant move down"); 
  write_text_small(0,0,0,810,425,"A,D - rotate left/right:"); 
  write_text_small(0,0,0,810,400,"W,S - rotate front/back:");
  write_text_small(0,0,0,810,375,"Q,E - turn left/right:");
  write_text_small(0,0,0,810,350,"P - pause");
  if(pause) write_text_big(1,0,0,-75,0,"Pause");
  glBegin(GL_POLYGON);
  glColor3f(1,1,0);
  glVertex2d(765,1000);
  glVertex2d(780,1000);
  glVertex2d(780,300);
  glVertex2d(765,300);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(1,1,0);
  glVertex2d(765,325);
  glVertex2d(765,300);
  glVertex2d(1000,300);
  glVertex2d(1000,325);
  glEnd();
  enable3D();
  glutSwapBuffers();
  glutPostRedisplay();
}
void Reshape(int width, int height)
{
	WindW = width;
  WindH = height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30, WindW/double(WindH), 1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void initwindow(int argc, char **argv)
{
	srand(time(0));
	WindW = 1000;
	WindH = 700;
	glutInit(&argc, argv);
  glutInitWindowSize(WindW, WindH);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("3D tetris");
  glClearColor(1, 1, 1, 1.0f);              
  glClearDepth(1.0f);                                  
  glEnable(GL_DEPTH_TEST);                             
  glDepthFunc(GL_LEQUAL);                              
  glShadeModel(GL_SMOOTH);                             // Включается плавное затенение
  glEnable(GL_LINE_SMOOTH);                            // Включается сглаживание линий
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);              // Выбирается самый качественный режим сглаживания для линий
  glEnable(GL_BLEND);                                  // Включается смешение цветов
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // способ смешения
}
void nextstep()
{
	if(!MyGame.gameover)
	{
	if(num)
		num--;
	else if(Temp.nomove(MyGame))
	{
		MyGame.add(Temp);
		Temp=Next;
		Next.renew(MyGame);
		if(MyGame.check())
			num++;
	}
	else
		Temp.movedown(MyGame);
	}
}
void timf(int value)
{
  glutPostRedisplay();
  if(mouseover)
  {
	  SetCursorPos(WindW/2,WindH/2);
	  ShowCursor(false);
  }
  if(!pause) mover++;
  if(mover==100000) mover=0;
  if(mover%5==0&&!pause)
	  nextstep();
  glutTimerFunc(200, timf, 0);
}
void Visibility(int state)
{
	if (state == GLUT_NOT_VISIBLE) cout<<"Window not visible!\n";
  if (state == GLUT_VISIBLE) cout<<"Window visible!\n";
}
void OnKeyboardEvent(unsigned char keyCode, int x, int y)
{
	switch(keyCode)
	{
		case 's'://rotete back
			if(!pause)
				Temp.rotate_back(MyGame);
			break;
		case 'w'://rotate front
			if(!pause)
				Temp.rotate_front(MyGame);
			break;			
		case 'p':
			pause=!pause;
			break;
		case '4':
			alpha-=1;
			break;
		case '6':
			alpha+=1;
			break;
		case 'e'://turn right
			if(!pause)
				Temp.turn_right(MyGame);
			break;
		case 'q'://turn left
			if(!pause)
				Temp.turn_left(MyGame);
			break;
		case '2':
			beta+=1;
			break;
		case '8':
			beta-=1;
			break;
		case '5':
			alpha=POSALPHA; beta=POSBETA;
			break;
		case '3':
			if(mouseover)
			{
				mouseover=false;
				ShowCursor(true);
			}
			else
			{
				mouseover=true;
				ShowCursor(false);
			}
			break;
		case 'a'://rotate left
			if(!pause)
				Temp.rotate_left(MyGame);
			break;
		case 'd'://rotate right
			if(!pause)
				Temp.rotate_right(MyGame);
			break;
		case 'g':
			glutFullScreen();
			break;
		case 'l':
			light0=!light0;
			break;
		case 'k':
			light1=!light1;
			break;
		case 'j':
			light2=!light2;
			break;
		case 'c':
			NewGame();
			break;
		case ' ':
			if(!pause&&!MyGame.gameover)
				Temp.finalize(MyGame);
			if(MyGame.gameover)
				NewGame();
			break;
		case Esc:
			exit(0);
	}
}
void OnMouseButton(int button, int state, int x, int y)
{
}
void OnMouse(int x, int y)
{
	if(mouseover)
	{
		beta+=double(y)/WindH*6-3;
		alpha+=double(x)/WindW*6-3;
	}
}
int main(int argc, char **argv)
{
	srand(time(0));
	NewGame();
	initwindow(argc, argv);
	glutDisplayFunc(Draw);
	pos_light();
	SetCursorPos(WindW/2,WindH/2);
	glutMouseFunc(OnMouseButton);
	glutPassiveMotionFunc(OnMouse);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Controls);
	glutTimerFunc(200, timf, 0);
	glutVisibilityFunc(Visibility);
	glutKeyboardFunc(OnKeyboardEvent);
	glutFullScreen();
	glutMainLoop();
	return 0; 
}
