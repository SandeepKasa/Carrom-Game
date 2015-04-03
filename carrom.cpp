#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <math.h>
#include <sys/time.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
//Board class for some general functions

class Board{
	public:
		void drawBox(float len,int t,float c) {
			glTranslatef(0.0f, 0.0f, c);

			if(t==0)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         
			glBegin(GL_QUADS);
                        glVertex2f(-len / 2, -len / 2);
			glVertex2f(len / 2, -len / 2);
			glVertex2f(len / 2, len / 2);
			glVertex2f(-len / 2, len / 2);
			glEnd();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		void drawBall(float rad,float x,float y) {
			glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glBegin(GL_LINE_LOOP);
			for(int i=0 ; i<360 ; i++) {
				glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
			}
			glEnd();
			glPopMatrix();
		}
};



class Coins{
	public:
	float x;
	float y;
	float rad;
	float vel_x;
	float vel_y;
	int sno;
/*	void Coins(float x,float y,float rad,int sno)
	{
		this.x=x;
		this.y=y;
		this.rad=rad;
		this.sno=sno;
	}*/
	void drawBall(float rad,float x,float y) 
	{
		 glPushMatrix();
		  glTranslatef(x, y, 0.0f);

		glBegin(GL_TRIANGLE_FAN);
	        for(int i=0 ; i<360 ; i++) {
			glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
		}
		glEnd();
		glPopMatrix();
	}
};

class Line{
	public:
	float x1;
	float x2;
	float y1;
	float y2;
	float lee;
	int theta;
        void drawLine(float x1,float y1,float x2,float y2,float l,float theta)
	{
		glLineWidth(2.5);
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_LINES);
		glVertex3f(x1, y1,0.0);
//		glVertex3f(x1+theta,y1+theta,0.0);
		glVertex3f(x1+l*cos(DEG2RAD(theta)),y1+l*sin(DEG2RAD(theta)),0.0);
		glEnd();
		
	}
};

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len,int t);
void drawBall(float rad,int tem);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void drawRect(float l, float b);
void drawRectFill(float l, float b, float x, float y, int color);
void mouse_motion(int x,int y);


float ball_x = 0.0f;
float ball_y = 0.0f;
float ball_velx = 0.0f;
float ball_vely = 0.0f;
float ball_rad = 0.83f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 90.0f;
int ta=0;
int power=0;
int collide=0;
int colour_code;
float frict;
int count=0;
Coins strik;
Coins co[9];
int ll=0;
Line l;
int timer=0;
int ycord=1.0f;
int score=30;
int first=0;
int mycoin;
int temp;
int display=score;
int aa,bb;
int reset=0;
int collide_strik1=0,collide_strik2=0;
int collide_coin1[9],collide_coin2[9];
int coin_strik[9],coin_coin[9][9];
int coins_number=0;
int drag_flag;
int main(int argc, char **argv) 
{

strik.rad=0.23f;
strik.x=0.0f;
strik.y=-1.8f;
strik.vel_x=0.0f;
strik.vel_y=0.0f;
strik.sno=1;

l.x1=0.0f;
l.x2=0.0f;
l.y1=-1.8f;
l.y2=-1.9f;
l.lee=1.0;
l.theta=0.0f;
for(int i=0;i<9;i++)
{
	co[i].rad=0.16f;
	co[i].vel_x=0.0;
	co[i].vel_y=0.0;
	if(i<4)
		co[i].sno=1;
	else if(i<8)
		co[i].sno=2;
	else
		co[i].sno=3;
}

co[8].x=0.0f;
co[8].y=0.0f;
co[0].x=0.0f;
co[0].y=0.663f;
co[1].y=0.0f;
co[1].x=0.663f;
co[2].x=0.0f;
co[2].y=-0.663f;
co[3].y=0.0f;
co[3].x=-0.663f;
co[4].x=-0.45f;
co[4].y=0.5f;
co[5].x=-0.45f;
co[5].y=-0.5f;
co[6].x=0.45f;
co[6].y=-0.5f;
co[7].x=0.45f;
co[7].y=0.5f;

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("CARROM BOARD");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
     glutMotionFunc(mouse_motion);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
//	cout<<"Strrtop"<<" "<<l.x1<<" "<<l.y1<<" "<<l.lee<<" "<<l.theta<<"\n";
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    Board b;
    // Draw Boxes
    glColor3f(0.0f, 0.0f, 0.0f);
    b.drawBox(box_len,0,-6.0f);
    
    glColor3f(0.96f, 0.87f, 0.67f);
    b.drawBox(box_len,0,-1.0f);

    glColor3f(0.8f, 0.0f, 0.0f);
    b.drawBox(box_len,1,-3.0f);

    b.drawBall(ball_rad,0.0f,0.0f);
    Coins c;
    glColor3f(0.05f, 0.05f, 0.05f);
    c.rad=0.27f;
    //Draw holes
    c.drawBall(0.27f,-2.654f,2.654f);
    c.drawBall(0.27f,2.654f,2.654f);
    c.drawBall(0.27f,-2.654f,-2.654f);
    c.drawBall(0.27f,2.654f,-2.654f);
     glColor3f(0.8f, 0.0f, 0.0f);
    b.drawBall(0.15f,-1.87f,1.87f);
    b.drawBall(0.15f,-1.87f,-1.87f);
    b.drawBall(0.15f,1.87f,1.87f);
    b.drawBall(0.15f,1.87f,-1.87f);

    //Draw Coins

    //Draw Red coin
    glColor3f(1.0f,0.0f,0.0f);
    co[8].drawBall(0.16f,co[8].x,co[8].y);
    //Draw White coins
    glColor3f(1.0f,1.0f,1.0f);
    co[0].drawBall(0.16f,co[0].x,co[0].y);
    co[1].drawBall(0.16f,co[1].x,co[1].y);
    co[2].drawBall(0.16f,co[2].x,co[2].y);
    co[3].drawBall(0.16f,co[3].x,co[3].y);

    //Draw Black Coins
    glColor3f(0.0f,0.0f,0.0f);
    co[4].drawBall(0.16f,co[4].x,co[4].y);
    co[5].drawBall(0.16f,co[5].x,co[5].y);
    co[6].drawBall(0.16f,co[6].x,co[6].y);
    co[7].drawBall(0.16f,co[7].x,co[7].y);
  
    

    //Draw striker
     glColor3f(0.0f, 0.0f, 0.2f);
     strik.drawBall(0.23f,strik.x,strik.y);

    //Draw striker line
     // cout<<"Strr"<<" "<<l.x1<<" "<<l.y1<<" "<<l.lee<<" "<<l.theta<<"\n";
      l.drawLine(l.x1,l.y1,0.0,0.0,l.lee,l.theta);
      l.x2=l.lee*cos(DEG2RAD(l.theta));
      l.y2=l.lee*sin(DEG2RAD(l.theta));

      //Draw power
      glPushMatrix();
      glColor3f(1.0f, 1.0f, 0.0f);
      glTranslatef(5.0f, 0.0f, 0.0f);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glBegin(GL_QUADS);
      glVertex2f(-0.4 / 2, -6.2 / 2);
      glVertex2f(0.4 / 2, -6.2 / 2);
      glVertex2f(0.4 / 2, 6.2 / 2);
      glVertex2f(-0.4 / 2, 6.2 / 2);
      glEnd();
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	      glBegin(GL_QUADS);
	      if (power < 2) 
		      glColor3d(1.0f, 0, 0);
	      else if (power<4) 
		      glColor3d(1.0f, 0.5f, 0);
	      else  
		      glColor3d(0, 1.0f, 0);
	      glVertex2f(-0.15, -3.0);
	      glVertex2f(-0.15 + 0.3, -3.0);
	      glVertex2f(-0.15 + 0.3, -3.0 + power);
	      glVertex2f(-0.15, -3.0 + power);
	      glEnd();
      glPopMatrix();


    //Display Score
      aa=0;
      bb=0;
      display=score;
      void *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
      glColor3f(1.0f,1.0f,1.0f);           
      glRasterPos2f (-6.0f, 3.0f); 
      if (display < 0) 
      {
	      display  = display * -1;
	      glRasterPos2f ((-6.0f - (bb * 0.2)), 3.0f);    
	      glutBitmapCharacter(font_style, 48);
	      bb++;
      }
      while(display > 9)
      {
	      aa = display % 10;
	      glRasterPos2f ((-6.0f-(bb)*0.2),3.0f);   
	      glutBitmapCharacter(font_style,48+aa);
	      bb++;
	      display=display/10;
      }
      glRasterPos2f ((-6.0f-(bb)*0.2), 3.0f);   
      glutBitmapCharacter(font_style,48+display);
    glPopMatrix();
    glutSwapBuffers();
}
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
double t1;
double timer2;
void update(int value) { 
	if(score==0)
		exit(0);
	if(timer==0)
	{
	struct timeval tim;  
	gettimeofday(&tim, NULL);  
	 t1=(tim.tv_sec)/10000000;
	 timer2=t1;
//	 cout<<"Timer2"<<timer2<<"\n";
        timer=1;
	}
	else
	{
		t1=t1+0.01;
//		cout<<t1<<"\n";
	}
//	cout<<t1<<" "<<timer2<<"\n";
	if(t1-timer2>=1)
	{
		score=score-1;
		timer=0;
	//	cout<<score<<"\n";
	}
	
	// Handle striker collisions with walls;
	if((strik.x + strik.rad > 0.7*box_len || strik.x - strik.rad < -0.7*box_len) && collide_strik1==0)
	{
		strik.vel_x *= -1;
		collide_strik1=1;
	}
	else
		collide_strik1=0;
	if((strik.y + strik.rad > 0.7*box_len || strik.y - strik.rad < -0.7*box_len) && collide_strik2==0)
	{
		strik.vel_y *= -1;
		collide_strik2=1;
	}
	else
		collide_strik2=0;

	strik.x =strik.x+ strik.vel_x*0.1;
	strik.y=strik.y+ strik.vel_y*0.1;
        strik.vel_x=strik.vel_x*0.96;
	strik.vel_y=strik.vel_y*0.96;
        cout<<strik.x<<" "<<strik.y<<" "<<strik.vel_x<<" "<<strik.vel_y<<" "<<l.theta<<"\n";
	//Update striker position
	if(fabs(strik.vel_x)<0.05 &&  (fabs(strik.vel_y)) <0.05)
	{
	//	cout<<"Entered"<<"\n";
		strik.vel_x=0.0;
		strik.vel_y=0.0;
		if(reset==1)
		{ 
			reset=0;
			strik.x=0.0;
			strik.y=-1.8;
			l.theta=0;
			l.lee=1.0;
			l.x1=0.0;
			l.y1=-1.8;
			power=0;
			ll=0;

		//	strik.vel_x=0.0;

		}


	}
/*	else if(((((fabs(strik.vel_x))<0.05 || (fabs(strik.vel_y))<0.05))) && theta!=90)
	{
	//	if(temp!=90)
	//	{
		cout<<"2Entered"<<"\n";
		strik.vel_x=0.0;
		strik.vel_y=0.0;
		if(reset==1)
		{
			cout<<"Entered"<<"\n";
			reset=0;
			strik.x=0.0;
			strik.y=-1.8;
			l.theta=90;
			l.lee=1.0;
			l.x1=0.0;
			l.y1=-1.8;
//
		}
	  //     }
	}*/
/*	 if(temp==90)
	{
	//	cout<<"halou"<<strik.vel_y<<" "<<strik.y<<"\n";
		if(fabs(strik.vel_y) <0.00000005)
		{
			strik.vel_y=0.0;
	//		cout<<"Entered"<<" "<<strik.vel_y;
		}
			
	}*/
	

	//strik.x =strik.x+ strik.vel_x*0.1;
	//strik.y=strik.y+ strik.vel_y*0.1;
//	strik.vel_x=strik.vel_x*0.96;
//	strik.vel_y=strik.vel_y*0.96;
//	cout<<"22"<<" "<<strik.x<<" "<<strik.y<<"\n";

	//Handle coins collisions with walls
	for(int j=0;j<9;j++)
	{
		if((co[j].x + co[j].rad > 0.7*box_len || co[j].x - co[j].rad < -0.7*box_len) && collide_coin1[j]==0)
		{
			co[j].vel_x *= -1;
			collide_coin1[j]=1;
		}
		else
			collide_coin1[j]=0;
		if((co[j].y + co[j].rad > 0.7*box_len || co[j].y - co[j].rad < -0.7*box_len) && collide_coin2[j]==0)
		{
			co[j].vel_y *= -1;
			collide_coin2[j]=1;
		}
		else
			collide_coin2[j]=0;
		co[j].x =co[j].x + co[j].vel_x*0.1;
		co[j].y =co[j].y + co[j].vel_y*0.1;
	//	cout<<"Velocity "<<co[j].vel_x<<" "<<co[j].vel_y<<"\n";
		if((fabs(co[j].vel_x))<0.05 || (fabs(co[j].vel_y)) <0.05)
		{
			co[j].vel_x=0.0;
			co[j].vel_y=0.0;
		}
		//	co[j].x =co[j].x+ co[j].vel_x;
		//      co[j].y=co[j].y+ co[j].vel_y;
		co[j].vel_x=co[j].vel_x*0.96;
		co[j].vel_y=co[j].vel_y*0.96;

	//	cout<<"Position "<<j<<" "<<co[j].x<<" "<<co[j].y<<"\n";
}

 //Handle coin coin collisions

	for(int i=0;i<9;i++)
	{
		for(int j=i+1;j<9;j++)
		{
			float angle,u1_n,u1_t,u2_n,u2_t,v1,v2;
			if(((co[j].x - co[i].x)*(co[j].x - co[i].x)+(co[j].y - co[i].y)*(co[j].y - co[i].y))<=0.1024f && i!=j && coin_coin[i][j]==0)
			{
				angle=atan((co[j].y-co[i].y)/(co[j].x-co[i].x))*(180/PI);
				u1_n=co[i].vel_y*sin(DEG2RAD(angle))+co[i].vel_x*cos(DEG2RAD(angle));
				u2_n=co[j].vel_y*sin(DEG2RAD(angle))+co[j].vel_x*cos(DEG2RAD(angle));
				u1_t=co[i].vel_y*cos(DEG2RAD(angle))-co[i].vel_x*sin(DEG2RAD(angle));
				//              u2_n=co[j].vel_y*sin(DEG2RAD(re))+co[j].vel_x*cos(DEG2RAD(re));
				u2_t=co[j].vel_y*cos(DEG2RAD(angle))-co[j].vel_x*sin(DEG2RAD(angle));
				v1=u2_n;
				v2=u1_n;
				co[i].vel_y=u1_t*cos(DEG2RAD(angle))+v1*sin(DEG2RAD(angle));
				co[i].vel_x=v1*cos(DEG2RAD(angle))-u1_t*sin(DEG2RAD(angle));
				co[j].vel_y=u2_t*cos(DEG2RAD(angle))+v2*sin(DEG2RAD(angle));
				co[j].vel_x=v2*cos(DEG2RAD(angle))-u2_t*sin(DEG2RAD(angle));
				coin_coin[i][j]=1;
			}
			else 
				coin_coin[i][j]=0;
		}
	}


	//Handle striker coins collisions

	for(int j=0;j<9;j++)
	{
		float angle,u1_n,u1_t,u2_n,u2_t,v1,v2;
		if(((co[j].x - strik.x)*(co[j].x - strik.x)+(co[j].y - strik.y)*(co[j].y - strik.y))<=0.1521f && coin_strik[j]==0)
		{
			angle=atan((co[j].y-strik.y)/(co[j].x-strik.x))*(180/PI);
			u1_n=strik.vel_y*sin(DEG2RAD(angle))+strik.vel_x*cos(DEG2RAD(angle));
			u2_n=co[j].vel_y*sin(DEG2RAD(angle))+co[j].vel_x*cos(DEG2RAD(angle));
			u1_t=strik.vel_y*cos(DEG2RAD(angle))-strik.vel_x*sin(DEG2RAD(angle));            
			u2_t=co[j].vel_y*cos(DEG2RAD(angle))-co[j].vel_x*sin(DEG2RAD(angle));
			v1=(u1_n+2*u2_n)/3.0f;//Formula
			v2=(4*u1_n-u2_n)/3.0f;//Formula
			strik.vel_y=(u1_t*cos(DEG2RAD(angle))+v1*sin(DEG2RAD(angle)));        //Resultant velocity of striker   
			strik.vel_x=(v1*cos(DEG2RAD(angle))-u1_t*sin(DEG2RAD(angle)));            
			co[j].vel_y=(u2_t*cos(DEG2RAD(angle))+v2*sin(DEG2RAD(angle)));           //Resultant velocity of coin
			co[j].vel_x=(v2*cos(DEG2RAD(angle))-u2_t*sin(DEG2RAD(angle)));
			coin_strik[j]=1;
	//		cout<<j<<" "<<strik.vel_y<<" "<<strik.vel_x<<" "<<co[j].vel_y<<" "<<co[j].vel_x<<"\n";
		}
		else
			coin_strik[j]=0;

	}

        //Coin into the holes

        for(int j=0;j<9;j++)
{

	if((co[j].x-2.654f)*(co[j].x-2.654f)+(co[j].y-2.654f)*(co[j].y-2.654f)<=0.1849f || (co[j].x+2.654f)*(co[j].x+2.654f)+(co[j].y-2.654f)*(co[j].y-2.654f)<=0.1849f || (co[j].x-2.654f)*(co[j].x-2.654f)+(co[j].y+2.654f)*(co[j].y+2.654f)<=0.1849f || (co[j].x+2.654f)*(co[j].x+2.654f)+(co[j].y+2.654f)*(co[j].y+2.654f)<=0.1849f )
          {
		  co[j].vel_x=0.0;
		  co[j].vel_y=0.0;
		  if(ycord<-3.0)
		  {
			  co[j].x=-5.0;
		          ycord=1.0f;
		  }
		  else
		  co[j].x=-6.0f;
		  co[j].y=ycord;
		  ycord=ycord-2.0;
		  if(first==0)
		  {
			  if(co[j].sno!=3)
			  {
			  mycoin=co[j].sno;
			  first=1;
			  }
			  if(co[j].sno==3)
			  {
			  score=score+50;
			  coins_number++;
			  }
			  if(co[j].sno==1 || co[j].sno==2)
			  {
		           score=score+10;
			   coins_number++;
			  }
		  }
		  else
		  {
			  if(co[j].sno==mycoin)
			  {
				  score=score+10;
				  coins_number++;
			  }
			  else if(co[j].sno==3)
			  {
				  score=score+50;
				  coins_number++;
			  }
			  else
				  score=score-5;

		  }
	  }
}
	 if((strik.x-2.654f)*(strik.x-2.654f)+(strik.y-2.654f)*(strik.y-2.654f)<=0.25f || (strik.x+2.654f)*(strik.x+2.654f)+(strik.y-2.654f)*(strik.y-2.654f)<=0.25f || (strik.x-2.654f)*(strik.x-2.654f)+(strik.y+2.654f)*(strik.y+2.654f)<=0.25f || (strik.x+2.654f)*(strik.x+2.654f)+(strik.y+2.654f)*(strik.y+2.654f)<=0.25f)
          {
		 strik.x=0.0;
		  strik.y=-1.8;
		  strik.vel_x=0.0;
		  strik.vel_y=0.0;
		  score=score-5;
	  }
count=0;
  /*       for(int j=0;j<9;j++)
{
	if(co[j].vel_x==0.0 && co[j].vel_y==0.0)
	{
		 count++;
//		cout<<j<<" "<<count;
	}
}
        if(count==9)
{
	count=0;
//	cout<<"ME IN"<<"\n";
	if(strik.vel_x==0.0 && strik.vel_y==0.0)
	{
		if(strik.x!=0.0 || strik.y!=-1.8)
		{
		strik.x=0.0;
		strik.y=-1.8;
		power=0;
		l.x1=0.0f;
//		l.x2=0.0f;
		l.y1=-1.8f;
//		l.y2=-1.9f;
		l.lee=1.0;
		l.theta=45.0f;
		}

	}*/
//	cout<<"Heredown"<<" "<<strik.x<<" "<<strik.y<<"\n";
//}
        if(coins_number==5)
{
	exit(0);
/*	co[8].x=0.0f;
	co[8].y=0.0f;
	co[0].x=0.0f;
	co[0].y=0.663f;
	co[1].y=0.0f;
	co[1].x=0.663f;
	co[2].x=0.0f;
	co[2].y=-0.663f;
	co[3].y=0.0f;
	co[3].x=-0.663f;
	co[4].x=-0.45f;
	co[4].y=0.5f;
	co[5].x=-0.45f;
	co[5].y=-0.5f;
	co[6].x=0.45f;
	co[6].y=-0.5f;
	co[7].x=0.45f;
	co[7].y=0.5f;*/

}
	glutTimerFunc(10, update, 0);
}
// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.2f, 0.0f, 0.0f, 0.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

  if (key == 27) {
        exit(0);     // escape key is pressed
    }
  else if(key == 32)
    {
//	      glutTimerFunc(10, update, 0);
	    strik.vel_x=l.x2;
	    strik.vel_y=l.y2;
	    strik.x=strik.x+strik.vel_x*0.1;
	    strik.y=strik.y+strik.vel_y*0.1;
	    l.lee=0.0;
	    l.x1=0.0;
	    l.y1=0.0;
	    l.theta=0;
	    ll=1;
	    reset=1;
    }
    else if(key=='a' || key=='A')
    {
	    l.theta += 5;
//	    cout<<l.theta<<" "<<l.x1<<" "<<l.y1<<" "<<l.lee;
//	    cout<<strik.x<<" "<<strik.y<<" "<<l.theta<<"\n";
	  //  ta=2;
    }
    else if(key=='c' || key=='C')
    {
	    
	    l.theta -=5;
	   // ta=2;
    }
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
    {

	    strik.x-=0.1;
	    if(strik.x<-2.0)
	    {
		    strik.x+=0.1;
	    }
	    else
	    {
	    strik.drawBall(0.23f,strik.x,strik.y);
	    }
	    l.x1 -=0.1;
	    l.x2 -=0.1;
	    if(l.x1<-2.0)
	    {
		    l.x1+=0.1;
		    l.x2+=0.1;
	    }
	    else
	    {
	    l.drawLine(l.x1,l.y1,l.x2,l.y2,l.lee,theta);
	    l.x2=l.x1+l.lee*cos(DEG2RAD(theta));
	    l.y2=l.x2+l.lee*sin(DEG2RAD(theta));

	    }
	 
    }
    if (key == GLUT_KEY_RIGHT)
    {
	    strik.x+=0.1;
	    if(strik.x>2.0)
	    {       
		            strik.x-=0.1;
	    }
	    else
	    {       
		    strik.drawBall(0.23f,strik.x,strik.y);
	    }
	    l.x1 +=0.1;
	    l.x2 +=0.1;
	    if(l.x1>2.0)
	    {       
		            l.x1-=0.1;
			    l.x2-=0.1;
	    }       
	    else
	    {       
		    l.drawLine(l.x1,l.y1,l.x2,l.y2,l.lee,theta);
	            l.x2=l.x1+l.lee*cos(DEG2RAD(theta));
		    l.y2=l.x2+l.lee*sin(DEG2RAD(theta));

	    }

    }
    if (key == GLUT_KEY_UP)
    {
	    if(power<6)
	    {
	    power=power+1;
	    l.lee=l.lee+0.5;
	    }
//	    cout<<power<<endl;
    }
    if (key == GLUT_KEY_DOWN)
     {
	     if(power>0)
	     {
		     power=power-1;
		     l.lee=l.lee-0.5;
	     }
//	     cout<<power<<endl;

     }
}

void handleMouseclick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN)
	{
		if(button == GLUT_RIGHT_BUTTON) {
			drag_flag = 1;
		}

		if(button == GLUT_LEFT_BUTTON)
		{
			if (ll == 0) {
				int ww = glutGet(GLUT_WINDOW_WIDTH);
				int wh = glutGet(GLUT_WINDOW_HEIGHT);
				float hw = (float)ww/2;
				float hh = (float)wh/2;
				float xx = ((float)x - hw)/hw * 5;
				float yy = ((float)y - hh)/-hh * 5;
                          //      cout<<xx<<" "<<yy<<" "<<strik.x<<" "<<strik.y<<"\n";
				float dist = sqrt((xx - strik.x) * (xx - strik.x) + (yy - strik.y) * (yy - strik.y));
				l.theta= atan2((xx - strik.x) , (yy - strik.y)) ;
				strik.vel_x = 10 * dist / 8;
				strik.vel_y = 10 * dist / 8;
			//	cout << dist << endl;
			}
		}
	}

	if(state == GLUT_UP)
	{
		if(button == GLUT_LEFT_BUTTON)
		{
			if (ll == 0) {
			//	cout << l.theta<< endl;
				strik.vel_x = strik.vel_x * cos(DEG2RAD(l.theta));
				strik.vel_y = strik.vel_y * sin(DEG2RAD(l.theta));
				ll = 1;
				reset = 1;
			}
		}

		if(button == GLUT_RIGHT_BUTTON)
		{
			drag_flag = 0;
		}
	}
}


void mouse_motion(int x,int y)
{

	int width = glutGet(GLUT_WINDOW_WIDTH);
	float offset = 2 * ((float)x - (width / 2))/width;
	if(drag_flag && (strik.x + 0.5 < (0.6*box_len - 2*0.27))  && (strik.x - 0.5 > (-1 * (0.6*box_len - 2*0.27))))
	{
		cout<<"Entered"<<"\n";
		strik.x = offset * 10; 
		l.lee=0;
		l.theta=0.0;
		l.x1=0;
		l.y1=0;
	}

	if (drag_flag && (strik.x + 0.5 >= (0.6*box_len - 2*0.27)) && offset < (((0.6*box_len - 2*0.27)) / 10))
	{
		 l.lee=0;
		  l.theta=0.0;
		   l.x1=0;
		    l.y1=0;

		strik.x = offset * 10;
	}

	if (drag_flag && (strik.x - 0.5 <= (-1 * (0.6*box_len - 2*0.27))) && offset > (-1 * (0.6*box_len - 2*0.27 )) / 10)
	{
		 l.lee=0;
		  l.theta=0.0;
		   l.x1=0;
		    l.y1=0;

		strik.x = offset * 10;
	}

	if (strik.x + 0.5 >= (0.6*box_len - 2*0.27))
	{
		 l.lee=0;
		  l.theta=0.0;
		   l.x1=0;
		    l.y1=0;

		strik.x = 0.6*box_len - 2*0.27;
	}
	if (strik.x - 0.5 <= (-1 * (0.6*box_len - 2*0.27 )))
	{
		 l.lee=0;
		  l.theta=0.0;
		   l.x1=0;
		    l.y1=0;

		strik.x = -1 * (0.6*box_len - 2*0.27);
}
}
	
