HEADERS += \
  classChessboard.h \
  classCone.h \
  classCylinder.h \
  classObjectPly.h \
  classObjectRevolution.h \
  classSphere.h \
  classTelescope.h \
  classTelescope_part_eyepiece.h \
  classTelescope_part_focusTube.h \
  classTelescope_part_lens.h \
  classTelescope_part_mount.h \
  classTelescope_part_tripod.h \
  classTelescope_part_tube.h \
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
  classChessboard.cpp \
  classCone.cc \
  classCylinder.cc \
  classObjectPly.cc \
  classObjectRevolution.cc \
  classSphere.cc \
  classTelescope.cc \
  classTelescope_part_eyepiece.cc \
  classTelescope_part_focusTube.cc \
  classTelescope_part_lens.cc \
  classTelescope_part_mount.cc \
  classTelescope_part_tripod.cc \
  classTelescope_part_tube.cc \
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
