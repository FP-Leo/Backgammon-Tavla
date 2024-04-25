#include "glew.h"
#include "freeglut.h"
#include <iostream>

using namespace std;

//DIKKAT: YAZDIGINIZ HER SEY ICIN YORUM KULLANIN. DIGERLERIN KODLARINI IYICE YORUM YAPMADAN DOKUNMAYIN. 
//SADECE ALANLARINDA KODLARINI YAZIN

//Prototip Alani

//Leo
void startingPosition();
int makeMove(int, int, int);
int checkMoveWhite(int, int, int);
int checkMoveBlack(int, int, int);
int getIndex(float, float);
void mouseClick(int, int, int, int);

//Baha
void drawStones();
void drawStoneIndex(int);
void drawCircle(float, float, float);


void rollDice();
void drawDiceAndTurnIndicator();
void handleDiceClick(int, int, int, int);
void drawMoveIndicators();

//Global Degisken Alani

//Leo
// 0 degeri - Beyaz, 1 ise siyah temsil eder. Beyaz tarafi 0dan 5'e kadar olan alanda toplicaktir. Siyah ise 18dan 23'e kadar olan alanda.
int colorArray[24] = { -1 };
int numberArray[24] = { 0 };
// Kimin halmesidir, 0 - beyaz, 1 - siyah
int toMove = 0;
bool rolled = false;
int rolledDicedOne = 0;
int rolledDicedTwo = 0;
int numberOfMoves = 0;

int won = -1;

int outsideWhite = 0;
int whiteReadyToCollect = false;
int baseWhite = 0;
int collectedWhite = 0;

int outsideBlack = 0;
int blackReadyToCollect = false;
int baseBlack = 0;
int collectedBlack = 0;

int clicked = 0;
int firstIndex = -1;
int secondIndex = -1;

//Baha
const int NUM_VERTICES = 360; // Dairenin çözünürlügü
const float BOARD_WIDTH = 800.0f; // Tahta genişligi
const float BOARD_HEIGHT = 600.0f; // Tahta yüksekligi
const float STONE_RADIUS = 6.0f; // Tahta yüksekligi


float stonePositionsX[12] = { 179, 167, 155, 143, 131, 119, 99, 87, 75, 63, 51, 39 }; // Taşların X konumları, diger 12 konumlari soldan saga
float stonePositionsYOne = 27; // Taşların Y konumları alt taraf
float stonePositionsYTwo = 194;

//-------------------------------------------------------------------------------------------------------------------------------
//EREN NOKTA - gover: Tahta Tasarimi

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

	drawStones();
	drawDiceAndTurnIndicator();
	if (rolled == false) {
		glutMouseFunc(handleDiceClick);  // Register handleDiceClick ONLY when not rolled
	}
	else {
		drawMoveIndicators();
		glutMouseFunc(mouseClick);       // Register mouseClick when rolled
	}
	


	glutSwapBuffers(); // Swap buffers for double buffering
}

//-------------------------------------------------------------------------------------------------------------------------------
//BAHA YOLAL - gover: Tas Tasrimi


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
	else if (index < 24 && index > 11) {
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
}

//-------------------------------------------------------------------------------------------------------------------------------
//ERLINDI ISAJ - gorev: Zar Tasarimi 

//-------------------------------------------------------------------------------------------------------------------------------
//LEONIT SHABANI - gorev: Oyun Mantigi

//Set up starting position
void startingPosition() {
    //Beyaz
    colorArray[23] = 0; colorArray[12] = 0; colorArray[7] = 0; colorArray[5] = 0;
    numberArray[23] = 2; numberArray[12] = 5; numberArray[7] = 3; numberArray[5] = 5;
	baseWhite = 5;

    //Siyah
    colorArray[0] = 1; colorArray[11] = 1; colorArray[16] = 1; colorArray[18] = 1;
    numberArray[0] = 2; numberArray[11] = 5; numberArray[16] = 3; numberArray[18] = 5;
	baseBlack = 5;
}

int makeMove(int currentIndex, int rolledNumber, int targetSquare) {
	int result = 0;
	switch (toMove) {
		case 0: result = checkMoveWhite(currentIndex, rolledNumber, targetSquare); break;
		case 1: result = checkMoveBlack(currentIndex, rolledNumber, targetSquare); break;
	}
	if (result == 1) {
		switch (toMove) {
			case 0: if (collectedWhite == 13) won = 0; break;
			case 1: if (collectedBlack == 13) won = 1; break;
		}
	}
	return result;
}

int checkMoveWhite(int currentIndex, int rolledNumber, int targetSquare) {
	if (colorArray[currentIndex] == 1)
		return 0;
	else if (targetSquare >= currentIndex)
		return 0;
	else if (outsideWhite > 0) {

	}
	else if (colorArray[targetSquare] != 0) {
		if (numberArray[targetSquare] > 1) {
			return 0;
		}
		colorArray[targetSquare] = 0;
		outsideBlack++;
		blackReadyToCollect = false;
		if (targetSquare >= 18 && targetSquare <= 23) {
			baseBlack--;
		}
	}
	else if (targetSquare < 0) {
		if (!whiteReadyToCollect)
			return 0;
		if (currentIndex - rolledNumber <= 0) {
			collectedWhite++;
			baseWhite--;
		}
	}
	else if (targetSquare > 23) {
		return 0;
	}
	else if (currentIndex - rolledNumber == targetSquare) {
		numberArray[targetSquare]++;
		colorArray[targetSquare] = 0;
		if (targetSquare <= 5 && targetSquare >= 0)
			baseWhite++;
	}

	numberArray[currentIndex]--;
	if (numberArray[currentIndex] == 0) {
		colorArray[currentIndex] = -1;
	}

	return 1;
}

int checkMoveBlack(int currentIndex, int rolledNumber, int targetSquare) {
	if (colorArray[currentIndex] == 0)
		return 0;
	else if (targetSquare <= currentIndex)
		return 0;
	else if (outsideBlack > 0) {

	}
	else if (colorArray[targetSquare] != 1) {
		if (numberArray[targetSquare] > 1) {
			return 0;
		}
		colorArray[targetSquare] = 1;
		outsideWhite++;
		whiteReadyToCollect = false;
		if (targetSquare >= 0 && targetSquare <= 5) {
			baseWhite--;
		}
	}
	else if (targetSquare > 23) {
		if (!blackReadyToCollect)
			return 0;
		if (currentIndex + rolledNumber >= 23) {
			collectedBlack++;
			baseBlack--;
		}
	}
	else if (targetSquare < 0) {
		return 0;
	}
	else if (currentIndex + rolledNumber == targetSquare) {
		numberArray[targetSquare]++;
		colorArray[targetSquare] = 1;
		if (targetSquare >= 18 && targetSquare <= 23) {
			baseBlack++;
		}
	}

	numberArray[currentIndex]--;
	if (numberArray[currentIndex] == 0) {
		colorArray[currentIndex] = -1;
	}
	return 1;
}

int getIndex(float x, float y) {
	cout << "x: " << x << ", y: " << y << endl;
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
		return col;
	}
	if (y <= 105 && y >= 20) {
		return col;
	}
	else if (y <= 200 && y >= 115) {
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

		// TODO: Perform any necessary actions based on the clicked coordinates,
		// such as identifying the clicked game piece or board location.

	}
}

//----------------------------------------------------------------------------------------------------------------------------------



void rollDice() {
	rolledDicedOne = rand() % 6 + 1;  // Generate random numbers between 1 and 6
	rolledDicedTwo = rand() % 6 + 1;
	numberOfMoves = (rolledDicedOne == rolledDicedTwo) ? 4 : 2; // 4 moves if same, else 2
	cout << "Rolled: " << rolledDicedOne << " and " << rolledDicedTwo << endl;
}

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
	for (int i = 0; i < numberOfMoves; i++) {
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
			rollDice();  // Generate random numbers
			rolled = true;
			glutPostRedisplay(); // Redraw
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