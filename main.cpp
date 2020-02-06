#include <GL/gl.h>
#include <GL/glut.h>
#include <ctime>

#include <iostream>

#define __BLANCO 1.0, 1.0, 1.0
#define __NEGRO 0.0, 0.0, 0.0

#include "HighLife.h"

using namespace std;

int N = 500;
HighLife* hl = nullptr;
int id = 0;

int randomInt(int min, int max)
{
    srand((unsigned)clock());  /* Seed the */
    max = max - min + 1;
    max = (max == 0) ? 1 : max;
    return min + (rand() % max);  /* Generate a random integer */
}

void display(void){
    float n=N;
    int m=n;

    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (__BLANCO);

    hl->run();
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            if(hl->cellState(i, j))
                glBegin(GL_QUADS);
                    glVertex2f(float(i/n), 1.0-float(j/n)); glVertex2f(float(i/n)+float(1.0/n), 1.0-float(j/n));
                    glVertex2f(float(i/n)+float(1.0/n), 1.0-float(j/n)-float(1.0/n)); glVertex2f(float(i/n), 1.0-float(j/n)-float(1.0/n));
                glEnd();
            }}
    glFlush();

    cout<<endl<<"Generation # "<<id;
    ++id;
    glutPostRedisplay();
}

void init (void){
    glClearColor (__NEGRO, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    for (int i = 0; i < N; i++)
    {
        int max = randomInt(0, N-1);
        int r = randomInt(0, max);
        int c = randomInt(0, max);

        hl->setCellState(r, c, 1);
    }

}

int main(int argc, char** argv)
{
    /**
     *  el formato de la descripcion es alive/brith
     *     /3 (estable) casi todo es una chispa
     * 5678/35678 (caótico) diamantes, catástrofes
     * 1357/1357 (crece) todo son replicantes
     * 1358/357 (caótico) un reino equilibrado de amebas
     * 23/3 (complejo) "Juego de la Vida de Conway"
     * 23/36 (caótico) "HighLife" (tiene replicante)
     * 2/7 (caótico) "Diffusion Rule" (gliders, guns, puffer trains)
     * 235678/3678 (estable) mancha de tinta que se seca rápidamente
     * 245/368 (estable) muerte, locomotoras y naves
     * 34/34 (crece) "Vida 34"
     * 4/2 (crece) generador de patrones de alfombras
     * 51/346 (estable) "Larga vida" casi todo son osciladores
     *
     *
     * La simulacion es
     * hl = new HighLife(ROWS, COLS, birth, alive); por lo que se invierten los valores
     * */
    int birth, alive;

//    birth = 3; alive = 0;
//    birth = 35678; alive = 5678;
//    birth = 1357; alive = 1357;
//    birth = 357; alive = 1358;
//    birth = 3; alive = 23;
    birth = 36; alive = 23;
//    birth = 7; alive = 2;
//    birth = 3678; alive = 235678;
//    birth = 368; alive = 245;
//    birth = 34; alive = 34;
//    birth = 2; alive = 4;
//    birth = 346; alive = 51;
//    hl = new HighLife(N, N, 35678, 5678);
//    hl = new HighLife(N, N, 1357, 1357);
//    hl = new HighLife(N, N, 357, 1358);
//    hl = new HighLife(N, N, 3, 23);

    hl = new HighLife(N, N, birth, alive);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("High life");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    delete hl;
    return 0;
}