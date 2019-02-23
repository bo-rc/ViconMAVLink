/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    main.cpp
 *
 * This is the entry point of the app.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#include <memory>
#include <QApplication>
#include "StationWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto station = std::make_unique<Station>();
    auto controller = std::make_unique<StationController>(station);
    auto mainWindow = std::make_unique<StationWindow>(controller);

    mainWindow->show();

    return app.exec();
}
