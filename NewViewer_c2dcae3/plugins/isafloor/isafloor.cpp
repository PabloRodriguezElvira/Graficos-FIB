#include "isafloor.h"
#include "glwidget.h"

void Isafloor::onPluginLoad()
{	
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./isafloor.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./isafloor.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	

	calcularLambda();
}

void Isafloor::calcularLambda() {
	float superficieTotal = 0.0;
	float superficieTerra = 0.0;
	const Object& object = scene()->objects()[0]; //Sólo hay 1 objeto en la escena.
	for (const Face& face : object.faces()) {
		Vector normal = face.normal();
		float percentSup = calcularPercentSup(normal);
		//Sacamos los índices de los vértices de la cara:
		int i = face.vertexIndex(0);
		int j = face.vertexIndex(1);
		int k = face.vertexIndex(2);
		//Sacamos las coordenadas de los vértices:
		Point p0 = object.vertices()[i].coord();
		Point p1 = object.vertices()[j].coord();
		Point p2 = object.vertices()[k].coord();
		//Calculamos superfície de la cara:
		float superficieCara = calcularSupCara(p0, p1, p2);
		if (percentSup > 0.7) {
			superficieTerra += superficieCara;
		}
		superficieTotal += superficieCara;
	}
	lambda = superficieTerra/superficieTotal;
	cout << "TERRA: " << lambda << endl;
}

float Isafloor::calcularSupCara(const Point& p0, const Point& p1, const Point& p2) {
	Vector u = p1-p0;
	Vector v = p2-p0;
	//Calcular el producto vectorial con determinante:
	// Vector crossProduct;
	// crossProduct[0] = u[1]*v[2] - v[1]*u[2];
	// crossProduct[1] = -u[0]*v[2] + v[0]*u[2];
	// crossProduct[2] = u[0]*v[1] - v[0]*u[1];
	// //Módulo del producto vectorial:
	// float mod = sqrt(crossProduct[0]*crossProduct[0] + crossProduct[1]*crossProduct[1] + crossProduct[2]*crossProduct[2]);
	Vector w = QVector3D::crossProduct(u, v);
	return w.length()/2.0;
}

float Isafloor::calcularPercentSup(const Vector& normal) {
	Vector vectorWS = Vector(0,0,1); //No hace falta aplicar transformación (Object Space == World Space).
	return dotProduct(nodotProductrmal, vectorWS);	
}

float Isafloor::dotProduct(const Vector& a, const Vector& b) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

void Isafloor::preFrame()
{
	// evitamos perder el contexto:
	GLWidget& g = *glwidget();
	g.makeCurrent();	

	// Bind shader and define uniforms:
	program->bind();
	// modelViewProjection
	QMatrix4x4 modelViewProj = camera()->projectionMatrix() * camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", modelViewProj);
	// normalMatrix
	QMatrix3x3 normalMat = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", normalMat);
	// lambda	
	program->setUniformValue("lambda", lambda);
}

void Isafloor::postFrame() {
	// release program:
	program->release();
}

void Isafloor::onObjectAdd()
{
	calcularLambda();	
}

bool Isafloor::drawScene()
{
	return false; // return true only if implemented
}

bool Isafloor::drawObject(int)
{
	return false; // return true only if implemented
}

bool Isafloor::paintGL()
{
	return false; // return true only if implemented
}

