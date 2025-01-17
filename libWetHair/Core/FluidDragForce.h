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

#ifndef LIBWETHAIR_CORE_FLUID_DRAG_FORCE_H_
#define LIBWETHAIR_CORE_FLUID_DRAG_FORCE_H_

#include <Eigen/Core>
#include <iostream>

#include "Force.h"
#include "MathDefs.h"

template <int DIM>
class TwoDScene;

template <int DIM>
class FluidDragForce : public Force {
 public:
  FluidDragForce(const TwoDScene<DIM>& scene, int hidx);

  virtual ~FluidDragForce();

  virtual void computeIntegrationVars(const VectorXs& x, const VectorXs& v,
                                      const VectorXs& m, VectorXs& lambda,
                                      VectorXs& lambda_v, TripletXs& J,
                                      TripletXs& Jv, TripletXs& Jxv,
                                      TripletXs& tildeK, TripletXs& stiffness,
                                      TripletXs& damping, VectorXs& Phi,
                                      VectorXs& Phiv, const scalar& dt);

  virtual void preCompute(const VectorXs& x, const VectorXs& v,
                          const VectorXs& m, const scalar& dt);

  virtual int numConstraintPos();

  virtual int numConstraintVel();

  virtual int numJ();

  virtual int numJv();

  virtual int numJxv();

  virtual int numTildeK();

  virtual bool isParallelized();

  virtual bool isPrecomputationParallelized();

  virtual void storeLambda(const VectorXs& lambda, const VectorXs& lambda_v);

  virtual Force* createNewCopy();

  virtual void getAffectedVars(int pidx, std::unordered_set<int>& vars);

  virtual int getAffectedHair(const std::vector<int> particle_to_hairs);

  virtual bool isContained(int pidx);

  virtual void addGradEToTotal(const VectorXs& x, const VectorXs& v,
                               const VectorXs& m, VectorXs& gradE);

  virtual const char* name();

 private:
  VectorXs m_k0;
  VectorXs m_liquid_u;
  std::vector<int> m_hair_particle_affected;
  int m_hidx;

  const TwoDScene<DIM>& m_scene;
};

#endif  // LIBWETHAIR_CORE_FLUID_DRAG_FORCE_H_
