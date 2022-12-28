#include "ModelInfo1.h"
#include "glwidget.h"

void ModelInfo1::getInfoEscena() {
	Scene* scn = scene();
	numeroObjetos = scn->objects().size();
	numeroPoligonos = numeroVertices = numeroTriangulos = percTriangulos = 0;
	for (int i = 0; i < numeroObjetos; ++i) {
		const Object& obj = scn->objects()[i];
		int num_caras = obj.faces().size();
		numeroPoligonos += num_caras;
		for (int j = 0; j < num_caras; ++j) {
			int nvert = obj.faces()[j].numVertices();
			numeroVertices += nvert;
			numeroTriangulos += (nvert == 3);		
		}
	}
	percTriangulos = (numeroTriangulos)/(numeroPoligonos) * 100;
}

void ModelInfo1::printInfoEscena() {
	cout << "Número de objetos de la escena: " << numeroObjetos << endl;
	cout << "Número de polígonos de la escena: " << numeroPoligonos << endl;
	cout << "Número de vértices de la escena: " << numeroVertices << endl;
	cout << "Número de triangulos de la escena: " << numeroTriangulos << endl;
	cout << "Porcentaje de triangulos de la escena: " << percTriangulos << endl;
	
}

void ModelInfo1::onPluginLoad()
{
	getInfoEscena();	
}

void ModelInfo1::preFrame()
{
	
}

void ModelInfo1::postFrame()
{
	printInfoEscena();	
}

void ModelInfo1::onObjectAdd()
{
	getInfoEscena();	
}

bool ModelInfo1::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo1::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo1::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo1::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo1::mouseMoveEvent(QMouseEvent *)
{
	
}

