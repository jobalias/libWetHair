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

#ifndef LIBWETHAIR_APP_RENDERING_UTILITIES_H_
#define LIBWETHAIR_APP_RENDERING_UTILITIES_H_

#ifdef WIN32
#include <Windows.h>
#endif
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cstdio>
#include <iostream>
#include <list>

#include "JET.h"
#include "MathDefs.h"
#include "MathUtilities.h"
#include "StringUtilities.h"

namespace renderingutils {
class Color {
 public:
  Color();

  Color(double r, double g, double b);

  Color(const Vector3s&);

  Vector3s toVector() const;

  double r;
  double g;
  double b;
};
}  // namespace renderingutils

extern int getDCWindowWidth();
extern int getDCWindowHeight();
extern renderingutils::Color& getDCBackgroundColor();

namespace renderingutils {
// False => error
bool checkGLErrors();

// TODO: Move these functions to scene renderer?
inline void setOrthographicProjection() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, getDCWindowWidth(), 0, getDCWindowHeight());

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  assert(renderingutils::checkGLErrors());
}

inline void renderBitmapString(float x, float y, float z, void* font,
                               const std::string& s) {
  glRasterPos3f(x, y, z);
  for (auto i = s.begin(); i != s.end(); ++i) {
    char c = *i;
    glutBitmapCharacter(font, c);
  }

  assert(checkGLErrors());
}

inline void drawHUDString(int line, const std::string& s) {
  if (s.empty()) return;
  setOrthographicProjection();
  auto& color = getDCBackgroundColor();
  glColor3f(1.0 - color.r, 1.0 - color.g, 1.0 - color.b);
  renderBitmapString(4, getDCWindowHeight() - 20 * (line + 1), 0.0,
                     GLUT_BITMAP_HELVETICA_18, s);
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  assert(renderingutils::checkGLErrors());
}

inline Vector3s interpolateColor(const scalar& x, const scalar& xmin,
                                 const scalar& xmax) {
  scalar dm = (xmax - xmin);

  scalar a;
  if (dm == 0.0)
    a = x;
  else
    a = (x - xmin) / dm * (scalar)(jetmapping_size - 1);

  int isel = std::max(std::min((int)a, jetmapping_size - 1), 0);
  int inext = (isel + 1) % (jetmapping_size);
  scalar fraca = std::max(std::min(a - (scalar)isel, 1.0), 0.0);

  return mathutils::lerp(jetmapping_real[isel], jetmapping_real[inext], fraca);
}

struct Viewport {
 public:
  Viewport()
      : cx(0.0), cy(0.0), cz(0.0), rx(1.0), ry(1.0), rz(1.0), size(1.2) {}
  double cx;
  double cy;
  double cz;
  double rx;
  double ry;
  double rz;
  double size;
};

}  // namespace renderingutils

#endif  // LIBWETHAIR_APP_RENDERING_UTILITIES_H_
