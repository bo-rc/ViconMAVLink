/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    SenderWindow.h
 *
 * A Sender object reads Vicon data from a Station object, processes the data
 * with Kalman filtering and computes a GPS MAVLink data pack, sends MAVLink
 * messages to a robot via UDP.
 *
 * This is the View of the
 * Model(Sender)-View(SenderWindow)-Controller(SenderController) pattern.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef SENDERWINDOW_H
#define SENDERWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include "SenderController.h"

namespace Ui
{
class SenderWindow;
}

class SenderWindow : public QWidget
{
    Q_OBJECT

  public:
    explicit SenderWindow(const QString &name,
                          std::unique_ptr<SenderController> &controller,
                          QWidget *parent = 0);
    void closeEvent(QCloseEvent *event) override;
    ~SenderWindow();
    void setStandBy();
    void setActive();

  signals:
    void closeSelf(const QString &name);
    void senderStarted();
    void senderStopped();
    void rateChanged();

  public slots:
    void updateRateLabel();
    void startSenderHandler();
    void stopSenderHandler();

  private:
    Ui::SenderWindow *ui;
    QString name;
    std::unique_ptr<SenderController> &controller;

    void initialize();
    void setupConnections();

    // helpers
    void setLabelColor(QLabel *label, QColor color);
};

#endif // SENDERWINDOW_H
