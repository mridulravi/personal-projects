#include <QtGui>
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
     painter.setPen(pen);									// setting the pen of the Qpainter object as the argument passed
     painter.setBrush(brush);								// for setting the argument passed as the brush of the painter
     painter.setFont(font);
     QList<int>::iterator itr;
     switch (shape) {										// switch statement to check whether push is done or pop 
	     case Pop_back:
	         if(list.empty() ){								// if list is empty then draw only the container box and terminate 
             	break;
             }
             list.pop_back();
            N=N-100;  										// decrement the value of n
            itr=list.begin();								// making itr point to the beginning of the list
			for (i=10;i<N and itr!=list.end();i+=100)
            {
				painter.drawRect(i, 50, 70, 40);			// drawing a rectangle,arguments are (x1,y1,length(horizontal),width(vertical) )
				QPointF baseline(i+10, 80);					// declaring a QpointF object and storing the coordinates in it
				QString ui;
				int be = *itr;								// storing the value pointed by itr in "be"
				itr++;
				ui= QString::number(be);					// converting the integer "be" in string and storing the string in "ui"
				painter.drawText(baseline,ui);				// writing the number in the drawn rectangle
				if(i>10){									// if i>10 then drawing the line and arrows which shows the next element of the linked list
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);
				}
				if(i==10){									// if i==10 then displaying the "front" label over it
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=100){								// if last element ,then displaying the "back" label over it
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}				
    	    }
            break;
            
	     case Pop_front:
	         if(list.empty() ){								// if list is empty then draw only the container box and terminate 
             	break;
             }
             list.pop_front();
            N=N-100;  										// decrement the value of n
            itr=list.begin();
			for (i=10;i<N and itr!=list.end();i+=100)
            {
				painter.drawRect(i, 50, 70, 40);			// drawing a rectangle,arguments are (x1,y1,length(horizontal),width(vertical) )
				QPointF baseline(i+10, 80);					// declaring a QpointF object and storing the coordinates in it
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}	
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}							
    	    }
            break;         
         
        case Push_back:
   			list.push_back(te);
   			itr=list.begin();
			for (i=10;i<=N and itr!=list.end();i+=100){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}	
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}							
			}
    		N=N+100;
         	break;
         	
        case Push_front:
   			list.push_front(te);
   			itr=list.begin();
			for (i=10;i<=N and itr!=list.end();i+=100){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}		
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}						
			}
    		N=N+100;
         	break; 
        
         case Delete:
         	itr=list.begin();
         	while(itr!=list.end() ){
         		if(*itr==te){
         			list.erase(itr);
         			N=N-100;
         			break;
         		}
         		itr++;
         	}
         	if(itr==list.end() ){
         		QPointF baseline(40,200);
         		QString ui="the entered element to be deleted was not found in the list";
         		painter.drawText(baseline,ui);
         	}
         	itr=list.begin();
			for (i=10;i<=N and itr!=list.end();i+=100){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}		
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}	
			}
         	break;  
         	
         	//
         	  
         case insert_Before:
         	itr=list.begin();
         	while(itr!=list.end() ){
         		if(*itr==value1){
         			N=N+100;
         			list.insert(itr,value2);   
         			break;
         		}
         		itr++;
         	}
         	if(itr==list.end() ){
         		QPointF baseline(40,200);
         		QString ui="the entered element before which the number is to be inserted is not found in the list";
         		painter.drawText(baseline,ui);
         	}
         	itr=list.begin();
			for (i=10;i<=N and itr!=list.end();i+=100){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}		
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}	
			}
         	break;  
         	
         	
         case insert_After:
         	itr=list.begin();
         	while(itr!=list.end() ){
         		if(*itr==value1){
         			N=N+100;
         			list.insert(++itr,value2);
         			itr--;
         			break;
         		}
         		itr++;
            }   
         	if(itr==list.end() ){
         		QPointF baseline(40,200);
         		QString ui="the entered element after which the number is to be inserted is not found in the list";
         		painter.drawText(baseline,ui);
         	} 
         	itr=list.begin();
			for (i=10;i<=N and itr!=list.end();i+=100){
    			painter.drawRect(i, 50, 70, 40);
				QPointF baseline(i+10, 80);
				QString ui;
				int be = *itr;
				itr++;
				ui= QString::number(be);
				painter.drawText(baseline,ui);
				if(i>10){
					painter.drawLine(i-30,70,i,70);
					painter.drawLine(i,70,i-5,75);
					painter.drawLine(i,70,i-5,65);					
				}		
				if(i==10){
					painter.drawLine(i+35,10.0,i+35,40.0);
					painter.drawLine(i+35,40.0,i+40,35.0);
					painter.drawLine(i+35,40,i+30,35);					
					ui="Front";
					baseline.setX(i+40);
					baseline.setY(30);
					painter.drawText(baseline,ui);
				}				
				if(N-i<=100){
					painter.drawLine(i+35,110.0,i+35,150.0);
					painter.drawLine(i+35,110,i+40,115);
					painter.drawLine(i+35,110,i+30,115);					
					ui="Back";
					baseline.setX(i+40);
					baseline.setY(140);
					painter.drawText(baseline,ui);
				}	
			}
         	break;           
     }
 }
