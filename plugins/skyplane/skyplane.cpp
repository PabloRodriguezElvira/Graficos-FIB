#include "skyplane.h"
#include "glwidget.h"

const int IMAGE_WIDTH = 512;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Skyplane::onPluginLoad()
{	
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    //Vertex Shader Mirror
	vs_mirror = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs_mirror->compileSourceFile("./mirror.vert");
    cout << "VS-Mirror log:" << vs_mirror->log().toStdString() << endl;

    //Fragment shader Mirror
    fs_mirror = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs_mirror->compileSourceFile("./mirror.frag");
    cout << "FS-Mirror log:" << fs_mirror->log().toStdString() << endl;

    //Vertex Shader Sky
	vs_sky = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs_sky->compileSourceFile("./sky.vert");
    cout << "VS-Sky log:" << vs_sky->log().toStdString() << endl;

    //Fragment shader Sky 
    fs_sky = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs_sky->compileSourceFile("./sky.frag");
    cout << "FS-Sky log:" << fs_sky->log().toStdString() << endl;

    //Program Mirror
    programMirror = new QOpenGLShaderProgram(this);
    programMirror->addShader(vs_mirror);
    programMirror->addShader(fs_mirror);
    programMirror->link();
    cout << "Mirror Link log:" << programMirror->log().toStdString() << endl;	

	//Program Sky
    programSky = new QOpenGLShaderProgram(this);
    programSky->addShader(vs_mirror);
    programSky->addShader(fs_mirror);
    programSky->link();
    cout << "Sky Link log:" << programSky->log().toStdString() << endl;	
 
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

    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
	
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();

	//Points in clip space:
	QVector4D V0 = QVector4D(-IMAGE_WIDTH,IMAGE_WIDTH,1,1);
	QVector4D V1 = QVector4D(IMAGE_WIDTH,IMAGE_HEIGHT,1,1);
	QVector4D V2 = QVector4D(IMAGE_WIDTH,-IMAGE_HEIGHT,1,1);
	QVector4D V3 = QVector4D(-IMAGE_WIDTH,-IMAGE_HEIGHT,1,1);
	// QVector4D V0 = QVector4D(0,1,0,1);
	// QVector4D V1 = QVector4D(1,1,0,1); 
	// QVector4D V2 = QVector4D(1,0,0,1);
	// QVector4D V3 = QVector4D(0,0,0,1);

	createRect(g, V0, V1, V2, V3);
}

// draws a quad with vertices V0, V1, V2, V3. 
void Skyplane::createRect(GLWidget &g, const QVector4D& V0, const QVector4D& V1, const QVector4D& V2, const QVector4D& V3) {
    // 1. Create VAO
    // Create & bind empty VAO
    g.glGenVertexArrays(1, &VAO_rect);
    g.glBindVertexArray(VAO_rect);

    // Create VBO with (x,y,z) coordinates
    float coords[] = { V0.x(), V0.y(), V0.z(),
                       V1.x(), V1.y(), V1.z(),
					   V3.x(), V3.y(), V3.z(),
					   V2.x(), V2.y(), V2.z() };

    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    g.glBindVertexArray(0);
}

void Skyplane::drawRect(GLWidget &g) {
    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}

bool Skyplane::paintGL()
{
    GLWidget & g = *glwidget();

    // ********************Pass 1: Pintar el quad usando sky.vert y sky.frag ********************

	g.glClearColor(0.8,0.8,0.8,0);
	g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	programSky->bind();
	programSky->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix());
	programSky->setUniformValue("modelViewMatrix", camera()->viewMatrix());
	programSky->setUniformValue("sampler0", 0);
	
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	drawRect(g);
	return true;
}



