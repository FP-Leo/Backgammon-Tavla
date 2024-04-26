#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <vector>

using namespace std;

//DIKKAT: YAZDIGINIZ HER SEY ICIN YORUM KULLANIN. DIGERLERIN KODLARINI IYICE YORUM YAPMADAN DOKUNMAYIN. 
//SADECE ALANLARINDA KODLARINI YAZIN

////Prototip Alani

//LEONIT SHABANI - 200401110
void startingPosition();
void makeMove(int);
int checkMoveWhite(int, int, int);
int checkMoveBlack(int, int, int);
int getIndex(float, float);
void mouseClick(int, int, int, int);
void drawDeadlockButton();
int checkDeadlock();
int checkDeadLockWhite();
int checkDeadLockBlack();

//Muhammet Eren NOKTA - 200401012 
void leftPocket(void);
void rightPocket(void);
void drawFrame(void);
void drawBackgammonBoard(void);
void drawSplitter(float x_center);
void drawTriangles(float x_center);
void display(void);

//Baha YOLAL - 200401031
void drawStones();
void drawStoneIndex(int);
void drawCircle(float, float, float);

void drawDiceAndTurnIndicator();
void handleDiceClick(int, int, int, int);
void drawMoveIndicators();

//Erlindi ISAJ - 200401114 
int randomNumber();
void drawCube();
void getDiceValues();
void rollDice1(int);
void rollDice2(int);
void rotateBasedOnValue_1();
void rotateBasedOnValue_2();
void display3D();
void dummyMouseFunc(int, int, int, int);
void dummyKeyboardFunc(unsigned char, int, int);
void keyboard(unsigned char, int, int);

////Global Degisken Alani

//Leonit SHABANI - 200401110
// 0 degeri - Beyaz, 1 ise siyah temsil eder. Beyaz tarafi 0dan 5'e kadar olan alanda toplicaktir. Siyah ise 18dan 23'e kadar olan alanda.
bool started = false;
int colorArray[28]; // 25 collectWhite, 26 outsideWhite, 27 outsideBlack, 28 collectBlack
int numberArray[28] = { 0 };
// Kimin halmesidir, 0 - beyaz, 1 - siyah
int toMove = 0;
// Zar atandı mı 
bool rolled = false;
// Zarlar ne dir
vector<int> diceToUse = {};

int won = -1;

int whiteReadyToCollect = false;
int baseWhite = 0;

int blackReadyToCollect = false;
int baseBlack = 0;

int clicked = 0;
int firstIndex = -1;

//Baha YOLAL - 200401031
const int NUM_VERTICES = 360; // Dairenin çözünürlügü
const float BOARD_WIDTH = 800.0f; // Tahta genişligi
const float BOARD_HEIGHT = 600.0f; // Tahta yüksekligi
const float STONE_RADIUS = 6.0f; // Tahta yüksekligi


float stonePositionsX[12] = { 179, 168.5, 156.5, 144.5, 132.5, 120.5, 100.5, 87.5, 76.5, 64.5, 52.5, 41 }; // Taşların X konumları
float collectedX = 195; // 
float outsideX = 25;
float stonePositionsYOne = 26.5; // Taşların Y konumları alt taraf
float stonePositionsYTwo = 193.5;// Taşların Y konumları ust taraf

//Erlindi ISAJ - 200401114

int dice1; // Random number for the first Dice
int dice2; // Random number for the second Dice
int currentView = 0;
int window3D = -1;
GLfloat angle1 = 0.0f;
GLfloat angle2 = 0.0f;
GLboolean rotateFlag1 = GL_FALSE;
GLboolean rotateFlag2 = GL_FALSE;

//-------------------------------------------------------------------------------------------------------------------------------
//Muhammet Eren NOKTA - 200401012, gover: Tahta Tasarimi

void leftPocket(void) {
	// Sol Cep
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(15, 15); // sol alt
	glVertex2i(15, 205); // sol üst
	glVertex2i(35, 205); // sað üst
	glVertex2i(35, 15); // sað alt
	glEnd();


	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(20, 200); // sol alt
	glVertex2i(20, 116); // sol üst
	glVertex2i(30, 116); // sað üst
	glVertex2i(30, 200); // sað alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(20, 20); // sol alt
	glVertex2i(20, 104); // sol üst
	glVertex2i(30, 104); // sað üst
	glVertex2i(30, 20); // sað alt
	glEnd();
}

void rightPocket(void) {
	// Sað 
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(187, 15); // sol alt
	glVertex2i(187, 205); // sol üst
	glVertex2i(205, 205); // sað üst
	glVertex2i(205, 15); // sað alt
	glEnd();


	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(190, 200); // sol alt
	glVertex2i(190, 116); // sol üst
	glVertex2i(200, 116); // sað üst
	glVertex2i(200, 200); // sað alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS); // yükseklik 84 birim
	glVertex2i(190, 20); // sol alt
	glVertex2i(190, 104); // sol üst
	glVertex2i(200, 104); // sað üst
	glVertex2i(200, 20); // sað alt
	glEnd();

}

void drawFrame(void) {
	//Alt
	glLineWidth(16.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(31, 18);
	glVertex2i(189, 18);
	glEnd();

	//Sað
	glLineWidth(14.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(187, 20);
	glVertex2i(187, 200);
	glEnd();

	//Üst
	glLineWidth(16.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(189, 202);
	glVertex2i(31, 202);
	glEnd();

	//Sol
	glLineWidth(14.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(33, 200);
	glVertex2i(33, 20);
	glEnd();

	leftPocket();
	rightPocket();
}

void drawBackgammonBoard(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(35, 20); // sol alt
	glVertex2i(35, 200); // sol üst
	glVertex2i(200, 200); // sað üst
	glVertex2i(200, 20); // sað alt
	glEnd();
}

void drawSplitter(float x_center) {

	glLineWidth(32.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i((35.0f + 185.0f) / 2, 200);
	glVertex2i((35.0f + 185.0f) / 2, 20);
	glEnd();
}

void drawTriangles(float x_center) {
	float width = 185.0f - 35.0f; // 150
	float height = 200.0f - 20.0f;
	float triangleWidth = width / 12.8f; // 11.71 ortalama her bir üçgenin geniþliði
	float triangleHeight = height / 4.0f;

	for (int i = 0; i < 6; i++) {
		//Sol alt taraf üçgenleri
		if (i % 2 == 0) {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		else {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_bottom_left = 35.0f + (triangleWidth * i); // Her bir üçgen için baþlangýç deðeri 35 + triangleWidth * i olacak þekilde yani = 35-46,7 , 46,7-58,4 arasýnda x deðerleri 
		glVertex2i(x_start_bottom_left, 20);
		glVertex2i(x_start_bottom_left + triangleWidth, 20);
		glVertex2i(x_start_bottom_left + triangleWidth / 2.0f, 105); // h =85 sanýrým 
		glEnd();

		//Ayrýca alt taraf üçgenleri için 35-20 , 46,7-20 , 35-105 , 46,7-105 þeklinde 
		// 
		// yani yukarýdaki üçgenlerin y noktalarý 115-199 arasýndandýr
		// aþaðýdaki üçgenlerin y noktalarý 20,105 arasýndadýr

		// Üçgenlerin x noktalarýný belirlerken
		// yukarýdaki fonksiyondan yola çýkarak 35 + üçgen geniþliði ( üçgenlerimiz 11.7 geniþliðindedir) * i ( kaçýncý üçgen olduðu).
		// yani ilk üçgen için 35 - 46.7 arasýnda , 2.üçgen için 46.7 ile 58.4 arasýnda ... ( Bu þekilde devam etmektedir)
		// Bir index aralýð 11.7 birimdir çünkü üçgenlerimizin geniþliði budur
		// ayrýca Sol alt , Sað alt , Sol üst ve Sað üst olacak þekilde 4 tane döngüden türemiþtir 


		// X deðiþkenleri base noktalarý
		// Sol alt için baþlangýç noktasý : 35.0f
		// Sað alt için baþlangýç noktasý : 115.0f
		// Sol üst için baþlangýç noktasý : 35.0f 
		// Sað üst için baþlangýç noktasý : 115.0f 

		// Ayný üçgenler için y deðiþkenleri 
		// Sol alt için baþlangýç Y noktasý : alt taraf noktalarý 20'den üst taraf ise 105'den 
		/*
				(35.0f,105.0f)					(46.7f,105.0f)


				(35.0f,20.0f)					(46.7f , 105.0f)

				bu alt tarafýn ilk üçgeninin bulunduðu dikdörtgene ait bilgilerdir.
				bir sonraki üçgenin baþlangiç noktasý bir önceki üçgenin son 2 noktasýndan baþlayacak þekilde +11.7 'dir
				YANÝ

				(46.7,105.0f)					(58.4,105.0f)

				(46.7,20.0f)					(58.4,105.0f)

				Bu þekilde devam etmektedir
				Bu þekilde sol alttaki 6 üçgenin indexlerini bulabilirsiniz.



		*/




		// Sol üst taraf üçgen çizimleri
		if (i % 2 == 0) {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		else {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_top_left = 35.0f + (triangleWidth * i);
		glVertex2i(x_start_top_left, 199);
		glVertex2i(x_start_top_left + triangleWidth, 199);
		glVertex2i(x_start_top_left + triangleWidth / 2.0f, 115); // h = 85
		glEnd();

	}

	for (int i = 0; i < 6; i++) {
		//Sað alt taraf üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		else {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_bottom_right = 115.0f + (triangleWidth * i);
		glVertex2i(x_start_bottom_right, 21);
		glVertex2i(x_start_bottom_right + triangleWidth, 21);
		glVertex2i(x_start_bottom_right + triangleWidth / 2.0f, 105);
		glEnd();

		// Sað üst taraf üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		else {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_top_right = 115.0f + (triangleWidth * i);
		glVertex2i(x_start_top_right, 199);
		glVertex2i(x_start_top_right + triangleWidth, 199);
		glVertex2i(x_start_top_right + triangleWidth / 2.0f, 115);
		glEnd();

	}

}

void display(void) {
	drawBackgammonBoard();
	drawFrame();
	

	float x_center = (35 + 185) / 2.0f; // TABLANIN MERKEZLERÝNÝ HESAPLADIM  
	float y_center = (20 + 200) / 2.0f;

	drawSplitter(x_center);

	//Ucgen ciz 
	drawTriangles(x_center);

	if (started == false) {
		startingPosition();
		started = true;
	}
	if (won != -1) {
		switch (won) {
			case 0: cout << "WHITE WON!" << endl; break;
			case 1: cout << "BLACK WON!" << endl; break;
		}
		glutMouseFunc(dummyMouseFunc);
		glutKeyboardFunc(dummyKeyboardFunc);
		drawStones();
		drawDiceAndTurnIndicator();
		drawDeadlockButton();
		return;
	}

	drawStones();
	drawDiceAndTurnIndicator();
	if (rolled == false) {
		glutMouseFunc(handleDiceClick);  // Register handleDiceClick ONLY when not rolled
	}
	else {
		drawMoveIndicators();
		glutMouseFunc(mouseClick);       // Register mouseClick when rolled
	}
	
	drawDeadlockButton();


	glutSwapBuffers(); // Swap buffers for double buffering
}

//-------------------------------------------------------------------------------------------------------------------------------
//Baha YOLAL - 200401031 - gover: Tas Tasrimi

void drawCircle(float x, float y, float radius) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < NUM_VERTICES; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(NUM_VERTICES);
		float dx = radius * cosf(theta);
		float dy = radius * sinf(theta);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

void drawStoneIndex(int index){
	int x;
	int y;
	int toAdd; 

	if (index < 12 && index >= 0) {
		x = stonePositionsX[index];
		y = stonePositionsYOne;
		toAdd = 2 * STONE_RADIUS;
	}
	else if ((index < 24 && index > 11)) {
		x = stonePositionsX[23-index];
		y = stonePositionsYTwo;
		toAdd = -2 * STONE_RADIUS;
	}
	else {
		return;
	}

	for (int i = 0; i < numberArray[index]; i++) {
		drawCircle(x, y+i*toAdd, STONE_RADIUS);
	}
}

void drawStones() {
	// Taşları çiz
	for (int i = 0; i < 24; i++) {
		switch(colorArray[i]){
			case 0: glColor3f(1.0, 1.0, 1.0); drawStoneIndex(i); break; // Beyaz
			case 1: glColor3f(0.0, 0.0, 0.0); drawStoneIndex(i); break; // Siyah
			default: break;
		}
	}
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < numberArray[24]; i++) {
		drawCircle(collectedX, stonePositionsYOne + 2 * i * STONE_RADIUS, STONE_RADIUS);
	}
	for (int i = 0; i < numberArray[25]; i++) {
		drawCircle(outsideX, stonePositionsYOne + 2 * i * STONE_RADIUS, STONE_RADIUS);
	}
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < numberArray[27]; i++) {
		drawCircle(collectedX, stonePositionsYTwo - 2 * i * STONE_RADIUS, STONE_RADIUS);
	}
	for (int i = 0; i < numberArray[26]; i++) {
		drawCircle(outsideX, stonePositionsYTwo - 2 * i * STONE_RADIUS, STONE_RADIUS);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//Erlindi ISAJ - 200401114 - gorev: Zar Tasarimi 
int randomNumber() {
	return rand() % 6 + 1;
}

void drawCube() {
	glBegin(GL_QUADS);

	// Front face
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Back face
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Right face
	glColor3f(0.25f, 0.25f, 0.25f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Left face
	glColor3f(0.65f, 0.65f, 0.65f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Top face
	glColor3f(0.65f, 0.65f, 0.65f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Bottom face
	glColor3f(0.25f, 0.25f, 0.25f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();

	// Draw black dots for dice pips
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);

	// Front face (one dot)
	glVertex3f(0.0f, 0.0f, 1.01f);

	// Back face (six dots) - arrange in a 2x3 grid
	glVertex3f(-0.5f, -0.5f, -1.01f);
	glVertex3f(0.5f, -0.5f, -1.01f);
	glVertex3f(-0.5f, 0.5f, -1.01f);
	glVertex3f(0.5f, 0.5f, -1.01f);
	glVertex3f(-0.5f, 0.0f, -1.01f);
	glVertex3f(0.5f, 0.0f, -1.01f);

	// Right face (four dots) - arrange in a 2x2 grid 
	glVertex3f(1.01f, -0.5f, -0.5f);
	glVertex3f(1.01f, 0.5f, -0.5f);
	glVertex3f(1.01f, -0.5f, 0.5f);
	glVertex3f(1.01f, 0.5f, 0.5f);

	// Left face (three dots) - arrange in a triangle
	glVertex3f(-1.01f, -0.5f, 0.0f);
	glVertex3f(-1.01f, 0.5f, -0.5f);
	glVertex3f(-1.01f, 0.5f, 0.5f);

	// Top face (five dots) - arrange in a quincunx pattern
	glVertex3f(-0.5f, 1.01f, -0.5f);
	glVertex3f(0.5f, 1.01f, -0.5f);
	glVertex3f(-0.5f, 1.01f, 0.5f);
	glVertex3f(0.5f, 1.01f, 0.5f);
	glVertex3f(0.0f, 1.01f, 0.0f);

	// Bottom face (two dots)
	glVertex3f(-0.5f, -1.01f, 0.0f);
	glVertex3f(0.5f, -1.01f, 0.0f);
	glEnd();

}

void getDiceValues() {
	if (rolled == true)
		return;
	srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
	dice1 = randomNumber();
	dice2 = randomNumber();
	diceToUse.push_back(dice1);
	diceToUse.push_back(dice2);
	if (dice1 == dice2) {
		diceToUse.push_back(dice1);
		diceToUse.push_back(dice2);
	}
	cout << "Dices rolled: " << dice1 << ", " << dice2 << endl;
}

void rollDice1(int value) {

	// Find the right Target Angle
	float targetAngle;
	if (dice1 == 1) targetAngle = 0;
	else if (dice1 == 2 || dice1 == 4) targetAngle = 240;
	else if (dice1 == 3 || dice1 == 5) targetAngle = 120;
	else targetAngle = 180;

	angle1 += 10.f;
	if (angle1 > targetAngle) {
		angle1 = targetAngle;
		rotateFlag1 = GL_FALSE;
	}
	glutPostRedisplay();
	if (rotateFlag1) {
		glutTimerFunc(25, rollDice1, 0);
	}

}

void rollDice2(int value) {

	// Find the right Target Angle
	float targetAngle;
	if (dice2 == 1) targetAngle = 0;
	else if (dice2 == 2 || dice2 == 4) targetAngle = 240;
	else if (dice2 == 3 || dice2 == 5) targetAngle = 120;
	else targetAngle = 180;

	angle2 += 10.f;
	if (angle2 > targetAngle) {
		angle2 = targetAngle;
		rotateFlag2 = GL_FALSE;
	}
	glutPostRedisplay();
	if (rotateFlag2) {
		glutTimerFunc(25, rollDice2, 0);
	}
}

void rotateBasedOnValue_1() {
	GLfloat xAxis;
	GLfloat yAxis;
	GLfloat zAxis;
	if (dice1 == 5 || dice1 == 4 || dice1 == 1) {
		xAxis = 1.0f;
		yAxis = 1.0f;
		zAxis = 1.0f;
	}
	else if (dice1 == 2 || dice1 == 3) {
		xAxis = 1.0f;
		yAxis = 1.0f;
		zAxis = -1.0f;
	}
	else {
		xAxis = 1.0f;
		yAxis = 0.0f;
		zAxis = 0.0f;
	}

	glRotatef(angle1, xAxis, yAxis, zAxis);
}

void rotateBasedOnValue_2() {
	GLfloat xAxis;
	GLfloat yAxis;
	GLfloat zAxis;
	if (dice2 == 5 || dice2 == 4 || dice2 == 1) {
		xAxis = 1.0f;
		yAxis = 1.0f;
		zAxis = 1.0f;
	}
	else if (dice2 == 2 || dice2 == 3) {
		xAxis = 1.0f;
		yAxis = 1.0f;
		zAxis = -1.0f;
	}
	else {
		xAxis = 1.0f;
		yAxis = 0.0f;
		zAxis = 0.0f;
	}

	glRotatef(angle2, xAxis, yAxis, zAxis);
}

void display3D() {

	glutSetWindow(window3D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	if (height == 0) height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);

	// Dice 1 (Zar 1)
	glLoadIdentity();
	glTranslatef(-2.0f, 0.0f, -10.0f); //Position the First Dice
	rotateBasedOnValue_1();
	drawCube();

	// Dice 2 (Zar 2)
	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -10.0f); //Position the Second Dice
	rotateBasedOnValue_2();
	drawCube();

	glutSwapBuffers();
}

void dummyMouseFunc(int button, int state, int x, int y) {}

void dummyKeyboardFunc(unsigned char key, int x, int y) {}

void keyboard(unsigned char Key, int x, int y) {
	switch (Key) {
	case 'r':
		getDiceValues();
		rolled = true;
		rotateFlag1 = GL_TRUE; // Start rotating Dice 1
		rotateFlag2 = GL_TRUE; // Start rotating Dice 2
		glutTimerFunc(0, rollDice1, 0);
		glutTimerFunc(0, rollDice2, 0);
		glutPostRedisplay(); // Redisplay the scene
		break;
	case 'd':
		glutDestroyWindow(window3D);
		glutKeyboardFunc(dummyKeyboardFunc);
		window3D = -1;
		cout << "(INCASE OF DEADLOCK PRESS THE RED BUTTON ABOVE THE BOARD)" << endl;
		break;
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//Leonit SHABANI - 200401110 - gorev: Oyun Mantigi

//Set up starting position
void startingPosition() {
	for (int i = 0; i < 28; i++) {
		colorArray[i] = -1;
	}
    //Beyaz
    colorArray[23] = 0; colorArray[12] = 0; colorArray[7] = 0; colorArray[5] = 0;
    numberArray[23] = 2; numberArray[12] = 5; numberArray[7] = 3; numberArray[5] = 5;
	baseWhite = 5;

    //Siyah
    colorArray[0] = 1; colorArray[11] = 1; colorArray[16] = 1; colorArray[18] = 1;
    numberArray[0] = 2; numberArray[11] = 5; numberArray[16] = 3; numberArray[18] = 5;
	baseBlack = 5;

	// Extra
	colorArray[24] = 0; colorArray[25] = 0; colorArray[26] = 1; colorArray[27] = 1;
	numberArray[24] = 0; numberArray[25] = 0; numberArray[26] = 0; numberArray[27] = 0;
}

void makeMove(int clickedIndex) {
	int result = 0;
	switch (toMove) {
	case 0:
		for (int i = 0; i < diceToUse.size(); i++) {
			result = checkMoveWhite(firstIndex, diceToUse[i], clickedIndex);
			if (result == 1) {
				diceToUse.erase(diceToUse.begin() + i);
				glutPostRedisplay();
				if (diceToUse.empty()) {
					toMove = !toMove;
					rolled = false;
				}
				if (numberArray[24] == 15) won = 0;
				break;
			}
		}
		break;
	case 1:
		for (int i = 0; i < diceToUse.size(); i++) {
			result = checkMoveBlack(firstIndex, diceToUse[i], clickedIndex);
			if (result == 1) {
				diceToUse.erase(diceToUse.begin() + i);
				glutPostRedisplay();
				if (diceToUse.empty()) {
					toMove = !toMove;
					rolled = false;
				}
				if (numberArray[27] == 15) won = 1;
				break;
			}
		}
		break;
	}
}

int checkMoveWhite(int currentIndex, int rolledNumber, int targetSquare) {
	if (targetSquare >= currentIndex)
		return 0;
	else if (numberArray[25] > 0) {
		if (currentIndex != 25)
			return 0;
		if (rolledNumber != 24 - targetSquare)
			return 0;
		if (colorArray[targetSquare] == 1) {
			if (numberArray[targetSquare] > 1) {
				return 0;
			}
			numberArray[targetSquare]--;
			numberArray[26]++;
			blackReadyToCollect = false;
			baseBlack--;
		}
		numberArray[25]--;
		colorArray[targetSquare] = 0;
		numberArray[targetSquare]++;
		return 1;
	}
	else if (targetSquare >= 0 && targetSquare <= 23 && currentIndex - rolledNumber == targetSquare) {
		if (colorArray[targetSquare] == 1) {
			if (numberArray[targetSquare] > 1) {
				return 0;
			}
			numberArray[targetSquare]--;
			colorArray[targetSquare] = 0;
			numberArray[26]++;
			blackReadyToCollect = false;
			if (targetSquare >= 18 && targetSquare <= 23) {
				baseBlack--;
			}
		}

		numberArray[targetSquare]++;
		colorArray[targetSquare] = 0;

		if (targetSquare <= 5 && currentIndex > 5)
			baseWhite++;
		if (baseWhite + numberArray[24] == 15)
			whiteReadyToCollect = true;
	}else if (targetSquare == 24) {
		if (!whiteReadyToCollect)
			return 0;
		if (currentIndex - rolledNumber < 0) {
			numberArray[24]++;
			baseWhite--;
		}
	}else {
		return 0;
	}

	numberArray[currentIndex]--;
	if (numberArray[currentIndex] == 0) {
		colorArray[currentIndex] = -1;
	}

	return 1;
}

int checkMoveBlack(int currentIndex, int rolledNumber, int targetSquare) {
	if (targetSquare <= currentIndex)
		return 0;
	else if (numberArray[26] > 0) {
		if (currentIndex != 26)
			return 0;
		if (rolledNumber - 1 != targetSquare)
			return 0;
		if (colorArray[targetSquare] == 0) {
			if (numberArray[targetSquare] > 1) {
				return 0;
			}
			numberArray[targetSquare]--;
			numberArray[25]++;
			whiteReadyToCollect = false;
			baseWhite--;
		}
		numberArray[26]--;
		colorArray[targetSquare] = 1;
		numberArray[targetSquare]++;
		return 1;
	}
	else if (targetSquare >= 0 && targetSquare <= 23 && currentIndex + rolledNumber == targetSquare) {
		if (colorArray[targetSquare] == 0) {
			if (numberArray[targetSquare] > 1) {
				return 0;
			}
			numberArray[25]++;
			numberArray[targetSquare]--;
			whiteReadyToCollect = false;
			if (targetSquare >= 0 && targetSquare <= 5) {
				baseWhite--;
			}
		}

		numberArray[targetSquare]++;
		colorArray[targetSquare] = 1;

		if (targetSquare >= 18 && currentIndex < 18)
			baseBlack++;
		if (baseBlack + numberArray[27] == 15)
			blackReadyToCollect = true;
	}
	else if (targetSquare == 27) {
		if (!blackReadyToCollect)
			return 0;
		if (currentIndex + rolledNumber > 23) {
			numberArray[27]++;
			baseBlack--;
		}
	}
	else {
		return 0;
	}

	numberArray[currentIndex]--;
	if (numberArray[currentIndex] == 0) {
		colorArray[currentIndex] = -1;
	}
	return 1;
}

int getIndex(float x, float y) {
	int col = -1;
	if (x >= 35 && x < 106) {
		if (x < 47) {
			col = 11;
		}
		else if (x < 59){
			col = 10;
		}
		else if (x < 71) {
			col = 9;
		}
		else if (x < 82) {
			col = 8;
		}
		else if (x < 94) {
			col = 7;
		}
		else {
			col = 6;
		}
	}
	else if( x >= 115 && x < 186){
		if (x < 127) {
			col = 5;
		}
		else if (x < 139) {
			col = 4;
		}
		else if (x < 150) {
			col = 3;
		}
		else if (x < 162) {
			col = 2;
		}
		else if (x < 174) {
			col = 1;
		}
		else {
			col = 0;
		}
	}
	else {
		if (x >= 190 && x <= 200)
			col = 13;
		else if (x >= 19 && x <= 29)
			col = 14;
		else
			return -1;
	}
	if (y <= 105 && y >= 20) {
		if (col == 13 || col == 14)
			return col + 11;
		return col;
	}
	else if (y <= 200 && y >= 115) {
		if (col == 13 || col == 14)
			return col + 13;
		return 23 - col;
	}
	else {
		return -1;
	}
}

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Convert window coordinates to OpenGL coordinates
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		GLdouble modelview[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		GLdouble projection[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		GLfloat winX = (float)x;
		GLfloat winY = (float)viewport[3] - (float)y;
		GLdouble posX, posY, posZ;
		gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

		// Print the clicked coordinates
		cout << "Index: " << getIndex(posX, posY) << endl;

		if (window3D != -1) {
			cout << "Please destroy the dice window! ( BY PRESSING D )" << endl;
			return;
		}

		if (posX >= 100 && posX <= 120 && posY >= 210 && posY <= 220) {
			cout << "Checking Deadlock" << endl;
			firstIndex = -1; // Reset firstIndex
			if (checkDeadlock() == 0) { // Call the deadlock check function
				cout << "Deadlock Found! Skipping turn!" << endl;
				diceToUse.clear();
				toMove = !toMove;
				rolled = false;
				glutPostRedisplay();
				return;
			}
			cout << "No Deadlock Found!" << endl;
			glutPostRedisplay(); // Redraw the scene
			return;
		}

		int clickedIndex = getIndex(posX, posY);
		if (clickedIndex == -1) {
			cout << "Error! Index Reset!!" << endl;
			return;
		}
		if (firstIndex == -1 ) {
			if (colorArray[clickedIndex] == toMove) {
				firstIndex = clickedIndex;
			}
			else {
				cout << "Error! Index Reset!!" << endl;
				return;
			}
		}
		else {
			cout << "Base, Collected ,ready to collect - ";
			switch (toMove) {
				case 0: cout << "(WHITE)" << baseWhite << ", " << numberArray[24] << ", " << boolalpha << whiteReadyToCollect << endl; break;
				case 1: cout << "(BLACK)" << baseBlack << ", " << numberArray[27] << ", " << boolalpha << blackReadyToCollect << endl; break;
			}
			makeMove(clickedIndex);
			firstIndex = -1;
			cout << "Index Reset!!" << endl;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
void drawDiceAndTurnIndicator() {
	// Black frame for die - Positioned outside the board with padding
	glColor3f(0.0f, 0.0f, 0.0f); // Black frame
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(210, 80);  // Smaller frame for die
	glVertex2i(210, 90);
	glVertex2i(220, 90);
	glVertex2i(220, 80);
	glEnd();

	// Die face square (static) - Smaller square
	glColor3f(1.0f, 1.0f, 1.0f); // White background
	glBegin(GL_QUADS);
	glVertex2i(212, 82);
	glVertex2i(212, 88);
	glVertex2i(218, 88);
	glVertex2i(218, 82);
	glEnd();

	// Draw dots representing a static die face (e.g., showing 1)
	glColor3f(0.0f, 0.0f, 0.0f); // Black dots
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2i(215, 85);  // Center dot
	glEnd();

	// Turn indicator frame - Positioned outside the board with padding
	glColor3f(0.0f, 0.0f, 0.0f); // Black frame
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(210, 110);  // Adjusted y position
	glVertex2i(210, 120);
	glVertex2i(220, 120);
	glVertex2i(220, 110);
	glEnd();

	// Turn indicator square - Smaller square
	if (toMove == 0) {
		glColor3f(1.0f, 1.0f, 1.0f); // White for white's turn
	}
	else {
		glColor3f(0.0f, 0.0f, 0.0f); // Black for black's turn
	}
	glBegin(GL_QUADS);
	glVertex2i(212, 112);
	glVertex2i(212, 118);
	glVertex2i(218, 118);
	glVertex2i(218, 112);
	glEnd();
}

void drawMoveIndicators() {
	// Move indicator rectangles (red) - Below the die square, vertical with spacing
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	for (int i = 0; i < diceToUse.size(); i++) {
		glBegin(GL_QUADS);
		glVertex2i(210 + i * 3, 130); // Added spacing between rectangles
		glVertex2i(212 + i * 3, 130);
		glVertex2i(212 + i * 3, 132);
		glVertex2i(210 + i * 3, 132);
		glEnd();
	}
}

void handleDiceClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		GLdouble modelview[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		GLdouble projection[16];
		glGetDoublev(GL_PROJECTION_MATRIX, projection);

		GLfloat winX = (float)x;
		GLfloat winY = (float)viewport[3] - (float)y;
		GLdouble posX, posY, posZ;

		gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

		// Check if click is within EITHER square (die or turn indicator)
		if (posX >= 210 && posX <= 220 && posY >= 80 && posY <= 90) { // Die square
			cout << "Please ROLL the dices! ( BY PRESSING R )" << endl;
			window3D = glutCreateWindow("Zar - 3D");
			glutDisplayFunc(display3D);
			glutReshapeWindow(300, 200);
			glutKeyboardFunc(keyboard);

			//display3D();  // Generate random numbers
			//glutPostRedisplay(); // Redraw
		}
	}
}

void drawDeadlockButton() {
	// Draw a red square above the triangles
	glColor3f(1.0f, 0.0f, 0.0f); // Red color
	glBegin(GL_QUADS);
	glVertex2i(100, 210);  // Adjust position as needed
	glVertex2i(100, 220);
	glVertex2i(120, 220);
	glVertex2i(120, 210);
	glEnd();
}

int checkDeadlock() {
	switch (toMove) {
		case 0: return checkDeadLockWhite(); break;
		case 1: return checkDeadLockBlack(); break;
	}
}

int checkSquareAvailability(int targetIndex, int color) {
	if (targetIndex < 0 && targetIndex > 23)
		return 0;
	if (color != 0 && color != 1)
		return 0;
	if (colorArray[targetIndex] == !color && numberArray[targetIndex] > 1) {
		return 0;
	}
	return 1;
}

int checkDeadLockWhite() {
	int available = 0;
	if (numberArray[25] > 0) {
		for (int i = 0; i < diceToUse.size(); i++) {
			available = checkSquareAvailability(24-diceToUse[i], 0);
		}
		return available;
	}
	if (whiteReadyToCollect) {
		for (int i = 0; i < diceToUse.size(); i++) {
			if (colorArray[i-1] == 0)
				return 1;
		}
	}
	for (int i = 0; i < 24; i++) {
		if (colorArray[i] == 0) {
			for (int j = 0; j < diceToUse.size(); j++) {
				if (checkSquareAvailability(i - j, 0)){
					available = 1;
					break;
				}
			}
			if (available) return available;
		}
	}
}

int checkDeadLockBlack() {
	int available = 0;
	if (numberArray[26] > 0) {
		for (int i = 0; i < diceToUse.size(); i++) {
			available = checkSquareAvailability(diceToUse[i-1], 1);
		}
		return available;
	}
	if (whiteReadyToCollect) {
		for (int i = 0; i < diceToUse.size(); i++) {
			if (colorArray[24 - i] == 1)
				return 1;
		}
	}
	for (int i = 0; i < 24; i++) {
		if (colorArray[i] == 0) {
			for (int j = 0; j < diceToUse.size(); j++) {
				if (checkSquareAvailability(i + j, 1)) {
					available = 1;
					break;
				}
			}
			if (available) return available;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);  
    glutInitWindowSize(BOARD_WIDTH, BOARD_HEIGHT);
    glutCreateWindow("Tavla");

	glClearColor(0.9f, 0.9f, 0.8f, 1.0f);
	gluOrtho2D(0.0, 222.0, 0.0, 220.0);
	startingPosition();
	glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}