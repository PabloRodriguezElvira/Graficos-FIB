#ifndef _DRAW_BOUNDING_BOX_H
#define _DRAW_BOUNDING_BOX_H

#include "plugin.h" 

class Draw_bounding_box: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
	 
  private:
	QOpenGLShaderProgram* program;
   	QOpenGLShader* vs;
	QOpenGLShader* fs;	
	
	GLuint cubo_VAO;
	GLuint coords_VBO;
	GLuint color_VBO;
	
	void createCube();
};

#endif
