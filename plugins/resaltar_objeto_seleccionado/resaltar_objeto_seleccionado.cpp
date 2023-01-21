#include "resaltar_objeto_seleccionado.h"
#include "glwidget.h"

void Resaltar_objeto_seleccionado::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./resaltar_objeto_seleccionado.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./resaltar_objeto_seleccionado.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	
}

void Resaltar_objeto_seleccionado::createBoundingBox() {
	GLWidget& g = *glwidget();
	g.makeCurrent();

	float coords[] = {
		0, 0, 0,
		0, 1, 0,
		1, 0, 0,
		1, 1, 0,  
		1, 1, 1,  
		0, 1, 0,  
		0, 1, 1,  
		0, 0, 1,  
		1, 1, 1,  
		1, 0, 1,  
		1, 0, 0,  
		0, 0, 1,  
		0, 0, 0,  
		0, 1, 0  
	};

	float color[] = {
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0
	};

	//Crear y bindear VAO vacío:
	g.glGenVertexArrays(1, &cubo_VAO);
	g.glBindVertexArray(cubo_VAO);

	//Crear VBO de coordenadas:
	g.glGenBuffers(1, &coords_VBO);
	g.glBindBuffer(GL_ARRAY_BUFFER, coords_VBO);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(0);

	//Crear VBO de colores:
	g.glGenBuffers(1, &color_VBO);
	g.glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
	g.glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	g.glEnableVertexAttribArray(2);
}

void Resaltar_objeto_seleccionado::drawBox(GLWidget& g) {
	g.glBindVertexArray(cubo_VAO);	
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //pintar la caja con líneas.
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //volvemos a pintar normal.
	g.glBindVertexArray(0);
}

void Resaltar_objeto_seleccionado::postFrame()
{
	//evitamos perder el contexto:
	GLWidget& g = *glwidget();
	g.makeCurrent();	

	//Creamos la caja contenedora:
	createBoundingBox();	

	//bind shader and define uniforms:
	program->bind();
	QMatrix4x4 modelViewProj = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", modelViewProj);
	
	//Cogemos el objeto seleccionado:
	int selectedObj= scene()->selectedObject();
	const Object& obj = scene()->objects()[selectedObj];

	//pintamos la caja contenedora del objeto seleccionado:
	Point boxMin = obj.boundingBox().min();
	Point boxMax = obj.boundingBox().max();

	//creamos matriz escalado: (POR FILAS)
	QMatrix4x4 scale = QMatrix4x4(boxMax.x()-boxMin.x(),0,0,0,  0,boxMax.y()-boxMin.y(),0,0, 
	0,0,boxMax.z()-boxMin.z(),0,  0,0,0,1);
	program->setUniformValue("scaleMatrix", scale);

	//creamos matriz translate: (POR FILAS)
	float centro[] = {boxMin.x(), boxMin.y(), boxMin.z()};
	QMatrix4x4 translate = QMatrix4x4(1,0,0,centro[0], 0,1,0,centro[1], 0,0,1,centro[2], 0,0,0,1);
	program->setUniformValue("translateMatrix", translate);

	//Pintamos la caja:
	drawBox(g);	

	//unbind shader
	program->release();
}

bool Resaltar_objeto_seleccionado::drawScene()
{
	return false; // return true only if implemented
}

bool Resaltar_objeto_seleccionado::drawObject(int)
{
	return false; // return true only if implemented
}

bool Resaltar_objeto_seleccionado::paintGL()
{
	return false; // return true only if implemented
}

void Resaltar_objeto_seleccionado::keyPressEvent(QKeyEvent *)
{
	
}

void Resaltar_objeto_seleccionado::mouseMoveEvent(QMouseEvent *)
{
	
}

