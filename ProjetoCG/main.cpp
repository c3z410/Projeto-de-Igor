#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "Camera.h"
#include "SOIL.h"
#include "AABB.h"
#include "objLoader.h"

using namespace std;
using namespace sowi;

bool c1 = false;
bool c2 = false;
bool close = false;

Camera camera;
objLoader *objData;

float r = 0.0f;
float a = 15.0f;
float b = 10.0f;
float c = 6.0f;
float d = 7.0f;
float h = 10.0f;
GLuint textures[7];

tAABB p1 = {45.6f, 15.6f, -45.6f, 14.4f};
tAABB p15 = {45.6f, -14.4f, 1.9f, -15.6f};
tAABB p14 = {-1.9f, -14.4f, -45.6f, -15.6f};
tAABB p2 = {45.6f, -14.4f, -45.6f, -15.6f};
tAABB p3 = {23.6f, 15.6f, 19.4f, -10.6f};
tAABB p4 = {37.6f, 3.6f, 33.4f, -15.6f};
tAABB p5 = {34.6f, 3.6f, 27.6f, -0.6f};
tAABB p6 = {34.6f, 11.6f, 30.4f, 2.4f};
tAABB p7 = {45.6f, 11.6f, 36.4f, 7.4f};
tAABB p8 = {15.6f, 7.6f, 14.4f, -15.6f};
tAABB p9 = {-14.4f, 7.6f, -15.6f, -15.6f};
tAABB p10 = {15.6f, 15.6f, 14.4f, 9.4f};
tAABB p11 = {-14.4f, 15.6f, -15.6f, 9.4f};
tAABB p12 = {45.6f, 15.6f, 44.4f, -15.6f};
tAABB p13 = {-44.4f, 15.6f, -45.6f, -15.6};

tAABB X1 = {50.0f, -15.0f, -50.0f, -17.0f};

tAABB s1 = {-28.455f, -4.4f, -31.54f, -15.6f};
tAABB s2 = {-36.85f, 5.6f, -40.1f, -5.6f};
tAABB s3 = {-19.885f, 5.6f, -22.97f, -5.6f};

tAABB s4 = {-19.885f, 15.6f, -22.97f, 4.4f};
tAABB s5 = {-36.85f, 15.6f, -40.1f, 4.4f};
tAABB s6 = {-19.885f, -4.4f, -22.97f, -15.6f};
tAABB s7 = {-28.455f, 15.6f, -31.54f, 4.4f};
tAABB s8 = {-28.455f, 5.6f, -31.54f, -5.6f};
tAABB s9 = {-36.85f, -4.4f, -40.1f, -15.6f};

tAABB cubo1 = {43.1f, -10.9f, 40.9f, -13.1f};
tAABB cubo2 = {-42.9f, 1.1f, -45.1f, -1.1f};

tAABB cubos[2] = {cubo1, cubo2};
tAABB gg[3] = {s1, s2, s3};
tAABB ff[6] = {s4, s5, s6, s7, s8, s9};
tAABB in[13] = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13};
tAABB in2[14] = {p1, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};

GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition1[]= { 0.0f, 9.9f, 0.0f, 1.0f };
GLfloat LightPosition2[]= { ((-a)*2), 9.9f, 0.0f, 1.0f };
GLfloat LightPosition3[]= { ((a)*2), 9.9f, 0.0f, 1.0f };

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
void FIM(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			close = true;
			glutDestroyWindow(1);
		}
}
void inBoxF(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			p->futposx = -15.0f;
			p->futposz = 8.5f;
		}
}

void pegaC1(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			c1 = true;
			p->futposx = 15.0f;
			p->futposz = 8.5f;
		}
}
void pegaC2(Camera *p, tAABB sala){
		if((AABBtoAABB(p->futplayer, sala))){
			c2 = true;
			p->futposx = -15.0f;
			p->futposz = 8.5f;
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

    if(textures[1] == 0)
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

    if(textures[2] == 0)
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

    if(textures[3] == 0)
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

    if(textures[4] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    textures[5] = SOIL_load_OGL_texture
        (
        "imagens/porta.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[5] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    textures[6] = SOIL_load_OGL_texture
        (
        "imagens/yellow.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(textures[6] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;
}

void DrawCubo()
{
	/*float lado = 0.5f;

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

	glEnd();*/
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glBegin(GL_QUADS);
		for(int i=0; i<objData->faceCount; i++)
		{
			obj_face *o = objData->faceList[i];

			glTexCoord2f(0.0f, 0.0f); glVertex3f(objData->vertexList[o->vertex_index[0]]->e[0], // primeira linha
						objData->vertexList[o->vertex_index[0]]->e[1],
						objData->vertexList[o->vertex_index[0]]->e[2]);
			glVertex3f(objData->vertexList[o->vertex_index[1]]->e[0],
						objData->vertexList[o->vertex_index[1]]->e[1],
						objData->vertexList[o->vertex_index[1]]->e[2]);

			glTexCoord2f(1.0f, 0.0f); glVertex3f(objData->vertexList[o->vertex_index[1]]->e[0],	// segunda linha
						objData->vertexList[o->vertex_index[1]]->e[1],
						objData->vertexList[o->vertex_index[1]]->e[2]);
			glVertex3f(	objData->vertexList[o->vertex_index[2]]->e[0],
						objData->vertexList[o->vertex_index[2]]->e[1],
						objData->vertexList[o->vertex_index[2]]->e[2]);

			glTexCoord2f(0.0f, 1.0f); glVertex3f(objData->vertexList[o->vertex_index[2]]->e[0],	// terceira linha
						objData->vertexList[o->vertex_index[2]]->e[1],
						objData->vertexList[o->vertex_index[2]]->e[2]);
			glVertex3f(	objData->vertexList[o->vertex_index[0]]->e[0],
						objData->vertexList[o->vertex_index[0]]->e[1],
						objData->vertexList[o->vertex_index[0]]->e[2]);
		}
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
		if(!(c1)){
		glPushMatrix();
			glTranslatef(12.0f,2.5f,-12.0f);
			glRotatef(r, 0, 1, 0);
			DrawCubo();
		glPopMatrix();
		}
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
		
		if(!(c2)){
		glPushMatrix();
			glTranslatef(-14.0f,2.5f, 0.0f);
			glRotatef(r, 0, 1, 0);
			DrawCubo();
		glPopMatrix();
		}
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
		//tras
		if((!(c1)) || (!(c2))){
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(a, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, 0.0f, -14.9f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f, 0.0f, -14.9f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f, c, -14.9f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, c, -14.9f);
		glEnd();
		} else {
		glBegin(GL_QUADS);	
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(a, h, -a);
		glEnd();
		glBegin(GL_QUADS);	
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-a, 0.0f, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, 0.0f, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.5f, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, h, -a);
		glEnd();
		glBegin(GL_QUADS);	
		glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, c, -a);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(2.5f, c, -a);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f, h, -a);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.5f, h, -a);
		glEnd();
		}
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
	gluPerspective(55.0f, 1.0f, 0.001f, 100.0f);

	camera.mover();
	if((!(c1)) || (!(c2))){
		for(int i = 0; i < 13; i++){
			outofBox(&camera, in[i]);
		}
	} else {
		for(int i = 0; i < 14; i++){
			outofBox(&camera, in2[i]);
		}
	}

	camera.attAABB();
	
	for(int i = 0; i < 6; i++){
		inBoxF(&camera, ff[i]);
	}
	
	pegaC1(&camera, cubo1);
	pegaC2(&camera, cubo2);
	
	FIM(&camera, X1);

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
	
	r += 3.0f;

	if(!close){
		glutSwapBuffers();
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	std::clog << "Begin...\n";
	
	objData = new objLoader();			
	objData->load("monkey_head2.obj");
	
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
