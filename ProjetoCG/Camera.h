#ifndef CAMERA_H_
#define CAMERA_H_
#include "AABB.h"

namespace sowi{
	
class Camera{
	public:
		Camera();	
		virtual ~Camera();
		void frenteStart();
		void frenteStop();
		void trasStart();
		void trasStop();
		void esquerdaStart();
		void esquerdaStop();
		void direitaStart();
		void direitaStop();
		
		void lookerCamera(int x, int y);
		void keyPressed(unsigned char key, int x, int y);
		void keyUp(unsigned char key, int x, int y);
		void mover();
		void attAABB();
		
		tAABB player;
		GLdouble posx, posy, posz;
		GLdouble lookx, looky, lookz;
		GLdouble camx, camy, camz;
		
		bool frente, esquerda, direita, tras;
		
		float sensmove;
		float mousePosx, mousePosy;
		int timer, width, height;
	};
}
#endif
		
