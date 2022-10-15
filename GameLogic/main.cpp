#include "RectangleWindow.h"

#include <QApplication>
#include <QSurfaceFormat>


int main(int argc, char **argv) {
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3,3);

	RectangleWindow window;

	window.setFormat(format);
	window.resize(640, 480);
	window.show();

	return app.exec();
}
