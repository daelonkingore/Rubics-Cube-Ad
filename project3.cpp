/*=================================================================
COURSE: CSC 525/625, Project 3
PROGRAMMERS: 
Daelon Kingore (20%) - base code, info instructions, rotations
Ashton Barnwell (20%) - designed base cube, presentation
Ethan Gardner (20%) - popup ad bubble, assisted presentation
Matthew Henningsen (20%) - axes on/off menu option, assisted presentation
Jonathan Adzick (20%) - assisted with base cube, added lines and color to form Rubik's cube
MODIFIED BY: Daelon Kingore, Ashton Barnwell, Ethan Gardner,
Matthew Henningsen, and Jonathan Adzick
LAST MODIFIED DATE: 12/08/2022
DESCRIPTION: This program is to use 3D rendering with OpenGl's library functions
to create an advertisement for a product
NOTES: The product we chose was a rubrik's cube
FILES: project3.cpp, (labProject.sln)
IDE/COMPILER: Microsoft Visual Studio 2019
INSTRUCTION FOR COMPILATION AND EXECUTION:
1. Double click on labProject.sln (the solution file in my VS project) to OPEN the project
2. Press Ctrl+F7 to COMPILE
3. Press Ctrl+F5 to EXECUTE
=================================================================*/

#include <iostream>
#include <string>
#include <GL/glut.h>				// include GLUT library
using namespace std;

//********* Prototypes **************************************************************
void myInit();
void myInit2(); // for info
void myDisplayCallback();
void myDisplayCallback2();

//********* Draw Prototypes **************************************************************
void drawAxes();
void drawCube(); 
void drawLines();
void drawAll();

// menu related prototypes
void menu(int num);
void createMenu();
void displayMenuPicks();

// info window prototypes
void createInfoWindow();
void infoInformation();
void infoMenu(int num);
void displayInfoMenuPicks();
void createInfoMenu();
int displayInfoRasterText(string infoText, int infoY);

// global vars
int submenuId, submenuId2, submenuId3, menuId, value, axesOn=0, textIncrement=0, infoValue, infoMenuId;
bool infoWindowExists = true, neverClosed = true;
static int window, infoWindow; // windows
GLfloat vertices[8][3] = {
		{75,75, 75},
		{75,-75, 75},
		{75, 75, -75},
		{75,-75, -75},
		{-75, 75, -75},
		{-75,-75, -75},
		{-75, 75, 75},
		{-75, -75, 75} };

//********* Subroutines *************************************************************
int main(int argc, char** argv)
{
	glutInit(&argc, argv);					// initialization

	glutInitWindowSize(600, 400);				// specify a window size
	glutInitWindowPosition(100, 100);			// specify a window position

	glutInitDisplayMode(GLUT_DEPTH);
	glutCreateWindow("Project 3");	// create a titled window
	
	glEnable(GL_DEPTH_TEST); // for using Z-buffer

	myInit();									// specify some settings
	createMenu();

	glutDisplayFunc(myDisplayCallback);		// register a callback

	createInfoWindow(); // launch the second info window initially

	glutMainLoop();							// get into an infinite loop

	return 1;									// something wrong happened
}

//***********************************************************************************
void createInfoWindow() { // this function creates a second window for the info screen
	infoWindowExists = true;
	value = 0;
	glutInitWindowSize(500, 300);				// specify a window size
	glutInitWindowPosition(700, 100);			// specify a window position
	infoWindow = glutCreateWindow("Info");	// create a titled window
	myInit2();
	createInfoMenu();
	glutDisplayFunc(myDisplayCallback2);		// register a callback
}

// set value to determine direction and axes affected
void menu(int num) {
	value = num;
	myDisplayCallback();
}

// design the menu for the main window
void createMenu() {
	// X-axes rotations
	submenuId = glutCreateMenu(menu);
	glutAddMenuEntry("Negative Direction (CW)", 1);
	glutAddMenuEntry("Positive Direction (CCW)", 2);
	// Y-axes rotations
	submenuId2 = glutCreateMenu(menu);
	glutAddMenuEntry("Negative Direction (CW)", 3);
	glutAddMenuEntry("Positive Direction (CCW)", 4);
	// Z-axes rotations
	submenuId3 = glutCreateMenu(menu);
	glutAddMenuEntry("Negative Direction (CW)", 5);
	glutAddMenuEntry("Positive Direction (CCW)", 6);
	// main menu
	menuId = glutCreateMenu(menu);
	glutAddSubMenu("Rotate on X-axes by 45 degrees", submenuId); // x-axes submenu
	glutAddSubMenu("Rotate on Y-axes by 45 degrees", submenuId2); // y-axes submenu
	glutAddSubMenu("Rotate on Z-axes by 45 degrees", submenuId3); // z-axes submenu
	glutAddMenuEntry("Turn On/Off Axes", 9); // turn the axes on or off
	glutAddMenuEntry("Open Info Window", 10);
	glutAddMenuEntry("Reset Polygon", 7);
	glutAddMenuEntry("Close Window", 8);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//***********************************************************************************
void drawInformation()
{
	// vertex's of the shape (zig-zag popup)
	GLfloat vertex1[2] = { 50, 80 };
	GLfloat vertex2[2] = { 30, 110 };
	GLfloat vertex3[2] = { 60, 110 };
	GLfloat vertex4[2] = { 80, 130 };
	GLfloat vertex5[2] = { 110, 120 };
	GLfloat vertex6[2] = { 135, 135 };
	GLfloat vertex7[2] = { 160, 110 };
	GLfloat vertex8[2] = { 200, 110 };
	GLfloat vertex9[2] = { 180, 80 };
	GLfloat vertex10[2] = { 200, 50 };
	GLfloat vertex11[2] = { 160, 50 };
	GLfloat vertex12[2] = { 135, 30 };
	GLfloat vertex13[2] = { 110, 40 };
	GLfloat vertex14[2] = { 80, 30 };
	GLfloat vertex15[2] = { 60, 45 };
	GLfloat vertex16[2] = { 30, 50 };

	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);

	glVertex2fv(vertex1);
	glVertex2fv(vertex2);
	glVertex2fv(vertex3);
	glVertex2fv(vertex4);
	glVertex2fv(vertex5);
	glVertex2fv(vertex6);
	glVertex2fv(vertex7);
	glVertex2fv(vertex8);
	glVertex2fv(vertex9);
	glVertex2fv(vertex10);
	glVertex2fv(vertex11);
	glVertex2fv(vertex12);
	glVertex2fv(vertex13);
	glVertex2fv(vertex14);
	glVertex2fv(vertex15);
	glVertex2fv(vertex16);

	glEnd();

	// Print the text
	void* font = GLUT_BITMAP_9_BY_15;
	// array that holds different ad slogans
	string textArr[4] = { "A fun andstimulatingactivity!", " Rubik's    Cube!", "   43    Quintillion Combos!", "Good for a wandering mind!"};
	string text = textArr[textIncrement]; // get one slogan based on increment
	if (textIncrement == 3) {
		textIncrement = 0;
	}
	else {
		textIncrement += 1;
	}
	int textLength = text.length();
	int xPos = 68;
	int yPos = 90;
	glColor3f(0.0, 0.0, 0.0);

	for (int i = 0; i < textLength; i++) { // loop throw text and print
		glRasterPos2i(xPos, yPos);
		glutBitmapCharacter(font, text[i]);

		xPos += 10;
		if (i == 8) {  // Start a new line
			yPos -= 15;
			xPos = 60;
		}
		else if (i == 19) { // Start a new line
			yPos -= 15;
			xPos = 68;
		}
	}

}

//***********************************************************************************
void displayMenuPicks() {
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-100, 0, 0); // push the cube over to the left side of the window

	// rotate x-axes CW
	if (value == 1) {
		glRotatef(-45, 1.0f, 0.0f, 0.0f);
	}
	// rotate x-axes CCW
	else if (value == 2) {
		glRotatef(45, 1.0f, 0.0f, 0.0f);
	}
	// rotate y-axes CW
	else if (value == 3) {
		glRotatef(-45, 0.0f, 1.0f, 0.0f);
	}
	// rotate y-axes CCW
	else if (value == 4) {
		glRotatef(45, 0.0f, 1.0f, 0.0f);
	}
	// rotate z-axes CW
	else if (value == 5) {
		glRotatef(-45, 0.0f, 0.0f, 1.0f);
	}
	// rotate z-axes CCW
	else if (value == 6) {
		glRotatef(45, 0.0f, 0.0f, 1.0f);
	}
	// reset polygon
	else if (value == 7) {
		glLoadIdentity();
		glTranslatef(-100, 0, 0);
	}
	// destroys the window and exits the program
	else if (value == 8) {
		glutDestroyWindow(window);
		exit(0);
	}
	// turns on/off the axes
	else if (value == 9) {
		if (axesOn) {
			axesOn = 0;
		}
		else {
			axesOn = 1;
		}
	}
	// displays the destroyed info window if it needs to
	else if (value == 10) {
		if (!infoWindowExists) { // if the window is destroyed, create it
			neverClosed = false;
			drawAll();
			createInfoWindow();
		}
	}
	// reset value and redraw the cube and axes
	value = 0;
	drawAll();
}

//***********************************************************************************
void drawAll() { // calls all the draw functions at once
	drawCube();
	drawLines();
	glTranslatef(100, 0, 0); // puts the axes back to the center of the window
	glPushMatrix();
	glLoadIdentity();
	drawInformation();
	glPopMatrix();
	if (axesOn) {
		drawAxes();
	}
}

//***********************************************************************************
void drawLines() {
	GLfloat lineVertices[48][3] = {
		//Front
		{75, 25, 76}, {-75, 25, 76},
		{75, -25, 76}, {-75, -25, 76},
		{25,-75, 76}, {25, 75, 76},
		{-25, -75, 76}, {-25, 75, 76},
		//Back
		{75, 25, -76}, {-75, 25, -76},
		{75, -25, -76}, {-75, -25, -76},
		{25,-75, -76}, {25, 75, -76},
		{-25, -75, -76}, {-25, 75, -76}, 
		//right
		{76, 25, 76},{76, 25, -76},
		{76, -25, 76}, {76, -25, -76},
		{76, -76, 25}, {76, 76, 25},
		{76, -76, -25}, {76, 76, -25},
		//left
		{-76, 25, 76},{-76, 25, -76},
		{-76, -25, 76}, {-76, -25, -76},
		{-76, -76, 25}, {-76, 76, 25},
		{-76, -76, -25}, {-76, 76, -25},
		//Top
		{75, 76, 25},{-75, 76, 25},
		{75, 76, -25}, {-75, 76, -25},
		{25, 76, -75}, {25, 76, 75},
		{-25, 76, 75}, {-25, 76, -75},
		//Bottom
		{75, -76, 25}, {-75, -76, 25},
		{75, -76, -25}, {-75, -76, -25},
		{25,-76, -75}, {25, -76, 75},
		{-25, -76, -75}, {-25, -76, 75}
		};
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_LINES);
	//front
	glColor3f(0.0, 0.0, 0.0);
	glVertex3fv(lineVertices[0]);
	glVertex3fv(lineVertices[1]);
	glVertex3fv(lineVertices[2]);
	glVertex3fv(lineVertices[3]);
	glVertex3fv(lineVertices[4]);
	glVertex3fv(lineVertices[5]);
	glVertex3fv(lineVertices[6]);
	glVertex3fv(lineVertices[7]);
	//back
	glVertex3fv(lineVertices[8]);
	glVertex3fv(lineVertices[9]);
	glVertex3fv(lineVertices[10]);
	glVertex3fv(lineVertices[11]);
	glVertex3fv(lineVertices[12]);
	glVertex3fv(lineVertices[13]);
	glVertex3fv(lineVertices[14]);
	glVertex3fv(lineVertices[15]);
	//Right
	glVertex3fv(lineVertices[16]);
	glVertex3fv(lineVertices[17]);
	glVertex3fv(lineVertices[18]);
	glVertex3fv(lineVertices[19]);
	glVertex3fv(lineVertices[20]);
	glVertex3fv(lineVertices[21]);
	glVertex3fv(lineVertices[22]);
	glVertex3fv(lineVertices[23]);
	//Left
	glVertex3fv(lineVertices[24]);
	glVertex3fv(lineVertices[25]);
	glVertex3fv(lineVertices[26]);
	glVertex3fv(lineVertices[27]);
	glVertex3fv(lineVertices[28]);
	glVertex3fv(lineVertices[29]);
	glVertex3fv(lineVertices[30]);
	glVertex3fv(lineVertices[31]);
	//Top
	glVertex3fv(lineVertices[32]);
	glVertex3fv(lineVertices[33]);
	glVertex3fv(lineVertices[34]);
	glVertex3fv(lineVertices[35]);
	glVertex3fv(lineVertices[36]);
	glVertex3fv(lineVertices[37]);
	glVertex3fv(lineVertices[38]);
	glVertex3fv(lineVertices[39]);
	//Bottom
	glVertex3fv(lineVertices[40]);
	glVertex3fv(lineVertices[41]);
	glVertex3fv(lineVertices[42]);
	glVertex3fv(lineVertices[43]);
	glVertex3fv(lineVertices[44]);
	glVertex3fv(lineVertices[45]);
	glVertex3fv(lineVertices[46]);
	glVertex3fv(lineVertices[47]);
	glEnd();
}
//***********************************************************************************
void drawCube() {
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_POLYGON);
	// Front
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[7]);
	glEnd();

	glBegin(GL_POLYGON);
	// Back
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[3]);
	glEnd();

	glBegin(GL_POLYGON);
	// Left
	glColor3f(1.0, 0.0, 1.0);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[1]);
	glEnd();

	glBegin(GL_POLYGON);
	// Right
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[5]);
	glEnd();

	glBegin(GL_POLYGON);
	// Top
	glColor3f(0.0, 1.0, 1.0);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[2]);
	glEnd();

	glBegin(GL_POLYGON);
	// Bottom
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[3]);
	glEnd();
}

//***********************************************************************************
void drawAxes()
{
	// X axis
	void* font = GLUT_BITMAP_8_BY_13;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3i(185, 0, 0);
	glutBitmapCharacter(font, 'X');

	// Y axis
	glRasterPos3i(0, 185, 0);
	glutBitmapCharacter(font, 'Y');

	// Z axis
	glRasterPos3i(0, 0, 185);
	glutBitmapCharacter(font, 'Z');

	// axis lines
	glPointSize(1);
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x = -175; x <= 175; x++) // draw X-axis
		glVertex3i(x, 0, 0);
	for (int y = -175; y <= 175; y++) // draw Y-axis
		glVertex3i(0, y, 0);
	for (int z = -175; z <= 175; z++) // draw Z-axis
		glVertex3i(0, 0, z);
	glEnd();
}


//***********************************************************************************
void infoMenu(int num) {
	infoValue = num; // the value of the info menu option the user clicked
	myDisplayCallback2(); // must be called to hide or close the info window
}

//***********************************************************************************
void createInfoMenu() {
	infoMenuId = glutCreateMenu(infoMenu); // create menu and log the id
	// menu entries
	glutAddMenuEntry("Close Window", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//***********************************************************************************
void infoInformation() { // this function contains all the info information displayed to the user
	string welcomeMsg = "Welcome to this interactive Rubik's Cube Ad!";
	string controls = "To control the Rubik's cube, simply right click to show the  menu.";
	string controlsContinued = "The first 3 menu options will open a sub menu to rotate the  Rubrik's cube on the chosen axis.";
	string otherMenuOptions = "The other menu options are explicitly labeled with what they do.";
	string hideInfoMenu = "Right click the info window to show the 'close' option to    close this window.";
	string openInfoMenu = "If the info menu is closed, right click the main window and  select 'Open Info Window'.";
	int infoY = 240;

	// call the display fuction to display the above strings
	infoY = displayInfoRasterText(welcomeMsg, infoY);
	infoY = displayInfoRasterText(controls, infoY - 26);
	infoY = displayInfoRasterText(controlsContinued, infoY - 26);
	infoY = displayInfoRasterText(otherMenuOptions, infoY - 26);
	infoY = displayInfoRasterText(hideInfoMenu, infoY - 26);
	infoY = displayInfoRasterText(openInfoMenu, infoY - 26);
}

//***********************************************************************************
int displayInfoRasterText(string infoText, int infoY) { // this funciton displays the information to the user
	glPushMatrix();
	if (!neverClosed) { // translate for the main window causes the info window to need to be translated back
		glTranslatef(-100, 0, 0);
	}

	glColor3f(0.0, 0.0, 0.0); // color black
	int infoX = -240; // every line should start at -190

	// loop through string and print every character
	for (int i = 0; i < infoText.size(); i++) {
		// go down a line once the x values reach the end
		if (infoX > 241) {
			infoX = -240;
			infoY -= 26;
		}
		// get position and display letter
		glRasterPos2i(infoX, infoY);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, infoText[i]);
		infoX += 8;
	}
	glFlush();
	glPopMatrix();
	return infoY; // return the y value for the above function to use
}

//***********************************************************************************
void displayInfoMenuPicks() {
	// if the menu option is 2, close the window
	if (infoValue == 2) {
		infoWindowExists = false;
		glutDestroyWindow(infoWindow);
	}
	infoValue = 0;
}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	glMatrixMode(GL_PROJECTION); // use projection to determine matrix view area
	glOrtho(-300, 300, -200, 200, -400, 400);  // specify a viewing volume
	gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
}

//***********************************************************************************
void myInit2()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white
	gluOrtho2D(-250, 250, -100, 250);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	glClear(GL_DEPTH_BUFFER_BIT);   // for using Z-buffer
	displayMenuPicks();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void myDisplayCallback2() // this function is the callback for the second window
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	infoInformation();	// raster text that needs to be displayed
	displayInfoMenuPicks(); // detect menu inputs

	glFlush(); // flush out the buffer contents
}