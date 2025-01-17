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

#ifndef LIBWETHAIR_APP_PARTICLE_SIMULATION_H_
#define LIBWETHAIR_APP_PARTICLE_SIMULATION_H_

#include "ExecutableSimulation.h"
#include "SceneStepper.h"
#include "TwoDScene.h"
#include "TwoDSceneRenderer.h"
#include "TwoDSceneSerializer.h"
#include "TwoDimensionalDisplayController.h"
#include "WetHairCore.h"

extern bool g_bPrintSummary;
extern bool g_rendering_enabled;

// TODO: Move code out of header!
template <int DIM>
class ParticleSimulation : public ExecutableSimulation {
 public:
  ParticleSimulation(TwoDScene<DIM>* scene, SceneStepper<DIM>* scene_stepper,
                     TwoDSceneRenderer<DIM>* scene_renderer,
                     const std::vector<Script>& scripts);
  ~ParticleSimulation();

  virtual void stepSystem();
  /////////////////////////////////////////////////////////////////////////////
  // Rendering Functions

  virtual void initializeOpenGLRenderer();
  virtual void renderSceneOpenGL();
  virtual void renderSceneDifferencesOpenGL();
  virtual void updateOpenGLRendererState();
  virtual void computeCameraCenter(renderingutils::Viewport& view);
  /////////////////////////////////////////////////////////////////////////////
  // Serialization Functions

  virtual void serializeScene(std::ostream& outputstream);
  virtual void serializeSceneReadable(std::vector<std::ostringstream>& osfluid,
                                      std::ostream& oshair,
                                      std::ostream& osflow,
                                      std::ostream& os_boundary_single,
                                      std::ostream& os_boundary_double,
                                      std::ostream& os_pe, std::ostream& os_poe,
                                      std::ostream& os_ppp);
  virtual bool deSerializeSceneReadable(
      const std::vector<std::string>& filename_fluids,
      const std::string& filename_hairs, const std::string& filename_flows,
      const std::string& filename_bd_single,
      const std::string& filename_bd_double);
  virtual void loadSerializedScene(std::istream& inputstream);
  /////////////////////////////////////////////////////////////////////////////
  // Status Functions

  virtual void centerCamera(bool b_reshape = true);
  virtual void keyboard(unsigned char key, int x, int y);
  virtual void reshape(int w, int h);

  virtual void special(int key, int x, int y);

  virtual void mouse(int button, int state, int x, int y);

  virtual void translateView(double dx, double dy);

  virtual void zoomView(double dx, double dy);

  virtual void motion(int x, int y);

  virtual int getWindowWidth() const;
  virtual int getWindowHeight() const;

  virtual void setWindowWidth(int w);
  virtual void setWindowHeight(int h);

  virtual const scalar& getDt() const;
  virtual const scalar& getCurrentTime() const;
  virtual scalar getCurrentFrame() const;

  virtual TwoDimensionalDisplayController<DIM>* getDC();

  virtual void setCenterX(double x);
  virtual void setCenterY(double y);
  virtual void setCenterZ(double z);
  virtual void setScaleFactor(double scale);

  virtual void setCamera(const Camera& cam);
  virtual void setView(const renderingutils::Viewport& view);

  virtual bool stepScript(const scalar& dt);

  virtual std::string getSolverName();

  virtual const std::vector<scalar>& getTimingStatistics() const;
  virtual const std::vector<scalar>& getStepperTimingStatistics() const;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
 private:
  WetHairCore<DIM>* m_wet_hair_core;

  TwoDScene<DIM>* m_scene;

  SceneStepper<DIM>* m_scene_stepper;

  TwoDSceneRenderer<DIM>* m_scene_renderer;

  TwoDimensionalDisplayController<DIM> m_display_controller;

  TwoDSceneSerializer<DIM> m_scene_serializer;

  std::vector<Script> m_scripts;
};

#endif  // LIBWETHAIR_APP_PARTICLE_SIMULATION_H_
