#include <QtGui>
#include <QQueue>
#include "renderarea.h"

 RenderArea::RenderArea(QWidget *parent)
     : QWidget(parent)
 {
	 N = 10;count=1;
     setBackgroundRole(QPalette::Base);
     setAutoFillBackground(true);
 }

 QSize RenderArea::minimumSizeHint() const
 {
     return QSize(100, 100);
 }

 QSize RenderArea::sizeHint() const
 {
     return QSize(400, 200);
 }

 void RenderArea::setShape(Shape shape)
 {
     this->shape = shape;							// setting the shape of the Qpainter object as the argument passed 
     update();										// update function-checking the paint engine's current state and update the properties that are changed
 }

 void RenderArea::setPen(const QPen &pen)
 {
     this->pen = pen;										
     update();
 }

 void RenderArea::setBrush(const QBrush &brush)
 {
     this->brush = brush;
     update();
 }
 
 void RenderArea::setFont(const QFont &font)
 {
 	 this->font = font;
 	 update();
 }
 
 void RenderArea::paintEvent(QPaintEvent *)
 {
     QPainter painter(this);
     painter.setPen(pen);										// setting the pen of the Qpainter object as the argument passed
     painter.setBrush(brush);									// for setting the argument passed as the brush of the painter
     painter.setFont(font);
     switch (shape) {											// switch statement to check whether push is done or pop 
	     case Dequeue:
	         if(queue1.isEmpty() ){								// if queue is empty then draw only the container box and terminate 
	    		painter.drawLine(5.0, 40.0, 1500.0, 40.0);
				painter.drawLine(5.0, 110.0, 1500.0, 110.0);
             	break;
             }
			queue1.dequeue();
            N=N-70;  											// decrement the value of n
			for (i=10;i<N;i+=70)
            {
				painter.drawRect(i, 50, 70, 40);				// drawing a rectangle,arguments are (x1,y1,length(horizontal),width(vertical) )
				QPointF baseline(i+10, 80);						// declaring a QpointF object and storing the coordinates in it
				QString ui;
				int be = queue1.dequeue();
				queue2.enqueue(be);
				ui= QString::number(be);
				painter.drawText(baseline,ui);					// writing the number in the rectangle drawn
	    		painter.drawLine(5.0, 40.0, 1500.0, 40.0);		// drawing the line above the rectangle
				painter.drawLine(5.0, 110.0, 1500.0, 110.0);	// drawing the line below the rectangle
				if(i==10){										// if it is the first block then displaying the "front" label over it
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=70){									// if last block then displaying the "back" label over it
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}				
    	    }
	        queue1=queue2;
			while(!queue2.isEmpty())
				queue2.dequeue();
            break;
            
        case Enqueue:
   			queue1.enqueue(te);
			for (i=10;i<=N;i+=70){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = queue1.dequeue();
				queue2.enqueue(be);
				ui= QString::number(be);
				painter.drawText(baseline,ui);
	    		painter.drawLine(5.0, 40.0, 1500.0, 40.0);
				painter.drawLine(5.0, 110.0, 1500.0, 110.0);
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<70){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}				
			}
			queue1=queue2;
			while(!queue2.isEmpty() ){
				queue2.dequeue();
			}
    		N=N+70;
		 	count=1;
         	break;
     }
 }
