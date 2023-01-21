#include "resaltar_objeto_mouse.h"
#include "glwidget.h"

void Resaltar_objeto_mouse::onPluginLoad()
{	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./resaltar_objeto_mouse.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./resaltar_objeto_mouse.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	
}

void Resaltar_objeto_mouse::createBoundingBox() {
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
	g.glGenVertexArrays(1, &caja_VAO);
	g.glBindVertexArray(caja_VAO);

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

void Resaltar_objeto_mouse::drawBox(GLWidget& g) {
	g.glBindVertexArray(caja_VAO);	
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //pintar la caja con líneas.
	g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
	g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //volvemos a pintar normal.
	g.glBindVertexArray(0);
}

void Resaltar_objeto_mouse::postFrame()
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

void Resaltar_objeto_mouse::mouseReleaseEvent(QMouseEvent *e)
{
	//Contexto:
	GLWidget &g = *glwidget();
	g.makeCurrent();

	//a) Comprobamos que se ha hecho click con el ratón:	
	if (!(e->button() & Qt::LeftButton)) return;

	// b) Borramos los buffers con color blanco:
	g.glClearColor(0,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//c) Bind de shader program:
	program->bind();

	//d) Enviar los uniforms modelViewProjectionMatrix y normalMatrix:
	QMatrix4x4 modelViewProj = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", modelViewProj);

	//e) Pintar los objetos cada uno con un color único:
	for (unsigned int i = 0; i < scene()->objects().size(); ++i)
    {
        GLubyte color[4];
		color[0] = 20.0*i + 30;
		color[1] = 10.0*i + 30;
		color[2] = 15.0*i + 30;
        program->setUniformValue("color", QVector4D(color[0]/255.0,color[1]/255.,color[2]/255.,1.0));
        drawPlugin()->drawObject(i);
    }

	//f) Leer el color del objeto debajo del cursor.
	int x = e -> x();
    int y = glwidget() -> height() - e->y();
    GLubyte read[4];
    glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,read); 

	//g) Si no es color de fondo, pintar el objeto:
	if (read[0] != 0) scene()->setSelectedObject((read[0]-30.0)/20.0);

	//h) Actualizamos escena:
	g.update();
}

bool Resaltar_objeto_mouse::drawScene()
{
	return false; // return true only if implemented
}

bool Resaltar_objeto_mouse::drawObject(int)
{
	return false; // return true only if implemented
}

bool Resaltar_objeto_mouse::paintGL()
{
	return false; // return true only if implemented
}
