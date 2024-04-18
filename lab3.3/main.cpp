#include "glew.h"
#include "glut.h"
#include <math.h>
// ��������� ���������
GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

// ���������� ��� ��������� �����
void RenderScene(void)
{
	// ���� �������� ������� �����/����
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;
	static float fnearRot = 0.0f;
	static float ffarRot = 0.0f;
	// ������� ���� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// ����������� ��� ����� � ���� ������
	glTranslatef(0.0f, 0.0f, -300.0f);
	// ������������� ���� ��������� �������
	// ������
	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 0);
	glutSolidSphere(15.0f, 30, 17);
	glEnable(GL_LIGHTING);
	// �������� ��������� �����, ����� ���������� ������!
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPushMatrix();
	// ������� ������� ���������
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
	// ���������� �����
	glColor3ub(0, 0, 255);
	glTranslatef(105.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 30, 17);


	// ������� � ������� ���������, ��������� � ������
	// � ����������� ����
	glColor3ub(200, 200, 200);
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	fMoonRot += 1.5f;
	if (fMoonRot > 360.0f)
		fMoonRot = 0.0f;
	glutSolidSphere(6.0f, 30, 17);
	glPopMatrix();

	// ��� �� ������ ����� ����� ���� ��������
	fEarthRot += 1.0f;
	if (fEarthRot > 360.0f)
		fEarthRot = 0.0f;

	glPushMatrix();
	fnearRot += 2.f;
	fnearRot = fnearRot > 360.f ? 0.f : fnearRot;
	glRotatef(10.f, 0.f, 0.f, 1.f);
	glRotatef(fnearRot * 2 , 0.f, 1.f, 0.f);
	glTranslatef(0.0f, 0.0f, 50.f );
	glColor3f(0.34f, 0.94f, 0.11f);
	glutSolidSphere(7.0f, 30, 17);

	glRotatef(2*fnearRot, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 20.f);
	
	glColor3f(0.7f, 0.3f, 0.51f);
	glutSolidSphere(3.0f, 30, 17);

	glPopMatrix();


	glPushMatrix();
	ffarRot += .5f;
	ffarRot = ffarRot > 360.f ? 0.f : ffarRot;
	glRotatef(20.f, 0.f, 0.f, 1.f);
	glRotatef(ffarRot, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 150.f);

	glColor3f(0.2f, 0.6f, 0.9f);
	glutSolidSphere(30.0f, 30, 17);

	glRotatef(110.f, 1.f, 0.f, 0.f);
	glColor3f(0.7f, 0.4f, 0.9f);
	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(-1.f, 50.f, 0.f);
	for (float angle = 0.f; angle <= 720.f + 1; angle += 1.f)
	{
		glVertex2f(50*sin(angle), 50*cos(angle));
	}

	glEnd();

	glPushMatrix();
	glRotatef(180.f, 1.f, 0.f, 0.f);

	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(-1.f, 50.f, 0.f);
	for (float angle = 0.f; angle <= 720.f + 1; angle += 1.f)
	{
		glVertex2f(50 * sin(angle), 50 * cos(angle));
	}

	glEnd();

	glPopMatrix();

	
	
	

	glPopMatrix();
	// ����������������� ��������� �������
	glPopMatrix(); // ������� ���������� ������
	
	// ������������ ����������� �����������
	glutSwapBuffers();
}
// ������� ��������� ��� ����������� ������������� � ���������
//������������
void SetupRC()
{
	// ��������� ����� � ����������
	glEnable(GL_DEPTH_TEST); // �������� ������� ������������
	glFrontFace(GL_CCW); //�������������� � ������� ������ //������� ������� ���������� ������
	glEnable(GL_CULL_FACE); //������� ������ �������� �� �����������
	// ��������� ���������
	glEnable(GL_LIGHTING);
	// ��������������� � �������������� �������� ����� 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// ������������ ������������ ������
	glEnable(GL_COLOR_MATERIAL);
	// �������� ���������� ������������� ����� glCo-lor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// �����-����� ���
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(2, TimerFunc, 1);
}
void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	// ������������� ������� �� ����
	if (h == 0)
		h = 1;
	// ������ ���� ��������� ��������������� ������ ������� ����
	glViewport(0, 0, w, h);
	// ������ ����������� ������ ����
	fAspect = (GLfloat)w / (GLfloat)h;
	// ������������� ������������� ������� ���������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ���� ������ ����� 45 ��������, ������� � ������� ���������
	// �������� ����� 1 � 425
	gluPerspective(45.0f, fAspect, 1.0, 625.0);
	// ��������� ������� ���������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Solar System");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}