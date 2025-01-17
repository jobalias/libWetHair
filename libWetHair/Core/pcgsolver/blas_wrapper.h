//
// This file is part of the libWetHair open source project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Copyright 2017 Yun (Raymond) Fei, Henrique Teles Maia, Christopher Batty,
// Changxi Zheng, and Eitan Grinspun
//

#ifndef LIBWETHAIR_CORE_BLAS_WRAPPER_H_
#define LIBWETHAIR_CORE_BLAS_WRAPPER_H_

// Simple placeholder code for BLAS calls - replace with calls to a real BLAS
// library

#include <Eigen/Core>
#include <vector>

namespace robertbridson {

namespace BLAS {
// dot products ==============================================================

inline double dot(const std::vector<double> &x, const std::vector<double> &y) {
  double sum = 0;
  size_t n = x.size() < y.size() ? x.size() : y.size();
  return Eigen::Map<Eigen::VectorXd>((double *)&y[0], n)
      .dot(Eigen::Map<Eigen::VectorXd>((double *)&x[0], n));
}

// inf-norm (maximum absolute value: index of max returned) ==================

inline int index_abs_max(const std::vector<double> &x) {
  int maxind = 0;
  int col = 0;

  size_t n = x.size();
  Eigen::Map<Eigen::VectorXd>((double *)&x[0], n)
      .cwiseAbs()
      .maxCoeff(&maxind, &col);

  return maxind;
}

// inf-norm (maximum absolute value) =========================================
// technically not part of BLAS, but useful

inline double abs_max(const std::vector<double> &x) {
  return std::fabs(x[index_abs_max(x)]);
}

// saxpy (y=alpha*x+y) =======================================================

inline void add_scaled(double alpha, const std::vector<double> &x,
                       std::vector<double> &y) {
  size_t n = x.size() < y.size() ? x.size() : y.size();
  Eigen::Map<Eigen::VectorXd>((double *)&y[0], n) +=
      Eigen::Map<const Eigen::VectorXd>((const double *)&x[0], n) * alpha;
}
}  // namespace BLAS
}  // namespace robertbridson
#endif  // LIBWETHAIR_CORE_BLAS_WRAPPER_H_
