 #ifndef RENDERAREA_H
 #define RENDERAREA_H

 #include <QBrush>
 #include <QPen>
 #include <QPixmap>
 #include <QWidget>
 #include <QQueue>
 #include <QVector>
 #include <string>
 #include "iitbOrderedSet.h"

 class RenderArea : public QWidget
 {
     Q_OBJECT

 public:
     enum Shape {Insert,Remove,Search,Find_Minimum,Find_Maximum};	// to be used in the comboBox(while taking the input from the user
									// and then comparing in the switch statement)
     RenderArea(QWidget *parent = 0);

     int i,te;								// te store the input given through the graphical interface
     iitbOrderedSet< int > S;
     QVector<int> myvector;

 public slots:
     void setShape(Shape shape);					// for setting the shape
     void setPen(const QPen &pen);					// for setting the pen
     void setBrush(const QBrush &brush);				// for setting the pen
     void setFont(const QFont &font);					// for setting the font

 protected:
     void paintEvent(QPaintEvent *event);

 private:
     Shape shape;
     QPen pen;
     QBrush brush;
     QFont font;
 };

 #endif
