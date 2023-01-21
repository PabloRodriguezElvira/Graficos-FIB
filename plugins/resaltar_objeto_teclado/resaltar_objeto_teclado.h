#ifndef _RESALTAR_OBJETO_TECLADO_H
#define _RESALTAR_OBJETO_TECLADO_H

#include "plugin.h" 

class Resaltar_objeto_teclado: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
		void onPluginLoad();
		void postFrame();

		bool drawScene();
		bool drawObject(int);

		bool paintGL();

		void keyPressEvent(QKeyEvent *);
  private:
		QOpenGLShaderProgram* program;
		QOpenGLShader* vs;
		QOpenGLShader* fs;	

		GLuint caja_VAO;
		GLuint coords_VBO;
		GLuint color_VBO;

		void createBoundingBox();
		void drawBox(GLWidget&);
};

#endif
