/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017 by University of Illinois			   *
 *                                                                         *
 *   http://illinois.edu                                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file    KalmanFilter.h
 *
 * A linear KalmanFilter aims to recover latent velocity variables based on
 * Vicon position measurement.
 *
 * @author  Bo Liu  <boliu1@illinois.edu>
 *
 */
#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <QObject>
#include "eigen3/Eigen/Dense"
#include <cmath>

class KalmanFilter : public QObject
{
    Q_OBJECT
public:
    explicit KalmanFilter(QObject *parent = 0);

    // state vector
    Eigen::VectorXd x_;

    // state covariance matrix
    Eigen::MatrixXd P_;

    // state transition matrix
    Eigen::MatrixXd F_;

    // process covariance matrix
    Eigen::MatrixXd Q_;

    // measurement matrix
    Eigen::MatrixXd H_;

    // measurement covariance matrix
    Eigen::MatrixXd R_;

    void update_dt(double dt);

    /**
     * Init Initializes Kalman filter
     * @param x_in Initial state
     * @param P_in Initial state covariance
     * @param F_in Transition matrix
     * @param H_in Measurement matrix
     * @param R_in Measurement covariance matrix
     * @param Q_in Process covariance matrix
     */
    void init(Eigen::VectorXd &x_in, Eigen::MatrixXd &P_in, Eigen::MatrixXd &F_in,
	Eigen::MatrixXd &Q_in, Eigen::MatrixXd &H_in, Eigen::MatrixXd &R_in);

    void predict();
    void update(const Eigen::VectorXd & z);

    double dt;

signals:

public slots:
};

#endif // KALMANFILTER_H
