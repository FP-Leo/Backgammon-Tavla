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



//-------------------------------------------------------------------------------------------------------------------------------
//BAHA YOLAL - gover: Tas Tasrimi

//-------------------------------------------------------------------------------------------------------------------------------
//ERLINDI ISAJ - gorev: Zar Tasarimi 
// Angle of rotation
GLfloat angle = 0.0f;
int window2D, window3D;
GLboolean rotateFlag = GL_FALSE;
int dice1;
int dice2;


int randomNumber() {
	return rand() % 6 + 1;
}



void drawCube() {

	// Set the color to gray for all faces
	glColor3f(0.7f, 0.7f, 0.7f);

	glBegin(GL_QUADS);

	// Front face
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Back face
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Right face
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Left face
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Top face
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Bottom face
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

// Global variable to track the current view (0 for 2D, 1 for 3D)
int currentView = 0;


void keyboard(unsigned char Key, int x, int y) {
	switch (Key) {
	case 'r':
		getDiceValues();
		rotateFlag = GL_TRUE; // Start rotating
		glutTimerFunc(0, rollDice, 0);
		glutPostRedisplay(); // Redisplay the scene
		break;
	case 'e':
		
		// Toggle between 2D and 3D views
		if (currentView == 1) currentView = 0;
		else currentView = 1;
		std::cout << currentView;
		glutPostRedisplay(); // Redisplay the scene
		break;
	}
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

void display3D() {

	glutSetWindow(window3D);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// Get current window dimensions (replace with your method if needed)
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Adjust viewport and projection if necessary
	if (height == 0) height = 1; // Prevent division by zero
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW); // Switch back to model-view

	


	glLoadIdentity();
	glTranslatef(-2.0f, 0.0f, -10.0f); //Position the First Dice
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	drawCube();

	glLoadIdentity();
	glTranslatef(2.0f, 0.0f, -10.0f); //Position the Second Dice
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	drawCube();

	
	glutSwapBuffers();
}



void display2D() {

	glutSetWindow(window2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 222.0, 0.0, 220.0);
	glMatrixMode(GL_MODELVIEW);

	drawBackgammonBoard();
	drawFrame();


	float x_center = (35 + 185) / 2.0f; // TABLANIN MERKEZLERÝNÝ HESAPLADIM  
	float y_center = (20 + 200) / 2.0f;

	drawSplitter(x_center);

	//Ucgen ciz 
	drawTriangles(x_center);

	glutSwapBuffers();

}



// Function to handle mouse clicks
void mouse(int button, int state, int x, int y) {
	std::cout << "Clicked" << currentView;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Define the button area (adjust coordinates as needed)
		if (x >= 10 && x <= 90 && y >= 10 && y <= 50) {
			// Toggle between 2D and 3D views
			if (currentView == 1) currentView = 0;
			else currentView = 1;
			glutPostRedisplay(); // Redisplay the scene
		}
	}
}



int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
    glutInitWindowSize(800, 600);     
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Create the 2D window
	window2D = glutCreateWindow("Tavlla - 2D");
	glutDisplayFunc(display2D);
	glutReshapeWindow(800, 600); // Set initial size

	// Create the 3D window
	window3D = glutCreateWindow("Zar - 3D");
	glutDisplayFunc(display3D);
	glutReshapeWindow(300, 200); // Set initial size
	//glutMouseFunc(mouse);


		// Erlindi
			
			
			glutKeyboardFunc(keyboard);

		

		//////////////////////////////////////////  

    glutMainLoop();

    return 0;
}