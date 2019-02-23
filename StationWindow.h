/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    StationWindow.h
 *
 * A Station object organizes drones and senders, communicates with Vicon and
 * updates measurements for drones using a separate thread.
 *
 * A StationWindow is the main GUI.
 *
 * This is the View of the
 * Model(Station)-View(StationWindow)-Controller(StationController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef STATIONWINDOW_H
#define STATIONWINDOW_H

#include "StationController.h"
#include <QMainWindow>
#include <SenderWindow.h>
#include <QLabel>
#include <QColor>
#include <QCloseEvent>
#include "Sender.h"
#include <memory>

namespace Ui
{
class StationWindow; // hidden class: builder for ui
}

class StationWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit StationWindow(std::unique_ptr<StationController> &controller, QWidget *parent = 0);
    ~StationWindow();
    void closeEvent(QCloseEvent *event) override;
    void senderWindowCloseHandler(const QString &name);

  signals:

  public slots:
    void launchViconStream();
    void stopViconStream();
    void addName(QString name);
    void removeName(QString name);
    void updatedt(double dt);
    void startSenderHandler();
    void setOnline();
    void setOffline();

  private:
    Ui::StationWindow *ui;
    std::unique_ptr<StationController> &controller;

    void initialize();
    void setupConnections();

    std::map<QString, std::unique_ptr<SenderWindow>> senderWindows;
    std::map<QString, std::unique_ptr<SenderController>> senderControllers;
    std::map<QString, std::unique_ptr<Sender>> senders;

    // helpers
    void setLabelColor(QLabel *, QColor);

    void setNorth(const QString &axis);
};

#endif // STATIONWINDOW_H
