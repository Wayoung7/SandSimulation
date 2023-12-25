//
// Created by 22584 on 2023/12/21.
//

#ifndef SANDSIMULATION_OPENGL_SHAPE_H
#define SANDSIMULATION_OPENGL_SHAPE_H

#include <glm/glm.hpp>
#include "Shader.h"

class Shape {
private:
    glm::vec2 pos;
public:
    virtual void draw(unsigned int vao, unsigned int vbo) const = 0;

    inline Shape() : pos(glm::vec2(0.0f, 0.0f)) {};

    inline Shape(float x, float y) : pos(glm::vec2(x, y)) {};

    virtual ~Shape() = default;

    [[nodiscard]] inline glm::vec2 getPos() const { return pos; }
};

class Rect : public Shape {
private:
    float width;
    float height;
public:
    inline Rect(float w, float h) : width(w), height(h), Shape() {};

    inline Rect(float x, float y, float w, float h) : width(w), height(h), Shape(x, y) {};

    void draw(unsigned int vao, unsigned int vbo) const override;

    static void
    drawSimilarRects(const Shader &shader, float _width, float _height, glm::vec2 offsets[], glm::vec4 colors[],
                     int numRects, unsigned int vao,
                     unsigned int vbo);
};


#endif //SANDSIMULATION_OPENGL_SHAPE_H
