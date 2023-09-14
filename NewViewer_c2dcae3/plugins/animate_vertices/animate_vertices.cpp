#include "animate_vertices.h"
#include "glwidget.h"

void Animate_vertices::onPluginLoad()
{
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./animate-vertices1.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./animate-vertices1.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

	elapsedTimer.start();
}

void Animate_vertices::preFrame()
{
	program->bind();
	program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
	QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
	program->setUniformValue("normalMatrix", NM); 
	QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
	program->setUniformValue("modelViewProjectionMatrix", MVP); 
}


void Animate_vertices::postFrame()
{
	program->release();	
}


