#include <QtGui>
#include "renderarea.h"
#include "window.h"
#include<iostream>
const int IdRole = Qt::UserRole;

 Window::Window()
 {
     renderArea = new RenderArea;							// making renderArea point to a new location

     shapeComboBox = new QComboBox;							// making the pointer shapeComboBox pointing to a ComboBox
     shapeComboBox->addItem(tr("Pop"), RenderArea::Pop);	// adding items to the comboBox
     shapeComboBox->addItem(tr("Push"), RenderArea::Push);	// adding items to the comboBox
     

     shapeLabel = new QLabel(tr("&Stack:"));				// making shapeLabel point to a QLabel storing "Stack"  (& in front of S means a shortcut "Alt+S")
     shapeLabel->setBuddy(shapeComboBox);					// associating the label with the comboBox
     
     Box = new QSpinBox;
     Box->setRange(INT_MIN, INT_MAX);
     BoxLabel = new QLabel(tr("&Text:"));
     BoxLabel->setBuddy(Box);

     connect(shapeComboBox, SIGNAL(activated(int) ),this, SLOT( shapeChanged() ) );				// connecting the "stack" button
             
     connect(Box, SIGNAL(valueChanged(int) ),this, SLOT( a() ) ) ;								// connecting the "text" button

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->setColumnStretch(0, 1);									// set the stretch factor of the specified column to the second argument
     mainLayout->setColumnStretch(3, 1);
     mainLayout->addWidget(renderArea, 0, 0, 1, 4);							// adds widget to the grid
     mainLayout->setRowMinimumHeight(1, 6);
     mainLayout->addWidget(shapeLabel, 2, 1, Qt::AlignRight);				// the arguments are widget *,row no.,column no.,alignment
     mainLayout->addWidget(shapeComboBox, 2, 2);
     mainLayout->addWidget(BoxLabel, 7, 1, Qt::AlignRight);
     mainLayout->addWidget(Box, 7, 2);
     setLayout(mainLayout);

     shapeChanged();														// calling these functions to set the shape,pen and brush of the renderArea class
     penChanged();
     brushChanged();
     fontChanged();
     setWindowTitle(tr("STACK"));											// setting the title of the window
 }

 void Window::shapeChanged()
 {
     RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(shapeComboBox->currentIndex(), IdRole).toInt());         
     renderArea->setShape(shape);										// setting the shape of renderArea class
 }

 void Window::penChanged()
 {
     renderArea->setPen(QPen(Qt::black,1.2,Qt::SolidLine));				// setting the pen of renderArea class 
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
     renderArea->te = Box->value();
 }
 
 void Window::fontChanged()
 {
 	 renderArea->setFont(QFont("Arial",20) );							// setting the font
 }
 
