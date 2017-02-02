#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "igvCamara.h"

// Metodos constructores

igvCamara::igvCamara () {
	modo = IGV_VISUALIZACION; // por defecto la c�mara se utiliza para visualizar la escena
	zoomFactor=1.4;
	altura=8.0;
}

igvCamara::~igvCamara () {}

igvCamara::igvCamara(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;

	tipo = _tipo;
}


// Metodos publicos 
void igvCamara::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V) {
	P0 = _P0;
	r = _r;
	V = _V;
}
void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
			                                double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	xwmin = _xwmin;
	xwmax = _xwmax;
	ywmin = _ywmin;
	ywmax = _ywmax;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
			                         double _angulo, double _raspecto, double _znear, double _zfar) {
	tipo = _tipo;

	P0 = _P0;
	r = _r;
	V = _V;

	angulo = _angulo;
	raspecto = _raspecto;
	znear = _znear;
	zfar = _zfar;
}

void igvCamara::aplicar(void) {
	if (modo == IGV_VISUALIZACION) {
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		if (tipo==IGV_PARALELA) {
			glOrtho(xwmin*zoomFactor, xwmax*zoomFactor, ywmin*zoomFactor, ywmax*zoomFactor, znear, zfar);
			//glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
		}
		if (tipo==IGV_FRUSTUM) {
			glFrustum(xwmin*zoomFactor, xwmax*zoomFactor, ywmin*zoomFactor, ywmax*zoomFactor, znear, zfar);
			//glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
		}
		if (tipo==IGV_PERSPECTIVA) {
			gluPerspective(angulo,raspecto,znear,zfar);
		}
		
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(P0[X],P0[Y],P0[Z], r[X],r[Y],r[Z], V[X],V[Y],V[Z]);
	}

	if (modo == IGV_SELECCION) {
////// Apartado D: obtener el tamano actual del viewport
		GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);

////// Apartado D: cargar la matriz de proyecci�n y generar el volumen de vision para la selecci�n alrededor del pixel pulsado
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPickMatrix(cursorX,viewport[3]-cursorY,ancho_seleccion,alto_seleccion,viewport);

////// Apartado D: calcular la proyeccion (paralela, frustum o perspectiva), la misma que en modo visualizaci�n
		if (tipo==IGV_PARALELA) {
			glOrtho(xwmin*zoomFactor, xwmax*zoomFactor, ywmin*zoomFactor, ywmax*zoomFactor, znear, zfar);
			//glOrtho(xwmin, xwmax, ywmin, ywmax, znear, zfar);
		}
		if (tipo==IGV_FRUSTUM) {
			glFrustum(xwmin*zoomFactor, xwmax*zoomFactor, ywmin*zoomFactor, ywmax*zoomFactor, znear, zfar);
			//glFrustum(xwmin, xwmax, ywmin, ywmax, znear, zfar);
		}
		if (tipo==IGV_PERSPECTIVA) {
			gluPerspective(angulo,raspecto,znear,zfar);
		}

////// Apartado D: cargar la matriz de modelado y establecer la transformaci�n de la c�mara
		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(P0[X],P0[Y],P0[Z], r[X],r[Y],r[Z], V[X],V[Y],V[Z]);
	}
}

