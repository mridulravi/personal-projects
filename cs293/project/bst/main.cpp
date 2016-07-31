
 #include <QApplication>

 #include "window.h"

 int main(int argc, char *argv[])
 {	
     QApplication app(argc, argv);
     Window window;
     window.resize(1200,700);
     window.move(100,200);
     window.show();
     return app.exec();
 }
