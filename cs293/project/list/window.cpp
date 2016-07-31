#include <QtGui>
#include "renderarea.h"
#include "window.h"
#include<iostream>
const int IdRole = Qt::UserRole;

 Window::Window()
 {
     renderArea = new RenderArea;											// making renderArea point to a new location

     shapeComboBox = new QComboBox;											// making the pointer shapeComboBox pointing to a ComboBox
     shapeComboBox->addItem(tr("Pop_back"), RenderArea::Pop_back);			// adding items to the comboBox
     shapeComboBox->addItem(tr("Pop_front"), RenderArea::Pop_front);
     shapeComboBox->addItem(tr("Push_back"), RenderArea::Push_back);		// adding items to the comboBox
     shapeComboBox->addItem(tr("Push_front"), RenderArea::Push_front);
     shapeComboBox->addItem(tr("Delete"),RenderArea::Delete );

     shapeLabel = new QLabel(tr("&List:"));					// making shapeLabel point to a QLabel storing "Stack"  (& in front of S means a shortcut "Alt+S")
     shapeLabel->setBuddy(shapeComboBox);					// associating the label with the comboBox
     
     Box = new QSpinBox;
     Box->setRange(INT_MIN, INT_MAX);
     BoxLabel = new QLabel(tr("&Text:"));
     BoxLabel->setBuddy(Box);

	combo =new QComboBox;
	combo->addItem(tr("insert_Before"), RenderArea::insert_Before);
	combo->addItem(tr("insert_After"), RenderArea::insert_After);
	
	comboLabel =new QLabel(tr("&insert_Before:"));
	comboLabel->setBuddy(combo);
	
	box1 =new QSpinBox;
	box1->setRange(INT_MIN,INT_MAX);
	box2=new QSpinBox;
	box2->setRange(INT_MIN,INT_MAX);
	element =new QLabel(tr("&element:"));
	element->setBuddy(box1);
	newElement = new QLabel(tr("&newElement:"));
	newElement->setBuddy(box2);

	connect(combo,SIGNAL( activated(int) ),this, SLOT(insert() ) );
	
	connect(box1 ,SIGNAL( valueChanged(int) ),this, SLOT( b() ) );
	
	connect(box2 ,SIGNAL( valueChanged(int) ),this, SLOT( c() ) );
	
     connect(shapeComboBox, SIGNAL(activated(int) ),this, SLOT( shapeChanged() ) );				// connecting the "stack" button
             
     connect(Box, SIGNAL(valueChanged(int) ),this, SLOT( a() ) ) ;								// connecting the "text" button

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(renderArea, 0, 0, 1, 6);							// adds widget to the grid
     mainLayout->setRowMinimumHeight(1, 6);
     mainLayout->addWidget(shapeLabel, 2, 0, Qt::AlignRight);				// the arguments are widget *,row no.,column no.,alignment
     mainLayout->addWidget(shapeComboBox, 2, 1);
     mainLayout->addWidget(BoxLabel, 7, 0, Qt::AlignRight);
     mainLayout->addWidget(Box, 7, 1);
     mainLayout->addWidget(comboLabel,2,3,Qt::AlignRight);
     mainLayout->addWidget(combo,2,4);
	 mainLayout->addWidget(element,7,3,Qt::AlignRight);
	 mainLayout->addWidget(box1,7,4);
	 mainLayout->addWidget(newElement,12,3,Qt::AlignRight);
	 mainLayout->addWidget(box2,12,4);

     setLayout(mainLayout);

     shapeChanged();														// calling these functions to set the shape,pen and brush of the renderArea class
     penChanged();
     brushChanged();
     fontChanged();
     setWindowTitle(tr("LIST"));											// setting the title of the window
 }

 void Window::shapeChanged()
 {
     RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(shapeComboBox->currentIndex(), IdRole).toInt());         
     renderArea->setShape(shape);										// setting the shape of renderArea class
 }

 void Window::penChanged()
 {
     renderArea->setPen(QPen(Qt::black,1.2,Qt::SolidLine));								// setting the pen of renderArea class 
 }

 void Window::brushChanged()
 {
	 QLinearGradient linearGradient(0, 0, 1500, 1500);					// the arguments are (x1,y1,x2,y2)
     linearGradient.setColorAt(0.3, Qt::white);							// setting the stop points and the colour till that stop point
     linearGradient.setColorAt(0.6, Qt::green);
     linearGradient.setColorAt(0.0, Qt::red);
     renderArea->setBrush(linearGradient);								// setting the brush of the renderArea class as linearGradient
 }

 void Window::a()
 {
     renderArea->te = Box->value();										// setting the value inserted in the "text" box as the value inserted 
 }
 
 void Window::fontChanged()
 {
 	 renderArea->setFont(QFont("Arial",20) );							// setting the font size
 }
 
 void Window::b(){
 	 renderArea->value1=box1->value();
 }
 
 void Window::c(){
 	 renderArea->value2=box2->value();
 }
 
 void Window::insert(){
     RenderArea::Shape shape = RenderArea::Shape(combo->itemData(combo->currentIndex(), IdRole).toInt());         
     renderArea->setShape(shape);										// setting the shape of renderArea class	 
 }
 
