#include "glew.h"
#include "freeglut.h"
#include <iostream>

//DIKKAT: YAZDIGINIZ HER SEY ICIN YORUM KULLANIN. DIGERLERIN KODLARINI IYICE YORUM YAPMADAN DOKUNMAYIN. 
//SADECE ALANLARINDA KODLARINI YAZIN

//Prototip Alani

//Leo
void startingPosition();
int checkMove(int, int, int);

//Global Degisken Alani

//Leo
// 0 degeri - Beyaz, 1 ise siyah temsil eder. Beyaz tarafi 0dan 5'e kadar olan alanda toplicaktir. Siyah ise 18dan 23'e kadar olan alanda.
int colorArray[24] = { -1 };
int numberArray[24] = { 0 };
// Kimin halmesidir, 0 - beyaz, 1 - siyah
int toMove = 0;

int outsideWhite = 0;
int whiteReadyToCollect = false;
int collectedWhite = 0;

int outsideBlack = 0;
int blackReadyToCollect = false;
int collectedBlack = 0;

//-------------------------------------------------------------------------------------------------------------------------------
//EREN NOKTA - gover: Tahta Tasarimi


void solCep(void) {
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
	glVertex2i(20, 125); // sol üst
	glVertex2i(30, 125); // sað üst
	glVertex2i(30, 200); // sað alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(20, 20); // sol alt
	glVertex2i(20, 100); // sol üst
	glVertex2i(30, 100); // sað üst
	glVertex2i(30, 20); // sað alt
	glEnd();
}
void sagCep(void) {
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
	glVertex2i(190, 125); // sol üst
	glVertex2i(200, 125); // sað üst
	glVertex2i(200, 200); // sað alt
	glEnd();

	glColor3f(0.7215686274509804f, 0.5411764705882353f, 0.0f);
	glPointSize(5.0f);

	glBegin(GL_QUADS);
	glVertex2i(190, 20); // sol alt
	glVertex2i(190, 100); // sol üst
	glVertex2i(200, 100); // sað üst
	glVertex2i(200, 20); // sað alt
	glEnd();

}
void cerceveCiz(void) {
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

	solCep();
	sagCep();




}
void tablaCiz(void) {
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
void ortaCubukCiz(float x_center) {

	glLineWidth(32.0f); // Kalýnlýk belirttim
	glColor3f(0.4f, 0.1960f, 0.0f); // Kahve
	glBegin(GL_LINES);
	glVertex2i((35.0f + 185.0f) / 2, 200);
	glVertex2i((35.0f + 185.0f) / 2, 20);
	glEnd();
}
void ucgenCiz(float x_center) {
	float width = 185.0f - 35.0f;
	float height = 200.0f - 20.0f;
	float triangleWidth = width / 12.8f;
	float triangleHeight = height / 4.0f;



	for (int i = 0; i < 6; i++) {
		//Alt tarafa üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		else {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		glBegin(GL_TRIANGLES);
		float x_start = 35.0f + (triangleWidth * i);
		glVertex2i(x_start, 20);
		glVertex2i(x_start + triangleWidth, 20);
		glVertex2i(x_start + triangleWidth / 2.0f, 105); // h =85 sanýrým 
		glEnd();

		// Üst tarafa üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		else {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_top = 185.0f + (triangleWidth * i);
		glVertex2i(x_start, 199);
		glVertex2i(x_start + triangleWidth, 199);
		glVertex2i(x_start + triangleWidth / 2.0f, 115); // h = 85
		glEnd();

	}

	for (int i = 0; i < 6; i++) {
		//Alt tarafa üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		else {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		glBegin(GL_TRIANGLES);
		float x_start = (35.0f + 185.0f) / 2 + 5 + (triangleWidth * i);
		glVertex2i(x_start, 21);
		glVertex2i(x_start + triangleWidth, 21);
		glVertex2i(x_start + triangleWidth / 2.0f, 105);
		glEnd();

		// Üst tarafa üçgen çizimi
		if (i % 2 == 0) {
			glColor3f(0.6745098039215687f, 0.6784313725490196f, 0.5137254901960784f);
		}
		else {
			glColor3f(1.0f, 0.2784313725490196f, 0.09803921568627451f);
		}
		glBegin(GL_TRIANGLES);
		float x_start_top = 185.0f + (triangleWidth * i);
		glVertex2i(x_start, 199);
		glVertex2i(x_start + triangleWidth, 199);
		glVertex2i(x_start + triangleWidth / 2.0f, 115);
		glEnd();

	}

}
void display(void) {
	tablaCiz();
	cerceveCiz();

	float x_center = (35 + 185) / 2.0f; // TABLANIN MERKEZLERÝNÝ HESAPLADIM  
	float y_center = (20 + 200) / 2.0f;

	ortaCubukCiz(x_center);

	//Ucgen ciz 
	ucgenCiz(x_center);



	glutSwapBuffers(); // Swap buffers for double buffering
}






//-------------------------------------------------------------------------------------------------------------------------------
//BAHA YOLAL - gover: Tas Tasrimi

//-------------------------------------------------------------------------------------------------------------------------------
//ERLINDI ISAJ - gorev: Zar Tasarimi 

//-------------------------------------------------------------------------------------------------------------------------------
//LEONIT SHABANI - gorev: Oyun Mantigi

//Set up starting position
void startingPosition() {
    //Beyaz
    colorArray[23] = 0; colorArray[12] = 0; colorArray[7] = 0; colorArray[5] = 0;
    numberArray[23] = 2; numberArray[12] = 5; numberArray[7] = 3; numberArray[5] = 5;

    //Siyah
    colorArray[0] = 1; colorArray[11] = 1; colorArray[16] = 1; colorArray[18] = 1;
    numberArray[0] = 2; numberArray[11] = 5; numberArray[16] = 3; numberArray[18] = 5;
}

int makeMove(int currentIndex, int rolledNumber, int targetSquare) {

}

int checkBase() {
    int lowerBound = 0;
    int upperBound = 7;
    if (toMove == 1){
        lowerBound = 18;
        upperBound = 24;
    }
    int stonesFound = 0;
    for (int i = lowerBound; i < upperBound; i++) {
        if (colorArray[i] == toMove) {
            stonesFound += numberArray[i];
        }
    }
    if (stonesFound == 13)
        return 1;
    else
        return 0;
}

int checkMove(int currentIndex, int rolledNumber, int targetSquare) {
    if (colorArray[targetSquare] != toMove) {
        if (numberArray[targetSquare] > 1) {
            return 0;
        }
        colorArray[targetSquare] = toMove;
        switch (toMove) {
            case 0: outsideBlack++; blackReadyToCollect = false; break;
            case 1: outsideWhite++; whiteReadyToCollect = false; break;
        }
        return 1;
    }
    else if (targetSquare < 0) {
        if (toMove == 1)
            return 0;
        if (checkBase() && rolledNumber >= currentIndex) {
            collectedWhite++;
            return 1;
        }
        return 0;
    }
    else if (targetSquare > 23) {
        if (toMove == 0)
            return 0;
        if (checkBase() && rolledNumber >= currentIndex) {
            collectedBlack++;
            return 1;
        }
        return 0;
    }
    else if (currentIndex + rolledNumber == targetSquare) {
        numberArray[targetSquare]++;
        colorArray[targetSquare] = toMove;
        return 1;
    }
    else 
        return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(500, 500);  
    glutInitWindowSize(800, 600);     
    glutCreateWindow("OpenGL Hello World");

    glutMainLoop();

    return 0;
}