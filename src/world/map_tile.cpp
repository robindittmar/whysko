#include "map_tile.h"

MapTile::MapTile(sf::FloatRect wrldRect, sf::FloatRect texRect, bool hasCollision, sf::FloatRect colRect)
    : worldRect(wrldRect), textureRect(texRect), collision(hasCollision), collisionRect(colRect) {}

void MapTile::writeVertexQuad(sf::Vertex* buffer) const {
    buffer[0].position = sf::Vector2f(worldRect.left, worldRect.top);
    buffer[1].position = sf::Vector2f(worldRect.width, worldRect.top);
    buffer[2].position = sf::Vector2f(worldRect.width, worldRect.height);
    buffer[3].position = sf::Vector2f(worldRect.left, worldRect.height);

    buffer[0].texCoords = sf::Vector2f((float)textureRect.left, (float)textureRect.top);
    buffer[1].texCoords = sf::Vector2f((float)textureRect.width, (float)textureRect.top);
    buffer[2].texCoords = sf::Vector2f((float)textureRect.width, (float)textureRect.height);
    buffer[3].texCoords = sf::Vector2f((float)textureRect.left, (float)textureRect.height);
}

void MapTile::writeDebugVertexQuad(sf::Vertex* buffer) const {
    buffer[0].position = sf::Vector2f(collisionRect.left, collisionRect.top);
    buffer[1].position = sf::Vector2f(collisionRect.left + collisionRect.width, collisionRect.top);
    buffer[2].position = sf::Vector2f(collisionRect.left + collisionRect.width, collisionRect.top + collisionRect.height);
    buffer[3].position = sf::Vector2f(collisionRect.left, collisionRect.top + collisionRect.height);

    buffer[0].color = sf::Color(200, 0, 0, 100);
    buffer[1].color = sf::Color(200, 0, 0, 100);
    buffer[2].color = sf::Color(200, 0, 0, 100);
    buffer[3].color = sf::Color(200, 0, 0, 100);
}
