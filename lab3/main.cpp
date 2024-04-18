#define _USE_MATH_DEFINES
#include "glew.h"
#include "glut.h"
#include <math.h>
#include <iostream>
#include <cmath>
#include <vector>
// Некоторые типы данных
typedef GLfloat GLTVector2[2];//Двукомпонентный вектор с плавающей запятой
typedef GLfloat GLTVector3[3];//Трехомпонентный вектор с плавающей запятой
typedef GLfloat GLTVector4[4];//Четырехкомпонентный вектор с плавающей //запятой
typedef GLfloat GLTMatrix[16];// Основноц столбец матрицы 4х4 с плавающей //запятой
// Величина поворота
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Вызывается для рисования сцены
static bool dirX = false;
static bool dirY = false;
static bool dirM = false;


struct Coord3
{
	GLfloat coord[3] = {};
	Coord3(GLfloat _x = {}, GLfloat _y = {}, GLfloat _z = {})
	{
		this->coord[0] = _x;
		this->coord[1] = _y;
		this->coord[2] = _z;
	}
};

GLfloat toRad(const GLfloat& angle)
{
	return M_PI * angle / 180.f;
}

void DrawThorus(GLfloat thorusR = 2.f, GLfloat thorusW = 1.f, unsigned int circleStep = 5, unsigned int circleCount = 5)
{
	const GLfloat _2pi = toRad(360.f);
	const GLfloat _360 = 360.f;
	GLfloat countStep = _360 / circleCount;
	GLfloat approxStep = _360 / circleStep;

	const int colorCount = 3;
	const GLfloat beginColor[colorCount] = { .9f, .0f, .9f };
	const GLfloat endColor[colorCount] = { .0f, .9f, 0.f };
	
	GLfloat colorDiff[colorCount] = { 0.f, 0.f, 0.f };

	for (int i = 0; i < colorCount; i++)
	{
		colorDiff[i] = (beginColor[i] + endColor[i]) / circleCount;
	}

	GLfloat c1 = beginColor[0], c2 = beginColor[1], c3 = beginColor[2];

	for (GLfloat angle = 0.f; angle < _360; angle += countStep)
	{
		GLfloat Rx = std::cos(toRad(angle)), Rz = std::sin(toRad(angle));
		glPushMatrix();
		
		glRotatef(angle + 90.f, 0.f, 1.f, 0.f);
		glTranslatef(0.f, 0.f, thorusR);
		glColor3f(c1, c2, c3);
		glBegin(GL_POINTS);
		for (GLfloat cAngle = 0.f; cAngle < _360; cAngle += approxStep)
		{
			GLfloat z = std::cos(toRad(cAngle)), y = std::sin(toRad(cAngle));
			glVertex3f(0.f, thorusW * y, thorusW * z);
		}
		glEnd();
		c1 += colorDiff[0];
		c2 += colorDiff[1];
		c3 += colorDiff[2];
		glPopMatrix();
	}
}

GLfloat thorusRot = 0.f;

void RenderThorus()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	glRotatef(thorusRot, 0.f, 1.f, 0.f);

	DrawThorus(60, 20.f, 50, 100);
	glutSwapBuffers();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Обновляем матрицу наблюдения модели
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// В качестве текущего цвета рисования задает красный glColor3f(1.0f, 0.0f, 0.0f);
	// Лицевая часть ///////////////////////////////////
	const float sides = 5.f;
	GLTVector3 objectVertex; // Вершина, находящаяся в поле зрения
	GLTVector3 transformedVertex; // Новая измененная вершина
	GLfloat size = 30.f;
	static GLfloat angleDiff = 360.f / (2*sides);
	GLfloat preRot = -45.f;

	//Нижний пятиугольник
	std::vector<Coord3> btmPentagon = {};
	for (float angle = 180.f + preRot; angle > 0 + preRot; angle -= angleDiff)
	{
		btmPentagon.push_back(Coord3(size * std::cos(angle * 2 * M_PI / 180), size, size * std::sin(angle * 2 * M_PI / 180)));
	}

	std::vector<Coord3> topPentagon = {};
	for (float angle = 90.f + preRot - 72.f; angle < 180.f + preRot + 90.f - 72.f; angle += angleDiff)
	{
		topPentagon.push_back(Coord3(size * std::cos(angle * 2 * M_PI / 180), 0, size * std::sin(angle * 2 * M_PI / 180)));
	}

	//Верхний пятиугольник

	glColor3b(127, 127, 0);
	glBegin(GL_POLYGON);
	//for (auto& c : btmPentagon) { glVertex3fv(c.coord); }
	for (int i = btmPentagon.size()-1; i >= 0; i--) { glColor3f((float)(i + 1) / 5, 127, 0); glVertex3fv(btmPentagon[i].coord); }
	glEnd();
	
	glColor3b(127, 0, 127);
	glBegin(GL_POLYGON);
	//for (auto& c : topPentagon) { glVertex3fv(c.coord); }
	for (int i = topPentagon.size() - 1; i >= 0; i--) { glColor3f((float)(i + 1) / 5, 0, 127); glVertex3fv(topPentagon[i].coord); }
	glEnd();
	glBegin(GL_TRIANGLES);
	for (int i = btmPentagon.size() - 1; i >= 0 ; i--)
	{
		glColor3b(0, 127/2, 127/2);
		glVertex3fv(btmPentagon[i].coord);
		glVertex3fv(btmPentagon[(i+1)%btmPentagon.size()].coord);
		glVertex3fv(topPentagon[btmPentagon.size() - 1 - i].coord);
		glColor3b(127, 0, 127/2);
		glVertex3fv(topPentagon[i].coord);
		glVertex3fv(topPentagon[(i + 1) % btmPentagon.size()].coord);
		glVertex3fv(btmPentagon[btmPentagon.size() - 1 - i].coord);
		/*glVertex3fv(btmPentagon[i].coord);
		glVertex3fv(topPentagon[ i == 0 ? i : (topPentagon.size() - 1 - i)].coord);*/
	}
	//glVertex3fv(btmPentagon[4].coord);
	//glVertex3fv(topPentagon[0].coord);
	glEnd();

	//длина высоты 
	const GLfloat icoHeight = 2 * size * std::sin(M_PI / (2*sides));

	//верх и дно 

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, icoHeight + size, 0);
	for (int i = btmPentagon.size() - 1; i >= 0; i--) { glColor3f((float)(i + 1) / 5, 127, 0); glVertex3fv(btmPentagon[i].coord); }
	glVertex3fv(btmPentagon[4].coord);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, -icoHeight, 0);
	for (int i = topPentagon.size() - 1; i >= 0; i--) { glColor3f((float)(i + 1) / 5, 0, 127); glVertex3fv(topPentagon[i].coord); }
	glVertex3fv(topPentagon[4].coord);
	glEnd();

	glutSwapBuffers();

	//Транслируем всю сцену в поле зрения
	//Это исходное преобразование наблюдения
}

void RenderScene1(void)
{
	// Угол поворота вокруг ядра
	static GLfloat fElect1 = 0.0f;
	static GLfloat electPosX = 0.0f;
	static GLfloat electPosY = -89.0f;
	static GLfloat move = 0.f;
	const float addMove = .3f;
	// Очищаем окно текущим цветом очистки
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Обновляем матрицу наблюдения модели
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Транслируем всю сцену в поле зрения
	//Это исходное преобразование наблюдения
	glTranslatef(move, 0.0f, -100.f);
	// Красное ядро
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glRotatef(fElect1, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(15.f, 0, 0);
	glutSolidTeapot(10);//glutSolidSphere(10.0f, 15, 15);
	// Желтые электроны
	glColor3ub(255, 255, 0);
	glPopMatrix();
	// Орбита первого электрона
	// Записываем преобразование наблюдения
	glPushMatrix();
	// Поворачиваем на угол поворота
	//glRotatef(fElect1, 0.f, 0.0f, 1.0f);
	// Трансляция элемента от начала координат на орбиту
	glTranslatef(electPosX, electPosY, 50.f);
	// Рисуем электрон
	glutSolidSphere(6.0f, 15, 15);
	// Восстанавливаем преобразование наблюдения
	glPopMatrix();
	//Орбита второго электрона
	glPushMatrix();
	glColor3ub(0, 255, 0);
	//glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	// Орбита третьего электрона
	glPushMatrix();
	glColor3ub(255, 0, 255);
	glRotatef(45.0f, 1.0f, 1.0f, 0.0f);
	glRotatef(fElect1*1.5, 0.f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	//glutSolidSphere(6.0f, 15, 15);
	glutSolidTeapot(1);
	glPopMatrix();
	// Увеличиваем угол поворота
	const float addAngle = 1.5f;
	fElect1 += addAngle;
	if (fElect1 > 720.0f)
		fElect1 = 0.0f;
	
	const float bordX = 90.f;
	const float bordY = 90.f;

	const float ibordX = 45.f;
	const float ibordY = 45.f;

	const float aspect = (bordX - ibordX);
	const float iaspect = aspect / 2;

	static float addX = 0.f;
	static float addY = 0.f;

	if (electPosX >= bordX || electPosX <= -bordX) dirX = !dirX;
	if (electPosY >= bordY || electPosY <= -bordY) dirY = !dirY;

	if (electPosX >= ibordX || electPosX <= -ibordX) addX = std::abs(electPosX / aspect) + .5f;
	else addX = std::abs(electPosX/ iaspect) + .5f;
	if (electPosY >= ibordY || electPosY <= -ibordY) addY = std::abs(electPosY / aspect) + .5f;
	else addY = std::abs(electPosY/ iaspect) + .5f;

	electPosX += (dirX ? 1 : -1) * addX;
	electPosY += (dirY ? 1 : -1) * addY;

	if (move > 30.f || move < -30.f) dirM = !dirM;
	move += (dirM ? 1 : -1) * addMove;
	//std::cout << "x: " << electPosX << " y: " << electPosY << std::endl;
	//const float bordX = 30.f;
	//const float addShift = 300;//bordX / (100* 360.f / addAngle);
	//electPosX += addShift * dirX ? 1 : -1;
	//if (electPosX >= 2 * bordX || electPosX <= -2 * bordX) dirX = !dirX;

	//const float bordY = 30.f;
	//electPosY += addShift * dirY ? 1 : -1;
	//if (electPosY >= 2 * bordY || electPosY <= -2 * bordY) dirY = !dirY;
	/*const float addShiftAcc = 4 * bord / (360.f / addAngle);*/
	/*if (dir && acc) electPos += addShiftAcc;
	else if (dir && !acc) electPos += addShift;
	else if (!dir && acc) electPos -= addShift;
	else if (!dir && !acc) electPos -= addShiftAcc;
	if (electPos <= -bord) dir = true;
	else if (electPos >= bord) dir = false;*/
	

	
	// Показываем построенное изображение
	glutSwapBuffers();
}

void RenderScene0(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSolidTeapot(10);//glutSolidSphere(10.0f, 15, 15);
	glutSwapBuffers();
}
// Функция выполняет необходимую инициализацию
// в контексте визуализации
void SetupRC()
{
	glEnable(GL_DEPTH_TEST); // Удаление скрытых поверхностей
	glFrontFace(GL_CCW); // Полигоны с обходом против
	//часовой стрелки направлены наружу
	glEnable(GL_CULL_FACE); //Внутри пирамиды расчеты не //производятся
	// Черный фон
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
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
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	// Перерисовывает сцену с новыми координатами
	glutPostRedisplay();
}
void keyboardHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '2':
		glutDisplayFunc(RenderScene);
		break;
	case '1':
		glutDisplayFunc(RenderScene1);
		break;
	case '3':
		glutDisplayFunc(RenderThorus);
		break;
		
	}
	glutPostRedisplay();
}


void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(5, TimerFunc, 1);
	thorusRot += 0.5f;
	if (thorusRot >= 360.f) thorusRot = 0.f;
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Предотвращение деления на ноль
	if (h == 0)
		h = 1;
	// Устанавливает поле просмотра по размерам окна
	glViewport(0, 0, w, h);
	// Обновляет стек матрицы проектирования
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
int main(int argc, char* argv[])
{
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Atom");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	//glutDisplayFunc(RenderThorus);
	glutDisplayFunc(RenderScene0);
	glutKeyboardUpFunc(keyboardHandler);
	//glutTimerFunc(500, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}