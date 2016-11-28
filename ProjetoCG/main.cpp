#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "Camera.h"
#include "SOIL.h"
#include "AABB.h"

using namespace std;
using namespace sowi;

Camera camera;

float a = 15.0f;
float b = 10.0f;
float c = 6.0f;
float d = 7.0f;
float h = 10.0f;
GLuint textures[5];

tAABB pz1 = {45.0f, 15.6f, -45.0f, 14.4f};
tAABB pz2 = {45.0f, -14.4f, -45.0f, -15.6f};
tAABB pz3 = {23.0f, -9.1f, 20.0f, -11.1f};
tAABB pz4 = {34.0f, 4.1f, 37.0f, 2.1f};
tAABB pz5 = {32.0f, 1.1f, 34.0f, -1.1f};
tAABB pz6 = {34.0f, 12.1f, 31.0f, 10.1f};
tAABB pz7 = {32.0f, 1.1f, 34.0f, -1.1f};
tAABB pz8 = {37.0f, 9.1f, 45.0f, 7.1f};
tAABB pz9 = {37.0f, 12.1f, 45.0f, 10.1f};

tAABB px1 = {16.1f, 7.0f, 14.1f, -15.0f};
tAABB px2 = {-14.1f, 7.0f, -16.1f, -15.0f};
tAABB px3 = {16.1f, 15.0f, 14.1f, 10.0f};
tAABB px4 = {-14.1f, 15.0f, -16.1f, 10.0f};
tAABB px5 = {46.1f, 15.0f, 44.1f, -15.0f};
tAABB px6 = {-44.1f, 15.0f, -46.1f, -15.0f};
tAABB px7 = {21.1f, 15.0f, 19.1f, -10.0f};
tAABB px8 = {24.1f, 15.0f,22.1f, -10.0f};
tAABB px9 = {35.1f, 3.0f, 33.1f, -15.0f};
tAABB px10 = {38.1f, 3.0f, 36.1f, -15.0f};
tAABB px11 = {29.1f, 3.0f, 27.1f, 0.0f};
tAABB px12 = {35.1f, 3.0f, 33.1f, 0.0f};
tAABB px13 = {33.1f, 11.0f, 35.1f, 3.0f};
tAABB px14 = {30.1f, 11.0f, 32.1f, 3.0f};
tAABB px15 = {36.1f, 11.0f, 34.1f, 8.0f};

tAABB inZ[9] = {pz1, pz2, pz3, pz4, pz5, pz6, pz7, pz8, pz9};
tAABB inX[15] = {px1, px2, px3, px4, px5, px6, px7, px8, px9, px10, px11, px12, px13, px14, px15};

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition1[]= { 0.0f, 10.0f, 0.0f, 1.0f };
GLfloat LightPosition2[]= { ((-a)*2), 10.0f, 0.0f, 1.0f };
GLfloat LightPosition3[]= { ((a)*2), 10.0f, 0.0f, 1.0f };

bool AABBtoAABB(const tAABB& tBox1, const tAABB& tBox2){
		return(tBox1.MaxX < tBox2.MaxX &&
			   tBox1.MinX > tBox2.MinX &&
			   tBox1.MaxZ < tBox2.MaxZ &&
			   tBox1.MinZ > tBox2.MinZ);
}
void outofBox(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			p->move = false;
		}
}

int LoadGLTextures()
{
    textures[0] = SOIL_load_OGL_texture
        (
        "imagens/chess.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	textures[1] = SOIL_load_OGL_texture
        (
        "imagens/red.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	textures[2] = SOIL_load_OGL_texture
        (
        "imagens/blue.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    textures[3] = SOIL_load_OGL_texture
        (
        "imagens/green.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    textures[4] = SOIL_load_OGL_texture
        (
        "imagens/black.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;
}

void DrawCubo()
{
	float lado = 0.5f;

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
		//baixo
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-lado, -lado, -lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(lado, -lado, -lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(lado, -lado, lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-lado, -lado, lado);
		//esquerda
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-lado, -lado, -lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-lado, -lado, lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-lado, lado, lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-lado, lado, -lado);
		//tras
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-lado, -lado, -lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-lado, lado, -lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(lado, lado, -lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(lado, -lado, -lado);
		//direita
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(lado, -lado, -lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(lado, lado, -lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(lado, lado, lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(lado, -lado, lado);
		//frente
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(lado, lado, lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-lado, lado, lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-lado, -lado, lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(lado, -lado, lado);
		//cima
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(lado, lado, lado);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(lado, lado, -lado);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-lado, lado, -lado);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-lado, lado, lado);

	glEnd();
}

void Draw1(){
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS);
		//piso
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, 0.0f, a);
		glEnd();
		glBegin(GL_QUADS);
		//teto
		glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, h, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, h, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		//parede da direita
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(a, h, -a);
		glEnd();
		glBegin(GL_QUADS);
		//esquerda 1
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-a, 0.0f, d);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-a, h, d);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();
		glBegin(GL_QUADS);
		//esquerda 2
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, c, d);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-a, c, b);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-a, h, b);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, d);
		glEnd();
		glBegin(GL_QUADS);
		//esquerda 3
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, b);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, b);
		glEnd();
		glBegin(GL_QUADS);
		//frente
		glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		glBegin(GL_QUADS);
		//tras
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();

		glPushMatrix();
			glTranslatef(12.0f,2.5f,-12.0f);
			DrawCubo();
		glPopMatrix();
		glColor4f(0.0f,0.0f,0.0f,0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, h, -10.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, h, a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, h, a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, 0.0f, a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, 0.0f, -10.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, h, -10.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, h, -10.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f, 0.0f, -10.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, h, -10.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 3.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, -a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, -a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 3.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, -a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, -a);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 3.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, h, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 0.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, h, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, h, 0.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, h, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 3.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 11.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, h, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 3.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, h, 11.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, h, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(4.0f, h, 11.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 8.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 8.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 11.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 8.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 8.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 8.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, h, 8.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, h, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, 0.0f, 11.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(7.0f, h, 11.0f);
		glEnd();
		glDisable(GL_BLEND);
}

void Draw2(){
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS);
		//piso
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, 0.0f, a);
		glEnd();
		glBegin(GL_QUADS);
		//teto
		glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, h, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, h, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10.715f, 0.01f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(6.43f, 0.01f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(6.43f, 0.01f, 5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(10.715f, 0.01f, 5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.145f, 0.01f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.14f, 0.01f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.14f, 0.01f, -5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(2.145f, 0.01f, -5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.71f, 0.01f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-6.25f, 0.01f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-6.25f, 0.01f, 5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.71f, 0.01f, 5.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10.715f, 0.01f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(6.43f, 0.01f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(6.43f, 0.01f, -5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(10.715f, 0.01f, -5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.145f, 0.01f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.14f, 0.01f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.14f, 0.01f, 5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(2.145f, 0.01f, 5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.71f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-6.25f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-6.25f, 0.01f, 5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.71f, 0.01f, 5.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10.715f, 0.01f, 5.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(6.43f, 0.01f, 5.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(6.43f, 0.01f, -5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(10.715f, 0.01f, -5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(2.145f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.14f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.14f, 0.01f, 5.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(2.145f, 0.01f, 5.0f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.71f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-6.25f, 0.01f, -5.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-6.25f, 0.01f, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.71f, 0.01f, -a);
		glEnd();
		//parede da esquerda
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();
		glBegin(GL_QUADS);
		//direita 1
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, d);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, d);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(a, h, -a);
		glEnd();
		glBegin(GL_QUADS);
		//direita 2
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(a, c, d);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, c, b);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, b);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(a, h, d);
		glEnd();
		glBegin(GL_QUADS);
		//direita 3
		glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(a, 0.0f, b);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(a, h, b);
		glEnd();
		glBegin(GL_QUADS);
		//frente
		glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		glBegin(GL_QUADS);
		//tras
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();

		glPushMatrix();
			glTranslatef(-14.0f,2.5f, 0.0f);
			DrawCubo();
		glPopMatrix();
}

void Draw3(){
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glBegin(GL_QUADS);
		//piso
		glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, 0.0f, a);
		glEnd();
		glBegin(GL_QUADS);
		//teto
		glNormal3f(0.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, h, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, h, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glBegin(GL_QUADS);
		//frente
		glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, a);
		glEnd();
		glBegin(GL_QUADS);
		//tras
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();
}

void free_mem(void)
{
	std::clog << "Exiting...\n";
}
void mexerCamera(int x, int y){
	camera.lookerCamera(x, y);
}
void keyPressed(unsigned char key, int x, int y){
	camera.keyPressed(key, x, y);
}
void keyUp(unsigned char key, int x, int y){
	camera.keyUp(key, x, y);
}
void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, camera.width, camera.height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55.0f, 1.0f, 0.1f, 100.0f);

	camera.mover();

	for(int i = 0; i < 9; i++){
		outofBox(&camera, inZ[i]);
	}
	for(int i = 0; i < 15; i++){
		outofBox(&camera, inX[i]);
	}

	camera.attAABB();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	camera.posx, camera.posy, camera.posz, //posição da camera
				camera.camx, camera.camy, camera.camz,	//look at da camera
				0.0f, 1.0f, 0.0f);  //vetor UP da camera


	Draw3();
	glPushMatrix();
		glTranslatef((-a*2), 0.0f, 0.0f);
		Draw2();
	glPopMatrix();
	glPushMatrix();
		glTranslatef((a*2), 0.0f, 0.0f);
		Draw1();
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	std::clog << "Begin...\n";

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
	glutInitWindowSize(camera.width, camera.height);
	glutInitWindowPosition(400,150);
	glutCreateWindow("GTFO");
	glutSetCursor(GLUT_CURSOR_NONE);

    if (!LoadGLTextures())
    {
        return false;
    }

	glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHTING);

	glutDisplayFunc(display);

	glutPassiveMotionFunc(mexerCamera);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	atexit(free_mem);

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	glutMainLoop();

	return 0;
}
