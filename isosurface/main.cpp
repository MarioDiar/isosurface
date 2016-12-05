//Isosurface Visualization - Graphics Final Project

// Controles:
// Teclas de Movimiento = Mueven objeto dentro del grid
// ALT + Teclas de Movmiento = Rotar todo el render (grid + objeto)
// Tecla "+" = Aumentar el tamaño del objeto
// Tecla "-" = Disminuir el tamaño del objeto

#include "stdio.h"
#include "math.h"
#include "iostream"
#if defined __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

struct Vertex {
    GLfloat X;
    GLfloat Y;
    GLfloat Z;
};

// CONFIGURACION VENTANA
#define WINDOW_POSITION_X  1500
#define WINDOW_POSITION_Y  100
#define WINDOW_SIZE 520


float movimientoHorizontal = 1.0;
float movimientoVertical = 1.0;
float puntoOrigenX;
float puntoOrigenY;
float puntoOrigenZ;
GLfloat isoValor = 7.0;
//GLfloat isoValor = 48.0;
static GLfloat rotacionVertical = 0.0;
static GLfloat rotacionHorizontal   = 0.0;

// Conseguimos este dataset del Arctic Region Supercomputing Center
int tablaArcos[256]= {0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };
int tablaTriangulos[256][13] = {{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 3, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 9, 0, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 3, 1, 8, 1, 9,-1,-1,-1,-1,-1,-1,-1},{10, 1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 3, 0, 1, 2,10,-1,-1,-1,-1,-1,-1,-1},{ 9, 0, 2, 9, 2,10,-1,-1,-1,-1,-1,-1,-1},{ 3, 2, 8, 2,10, 8, 8,10, 9,-1,-1,-1,-1},{11, 2, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{11, 2, 0,11, 0, 8,-1,-1,-1,-1,-1,-1,-1},{11, 2, 3, 0, 1, 9,-1,-1,-1,-1,-1,-1,-1},{ 2, 1,11, 1, 9,11,11, 9, 8,-1,-1,-1,-1},{10, 1, 3,10, 3,11,-1,-1,-1,-1,-1,-1,-1},{ 1, 0,10, 0, 8,10,10, 8,11,-1,-1,-1,-1},{ 0, 3, 9, 3,11, 9, 9,11,10,-1,-1,-1,-1},{ 8,10, 9, 8,11,10,-1,-1,-1,-1,-1,-1,-1},{ 8, 4, 7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 3, 0, 4, 3, 4, 7,-1,-1,-1,-1,-1,-1,-1},{ 1, 9, 0, 8, 4, 7,-1,-1,-1,-1,-1,-1,-1},{ 9, 4, 1, 4, 7, 1, 1, 7, 3,-1,-1,-1,-1},{10, 1, 2, 8, 4, 7,-1,-1,-1,-1,-1,-1,-1},{ 2,10, 1, 0, 4, 7, 0, 7, 3,-1,-1,-1,-1},{ 4, 7, 8, 0, 2,10, 0,10, 9,-1,-1,-1,-1},{ 2, 7, 3, 2, 9, 7, 7, 9, 4, 2,10, 9,-1},{ 2, 3,11, 7, 8, 4,-1,-1,-1,-1,-1,-1,-1},{ 7,11, 4,11, 2, 4, 4, 2, 0,-1,-1,-1,-1},{ 3,11, 2, 4, 7, 8, 9, 0, 1,-1,-1,-1,-1},{ 2, 7,11, 2, 1, 7, 1, 4, 7, 1, 9, 4,-1},{ 8, 4, 7,11,10, 1,11, 1, 3,-1,-1,-1,-1},{11, 4, 7, 1, 4,11, 1,11,10, 1, 0, 4,-1},{ 3, 8, 0, 7,11, 4,11, 9, 4,11,10, 9,-1},{ 7,11, 4, 4,11, 9,11,10, 9,-1,-1,-1,-1},{ 9, 5, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 3, 0, 8, 4, 9, 5,-1,-1,-1,-1,-1,-1,-1},{ 5, 4, 0, 5, 0, 1,-1,-1,-1,-1,-1,-1,-1},{ 4, 8, 5, 8, 3, 5, 5, 3, 1,-1,-1,-1,-1},{ 2,10, 1, 9, 5, 4,-1,-1,-1,-1,-1,-1,-1},{ 0, 8, 3, 5, 4, 9,10, 1, 2,-1,-1,-1,-1},{10, 5, 2, 5, 4, 2, 2, 4, 0,-1,-1,-1,-1},{ 3, 4, 8, 3, 2, 4, 2, 5, 4, 2,10, 5,-1},{11, 2, 3, 9, 5, 4,-1,-1,-1,-1,-1,-1,-1},{ 9, 5, 4, 8,11, 2, 8, 2, 0,-1,-1,-1,-1},{ 3,11, 2, 1, 5, 4, 1, 4, 0,-1,-1,-1,-1},{ 8, 5, 4, 2, 5, 8, 2, 8,11, 2, 1, 5,-1},{ 5, 4, 9, 1, 3,11, 1,11,10,-1,-1,-1,-1},{ 0, 9, 1, 4, 8, 5, 8,10, 5, 8,11,10,-1},{ 3, 4, 0, 3,10, 4, 4,10, 5, 3,11,10,-1},{ 4, 8, 5, 5, 8,10, 8,11,10,-1,-1,-1,-1},{ 9, 5, 7, 9, 7, 8,-1,-1,-1,-1,-1,-1,-1},{ 0, 9, 3, 9, 5, 3, 3, 5, 7,-1,-1,-1,-1},{ 8, 0, 7, 0, 1, 7, 7, 1, 5,-1,-1,-1,-1},{ 1, 7, 3, 1, 5, 7,-1,-1,-1,-1,-1,-1,-1},{ 1, 2,10, 5, 7, 8, 5, 8, 9,-1,-1,-1,-1},{ 9, 1, 0,10, 5, 2, 5, 3, 2, 5, 7, 3,-1},{ 5, 2,10, 8, 2, 5, 8, 5, 7, 8, 0, 2,-1},{10, 5, 2, 2, 5, 3, 5, 7, 3,-1,-1,-1,-1},{11, 2, 3, 8, 9, 5, 8, 5, 7,-1,-1,-1,-1},{ 9, 2, 0, 9, 7, 2, 2, 7,11, 9, 5, 7,-1},{ 0, 3, 8, 2, 1,11, 1, 7,11, 1, 5, 7,-1},{ 2, 1,11,11, 1, 7, 1, 5, 7,-1,-1,-1,-1},{ 3, 9, 1, 3, 8, 9, 7,11,10, 7,10, 5,-1},{ 9, 1, 0,10, 7,11,10, 5, 7,-1,-1,-1,-1},{ 3, 8, 0, 7,10, 5, 7,11,10,-1,-1,-1,-1},{11, 5, 7,11,10, 5,-1,-1,-1,-1,-1,-1,-1},{10, 6, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 3, 0,10, 6, 5,-1,-1,-1,-1,-1,-1,-1},{ 0, 1, 9, 5,10, 6,-1,-1,-1,-1,-1,-1,-1},{10, 6, 5, 9, 8, 3, 9, 3, 1,-1,-1,-1,-1},{ 1, 2, 6, 1, 6, 5,-1,-1,-1,-1,-1,-1,-1},{ 0, 8, 3, 2, 6, 5, 2, 5, 1,-1,-1,-1,-1},{ 5, 9, 6, 9, 0, 6, 6, 0, 2,-1,-1,-1,-1},{ 9, 6, 5, 3, 6, 9, 3, 9, 8, 3, 2, 6,-1},{ 3,11, 2,10, 6, 5,-1,-1,-1,-1,-1,-1,-1},{ 6, 5,10, 2, 0, 8, 2, 8,11,-1,-1,-1,-1},{ 1, 9, 0, 6, 5,10,11, 2, 3,-1,-1,-1,-1},{ 1,10, 2, 5, 9, 6, 9,11, 6, 9, 8,11,-1},{11, 6, 3, 6, 5, 3, 3, 5, 1,-1,-1,-1,-1},{ 0, 5, 1, 0,11, 5, 5,11, 6, 0, 8,11,-1},{ 0, 5, 9, 0, 3, 5, 3, 6, 5, 3,11, 6,-1},{ 5, 9, 6, 6, 9,11, 9, 8,11,-1,-1,-1,-1},{10, 6, 5, 4, 7, 8,-1,-1,-1,-1,-1,-1,-1},{ 5,10, 6, 7, 3, 0, 7, 0, 4,-1,-1,-1,-1},{ 5,10, 6, 0, 1, 9, 8, 4, 7,-1,-1,-1,-1},{ 4, 5, 9, 6, 7,10, 7, 1,10, 7, 3, 1,-1},{ 7, 8, 4, 5, 1, 2, 5, 2, 6,-1,-1,-1,-1},{ 4, 1, 0, 4, 5, 1, 6, 7, 3, 6, 3, 2,-1},{ 9, 4, 5, 8, 0, 7, 0, 6, 7, 0, 2, 6,-1},{ 4, 5, 9, 6, 3, 2, 6, 7, 3,-1,-1,-1,-1},{ 7, 8, 4, 2, 3,11,10, 6, 5,-1,-1,-1,-1},{11, 6, 7,10, 2, 5, 2, 4, 5, 2, 0, 4,-1},{11, 6, 7, 8, 0, 3, 1,10, 2, 9, 4, 5,-1},{ 6, 7,11, 1,10, 2, 9, 4, 5,-1,-1,-1,-1},{ 6, 7,11, 4, 5, 8, 5, 3, 8, 5, 1, 3,-1},{ 6, 7,11, 4, 1, 0, 4, 5, 1,-1,-1,-1,-1},{ 4, 5, 9, 3, 8, 0,11, 6, 7,-1,-1,-1,-1},{ 9, 4, 5, 7,11, 6,-1,-1,-1,-1,-1,-1,-1},{10, 6, 4,10, 4, 9,-1,-1,-1,-1,-1,-1,-1},{ 8, 3, 0, 9,10, 6, 9, 6, 4,-1,-1,-1,-1},{ 1,10, 0,10, 6, 0, 0, 6, 4,-1,-1,-1,-1},{ 8, 6, 4, 8, 1, 6, 6, 1,10, 8, 3, 1,-1},{ 9, 1, 4, 1, 2, 4, 4, 2, 6,-1,-1,-1,-1},{ 1, 0, 9, 3, 2, 8, 2, 4, 8, 2, 6, 4,-1},{ 2, 4, 0, 2, 6, 4,-1,-1,-1,-1,-1,-1,-1},{ 3, 2, 8, 8, 2, 4, 2, 6, 4,-1,-1,-1,-1},{ 2, 3,11, 6, 4, 9, 6, 9,10,-1,-1,-1,-1},{ 0,10, 2, 0, 9,10, 4, 8,11, 4,11, 6,-1},{10, 2, 1,11, 6, 3, 6, 0, 3, 6, 4, 0,-1},{10, 2, 1,11, 4, 8,11, 6, 4,-1,-1,-1,-1},{ 1, 4, 9,11, 4, 1,11, 1, 3,11, 6, 4,-1},{ 0, 9, 1, 4,11, 6, 4, 8,11,-1,-1,-1,-1},{11, 6, 3, 3, 6, 0, 6, 4, 0,-1,-1,-1,-1},{ 8, 6, 4, 8,11, 6,-1,-1,-1,-1,-1,-1,-1},{ 6, 7,10, 7, 8,10,10, 8, 9,-1,-1,-1,-1},{ 9, 3, 0, 6, 3, 9, 6, 9,10, 6, 7, 3,-1},{ 6, 1,10, 6, 7, 1, 7, 0, 1, 7, 8, 0,-1},{ 6, 7,10,10, 7, 1, 7, 3, 1,-1,-1,-1,-1},{ 7, 2, 6, 7, 9, 2, 2, 9, 1, 7, 8, 9,-1},{ 1, 0, 9, 3, 6, 7, 3, 2, 6,-1,-1,-1,-1},{ 8, 0, 7, 7, 0, 6, 0, 2, 6,-1,-1,-1,-1},{ 2, 7, 3, 2, 6, 7,-1,-1,-1,-1,-1,-1,-1},{ 7,11, 6, 3, 8, 2, 8,10, 2, 8, 9,10,-1},{11, 6, 7,10, 0, 9,10, 2, 0,-1,-1,-1,-1},{ 2, 1,10, 7,11, 6, 8, 0, 3,-1,-1,-1,-1},{ 1,10, 2, 6, 7,11,-1,-1,-1,-1,-1,-1,-1},{ 7,11, 6, 3, 9, 1, 3, 8, 9,-1,-1,-1,-1},{ 9, 1, 0,11, 6, 7,-1,-1,-1,-1,-1,-1,-1},{ 0, 3, 8,11, 6, 7,-1,-1,-1,-1,-1,-1,-1},{11, 6, 7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{11, 7, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 0, 8, 3,11, 7, 6,-1,-1,-1,-1,-1,-1,-1},{ 9, 0, 1,11, 7, 6,-1,-1,-1,-1,-1,-1,-1},{ 7, 6,11, 3, 1, 9, 3, 9, 8,-1,-1,-1,-1},{ 1, 2,10, 6,11, 7,-1,-1,-1,-1,-1,-1,-1},{ 2,10, 1, 7, 6,11, 8, 3, 0,-1,-1,-1,-1},{11, 7, 6,10, 9, 0,10, 0, 2,-1,-1,-1,-1},{ 7, 6,11, 3, 2, 8, 8, 2,10, 8,10, 9,-1},{ 2, 3, 7, 2, 7, 6,-1,-1,-1,-1,-1,-1,-1},{ 8, 7, 0, 7, 6, 0, 0, 6, 2,-1,-1,-1,-1},{ 1, 9, 0, 3, 7, 6, 3, 6, 2,-1,-1,-1,-1},{ 7, 6, 2, 7, 2, 9, 2, 1, 9, 7, 9, 8,-1},{ 6,10, 7,10, 1, 7, 7, 1, 3,-1,-1,-1,-1},{ 6,10, 1, 6, 1, 7, 7, 1, 0, 7, 0, 8,-1},{ 9, 0, 3, 6, 9, 3, 6,10, 9, 6, 3, 7,-1},{ 6,10, 7, 7,10, 8,10, 9, 8,-1,-1,-1,-1},{ 8, 4, 6, 8, 6,11,-1,-1,-1,-1,-1,-1,-1},{11, 3, 6, 3, 0, 6, 6, 0, 4,-1,-1,-1,-1},{ 0, 1, 9, 4, 6,11, 4,11, 8,-1,-1,-1,-1},{ 1, 9, 4,11, 1, 4,11, 3, 1,11, 4, 6,-1},{10, 1, 2,11, 8, 4,11, 4, 6,-1,-1,-1,-1},{10, 1, 2,11, 3, 6, 6, 3, 0, 6, 0, 4,-1},{ 0, 2,10, 0,10, 9, 4,11, 8, 4, 6,11,-1},{ 2,11, 3, 6, 9, 4, 6,10, 9,-1,-1,-1,-1},{ 3, 8, 2, 8, 4, 2, 2, 4, 6,-1,-1,-1,-1},{ 2, 0, 4, 2, 4, 6,-1,-1,-1,-1,-1,-1,-1},{ 1, 9, 0, 3, 8, 2, 2, 8, 4, 2, 4, 6,-1},{ 9, 4, 1, 1, 4, 2, 4, 6, 2,-1,-1,-1,-1},{ 8, 4, 6, 8, 6, 1, 6,10, 1, 8, 1, 3,-1},{ 1, 0,10,10, 0, 6, 0, 4, 6,-1,-1,-1,-1},{ 8, 0, 3, 9, 6,10, 9, 4, 6,-1,-1,-1,-1},{10, 4, 6,10, 9, 4,-1,-1,-1,-1,-1,-1,-1},{ 9, 5, 4, 7, 6,11,-1,-1,-1,-1,-1,-1,-1},{ 4, 9, 5, 3, 0, 8,11, 7, 6,-1,-1,-1,-1},{ 6,11, 7, 4, 0, 1, 4, 1, 5,-1,-1,-1,-1},{ 6,11, 7, 4, 8, 5, 5, 8, 3, 5, 3, 1,-1},{ 6,11, 7, 1, 2,10, 9, 5, 4,-1,-1,-1,-1},{11, 7, 6, 8, 3, 0, 1, 2,10, 9, 5, 4,-1},{11, 7, 6,10, 5, 2, 2, 5, 4, 2, 4, 0,-1},{ 7, 4, 8, 2,11, 3,10, 5, 6,-1,-1,-1,-1},{ 4, 9, 5, 6, 2, 3, 6, 3, 7,-1,-1,-1,-1},{ 9, 5, 4, 8, 7, 0, 0, 7, 6, 0, 6, 2,-1},{ 4, 0, 1, 4, 1, 5, 6, 3, 7, 6, 2, 3,-1},{ 7, 4, 8, 5, 2, 1, 5, 6, 2,-1,-1,-1,-1},{ 4, 9, 5, 6,10, 7, 7,10, 1, 7, 1, 3,-1},{ 5, 6,10, 0, 9, 1, 8, 7, 4,-1,-1,-1,-1},{ 5, 6,10, 7, 0, 3, 7, 4, 0,-1,-1,-1,-1},{10, 5, 6, 4, 8, 7,-1,-1,-1,-1,-1,-1,-1},{ 5, 6, 9, 6,11, 9, 9,11, 8,-1,-1,-1,-1},{ 0, 9, 5, 0, 5, 3, 3, 5, 6, 3, 6,11,-1},{ 0, 1, 5, 0, 5,11, 5, 6,11, 0,11, 8,-1},{11, 3, 6, 6, 3, 5, 3, 1, 5,-1,-1,-1,-1},{ 1, 2,10, 5, 6, 9, 9, 6,11, 9,11, 8,-1},{ 1, 0, 9, 6,10, 5,11, 3, 2,-1,-1,-1,-1},{ 6,10, 5, 2, 8, 0, 2,11, 8,-1,-1,-1,-1},{ 3, 2,11,10, 5, 6,-1,-1,-1,-1,-1,-1,-1},{ 9, 5, 6, 3, 9, 6, 3, 8, 9, 3, 6, 2,-1},{ 5, 6, 9, 9, 6, 0, 6, 2, 0,-1,-1,-1,-1},{ 0, 3, 8, 2, 5, 6, 2, 1, 5,-1,-1,-1,-1},{ 1, 6, 2, 1, 5, 6,-1,-1,-1,-1,-1,-1,-1},{10, 5, 6, 9, 3, 8, 9, 1, 3,-1,-1,-1,-1},{ 0, 9, 1, 5, 6,10,-1,-1,-1,-1,-1,-1,-1},{ 8, 0, 3,10, 5, 6,-1,-1,-1,-1,-1,-1,-1},{10, 5, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{11, 7, 5,11, 5,10,-1,-1,-1,-1,-1,-1,-1},{ 3, 0, 8, 7, 5,10, 7,10,11,-1,-1,-1,-1},{ 9, 0, 1,10,11, 7,10, 7, 5,-1,-1,-1,-1},{ 3, 1, 9, 3, 9, 8, 7,10,11, 7, 5,10,-1},{ 2,11, 1,11, 7, 1, 1, 7, 5,-1,-1,-1,-1},{ 0, 8, 3, 2,11, 1, 1,11, 7, 1, 7, 5,-1},{ 9, 0, 2, 9, 2, 7, 2,11, 7, 9, 7, 5,-1},{11, 3, 2, 8, 5, 9, 8, 7, 5,-1,-1,-1,-1},{10, 2, 5, 2, 3, 5, 5, 3, 7,-1,-1,-1,-1},{ 5,10, 2, 8, 5, 2, 8, 7, 5, 8, 2, 0,-1},{ 9, 0, 1,10, 2, 5, 5, 2, 3, 5, 3, 7,-1},{ 1,10, 2, 5, 8, 7, 5, 9, 8,-1,-1,-1,-1},{ 1, 3, 7, 1, 7, 5,-1,-1,-1,-1,-1,-1,-1},{ 8, 7, 0, 0, 7, 1, 7, 5, 1,-1,-1,-1,-1},{ 0, 3, 9, 9, 3, 5, 3, 7, 5,-1,-1,-1,-1},{ 9, 7, 5, 9, 8, 7,-1,-1,-1,-1,-1,-1,-1},{ 4, 5, 8, 5,10, 8, 8,10,11,-1,-1,-1,-1},{ 3, 0, 4, 3, 4,10, 4, 5,10, 3,10,11,-1},{ 0, 1, 9, 4, 5, 8, 8, 5,10, 8,10,11,-1},{ 5, 9, 4, 1,11, 3, 1,10,11,-1,-1,-1,-1},{ 8, 4, 5, 2, 8, 5, 2,11, 8, 2, 5, 1,-1},{ 3, 2,11, 1, 4, 5, 1, 0, 4,-1,-1,-1,-1},{ 9, 4, 5, 8, 2,11, 8, 0, 2,-1,-1,-1,-1},{11, 3, 2, 9, 4, 5,-1,-1,-1,-1,-1,-1,-1},{ 3, 8, 4, 3, 4, 2, 2, 4, 5, 2, 5,10,-1},{10, 2, 5, 5, 2, 4, 2, 0, 4,-1,-1,-1,-1},{ 0, 3, 8, 5, 9, 4,10, 2, 1,-1,-1,-1,-1},{ 2, 1,10, 9, 4, 5,-1,-1,-1,-1,-1,-1,-1},{ 4, 5, 8, 8, 5, 3, 5, 1, 3,-1,-1,-1,-1},{ 5, 0, 4, 5, 1, 0,-1,-1,-1,-1,-1,-1,-1},{ 3, 8, 0, 4, 5, 9,-1,-1,-1,-1,-1,-1,-1},{ 9, 4, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 7, 4,11, 4, 9,11,11, 9,10,-1,-1,-1,-1},{ 3, 0, 8, 7, 4,11,11, 4, 9,11, 9,10,-1},{11, 7, 4, 1,11, 4, 1,10,11, 1, 4, 0,-1},{ 8, 7, 4,11, 1,10,11, 3, 1,-1,-1,-1,-1},{ 2,11, 7, 2, 7, 1, 1, 7, 4, 1, 4, 9,-1},{ 3, 2,11, 4, 8, 7, 9, 1, 0,-1,-1,-1,-1},{ 7, 4,11,11, 4, 2, 4, 0, 2,-1,-1,-1,-1},{ 2,11, 3, 7, 4, 8,-1,-1,-1,-1,-1,-1,-1},{ 2, 3, 7, 2, 7, 9, 7, 4, 9, 2, 9,10,-1},{ 4, 8, 7, 0,10, 2, 0, 9,10,-1,-1,-1,-1},{ 2, 1,10, 0, 7, 4, 0, 3, 7,-1,-1,-1,-1},{10, 2, 1, 8, 7, 4,-1,-1,-1,-1,-1,-1,-1},{ 9, 1, 4, 4, 1, 7, 1, 3, 7,-1,-1,-1,-1},{ 1, 0, 9, 8, 7, 4,-1,-1,-1,-1,-1,-1,-1},{ 3, 4, 0, 3, 7, 4,-1,-1,-1,-1,-1,-1,-1},{ 8, 7, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 9,10, 8,10,11,-1,-1,-1,-1,-1,-1,-1},{ 0, 9, 3, 3, 9,11, 9,10,11,-1,-1,-1,-1},{ 1,10, 0, 0,10, 8,10,11, 8,-1,-1,-1,-1},{10, 3, 1,10,11, 3,-1,-1,-1,-1,-1,-1,-1},{ 2,11, 1, 1,11, 9,11, 8, 9,-1,-1,-1,-1},{11, 3, 2, 0, 9, 1,-1,-1,-1,-1,-1,-1,-1},{11, 0, 2,11, 8, 0,-1,-1,-1,-1,-1,-1,-1},{11, 3, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 3, 8, 2, 2, 8,10, 8, 9,10,-1,-1,-1,-1},{ 9, 2, 0, 9,10, 2,-1,-1,-1,-1,-1,-1,-1},{ 8, 0, 3, 1,10, 2,-1,-1,-1,-1,-1,-1,-1},{10, 2, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 1, 3, 8, 9, 1,-1,-1,-1,-1,-1,-1,-1},{ 9, 1, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{ 8, 0, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};


// Configuramos background, extensiones, luz y materiales
void init(void){
  glClearColor( 169.0/255.0, 169.0/255.0, 169.0/255.0, 1.0 );
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
	
	GLfloat rojo [] = {0.75, 0.00, 0.00, 1.00};
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
  
  glEnable( GL_LIGHT0 );
  
  glMaterialfv(GL_BACK,  GL_DIFFUSE,   rojo);
  glMaterialf( GL_FRONT, GL_SHININESS, 25.0);
}

// Se asegura que la ventana siga pintando aun cuando no esta activa
void reRenderizar() {
    glutPostRedisplay();
}

// Se asegura de manetener la proporción cuando la ventana es "resizeada"
void reRenderizar2(int ancho, int alto) {
    float aspecto = 0.0;
		float origen = 0.7071;
    
    glViewport( 0, 0, ancho, alto );
		//Entramos a modo Proyeccion (Aqui se cambia el "lente" de la camara)
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    
    aspecto = (GLfloat)alto / (GLfloat)ancho;
    glOrtho(-origen, origen, -origen*aspecto,
            origen*aspecto, -10*origen, 10*origen);

		//Regresamos a modo Vista-Modelo
    glMatrixMode( GL_MODELVIEW );
}

void controlesExtra(unsigned char key, int x, int y){
  if (key == 45) // -
    isoValor += 0.5;
	
	if (key == 43) // +
		isoValor -= 0.5;
}

void controles(int key, int x, int y) {
    float angulo = 0.9f;
    float pasos = 0.1f;
		
    int mod = glutGetModifiers();
    
    switch (key) {
        case GLUT_KEY_LEFT :
            if (mod == GLUT_ACTIVE_ALT) {
                rotacionHorizontal -= angulo;
            } else {
                movimientoHorizontal += pasos;
            }
            break;
        case GLUT_KEY_RIGHT :
            if (mod == GLUT_ACTIVE_ALT) {
                rotacionHorizontal += angulo;
            } else {
                movimientoHorizontal -= pasos;
            }
            break;
        case GLUT_KEY_UP :
            if (mod == GLUT_ACTIVE_ALT) {
                rotacionVertical += angulo;
            } else {
                movimientoVertical += pasos;
            }
            break;
        case GLUT_KEY_DOWN :
            if (mod == GLUT_ACTIVE_ALT) {
                rotacionVertical -= angulo;
            } else {
                movimientoVertical -= pasos;
            }
            break;
    }
}

void deplazarObjeto(float stepHorizontal, float stepVertical) {
		puntoOrigenX = 0.5;
		puntoOrigenY = 0.5;
		puntoOrigenZ = 0.5;

     
    puntoOrigenX *= stepHorizontal;
    puntoOrigenY *= stepVertical;
}


float funcion3D(float X, float Y, float Z) {
    
    GLfloat fResult;
    
    X-=puntoOrigenX;
    Y-=puntoOrigenY;
    Z-=puntoOrigenZ;
    
    // Cylinder
    //fResult= X*X+Z*Z;
  
    // Parabola
    //fResult = 4*(X*X) + 9*(Y*Y) + Z;
			
		fResult = X*X+Y*Y+Z*Z;

    fResult = 1.5/fResult;
    return fResult;
}

float diferencia(float a, float b, float c) {
    GLdouble fDelta = b - a;
    
    if(fDelta == 0.0)
    {
        return 0.5;
    }
    return (c - a)/fDelta;
}

void normalizarVector(Vertex &vectorResultante, Vertex &vectorOrigen) {
    float distancia;
    float escala;
    
    distancia = sqrtf( (vectorOrigen.X * vectorOrigen.X) + (vectorOrigen.Y * vectorOrigen.Y) + (vectorOrigen.Z * vectorOrigen.Z) );
    
    if(distancia == 0.0){
        vectorResultante.X = vectorOrigen.X;
        vectorResultante.Y = vectorOrigen.Y;
        vectorResultante.Z = vectorOrigen.Z;
    }else{
        escala = 1.0/distancia;
        vectorResultante.X = vectorOrigen.X*escala;
        vectorResultante.Y = vectorOrigen.Y*escala;
        vectorResultante.Z = vectorOrigen.Z*escala;
    }
}


void generarNormal(Vertex &vnormal, float X, float Y, float Z) {
    vnormal.X = funcion3D(X-0.01, Y, Z) - funcion3D(X+0.01, Y, Z);
    vnormal.Y = funcion3D(X, Y-0.01, Z) - funcion3D(X, Y+0.01, Z);
    vnormal.Z = funcion3D(X, Y, Z-0.01) - funcion3D(X, Y, Z+0.01);
    normalizarVector(vnormal, vnormal);
}

void generarColor(Vertex &color, Vertex &posicion, Vertex &vnormal) {
    float X = vnormal.X;
    float Y = vnormal.Y;
    float Z = vnormal.Z;
    color.X = (X > 0.0 ? X : 0.0) + (Y < 0.0 ? -0.5*Y : 0.0) + (Z < 0.0 ? -0.5*Z : 0.0);
    color.Y = (Y > 0.0 ? Y : 0.0) + (Z < 0.0 ? -0.5*Z : 0.0) + (X < 0.0 ? -0.5*X : 0.0);
    color.Z = (Z > 0.0 ? Z : 0.0) + (X < 0.0 ? -0.5*X : 0.0) + (Y < 0.0 ? -0.5*Y : 0.0);
}

void marchingCube(float X, float Y, float Z, float escala) {
    
		int VertexToVertex[8][3] = {
		    {0.0, 0.0, 0.0},{1.0, 0.0, 0.0},{1.0, 1.0, 0.0},{0.0, 1.0, 0.0},
		    {0.0, 0.0, 1.0},{1.0, 0.0, 1.0},{1.0, 1.0, 1.0},{0.0, 1.0, 1.0}
		};

		int edgeIndex[12][2] = {
		    {0,1}, {1,2}, {2,3}, {3,0},
		    {4,5}, {5,6}, {6,7}, {7,4},
		    {0,4}, {1,5}, {2,6}, {3,7}
		};

		int VertextVector[12][3] = {
		    {1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{-1.0, 0.0, 0.0},{0.0, -1.0, 0.0},
		    {1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{-1.0, 0.0, 0.0},{0.0, -1.0, 0.0},
		    {0.0, 0.0, 1.0},{0.0, 0.0, 1.0},{ 0.0, 0.0, 1.0},{0.0,  0.0, 1.0}
		};
	
    int cubeIndex, interseccionaBool;
    float offset;
    Vertex color;
    float grid[8];
    Vertex arcoVector[12];
    Vertex arcoNormal[12];
    
    for(int i = 0; i < 8; i++)
    {
        grid[i] = funcion3D(X + VertexToVertex[i][0]*escala, Y + VertexToVertex[i][1]*escala, Z + VertexToVertex[i][2]*escala);
    }
    
    cubeIndex = 0;
    for(int i = 0; i < 8; i++)
        if(grid[i] <= isoValor)
            cubeIndex |= 1<<i;
    
    //Checar los arcos que interseccionaron con la superficie
    interseccionaBool = tablaArcos[cubeIndex];
    
    // No dibujar si no intersecciona con nada
    if(interseccionaBool==0)
        return;
    
    
    for(int e = 0; e < 12; e++)
    {
			if(interseccionaBool & (1<<e))
        {
            offset = diferencia( grid[ edgeIndex[e][0] ],
                                 grid[ edgeIndex[e][1] ], isoValor);
            
            arcoVector[e].X = X + (VertexToVertex[ edgeIndex[e][0] ][0]  +  offset * VertextVector[e][0]) * escala;
            arcoVector[e].Y = Y + (VertexToVertex[ edgeIndex[e][0] ][1]  +  offset * VertextVector[e][1]) * escala;
            arcoVector[e].Z = Z + (VertexToVertex[ edgeIndex[e][0] ][2]  +  offset * VertextVector[e][2]) * escala;
            
            generarNormal(arcoNormal[e], arcoVector[e].X, arcoVector[e].Y, arcoVector[e].Z);
        }
    }
    
    for(int t = 0; t < 5; t++)
    {
        if(tablaTriangulos[cubeIndex][3*t] < 0)
            break;
        
        for(int c = 0; c < 3; c++)
        {
            int i = tablaTriangulos[cubeIndex][3*t+c];
            
            generarColor(color, arcoVector[i], arcoNormal[i]);
            glColor3f(color.X, color.Y, color.Z);
            glNormal3f(arcoNormal[i].X,   arcoNormal[i].Y,   arcoNormal[i].Z);
            glVertex3f(arcoVector[i].X, arcoVector[i].Y, arcoVector[i].Z);
        }
    }
}


void marchingCubes() {
	for(int x = 0; x < 13; x++){
		for(int y = 0; y < 13; y++){
			for(int z = 0; z < 13; z++){
			marchingCube(x*(1.0/13.0), y*(1.0/13.0), z*(1.0/13.0), (1.0/13.0));
			}
		}
	}
}


void renderizar() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
    glLoadIdentity (); 
    // Posicionamos la camara
    gluLookAt (0.5, 0.5,-5.5, 0.0, -0.1, 0.0, 0.0, 1.0, 0.0);
		
    glPushMatrix();  
    	deplazarObjeto(movimientoHorizontal, movimientoVertical);
    
	    glTranslatef(0.0, 0.0, -1.0);
	    glRotatef( -rotacionVertical, 1.0, 0.0, 0.0);
	    glRotatef(0.0, 0.0, 1.0, 0.0);
	    glRotatef(rotacionHorizontal, 0.0, 1.0, 0.0);
    
			//Desactivamos la luz para el grid
	    glPushAttrib(GL_LIGHTING_BIT);
			  glDisable(GL_LIGHTING);
		    glColor3f(1.0, 0.0, 0.0);
		    glutWireCube(1.0); //funcion integrada en glut
	    glPopAttrib();
    
    	// Dibujamos nuestra isosuperficie utilizando marchingcubes :)
			// Lo posicionamos en el centro
	    glPushMatrix();
		    glTranslatef(-0.5, -0.5, -0.5);
		    glBegin(GL_TRIANGLES);
			    marchingCubes();
		    glEnd();
	    glPopMatrix();
    
    glPopMatrix();
    
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    
		// Inicializamos Glut
    glutInit(&argc, argv);
    glutInitWindowPosition( WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutCreateWindow( "Isosurface Visualization - The Graficos");
		
		// Los callbacks de Glut
    glutDisplayFunc(renderizar);
    glutIdleFunc(reRenderizar);
    glutReshapeFunc(reRenderizar2);
    glutSpecialFunc(controles); // Controles de movimiento
    glutKeyboardFunc(controlesExtra); // Controles de tamaño
    
		// Inicializamos configuración para openGL
		init();
    
    reRenderizar2(WINDOW_SIZE, WINDOW_SIZE);
    
    glutMainLoop();
    return 1;
}

