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
int baseWhite = 0;
int collectedWhite = 0;

int outsideBlack = 0;
int blackReadyToCollect = false;
int baseBlack = 0;
int collectedBlack = 0;

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
    colorArray[23] = 0; colorArray[12] = 0; colorArray[7] = 0; colorArray[5] = 0;
    numberArray[23] = 2; numberArray[12] = 5; numberArray[7] = 3; numberArray[5] = 5;
    baseWhite = 5;

    //Siyah
    colorArray[0] = 1; colorArray[11] = 1; colorArray[16] = 1; colorArray[18] = 1;
    numberArray[0] = 2; numberArray[11] = 5; numberArray[16] = 3; numberArray[18] = 5;
    baseBlack = 5;
}

int makeMove(int currentIndex, int rolledNumber, int targetSquare) {
    int result = checkMove(currentIndex, rolledNumber, targetSquare);
    if (result == 1){
        if (toMove == 0 && !whiteReadyToCollect && targetSquare <= 5 && targetSquare >= 0) {
            baseWhite++;
            if (baseWhite + collectedWhite == 13)
                whiteReadyToCollect = true;
        }
        else if (toMove == 1 && !blackReadyToCollect && targetSquare >= 18 && targetSquare <= 23) {
            baseBlack++;
            if (baseBlack + collectedBlack == 13)
                blackReadyToCollect = true;
        }
    }
    return result;
}

int checkMove(int currentIndex, int rolledNumber, int targetSquare) {
    if (toMove == 0 && targetSquare >= currentIndex)
        return 0;
    else if (toMove == 1 && targetSquare <= currentIndex)
        return 0;
    else if (colorArray[targetSquare] != toMove) {
        if (numberArray[targetSquare] > 1) {
            return 0;
        }
        numberArray[currentIndex]--;
        if (numberArray[currentIndex] == 0) {
            colorArray[currentIndex] = -1;
        }
        colorArray[targetSquare] = toMove;
        switch (toMove) {
            case 0: outsideBlack++; blackReadyToCollect = false; 
                if (targetSquare >= 18 && targetSquare <= 23) {
                    baseBlack--;
                }
                break;
            case 1: outsideWhite++; whiteReadyToCollect = false; 
                if (targetSquare <= 5 && targetSquare >= 0) {
                    baseWhite--;
                }
                break;
        }
        return 1;
    }
    else if (targetSquare < 0) {
        if (toMove == 1)
            return 0;
        if (whiteReadyToCollect && rolledNumber >= currentIndex) {
            collectedWhite++;
            baseWhite--;
            return 1;
        }
        return 0;
    }
    else if (targetSquare > 23) {
        if (toMove == 0)
            return 0;
        if (blackReadyToCollect && rolledNumber >= currentIndex) {
            collectedBlack++;
            baseBlack--;
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