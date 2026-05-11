//
// Created by Antonin Fruchet on 10/05/2026.
//

#ifndef INC_3DRENDERER_OBJECT3D_H
#define INC_3DRENDERER_OBJECT3D_H

#include <SFML/Graphics.hpp>

class Object3D {
public:
  sf::Vector3f pos;
  sf::Vector3f angle;
  sf::Vector3f scale;

  Object3D(
    const sf::Vector3f& pos,
    const sf::Vector3f& angle,
    const sf::Vector3f& scale
    );
  virtual ~Object3D() = default;

  void virtual update(sf::Time elapsedTime);
  void draw(sf::RenderWindow &window) const;

  void move(const sf::Vector3f& vector);
  void rotate(const sf::Vector3f& angles);
  void rescale(const sf::Vector3f& scaleFactor);

protected:
  sf::Color color;

  std::vector<sf::Vector3f> mVertices; // list of 3D points that are vertices of the object
  std::vector<sf::Vector2i> mEdges; // (1, 2) -> edge between mVertices[1] and mVertices[2]

  void virtual construct_vertices() = 0;
  void virtual construct_edges() = 0;
};



#endif //INC_3DRENDERER_OBJECT3D_H
