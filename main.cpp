#include <string.h>

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <Soil.h>
#include <fstream>
//#define _WIN32_WINNT 0x0502
#include <windows.h>
using namespace std;

bool WireFrame= false;
GLuint textures[5]; // Texture pointer
GLfloat matrixX[16];
GLfloat matrixY[16];
GLfloat matrixZ[16];
GLfloat x, y, z, w;
static GLint RotateY=0; /* model rotation Y index*/
static GLint RotateX=0; /* model rotation X index*/
static GLint RotateZ=0; /* model rotation X index*/
int Spin = 0;
float TEX_SIZE = 1.0;
float translate_z =-1;
GLuint Tload(const char *file);
//float prev_x, prev_y;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


struct Vertex {
    float p;
    float x;
    float y;
    float z;

};

Vertex vertex[11146];
Vertex Normal[11150];
int index[22250][6];
int i;


void getCoordinates(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'v' && str[1] == ' ') break; //if we have a vertex line, stop
    }
    int v = 0;
    while(str[0] == 'v' && str[1] == ' ') {
   // cout<<str<<endl;
        int i = 0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            vertex[v].p = (float)atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            vertex[v].x = (float)atof(str.substr(q, w-q).c_str());

            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != ' ' ) {
                i++;
                s = i;
            }
            vertex[v].y = (float)atof(str.substr(a, s-a).c_str());

             while(str[i] == ' ' ) {
                i++;
            }

            int t = i, u = i;
            while(str[i] != ' ' ) {
                i++;
                u = i;
            }
            vertex[v].z = (float)atof(str.substr(t, u-t).c_str());

            break;
        }
        //cout<<vertex[v].x<<"  "<< vertex[v].y<<"  "<< vertex[v].z<<endl;
        v++;
        getline(file, str);
    }
}

void getNormals(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'v' && str[1] == 'n') break; //if we have a vertex line, stop
    }
    int v = 0;
    while(str[0] == 'v' && str[1] == 'n') {
    //cout<<str<<endl;
        int i = 0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            Normal[v].x = (float)atof(str.substr(j, k-j).c_str());

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            Normal[v].y = (float)atof(str.substr(q, w-q).c_str());

            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != ' ' ) {
                i++;
                s = i;
            }
            Normal[v].z = (float)atof(str.substr(a, s-a).c_str());

            break;
        }
        //cout<<Normal[v].x<<"  "<< Normal[v].y<<"  "<< Normal[v].z<<endl;
        v++;

        getline(file, str);
    }
}

void getIndices(char* filename)
{
    ifstream file;
    file.open(filename);
    string str;
    while(!file.eof()) //while we are still in the file
    {
        getline(file,str); //move one line down
        if(str[0] == 'f' && str[1] == ' ') break; //if we have a vertex line, stop
    }
    int v = 0,indX=0;
    while(str[0] == 'f' && str[1] == ' ') {
   // cout<<str<<endl;
        int i = 0,indY=0;
        while(true){
            while(str[i] == ' ' )
            {
                i++; //move a space over
            }
            i++;
            i++;
            int j = i, k = i;
            while(str[i] != ' ') {
                i++;
                k = i;
            }
            //cout<<str[j]<<"  "<<str[i-1]<<endl;
            index[indX][indY] = atof(str.substr(j, j+1).c_str()) - 1;
            indY++;
            index[indX][indY] = atof(str.substr(i-1, i).c_str()) - 1;
            indY++;

            //moving on to the y coord

            while(str[i] == ' ' ) {
                i++;
            }

            int q = i, w = i;
            while(str[i] != ' ' ) {
                i++;
                w = i;
            }
            index[indX][indY] = atof(str.substr(q, q+1).c_str()) - 1;
            indY++;
            index[indX][indY] = atof(str.substr(i-1, i).c_str()) - 1;
            indY++;


            while(str[i] == ' ' ) {
                i++;
            }

            int a = i, s = i;
            while(str[i] != '\0' ) {
                i++;
                s = i;
            }
            index[indX][indY] = atof(str.substr(a, a+1).c_str()) - 1;
            indY++;
            index[indX][indY] = atof(str.substr(i-1, i).c_str()) - 1;
            break;
        }

        indX++;


        getline(file, str);
    }

}


static void resize(int width, int height)
{
    double Ratio;
    Ratio=(double)width/(double)height;
    glViewport(0,0,(GLsizei) width,(GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0f,Ratio,0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //Draw Our Mesh In Wireframe Mesh
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //Toggle WIRE FRAME

    // your code here
    glTranslated(-0.5,-0.5,translate_z);
    glRotatef(RotateX,1,0,0);
    glRotatef(RotateY,0,1,0);
    glRotatef(RotateZ,0,0,1);


    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();

    // triangle used to create cube are given colors here

    glBegin(GL_TRIANGLES);

  for(i=0;i<22250;i++)
        {

        //glColor3f(vertex[index[i][0]].x,vertex[index[i][0]].y,vertex[index[i][0]].z);
        glNormal3f(Normal[index[i][1]].x,Normal[index[i][1]].y,Normal[index[i][1]].z);
        glVertex3f((vertex[index[i][0]].x)/200,(vertex[index[i][0]].y)/200,(vertex[index[i][0]].z)/200);

        //glColor3f(vertex[index[i][2]].x,vertex[index[i][2]].y,vertex[index[i][2]].z);
        glNormal3f(Normal[index[i][3]].x,Normal[index[i][3]].y,Normal[index[i][3]].z);
        glVertex3f((vertex[index[i][2]].x)/200,(vertex[index[i][2]].y)/200,(vertex[index[i][2]].z)/200);

        //glColor3f(vertex[index[i][4]].x,vertex[index[i][4]].y,vertex[index[i][4]].z);
        glNormal3f(Normal[index[i][5]].x,Normal[index[i][5]].y,Normal[index[i][5]].z);
        glVertex3f((vertex[index[i][4]].x)/200,(vertex[index[i][4]].y)/200,(vertex[index[i][4]].z)/200);

        }



    glEnd();



    glPopMatrix();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

 case 'w':
WireFrame =!WireFrame;
      break;


      case 'd':
          RotateZ = ((int)RotateZ +15)%360;

break;
 case 'a':
     RotateZ = ((int)RotateZ -15)%360;

break;

    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_END:
 translate_z += (float) 1.0f;
break;
case GLUT_KEY_HOME:
 translate_z -= (float) 1.0f;
break;
    case GLUT_KEY_UP:
/* Clockwise rotation over X */
RotateX = ((int)RotateX +15)%360;
break;
case GLUT_KEY_DOWN:
/* Counter Clockwise rotation over X */
RotateX = ((int)RotateX -15)%360;
 break;
case GLUT_KEY_LEFT:
/* Clockwise rotation over Y */

RotateY =((int)RotateY +15)%360;
break;
case GLUT_KEY_RIGHT :
RotateY = ((int)RotateY -15)%360;/* Counter Clockwise rotation over Y */
break;
   }
  glutPostRedisplay();
}

static void idle(void)
{
    Spin=((int)Spin+5)%360;
    glutPostRedisplay();
}


static void init(void)
{
    AllocConsole();
    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );

    // cube.obj file is loaded here

    getCoordinates("ateneam.obj");
    getNormals("ateneam.obj");
    getIndices("ateneam.obj");
   // for(int i=0;i<6;i++){
//    textures[i] = Tload(ImageName[i]);
    }

//}

GLuint Tload(const char *file)
{
    int width, height; // width & height for the image reader
    unsigned char* image;
    GLuint tex;
    glGenTextures(1, &tex);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D, tex);


    image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // binding image data
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    return tex;
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1000,800);                   //output window size is set here
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D_MODEL_LOADING");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
