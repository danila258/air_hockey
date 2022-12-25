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
    window.setMinimumSize(WINDOW_SIZE_MIN);
    window.setMaximumSize(WINDOW_SIZE_MAX);
    window.show();

	return app.exec();
}
