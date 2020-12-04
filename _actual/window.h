/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include <QComboBox>
#include <string>

class _gl_widget;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _window : public QMainWindow
{
    Q_OBJECT

public:
    _window();

    //  Interaction with OpenGL
    // Checkboxes
    void pointCheckBoxInteraction(bool Checked);
    void lineCheckBoxInteraction(bool Checked);
    void fillCheckBoxInteraction(bool Checked);
    void chessCheckBoxInteraction(bool Checked);

    // Combo box
    void modelSelectorInteraction(int item);
    // Text
    void text(std::string foo);
private:
  _gl_widget *GL_widget;

  //  Interaction with OpenGL
  // Checkboxes
  QCheckBox *pointCheckBox,
            *lineCheckBox,
            *fillCheckBox,
            *chessCheckBox;

  // Combo Box
  QComboBox *modelSelector;
  // Text
  QLabel *cameraXAngle;
};

#endif
