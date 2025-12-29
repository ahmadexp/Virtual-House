const float version = 5.8;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#ifndef _WIN32
#include <unistd.h>  // for usleep
#endif

#include "testapp.h"
#include "platform_audio.h"
#include <cstdlib>

int screenw=800;
int screenh=600;
float screenfov=60;          //the field of view
float screenaspect=16.f/9.f;
double elapsedtime=0;
double elapseddist=0;
double expectdist=0;
double starttime=0;
double start_time=0;
double start_move_time=0;
bool not_moved=1;
double motion_time=0;
bool starttimeflag=1;
float turn_duration = 40;
int countdownjoystickstart=0;

char win_clue;

float camxpos,camypos,camzpos;
float camxang,camyang,camzang,tmpcamyang;
float camxposmov,camyposmov,camzposmov;
float camxangmov,camyangmov,camzangmov;
int trial=1;
int latency=1;
int sound_delay=10;
bool kidmode=0;
bool animal_background_sound=0;
float JoyAngVel=2.36;
float JoyTransVel=0.1;
float InOutRatio=1;

int lang=1;   // 1=English 2=Spanish 3=French 4=German

#define max_latency 1000
int control_buffer[4][max_latency];
int latency_write_pointer=0;
int latency_read_pointer=0;
int stairtype=3;   //1=stairs at 180degrees, 2=stairs at 90 degrees, 3=ramp at 180degrees, 4=ramp at 90 degrees, 5=double stairs at 180degrees, 6= double ramps at 180degrees

//int temp;

const char mediadir[] = "Media/";
const char* logfilename="default.txt";
const char* total_logfilename="total.txt";
char logfilename_2[100];
FILE * pFile;
FILE * pFile_2;
FILE * pFile_3;


#include "generic.h"
#include "gamespecific/tilenames.h"
#include "setup.h"
#include "judgement.h"
#include "play.h"
#include "drawworld.h"
#include "drawhud.h"


// instantiate the class
TestApp app;

//-----------------------------------------------------------------------------
// Description: Constructor
//-----------------------------------------------------------------------------
TestApp::TestApp(){
	// set window title for Win32/Linux

	char windowtitle[64];
	snprintf(windowtitle, sizeof(windowtitle), "%s[Version %.1f]","The Virtual House ",version);
	strcpy(mStartupInfo.mWindowTitle, windowtitle);
	// enable antialiasing
	mDispInfo.mAntiAlias = false;
}

//-----------------------------------------------------------------------------
// Description: Initialization callback
//-----------------------------------------------------------------------------
bool TestApp::onInit(int argc, char **ppArgv){
	// printf("DEBUG: onInit called with argc=%d\n", argc);
	// fflush(stdout);
	
	// Use default logfilename if no arguments provided, OR
	// if first argument doesn't start with '/' (which indicates a command flag)
	// Note: argc/ppArgv here exclude the program name (see FWGLFWMain.cpp)
	if(argc>0 && ppArgv && ppArgv[0] && ppArgv[0][0] != '/') {
		// printf("DEBUG: Setting logfilename to ppArgv[0]='%s'\n", ppArgv[0]);
		// fflush(stdout);
		logfilename=ppArgv[0];
	}
	
	// printf("DEBUG: Starting argument loop\n");
	// fflush(stdout);
	
	// Loop starts at 0 because main() already skipped program name (argc-1, &ppArgv[1])
	for(int i=0;i<argc;i++){
		if(!ppArgv[i]) continue;  // Safety check
		
		if(!strcmp(ppArgv[i],"/NOINFO")) showinfo=0;
		if(!strcmp(ppArgv[i],"/TESTMODE")) testmode=1;
		if(!strcmp(ppArgv[i],"/SHOWPLAYER")) showplayer=1;
		if(!strcmp(ppArgv[i],"/USEMOUSE")) freecamera=1;
		if(!strcmp(ppArgv[i],"/AUTOEXIT")) autoexit=1;
		if(!strcmp(ppArgv[i],"/USEJOYSTICK")) countdownjoystickstart=5;
		if(!strcmp(ppArgv[i],"/TRIAL") && i+1<argc && ppArgv[i+1]) trial=atoi(ppArgv[i+1]);                    
		if(!strcmp(ppArgv[i],"/LATENCY") && i+1<argc && ppArgv[i+1]) latency=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/ALLOCENTRIC")) allocentric=1;
		if(!strcmp(ppArgv[i],"/JOYANGVEL") && i+1<argc && ppArgv[i+1]) JoyAngVel*=atof(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/JOYTRANSVEL") && i+1<argc && ppArgv[i+1]) JoyTransVel*=atof(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/LANGUAGE") && i+1<argc && ppArgv[i+1]) lang*=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/INOUTRATIO") && i+1<argc && ppArgv[i+1]) InOutRatio*=atof(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/KIDMODE")) kidmode=1;
		if(!strcmp(ppArgv[i],"/ANIMSOUND")) animal_background_sound=1;
		if(!strcmp(ppArgv[i],"/PERPSTAIR") && i+1<argc && ppArgv[i+1]) stairtype=atoi(ppArgv[i+1]);
		if(!strcmp(ppArgv[i],"/LOGTOTAL") && i+1<argc && ppArgv[i+1]) total_logfilename=ppArgv[i+1];
		if(!strcmp(ppArgv[i],"/NOTEXTURE")) usetextures=0;
		if(!strcmp(ppArgv[i],"/TURNDURATION") && i+1<argc && ppArgv[i+1]) turn_duration=atof(ppArgv[i+1]);
	}
	
	// printf("DEBUG: Finished argument loop\n");
	// fflush(stdout);

#ifdef _WIN32
	ShowCursor(0);  // added to hide the mouse cursor
#endif

	// printf("DEBUG: About to process testmode\n");
	// fflush(stdout);

	if(testmode)
	{
		showinfo=0;
		countdownjoystickstart=5;
	}

	// printf("DEBUG: About to init control_buffer\n");
	// fflush(stdout);

	for(int temp1=0;temp1<4;temp1++)
		for(int temp2=0;temp2<max_latency;temp2++)
			control_buffer[temp1][temp2]=0;

	// printf("DEBUG: About to open log files, logfilename='%s'\n", logfilename ? logfilename : "NULL");
	// fflush(stdout);

	pFile = fopen (logfilename,"w");
	
	// printf("DEBUG: About to sprintf logfilename_2\n");
	// fflush(stdout);
	
	snprintf(logfilename_2, sizeof(logfilename_2), "%s%s",logfilename,"_Int.txt");
	
	// printf("DEBUG: After sprintf, logfilename_2='%s'\n", logfilename_2);
	// fflush(stdout);
	
	pFile_2 = fopen ((char *)logfilename_2,"w");
	
	// printf("DEBUG: Opened pFile_2, about to check trial\n");
	// fflush(stdout);
	
	if(trial==1)
		pFile_3 = fopen ((char *)total_logfilename,"w");		//open a new total file
	else if(trial>1)
		pFile_3 = fopen ((char *)total_logfilename,"a");		//append to the existing total file
	
	// printf("DEBUG: Past file opening, calling srand\n");
	// fflush(stdout);
	
	srand(time(NULL));
	//////////////////////////////locked on x windows per requested by Zahra
	/*
	if(allocentric)
		targetwin=(int)(trial-1)%3;
	else
		targetwin=(int)rand()%3;
	*/
	targetwin=1;
	///////////////////////////////////////

	// printf("DEBUG: About to call FWGLApplication::onInit\n");
	// fflush(stdout);

	FWGLApplication::onInit(argc, ppArgv);
	
	// printf("DEBUG: Called FWGLApplication::onInit, setting up OpenGL\n");
	// fflush(stdout);
	
	glEnable(GL_DEPTH_TEST);
	
	glDepthFunc(GL_LESS);
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepthf(1000.f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.0f);
	
	// printf("DEBUG: OpenGL setup done, calling srand again\n");
	// fflush(stdout);
	
	srand((int)time(NULL));
	
	printf("DEBUG: About to call bindcontrols()\n");
	fflush(stdout);
	
	// Try-catch to debug bindcontrols crash
	try {
		bindcontrols();
		printf("DEBUG: bindcontrols() succeeded\n");
	} catch (...) {
		printf("ERROR: bindcontrols() threw exception\n");
	}
	fflush(stdout);
	gamestate=0;
	lastgamestate=0;
	menustate=0;
	waitforscreenrefresh=0;
	return true;
}

//-----------------------------------------------------------------------------
// Description: Update callback
//-----------------------------------------------------------------------------
bool TestApp::onUpdate(){

	// printf("DEBUG: TestApp::onUpdate() entered\n");
	// fflush(stdout);

	//get frame rate and adjust game speed
	FWTimeVal time=FWTime::getCurrentTime();
	
	// printf("DEBUG: got current time\n");
	// fflush(stdout);
	
	if(starttimeflag){
		starttimeflag=0;
		starttime=(double)time;
	}
	elapsedtime=((double)time-starttime);
	fFPS=1.f/(float)(time-mLastTime);
	mLastTime=time;
	float gamespeed=60.f/fFPS;
	if(gamespeed<0.01)gamespeed=0.01;
	if(gamespeed>2.0)gamespeed=2.0;

	// printf("DEBUG: calculated frame rate, fFPS=%f gamespeed=%f\n", fFPS, gamespeed);
	// fflush(stdout);

	int templastgamestate;
	int templastmenustate;
	if(!waitforscreenrefresh){
		templastgamestate=gamestate;
		templastmenustate=menustate;
	}

	// printf("DEBUG: about to check gamestate, gamestate=%d\n", gamestate);
	// fflush(stdout);

	if(waitforscreenrefresh){//damn you screen buffering
	}else if(gamestate==0){//load the loading screen
		// printf("DEBUG: gamestate 0 - calling setuptext()\n");
		// fflush(stdout);
		setuptext();
		gamestate=1;
	}else if(gamestate==1){//loading screen for media
		// printf("DEBUG: gamestate 1 - setting up media\n");
		// fflush(stdout);
		setupbuttons();
		setupmedia();
		skybox = new SKYBOX();
		skybox->Initialize();
		gamestate=3;
	}else if(gamestate==3){//setup the game world
		setupgame();
		gamestate=4;
	}else if(gamestate==4){//play
			play(gamespeed);
	}

	if(!waitforscreenrefresh){
		lastgamestate=templastgamestate;
		lastmenustate=templastmenustate;
		if(gamestate==1)waitforscreenrefresh=1;
		if(gamestate==3)waitforscreenrefresh=1;
	}else{
		waitforscreenrefresh=0;
	}

	return true;

}

//-----------------------------------------------------------------------------
// Description: Render callback
//-----------------------------------------------------------------------------
void TestApp::onRender(){

	//clear screen and set the viewport to the full screen
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,(GLsizei)screenw,(GLsizei)screenh);

	//draw the loading text
	if(gamestate==1 || gamestate==3){
		set2dcamera();
		switch(lang){
			case 1:
				drawtextcentered(0,0,(char*)"Loading Virtual House...",5);
				break;
			case 2:
				drawtextcentered(0,0,(char*)"Chargement Virtuelle Maison...",5);
				break;
			case 3:
				drawtextcentered(0,0,(char*)"Cargando Casa Virtual...",5);
				break;
			case 4:
				drawtextcentered(0,0,(char*)"Virtuelle Haus Aufladung...",5);
				break;
		}
		unset2dcamera();
	}
	//draw the game world
	if(gamestate==4){
		set3dcamera(
			camxpos,camypos,camzpos,
			camxang,camyang,camzang,
			screenfov,screenaspect);
		drawworld();
		set2dcamera();
		drawhud();
		unset2dcamera();
	}

}

//-----------------------------------------------------------------------------
// Description: Resize callback
//-----------------------------------------------------------------------------
void TestApp::onSize(const FWDisplayInfo &dispInfo){
	FWGLApplication::onSize(dispInfo);
	screenw = dispInfo.mWidth;
	screenh = dispInfo.mHeight;
	screenaspect = (float)screenw/(float)screenh;
}

//-----------------------------------------------------------------------------
// Description: Shutdown callback
//-----------------------------------------------------------------------------
void TestApp::onShutdown(){
	unbindcontrols();
	skybox->Finalize();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	fclose (pFile);
	fprintf(pFile_2,"_______________________________________________________________________________________________________________________\n");
	fclose (pFile_2);
	fclose (pFile_3);
}
