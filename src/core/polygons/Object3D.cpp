//
// Created by Antonin Fruchet on 10/05/2026.
//

#include "Object3D.hpp"

#include "../../../cmake-build-debug/_deps/sfml-src/extlibs/headers/glad/include/glad/gl.h"

Object3D::Object3D(
    const sf::Vector3f& pos,
    const sf::Vector3f& angle,
    const sf::Vector3f& scale
  )
{
  this->pos = pos;
  this->angle = angle;
  this->scale = scale;
  color = sf::Color::Green;
}

void Object3D::update(const sf::Time elapsedTime) {

}

void Object3D::draw(sf::RenderWindow &window) const{
  std::vector<sf::Vertex> points2d;
  points2d.reserve(mVertices.size());

  // projection
  for (int i=0; i<mVertices.size(); i++) {
    points2d.push_back(sf::Vertex(sf::Vector2f{mVertices[i].x / mVertices[i].z, mVertices[i].y / mVertices[i].z}, color));
  }

  // l'affichage dans le repere de la fenetre
  sf::Vector2i w_size{window.getSize()};
  for (int i=0; i<points2d.size(); i++) {
    points2d[i].position.x = (points2d[i].position.x + 1) / 2 * w_size.x;
    points2d[i].position.y = (-points2d[i].position.y + 1) / 2 * w_size.y;
  }

  for (int i = 0; i < mEdges.size(); i++) {
    // On récupère les points 3D d'origine pour vérifier le Z
    const sf::Vector3f& v1 = mVertices[mEdges[i].x];
    const sf::Vector3f& v2 = mVertices[mEdges[i].y];

    // Si l'un des points est derrière ou sur la caméra, on ne dessine pas
    if (v1.z <= 0.1f || v2.z <= 0.1f) continue;

    std::array line {
      points2d[mEdges[i].x],
      points2d[mEdges[i].y]
    };
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
  }

#if 0
  // DEBUG : draw the center point
  sf::Vector2f projectedPos{ pos.x / pos.z, pos.y / pos.z };

  // 2. Conversion vers l'espace écran (même calcul que pour tes points)
  float screenX = (projectedPos.x + 1) / 2 * w_size.x;
  float screenY = (-projectedPos.y + 1) / 2 * w_size.y;

  // 3. Création et dessin du point rouge
  sf::CircleShape centerPoint(4.f); // Rayon de 4 pixels
  centerPoint.setFillColor(sf::Color::Red);
  // On centre le cercle sur la position (on retire le rayon)
  centerPoint.setPosition({screenX - 4.f, screenY - 4.f});

  window.draw(centerPoint);
#endif
}

void Object3D::move(const sf::Vector3f& vector) {
  for (auto& v : mVertices) {
    v += vector;
  }
  this->pos += vector;
}
void Object3D::rotate(const sf::Vector3f& angles) {
  float ax = angles.x * 3.14159265f / 180.f;
  float ay = angles.y * 3.14159265f / 180.f;
  float az = angles.z * 3.14159265f / 180.f;

  // On pré-calcule les sinus et cosinus pour ne pas le faire 8 fois par axe
  float cx = cos(ax), sx = sin(ax);
  float cy = cos(ay), sy = sin(ay);
  float cz = cos(az), sz = sin(az);

  for (auto& v : mVertices) {
    // --- ÉTAPE A : Ramener le sommet au centre local (autour de 0,0,0) ---
    // On soustrait la position du centre (this->pos)
    v.x -= this->pos.x;
    v.y -= this->pos.y;
    v.z -= this->pos.z;

    // --- ÉTAPE B : Appliquer les rotations ---

    // Rotation X
    if (ax != 0) {
      float y = v.y;
      v.y = y * cx - v.z * sx;
      v.z = y * sx + v.z * cx;
    }

    // Rotation Y
    if (ay != 0) {
      float x = v.x;
      v.x = x * cy + v.z * sy;
      v.z = -x * sy + v.z * cy;
    }

    // Rotation Z
    if (az != 0) {
      float x = v.x;
      v.x = x * cz - v.y * sz;
      v.y = x * sz + v.y * cz;
    }

    // --- ÉTAPE C : Replacer le sommet à sa position d'origine ---
    v.x += this->pos.x;
    v.y += this->pos.y;
    v.z += this->pos.z;
  }
  this->angle += angles;
}

void Object3D::rescale(const sf::Vector3f& scaleFactor) {
  for (auto& v : mVertices) {
    v.x -= this->pos.x;
    v.y -= this->pos.y;
    v.z -= this->pos.z;

    v.x *= scaleFactor.x;
    v.y *= scaleFactor.y;
    v.z *= scaleFactor.z;

    v.x += this->pos.x;
    v.y += this->pos.y;
    v.z += this->pos.z;
  }
  this->scale.x *= scaleFactor.x;
  this->scale.y *= scaleFactor.y;
  this->scale.z *= scaleFactor.z;

  this->scale += scaleFactor;
}
