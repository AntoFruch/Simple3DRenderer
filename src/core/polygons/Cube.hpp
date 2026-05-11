//
// Created by Antonin Fruchet on 10/05/2026.
//

#ifndef INC_3DRENDERER_CUBE_H
#define INC_3DRENDERER_CUBE_H
#include "Object3D.hpp"
#include "SFML/Graphics.hpp"

class Cube : public Object3D {
public:

  Cube(
    const sf::Vector3f& pos,
    const sf::Vector3f& angle,
    const sf::Vector3f& scale
    );
  ~Cube() override = default;

  void update(const sf::Time elapsedTime) override;

protected:
  void construct_vertices() override;
  void construct_edges() override;
};



#endif //INC_3DRENDERER_CUBE_H
