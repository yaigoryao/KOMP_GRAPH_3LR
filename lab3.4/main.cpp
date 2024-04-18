#include "glew.h"
#include "glut.h"
#include <windows.h>
#include <math.h>
#include <iostream>
// Используемые константы
#define GLT_PI 3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229
#define gltDegToRad(x) ((x)*GLT_PI_DIV_180)
// Некоторые типы данных
typedef GLfloat GLTVector2[2];//Двукомпонентный вектор с плавающей запятой
typedef GLfloat GLTVector3[3];//Трехомпонентный вектор с плавающей запятой
typedef GLfloat GLTVector4[4];//Четырехкомпонентный вектор с плавающей //запятой
typedef GLfloat GLTMatrix[16];// Основноц столбец матрицы 4х4 с плавающей //запятой

GLfloat ww = 0, wh = 0;
void gltLoadIdentityMatrix(GLTMatrix m)
{
	static GLTMatrix identity = { 1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f };
	memcpy(m, identity, sizeof(GLTMatrix));
};
void gltTransformPoint(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
{
	vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] * vSrcVector[2] + mMatrix[12];
	vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] * vSrcVector[2] + mMatrix[13];
	vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2] + mMatrix[14];
};
void gltRotationMatrix(float angle, float x, float y, float z, GLTMatrix mMatrix)
{
	float vecLength, sinSave, cosSave, oneMinusCos;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs;
	// Если нулевой вектор проходит, то …
	if (x == 0.0f && y == 0.0f && z == 0.0f)
	{
		gltLoadIdentityMatrix(mMatrix);
		return;
	}
	// Вектор масштабирования
	vecLength = (float)sqrt(x * x + y * y + z * z);
	// Нормализованная матрица вращения
	x /= vecLength;
	y /= vecLength;
	z /= vecLength;
	sinSave = (float)sin(angle);
	cosSave = (float)cos(angle);
	oneMinusCos = 1.0f - cosSave;
	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * sinSave;
	ys = y * sinSave;
	zs = z * sinSave;
	mMatrix[0] = (oneMinusCos * xx) + cosSave;
	mMatrix[4] = (oneMinusCos * xy) - zs;
	mMatrix[8] = (oneMinusCos * zx) + ys;
	mMatrix[12] = 0.0f;
	mMatrix[1] = (oneMinusCos * xy) + zs;
	mMatrix[5] = (oneMinusCos * yy) + cosSave;
	mMatrix[9] = (oneMinusCos * yz) - xs;
	mMatrix[13] = 0.0f;
	mMatrix[2] = (oneMinusCos * zx) - ys;
	mMatrix[6] = (oneMinusCos * yz) + xs;
	mMatrix[10] = (oneMinusCos * zz) + cosSave;
	mMatrix[14] = 0.0f;
	mMatrix[3] = 0.0f;
	mMatrix[7] = 0.0f;
	mMatrix[11] = 0.0f;
	mMatrix[15] = 1.0f;
};
// Контейнер системы отсчета
typedef struct GLTFrame
{ 
	GLTVector3 vLocation;
	GLTVector3 vUp;
	GLTVector3 vForward;
};

GLfloat mR = 0.175f;
// Прорисовка тора(бублика), с использованием текущей структуры 1D для легкого затемнения света
void DrawTorus(GLTMatrix mTransform)
{
	GLfloat majorRadius = mR;
	GLfloat minorRadius = 0.075f;
	GLint numMajor = 40;
	GLint numMinor = 20;
	GLTVector3 objectVertex; // Вершина, находящаяся в поле зрения
	GLTVector3 transformedVertex; // Новая измененная вершина
	double majorStep = 2.0f * GLT_PI / numMajor;
	double minorStep = 2.0f * GLT_PI / numMinor;
	int i, j;
	for (i = 0; i < numMajor; ++i)
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat)cos(a0);
		GLfloat y0 = (GLfloat)sin(a0);
		GLfloat x1 = (GLfloat)cos(a1);
		GLfloat y1 = (GLfloat)sin(a1);
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; ++j)
		{
			double b = j * minorStep;
			GLfloat c = (GLfloat)cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat)sin(b);
			// Первая точка
			objectVertex[0] = x0 * r;
			objectVertex[1] = y0 * r;
			objectVertex[2] = z;
			gltTransformPoint(objectVertex, mTransform, transformedVertex);
			glVertex3fv(transformedVertex);
			// Вторая точка
			objectVertex[0] = x1 * r;
			objectVertex[1] = y1 * r;
			objectVertex[2] = z;
			gltTransformPoint(objectVertex, mTransform, transformedVertex);
			glVertex3fv(transformedVertex);
		}
		glEnd();
	}
	//0.0612398 -0.188477 -0.0713292
}
// Вызывается для рисования сцены

static GLfloat xSpeed = 0.27f;
static GLfloat ySpeed = 0.5f;
static GLfloat zSpeed = .7f;

static GLfloat xPlane = 1.0f;
static GLfloat yPlane = 0.0f;
static GLfloat zPlane = 0.0f;


void RenderScene(void)
{
	GLTMatrix transformationMatrix; // Матрица поворота
	static GLfloat yRot = 0.0f, xRot = 0.0f, zRot = 0.0f; // Угол поворота, задействованный //в //анимации
	xRot += xSpeed;
	yRot += ySpeed;
	zRot += zSpeed;
	// Очистка окна ткущим цветом очистки
	glPolygonMode(GL_FRONT_AND_BACK, CRYPT_OID_NO_NULL_ALGORITHM_PARA_FLAG);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Строим матрицу поворота
	gltRotationMatrix(gltDegToRad(xRot), xPlane, yPlane, zPlane, transformationMatrix);
	transformationMatrix[12] = 0.5f - mR/2;
	transformationMatrix[13] = 0.5f - mR;
	transformationMatrix[14] = -2.f;
	DrawTorus(transformationMatrix);

	gltRotationMatrix(gltDegToRad(yRot), 0.0f, 1.0f, 0.0f, transformationMatrix);
	transformationMatrix[12] = -0.5f + mR/2;
	transformationMatrix[13] = 0.5f - mR;
	transformationMatrix[14] = -2.f;
	DrawTorus(transformationMatrix);

	gltRotationMatrix(gltDegToRad(zRot), 0.0f, 0.0f, 1.0f, transformationMatrix);
	transformationMatrix[12] = -0.5f + mR/2;
	transformationMatrix[13] = -0.5f + mR;
	transformationMatrix[14] = -2.f;
	DrawTorus(transformationMatrix);
	/*gltRotationMatrix(gltDegToRad(yRot), 0.0f, 1.0f, 0.0f, transformationMatrix);
	transformationMatrix[12] = 0.f;
	transformationMatrix[13] = 0.f;
	transformationMatrix[14] = -2.f;
	DrawTorus(transformationMatrix);
	glPopMatrix();*/

	// Буфер обмена
	glutSwapBuffers();
}
// Функция выполняет всю необходимую инициализацию в контексте // визуализации
void SetupRC()
{
	// Голубой фон
	glClearColor(0.0f, 0.0f, 0.f, 1.0f);
	// Все рисуется в каркасном виде
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
///////////////////////////////////////////////////////////
// Вызывается библиотекой GLUT в холостом состоянии
//(окно не меняет размера и не перемещается)
static bool dir = true;
void TimerFunction(int value)
{
	static float bgColor = 0.3f;
	// Перерисовывает сцену с новыми координатами glutPostRedisplay();
	glClearColor(0.0f, 0.0f, bgColor, 1.0f);
	bgColor += 0.001f * (dir ? 1 : -1);
	if (bgColor >= 0.8) dir = !dir;
	else if (bgColor <= 0.2f) dir = !dir;
	glutTimerFunc(10, TimerFunction, 1);
	RenderScene();
}
void ChangeSize(int w, int h)
{
	GLfloat fAspect;
	// Предотвращает деление на нуль, когда окно слишком маленькое
	// (нельзя сделать окно нулевой ширины).
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	ww = w;
	wh = h;
	// Система координат обновляется перед модификацией
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Генерируется перспективная проекция
	gluPerspective(35.f, fAspect, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardHandler(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'l': 
			glColor3b(127, 127, 127);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 'f': 
			glColor3b(std::rand() % 127, std::rand() % 127, std::rand() % 127);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
			break;
		case 's':
			xSpeed = (std::rand() % 2 ? 1 : -1) * (1 + std::rand() % 14) / 7.5;
			ySpeed = (std::rand() % 2 ? 1 : -1) * (1 + std::rand() % 14) / 7.5;
			zSpeed = (std::rand() % 2 ? 1 : -1) * (1 + std::rand() % 14) / 7.5;
			break;
		case 'd':
			xPlane = std::rand() % 2;
			yPlane = std::rand() % 2;
			zPlane = std::rand() % 2;
			if (xPlane == yPlane == zPlane == false)
			{
				while (!xPlane || !yPlane || !zPlane)
				{
					xPlane = std::rand() % 2;
					yPlane = std::rand() % 2;
					zPlane = std::rand() % 2;
				}
			}

			break;
	}
}
int main(int argc, char* argv[])
{
	std::srand(std::time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Manual Transformations Demo");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboardHandler);
	SetupRC();
	glutTimerFunc(33, TimerFunction, 1);
	glutMainLoop();
	return 0;
}