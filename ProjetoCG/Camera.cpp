#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "Camera.h"

#define PI 3.14159265

using namespace std;

namespace sowi{

	Camera::Camera(){
		move = true;
		futposx = 0.0f;
		futposz = 0.0f;
		posx = 0.0f;
		posy = 3.0f;
		posz = 0.0f;
		lookx = 0.0f;
		looky = 0.0f;
		lookz = 0.0f;
		camx = 0.0f;
		camy = 0.0f;
		camz = 0.0f;
		frente = false;
		direita = false;
		esquerda = false;
		tras = false;
		sensmove = 0.08f;
		timer = 0;
		mousePosx = 180.0f;
		mousePosy = 95.0f;
		width = 800;
		height = 600;
		player = {0.5f, 0.5f, -0.5f, -0.5f};
		futplayer = {0.5f, 0.5f, -0.5f, -0.5f};
	}
	Camera::~Camera(){

	}
	void Camera::frenteStart(){
		frente = true;
	}
	void Camera::frenteStop(){
		frente = false;
	}
	void Camera::direitaStart(){
		direita = true;
	}
	void Camera::direitaStop(){
		direita = false;
	}
	void Camera::esquerdaStart(){
		esquerda = true;
	}
	void Camera::esquerdaStop(){
		esquerda = false;
	}
	void Camera::trasStart(){
		tras = true;
	}
	void Camera::trasStop(){
		tras = false;
	}

	void Camera::keyPressed(unsigned char key, int x, int y){
		if(key == 'w'){
			frenteStart();
		}
		if(key == 'a'){
			esquerdaStart();
		}
		if(key == 's'){
			trasStart();
		}
		if(key == 'd'){
			direitaStart();
		}
	}

	void Camera::keyUp(unsigned char key, int x, int y){
		if(key == 'w'){
			frenteStop();
		}
		if(key == 'a'){
			esquerdaStop();
		}
		if(key == 's'){
			trasStop();
		}
		if(key == 'd'){
			direitaStop();
		}
	}

	void Camera::lookerCamera(int x, int y){
		mousePosx -= (x - (width/2))*0.1f;
		mousePosy += (y - (height/2))*0.1f;
		if(mousePosy > 180){
			mousePosy = 180.0f;
		}
		else if(mousePosy < 0.0000001){
			mousePosy = 0.0000001f;
		}
	}

	void Camera::mover(){

		int atualtimer = glutGet(GLUT_ELAPSED_TIME);
		int intervalo = atualtimer - timer;

		lookx = sin(mousePosy*PI/180)*sin(mousePosx*PI/180);
		looky = cos(mousePosy*PI/180);
		lookz = sin(mousePosy*PI/180)*cos(mousePosx*PI/180);

		if(frente){
			futposx += intervalo * lookx / 10*sensmove;
			futposz += intervalo * lookz / 10*sensmove;
		}
		if(esquerda){
			futposx += intervalo * sin((mousePosx+90)*PI/180) / 10*sensmove;
			futposz += intervalo * cos((mousePosx+90)*PI/180) / 10*sensmove;
		}
		if(tras){
			futposx -= intervalo * lookx / 10*sensmove;
			futposz -= intervalo * lookz / 10*sensmove;
		}
		if(direita){
			futposx -= intervalo * sin((mousePosx+90)*PI/180) / 10*sensmove;
			futposz -= intervalo * cos((mousePosx+90)*PI/180) / 10*sensmove;
		}

		timer = atualtimer;
		glutWarpPointer(width/2,height/2);

		futplayer.MaxX = futposx + 0.5f;
		futplayer.MaxZ = futposz + 0.5f;
		futplayer.MinX = futposx - 0.5f;
		futplayer.MinZ = futposz - 0.5f;

		camx = posx + lookx;
		camy = posy + looky;
		camz = posz + lookz;
	}

	void Camera::attAABB(){
		if(move){
			posx = futposx;
			posz = futposz;
			player.MaxX = posx + 0.5f;
			player.MaxZ = posz + 0.5f;
			player.MinX = posx - 0.5f;
			player.MinZ = posz - 0.5f;

			futplayer.MaxX = player.MaxX;
			futplayer.MaxZ = player.MaxZ;
			futplayer.MinX = player.MinX;
			futplayer.MinZ = player.MinZ;

			camx = posx + lookx;
			camy = posy + looky;
			camz = posz + lookz;
		} else {
			futposx = posx;
			futposz = posz;
			futplayer.MaxX = futposx + 0.5f;
			futplayer.MaxZ = futposz + 0.5f;
			futplayer.MinX = futposx - 0.5f;
			futplayer.MinZ = futposz - 0.5f;

			camx = posx + lookx;
			camy = posy + looky;
			camz = posz + lookz;

			move = true;
		}
	}
}
