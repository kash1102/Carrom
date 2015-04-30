










#include<sys/time.h>
#include<stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void printscore(int k,float a, float b);
void Resetstiger();
void drawScene();
void update(int value);
void drawBox(float len);
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius);
void drag(int x, int y);
void scoreupdate(int val);
//void drawBBox(float len);
void drawBall(float rad);
void fill();
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

struct timeval tim;
double t1;
int time_;
int oldtime;

// Global Variables
float fric = 0.00002f;
float  s_y =  -2.0f + .17f;
float s_x = 0.0f;
float hole_rad = 0.2f;
float ihole_rad = 0.14f;
float box_len = 5.5f;
float bbox_len = 6.0f;
float ibox_len = 4.0f;



float ball_rad = 0.2f;

float iball_rad = 0.14f;
float stiger_rad = 0.16f;
float iball_value = 0.56f; // value to be rememberd

//float ball_rad = 0.2f

float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
int flag=0;
float c = 0.0f;
float s = 0.0f;
float co = 0.0f;
float si = 0.0f;
float line_x = 0.0f;
float line_y = 0.0f;
float draw = 0.14f;

int angle = 90;

int flag1=0;

int flag2=0; //stiger flag
int flag3=0;

int sca=30 ;
int scb ;
int oldx = 0;
int oldy = 0;


class Shapes
{

	public:

		void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
			int i;
			int lineAmount = 100; //# of triangles used to draw circle
			//GLfloat radius = 0.8f; //radius
			GLfloat twicePi = 2.0f * PI;
			glBegin(GL_LINE_LOOP);
			for(i = 0; i <= lineAmount;i++) {
				glVertex2f(
						x + (radius * cos(i * twicePi / lineAmount)),
						y + (radius* sin(i * twicePi / lineAmount))
					  );
			}
			glEnd();
		}

		void drawBox(float len) {


			if( len==4.0f)

				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glBegin(GL_QUADS);


			glVertex2f(-len / 2, -len / 2);
			glVertex2f(len / 2, -len / 2);
			glVertex2f(len / 2, len / 2);
			glVertex2f(-len / 2, len / 2);
			glEnd();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		void drawBall(float rad) {

			// glTriangleMode(GL_FRONT_AND_BACK, GL_LINE);

			glBegin(GL_TRIANGLE_FAN);
			for(int i=0 ; i<360 ; i++) {
				glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
			}       
			glEnd();
		}



		void drawLine(float x, float y, float x1, float y1){
			glBegin(GL_LINES);
			glVertex2f(x,y);
			glVertex2f(x1,y1);
			glEnd();

		}   





};




class Coin
{
	public:
		float x;
		float y;
		float vel_x;
		float vel_y;
		float rad;
		int fl;
		char c;

	public:

		void drawcoin(float x, float y, float rad, char c)
		{
			Shapes(a);
			glPushMatrix();
			glTranslatef(x ,y,0.0f);
			if(c=='r')
				glColor3f(1.0f,0.0f,0.0f);
			else if(c=='w')
				glColor3f(0.000, 0.749, 1.000);
			else if(c=='b')
				glColor3f(0.663, 0.663, 0.663);

			a.drawBall(rad);
			glPopMatrix();
		}










};



// array filling
Coin coins[10],stiger[1],holes[4];










int main(int argc, char **argv) {


           

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        gettimeofday(&tim,NULL);
	              t1 = tim.tv_sec+(tim.tv_usec/1000000.0);
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);    
//	sca = sca -10;
  //       printf("%d",sca);
	// glutInitWindowSize(1000,1000);
	// glutInitWindowPosition(100,100);
       // gettimeofday(&tim,NULL);
	 //   t1 = tim.tv_sec+(tim.tv_usec/1000000.0);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(drag);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutTimerFunc(1000, scoreupdate, 0);


	glutMainLoop();

	return 0;
}

// Function to draw objects on the screen
void drawScene() {

	Shapes(a);



         int ini_time = 0;
	 gettimeofday(&tim,NULL);
	 double t2 = tim.tv_sec+(tim.tv_usec/1000000.0);
	 time_ = int(t2 -t1);
	// glClearColor(0.8f, 0.7f, 0.5f,0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	// Draw Box
	//glTranslatef(0.0f, 0.0f, -8.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//drawBox(box_len);

	// Draw BBox
	glTranslatef(0.0f, 0.0f, -8.0f);
	glColor3f(0.871, 0.722, 0.529);
	a.drawBox(bbox_len);

	// Draw Box
	//glTranslatef(0.0f, 0.0f, -0.0f);
	glColor3f(0.992, 0.961, 0.902);
	a.drawBox(box_len);
	// Draw inner box
	glColor3f(0.502, 0.000, 0.000);
	a.drawBox(ibox_len);





	// Draw holes
	glPushMatrix();
	glTranslatef(-box_len/2 + hole_rad - 0.05f , box_len/2 - hole_rad + 0.05f , 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	a.drawBall(hole_rad);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(+box_len/2 - hole_rad + 0.05f , box_len/2 - hole_rad + 0.05f , 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	a.drawBall(hole_rad);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-box_len/2 + hole_rad - 0.05f ,  -box_len/2 + hole_rad - 0.05f , 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	a.drawBall(hole_rad);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(+box_len/2 - hole_rad + 0.05f , -box_len/2 + hole_rad - 0.05f , 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	a.drawBall(hole_rad);
	glPopMatrix();



	// Draw inner holes

	glPushMatrix();
	glTranslatef(-ibox_len/2 + ihole_rad - 0.05f , ibox_len/2 - ihole_rad + 0.05f , 0.0f);
	glColor3f(0.502, 0.000, 0.000);
	a.drawBall(ihole_rad);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(+ibox_len/2 - ihole_rad + 0.05f , ibox_len/2 - ihole_rad + 0.05f , 0.0f);
	glColor3f(0.502, 0.000, 0.000);
	a.drawBall(ihole_rad);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(-ibox_len/2 + ihole_rad - 0.05f ,  -ibox_len/2 + ihole_rad - 0.05f , 0.0f);
	glColor3f(0.502, 0.000, 0.000);
	a.drawBall(ihole_rad);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(+ibox_len/2 - ihole_rad + 0.05f , -ibox_len/2 + ihole_rad - 0.05f , 0.0f);
	glColor3f(0.502, 0.000, 0.000);
	a.drawBall(ihole_rad);
	glPopMatrix();


	//Draw inner balls

	if(flag == 0)
	{
		coins[0].x=iball_value;
		coins[0].y=0.0f;
		coins[0].vel_x=0.0f;
		coins[0].vel_y=0.0f;
		coins[0].fl = 0;
		coins[0].c = 'w';



		coins[1].x=-iball_value;
		coins[1].y=0.0f;
		coins[1].vel_x=0.00f;
		coins[1].vel_y=0.00f;
		coins[1].fl = 0;
		coins[1].c = 'w';



		coins[2].x=0.0f;
		coins[2].y=-iball_value;
		coins[2].vel_x=0.0f;
		coins[2].vel_y=0.0f;
		coins[2].fl = 0;
		coins[2].c = 'w';



		coins[3].x=0.0f;
		coins[3].y=iball_value;
		coins[3].vel_x=0.0f;
		coins[3].vel_y=0.0f;
		coins[3].fl = 0;
		coins[3].c = 'w';



		coins[4].x=0.0f;
		coins[4].y=0.0f;
		coins[4].vel_x=0.0f;
		coins[4].vel_y=0.0f;
		coins[4].fl = 0;
		coins[4].c = 'r';



		coins[5].x=-0.7f/sqrt(2) + .14f/sqrt(2);
		coins[5].y=0.7f/sqrt(2) - .14f/sqrt(2);
		coins[5].vel_x=0.0f;
		coins[5].vel_y=0.0f;
		coins[5].fl = 0;
		coins[5].c = 'b';



		coins[6].x=-0.7f/sqrt(2) + .14f/sqrt(2);
		coins[6].y=-0.7f/sqrt(2) + .14f/sqrt(2);
		coins[6].vel_x=0.0f;
		coins[6].vel_y=0.0f;
		coins[6].fl = 0;
		coins[6].c = 'b';


		coins[7].x=0.7f/sqrt(2) - .14f/sqrt(2);
		coins[7].y=0.7f/sqrt(2) - .14f/sqrt(2);
		coins[7].vel_x=0.0f;
		coins[7].vel_y=0.0f;
		coins[7].fl = 0;
		coins[7].c = 'b';


		coins[8].x=0.7f/sqrt(2) - .14f/sqrt(2);
		coins[8].y=-0.7f/sqrt(2) + .14f/sqrt(2);
		coins[8].vel_x=0.0f;
		coins[8].vel_y=0.0f;
		coins[8].fl = 0;
		coins[8].c = 'b';




		stiger[0].x = s_x; 
		stiger[0].y = s_y;
		stiger[0].vel_x = 0.0f;
		stiger[0].vel_y = 0.0f;

		holes[0].x = -box_len/2 + hole_rad - 0.05f;
		holes[0].y = box_len/2 - hole_rad + 0.05f;
		holes[1].x = box_len/2 - hole_rad + 0.05f;
		holes[1].y = box_len/2 - hole_rad + 0.05f;
		holes[2].x = -box_len/2 + hole_rad - 0.05f;
		holes[2].y = -box_len/2 + hole_rad - 0.05f;
		holes[3].x = box_len/2 - hole_rad + 0.05f;
		holes[3].y = -box_len/2 + hole_rad - 0.05f;

		sca = 30;


		flag=1;

	}


	int i;
	Coin b;
	for(i=0;i<=8;i++)
	{


		if(i==4 )
			b.drawcoin(coins[i].x ,coins[i].y,iball_rad,'r');
		else if(i <=3) 
			b.drawcoin(coins[i].x,coins[i].y,iball_rad,'w');
		else if( i > 4)
			b.drawcoin(coins[i].x,coins[i].y,iball_rad,'b');





	}




	// Draw stiger

	glPushMatrix();
	glTranslatef(stiger[0].x,stiger[0].y ,0.0f);
	glColor3f(0.502, 0.000, 0.502);
	a.drawBall(stiger_rad);
	glPopMatrix();

	// Draw hollow circle

	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);
	glColor3f(0.502, 0.000, 0.000);
	a.drawHollowCircle(0.0f, 0.0f, 0.7f);
	glPopMatrix();

	// Draw line
	glPushMatrix();
	glTranslatef(stiger[0].x,stiger[0].y,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
	a.drawLine(0.0f,0.0f,line_x,line_y);
	glPopMatrix();













	// Draw font
	
	if(sca < 0)
	{
	 glColor3f(0.0, 1.0, 0.0); // Green
	           glRasterPos3f(-5.1f, 0.0f,0.0f);
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;
	glutBitmapCharacter(font,'-');
	}
	printscore(sca,-5.0f,0.0f);
	//printscore(scb,5.0f,0.0f);





	glPopMatrix();

	glutSwapBuffers();







}

void printscore(int k, float b , float c)
{



       int n;
       n = k;

	string temp="";
	string returnvalue="";
	if (n == 0)
		returnvalue = "0";
	if(n<0)n*=-1;
	while (n>0)
	{
		temp+=n%10+48;
		n/=10;
	}
	for (int i=0;i<temp.length();i++)
		returnvalue+=temp[temp.length()-i-1];





	glColor3f(0.0, 1.0, 0.0); // Green
	glRasterPos3f(b, c,0.0f);

	string s = returnvalue;
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}	  




void perfect_hit()
{

	int i,j,p;

	for(i=0;i<=8;i++)
	{
		for(j=0;j<4;j++)
		{
			if(sqrt( (coins[i].x - holes[j].x)*(coins[i].x - holes[j].x) + (coins[i].y - holes[j].y)*(coins[i].y - holes[j].y)) <= iball_rad)
			{
				if(s_y < 0 )
				{
					coins[i].x = -2.0f + draw;
					coins[i].y = s_y - 1.05f ;
					//printf("%c  ",coins[i].c);
					if(i > 4)
					sca = sca + 10;
					else if(i <= 3)
					sca = sca - 10;
					else if(i == 4)
					sca = sca +50;

					//printf("%d",sca);
				}
				if(s_y > 0 )
				{
					coins[i].x = -2.0f + draw;
					coins[i].y = s_y +1.05f ;
				}
				if(s_x < 0)
				{
					coins[i].x = s_x - 1.05f;
					coins[i].y = -2.0f + draw ;
				}
				if(s_x > 0)
				{
					coins[i].x = s_x + 1.05f;
					coins[i].y = -2.0f + draw;
				}
				coins[i].fl = 1;
				coins[i].vel_x = 0;
				coins[i].vel_y = 0;
				draw = draw + 2*iball_rad;
				

				//printf("%g %g", coins[i].x, coins[i].y);

			}
		}

	}

	for(p=0;p<4;p++)
	{
	if(sqrt((holes[p].x - stiger[0].x)*(holes[p].x - stiger[0].x) + (holes[p].y - stiger[0].y)*(holes[p].y - stiger[0].y)) <= hole_rad  && flag3 == 0)
	{
	 
	 sca = sca - 10;
	 stiger[0].x = holes[p].x;
	 stiger[0].y = holes[p].y;
	 flag3=1;
	 }
	 }
	 


}
void friction(float &v_x, float &v_y)
{

	float total;
	total = sqrt(v_x*v_x + v_y*v_y);

	if(total < 0.0001)
	{
		v_x= 0.0f;
		v_y = 0.0f;
	}
	else
	{
		v_x = v_x - (fric*9.8*v_x)/total;
		v_y = v_y - (fric*9.8*v_y)/total;
	}

}



// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {





	// Handle ball collisions with box


	if(stiger[0].x + stiger_rad >box_len/2 || stiger[0].x - stiger_rad < -box_len/2)
		stiger[0].vel_x *= -1;

	if(stiger[0].y + stiger_rad > box_len/2 || stiger[0].y - stiger_rad < -box_len/2)
		stiger[0].vel_y *= -1;


	if(flag1 == 1)
	{
		stiger[0].x += stiger[0].vel_x;
		stiger[0].y += stiger[0].vel_y;
	}





	// Handle coins collisions with box



	int jhanda[9]={0};
	int m;
	for(m=0;m<=8;m++)
	{
		if(coins[m].fl == 0)
		{
			if(coins[m].x + iball_rad >= box_len/2.0 || coins[m].x - iball_rad <= -box_len/2.0  )
			{
				coins[m].vel_x *= -1;
				jhanda[m]=1;
				//coins[m].x += coins[m].vel_x;
			}

			if(coins[m].y + iball_rad >= box_len/2.0 || coins[m].y - iball_rad <= -box_len/2.0)
			{
				coins[m].vel_y *= -1;
				jhanda[m]=2;
				//	printf("Punjani %f\n",coins[m].vel_y);
				//coins[m].y = coins[m].vel_y;
			}
		}
		//printf("Yo1 %f\n",coins[m].vel_y );
	}
	//printf("Yo2 %f\n",coins[0].vel_y );

	for(m=0;m<=8;m++)
	{
		coins[m].x += coins[m].vel_x;
		//printf("Yo3 %f\n",coins[m].vel_y );
		if(jhanda[m]==1)
		{
			jhanda[m]=0;
			while(coins[m].x + iball_rad >= box_len/2.0 || coins[m].x - iball_rad <= -box_len/2.0 )
			{
				coins[m].x += coins[m].vel_x;
			}
		}
		coins[m].y += coins[m].vel_y;
		//printf("Yo4 %f\n",coins[m].vel_y );
		if(jhanda[m]==2)
		{
			jhanda[m]=0;
			//printf("Hello %f\n",coins[m].vel_y );
			while(coins[m].y + iball_rad >= box_len/2.0 || coins[m].y - iball_rad <= -box_len/2.0)
				coins[m].y += coins[m].vel_y;
		}
	}


	// stiger collision with coin

	for(m=0;m<=8;m++)
	{
		if(coins[m].fl == 0)
		{
			if(sqrt((coins[m].x - stiger[0].x)*(coins[m].x - stiger[0].x) + (coins[m].y - stiger[0].y)*(coins[m].y - stiger[0].y)) <= iball_rad + stiger_rad)
			{
				c = (coins[m].x - stiger[0].x)/sqrt((coins[m].x - stiger[0].x)*(coins[m].x - stiger[0].x) + (coins[m].y - stiger[0].y)*(coins[m].y - stiger[0].y));

				s = (coins[m].y - stiger[0].y)/sqrt((coins[m].x - stiger[0].x)*(coins[m].x - stiger[0].x) + (coins[m].y - stiger[0].y)*(coins[m].y - stiger[0].y));


				float tex=coins[m].vel_x;
				float tey=coins[m].vel_y;
				float tex1=stiger[0].vel_x;


				coins[m].vel_x =  (stiger[0].vel_x*c + stiger[0].vel_y*s)*c - (coins[m].vel_y*c - coins[m].vel_x*s)*s;
				coins[m].vel_y =  (stiger[0].vel_x*c + stiger[0].vel_y*s)*s + (coins[m].vel_y*c - tex*s)*c;
				stiger[0].vel_x = (tex*c +tey*s)*c - (stiger[0].vel_y*c - stiger[0].vel_x*s)*s;
				stiger[0].vel_y = (tex*c + tey*s)*s + (stiger[0].vel_y*c - tex1*s)*c;

				stiger[0].x += stiger[0].vel_x;
				stiger[0].y += stiger[0].vel_y;
				coins[m].x += coins[m].vel_x;
				coins[m].y += coins[m].vel_y;

			}
		}
	}


	int i,j;
	for(i=0;i<=8;i++)
	{
		if(coins[i].fl == 0)
		{
			for(j=i+1;j<=8;j++)
			{
				if(coins[j].fl == 0)
				{


					if(sqrt((coins[i].x - coins[j].x)*(coins[i].x - coins[j].x) + (coins[i].y - coins[j].y)*(coins[i].y - coins[j].y)) <= 2*iball_rad)
					{
						co = (coins[i].x - coins[j].x)/sqrt((coins[i].y - coins[j].y)*(coins[i].y - coins[j].y) + (coins[i].x - coins[j].x)*(coins[i].x - coins[j].x));

						si = (coins[i].y - coins[j].y)/sqrt((coins[i].y - coins[j].y)*(coins[i].y - coins[j].y) + (coins[i].x - coins[j].x)*(coins[i].x     - coins[j].x));

						float temx=coins[i].vel_x;
						float temy=coins[i].vel_y;
						float temx1=coins[j].vel_x;


						coins[i].vel_x = (coins[j].vel_x*co + coins[j].vel_y*si)*co - (coins[i].vel_y*co - coins[i].vel_x*si)*si;
						coins[i].vel_y = (coins[j].vel_x*co + coins[j].vel_y*si)*si + (coins[i].vel_y*co - temx*si)*co;

						coins[j].vel_x = (temx*co + temy*si)*co - (coins[j].vel_y*co - coins[j].vel_x*si)*si;
						coins[j].vel_y = (temx*co + temy*si)*si + (coins[j].vel_y*co - temx1*si)*co;




						coins[i].x += coins[i].vel_x;
						coins[i].y += coins[i].vel_y;
						coins[j].x += coins[j].vel_x;
						coins[j].y += coins[j].vel_y;
						//glutTimerFunc(10, update, 0);


					}

					/* coins[i].x += coins[i].vel_x;
					   coins[i].y += coins[i].vel_y;
					   coins[j].x += coins[j].vel_x;
					   coins[j].y += coins[j].vel_y;*/





				}

			}

		}
	}




	//friction



	if(flag1==1)
	{
		for(m=0;m<=8;m++)

			friction(coins[m].vel_x,coins[m].vel_y);
		friction(stiger[0].vel_x,stiger[0].vel_y); 

	}

	if(flag1==1)
		perfect_hit();



	if(flag1==1)
		Resetstiger();

       
	 printscore(sca,-5.0f,0.0f);
	 //printscore(S_B,5.0f,0.0f);
       







	glutTimerFunc(10, update, 0);




}


void scoreupdate(int val)
{

if(oldtime +1 == time_)
sca = sca - 1;
 glutTimerFunc(1000, scoreupdate, 0);
 oldtime = time_;
// printf("%d ",time_);

}










void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
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

void Resetstiger(){


	if(flag1==1)
	{
		int f = 0,m;
		for(m=0;m<=8;m++)
		{
			if(sqrt(coins[m].vel_x*coins[m].vel_x + coins[m].vel_y*coins[m].vel_y) < 0.0001 )
			{

				f++;
			}
		}
		if(f==9)
		{

			if(sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y) < 0.0001  )
			{

				stiger[0].x = s_x;
				stiger[0].y = s_y;
			       	/*s_x = stiger[0].x;
				s_y = stiger[0].y;*/
				flag1=0;
				if(s_y > 0 )
				angle = 270;
				if(s_y < 0)
				angle = 90;
				if(s_x > 0 )
				angle = 180;
				if(s_x < 0)
				angle = 0;
			}
		}
	}

}
void handleKeypress1(unsigned char key, int x, int y) {


	float dis,total;

	if (key == 27) 
		exit(0);     // escape key is pressed


	if (key == 'a' && flag1==0 ) 
	{

		dis = sqrt(line_x*line_x + line_y*line_y);
		total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);

		angle=angle+1;

		line_x = dis*cos((3.142*angle)/180);
		line_y = dis*sin((3.142*angle)/180);
		stiger[0].vel_x = total*cos((3.142*angle)/180);
		stiger[0].vel_y = total*sin((3.142*angle)/180);

	}

	if(key == 'c' && flag1==0)
	{
		dis = sqrt(line_x*line_x + line_y*line_y);
		total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);



		angle=angle-1;

		line_x = dis*cos((3.142*angle)/180);
		line_y = dis*sin((3.142*angle)/180);
		stiger[0].vel_x = total*cos((3.142*angle)/180);
		stiger[0].vel_y = total*sin((3.142*angle)/180);



	}
	if(key == 32 && flag1==0)
	{
	             
                total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);

		stiger[0].x += stiger[0].vel_x*cos((3.142*angle)/180);
		stiger[0].y += stiger[0].vel_y*sin((3.142*angle)/180);
		flag1=1;
		line_x = 0.0f;
		line_y = 0.0f;
		
	}





}

void handleKeypress2(int key, int x, int y) {

	float total,total2;

	if (key == GLUT_KEY_LEFT  && flag1==0)
	{
		tri_x -= 0.1;
		if(s_x ==0 && stiger[0].x >= -2.0f + stiger_rad)
			stiger[0].x -= 0.05f;
		else if(s_y == 0 && (stiger[0].y) >= -2.0f + stiger_rad)
			stiger[0].y -= 0.05f;
	}
	if (key == GLUT_KEY_RIGHT && flag1==0 )
	{
		tri_x += 0.1;
		if(s_x == 0 && (stiger[0].x) <= 2.0f - stiger_rad )
			stiger[0].x += 0.05f;
		else if(s_y == 0 && (stiger[0].y) <= 2.0f - stiger_rad)
			stiger[0].y += 0.05f;
	}
	if (key == GLUT_KEY_UP && flag1==0)
	{
		total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);
		total += 0.05;
		total2 = sqrt(line_x*line_x + line_y*line_y);
		total2 += 0.05;

		line_x = total2*cos((angle*3.142)/180);

		line_y = total2*sin((angle*3.142)/180);

		stiger[0].vel_x = total*cos((angle*3.142)/180);
		stiger[0].vel_y = total*sin((angle*3.142)/180);
		tri_y += 0.1;
	}

	if (key == GLUT_KEY_DOWN && flag1==0)
	{ 
		total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);
		total -= 0.05f;

		total2 = sqrt(line_x*line_x + line_y*line_y);
		total2 -= 0.05f;

		line_x = total2*cos((angle*3.142)/180);
		line_y = total2*sin((angle*3.142)/180);


		stiger[0].vel_x = total*cos((angle*3.142)/180);

		stiger[0].vel_y = total*sin((angle*3.142)/180);
		tri_y -= 0.1;
	}
}

void handleMouseclick(int button, int state, int x, int y) {
         
	 float x1, y1,t,cosa,sina,k,total,total2,tempx;
	if (state == GLUT_DOWN && flag1==0)

	{
		if (button == GLUT_LEFT_BUTTON)
		{  
		       x1 = (x - 652)/112;
		       y1 = (y - 370)/-112;
		       t = sqrt((x1 - stiger[0].x)*(x1 - stiger[0].x) + (y1 - stiger[0].y)*(y1 - stiger[0].y));
		        
		      // cosa = (x1 - stiger[0].x)/t;

		       //sina = (y1  - stiger[0].y)/t;
		       angle = (atan((y1-stiger[0].y)/(x1-stiger[0].x))*180)/3.142;
		       if(angle < 0)
		       angle+=180;
		       tempx = line_x;
		       line_x = sqrt(line_x*line_x + line_y*line_y)*cos((angle*3.142)/180);
		      line_y = sqrt(line_y*line_y + tempx*tempx)*sin((angle*3.142)/180);
		       k=sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);
		       stiger[0].vel_x = k*cos((angle*3.142)/180);
		       stiger[0].vel_y = k*sin((angle*3.142)/180);
		       printf("%d %d",x,y);
			theta += 15;
			flag2 = 0;
		}	
		else if (button == GLUT_RIGHT_BUTTON)
		{
		        oldx = x;
		        oldy = y;
                        flag2 = 1;
			theta -= 15;
		}

		else if( button == GLUT_MIDDLE_BUTTON)
		{
		              

                           total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);
			                     total += 0.05;
			                      total2 = sqrt(line_x*line_x + line_y*line_y);
			                       total2 += 0.05;
			        
			                         line_x = total2*cos((angle*3.142)/180);
				  
				                   line_y = total2*sin((angle*3.142)/180);
				    
				                     stiger[0].vel_x = total*cos((angle*3.142)/180);
				                      stiger[0].vel_y = total*sin((angle*3.142)/180);



		}
	}
	else if (state == GLUT_UP && flag1 == 0) 
	{
	    if( button == GLUT_LEFT_BUTTON)
	    {
	       total = sqrt(stiger[0].vel_x*stiger[0].vel_x + stiger[0].vel_y*stiger[0].vel_y);

               stiger[0].x += stiger[0].vel_x*cos((3.142*angle)/180);
	                        stiger[0].y += stiger[0].vel_y*sin((3.142*angle)/180);
		                  flag1=1;
		                   line_x = 0.0f;
		                    line_y = 0.0f;


	    }
	}
} 

void drag(int x, int y){
if( x > oldx && flag2==1)
{
if(s_x == 0 && (stiger[0].x) <= 2.0f - stiger_rad )
                         stiger[0].x += 0.05f;
                   

}

else if(x < oldx && flag2==1)
{
if(s_x ==0 && stiger[0].x >= -2.0f + stiger_rad)
                        stiger[0].x -= 0.05f;
                 

}

else if( y > oldy)
{
 if(s_y == 0 && (stiger[0].y) <= 2.0f - stiger_rad)
                            stiger[0].y += 0.05f;

}
else if(y < oldy)
{
  if(s_y == 0 && (stiger[0].y) >= -2.0f + stiger_rad)
                         stiger[0].y -= 0.05f;



}
oldx = x;
oldy = y;


}

