#include "glew.h"
#include "glut.h"
// �������� ��������
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// ������ ����������� ����� � ���� ���������
// ���������� ��� ��������� �������� ����
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;
	// ������������� ������� �� ����
	if (h == 0)
		h = 1;
	// ������������� ���� ��������� �� �������� ����
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	// ��������� ���� ������� ��������������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ���������� ������������� ��������
	gluPerspective(60.0f, fAspect, 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// ��� ������� ��������� ����������� ������������� � ���������
// ������������. � ������ ������ ���������������
// � ���������������� ��������� �����.
void SetupRC()
{
	// ��������� ��������� � ����������
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
	glEnable(GL_DEPTH_TEST); // �������� ������� ������������
	glFrontFace(GL_CCW); // �������������� � ������� ������ //������� ������� ���������� ������
	glEnable(GL_CULL_FACE); // ������� ������ �������� �� �����������
	// ����������� ���������
	glEnable(GL_LIGHTING);
	// ��������������� � �������������� �������� ����� 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// ������������ ������������ ������
	glEnable(GL_COLOR_MATERIAL);
	// �������� ���������� ������������� ����� glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// �����-����� ���
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
// ��������� �� ������� �� ���������, ������ ������� ������� ������
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);
	// ��������� ����
	glutPostRedisplay();
}
// ���������� ��� ��������� �����
void RenderScene(void)
{
	// ������� ���� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������������ ��������� ������� � ����������� ��������
	glPushMatrix();
	glTranslatef(0.0f, -30.0f, -100.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// � �������� �������� ����� ��������� ������ �������
	glColor3f(1.0f, 0.0f, 0.0f);

	float zWidth = 15.f;
	//������� �����
	glBegin(GL_POLYGON);
	glVertex3f(-25.f, 0, zWidth);
	glVertex3f(25.f, 0, zWidth);
	glVertex3f(35.f, 25.f, zWidth);
	glVertex3f(-35.f, 25.f, zWidth);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 25.f, -zWidth);
	glVertex3f(35.f, 25.f, -zWidth);
	glVertex3f(25.f, 0, -zWidth);
	glVertex3f(-25.f, 0, -zWidth);
	glEnd();

	//�������� � ������ �����
	glColor3f(0.9f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-25.f, 0.f, zWidth);
	glVertex3f(-35.f, 25.f, zWidth);
	glVertex3f(-35.f, 25.f, -zWidth);
	glVertex3f(-25.f, 0, -zWidth);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(25.f, 0.f, zWidth);
	glVertex3f(25.f, 0.f, -zWidth);
	glVertex3f(35.f, 25.f, -zWidth);
	glVertex3f(35.f, 25.f, zWidth);
	glEnd();
	
	//��� � ����

	glColor3f(0.f, 0.3f, 0.2f);
	glBegin(GL_POLYGON);
	glVertex3f(-25.f, 0.f, -zWidth);
	glVertex3f(25.f, 0.f, -zWidth);
	glVertex3f(25.f, 0.f, zWidth);
	glVertex3f(-25.f, 0.f, zWidth);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 25.f, zWidth);
	glVertex3f(35.f, 25.f, zWidth);
	glVertex3f(35.f, 25.f, -zWidth);
	glVertex3f(-35.f, 25.f, -zWidth);
	glEnd();

	//������� ������� ����� ��������

	glColor3f(0.1f, 0.7f, 0.1f);
	glBegin(GL_POLYGON);
	glVertex3f(-20.f, 25.f, zWidth);
	glVertex3f(0.f, 50.f, zWidth);
	glVertex3f(0.f, 50.f, -zWidth);
	glVertex3f(-20.f, 25.f, -zWidth);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(20.f, 25.f, -zWidth);
	glVertex3f(0.f, 50.f, -zWidth);
	glVertex3f(0.f, 50.f, zWidth);
	glVertex3f(20.f, 25.f, zWidth);
	glEnd();

	glColor3f(0.1f, 0.5f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-20.f, 25.f , zWidth);
	glVertex3f(20.f, 25.f, zWidth);
	glVertex3f(0.f, 50.f, zWidth);

	glVertex3f(0.f, 50.f, -zWidth);
	glVertex3f(20.f, 25.f, -zWidth);
	glVertex3f(-20.f, 25.f, -zWidth);
	glEnd();


	// ����������������� ��������� �������
	glPopMatrix();
	// ����� ������
	glutSwapBuffers();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Perspective Projection");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}