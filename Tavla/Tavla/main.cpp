#include "glew.h"
#include "freeglut.h"
#include <iostream>

//DIKKAT: YAZDIGINIZ HER SEY ICIN YORUM KULLANIN. DIGERLERIN KODLARINI IYICE YORUM YAPMADAN DOKUNMAYIN. 
//SADECE ALANLARINDA KODLARINI YAZIN

//Prototip Alani

//Leo
void startingPosition();
int checkMove(int , int , int);

//Global Degisken Alani

//Leo
// 1 degeri - Beyaz, 2 ise siyah temsil eder. Beyaz tarafi 0dan 5'e kadar olan alanda toplicaktir. Siyah ise 18dan 23'e kadar olan alanda.
int colorArray[24] = { 0 }; 
int numberArray[24] = { 0 };
// Kimin halmesidir, 1 - beyaz, 2 - siyah
int toMove = 1;
int collectedWhite = 0;
int collectedBlack = 0;
int outsideWhite = 0;
int outsideBlack = 0;

//-------------------------------------------------------------------------------------------------------------------------------
//EREN NOKTA - gover: Tahta Tasarimi

//-------------------------------------------------------------------------------------------------------------------------------
//BAHA YOLAL - gover: Tas Tasrimi

//-------------------------------------------------------------------------------------------------------------------------------
//ERLINDI ISAJ - gorev: Zar Tasarimi 

//-------------------------------------------------------------------------------------------------------------------------------
//LEONIT SHABANI - gorev: Oyun Mantigi

//Set up starting position
void startingPosition() {
    //Beyaz
    colorArray[23] = 1; colorArray[12] = 1; colorArray[7] = 1; colorArray[5] = 1;
    numberArray[23] = 2; numberArray[12] = 5; numberArray[7] = 3; numberArray[5] = 5;

    //Siyah
    colorArray[0] = 2; colorArray[11] = 2; colorArray[16] = 2; colorArray[18] = 2;
    numberArray[0] = 2; numberArray[11] = 5; numberArray[16] = 3; numberArray[18] = 5;
}

int checkMove(int currentIndex, int rolledNumber, int targetSquare) {
    if (colorArray[targetSquare] != toMove)
        return 0;
    else if (targetSquare < 0) {
        // To be implemented
        return 0;
    }
    else if (targetSquare > 23) {
        // To be implemented
        return 0;
    }
    else if (currentIndex + rolledNumber == targetSquare) {
        // To be implemented
        return 0;
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