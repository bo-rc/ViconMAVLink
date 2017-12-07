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
#include "StationWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<Station> station { new Station };
    std::unique_ptr<StationController> controller{ new StationController(station) };
    std::unique_ptr<StationWindow> w { new StationWindow(controller) };
    w->show();

    return a.exec();
}
