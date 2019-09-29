//
// Created by hatim tachi on 29/09/2019.
//

#ifndef ALGOGENE_STRUCTURE_H
#define ALGOGENE_STRUCTURE_H


#define NBLIGNES 2589
#define NBCOLONNES 7

#define LOW_VALUE 0.2
#define HEIGHT_VALUE 1.8
#define NB_POPULATION 128
#define RANDLINE 4
#define POP_BEST (NB_POPULATION * 0.1) // 10%

#define NB_EPOCH 20


static float** data_vec;

struct population_struct{

    float *vector;
    float gain;

};

typedef struct population_struct pop_struct;


#endif //ALGOGENE_STRUCTURE_H
