cmake_minimum_required(VERSION 3.16)

project(VisioPlot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Find Qt 6 ----
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)

# ---- Sources ----
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    qcustomplot/qcustomplot.cpp
    qcustomplot/qcustomplot.h
)

# ---- Executable ----
qt_add_executable(VisioPlot
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# ---- Link Qt libraries ----
target_link_libraries(VisioPlot
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::PrintSupport
)

set_target_properties(VisioPlot PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# ---- Install ----
include(GNUInstallDirs)
install(TARGETS VisioPlot
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(VisioPlot)
