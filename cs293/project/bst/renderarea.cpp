#include <QStack>
#include <QtGui>
#include <iostream>
#include <QTextStream>
#include <QQueue>
#include <QStack>
#include <QVector>
#include <utility>
#include <cmath>
#include "renderarea.h"

 RenderArea::RenderArea(QWidget *parent)
     : QWidget(parent)
 {
     setBackgroundRole(QPalette::Base);
     setAutoFillBackground(true);
 }

 void RenderArea::setShape(Shape shape)
 {
     this->shape = shape;			// setting the shape of the Qpainter object as the argument passed 
     update();		
    /** update function-checking the paint engine's current state and update the properties that are changed **/
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
     painter.setPen(pen);					// setting the pen of the Qpainter object as the argument passed
     painter.setBrush(brush);					// for setting the argument passed as the brush of the painter
     painter.setFont(font);
     switch (shape) {						// switch statement to check whether push is done or pop 
		case Insert:
			{
				S.insert(te);			// calling the insert function to insert the integer in BST
				QVector <int> V = S.print_inorder();		// calling inorder function to assign the pos and depth 
										// and return the required data as a vector
				for(int i=0; i<V.size(); )			
				{				
				int x = V[i];			// x stores the pos of the element(used for x co-ordinate)
				i++;				
				int y = V[i];			// y stores the depth
				i++;
				int n = V[i];			// n stores the element
				i++;
				int l = V[i];			// l stores whether right or left child or root
				i++;
				int p = V[i];			// p stores the parent key
				i++;
				if(l==0)			// if root then
				{				
				painter.drawEllipse(600+x*100, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				}
				else if(l==-1)			// if left child then
				{				
				painter.drawEllipse(600+x*100+50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100+50, y*100+85);
				QString ui;
				ui= QString::number(n);		// converting the integer "n" in string and storing it in string "ui"
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);		// find the parent element
	
				if (P.third==0)			// if parent was root
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)		// if parent was a right child
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)		// if parent was a left child itself
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				
				else if (l==1)			// if right child then
				{
				painter.drawEllipse(600+x*100-50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100-50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);		// find the parent element
	
				if (P.third==0)			// if the parent was a root
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)		// if the parent was a right child
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)		// if the parent was a left child
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				}				
			}

		break;
		case Remove:
			{
				S.remove(te);
				QVector <int> V = S.print_inorder();
				for(int i=0; i<V.size(); )
				{
				int x = V[i];
				i++;
				int y = V[i];
				i++;
				int n = V[i];
				i++;
				int l = V[i];
				i++;
				int p = V[i];
				i++;
				if(l==0)
				{				
				painter.drawEllipse(600+x*100, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				}
				else if(l==-1)
				{				
				painter.drawEllipse(600+x*100+50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100+50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				else if (l==1)
				{
				painter.drawEllipse(600+x*100-50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100-50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				}				
			}		
		break;
		case Search:
			{
				PAIR M;
				M=S.isPresent(te);
				QVector <int> V = S.print_inorder();
				for(int i=0; i<V.size(); )
				{
				int x = V[i];
				i++;
				int y = V[i];
				i++;
				int n = V[i];
				i++;
				int l = V[i];
				i++;
				int p = V[i];
				i++;
				if(l==0)
				{				
				painter.drawEllipse(600+x*100, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				}
				else if(l==-1)
				{				
				painter.drawEllipse(600+x*100+50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100+50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				else if (l==1)
				{
				painter.drawEllipse(600+x*100-50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100-50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				}
				
		// the three cases(if-else) are for drawing a square around the element which was searched 	
				if (M.third==0)
				{
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100+50,M.second*100+50);
				painter.drawLine(600+M.first*100,M.second*100+50+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				}
				else if (M.third==1)
				{
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100+50-50,M.second*100+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50+50,600+M.first*100+50-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50+50,M.second*100+50,600+M.first*100+50-50,M.second*100+50+50);
				}
				else if (M.third==-1)
				{
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50+50,600+M.first*100+50+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50+50);
				}
			}		
		break;
		case Find_Minimum:
			{
				PAIR M;
				M=S.findMin();
				QVector <int> V = S.print_inorder();
				for(int i=0; i<V.size(); )
				{
				int x = V[i];
				i++;
				int y = V[i];
				i++;
				int n = V[i];
				i++;
				int l = V[i];
				i++;
				int p = V[i];
				i++;
				if(l==0)
				{				
				painter.drawEllipse(600+x*100, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				}
				else if(l==-1)
				{				
				painter.drawEllipse(600+x*100+50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100+50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				else if (l==1)
				{
				painter.drawEllipse(600+x*100-50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100-50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				}

		// the three cases(if-else) are for drawing a square around the  minimum element 	
				if (M.third==0)
				{
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100+50,M.second*100+50);
				painter.drawLine(600+M.first*100,M.second*100+50+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				}
				else if (M.third==1)
				{
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100+50-50,M.second*100+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50+50,600+M.first*100+50-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50+50,M.second*100+50,600+M.first*100+50-50,M.second*100+50+50);
				}
				else if (M.third==-1)
				{
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50+50,600+M.first*100+50+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50+50);
				}
			}		
		break;
		case Find_Maximum:
			{
				PAIR M;
				M=S.findMax();
				QVector <int> V = S.print_inorder();
				for(int i=0; i<V.size(); )
				{
				int x = V[i];
				i++;
				int y = V[i];
				i++;
				int n = V[i];
				i++;
				int l = V[i];
				i++;
				int p = V[i];
				i++;
				if(l==0)
				{				
				painter.drawEllipse(600+x*100, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				}
				else if(l==-1)
				{				
				painter.drawEllipse(600+x*100+50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100+50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				else if (l==1)
				{
				painter.drawEllipse(600+x*100-50, y*100+50, 50,50);		
				QPointF baseline(600+10+x*100-50, y*100+85);
				QString ui;
				ui= QString::number(n);
				painter.drawText(baseline,ui);
				PAIR P=S.isPresent(p);
	
				if (P.third==0)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25,P.second*100+50+50);
				}
				else if (P.third==1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25-50,P.second*100+50+50);
				}
				else if (P.third==-1)
				{
				painter.drawLine(600+x*100+50+25-100,y*100+50,600+P.first*100+25+50,P.second*100+50+50);
				}
				}
				}

		// the three cases(if-else) are for drawing a square around the  maximum element	
				if (M.third==0)
				{
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100+50,M.second*100+50);
				painter.drawLine(600+M.first*100,M.second*100+50+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100,M.second*100+50,600+M.first*100,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				}
				else if (M.third==1)
				{
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100+50-50,M.second*100+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50+50,600+M.first*100+50-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50,M.second*100+50,600+M.first*100-50,M.second*100+50+50);
				painter.drawLine(600+M.first*100-50+50,M.second*100+50,600+M.first*100+50-50,M.second*100+50+50);
				}
				else if (M.third==-1)
				{
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50+50,600+M.first*100+50+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50,M.second*100+50,600+M.first*100+50,M.second*100+50+50);
				painter.drawLine(600+M.first*100+50+50,M.second*100+50,600+M.first*100+50+50,M.second*100+50+50);
				}
			}		
		break;
     }
 }
