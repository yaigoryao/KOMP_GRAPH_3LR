#include "glew.h"
#include "glut.h"
// Величина поворота
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Вызывается при изменении размеров окна
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 70.0f;
	
	// Предотвращает деление на нуль
	if (h == 0)
		h = 1;
	// Устанавливает размеры поля просмотра равны размерам окна glViewport(0, 0, w, h);
	// Устанавливаем перспективную систему координат
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Устанавливает объем отсечения с помощью отсекающих
	// плоскостей (левая, правая, нижняя, верхняя,
	// ближняя, дальняя)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange * 2.0f, nRange * 2.0f);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange * 2.0f, nRange * 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
// Эта функция выполняет необходимую инициализацию в контексте
// визуализации. В данном случае устанавливается
// и инициализируется освещение сцены.
void SetupRC()
{
	// Параметры света
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
	glEnable(GL_DEPTH_TEST); // Удаление скрыьых поверхностей
	glFrontFace(GL_CCW); //Многоугольники с обходом против //часовой стрелки направлены наружу
	glEnable(GL_CULL_FACE); // Расчеты внутри самолета не
	// выполняются
	// Активизация освещения
	glEnable(GL_LIGHTING);
	// Устанавливается и активизируется источник света 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	// Активизирует согласование цветов
	glEnable(GL_COLOR_MATERIAL);
	// Свойства материалов соответствуют кодам glColor glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// Темно-синий фон
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
// Реагирует на клавиши со стрелками, двигая систему отсчета камеры
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
	// Обновляем окно
	glutPostRedisplay();
}
// Вызывается для рисования сцены
void RenderScene(void)
{
	float fZ, bZ;
	// Очищаем окно текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	fZ = 100.0f;
	bZ = -100.0f;
	// Записываем состояние матрицы и выполняем поворот
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	// В качестве текущего цвета рисования задает красный glColor3f(1.0f, 0.0f, 0.0f);
	// Лицевая часть ///////////////////////////////////
	glColor3f(1.0f, 0.0f, 0.0f);

	///////////////////// "форма стрелочки"
	
	//боковые грани
	glPushMatrix();
	glTranslatef(0.f, 0.f, 15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-35.f, 0, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-20.f, 25.f, 0.f);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.f, 0.f, -15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-20.f, 25.f, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-35.f, 0, 0.f);
	glEnd();
	glPopMatrix();

	//передняя грань
	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 0.f,15.f);
	glVertex3f(-20.f, 25.f, 15.f);

	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-35.f, 0.f, -15.f);
	glEnd();

	glPushMatrix();
	glRotated(180.f, 1.f, 0.f, 0.f);

	glPushMatrix();
	glTranslatef(0.f, 0.f, 15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-35.f, 0, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-20.f, 25.f, 0.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-20.f, 25.f, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-35.f, 0, 0.f);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 0.f, 15.f);
	glVertex3f(-20.f, 25.f, 15.f);

	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-35.f, 0.f, -15.f);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(-20.f, -25.f,-15.f);
	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-20.f, 25.f, 15.f);
	glVertex3f(-20.f, -25.f, 15.f);
	glEnd();

	/////////////////
	//дублируем с поворотом 
	
	glPushMatrix();
	glRotatef(180.f, 0.f, 0.f, 1.f);
	glTranslatef(-25.f, 0.f, 0.f);
	//боковые грани
	glPushMatrix();
	glTranslatef(0.f, 0.f, 15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-35.f, 0, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-20.f, 25.f, 0.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-20.f, 25.f, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-35.f, 0, 0.f);
	glEnd();
	glPopMatrix();

	//передняя грань
	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 0.f, 15.f);
	glVertex3f(-20.f, 25.f, 15.f);

	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-35.f, 0.f, -15.f);
	glEnd();

	glPushMatrix();
	glRotated(180.f, 1.f, 0.f, 0.f);

	glPushMatrix();
	glTranslatef(0.f, 0.f, 15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-35.f, 0, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-20.f, 25.f, 0.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.f, 0.f, -15.f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-20.f, 25.f, 0.f);
	glVertex3f(-20.f, 0, 0.f);
	glVertex3f(-35.f, 0, 0.f);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(-35.f, 0.f, 15.f);
	glVertex3f(-20.f, 25.f, 15.f);

	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-35.f, 0.f, -15.f);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glVertex3f(-20.f, -25.f, -15.f);
	glVertex3f(-20.f, 25.f, -15.f);
	glVertex3f(-20.f, 25.f, 15.f);
	glVertex3f(-20.f, -25.f, 15.f);
	glEnd();


	glPopMatrix();
	////////////////////////////////
	// соединительный "мост"
	glColor3b(0, 127, 0);
	glBegin(GL_QUADS);
	glVertex3f(50.f, -15.f, -15.f);
	glVertex3f(50.f, -15.f, 15.f);
	glVertex3f(-25.f, -15.f, 15.f);
	glVertex3f(-25.f, -15.f, -15.f);
	glColor3b(64, 127, 32);
	glVertex3f(45.f, -15.f, 15.f);
	glVertex3f(45.f, 15.f, 15.f);
	glVertex3f(-20.f, 15.f, 15.f);
	glVertex3f(-20.f, -15.f, 15.f);
	
	glEnd();

	glPushMatrix();

	glRotatef(180.f, 1.f, 0.f, 0.f);
	glColor3b(0, 127, 0);
	glBegin(GL_QUADS);
	glVertex3f(50.f, -15.f, -15.f);
	glVertex3f(50.f, -15.f, 15.f);
	glVertex3f(-25.f, -15.f, 15.f);
	glVertex3f(-25.f, -15.f, -15.f);
	glColor3b(64, 127, 32);
	glVertex3f(45.f, -15.f, 15.f);
	glVertex3f(45.f, 15.f, 15.f);
	glVertex3f(-20.f, 15.f, 15.f);
	glVertex3f(-20.f, -15.f, 15.f);

	glEnd();

	glPopMatrix();
	// Восстанавливается состояние матрицы
	glPopMatrix();

	// Буфер-обмена
	glutSwapBuffers();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Orthographic Projection");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	SetupRC();
	glutMainLoop();
	return 0;
}