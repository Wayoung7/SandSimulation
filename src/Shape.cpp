//
// Created by 22584 on 2023/12/21.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shape.h"

void Rect::draw(unsigned int vao, unsigned int vbo) const {
    float vertices[] = {
            getPos().x, getPos().y,
            getPos().x + width, getPos().y,
            getPos().x, getPos().y + height,
            getPos().x + width, getPos().y,
            getPos().x, getPos().y + height,
            getPos().x + width, getPos().y + height
    };
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Rect::drawSimilarRects(const Shader &shader, float _width, float _height, glm::vec2 *offsets, glm::vec4 *colors,
                            int numRects, unsigned int vao,
                            unsigned int vbo) {
    shader.Activate();
    float data[numRects * 6];
    for (int i = 0; i < numRects; i++) {
        data[i * 6 + 0] = offsets[i].x;
        data[i * 6 + 1] = offsets[i].y;
        data[i * 6 + 2] = colors[i].r;
        data[i * 6 + 3] = colors[i].g;
        data[i * 6 + 4] = colors[i].b;
        data[i * 6 + 5] = colors[i].a;
    }
//    for (unsigned int i = 0; i < numRects; i++) {
//        shader.setVec2(("offsets[" + std::to_string(i) + "]"), offsets[i]);
//        shader.setVec4(("colors[" + std::to_string(i) + "]"), colors[i]);
//    }
    float vertices[] = {
            0.0f, 0.0f,
            _width, 0.0f,
            0.0f, _height,
            _width, 0.0f,
            0.0f, _height,
            _width, _height
    };
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * numRects, &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, numRects);
    glBindVertexArray(0);
}