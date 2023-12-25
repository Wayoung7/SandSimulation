//
// Created by 22584 on 2023/12/21.
//

#ifndef SANDSIMULATION_OPENGL_SIMULATOR_H
#define SANDSIMULATION_OPENGL_SIMULATOR_H

#include <vector>
#include "Particle.h"
#include "Constants.h"
#include "Shader.h"

class Simulator {
public:
    inline Simulator() : selectedParticleType(SAND), vao(0), verticesVbo(0), offsetVbo(0), colorVbo(0) {};

    inline void setSelectedParticleType(ParticleType t) { selectedParticleType = t; }

    inline ParticleType getSelectedParticleType() { return selectedParticleType; }

    void update();

    void render(const Shader &shader, unsigned int vao, unsigned int vbo) const;

    void renderSetup();

    void renderWithInstances(const Shader &shader);

    void initialize();

    void genParticleInCircle(int mouseI, int mouseJ);

    void cleanUpBuffers();

private:
    std::vector<std::vector<Particle>> grid;
    unsigned int vao;
    unsigned int verticesVbo, offsetVbo, colorVbo;
    ParticleType selectedParticleType;

    [[nodiscard]] static inline bool inside(int row, int col) {
        return row >= 0 && col >= 0 && row <= GRID_HEIGHT_CELLS - 1 && col <= GRID_WIDTH_CELLS - 1;
    }
};


#endif //SANDSIMULATION_OPENGL_SIMULATOR_H
