#ifndef _TEXTURE_SPLATTING_H
#define _TEXTURE_SPLATTING_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

class Texture_splatting: public QObject, public Plugin
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
   	QOpenGLShader* vs;
	QOpenGLShader* fs;	

    GLuint textureId0, textureId1, textureId2;
};

#endif



