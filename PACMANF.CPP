#include<fstream.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define ANGLE 45
#define ANGLE2 20
#define RADIUS 12
#define STEP 3
#define RATE 8
#define PAC 34
#define CORE 3

class horizontal;
class vertical;
class ghost;
class path;
class turningPoint;


float distance(int x1,int y1,int x2,int y2)
{

return sqrt(  pow(x2-x1,2)+pow(y2-y1,2)  );

}
//for better designing , 1 pacman = 34 pixels
//Extend ghost eyes in up mode (mode=1) so that eyes reach all the way up

float cosA[361],sinA[361];



void displayAllH();
void displayAllV();

class pacman
{
 public:	int x,y,mode,radius,color,milestone,score,lives;
		int scoreClock;

	public:  pacman(int x,int y,int color=YELLOW,int mode=3)
		 {
		    this->x=x;
		    this->y=y;
		    this->color=color;
		    radius=RADIUS;
		    this->mode=mode;
		    milestone=1;
		    score=0;

		    this->scoreClock=0;

		    this->lives=2;

		 }
		 /*draw() first updates pacman's coordinates directionwise
		  and then draws pacman
		 */
		 void draw();


		 void showScore(int);

		 void showLives(int);
		 // justDraw() only draws pacman
		 void justDraw();

		 friend int stillDeadAnyOne();
		 //When pacman eats a big coin
		 void scareAllGhosts();

		 void move(char);

	int isCloseToH(horizontal&);



	int isCloseToV(vertical&);

		void correct(int,int);

	int inRange(horizontal&);
	int inRange(vertical&);

	friend class ghost;
	friend path;
	friend class token;
	int isAnyGhostDead(pacman&);

	friend int stillDeadAnyOne();

};

//Most pacman methods will be defined here



void pacman::showLives(int cls=0)
{
 int currentX=this->x,currentY=this->y;
 int currentMode=this->mode;


 this->mode=3;

 if(cls)
 {setcolor(BLACK);
 setfillstyle(SOLID_FILL,BLACK);
 bar(3,370,130,400);}



 this->radius=8;

 this->x=12;
 this->y=382;

 for(int i=1;i<=this->lives;i++)
 {
   this->correct(x+=24,y);


 }


 this->x=currentX; this->y=currentY;
 this->radius=RADIUS;
 this->mode=currentMode;
 this->correct(this->x,this->y);

}

void pacman::showScore(int cls=0)
{

char str[60];
int i;

 if(cls)
{ setcolor(BLACK);
 setfillstyle(SOLID_FILL,BLACK);
 bar(54,28,320,53);
 }

 if(scoreClock>=0&&scoreClock<=5)

    setcolor(BLACK);

 else setcolor(WHITE);




 outtextxy(125,20,"1 UP");

 scoreClock=++scoreClock%10;




 setcolor(WHITE);

 outtextxy(200,20,"HIGH SCORE");

 int tx,ty;

 tx=129,ty=38;

 int temp=score;

 i=0;

 while(temp)
 {
   str[i++]=temp%10+48;
   temp/=10;

 }

 str[i]='\0';

 strrev(str);

 outtextxy(tx,ty,str);
 outtextxy(tx+120,ty,str);


}

void pacman::move(char input)
{       setcolor(0);
	setfillstyle(SOLID_FILL,BLACK);
	pieslice(x,y,0,360,radius+2);

	setcolor(color);
	setfillstyle(SOLID_FILL,color);

	switch(input)
	{
	 case 'a':
	 case 'A':
	 case 75 : mode=3; break;
	 case 'd':
	 case 'D':
	 case 77: mode=1; break;
	 case 's':
	 case 'S':
	 case 80: mode=4; break;
	 case 'w':
	 case 'W':
	 case 72: mode=2; break;



	}



	draw();




}



void pacman::correct(int tx,int ty)
{
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	pieslice(x,y,0,360,radius+2);

	setfillstyle(SOLID_FILL,color);

	x=tx;
	y=ty;

	justDraw();

	displayAllH();
	   displayAllV();


}

//Pacman method definitions end here

//All obstacle methods will be defined in this area
horizontal** hs=new horizontal*[80];


class horizontal
{
   int a,b,c,d,color;


   char type;
   public:
	    horizontal(int a,int b,int c,int d,int color=BLUE,char type='U')
	   {
	     this->a=a;
	     this->b=b;
	     this->c=c;
	     this->d=d;
	     this->color=color;
	     this->type=type;

	      hs[count++]=this;


	   }

	     static int count;

	   void draw()
	   { setcolor(color);
	     line(a,b,c,d);

	   }

	   friend pacman;
	   friend ghost;
	   friend void displayAllH();
};

int horizontal::count=0;



void displayAllH()
{
    for(int i=0;i<horizontal::count;i++)
    { if(hs[i]->color==BLACK)
      continue;

    hs[i]->draw();
    }

}


vertical** vs=new vertical*[80];

class vertical
{ int a,b,c,d,color;
  char type;
  public:
	   vertical(int a,int b,int c,int d,int color=BLUE,char type='L')
	  {
	    this->a=a;
	    this->b=b;
	    this->c=c;
	    this->d=d;
	    this->color=color;
	    this->type=type;

	    vs[count++]=this;
	  }

	  void draw()
	  { setcolor(color);
	    line(a,b,c,d);
	  }

	  static int count;

	  friend pacman;
	  friend ghost;
	 friend void displayAllV();
};

int vertical::count=0;

void displayAllV()
{
	for(int i=0;i<vertical::count;i++)
	{
	  if(vs[i]->color==BLACK)
	  continue;

	vs[i]->draw();
	}
}

//Obstacles are defined globally here
 horizontal h1(7,80,623,80,BLUE,'U');

// horizontal h2(5,450,639,450,BLUE,'D');

 horizontal h3(10-3,80+84,93,80+84,BLUE,'D');

 horizontal h4(10,193,93,193,BLUE,'U');

 horizontal h5e(5,80,11,80,BLACK,'U');
 horizontal h6e(90,164,95,164,BLACK,'D');
 horizontal h7e(91,193,95,193,BLACK,'U');
 horizontal h8e(5,164,9,164,BLACK,'D');

 horizontal h9(9,229,93,229,BLUE,'D');
 horizontal h10(7,258,93,258,BLUE,'U');

 horizontal h11e(90,224+5,95,224+5,BLACK,'D');

 horizontal h12e(90,253+5,95,253+5,BLACK,'U');
 horizontal h13e(5,253+5,9,253+5,BLACK,'U');

 horizontal h14(7,348,262,348,BLUE,'D');
 horizontal h15e(5,348,9,348,BLACK,'D');
 horizontal h16(276,348,472,348,BLUE,'D');

 horizontal h17(487,348,623,348,BLUE,'D');

 horizontal h18e(263,300,275,300,BLACK,'D');
 horizontal h19e(473,313,486,313,BLACK,'D');
 horizontal h20e(621,80,625,80,BLACK,'U');
 horizontal h21e(621,165-3,625,165-3,BLACK,'D');
 horizontal h22(536,162,623,162,BLUE,'D');
 horizontal h23e(535,162,540,162,BLACK,'D');
 horizontal h24e(534,193,539,193,BLACK,'U');
 horizontal h25(536,193,620,193,BLUE,'U');
 horizontal h26(536,228,620,228,BLUE,'D');
 horizontal h27e(534,228,539,228,BLACK,'D');
 horizontal h28e(534,259,539,259,BLACK,'U');
 horizontal h29(536,259,623,259,BLUE,'U');
 horizontal h30e(621,259,625,259,BLACK,'U');
 horizontal h31e(621,348,625,348,BLACK,'D');



 horizontal h32(45,292,93,292,BLUE,'D');
 horizontal h33(45,312,93,312,BLUE,'U');
 horizontal h34(145,292,217,292,BLUE,'D');
 horizontal h35(145,312,217,312,BLUE,'U');
 horizontal h36(43,132,75,132,BLUE,'U');
 horizontal h37(43,114,75,114,BLUE,'D');
 horizontal h38(144,114,218,114,BLUE,'D');
 horizontal h39(157,132,218,132,BLUE,'U');
 horizontal h40(198,165,220,165,BLUE,'D');
 horizontal h41(144,258,220,258,BLUE,'U');
 horizontal h42(157,238,212,238,BLUE,'D');
 horizontal h43(198,184,211,184,BLUE,'U');
 horizontal h44(257,151,340,151,RED,'D');
 horizontal h45(257,247,340,247,RED,'U');
 horizontal h46(380,152,414,152,BLUE,'D');

 horizontal h47(452,152,484,152,BLUE,'D');
 horizontal h48(380,219,484,219,BLUE,'U');
 horizontal h49(385,157,414,157,BLUE,'U');
 horizontal h50(452,157,480,157,BLUE,'U');
 horizontal h51(385,214,480,214,BLUE,'U');
 horizontal h52(284,184,312,184,RED,'D');
 horizontal h53(284,213,312,213,RED,'D');
 horizontal h54(268,118,327,118,BLUE,'U');
 horizontal h55(268,111,327,111,BLUE,'D');
 horizontal h56(390,117,472,117,GREEN,'U');
 horizontal h57(390,112,472,112,GREEN,'D');
 horizontal h58(539,113,582,113,BLUE,'D');
 horizontal h59(539,121,582,121,BLUE,'U');
 horizontal h60(315,315,429,315,BLUE,'U');
 horizontal h61(315,295,429,295,BLUE,'D');
 horizontal h62(522,314,581,314,BLUE,'U');
 horizontal h63(522,295,581,295,BLUE,'D');
 horizontal h64(392,263,451,263,BLUE,'U');
 horizontal h65(392,255,451,255,BLUE,'D');
 horizontal h66e(265,300,273,300,BLUE,'D');
 horizontal h67e(475,313,484,313,BLUE,'D');
 horizontal h68(10,188,88,188,BLUE,'D');
 horizontal h69(2,169,89,169,BLUE,'D');
 horizontal h70(2,75,628,75,BLUE,'U');
 horizontal h71(9,234,88,234,BLUE,'D');
 horizontal h72(541,167,628,167,BLUE,'D');
 horizontal h73(541,188,620,188,BLUE,'U');
 horizontal h74(2,253,88,253,BLUE,'U');
 horizontal h75(541,233,620,233,BLUE,'D');
 horizontal h76(541,254,628,254,BLUE,'U');
 horizontal h77(2,353,628,353,BLUE,'D');








// repeated for reverse directions

















 vertical v1(5,82,5,83+84-5,BLUE,'L');
// vertical v2(639,80,639,450,BLUE,'R');
 vertical v3(95,166,95,191,BLUE,'L');

// vertical v4(9,194,9,222,GREEN,'L');

 vertical v5e(5,80,5,84,BLACK,'L');
 vertical v6e(95,165,95,169,BLACK,'L');
 vertical v7e(5,160,5,164,BLACK,'L');
 vertical v8e(95,189,95,193,BLACK,'L');

 vertical v9(95,231,95,256,BLUE,'L');

 vertical v10e(95,224+5,95,228+5,BLACK,'L');

 vertical v11e(95,248+5,95,253+5,BLACK,'L');

 vertical v12(5,260,5,346,BLUE,'L');

 vertical v13e(5,253+5,5,257+5,BLACK,'L');
 vertical v14e(5,343,5,348,BLACK,'L');
 vertical v15(263,302,263,348,BLUE,'R');
 vertical v16(275,302,275,348,BLUE,'L');
 vertical v17(473,315,473,348,BLUE,'R');
 vertical v18e(263,301,263,305,BLACK,'R');
 vertical v19e(275,301,275,305,BLACK,'L');
 vertical v20e(473,314,473,319,BLACK,'R');
 vertical v21(486,315,486,348,BLUE,'L');
 vertical v22e(486,314,486,319,BLACK,'L');
 vertical v23(625,82,625,160,BLUE,'R');
 vertical v24e(625,80,625,84,BLACK,'R');
 vertical v25e(625,160-3,625,164-3,BLACK,'R');
 vertical v26e(534,162,534,167,BLACK,'R');
 vertical v27(534,164,534,191,BLUE,'R');
 vertical v28e(534,188,534,193,BLACK,'R');
 vertical v29e(534,229,534,233,BLACK,'R');
 vertical v30e(534,230,534,257,BLUE,'R');
 vertical v31e(534,253,534,258,BLACK,'R');
 vertical v32e(625,259,625,263,BLACK,'R');
 vertical v33(625,261,625,346,BLUE,'R');
 vertical v34e(625,343,625,348,BLACK,'R');
 vertical v35(155,134,155,236,BLUE,'L');
 vertical v36(142,116,142,256,BLUE,'R');
 vertical v37(196,167,196,182,BLUE,'R');
 vertical v38(213,186,213,236,BLUE,'R');
 vertical v39(222,167,222,256,BLUE,'L');
 vertical v40(255,154,255,244,RED,'R');
 vertical v41(342,154,342,244,RED,'L');
 vertical v42(380,153,380,218,BLUE,'R');
 vertical v43(485,152,485,219,BLUE,'L');
 vertical v44(385,157,385,214,BLUE,'L');
 vertical v45(480,157,480,214,BLUE,'R');
 vertical v46(451,152,451,157,BLUE,'R');
 vertical v47(415,152,415,157,BLUE,'L');
 vertical v48(282,186,282,211,RED,'R');
 vertical v49(314,186,314,211,RED,'L');
 vertical v50(77,116,77,130,BLUE,'L');
 vertical v51(41,116,41,130,BLUE,'R');
 vertical v52(95,294,95,310,BLUE,'L');
 vertical v53(43,294,43,310,BLUE,'R');
 vertical v54(143,294,143,310,BLUE,'R');
 vertical v55(219,294,219,310,BLUE,'L');
 vertical v56(220,116,220,130,BLUE,'L');
 vertical v57(266,113,266,116,BLUE,'R');
 vertical v58(329,113,329,116,BLUE,'L');
 vertical v59(313,297,313,313,BLUE,'R');
 vertical v60(431,297,431,313,BLUE,'L');
 vertical v61(389,113,389,116,GREEN,'R');
 vertical v62(473,113,473,116,GREEN,'L');

 vertical v63(389,257,389,261,BLUE,'R');
 vertical v64(454,257,454,261,BLUE,'L');
 vertical v65(537,115,537,119,BLUE,'R');
 vertical v66(584,115,584,119,BLUE,'L');

 vertical v67(520,297,520,312,BLUE,'R');
 vertical v68(583,297,583,312,BLUE,'L');
 vertical v69(90,171,90,186,BLUE,'L');
 vertical v70(90,236,90,251,BLUE,'L');
 vertical v71(0,77,0,167,BLUE,'L');
 vertical v72(0,255,0,351,BLUE,'L');

 vertical v73(539,235,539,252,BLUE,'R');
 vertical v74(539,169,539,186,BLUE,'R');
 vertical v75(630,77,630,165,BLUE,'R');
 vertical v76(630,256,630,351,BLUE,'R');



































//


void pacman::justDraw()
{
   setcolor(color);
   setfillstyle(SOLID_FILL,color);



   switch(mode)
   {
    case 1:
	     x=x>=639+radius?1:x;
	     pieslice(x,y,0+ANGLE,360-ANGLE,radius);

	     break;

    case 2:
	     y=y<=1-radius?479:y;
	     pieslice(x,y,0,90-ANGLE,radius);
	     pieslice(x,y,90+ANGLE,360,radius);
	     break;

    case 3:
	     x=x<=1-radius?639:x;
	     pieslice(x,y,0,180-ANGLE,radius);
	     pieslice(x,y,180+ANGLE,360,radius);
	     break;

    case 4:
	     y=y>=479+radius?1:y;
	     pieslice(x,y,0,270-ANGLE,radius);
	     pieslice(x,y,270+ANGLE,360,radius);
	     break;

    case -1:
	     pieslice(x,y,0+ANGLE2,360-ANGLE2,radius);

	     break;

    case -2:
	     pieslice(x,y,0,90-ANGLE2,radius);
	     pieslice(x,y,90+ANGLE2,360,radius);
	     break;

    case -3:
	     pieslice(x,y,0,180-ANGLE2,radius);
	     pieslice(x,y,180+ANGLE2,360,radius);
	     break;

    case -4:
	     pieslice(x,y,0,270-ANGLE2,radius);
	     pieslice(x,y,270+ANGLE2,360,radius);
	     break;





    default: pieslice(x,y,0,360,radius);






   }




}



void pacman::draw()
{
   setcolor(color);
   setfillstyle(SOLID_FILL,color);

   milestone=(milestone+1)%STEP;

   if(milestone==0)
   mode=-mode;

   switch(mode)
   {
    case 1:  x+=RATE;
	     x=x>=639+radius?1:x;

	     pieslice(x,y,0+ANGLE,360-ANGLE,radius);

	     break;

    case 2:  y-=RATE;
	     y=y<=1-radius?479:y;

	     pieslice(x,y,0,90-ANGLE,radius);
	     pieslice(x,y,90+ANGLE,360,radius);
	     break;

    case 3:  x-=RATE;
	     x=x<=1-radius?639:x;
	     pieslice(x,y,0,180-ANGLE,radius);
	     pieslice(x,y,180+ANGLE,360,radius);
	     break;

    case 4:  y+=RATE;
	     y=y>=479+radius?1:y;
	     pieslice(x,y,0,270-ANGLE,radius);
	     pieslice(x,y,270+ANGLE,360,radius);
	     break;

    case -1:  x+=RATE;
	     pieslice(x,y,0+ANGLE2,360-ANGLE2,radius);

	     break;

    case -2:  y-=RATE;
	     pieslice(x,y,0,90-ANGLE2,radius);
	     pieslice(x,y,90+ANGLE2,360,radius);
	     break;

    case -3:  x-=RATE;
	     pieslice(x,y,0,180-ANGLE2,radius);
	     pieslice(x,y,180+ANGLE2,360,radius);
	     break;

    case -4:  y+=RATE;
	     pieslice(x,y,0,270-ANGLE2,radius);
	     pieslice(x,y,270+ANGLE2,360,radius);
	     break;





    default: pieslice(x,y,0,360,radius);






   }




}


int mod(int a)
{return (a<0?-a:a);}

int pacman::isCloseToH(horizontal& h)
{


	switch(h.type)
	{
	 case 'U':  if(this->y-radius<=h.b-12)
		     return 0;

		   if(this->y-radius<=h.b+2&& (this->x>=h.a&&this->x<=h.c|| x+radius>=h.a-2&&x+radius<=h.c+2||x-radius<=h.c+2&&x-radius>=h.a-2 ))
		   {
		       this->correct(x,h.b+3+this->radius);

		       if(h.color==BLACK)
			return 0;


		   //    h.draw();

		       //printing for testing only
			//   cout<<h.a<<","<<h.b<<","<<h.c<<","<<h.d<<" ";

		   }
			 break;

	 case 'D':
			if(this->y+radius>=h.b+12)
		     return 0;


		   if(this->y+radius>=h.b-2&& (this->x>=h.a&&this->x<=h.c||x+radius>=h.a-2&&x+radius<=h.c+2||x-radius<=h.c+2&&x-radius>=h.a-2))
		   {
			  this->correct(x,h.b-3-this->radius);

		       if(h.color==BLACK)
			return 0;


		  //     h.draw();

			//printing for testing only
		  //	   cout<<h.a<<","<<h.b<<","<<h.c<<","<<h.d<<" ";

		   }

			 break;
	}


return 0;}

int pacman::isCloseToV(vertical& v)
{


	switch(v.type)
	{
	 case 'L':


		    if(this->x-radius<=v.a-12)
		    return 0;



		    if(this->x-radius<=v.a+2&& (this->y>=v.b&&this->y<=v.d || y-radius<=v.d+2&&y-radius>=v.b || y+radius>=v.b&&y+radius<=v.d) )
		    {
			this->correct(v.a+3+this->radius,y);

			if(v.color==BLACK)
			return 0;


		    //	v.draw();

			 //printing for testing only
		    //	   cout<<v.a<<","<<v.b<<","<<v.c<<","<<v.d<<" ";

		    }


		    break;


	 case 'R':  if(this->x+radius>=v.a+12)
		    return 0;


		    if(this->x+radius>=v.a-2&& (this->y>=v.b&&this->y<=v.d|| y-radius<=v.d+2&&y-radius>=v.b || y+radius>=v.b&&y+radius<=v.d) )
		    {
			this->correct(v.a-3-this->radius,y);

			if(v.color==BLACK)
			return 0;


		     //	v.draw();

			 //printing for testing only
		      //	   cout<<v.a<<","<<v.b<<","<<v.c<<","<<v.d<<" ";

		    }



		    break;



	}



return 0;}



//Obstacle code area ends



//Most ghost methods will be defined here
   ghost** gs=new ghost*[4];

  class ghost
  {  int x,y,mode,color,rate,id,taken,i,j,inbox,scared,fault,hitBottom,actualColor;
     int scareDuration;

     turningPoint* current;





     public: int dead;

	     ghost(int x,int y,int color,int mode=1,int id=1)
	     {
		this->x=x;
		this->y=y;
		this->color=color;
		this->actualColor=color;
		this->mode=mode;
		this->rate=2;

		dead=0;
		this->id=id;
		taken=0;
		this->scared=0;

		this->hitBottom=0;

		gs[count++]=this;
		this->current=NULL;

		this->i=this->j=0;

		this->inbox=0;
		this->fault=0;

		this->scareDuration=0;

	     }

	     static int count;

	     void draw();

	     int toggleUpDown();

	     void justDraw();

	     void drawWithColors();

	friend int isAnyGhostDead(pacman&);

	     void move(char);

	     void moveLittle();

	     void moveAroundOnItsOwn()
	     {draw();}

	     void setMode(char input)
	     {
		    this->mode=input;

	     }


	     int isCloseToH(horizontal&);
	     int isCloseToV(vertical&);
	     void correct(int,int);
	     int isDead(pacman&);




	     int isOn(turningPoint&);

	     int canReach(turningPoint&);

   friend pacman;
   friend vertical;
   friend horizontal;
   friend void correctAllGhosts();      //done
   friend void backToPath(ghost&);
   friend void backToPathAllGhosts();
   friend void drawAllGhosts();        //done
   friend class path;

   friend void directAllGhosts();

	void totallyOnTurn(turningPoint&);
   friend void allGhostsMoveAround();
  };



int stillDeadAnyOne()
{
   for(int i=0;i<ghost::count;i++)
   {
      if(gs[i]->dead==1)
      return 1;
   }

  return 0;
}


  void allGhostsMoveAround()
  {
   for(int i=0;i<ghost::count;i++)
   gs[i]->moveAroundOnItsOwn();

  }


  int ghost::count=0;




  void correctAllGhosts()
  {
     for(int i=0;i<ghost::count;i++)
     {
	  for(int j=0;j<horizontal::count;j++)
	  gs[i]->isCloseToH(*hs[j]);

	  for(j=0;j<vertical::count;j++)
	  gs[i]->isCloseToV(*vs[j]);





     }


  }



  void drawAllGhosts()
  {
     for(int i=0;i<ghost::count;i++)
     gs[i]->draw();

  }



  void ghost::correct(int tx,int ty)
  {
       //first erasing old ghost

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,BLACK);

       pieslice(x,y,0,180,12);
       bar(x-14,y-14,x+14,y+14);


       //

       setcolor(color);
       setfillstyle(SOLID_FILL,color);

       this->x=tx;
       this->y=ty;

       this->justDraw();



  }


  int ghost::isCloseToH(horizontal& h)
  {

	switch(h.type)
	{
	 case 'U':      if(this->y-12<=h.b-8)
			return 0;

		       if(this->y-12<=h.b+2&&this->x>=h.a&&this->x<=h.c)
		       {
				this->correct(x,h.b+3+12);
				h.draw();




				this->fault++;

				if(this->fault>=10)
				{this->mode=(this->mode+1)%5;
				this->fault=0;
		     //	  outtextxy(x,y,"fault");
			  }

				if(this->mode==0)
				this->mode=1;

				return 1;

		       }

	 break;


	 case 'D':      if(this->y+10>=h.b+8)
			return 0;

		       if(this->y+10>=h.b-2&&this->x>=h.a&&this->x<=h.c)

		       {
				this->correct(x,h.b-3-10);
				h.draw();

				this->fault++;

				if(this->fault>=10)
				{this->mode=(this->mode+1)%5;
				this->fault=0;
		       //		outtextxy(x,y,"fault");
				}

				if(this->mode==0)
				this->mode=1;


				return 1;

		       }

	 break;



	}




  return 0;}

  int ghost::isCloseToV(vertical& v)
  {
	switch(v.type)
	{


	 case 'L':        if(this->x-12<=v.a-8)
			  return 0;

			  if(this->x-12<=v.a+2&&this->y>=v.b&&this->y<=v.d)
			  {
				this->correct(v.a+3+12,y);
				v.draw();

				this->fault++;

				if(this->fault>=10)
				{this->mode=(this->mode+1)%5;
				 this->fault=0;
			 //	 outtextxy(x,y,"fault");
				 }

				if(this->mode==0)
				this->mode=1;


				return 1;

			  }

	 break;


	 case 'R':        if(this->x+12>=v.a+8)
			  return 0;


			 if(this->x+12>=v.a-2&&this->y>=v.b&&this->y<=v.d)
			  {
				this->correct(v.a-3-12,y);
				v.draw();

				this->fault++;

				if(this->fault>=10)
				{this->mode=(this->mode+1)%5;
				 this->fault=0;

			   //	 outtextxy(x,y,"fault");

				}

				if(this->mode==0)
				this->mode=1;


				return 1;
			  }


	 break;






	}



  return 0;}

  void ghost::move(char input)
  {
	switch(input)
	{
	 case 'a':
	 case 'A': mode=4; break;

	 case 'd':
	 case 'D': mode=2; break;

	 case 's':
	 case 'S': mode=3; break;

	 case 'w':
	 case 'W': mode=1; break;
	}

	    this->draw();


  }


//




  void ghost::moveLittle()
  {

       //first erasing old ghost

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,BLACK);

       pieslice(x,y,0,180,12);
       bar(x-14,y-14,x+14,y+11);

       if(this->dead==1)
       {

	switch(mode)
       {
	case 1:  y-=4; y=y<1?479:y;  break;
	case 2:  x+=4; x=x>639?1:x;   break;
	case 3:  y+=4; y=y>479?1:y;   break;
	case 4:  x-=4; x=x<1?639:x;  break;



       }

       goto eyes;


       }
       //


       //Updating position of ghost











       if(!ghost::scared)
       {

      eyes: setcolor(WHITE);
       setfillstyle(SOLID_FILL,WHITE);

       switch(mode)
       {
	case 3:

		fillellipse(x-5,y-2,3,4);
		fillellipse(x+5,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-2,x-4,y+2);
		putpixel(x-3,y-2,BLUE);
		putpixel(x-3,y-1,BLUE);
		putpixel(x-3,y,BLUE);
		putpixel(x-3,y+1,BLUE);


		bar(x+6,y-2,x+4,y+2);
		putpixel(x+3,y-2,BLUE);
		putpixel(x+3,y-1,BLUE);
		putpixel(x+3,y,BLUE);
		putpixel(x+3,y+1,BLUE);


	break;



	case 1:

		fillellipse(x-5,y-7,2,3);
		fillellipse(x+5,y-7,2,3);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-7,x-4,y-10);


		bar(x+6,y-7,x+4,y-10);

		break;
	case 4:


		fillellipse(x-7,y-2,3,4);
		fillellipse(x+3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-10,y-3,x-8,y);


		bar(x+2,y-3,x,y);

		break;

	case 2:

		fillellipse(x+7,y-2,3,4);
		fillellipse(x-3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x+10,y-3,x+8,y);


		bar(x-2,y-3,x,y);


		break;

       }



       }

  }


void readTrigFiles()
{
	 //Setting cos and sin array values for consistent drawing
   ifstream file("sin.bin",ios::in|ios::binary);

   file.read((char*)sin,sizeof(float)*361);

   file.close();

   file.open("cos.bin",ios::in|ios::binary);

   file.read((char*)cos,sizeof(float)*361);

   file.close();


}





//Tool area for level creation

path** ps=new path*[100];

class path
{
public:   int a,b,c,d,color;
	  char type;
	  static int count;
	  path(int a,int b,int c,int d,int color=BLACK,char type='H')
	  {
		this->a=a;
		this->b=b;
		this->c=c;
		this->d=d;
		this->color=color;
		this->type=type;
		ps[count++]=this;

	  }

	 void backToPath(pacman&);
	 void backToPath(ghost&);

      friend	 void backToAll(pacman&);

      friend void backToPathAllGhosts();
};

int path::count=0;




void path::backToPath(ghost& g)
{

	switch(this->type)
	{

	case 'H':

		   if((g.y<this->b||g.y>this->b)&&(g.x+12>=this->a&&g.x-12<=this->c)&&(this->b>=g.y-12&&this->b<=g.y+10))
		   {//correction logic for ghost
		    g.correct(g.x,this->b);

	      //	    cout<<"H case ";


		   }

	break;

	//Y mode is specially made to only affect ghosts vertically
	case 'Y':
	case 'V':

			 if((g.x<this->a||g.x>this->a)&&(this->a>=g.x-12&&this->a<=g.x+12)&&(g.y+10>=this->b&&g.y+10<=this->d||g.y-12<=this->d&&g.y-12>=this->b))
			 {//correction logic for ghost
			 g.correct(this->a,g.y);

		//		 cout<<"V case ";

			 }


	 break;


	}











}


void backToPathAllGhosts()
{

	for(int i=0;i<path::count;i++)
	{
	     for(int j=0;j<ghost::count;j++)
	     ps[i]->backToPath(*gs[j]);





	}



}



void backToAll(pacman& p)
{
	for(int i=0;i<path::count;i++)
	ps[i]->backToPath(p);

}

       //Here we draw path lines
       //*
       //*
       //*
       //*
       //*
       //*
//*
//*
//*
//*





void path::backToPath(pacman& p)
{ //    setcolor(color);
    //	line(a,b,c,d);

	switch(this->type)
	{
	 case 'H':                                       //adjusts hight range only to bit above and below to horizontal line
			if( (p.y>this->b||p.y<this->b)&&(this->b>=p.y-RADIUS&&this->b<=p.y+RADIUS)&&(p.x+CORE>=this->a&&p.x+CORE<=this->c||p.x-CORE<=this->c&&p.x-CORE>=this->a)  )
			{  //     cout<<" "<<a<<","<<b<<","<<c<<","<<d;
				p.correct(p.x,this->b);


			}




	 break;

	 case 'V':
			if((p.x>this->a||p.x<this->a)&&(this->a>=p.x-RADIUS&&this->a<=p.x+RADIUS  )&&(p.y+CORE>=this->b&&p.y+CORE<=this->d||p.y-CORE<=this->d&&p.y-CORE>=this->b))
			{    //   cout<<" "<<a<<","<<b<<","<<c<<","<<d;
				p.correct(this->a,p.y);

			}

	 break;



	}



}



class corner;

corner** cs=new corner*[150];

 class corner
 {  int a,b,c,d,color;
    static int count;

    public:   corner(int a,int b,int c,int d,int color)
	      {
		this->a=a;
		this->b=b;
		this->c=c;
		this->d=d;

		this->color=color;

	       cs[count++]=this;



	      }


	      void draw();

	    friend  void drawAllCorners();

 };

 int corner::count=0;




 corner c38(389,256,391,255,BLUE);
 corner c39(391,263,389,262,BLUE);
 corner c40(454,262,452,263,BLUE);
 corner c41(452,255,454,256,BLUE);
 corner c42(538,121,537,120,BLUE);
 corner c43(537,114,538,113,BLUE);
 corner c44(583,113,584,114,BLUE);
 corner c45(584,120,583,121,BLUE);
 corner c46(266,112,267,111,BLUE);
 corner c47(266,117,267,118,BLUE);
 corner c48(328,111,329,112,BLUE);
 corner c49(328,118,329,117,BLUE);
 corner c50(255,153,256,151,RED);
 corner c51(341,151,342,153,RED);
 corner c52(342,245,341,247,RED);
 corner c53(256,247,255,245,RED);
 corner c54(6,81,6,81,BLUE);
 corner c55(6,163,6,163,BLUE);
 corner c56(94,165,94,165,BLUE);
 corner c57(94,192,94,192,BLUE);
 corner c58(94,230,94,230,BLUE);
 corner c59(94,257,94,257,BLUE);
 corner c60(6,259,6,259,BLUE);
 corner c61(6,347,6,347,BLUE);
 corner c62(264,301,264,301,BLUE);
 corner c63(274,301,274,301,BLUE);
 corner c64(474,314,474,314,BLUE);
 corner c65(485,314,485,314,BLUE);
 corner c66(624,347,624,347,BLUE);
 corner c67(624,260,624,260,BLUE);
 corner c68(625,260,625,259,BLACK);
 corner c69(535,258,535,258,BLUE);
 corner c70(535,229,535,229,BLUE);
 corner c71(535,192,535,192,BLUE);
 corner c72(535,163,535,163,BLUE);
 corner c73(624,161,624,161,BLUE);
 corner c74(624,81,624,81,BLUE);
 corner c75(42,115,42,115,BLUE);
 corner c76(76,115,76,115,BLUE);
 corner c77(76,131,76,131,BLUE);
 corner c78(42,131,42,131,BLUE);
 corner c79(44,293,44,293,BLUE);
 corner c80(44,311,44,311,BLUE);
 corner c81(94,293,94,293,BLUE);
 corner c82(94,311,94,311,BLUE);
 corner c83(144,293,144,293,BLUE);
 corner c84(218,293,218,293,BLUE);
 corner c85(144,311,144,311,BLUE);
 corner c86(218,311,218,311,BLUE);
 corner c87(314,296,314,296,BLUE);
 corner c88(430,296,430,296,BLUE);
 corner c89(430,314,430,314,BLUE);
 corner c90(314,314,314,314,BLUE);
 corner c91(521,296,521,296,BLUE);
 corner c92(582,296,582,296,BLUE);
 corner c93(582,313,582,313,BLUE);
 corner c94(521,313,521,313,BLUE);
 corner c95(143,115,143,115,BLUE);
 corner c96(219,115,219,115,BLUE);
 corner c97(156,133,156,133,BLUE);
 corner c98(219,131,219,131,BLUE);
 corner c99(156,237,156,237,BLUE);
 corner c100(213,237,213,237,BLUE);
 corner c101(143,257,143,257,BLUE);
 corner c102(221,257,221,257,BLUE);
 corner c103(197,166,197,166,BLUE);
 corner c104(221,166,221,166,BLUE);
 corner c105(197,183,197,183,BLUE);
 corner c106(212,185,212,185,BLUE);
 corner c107(89,170,89,170,BLUE);
 corner c108(89,187,89,187,BLUE);
 corner c109(1,168,1,168,BLUE);
 corner c110(1,76,1,76,BLUE);
 corner c111(629,76,629,76,BLUE);
 corner c112(540,168,540,168,BLUE);
 corner c113(540,187,540,187,BLUE);
 corner c114(540,234,540,234,BLUE);
 corner c115(540,253,540,253,BLUE);
 corner c116(89,235,89,235,BLUE);
 corner c117(89,252,89,252,BLUE);
 corner c118(1,254,1,254,BLUE);
 corner c119(629,166,629,166,BLUE);
 corner c120(629,255,629,255,BLUE);
 corner c121(1,352,1,352,BLUE);
 corner c122(629,352,629,352,BLUE);
 corner c123(416,154,450,154,LIGHTMAGENTA);
 corner c124(416,155,450,155,LIGHTMAGENTA);















































































































 void corner::draw()
 {
	setcolor(color);
	line(a,b,c,d);

 }



 void drawAllCorners()
 {

	for(int i=0;i<corner::count;i++)
	{setcolor(cs[i]->color);
	cs[i]->draw();
	 }


 }




  class line0
  {
    int a,b,c,d,color;

    public:  line0(int a=125,int b=125,int c=150,int d=125,int color=GREEN)
	     {this->a=a; this->b=b; this->c=c; this->d=d; this->color=color;}

	     void input(char i);


  };

  void line0::input(char key)
  {
  setcolor(0);
  line(a,b,c,d);

	switch(key)
	{
	 case 'a':
	 case 'A': a--; c--; break;
	 case 'd':
	 case 'D': a++; c++; break;

	 case 's':
	 case 'S': b++; d++; break;
	 case 'w':
	 case 'W': b--; d--; break;

	 case 'c':
	 case 'C': a+=5; c-=5; break;

	 case '1': c=a+PAC*1;

	 break;

	 case '2': c=a+PAC*2;

	 break;

	 case '3': c=a+PAC*3;

	 break;

	 case '4': c=a+PAC*4;

	 break;

	 case '5': c=a+PAC*5;

	 break;

	 case '6': c=a+PAC*6;

	 break;

	 case '7': c=a+PAC*7;

	 break;

	 case '8': c=a+PAC*8;

	 break;


	 case '9': c=a+PAC*9;

	 break;

	 case 'p':
	 case 'P':
		cout<<a<<","<<b<<","<<c<<","<<d;

	 break;


	 case '+': c++; break;

	 case '-': c--; break;

	}

	setcolor(color);
	line(a,b,c,d);

  }




    class line1
  {
    int a,b,c,d,color;

    public:  line1(int a=125,int b=125,int c=125,int d=150,int color=GREEN)
	     {this->a=a; this->b=b; this->c=c; this->d=d; this->color=color;}

	     void input(char i);


  };

  void line1::input(char key)
  {
  setcolor(0);
  line(a,b,c,d);

	switch(key)
	{
	 case 'a':
	 case 'A': a--; c--; break;
	 case 'd':
	 case 'D': a++; c++; break;

	 case 's':
	 case 'S': b++; d++; break;
	 case 'w':
	 case 'W': b--; d--; break;

	 case 'c':
	 case 'C': b+=5; d-=5; break;

	 case '1': d=b+PAC*1;

	 break;

	 case '2': d=b+PAC*2;

	 break;

	 case '3': d=b+PAC*3;

	 break;

	 case '4': d=b+PAC*4;

	 break;

	 case '5': d=b+PAC*5;

	 break;

	 case '6': d=b+PAC*6;

	 break;

	 case '7': d=b+PAC*7;

	 break;

	 case '8': d=b+PAC*8;

	 break;


	 case '9': d=b+PAC*9;

	 break;

	 case 'p':
	 case 'P':
		cout<<a<<","<<b<<","<<c<<","<<d;

	 break;

	 case '+': d++; break;

	 case '-': d--; break;



	}

	setcolor(color);
	line(a,b,c,d);

  }

//



void respectAllH(pacman& p)
{
	for(int i=0;i<horizontal::count;i++)
	p.isCloseToH(*hs[i]);

}

void respectAllV(pacman& p)
{
	for(int i=0;i<vertical::count;i++)
	p.isCloseToV(*vs[i]);


}



token** ts=new token*[200];

class token
{
 public: int x,y,color,type,state,blinker;  //'B' for big or 'S' for small
  static int count;
	 token(int x,int y,int type)
	 {
		this->x=x;
		this->y=y;
		this->type=type;
		this->color=EGA_LIGHTRED;
		this->state=1;
	       ts[count++]=this;
	       this->blinker=0;
	 }

	 token()
	 {



		this->color=EGA_LIGHTRED;
		this->state=1;
	       ts[count++]=this;
	 }

	 void draw();

	 ~token()
	 {
	 }

	 void touchedPacman(pacman& p);

	 friend void checkTokensForPacman(pacman& p);
	 friend void drawAllTokens();

};


void drawAllTokens()
{  //     in this level , 147 tokens are drawn
	for(int i=0;i<147;i++)
	ts[i]->draw();


}


	 void token::touchedPacman(pacman& p)
	 {
		if(state==0)
		return;

	     if(this->x>=p.x-RADIUS+2&&this->x<=p.x+RADIUS-2&&this->y>=p.y-RADIUS+2&&this->y<=p.y+RADIUS-2)
	      {
		    this->state=0;
		    this->draw();

		    p.justDraw();


		    p.score=this->type=='S'?p.score+10:p.score+50;
		    p.showScore(1);
		//    cout<<" Eaten ";


		if(this->type=='B')
		p.scareAllGhosts();


		    for(int i=0;i<token::count;i++)
		    {
			if(ts[i]==this)
			{ts[i]=NULL; break;}
		    }

	      sound(420);
	      delay(10);
	      nosound();



	}

	 }


void checkTokensForPacman(pacman& p)
{
	for(int i=0;i<token::count;i++)
	{  if(ts[i]==NULL)
	   continue;

	ts[i]->touchedPacman(p);
	 }

}

int token::count=0;



	 void token::draw()
	 {
	 blinker=++blinker%10;




		switch(type)
		{
		case 'B':  if(state)
			   {
			   if(blinker>=0&&blinker<=5)
			   {setcolor(EGA_LIGHTRED); setfillstyle(SOLID_FILL,color);}

			   else
			   {setcolor(WHITE); setfillstyle(SOLID_FILL,WHITE);}

			    }

			   else {setcolor(BLACK); setfillstyle(SOLID_FILL,BLACK);   }
			   pieslice(x,y,0,360,5);
			   break;
		case 'S':
			   if(state)
			   setcolor(color);

			   else setcolor(BLACK);

			outtextxy(x,y,".");


		     //	   putpixel(x-1,y-1,color);
		   //	   putpixel(x,y-1,color);
		 //	   putpixel(x+1,y-1,color);
	       //	   putpixel(x-1,y,color);
	     //		   putpixel(x,y,color);
	   //		   putpixel(x+1,y,color);
	 //		   putpixel(x-1,y+1,color);
       //		   putpixel(x,y+1,color);
     //			   putpixel(x+1,y+1,color);

			   break;


		}
	 }



	  class turningPoint;

	  turningPoint** tps=new turningPoint*[50];


	 class turningPoint
	 {   int a,b,c,d,*options;

	     static int count;

	     public:   int last;

		       turningPoint(int a,int b,int c,int d)
		       {
			this->a=a;
			this->b=b;
			this->c=c;
			this->d=d;
			tps[count++]=this;

			options=new int[4];
			this->last=0;
		       }

		       //default contructor needed for graph
		       turningPoint()
		       {}


		       int operator ==(turningPoint& t)
		       {
			 if(this->a==t.a&&this->b==t.b)

		       return 1;

		       else return 0;
		       }

		       void setWays(int a,int b,int c,int d)
		       {
			options[0]=a;
			options[1]=b;
			options[2]=c;
			options[3]=d;

		       }


		       void setValues(int a,int b,int l=0)
		       {this->a=a; this->b=b; this->c=a+8;this->d=b+8; this->last=l;}

		       //just for testing purposes
		       friend void drawAllTurningPoints();
		       friend ghost;

		       friend void directAllGhosts();








	 };

	 int turningPoint::count=0;


	 void directAllGhosts()
	 {
	     for(int i=0;i<ghost::count;i++)
	     {
	       for(int j=0;j<turningPoint::count;j++)
	       gs[i]->totallyOnTurn(*tps[j]);




	     }

	 }


	 void drawAllTurningPoints()
	 {
	   setcolor(WHITE);
	   setfillstyle(SOLID_FILL,WHITE);

	   for(int i=0;i<turningPoint::count;i++)
	   bar(tps[i]->a,tps[i]->b,tps[i]->c,tps[i]->d);

	 }




	 void ghost::totallyOnTurn(turningPoint& t)
	 {                      //was 12 before             //was 12 before  , y+8 was y+10 before
		if(t.a>this->x-10&&t.c<this->x+10&&t.b>this->y-8&&t.d<this->y+8&&this->taken==0&&current==NULL)
		{
	    //	cout<<"Completely on Podint ";

		this->fault=0;

		int choice;

		decisionPoint :   choice=random(4);

		if(t.options[choice]==0)
		goto decisionPoint;

		this->mode=choice+1;

     //	    cout<<" "<<choice+1;

		this->taken=1;
		this->current=&t;


	   //	cout<<"Tp "<<t.a<<","<<t.b<<","<<t.c<<","<<t.d;

		}

		else if(current!=NULL&&!(current->a>this->x-12&&current->c<this->x+12&&current->b>this->y-12&&current->d<this->y+10)&&taken==1)
		{
		     taken=0;
  //		     cout<<"S";
		     current=NULL;

		}

	 }




	 turningPoint graph[35][12];

	 void setGraph()
	 {


	 graph[0][0].setValues(20,94);
	 graph[0][1].setValues(353,92);
	 graph[0][2].setValues(354,130);
	 graph[0][3].setValues(427,130,1);


	 graph[1][0].setValues(19,143);
	 graph[1][1].setValues(113,143);
	 graph[1][2].setValues(113,94);
	 graph[1][2].setValues(353,92);
	 graph[1][3].setValues(354,130);
	 graph[1][4].setValues(427,130,1);


	 graph[2][0].setValues(21,270);
	 graph[2][1].setValues(235,270);
	 graph[2][2].setValues(235,94);
	 graph[2][3].setValues(353,92);
	 graph[2][4].setValues(354,130);
	 graph[2][5].setValues(427,130,1);


	 graph[3][0].setValues(21,325);
	 graph[3][1].setValues(113,325);
	 graph[3][2].setValues(113,94);
	 graph[3][3].setValues(353,92);
	 graph[3][4].setValues(354,130);
	 graph[3][5].setValues(427,130,1);

	 graph[4][0].setValues(113,325);
	 graph[4][1].setValues(113,94);
	 graph[4][2].setValues(353,92);
	 graph[4][3].setValues(354,130);
	 graph[4][4].setValues(427,130,1);




	 graph[5][0].setValues(113,270);
	 graph[5][1].setValues(113,94);
	 graph[5][2].setValues(353,92);
	 graph[5][3].setValues(354,130);
	 graph[5][4].setValues(427,130,1);


	 graph[6][0].setValues(113,205);
	 graph[6][1].setValues(113,94);
	 graph[6][2].setValues(353,92);
	 graph[6][3].setValues(354,130);
	 graph[6][4].setValues(427,130,1);



	 graph[7][0].setValues(113,143);
	 graph[7][1].setValues(113,94);
	 graph[7][2].setValues(353,92);
	 graph[7][3].setValues(354,130);
	 graph[7][4].setValues(427,130,1);



	 graph[8][0].setValues(113,94);
	 graph[8][1].setValues(353,92);
	 graph[8][2].setValues(354,130);
	 graph[8][3].setValues(427,130,1);



	 graph[9][0].setValues(235,324);
	 graph[9][1].setValues(235,94);
	 graph[9][2].setValues(353,92);
	 graph[9][3].setValues(354,130);
	 graph[9][4].setValues(427,130,1);



	 graph[10][0].setValues(235,270);
	 graph[10][1].setValues(235,94);
	 graph[10][2].setValues(353,92);
	 graph[10][3].setValues(354,130);
	 graph[10][4].setValues(427,130,1);


	 graph[11][0].setValues(238,146);
	 graph[11][1].setValues(235,94);
	 graph[11][2].setValues(353,92);
	 graph[11][3].setValues(354,130);
	 graph[11][4].setValues(427,130,1);



	 graph[12][0].setValues(235,129);
	 graph[12][1].setValues(235,94);
	 graph[12][2].setValues(353,92);
	 graph[12][3].setValues(354,130);
	 graph[12][4].setValues(427,130,1);


	 graph[13][0].setValues(235,94);
	 graph[13][1].setValues(353,92);
	 graph[13][2].setValues(354,130);
	 graph[13][3].setValues(427,130,1);



	 graph[14][0].setValues(293,327);
	 graph[14][1].setValues(293,267);
	 graph[14][2].setValues(500,276);
	 graph[14][3].setValues(507,138);
	 graph[14][4].setValues(427,130,1);


	 graph[15][0].setValues(293,267);
      //	 graph[15][1].setValues(293,267);
	 graph[15][1].setValues(500,276);
	 graph[15][2].setValues(507,138);
	 graph[15][3].setValues(427,130,1);


	 graph[16][0].setValues(359,267);
	 graph[16][1].setValues(354,130);
	 graph[16][2].setValues(427,130,1);

	 graph[17][0].setValues(359,233);
	 graph[17][1].setValues(354,130);
	 graph[17][2].setValues(427,130,1);


	 graph[18][0].setValues(354,130);
	 graph[18][1].setValues(427,130,1);


	 graph[19][0].setValues(427,130,1);



	 graph[20][0].setValues(353,92);
	 graph[20][1].setValues(354,130);
	 graph[20][2].setValues(427,130,1);



	 graph[21][0].setValues(446,327);
	 graph[21][1].setValues(446,278);
	 graph[21][2].setValues(500,276);
	 graph[21][3].setValues(507,138);
	 graph[21][4].setValues(427,130,1);



	 graph[22][0].setValues(446,278);
	 graph[22][1].setValues(500,276);
	 graph[22][2].setValues(507,138);
	 graph[22][3].setValues(427,130,1);




	 graph[23][0].setValues(500,326);
	 graph[23][1].setValues(507,138);
	 graph[23][2].setValues(427,130,1);


	 graph[24][0].setValues(500,276);
	 graph[24][1].setValues(507,138);
	 graph[24][2].setValues(427,130,1);


	 graph[25][0].setValues(501,234);
	 graph[25][1].setValues(507,138);
	 graph[25][2].setValues(427,130,1);



	 graph[26][0].setValues(507,205);
	 graph[26][1].setValues(507,138);
	 graph[26][2].setValues(427,130,1);



	 graph[27][0].setValues(507,138);
	 graph[27][1].setValues(427,130,1);



	 graph[28][0].setValues(507,93);
	 graph[28][1].setValues(507,138);
	 graph[28][2].setValues(427,130,1);


	 graph[29][0].setValues(601,326);
	 graph[29][1].setValues(601,276);
	 graph[29][2].setValues(500,276);
	 graph[29][3].setValues(507,138);
	 graph[29][4].setValues(427,130,1);


	 graph[30][0].setValues(601,276);
	 graph[30][1].setValues(500,276);
	 graph[30][2].setValues(507,138);
	 graph[30][3].setValues(427,130,1);


	 graph[31][0].setValues(605,93);
	 graph[31][1].setValues(507,93);
	 graph[31][2].setValues(507,138);
	 graph[31][3].setValues(427,130,1);


	 graph[32][0].setValues(601,142);
	 graph[32][1].setValues(427,130,1);


	 graph[33][0].setValues(172,146);
	 graph[33][1].setValues(238,146);
	 graph[33][2].setValues(235,94);
	 graph[33][3].setValues(353,92);
	 graph[33][4].setValues(354,130);
	 graph[33][5].setValues(427,130,1);


	 graph[34][0].setValues(172,212);
	 graph[34][1].setValues(172,146);
	 graph[34][2].setValues(238,146);
	 graph[34][3].setValues(235,94);
	 graph[34][4].setValues(353,92);
	 graph[34][5].setValues(354,130);
	 graph[34][6].setValues(427,130,1);










	 }


	 int ghost::isOn(turningPoint& t)
	 {    //t.a>this->x-10&&t.c<this->x+10&&t.b>this->y-8&&t.d<this->y+8
	   if(t.a>this->x-12&&t.c<this->x+12&&t.b>this->y-12&&t.d<this->y+10)
	   return 1;

	 return 0;
	 }


  int ghost::isDead(pacman& p)
  {
	if(!this->scared||this->dead)
	return 0;

	if((p.x+RADIUS>=x-12&&p.x+RADIUS<=x+12||p.x-RADIUS>=x-12&&p.x-RADIUS<=x+12)&&(p.y+RADIUS>=y-12&&p.y+RADIUS<=y+10||p.y-RADIUS>=y-12&&p.y-RADIUS<=y+10) )
	{ this->dead=1;


	int tx=p.x,ty=p.y-RADIUS;


	for(int i=1;i<=9;i++)
	{ setcolor(EGA_CYAN);
	outtextxy(tx,ty,"500");
	  setcolor(BLACK);
	   delay(25);
	  outtextxy(tx,ty--,"500");


	  p.justDraw();


	}

	p.score+=500;
	 p.showScore(1);



	//finding closest turningPoint to dead ghost
	 int loc;

	 turningPoint closest=*tps[0];

	 for(loc=0;loc<turningPoint::count;loc++)
	 {       if(this->canReach(*tps[loc])&&distance(this->x,this->y,tps[loc]->a+4,tps[loc]->b+4)<distance(this->x,this->y,closest.a+4,closest.b+4))
	   { closest=*tps[loc];


	    }


	 }



				 //defective location needs better conditions
				 //for overlapping
	 while(this->isOn(closest)==0)
	 {
	     if(x-10>closest.a)
	     {mode=4;
	     this->moveLittle();
	     this->justDraw();}

	     if(x+10<closest.a)
	     {mode=2;
	     this->moveLittle();
	     this->justDraw();}

	     if(y-10>closest.b)
	     {mode=1;
	     this->moveLittle();
	     this->justDraw();}


	     if(y+8<closest.b)
	     {mode=4;
	     this->moveLittle();
	     this->justDraw();}



	     if(x-10>closest.c)
	     {mode=4;
	     this->moveLittle();
	     this->justDraw();}


	     if(x+10<closest.c)
	     {mode=2;
	     this->moveLittle();
	     this->justDraw();}

	     if(y-10>closest.d)
	     {mode=1;
	     this->moveLittle();
	     this->justDraw();}

	     if(y+8<closest.d)
	     {mode=3;
	     this->moveLittle();
	     this->justDraw();}



	     backToPathAllGhosts();

    //	      cout<<"Where is closest?";

	  //    setcolor(RED);
	//      outtextxy(closest.a,closest.b,"Target");


       //	     if(getch()=='0')
	 //		    exit(0);
	 }


	//  cout<<"Standing on closest ";


      for(i=0;i<35;i++)
      {
	 if(graph[i][0]==closest)
	 {
	   this->i=i;
	   this->j=0;
	   break;
	 }



      }


      p.correct(p.x,p.y);

       return 1;
	}



   return 0;
  }



  int ghost::canReach(turningPoint& t)
  {
	int i;

	for(i=0;i<vertical::count;i++)
	{
	    if((vs[i]->a>=this->x&&vs[i]->a<=t.a || vs[i]->a<=this->x&&vs[i]->a>=t.a) && (this->y+10>=vs[i]->b&&this->y+10<=vs[i]->d||this->y-12>=vs[i]->b&&this->y-12<=vs[i]->d)&&(t.b>=vs[i]->b&&t.b<=vs[i]->d || t.d>=vs[i]->b&&t.d<=vs[i]->d )   )
	    return 0;


	}

	for(i=0;i<horizontal::count;i++)
	{
		if((hs[i]->b>=this->y+10&&hs[i]->b<=t.b||hs[i]->b>=t.d&&hs[i]->b<=this->y-12)&&(this->x-12>=hs[i]->a&&this->x-12<=hs[i]->c||this->x+12>=hs[i]->a&&this->x+12<=hs[i]->c)&&(t.a>=hs[i]->a&&t.a<=hs[i]->c||t.c>=hs[i]->a&&t.c<=hs[i]->c))
		return 0;


	}





  return 1;}



      void ghost::justDraw()
  {

       //first erasing old ghost

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,BLACK);

       pieslice(x,y,0,180,12);
       bar(x-14,y-14,x+14,y+11);

       if(this->dead==1)
       goto eyes;

       //

       if(this->scared)
       {setcolor(BLUE); setfillstyle(SOLID_FILL,BLUE);

       pieslice(x,y,0,180,12);
       bar(x-12,y,x+12,y+6);

       line(x-12,y+4,x-12,y+10);

       line(x+12,y+4,x+12,y+10);

       line(x-12,y+10,x,y);
       line(x+12,y+10,x,y);

       floodfill(x-11,y+8,BLUE);
       floodfill(x+11,y+8,BLUE);


       line(x-8,y+3,x-4,y+10);
       line(x+8,y+3,x+4,y+10);


       line(x-2,y+3,x-2,y+10);
       line(x+2,y+3,x+2,y+10);

       putpixel(x-3,y+10,BLUE);
       putpixel(x+3,y+10,BLUE);

       floodfill(x-3,y+9,BLUE);
       floodfill(x+3,y+9,BLUE);



       //mouth
       putpixel(x,y+2,EGA_LIGHTRED);
       putpixel(x-1,y+2,EGA_LIGHTRED);
       putpixel(x+1,y+2,EGA_LIGHTRED);

       putpixel(x-2,y+3,EGA_LIGHTRED);
       putpixel(x-3,y+3,EGA_LIGHTRED);
       putpixel(x-4,y+3,EGA_LIGHTRED);

       putpixel(x+2,y+3,EGA_LIGHTRED);
       putpixel(x+3,y+3,EGA_LIGHTRED);
       putpixel(x+4,y+3,EGA_LIGHTRED);



       putpixel(x-5,y+2,EGA_LIGHTRED);
       putpixel(x-6,y+2,EGA_LIGHTRED);
       putpixel(x-7,y+2,EGA_LIGHTRED);

       putpixel(x+5,y+2,EGA_LIGHTRED);
       putpixel(x+6,y+2,EGA_LIGHTRED);
       putpixel(x+7,y+2,EGA_LIGHTRED);



       putpixel(x-8,y+3,EGA_LIGHTRED);
       putpixel(x+8,y+3,EGA_LIGHTRED);


       }



       else if(!this->scared&&this->dead==0)
       {setcolor(this->color); setfillstyle(SOLID_FILL,this->color);


       pieslice(x,y,0,180,12);
       bar(x-12,y,x+12,y+6);

       line(x-12,y+4,x-12,y+10);

       line(x+12,y+4,x+12,y+10);

       line(x-12,y+10,x,y);
       line(x+12,y+10,x,y);

       floodfill(x-11,y+8,color);
       floodfill(x+11,y+8,color);


       line(x-8,y+3,x-4,y+10);
       line(x+8,y+3,x+4,y+10);


       line(x-2,y+3,x-2,y+10);
       line(x+2,y+3,x+2,y+10);

       putpixel(x-3,y+10,color);
       putpixel(x+3,y+10,color);

       floodfill(x-3,y+9,color);
       floodfill(x+3,y+9,color);
       }







       if(!this->scared)
       {
     eyes:  setcolor(WHITE);
       setfillstyle(SOLID_FILL,WHITE);

       switch(mode)
       {
	case 3:

		fillellipse(x-5,y-2,3,4);
		fillellipse(x+5,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-2,x-4,y+2);
		putpixel(x-3,y-2,BLUE);
		putpixel(x-3,y-1,BLUE);
		putpixel(x-3,y,BLUE);
		putpixel(x-3,y+1,BLUE);


		bar(x+6,y-2,x+4,y+2);
		putpixel(x+3,y-2,BLUE);
		putpixel(x+3,y-1,BLUE);
		putpixel(x+3,y,BLUE);
		putpixel(x+3,y+1,BLUE);


	break;



	case 1:

		fillellipse(x-5,y-7,2,3);
		fillellipse(x+5,y-7,2,3);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-7,x-4,y-10);


		bar(x+6,y-7,x+4,y-10);

		break;
	case 4:


		fillellipse(x-7,y-2,3,4);
		fillellipse(x+3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-10,y-3,x-8,y);


		bar(x+2,y-3,x,y);

		break;

	case 2:

		fillellipse(x+7,y-2,3,4);
		fillellipse(x-3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x+10,y-3,x+8,y);


		bar(x-2,y-3,x,y);


		break;

       }



       }

  }


      void ghost::drawWithColors()
  {




       //first erasing old ghost

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,BLACK);

       pieslice(x,y,0,180,12);
       bar(x-14,y-14,x+14,y+11);


       //




       setcolor(this->color); setfillstyle(SOLID_FILL,this->color);


       pieslice(x,y,0,180,12);
       bar(x-12,y,x+12,y+6);

       line(x-12,y+4,x-12,y+10);

       line(x+12,y+4,x+12,y+10);

       line(x-12,y+10,x,y);
       line(x+12,y+10,x,y);

       floodfill(x-11,y+8,color);
       floodfill(x+11,y+8,color);


       line(x-8,y+3,x-4,y+10);
       line(x+8,y+3,x+4,y+10);


       line(x-2,y+3,x-2,y+10);
       line(x+2,y+3,x+2,y+10);

       putpixel(x-3,y+10,color);
       putpixel(x+3,y+10,color);

       floodfill(x-3,y+9,color);
       floodfill(x+3,y+9,color);








     eyes: setcolor(WHITE);
       setfillstyle(SOLID_FILL,WHITE);

       switch(mode)
       {
	case 3:

		fillellipse(x-5,y-2,3,4);
		fillellipse(x+5,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-2,x-4,y+2);
		putpixel(x-3,y-2,BLUE);
		putpixel(x-3,y-1,BLUE);
		putpixel(x-3,y,BLUE);
		putpixel(x-3,y+1,BLUE);


		bar(x+6,y-2,x+4,y+2);
		putpixel(x+3,y-2,BLUE);
		putpixel(x+3,y-1,BLUE);
		putpixel(x+3,y,BLUE);
		putpixel(x+3,y+1,BLUE);


	break;



	case 1:

		fillellipse(x-5,y-7,2,3);
		fillellipse(x+5,y-7,2,3);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-7,x-4,y-10);


		bar(x+6,y-7,x+4,y-10);

		break;
	case 4:


		fillellipse(x-7,y-2,3,4);
		fillellipse(x+3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-10,y-3,x-8,y);


		bar(x+2,y-3,x,y);

		break;

	case 2:

		fillellipse(x+7,y-2,3,4);
		fillellipse(x-3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x+10,y-3,x+8,y);


		bar(x-2,y-3,x,y);


		break;

       }





  }


 void ghost::draw()
  {



	if(this->scared)

	   scareDuration++;

       //	if(scareDuration>=690)
      //	{
	//   this->color=WHITE;

       //	}


	if(this->scared&&scareDuration==700)
	{this->scared=0; scareDuration=0; }




       //first erasing old ghost

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,BLACK);

       pieslice(x,y,0,180,12);
       bar(x-14,y-14,x+14,y+11);

       if(this->dead==1)
     {



      //restoration logic
		     //does'nt work yet
      if(this->isOn(graph[this->i][this->j])&&graph[this->i][this->j].last==0)
      {
	this->j++;
     //	outtextxy(x,y,"next");
      }



      else if(this->inbox==1||this->isOn(graph[this->i][this->j])&&graph[this->i][this->j].last==1)

      {// cout<<"On laast one "<<graph[this->i][this->j].a
     // <<","<<graph[this->i][this->j].b<<","<<graph[this->i][this->j].c<<","<<graph[this->i][this->j].d;




	    /*Correct previous logic that works
		this->correct(433,this->y);

		    for(int i=1;i<=50;i++)
		   {
			  this->correct(this->x,++this->y);
			  drawAllCorners();
		   }



		   this->dead=0;
		   this->scared=0;
		   this->justDraw();

		    for(i=1;i<=50;i++)
		   {
			  this->correct(this->x,--this->y);
			  drawAllCorners();
		   }

      //		   this->inbox=0;


      */

    //		}

		 if(this->inbox==0)
		 {
		   this->inbox=1;

		   this->correct(438,this->y);

		 }

		 if(toggleUpDown()==1)
		 this->dead=0;






	}

       else if(this->isOn(graph[this->i][this->j])==0&&this->inbox==0)
      {
    //  setcolor(EGA_CYAN);
    //  outtextxy(x,y,"adjusting");


    //  outtextxy(graph[this->i][this->j].a,graph[this->i][this->j].b,"next");


      if(x<graph[this->i][this->j].c&&mod(x-graph[this->i][this->j].c)>20)
      x+=rate;

      if(x>graph[this->i][this->j].a&&mod(x-graph[this->i][this->j].a)>20)
      x-=rate;

      if(y<graph[this->i][this->j].d&&mod(y-graph[this->i][this->j].d)>20)
      y+=rate;

      if(y>graph[this->i][this->j].b&&mod(y-graph[this->i][this->j].b)>20)
      y-=rate;


      if(x<graph[this->i][this->j].c&&mod(x-graph[this->i][this->j].c)>0)
      x+=rate;

      if(x>graph[this->i][this->j].a&&mod(x-graph[this->i][this->j].a)>0)
      x-=rate;

      if(y<graph[this->i][this->j].d&&mod(y-graph[this->i][this->j].d)>0)
      y+=rate;

      if(y>graph[this->i][this->j].b&&mod(y-graph[this->i][this->j].b)>0)
      y-=rate;







      }




     goto eyes;      }

       //

       if(this->dead==0||this->dead==1)
     {
       //Updating position of ghost

       switch(mode)
       {
	case 1:  y-=rate; y=y<1?479:y;  break;
	case 2:  x+=rate; x=x>639?1:x;   break;
	case 3:  y+=rate; y=y>479?1:y;   break;
	case 4:  x-=rate; x=x<1?639:x;  break;



       }


      }








       if(this->scared)
       {setcolor(BLUE); setfillstyle(SOLID_FILL,BLUE);

       pieslice(x,y,0,180,12);
       bar(x-12,y,x+12,y+6);

       line(x-12,y+4,x-12,y+10);

       line(x+12,y+4,x+12,y+10);

       line(x-12,y+10,x,y);
       line(x+12,y+10,x,y);

       floodfill(x-11,y+8,BLUE);
       floodfill(x+11,y+8,BLUE);


       line(x-8,y+3,x-4,y+10);
       line(x+8,y+3,x+4,y+10);


       line(x-2,y+3,x-2,y+10);
       line(x+2,y+3,x+2,y+10);

       putpixel(x-3,y+10,BLUE);
       putpixel(x+3,y+10,BLUE);

       floodfill(x-3,y+9,BLUE);
       floodfill(x+3,y+9,BLUE);


       putpixel(x-3,y-3,EGA_LIGHTRED);
       putpixel(x+3,y-3,EGA_LIGHTRED);

       putpixel(x-3,y-2,EGA_LIGHTRED);
       putpixel(x+3,y-2,EGA_LIGHTRED);


       putpixel(x-4,y-3,EGA_LIGHTRED);
       putpixel(x+4,y-3,EGA_LIGHTRED);

       putpixel(x-4,y-2,EGA_LIGHTRED);
       putpixel(x+4,y-2,EGA_LIGHTRED);

       //mouth
       putpixel(x,y+2,EGA_LIGHTRED);
       putpixel(x-1,y+2,EGA_LIGHTRED);
       putpixel(x+1,y+2,EGA_LIGHTRED);

       putpixel(x-2,y+3,EGA_LIGHTRED);
       putpixel(x-3,y+3,EGA_LIGHTRED);
       putpixel(x-4,y+3,EGA_LIGHTRED);

       putpixel(x+2,y+3,EGA_LIGHTRED);
       putpixel(x+3,y+3,EGA_LIGHTRED);
       putpixel(x+4,y+3,EGA_LIGHTRED);



       putpixel(x-5,y+2,EGA_LIGHTRED);
       putpixel(x-6,y+2,EGA_LIGHTRED);
       putpixel(x-7,y+2,EGA_LIGHTRED);

       putpixel(x+5,y+2,EGA_LIGHTRED);
       putpixel(x+6,y+2,EGA_LIGHTRED);
       putpixel(x+7,y+2,EGA_LIGHTRED);



       putpixel(x-8,y+3,EGA_LIGHTRED);
       putpixel(x+8,y+3,EGA_LIGHTRED);

       }



       else if(!this->scared&&this->dead==0)
       {setcolor(this->color); setfillstyle(SOLID_FILL,this->color);


       pieslice(x,y,0,180,12);
       bar(x-12,y,x+12,y+6);

       line(x-12,y+4,x-12,y+10);

       line(x+12,y+4,x+12,y+10);

       line(x-12,y+10,x,y);
       line(x+12,y+10,x,y);

       floodfill(x-11,y+8,color);
       floodfill(x+11,y+8,color);


       line(x-8,y+3,x-4,y+10);
       line(x+8,y+3,x+4,y+10);


       line(x-2,y+3,x-2,y+10);
       line(x+2,y+3,x+2,y+10);

       putpixel(x-3,y+10,color);
       putpixel(x+3,y+10,color);

       floodfill(x-3,y+9,color);
       floodfill(x+3,y+9,color);
       }




       if(!this->scared)
       {

      eyes: setcolor(WHITE);
       setfillstyle(SOLID_FILL,WHITE);

       switch(mode)
       {
	case 3:

		fillellipse(x-5,y-2,3,4);
		fillellipse(x+5,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-2,x-4,y+2);
		putpixel(x-3,y-2,BLUE);
		putpixel(x-3,y-1,BLUE);
		putpixel(x-3,y,BLUE);
		putpixel(x-3,y+1,BLUE);


		bar(x+6,y-2,x+4,y+2);
		putpixel(x+3,y-2,BLUE);
		putpixel(x+3,y-1,BLUE);
		putpixel(x+3,y,BLUE);
		putpixel(x+3,y+1,BLUE);


	break;



	case 1:

		fillellipse(x-5,y-7,2,3);
		fillellipse(x+5,y-7,2,3);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-6,y-7,x-4,y-10);


		bar(x+6,y-7,x+4,y-10);

		break;
	case 4:


		fillellipse(x-7,y-2,3,4);
		fillellipse(x+3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x-10,y-3,x-8,y);


		bar(x+2,y-3,x,y);

		break;

	case 2:

		fillellipse(x+7,y-2,3,4);
		fillellipse(x-3,y-2,3,4);
		setcolor(BLUE);
		setfillstyle(SOLID_FILL,BLUE);

		bar(x+10,y-3,x+8,y);


		bar(x-2,y-3,x,y);


		break;

       }



       }

  }


    int ghost::toggleUpDown()
  {
     if(this->inbox==1)
     {
	 if(this->hitBottom==0&&this->y<182)
	 {
	     ++this->y;

	     if(this->y-10>154)
	     this->drawWithColors();

	     else this->correct(this->x,this->y);

	     drawAllCorners();
	     return 0;
	 }

	 else if(this->y==182&&this->hitBottom==0)
	 {
	   this->hitBottom=1;
	   this->drawWithColors();
	    return 0;
	 }

	 else if(this->hitBottom==1&&this->y>138)
	 {
	     this->correct(this->x,--this->y);
	     drawAllCorners();
	     return 0;

	 }

	 else if(this->y==138&&hitBottom==1)
	 {
	  this->dead=0;
	  this->scared=0;
	  this->hitBottom=0;
	  drawAllCorners();
	  this->inbox=0;

	  int two[]={2,4};

	  int choice=random(2);

	  this->mode=two[choice];



	  return 1;

	 }

     }


  return 1;}



  void pacman::scareAllGhosts()
  {
     for(int i=0;i<ghost::count;i++)
     gs[i]->scared=1;

  }


  int isAnyGhostDead(pacman& p)
  {  int res=0;

   for(int i=0;i<ghost::count;i++)
   {
      if( gs[i]->isDead(p))
      res=1;
    }
   return res;
  }

void main()
{      int  gd=DETECT,gm,i;

     //	path p1(125,125,250,125,MAGENTA,'H');

       //	path p2(260,150,260,250,MAGENTA,'V');

	int x=46,y=320,turn=1;



	token* t=new token[200];



       setGraph();

       path p1(13,211,100,211,MAGENTA,'H');
       path p2(528,210,618,210,MAGENTA,'H');
       path p3(117,164,117,189,MAGENTA,'V');
       path p4(117,228,117,256,MAGENTA,'V');
       path p5(512,160,512,185,MAGENTA,'V');
   //    path p6(510,232,510,257,MAGENTA,'V');
       path p7(137,275,220,275,MAGENTA,'H');
       path p8(49,275,99,275,MAGENTA,'H');
       path p9(24,293,24,309,MAGENTA,'V');
       path p10(118,293,118,309,MAGENTA,'V');
       path p11(243,293,243,309,MAGENTA,'V');
       path p12(239,171,239,254,MAGENTA,'V');
       path p13(44,330,97,330,MAGENTA,'H');
       path p14(143,330,221,330,MAGENTA,'H');
       path p15(200,150,223,150,MAGENTA,'H');
       path p16(178,168,178,198,MAGENTA,'V');
     //  path p17(238,118,238,133,MAGENTA,'V');
       path p18(117,113,117,128,MAGENTA,'V');
       path p19(24,112,24,128,MAGENTA,'V');
       path p20(322,277,341,277,MAGENTA,'H');
       path p21(385,279,428,279,MAGENTA,'H');
       path p22(540,277,581,277,MAGENTA,'H');
       path p23(319,331,431,331,MAGENTA,'H');
       path p24(524,331,585,331,MAGENTA,'H');
       path p25(457,136,491,136,MAGENTA,'H');
       path p26(380,136,412,136,MAGENTA,'H');
       path p27(261,134,336,134,MAGENTA,'H');
       path p28(146,97,218,97,MAGENTA,'H');
       path p29(47,97,84,97,MAGENTA,'H');
       path p30(267,97,337,97,MAGENTA,'H');
       path p31(392,97,468,97,MAGENTA,'H');
       path p32(540,97,588,97,MAGENTA,'H');
       path p33(43,149,83,149,MAGENTA,'H');
       path p34(535,143,584,143,MAGENTA,'H');
       path p35(393,237,458,237,MAGENTA,'H');
       path p36(609,119,609,128,MAGENTA,'V');
       path p37(609,299,609,313,MAGENTA,'V');
       path p38(362,157,362,214,MAGENTA,'V');
//       path p39(239,119,239,123,RED,'V');

	path p39(239,113,239,116,WHITE,'V');

//	path p40G(360,114,360,118,WHITE,'Y');



	//Setting turning points
	      // UP RIGHT DOWN LEFT
	turningPoint tp1(235,270,243,278);
    tp1.setWays(1,1,1,1);
		     //1111
	turningPoint tp2(238,146,246,154);
	tp2.setWays(1,0,1,1);
		      //1011

	turningPoint tp3(172,146,180,154);
	tp3.setWays(0,1,1,0);


	turningPoint tp4(172,212,180,220);
	tp4.setWays(1,0,0,0);

	turningPoint tp5(235,94,243,102);
	tp5.setWays(0,0,1,1);

	turningPoint tp6(235,324,243,332);
	tp6.setWays(1,0,0,1);

	turningPoint tp7(113,270,121,278);
	tp7.setWays(1,1,1,1);


	turningPoint tp8(113,205,121,213);
	tp8.setWays(1,0,1,1);

	turningPoint tp9(113,325,121,333);
	tp9.setWays(1,1,0,1);


	turningPoint tp10(113,143,121,151);
	tp10.setWays(1,0,1,1);


	turningPoint tp11(21,270,29,278);
	tp11.setWays(0,1,1,0);

	turningPoint tp12(21,325,29,333);
	tp12.setWays(1,1,0,0);


	turningPoint tp13(113,94,121,102);
	tp13.setWays(0,1,1,1);

	turningPoint tp14(20,94,28,102);
	tp14.setWays(0,1,1,0);

	turningPoint tp15(19,143,27,151);
	tp15.setWays(1,1,0,0);

	turningPoint tp16(293,327,301,335);
	tp16.setWays(1,1,0,0);



	turningPoint tp17(293,267,301,275);
	tp17.setWays(0,1,1,1);

	turningPoint tp18(359,267,367,275);
	tp18.setWays(1,1,0,1);


	turningPoint tp19(446,327,454,335);
	tp19.setWays(1,0,0,1);


	turningPoint tp20(446,278,454,286);
	tp20.setWays(0,1,1,1);


	turningPoint tp21(359,233,367,241);
	tp21.setWays(1,1,1,0);


	turningPoint tp22(235,129,243,137);
	tp22.setWays(1,1,1,0);


	turningPoint tp23(354,130,362,138);
	tp23.setWays(1,1,1,1);
				//   353,92  earlier
	turningPoint tp24(356,92,364,100);  //  repair needed
	tp24.setWays(0,1,1,1);

	turningPoint tp25(427,130,435,138);
	tp25.setWays(0,1,0,1);

	turningPoint tp26(507,138,515,146);
	tp26.setWays(1,1,1,1);

	turningPoint tp27(507,93,515,101);
	tp27.setWays(0,1,1,1);

	turningPoint tp28(605,93,613,101);
	tp28.setWays(0,0,1,1);

	turningPoint tp29(601,142,609,150);
	tp29.setWays(1,0,0,1);

	turningPoint tp30(507,205,515,213);
	tp30.setWays(1,1,1,0);

	turningPoint tp31(501,234,509,242);
	tp31.setWays(1,0,1,1);

	turningPoint tp32(500,276,508,284);
	tp32.setWays(1,1,1,1);


	turningPoint tp33(601,276,609,284); //somehow this gave up direction
	tp33.setWays(0,0,1,1);


	turningPoint tp34(500,326,508,334);
	tp34.setWays(1,1,0,0);


	turningPoint tp35(601,326,609,334);
	tp35.setWays(1,0,0,1);



	//done setting turning points







































	line1 l;


	//this is a simple rate variable to ensure that ghost move slowly
	//in form of cycles
	int ghostCycle=0;

clrscr();

randomize();

	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");

	pacman p(18,211,YELLOW,1);
				 //  last value is id in ghost()
	ghost g(240,225,EGA_CYAN,3,4);
	ghost g1(255,225,EGA_LIGHTMAGENTA,3,2);
	ghost g2(235,260,RED,1,1);
	ghost g3(250,128,BROWN,2,3);



	char input='1';

	setcolor(BLUE);



	//Drawing tokens for pacman to eat



	x=40;
	y=324;

	for(i=0;i<=10;i++,x+=20)
	{
		if(i==6)
		{
		 t[i].x=x;
	       t[i].y=y+6;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='B';

	       t[i].draw();

	       continue;


		}

	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}

	x=137;
	y=269;
	for(i=11;i<=15;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=47;
	y=269;
	for(i=16;i<=18;i++,x+=20)
	{


	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=115;
	y=113;
	for(i=19;i<=25;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}

	x=237;
	y=116;
	for(i=25;i<=32;i++,y+=20)
	{



	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}

		x=241;
	y=280;
	for(i=33;i<=34;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=116;
	y=257;
	for(i=35;i<=37;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=22;
	y=275;
	for(i=38;i<=40;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=22;
	y=97;
	for(i=41;i<=43;i++,y+=20)
	{
		if(i==43)
		{
		t[i].x=x+3;
	       t[i].y=y+6;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='B';

	       t[i].draw();

	       continue;

		}

	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=176;
	y=150;
	for(i=44;i<=47;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=360;
	y=157;
	for(i=48;i<=50;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=45;
	y=91;
	for(i=51;i<=79;i++,x+=20)
	{
	       if(i==62)
	       {
	       t[i].x=x;
	       t[i].y=y+6;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='B';

	       t[i].draw();


	       continue;
	       }

	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}

		x=296;
	y=325;
	for(i=80;i<=88;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=297;
	y=271;
	for(i=89;i<=104;i++,x+=20)
	{

		if(i==97)
		{
		t[i].x=x;
	       t[i].y=y+6;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='B';

	       t[i].draw();


		continue;
		}

	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=261;
	y=128;
	for(i=105;i<=109;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=535;
	y=137;
	for(i=110;i<=112;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=524;
	y=325;
	for(i=113;i<=115;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=43;
	y=143;
	for(i=116;i<=118;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}




		x=379;
	y=231;
	for(i=119;i<=124;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=198;
	y=144;
	for(i=125;i<=126;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=197;
	y=210;
	for(i=127;i<=127;i++,x+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=297;
	y=298;
	for(i=128;i<=128;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=510;
	y=117;
	for(i=129;i<=135;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=501;
	y=296;
	for(i=136;i<=137;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=360;
	y=221;
	for(i=138;i<=139;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=360;
	y=113;
	for(i=140;i<=141;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=607;
	y=108;
	for(i=142;i<=143;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



		x=607;
	y=291;
	for(i=143;i<=145;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}


		x=457;
	y=299;
	for(i=146;i<=146;i++,y+=20)
	{
	       t[i].x=x;
	       t[i].y=y;
	       t[i].color=EGA_LIGHTRED;
	       t[i].type='S';

	       t[i].draw();

	}



	//done drawing tokens

	//Drawing obstacles
	   //  h1.draw();
	   //  h2.draw();


	   displayAllH();
	   displayAllV();

     //	     v1.draw();
       //	     v2.draw();
	//Inital obstacles drawn

	setcolor(EGA_LIGHTRED);
	setfillstyle(SOLID_FILL,EGA_LIGHTRED);


   //	for(i=1;i<=40;i++,x+=12)
     //	{
      //	   outtextxy(x,y,".");
     //	}


  //	g.draw();


	putpixel(283,185,RED);
	putpixel(313,185,RED);
	putpixel(283,212,RED);
	putpixel(313,212,RED);


	p.showLives();



	while(input!='0')
	{
	    if(ghostCycle==0)
	   { //g.moveAroundOnItsOwn();

	  //  g.totallyOnTurn(tp1);
	    allGhostsMoveAround();
	    directAllGhosts();
	    }

	 //   ghostCycle=(ghostCycle+1)%2;

   //	 g.isDead(p);

   isAnyGhostDead(p);


	   if(kbhit())
	   {
	    input=getch();


	    if(input=='0')
	    break;

	    if(input=='o'||input=='O')
	    turn=2;
	    else if(input=='l'||input=='L')
	    turn=1;
	    else if(input=='g'||input=='G')
	    turn=3;

	    if(turn==1)

       l.input(input);

      else if(turn==2)
	 p.move(input);

	 else if(turn==3)
	      g.move(input);

		backToAll(p);
	 //     drawAllCorners();



	      checkTokensForPacman(p);

   //	    p1.backToPath(p);
    //	    p2.backToPath(p);



	    switch(input)
	  { case 'w':
	    case 'W':
	    case 's':
	    case 'S':
	    respectAllH(p);
	    break;
	    case 'a':
	    case 'A':
	    case 'D':
	    case 'd':
	     respectAllV(p);
	     break;
	   }



	//    g.move(input);



       //	    g1.move(input);
	//    g2.move(input);


     //	drawAllTokens();
     //	drawAllGhosts();
     //	correctAllGhosts();
       //	backToPathAllGhosts();
      //	drawAllTurningPoints();

 }

	     drawAllCorners();


	displayAllH();
	   displayAllV();

	if(stillDeadAnyOne())
       p.justDraw();

	drawAllTokens();
     //	drawAllGhosts();
	correctAllGhosts();
      backToPathAllGhosts();
// drawAllTurningPoints();

p.showScore();

	}

getch();
closegraph();}

