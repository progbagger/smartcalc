cmake_minimum_required(VERSION 3.5)

project(view VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

include_directories("model" "view" "controller")

set(PROJECT_SOURCES
  main.cpp

  view/view.h
  model/model.h
  controller/controller.h

  view/credit_calculator_view.h
  view/credit_calculator_view.cpp
  view/credit_calculator_view.ui
  view/deposit_calculator_view.h
  view/deposit_calculator_view.cpp
  view/deposit_calculator_view.ui
  view/math_calculator_view.h
  view/math_calculator_view.cpp
  view/math_calculator_view.ui
  view/paymentwidget.h
  view/paymentwidget.cpp
  view/paymentwidget.ui

  view/qcustomplot.h
  view/qcustomplot.cpp

  model/tokens.h
  model/tokens.cc
  model/tokenizer.h
  model/tokenizer.cc
  model/validator.h
  model/validator.cc
  model/date.h
  model/date.cc

  model/math_calc.h
  model/math_calc.cc
  model/credit_calc.h
  model/credit_calc.cc
  model/deposit_calc.h
  model/deposit_calc.cc
  model/credit_misc.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(view
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET view APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(view SHARED
      ${PROJECT_SOURCES}
    )

  # Define properties for Android with Qt 5 after find_package() calls as:
  # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(view
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_link_libraries(view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(view PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(view)
endif()
