#ifndef _ANIMATE_VERTICES_H
#define _ANIMATE_VERTICES_H

#include <QElapsedTimer>
#include "plugin.h" 

class Animate_vertices: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

  private:
	QOpenGLShaderProgram* program;
	QOpenGLShader *fs, *vs;
	QElapsedTimer elapsedTimer;
};

#endif
