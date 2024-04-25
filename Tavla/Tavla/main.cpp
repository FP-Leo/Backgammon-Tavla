#include "glew.h"
#include "freeglut.h"
#include <iostream>

//DIKKAT: YAZDIGINIZ HER SEY ICIN YORUM KULLANIN. DIGERLERIN KODLARINI IYICE YORUM YAPMADAN DOKUNMAYIN. 
//SADECE ALANLARINDA KODLARINI YAZIN

//Prototip Alani

//Leo
void startingPosition();
int makeMove(int, int, int);
int checkMoveWhite(int, int, int);
int checkMoveBlack(int, int, int);

//Global Degisken Alani

//Leo
// 0 degeri - Beyaz, 1 ise siyah temsil eder. Beyaz tarafi 0dan 5'e kadar olan alanda toplicaktir. Siyah ise 18dan 23'e kadar olan alanda.
int colorArray[24] = { -1 };
int numberArray[24] = { 0 };
// Kimin halmesidir, 0 - beyaz, 1 - siyah
int toMove = 0;

int won = -1;

int outsideWhite = 0;
int whiteReadyToCollect = false;
int baseWhite = 0;
int collectedWhite = 0;

int outsideBlack = 0;
int blackReadyToCollect = false;
int baseBlack = 0;
int collectedBlack = 0;

//-------------------------------------------------------------------------------------------------------------------------------
//EREN NOKTA - gover: Tahta Tasarimi

void leftPocket(void) {
	// Sol Cep
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(15, 15); // sol alt
	glVertex2i(15, 205); // sol �st
	glVertex2i(35, 205); // sa� �st
	glVertex2i(35, 15); // sa� alt
	glEnd();


	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(20, 200); // sol alt
	glVertex2i(20, 116); // sol �st
	glVertex2i(30, 116); // sa� �st
	glVertex2i(30, 200); // sa� alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(20, 20); // sol alt
	glVertex2i(20, 104); // sol �st
	glVertex2i(30, 104); // sa� �st
	glVertex2i(30, 20); // sa� alt
	glEnd();
}

void rightPocket(void) {
	// Sa� 
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(187, 15); // sol alt
	glVertex2i(187, 205); // sol �st
	glVertex2i(205, 205); // sa� �st
	glVertex2i(205, 15); // sa� alt
	glEnd();


	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(190, 200); // sol alt
	glVertex2i(190, 116); // sol �st
	glVertex2i(200, 116); // sa� �st
	glVertex2i(200, 200); // sa� alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS); // y�kseklik 84 birim
	glVertex2i(190, 20); // sol alt
	glVertex2i(190, 104); // sol �st
	glVertex2i(200, 104); // sa� �st
	glVertex2i(200, 20); // sa� alt
	glEnd();

}

void drawFrame(void) {
	//Alt
	glLineWidth(16.0f); // Kal�nl�k belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(31, 18);
	glVertex2i(189, 18);
	glEnd();

	//Sa�
	glLineWidth(14.0f); // Kal�nl�k belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(187, 20);
	glVertex2i(187, 200);
	glEnd();

	//�st
	glLineWidth(16.0f); // Kal�nl�k belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i(189, 202);
	glVertex2i(31, 202);
	glEnd();

	//Sol
	glLineWidth(14.0f); // Kal�nl�k belirttim
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
	glVertex2i(35, 200); // sol �st
	glVertex2i(200, 200); // sa� �st
	glVertex2i(200, 20); // sa� alt
	glEnd();
}

void drawSplitter(float x_center) {

	glLineWidth(32.0f); // Kal�nl�k belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i((35.0f + 185.0f) / 2, 200);
	glVertex2i((35.0f + 185.0f) / 2, 20);
	glEnd();
}

void drawTriangles(float x_center) {
	float width = 185.0f - 35.0f; // 150
	float height = 200.0f - 20.0f;
	float triangleWidth = width / 12.8f; // 11.71 ortalama her bir ��genin geni�li�i
	float triangleHeight = height / 4.0f;

	for (int i = 0; i < 6; i++) {
		//Sol alt taraf ��genleri
		if (i % 2 == 0) {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		else {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_bottom_left = 35.0f + (triangleWidth * i); // Her bir ��gen i�in ba�lang�� de�eri 35 + triangleWidth * i olacak �ekilde yani = 35-46,7 , 46,7-58,4 aras�nda x de�erleri 
		glVertex2i(x_start_bottom_left, 20);
		glVertex2i(x_start_bottom_left + triangleWidth, 20);
		glVertex2i(x_start_bottom_left + triangleWidth / 2.0f, 105); // h =85 san�r�m 
		glEnd();

		//Ayr�ca alt taraf ��genleri i�in 35-20 , 46,7-20 , 35-105 , 46,7-105 �eklinde 
		// 
		// yani yukar�daki ��genlerin y noktalar� 115-199 aras�ndand�r
		// a�a��daki ��genlerin y noktalar� 20,105 aras�ndad�r

		// ��genlerin x noktalar�n� belirlerken
		// yukar�daki fonksiyondan yola ��karak 35 + ��gen geni�li�i ( ��genlerimiz 11.7 geni�li�indedir) * i ( ka��nc� ��gen oldu�u).
		// yani ilk ��gen i�in 35 - 46.7 aras�nda , 2.��gen i�in 46.7 ile 58.4 aras�nda ... ( Bu �ekilde devam etmektedir)
		// Bir index aral�� 11.7 birimdir ��nk� ��genlerimizin geni�li�i budur
		// ayr�ca Sol alt , Sa� alt , Sol �st ve Sa� �st olacak �ekilde 4 tane d�ng�den t�remi�tir 


		// X de�i�kenleri base noktalar�
		// Sol alt i�in ba�lang�� noktas� : 35.0f
		// Sa� alt i�in ba�lang�� noktas� : 115.0f
		// Sol �st i�in ba�lang�� noktas� : 35.0f 
		// Sa� �st i�in ba�lang�� noktas� : 115.0f 

		// Ayn� ��genler i�in y de�i�kenleri 
		// Sol alt i�in ba�lang�� Y noktas� : alt taraf noktalar� 20'den �st taraf ise 105'den 
		/*
				(35.0f,105.0f)					(46.7f,105.0f)


				(35.0f,20.0f)					(46.7f , 105.0f)

				bu alt taraf�n ilk ��geninin bulundu�u dikd�rtgene ait bilgilerdir.
				bir sonraki ��genin ba�langi� noktas� bir �nceki ��genin son 2 noktas�ndan ba�layacak �ekilde +11.7 'dir
				YAN�

				(46.7,105.0f)					(58.4,105.0f)

				(46.7,20.0f)					(58.4,105.0f)

				Bu �ekilde devam etmektedir
				Bu �ekilde sol alttaki 6 ��genin indexlerini bulabilirsiniz.



		*/




		// Sol �st taraf ��gen �izimleri
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
		//Sa� alt taraf ��gen �izimi
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

		// Sa� �st taraf ��gen �izimi
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

	float x_center = (35 + 185) / 2.0f; // TABLANIN MERKEZLER�N� HESAPLADIM  
	float y_center = (20 + 200) / 2.0f;

	drawSplitter(x_center);

	//Ucgen ciz 
	drawTriangles(x_center);



	glutSwapBuffers(); // Swap buffers for double buffering
}

//-------------------------------------------------------------------------------------------------------------------------------
//BAHA YOLAL - gover: Tas Tasrimi

//-------------------------------------------------------------------------------------------------------------------------------
//ERLINDI ISAJ - gorev: Zar Tasarimi 
// Angle of rotation
GLfloat angle = 0.0f;
GLboolean rotateFlag = GL_FALSE;
int dice1;
int dice2;


int randomNumber() {
	return rand() % 6 + 1;
}

/*
	int rollDice() {
		srand(time(0));
		int dice = randomNumber();
		return dice;
	}
*/




void drawText(float x, float y, float z, std::string text) {
	glRasterPos3f(x, y, z);

	for (char c : text) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}



void drawCube() {

	// glRotatef(angle, 1.0, 1.0, 1.0); // Rotate the cube
	// glTranslatef(0.0, 0.0, -5.0);

	 // Front face (blue)
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	// Back face (darker blue)
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.5);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.8); // Lighter shade
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glColor3f(0.0, 0.0, 0.6); // Medium shade
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3f(0.0, 0.0, 0.4); // Darker shade
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
	// drawText(-0.1, -0.1, 1.01, "5"); // Front face
   //  drawText(-0.1, -0.1, -1.01, "2"); // Back face
   //  drawText(1.01, -0.1, -0.1, "4"); // Right face
   //  drawText(-1.01, -0.1, -0.1, "3"); // Left face
   //  drawText(-0.1, 1.01, -0.1, "1"); // Top face
  //   drawText(-0.1, -1.01, -0.1, "6"); // Bottom face




}




void rollDice(int value) {
	angle += 10.f;
	if (angle > 360) {
		angle = 0;
		rotateFlag = GL_FALSE;
	}
	glutPostRedisplay();
	if (rotateFlag) {
		glutTimerFunc(15, rollDice, 0);
	}
}

void getDiceValues() {
	srand(static_cast<unsigned int>(std::time(nullptr)));
	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			dice1 = randomNumber();
		}
		else {
			dice2 = randomNumber();
		}
	}
	std::cout << dice1 << " " << dice2;
}




void keyboard(unsigned char Key, int x, int y) {
	switch (Key) {
	case 'r':
		getDiceValues();
		rotateFlag = GL_TRUE; // Start rotating
		glutTimerFunc(0, rollDice, 0);
		break;
	}
}



// Function to handle window resizing
void reshape(int width, int height) {
	if (height == 0) height = 1; // Prevent division by zero
	glViewport(0, 0, width, height); // Set the viewport to cover the entire window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
	glLoadIdentity(); // Reset the projection matrix
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); // Set the perspective
	glMatrixMode(GL_MODELVIEW); // Switch back to the model-view matrix
}



void displayDice() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(3.0f, 0.0f, -30.0f); //Position the First Dice
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	drawCube();

	glLoadIdentity();
	glTranslatef(6.0f, 0.0f, -30.0f); //Position the Second Dice
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	drawCube();

	glutSwapBuffers();
}



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
	if (targetSquare >= currentIndex)
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
	if (targetSquare <= currentIndex)
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

//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);  
    glutInitWindowSize(800, 600);     
    glutCreateWindow("Tavlla");

	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 222.0, 0.0, 220.0);
	glutDisplayFunc(display);




		// Erlindi
			//glutDisplayFunc(displayDice);
			//glutReshapeFunc(reshape);
			//glutKeyboardFunc(keyboard);

			//glEnable(GL_DEPTH_TEST);
			//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//////////////////////////////////////////  

    glutMainLoop();

    return 0;
}