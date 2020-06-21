#-------------------------------------------------
#
# Project created by QtCreator 2016-07-10T11:49:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Digitos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    recognition.cpp

HEADERS  += mainwindow.h \
    recognition.h \
    TNT&JAMA/jama_cholesky.h \
    TNT&JAMA/jama_eig.h \
    TNT&JAMA/jama_lu.h \
    TNT&JAMA/jama_qr.h \
    TNT&JAMA/jama_svd.h \
    TNT&JAMA/tnt.h \
    TNT&JAMA/tnt_array1d.h \
    TNT&JAMA/tnt_array1d_utils.h \
    TNT&JAMA/tnt_array2d.h \
    TNT&JAMA/tnt_array2d_utils.h \
    TNT&JAMA/tnt_array3d.h \
    TNT&JAMA/tnt_array3d_utils.h \
    TNT&JAMA/tnt_cmat.h \
    TNT&JAMA/tnt_fortran_array1d.h \
    TNT&JAMA/tnt_fortran_array1d_utils.h \
    TNT&JAMA/tnt_fortran_array2d.h \
    TNT&JAMA/tnt_fortran_array2d_utils.h \
    TNT&JAMA/tnt_fortran_array3d.h \
    TNT&JAMA/tnt_fortran_array3d_utils.h \
    TNT&JAMA/tnt_i_refvec.h \
    TNT&JAMA/tnt_math_utils.h \
    TNT&JAMA/tnt_sparse_matrix_csr.h \
    TNT&JAMA/tnt_stopwatch.h \
    TNT&JAMA/tnt_subscript.h \
    TNT&JAMA/tnt_vec.h \
    TNT&JAMA/tnt_version.h

FORMS    += mainwindow.ui
