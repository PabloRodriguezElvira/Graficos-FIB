#include "RGBDepth.h"
#include "glwidget.h"

void RGBDepth::onPluginLoad()
{	
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    //Vertex Shader RGBDepth
	vs_rgb = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs_rgb->compileSourceFile("./RGBDepth.vert");
    cout << "VS-rgb log:" << vs_rgb->log().toStdString() << endl;

    //Fragment shader RGB 
    fs_rgb = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs_rgb->compileSourceFile("./RGBDepth.frag");
    cout << "FS-rgb log:" << fs_rgb->log().toStdString() << endl;

    //Vertex Shader SplitView
	vs_split = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs_split->compileSourceFile("./SplitView.vert");
    cout << "VS-Split log:" << vs_split->log().toStdString() << endl;

    //Fragment shader Split
    fs_split = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs_split->compileSourceFile("./SplitView.frag");
    cout << "FS-Sky log:" << fs_split->log().toStdString() << endl;

    //Program Mirror
    programRGB = new QOpenGLShaderProgram(this);
    programRGB->addShader(vs_rgb);
    programRGB->addShader(fs_rgb);
    programRGB->link();
    cout << "RGB Link log:" << programRGB->log().toStdString() << endl;	

	//Program Split
    programSplit = new QOpenGLShaderProgram(this);
    programSplit->addShader(vs_split);
    programSplit->addShader(fs_split);
    programSplit->link();
    cout << "Sky Link log:" << programSplit->log().toStdString() << endl;	
 
    // Load Texture Sky.jpg
	QString filename1 = QFileDialog::getOpenFileName(0, "Open Image", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename1);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void RGBDepth::preFrame()
{
	
}

void RGBDepth::postFrame()
{
	
}

void RGBDepth::onObjectAdd()
{
	
}

bool RGBDepth::drawScene()
{
	return false; // return true only if implemented
}

bool RGBDepth::drawObject(int)
{
	return false; // return true only if implemented
}

bool RGBDepth::paintGL()
{
	return false; // return true only if implemented
}

void RGBDepth::keyPressEvent(QKeyEvent *)
{
	
}

void RGBDepth::mouseMoveEvent(QMouseEvent *)
{
	
}

