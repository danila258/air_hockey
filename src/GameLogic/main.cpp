#include "Configuration.h"
#include "GameWindow.h"

#include <QApplication>
#include <QSurfaceFormat>


int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(OPEN_GL_VERSION_MAJOR, OPEN_GL_VERSION_MINOR);
    format.setSamples(ANTIALIASING_SAMPLES);

    GameWindow window;

	window.setFormat(format);
    window.resize(640, 640);
    window.show();

	return app.exec();
}
