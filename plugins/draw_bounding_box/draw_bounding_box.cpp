#include "draw_bounding_box.h"
#include "glwidget.h"

void Draw_bounding_box::onPluginLoad()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./draw_bounding_box.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./draw_bounding_box.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	

	createCube();
}


void Draw_bounding_box::postFrame()
{
	//evitamos perder el contexto:
	GLWidget& g = *glwidget();
	g.makeCurrent();	

	//bind shader and define uniforms:
	program->bind();
	QMatrix4x4 modelViewProj = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", modelViewProj);
	
	//creamos normalMatrix
	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", NM);

	Scene* scn = scene();
	const vector<Object>& obj = scn->objects();

	//pintamos la caja contenedora de cada objeto de la escena:
	for (long unsigned int i = 0; i < obj.size(); ++i) {
		Point boxMin = obj[i].boundingBox().min();
		Point boxMax = obj[i].boundingBox().max();

		//creamos matriz escalado: (POR FILAS)
		QMatrix4x4 scale = QMatrix4x4(boxMax.x()-boxMin.x(),0,0,0,  0,boxMax.y()-boxMin.y(),0,0, 
		0,0,boxMax.z()-boxMin.z(),0,   0,0,0,1);
		program->setUniformValue("scaleMatrix", scale);

		//creamos matriz translate: (POR FILAS)
		float centro[] = {boxMin.x(), boxMin.y(), boxMin.z()};
		QMatrix4x4 translate = QMatrix4x4(1,0,0,centro[0],  0,1,0,centro[1],  0,0,1,centro[2],  0,0,0,1);
		program->setUniformValue("translateMatrix", translate);

		g.glBindVertexArray(caja_VAO);	
		g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //pintar la caja con líneas.
		g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
		g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //volvemos a pintar normal.
		g.glBindVertexArray(0);
	}

	//unbind shader
	program->release();
}


void Draw_bounding_box::createCube() {
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