#ifndef _SKYPLANE_H
#define _SKYPLANE_H

#include "plugin.h" 

class Skyplane: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 bool paintGL();

  private:
	QOpenGLShaderProgram* programMirror;
	QOpenGLShaderProgram* programSky;

   	QOpenGLShader* vs_mirror;
	QOpenGLShader* fs_mirror;
   	QOpenGLShader* vs_sky;
	QOpenGLShader* fs_sky;

    GLuint VAO_rect;
	GLuint VBO_coords;
    GLuint textureId0; 

	void createRect(GLWidget&, const QVector4D&, const QVector4D&, const QVector4D&, const QVector4D&);
	void drawRect(GLWidget&);
};

#endif
