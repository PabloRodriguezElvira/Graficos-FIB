#include "mipmapping.h"
#include "glwidget.h"

void Mipmapping::onPluginLoad()
{	
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    //Vertex Shader
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("./mipmapping.vert");

    //Fragment shader
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("./mipmapping.frag");

    //Program
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Load brick texture.
    QString filename1 = "../../Textures/brickbump.jpg";
	QImage img1(filename1);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
    g.makeCurrent();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId);
	g.glBindTexture(GL_TEXTURE_2D, textureId);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());

    //Change mipmapping setting and print, also initialize tiles to 1.0.
    g.glGenerateMipmap(GL_TEXTURE_2D);
    mode = GL_NEAREST;
    tiles = 1.0;
    changeMipmap();
	g.glBindTexture(GL_TEXTURE_2D, 0);

    //Add plane as the default object:
    g.clearScene();
    g.addObjectFromFile("../../models/plane.obj");

    //Make viewport fullscreen:
    g.resize(1920, 1080);
}

bool Mipmapping::paintGL() {
	GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms.
    program->bind();
    program->setUniformValue("colorMap", 0);  // texture unit del primer sampler.

    //Set uniform quantity to tiles.
    setQuantity();
 
	// bind texture. 
    g.glBindTexture(GL_TEXTURE_2D, textureId);
    if (drawPlugin()) drawPlugin()->drawScene();
    return true;
}

void Mipmapping::setQuantity() {
    program->setUniformValue("quantity", tiles);

    //If there are multiple textures, we rotate the plane and make it bigger to better visualize the mipmapping setting.
    QMatrix4x4 modelMatrix;
    if (tiles == 50.0) {
        modelMatrix.scale(4,4,4);
        modelMatrix.rotate(-80.0, QVector3D(1,0,0));
    }
    else modelMatrix.setToIdentity();
    program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix() * modelMatrix);
}

void Mipmapping::printMode() {
    QString mod;
    switch (mode) {
        case GL_NEAREST:
            mod = "GL_NEAREST";
            break;
        case GL_LINEAR:
            mod = "GL_LINEAR";
            break;
        case GL_NEAREST_MIPMAP_NEAREST:
            mod = "GL_NEAREST_MIPMAP_NEAREST";
            break;
        case GL_NEAREST_MIPMAP_LINEAR:
            mod = "GL_NEAREST_MIPMAP_LINEAR";
            break;
        case GL_LINEAR_MIPMAP_NEAREST:
            mod = "GL_LINEAR_MIPMAP_NEAREST";
            break;
        default:
            mod = "GL_LINEAR_MIPMAP_LINEAR";
    } 
    cout << "\n--------------------------------------------------\n";
    cout << "FILTER MODE: " << mod.toStdString() << "\n";
    cout << "TILES IS SET TO: " << tiles << "\n";
    cout << "--------------------------------------------------\n" << endl;
}

void Mipmapping::changeMipmap() {
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
    printMode();
}

void Mipmapping::keyPressEvent(QKeyEvent* e)
{	
    if (e->key() == Qt::Key_1) {mode = GL_NEAREST; changeMipmap();}
    if (e->key() == Qt::Key_2) {mode = GL_LINEAR; changeMipmap();}
    if (e->key() == Qt::Key_3) {mode = GL_NEAREST_MIPMAP_NEAREST; changeMipmap();}
    if (e->key() == Qt::Key_4) {mode = GL_NEAREST_MIPMAP_LINEAR; changeMipmap();}
    if (e->key() == Qt::Key_5) {mode = GL_LINEAR_MIPMAP_NEAREST; changeMipmap();}
    if (e->key() == Qt::Key_6) {mode = GL_LINEAR_MIPMAP_LINEAR; changeMipmap();}
    if (e->key() == Qt::Key_Q) {tiles = 1.0; setQuantity(); printMode();} 
    if (e->key() == Qt::Key_W) {tiles = 50.0; setQuantity(); printMode();} 
    glwidget()->update();
}
