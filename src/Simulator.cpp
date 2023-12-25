//
// Created by 22584 on 2023/12/21.
//

#include <random>
#include "Simulator.h"
#include "Shape.h"

void Simulator::update() {
    // Make a new grid
    std::vector<std::vector<Particle>> newGrid(GRID_HEIGHT_CELLS, std::vector<Particle>(GRID_WIDTH_CELLS, {EMPTY}));

    // Iterate through each cell
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
        for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
            if (grid[i][j].type == EMPTY) {
            } else if (grid[i][j].type == WALL) {
                newGrid[i][j].type = WALL;
            } else if (grid[i][j].type == SAND) {
                if (inside(i + 1, j) && grid[i + 1][j].type == EMPTY) { // Check bottom
                    newGrid[i + 1][j].type = SAND;
                    newGrid[i][j].type = EMPTY;
                } else if (inside(i + 1, j - 1) && grid[i + 1][j - 1].type == EMPTY) { // Check bottom left
                    newGrid[i + 1][j - 1].type = SAND;
                    newGrid[i][j].type = EMPTY;
                } else if (inside(i + 1, j + 1) && grid[i + 1][j + 1].type == EMPTY) { // Check bottom right
                    newGrid[i + 1][j + 1].type = SAND;
                    newGrid[i][j].type = EMPTY;
                } else {
                    newGrid[i][j].type = SAND;
                }
            }
        }
    }

    // Swap
    grid = newGrid;
}

void Simulator::initialize() {
    grid.resize(GRID_HEIGHT_CELLS, std::vector<Particle>(GRID_WIDTH_CELLS, {EMPTY}));
    for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
        grid[0][j].type = WALL;
        grid[GRID_HEIGHT_CELLS - 1][j].type = WALL;
    }
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
        grid[i][0].type = WALL;
        grid[i][GRID_WIDTH_CELLS - 1].type = WALL;
    }
}

void Simulator::render(const Shader &shader, unsigned int vao, unsigned int vbo) const {
//    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
//        for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
//            switch (grid[i][j].type) {
//                case EMPTY:
//                    shader.setColor(0, 0, 0, 255);
//                    break;
//                case WALL:
//                    shader.setColor(255, 255, 255, 255);
//                    break;
//                case SAND:
//                    shader.setColor(242, 210, 169, 255);
//                    break;
//                default:
//                    break;
//            }
//            Rect newRect = Rect((float) j * CELL_WIDTH, (float) i * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);
//            newRect.draw(vao, vbo);
//        }
//    }
    glm::vec2 offsets[GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS];
    glm::vec4 colors[GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS];
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
        for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
            offsets[i * GRID_WIDTH_CELLS + j] = glm::vec2((float) j * CELL_WIDTH, (float) i * CELL_HEIGHT);
            switch (grid[i][j].type) {
                case EMPTY:
                    colors[i * GRID_WIDTH_CELLS + j] = glm::vec4(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);
                    break;
                case WALL:
                    colors[i * GRID_WIDTH_CELLS + j] = glm::vec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f,
                                                                 1.0f);
                    break;
                case SAND:
                    colors[i * GRID_WIDTH_CELLS + j] = glm::vec4(242.0f / 255.0f, 210.0f / 255.0f, 169.0f / 255.0f,
                                                                 1.0f);
                    break;
                default:
                    break;
            }
        }
    }
    Rect::drawSimilarRects(shader, CELL_WIDTH, CELL_HEIGHT, offsets, colors, GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS, vao,
                           vbo);
}

void Simulator::renderSetup() {
    float vertices[] = {
            0.0f, 0.0f,
            CELL_WIDTH, 0.0f,
            0.0f, CELL_HEIGHT,
            CELL_WIDTH, CELL_HEIGHT
    };

    float offsets[GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS * 2];
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
        for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
            offsets[(i * GRID_WIDTH_CELLS + j) * 2] = (float) j * CELL_WIDTH;
            offsets[(i * GRID_WIDTH_CELLS + j) * 2 + 1] = (float) i * CELL_HEIGHT;
        }
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &verticesVbo);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &offsetVbo);
    glGenBuffers(1, &colorVbo);

    glBindBuffer(GL_ARRAY_BUFFER, offsetVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(offsets), offsets, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);  // Set divisor to 1 to indicate per-instance data

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);  // Set divisor to 1 to indicate per-instance data

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Simulator::genParticleInCircle(int mouseI, int mouseJ) {
    const int circleRadius = 5;
    for (int i = -circleRadius; i <= circleRadius; i++) {
        for (int j = -circleRadius; j <= circleRadius; j++) {
            if (i * i + j * j <= circleRadius * circleRadius) {
                int newI = mouseI + i;
                int newJ = mouseJ + j;

                if (inside(newI, newJ) && grid[newI][newJ].type != WALL) {
                    grid[newI][newJ] = {selectedParticleType};
                }
            }
        }
    }
}

void Simulator::renderWithInstances(const Shader &shader) {
    shader.Activate();
    float colors[GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS * 4];
    for (int i = 0; i < GRID_HEIGHT_CELLS; i++) {
        for (int j = 0; j < GRID_WIDTH_CELLS; j++) {
            switch (grid[i][j].type) {
                case EMPTY:
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 0] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 1] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 2] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 3] = 1.0f;
                    break;
                case WALL:
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 0] = 1.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 1] = 1.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 2] = 1.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 3] = 1.0f;
                    break;
                case SAND:
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 0] = 242.0f / 255.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 1] = 210.0f / 255.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 2] = 196.0f / 255.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 3] = 1.0f;
                    break;
                case WATER:
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 0] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 1] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 2] = 1.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 3] = 1.0f;
                    break;
                default:
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 0] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 1] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 2] = 0.0f;
                    colors[(i * GRID_WIDTH_CELLS + j) * 4 + 3] = 1.0f;
                    break;
            }
        }
    }
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, GRID_WIDTH_CELLS * GRID_HEIGHT_CELLS);
    glBindVertexArray(0);
}

void Simulator::cleanUpBuffers() {
    glDeleteBuffers(1, &verticesVbo);
    glDeleteBuffers(1, &colorVbo);
    glDeleteBuffers(1, &offsetVbo);
    glDeleteVertexArrays(1, &vao);
}
