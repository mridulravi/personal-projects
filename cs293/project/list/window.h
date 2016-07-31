 #ifndef WINDOW_H
 #define WINDOW_H

 #include <QWidget>

 class QCheckBox;
 class QComboBox;
 class QLabel;
 class QSpinBox;

 class RenderArea;

 class Window : public QWidget
 {
     Q_OBJECT

 public:
     Window();

 private slots:
     void shapeChanged();
     void penChanged();
     void brushChanged();
     void fontChanged() ;
     void a();
     //
     void b();
     void c();
     void insert();
	 
 private:
     RenderArea *renderArea;
     QLabel *shapeLabel;
     QLabel *BoxLabel;
     QComboBox *shapeComboBox;
     QSpinBox *Box;
     QLabel * comboLabel;
     QLabel * newElement;
     QLabel * element;
     QComboBox * combo;
     QSpinBox *box1,*box2;
     
 };

 #endif
