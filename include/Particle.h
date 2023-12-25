//
// Created by 22584 on 2023/12/21.
//

#ifndef SANDSIMULATION_OPENGL_PARTICLE_H
#define SANDSIMULATION_OPENGL_PARTICLE_H

enum ParticleType {
    EMPTY,
    WALL,
    SAND,
    WATER,
    EnumCount
};

struct Particle {
    ParticleType type;
};

#endif //SANDSIMULATION_OPENGL_PARTICLE_H
