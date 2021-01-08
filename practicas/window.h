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
    void firstLightCheckBoxInteraction(bool Checked);
    void secondLightCheckBoxInteraction(bool Checked);
    void animationCheckBoxInteraction(bool Checked);

    // Combo box
    void modelSelectorInteraction(int item);

    // Slider
    void alphaSetSlider(int pos);
    void betaSetSlider(int pos);
    void gammaSetSlider(int pos);

    // Text Display
    void alphaSetText(std::string input);
    void betaSetText(std::string input);
    void gammaSetText(std::string input);

private:
  _gl_widget *GL_widget;

  //  Interaction with OpenGL
  // Checkboxes
  QCheckBox *pointCheckBox,
            *lineCheckBox,
            *fillCheckBox,
            *chessCheckBox,
            *flatLCheckBox,
            *smoothLCheckBox,
            *unlitTCheckBox,
            *flatTextCheckBox,
            *smoothTextCheckBox,
            *firstLightBox,
            *secondLightBox,
            *animationCheckBox;

  // Combo Box
  QComboBox *modelSelector,
            *cameraSelector,
            *materialSelector;

  // Line Edit
  QLineEdit *modAlphaText,
            *modBetaText,
            *modGammaText;

  // Sliders
  QSlider *alphaSlider,
          *betaSlider,
          *gammaSlider;
};

#endif
