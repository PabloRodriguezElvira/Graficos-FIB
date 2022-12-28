#include "texture_splatting.h"
#include "glwidget.h"

void Texture_splatting::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    //Vertex Shader
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./splatting.vert");
    cout << "VS log:" << vs->log().toStdString() << endl;

    //Fragment shader
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./splatting.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;

    //Program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	
    
    // Load Texture 1
	QString filename1 = QFileDialog::getOpenFileName(0, "Open Image", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename1);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
	
    // Load Texture 2
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img2(filename2);	
	QImage im2 = img2.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE1);
	g.glGenTextures(1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im2.width(), im2.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im2.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
    
    // Load Texture 3 
	QString filename3 = QFileDialog::getOpenFileName(0, "Open Image", "../../Textures", "Image file (*.png *.jpg)");	
	QImage img3(filename3);	
	QImage im3 = img3.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE2);
	g.glGenTextures(1, &textureId2);
	g.glBindTexture(GL_TEXTURE_2D, textureId2);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im3.width(), im3.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im3.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
	
}

void Texture_splatting::preFrame()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("sampler2", 2);  // texture unit del tercer sampler 
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    
	// bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);

	g.glActiveTexture(GL_TEXTURE2);
	g.glBindTexture(GL_TEXTURE_2D, textureId2);
	
}

void Texture_splatting::postFrame()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind default shaders
    g.defaultProgram()->bind();
    
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    
    g.glActiveTexture(GL_TEXTURE2);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}
