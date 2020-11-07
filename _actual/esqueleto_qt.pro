HEADERS += \
  classCone.h \
  classCylinder.h \
  classObjectPly.h \
  classObjectRevolution.h \
  classSphere.h \
  classTelescope.h \
  colors.h \
  basic_object3d.h \
  cube.h \
  file_ply_stl.h \
  object3d.h \
  axis.h \
  tetrahedron.h \
  glwidget.h \
  window.h

SOURCES += \
  basic_object3d.cc \
  classCone.cc \
  classCylinder.cc \
  classObjectPly.cc \
  classObjectRevolution.cc \
  classSphere.cc \
  classTelescope.cc \
  cube.cc \
  file_ply_stl.cc \
  object3d.cc \
  axis.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets
