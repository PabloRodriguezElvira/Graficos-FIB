#ifndef _ISAFLOOR_H
#define _ISAFLOOR_H

#include "plugin.h" 
#include <QtMath>

class Isafloor: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	void onPluginLoad();
	void preFrame();
	void postFrame();

	void onObjectAdd();
	bool drawScene();
	bool drawObject(int);

	bool paintGL();

  private:
	QOpenGLShaderProgram* program;
	QOpenGLShader* vs;
	QOpenGLShader* fs;	

	float lambda;
	void calcularLambda();
	float calcularPercentSup(const Vector&);
	float dotProduct(const Vector&, const Vector&);
	float calcularSupCara(const Point&, const Point&, const Point&);
};

#endif
