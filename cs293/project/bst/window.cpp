#include <QtGui>
//#include "iitbOrderedSet.h"
#include "renderarea.h"
#include "window.h"
#include<iostream>
const int IdRole = Qt::UserRole;

 Window::Window()
 {
     renderArea = new RenderArea;					// making renderArea point to a new location

     shapeComboBox = new QComboBox;					// making the pointer shapeComboBox pointing to a ComboBox
     shapeComboBox->addItem(tr("Remove"), RenderArea::Remove);		// adding items to the comboBox  
     shapeComboBox->addItem(tr("Insert"), RenderArea::Insert);		// adding items to the comboBox 
     shapeComboBox->addItem(tr("Search"), RenderArea::Search);		// adding items to the comboBox   
     shapeComboBox->addItem(tr("Find_Minimum"), RenderArea::Find_Minimum);// adding items to the comboBox 
     shapeComboBox->addItem(tr("Find_Maximum"), RenderArea::Find_Maximum);// adding items to the comboBox 

     shapeLabel = new QLabel(tr("&Operation:"));		
     // making shapeLabel point to a QLabel storing "Operation"  (& in front of O means a shortcut "Alt+O")
     shapeLabel->setBuddy(shapeComboBox);			// associating the label with the comboBox
     
     Box = new QSpinBox;					// creating a new QSpinBox which would be used to input text
     Box->setRange(INT_MIN, INT_MAX);
     BoxLabel = new QLabel(tr("&Text:"));			// making BoxLabel point to a QLabel storing "Text"
     BoxLabel->setBuddy(Box);					// associating the label with the spinbox

     connect(shapeComboBox, SIGNAL(activated(int) ),this, SLOT( shapeChanged() ) );// connecting the "stack" button
             
     connect(Box, SIGNAL(valueChanged(int) ),this, SLOT( a() ) ) ;		   // connecting the "text" button

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->setColumnStretch(0, 1);			// set the stretch factor of the specified column to the second argument
     mainLayout->setColumnStretch(3, 1);
     mainLayout->addWidget(renderArea, 0, 0, 1, 4);		// adds widget to the grid
     mainLayout->setRowMinimumHeight(1, 6);
     mainLayout->addWidget(shapeLabel, 2, 1, Qt::AlignRight);	// the arguments are widget *,row no.,column no.,alignment
     mainLayout->addWidget(shapeComboBox, 2, 2);
     mainLayout->addWidget(BoxLabel, 7, 1, Qt::AlignRight);
     mainLayout->addWidget(Box, 7, 2);
     setLayout(mainLayout);

     shapeChanged();					// calling these functions to set the shape,pen and brush of the renderArea class
     penChanged();
     fontChanged();
     setWindowTitle(tr("Binary Search Tree"));		// setting the title of the window
 }

 void Window::shapeChanged()
 {
     RenderArea::Shape shape = RenderArea::Shape(shapeComboBox->itemData(shapeComboBox->currentIndex(), IdRole).toInt());         
     renderArea->setShape(shape);					// setting the shape of renderArea class
 }

 void Window::penChanged()
 {
     renderArea->setPen(QPen(Qt::black,1.2,Qt::SolidLine));		// setting the pen of renderArea class 
 }

 void Window::a()
 {
     renderArea->te = Box->value();					// storing the value inserted in the "Text" SpinBox in the 
 }									// int variable "te" of the renderArea class
 
 void Window::fontChanged()
 {
 	 renderArea->setFont(QFont("Arial",20) );			// setting the font
 }
 
