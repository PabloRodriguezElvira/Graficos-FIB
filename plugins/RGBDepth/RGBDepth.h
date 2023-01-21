#ifndef _RGBDEPTH_H
#define _RGBDEPTH_H

#include "plugin.h" 

class RGBDepth: public QObject, public Plugin
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

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	QOpenGLShaderProgram* programRGB;
	QOpenGLShaderProgram* programSplit;

   	QOpenGLShader* vs_rgb;
	QOpenGLShader* fs_rgb;
   	QOpenGLShader* vs_split;
	QOpenGLShader* fs_ssplitt;

};

#endif
