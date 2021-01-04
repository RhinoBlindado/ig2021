/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QTimer>
#include <QComboBox>
#include <QGroupBox>
#include "window.h"
#include "glwidget.h"
#include <QImageReader>


// EXTRA: COMMUNICATION WITH OPENGL

void _window::pointCheckBoxInteraction(bool checked)
{
  pointCheckBox->blockSignals(true);

  if(checked)
  {
      pointCheckBox->setCheckState(Qt::Checked);
  }
  else
  {
      pointCheckBox->setCheckState(Qt::Unchecked);
  }

  pointCheckBox->blockSignals(false);
}

void _window::lineCheckBoxInteraction(bool checked)
{
  lineCheckBox->blockSignals(true);

  if(checked)
  {
      lineCheckBox->setCheckState(Qt::Checked);
  }
  else
  {
      lineCheckBox->setCheckState(Qt::Unchecked);
  }

  lineCheckBox->blockSignals(false);
}

void _window::fillCheckBoxInteraction(bool checked)
{
  fillCheckBox->blockSignals(true);

  if(checked)
  {
      fillCheckBox->setCheckState(Qt::Checked);
  }
  else
  {
      fillCheckBox->setCheckState(Qt::Unchecked);
  }

  fillCheckBox->blockSignals(false);
}

void _window::chessCheckBoxInteraction(bool checked)
{
  chessCheckBox->blockSignals(true);

  if(checked)
  {
      chessCheckBox->setCheckState(Qt::Checked);
  }
  else
  {
      chessCheckBox->setCheckState(Qt::Unchecked);
  }

  chessCheckBox->blockSignals(false);
}

/**
 * @brief Change the item in the selector box
 * @param item      Index of the item.
 */
void _window::modelSelectorInteraction(int item)
{
    modelSelector->blockSignals(true);

    modelSelector->setCurrentIndex(item);

    modelSelector->blockSignals(false);
}

/*****************************************************************************//**
 * @brief The initialization of the Window class.
 *
 *****************************************************************************/
_window::_window()
{
 // Initializing the Main Widget
 QWidget *mainWidget = new QWidget(this);
 setCentralWidget(mainWidget);
 setWindowTitle(tr("[IG] Práctica de Valentino Lugli"));
 resize(800,600);
 mainWidget->setMinimumWidth(400);
 mainWidget->setMinimumHeight(400);

 // Initizaling the Main Layout
 QHBoxLayout *mainLayout = new QHBoxLayout;

 // Initializing the sidebar
 QTabWidget *sideBar = new QTabWidget;
 sideBar->setMaximumWidth(200);

 // Initializing the OpenGL Widget
 GL_widget = new _gl_widget(this);
 QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);
 GL_widget->setSizePolicy(Q);

 // Adding the Main Layout to the Main Widget
 mainWidget->setLayout(mainLayout);
 // Adding the GL_Widget and Sidebar to Main Layout
 mainLayout->addWidget(GL_widget);
 mainLayout->addWidget(sideBar);


 //     SIDEBAR
 QWidget *generalWidget = new QWidget;
 sideBar->addTab(generalWidget,"General");

 //     GENERAL TAB
 // Connecting it to the general widget
 QVBoxLayout *generalLayout = new QVBoxLayout;
 generalWidget->setLayout(generalLayout);

 // Model Selector
 QGroupBox *modelBox = new QGroupBox("Modelo");
 generalLayout->addWidget(modelBox);

 QVBoxLayout *modelLayout = new QVBoxLayout;
 modelBox->setLayout(modelLayout);

 modelSelector = new QComboBox;
 modelSelector->addItem("Tetrahedro");
 modelSelector->addItem("Cubo");
 modelSelector->addItem("Cono");
 modelSelector->addItem("Cilindro");
 modelSelector->addItem("Esfera");
 modelSelector->addItem("Objeto PLY");
 modelSelector->addItem("Objeto Jerárquico");
 modelSelector->addItem("Tablero de Ajedrez");

 modelLayout->addWidget(modelSelector);
 connect(modelSelector, SIGNAL(activated(int)), GL_widget, SLOT(slotModel(int)));


 // Draw Modes
 QGroupBox *modesBox = new QGroupBox("Modos de Dibujado");
 generalLayout->addWidget(modesBox);

 QGridLayout *modeLayout = new QGridLayout;
 modesBox->setLayout(modeLayout);

 QLabel *basicTitle = new QLabel("Básicos");
 basicTitle->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px;");
 modeLayout->addWidget(basicTitle,0,1);

 //     Points
 pointCheckBox = new QCheckBox;
 QLabel *pointsLabel = new QLabel("Puntos");
 modeLayout->addWidget(pointCheckBox,1,0);
 modeLayout->addWidget(pointsLabel,1,1);

 connect(pointCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotPoint(int)));

 //     Lines
 lineCheckBox = new QCheckBox;
 QLabel *lineLabel = new QLabel("Líneas");
 modeLayout->addWidget(lineCheckBox,2,0);
 modeLayout->addWidget(lineLabel,2,1);

 lineCheckBox->setCheckState(Qt::Checked);
 connect(lineCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotLine(int)));

//      Fill
 fillCheckBox = new QCheckBox;
 QLabel *fillLabel = new QLabel("Relleno");
 modeLayout->addWidget(fillCheckBox,3,0);
 modeLayout->addWidget(fillLabel,3,1);

 connect(fillCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotFill(int)));

//      Chess
 chessCheckBox = new QCheckBox;
 QLabel *chessLabel = new QLabel("Ajedrez");
 modeLayout->addWidget(chessCheckBox,4,0);
 modeLayout->addWidget(chessLabel,4,1);
 connect(chessCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotChess(int)));


 QLabel *basicTitle2 = new QLabel("Iluminación");
 basicTitle2->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px;");
 modeLayout->addWidget(basicTitle2,5,1);
 //          Flat Light
  flatLCheckBox = new QCheckBox;
  QLabel *flatLLabel = new QLabel("Plana");
  modeLayout->addWidget(flatLCheckBox,6,0);
  modeLayout->addWidget(flatLLabel,6,1);
  connect(flatLCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotFlat(int)));

 //          Smooth Light
  smoothLCheckBox = new QCheckBox;
  QLabel *smoothLLabel = new QLabel("Goraund");
  modeLayout->addWidget(smoothLCheckBox,7,0);
  modeLayout->addWidget(smoothLLabel,7,1);
  connect(smoothLCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotSmooth(int)));

  QLabel *basicTitle3 = new QLabel("Textura");
  basicTitle3->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px;");
  modeLayout->addWidget(basicTitle3,8,1);
  //      Unlit Texture
   unlitTCheckBox = new QCheckBox;
   QLabel *unlitLabel = new QLabel("Sin Iluminación");
   modeLayout->addWidget(unlitTCheckBox,9,0);
   modeLayout->addWidget(unlitLabel,9,1);
   connect(unlitTCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotUnlitText(int)));

  //      Flat Lit Texture
   flatTextCheckBox = new QCheckBox;
   QLabel *flatTextLabel = new QLabel("Plana");
   modeLayout->addWidget(flatTextCheckBox,10,0);
   modeLayout->addWidget(flatTextLabel,10,1);
   connect(flatTextCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotFlatText(int)));

  //      Smooth Lit Texture
   smoothTextCheckBox = new QCheckBox;
   QLabel *smoothTextLabel = new QLabel("Goraund");
   modeLayout->addWidget(smoothTextCheckBox,11,0);
   modeLayout->addWidget(smoothTextLabel,11,1);
   connect(smoothTextCheckBox, SIGNAL(stateChanged(int)), GL_widget, SLOT(slotSmoothText(int)));

// LIGHTING
 //     Lights
 QGroupBox *lLightsBox = new QGroupBox("Luces");
 generalLayout->addWidget(lLightsBox);

 QGridLayout *lLBox = new QGridLayout;
 lLightsBox->setLayout(lLBox);

 //         1st Light
 firstLightBox = new QCheckBox;
 lLBox->addWidget(firstLightBox,0,0);
 lLBox->addWidget(new QLabel("Luz Blanca ∞"),0,1);

 //         2nd Light
 secondLightBox = new QCheckBox;
 lLBox->addWidget(secondLightBox,1,0);
 lLBox->addWidget(new QLabel("Luz Magenta"),1,1);

 //generalLayout->addStretch();

// QSlider *mySlider = new QSlider(Qt::Horizontal);
// generalLayout->addWidget(mySlider);

 // ADVANCED TAB
 QWidget *advancedWidget = new QWidget;
 sideBar->addTab(advancedWidget,"Animación");

 // PLY settings




 // NON UI SETTINGS
 // [P3] TIMER FOR ANIMATION
 QTimer *mainTimer = new QTimer;
 mainTimer->start(10);
 connect(mainTimer, SIGNAL(timeout()), GL_widget, SLOT(slotAnimationToggle()));


 // [P4] TEXTURES
 //     Loading the image
 QString File_name("../textures/dia_8192.jpg");
 QImage Image;
 QImageReader Reader(File_name);
 Reader.setAutoTransform(true);
 Image = Reader.read();
 if (Image.isNull()) {
   QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                            tr("Cannot load %1.").arg(QDir::toNativeSeparators(File_name)));
   exit(-1);
 }
 Image=Image.mirrored();
 Image=Image.convertToFormat(QImage::Format_RGB888);

 //     Sending the texture to GL Widget
 GL_widget->getTexture(Image);

 // MENU BAR
 //     Actions for the Menus.
 QAction *Exit = new QAction(QIcon("./icons/exit.png"), tr("&Exit..."), this);
 Exit->setShortcut(tr("Ctrl+Q"));
 Exit->setToolTip(tr("Exit the application"));
 connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

 //     Menus.
 QMenu *File_menu=menuBar()->addMenu(tr("&File"));
 File_menu->addAction(Exit);
 File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);


/*  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);

  QFrame *Framed_widget= new QFrame(Central_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);


  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);

  QHBoxLayout *Horizontal_frame = new QHBoxLayout();
  Horizontal_frame->setContentsMargins(1,1,1,1);

  Horizontal_frame->addWidget(GL_widget);
  Framed_widget->setLayout(Horizontal_frame);

  QHBoxLayout *Horizontal_main = new QHBoxLayout(Central_widget);

  Horizontal_main->addWidget(Framed_widget);

  Central_widget->setLayout(Horizontal_main);
  setCentralWidget(Central_widget);

  resize(800,800);
  */
}
