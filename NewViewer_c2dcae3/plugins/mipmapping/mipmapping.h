#ifndef _MIPMAPPING_H
#define _MIPMAPPING_H

#include "plugin.h" 

class Mipmapping: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	void onPluginLoad();
	void keyPressEvent(QKeyEvent *);
	bool paintGL();

  private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    GLuint textureId;
	GLint mode;
	float tiles;

	void changeMipmap();
	void printMode();
	void setQuantity();
};

#endif
