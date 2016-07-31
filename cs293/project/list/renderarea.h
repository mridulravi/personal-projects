 #ifndef RENDERAREA_H
 #define RENDERAREA_H

 #include <QBrush>
 #include <QPen>
 #include <QPixmap>
 #include <QWidget>
 #include <QList>

 class RenderArea : public QWidget
 {
     Q_OBJECT

 public:
     enum Shape {Pop_back,Pop_front,Push_back,Push_front,Delete,insert_Before,insert_After};

     RenderArea(QWidget *parent = 0);

     QSize minimumSizeHint() const;
     QSize sizeHint() const;
	 int i,N,te,count,value1,value2;
 	 QList<int> list;

 public slots:
     void setShape(Shape shape);
     void setPen(const QPen &pen);
     void setBrush(const QBrush &brush);
     void setFont(const QFont &font);

 protected:
     void paintEvent(QPaintEvent *event);

 private:
     Shape shape;
     QPen pen;
     QBrush brush;
     QFont font;
 };

 #endif
