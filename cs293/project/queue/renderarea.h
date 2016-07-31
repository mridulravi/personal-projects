 #ifndef RENDERAREA_H
 #define RENDERAREA_H

 #include <QBrush>
 #include <QPen>
 #include <QPixmap>
 #include <QWidget>
 #include <QQueue>

 class RenderArea : public QWidget
 {
     Q_OBJECT

 public:
     enum Shape {Dequeue, Enqueue};

     RenderArea(QWidget *parent = 0);

     QSize minimumSizeHint() const;
     QSize sizeHint() const;
	 int i,N,te,count;
     QQueue<int> queue1;
     QQueue<int> queue2;

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
