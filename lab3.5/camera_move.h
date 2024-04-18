#pragma once
#include "glew.h"
#include "glut.h"



namespace cam
{
	class Camera
	{
		double d = 0.1;
		double cur_rot_x = 0;
		double cur_rot_y = 0;
		public:	
			Camera() { this->d = 0.1; };
			void move(unsigned char key, int x, int y) 
			{
				glRotatef(cur_rot_x, 1.f, 0.f, 0.f);
				glRotatef(cur_rot_y, 0.f, 1.f, 0.f);
				switch (key)
				{
				case 'w':
					glTranslatef(0, 0, d);
					//gltMoveFrameForward(&frameCamera, 0.1f);
					break;
				case 's':
					glTranslatef(0, 0, -d);
					//gltMoveFrameForward(&frameCamera, -0.1f);
					break;
				case 'a':
					glTranslatef(d, 0, 0);
					//gltRotateFrameLocalY(&frameCamera, 0.1);
					break;
				case 'd':
					glTranslatef(-d, 0, 0);
					//gltRotateFrameLocalY(&frameCamera, -0.1);
					break;
				case ' ':
					if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
					{
						glTranslatef(0, d, 0);
						//gltMoveFrameUp(&frameCamera, -0.1);
					}
					else
					{
						glTranslatef(0, -d, 0);
						//gltMoveFrameUp(&frameCamera, 0.1);
					}
					break;
				}
				//gltApplyCameraTransform(&frameCamera);
				glutPostRedisplay();
			};

			void rotate(int key, int x, int y) 
			{
				switch (key)
				{
				case GLUT_KEY_UP:
					cur_rot_x -= d;
					glRotatef(-d, 1.f, 0.f, 0.f);
					break;
				case GLUT_KEY_DOWN:
					cur_rot_x += d;
					glRotatef(d, 1.f, 0.f, 0.f);
					break;
				case GLUT_KEY_LEFT:
					cur_rot_y -= d;
					glRotatef(-d, 0.f, 1.f, 0.f);
					break;
				case GLUT_KEY_RIGHT:
					cur_rot_y += d;
					glRotatef(d, 0.f, 1.f, 0.f);
					break;
				}
				/*if (key == GLUT_KEY_UP)
					
				if (key == GLUT_KEY_DOWN)
					*/
				//if (key == 16)
				//	gltMoveFrameUp(&frameCamera, -0.1);
				//gltApplyCameraTransform(&frameCamera);
				glutPostRedisplay();
			};
			void set(double v) { this->d = v; };
	};
}
