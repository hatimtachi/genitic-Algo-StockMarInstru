//
// Created by hatim tachi on 29/09/2019.
//

#include <time.h>
#include "DataFunctions.h"
#include "Structure.h"

float RandomValue(float Min, float Max)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = Max - Min;
    float r = random * diff;
    return Min + r;
}

/****************************************************************************/

void Init_Population(pop_struct *tab_population)
{
    int Nb_pop, Nb_col;
    for (Nb_pop = 0; Nb_pop < NB_POPULATION; ++Nb_pop)
    {
        for (Nb_col = 0; Nb_col < NBCOLONNES; ++Nb_col)
        {
            tab_population[Nb_pop].vector[Nb_col] = RandomValue(LOW_VALUE, HEIGHT_VALUE);
        }
    }
}

/****************************************************************************/

void Affiche_struct(pop_struct *tab_population)
{
    int Nb_pop, Nb_col;
    printf("_____________________\n");
    for (Nb_pop = 0; Nb_pop < NB_POPULATION; ++Nb_pop)
    {
        for (Nb_col = 0; Nb_col < NBCOLONNES; ++Nb_col)
        {
            printf("%f ",tab_population[Nb_pop].vector[Nb_col]);
        }
        printf(" : %f ",tab_population[Nb_pop].gain);
        printf("\n");
    }
}

/****************************************************************************/

int compare(const void *s1, const void *s2)
{
    pop_struct *e1 = (pop_struct *)s1;
    pop_struct *e2 = (pop_struct *)s2;
    return (int) (e2->gain - e1->gain);
}

/****************************************************************************/

void Population_Evaluation(pop_struct *tab_population)
{
    int Nb_pop, Nb_col, Nb_lin;
    for (Nb_pop = 0; Nb_pop < NB_POPULATION; ++Nb_pop)
    {
        for (Nb_lin = 0; Nb_lin < NBLIGNES; ++Nb_lin)
        {
            float tmp_sum = 0;
            for (Nb_col = 0; Nb_col < NBCOLONNES; ++Nb_col)
            {
                tmp_sum += tab_population[Nb_pop].vector[Nb_col] * data_vec[Nb_lin][Nb_col];
            }
            tab_population[Nb_pop].gain += tmp_sum;
        }
    }

    qsort(tab_population, NB_POPULATION, sizeof(pop_struct), compare);

}

/****************************************************************************/

void init_gain_poplation(pop_struct *tab_population)
{

    int Nb_pop, Nb_col;
    for (Nb_pop = 0; Nb_pop < NB_POPULATION; ++Nb_pop)
    {
        for (Nb_col = 0; Nb_col < NBCOLONNES; ++Nb_col)
        {
            tab_population[Nb_pop].gain = 0;
        }
    }
}

/****************************************************************************/

void swap(float *a, float *b)
{
    float t;

    t  = *b;
    *b = *a;
    *a = t;
}

/****************************************************************************/

void Croisement(pop_struct *tab_population)
{
    int Nb_pop, Nb_col;
    for (Nb_pop = (int) POP_BEST; Nb_pop < NB_POPULATION; Nb_pop += 2)
    {
        for (Nb_col = 0; Nb_col < NBCOLONNES; ++Nb_col)
        {
            /* permute les cases impaires entre deux membres de la population */
            if((Nb_col % 2) == 1)
            {
                swap(&tab_population[Nb_pop].vector[Nb_col], &tab_population[Nb_pop + 1].vector[Nb_col]);
            }
        }
    }
}

/****************************************************************************/

void Mutation(pop_struct *tab_population)
{
    int Nb_pop;
    for (Nb_pop = (int) POP_BEST; Nb_pop < NB_POPULATION; Nb_pop += 2)
    {
        if(RandomValue(0, 100) == RANDLINE)
        {
            int position_pop = (int) RandomValue(0, NB_POPULATION - 1);
            int position_col = (int) RandomValue(0,NBCOLONNES - 1);
            float mutation_value = RandomValue(LOW_VALUE, HEIGHT_VALUE);
            tab_population[position_pop].vector[position_col] = mutation_value;
        }
    }
}

/****************************************************************************/

int main(int argc, const char * argv[]) {

    srand((unsigned int)time(NULL));

    /**
     * Allocation Data Vector
     */
    data_vec = malloc(NBLIGNES  * sizeof(float *));

    if (data_vec != NULL)
    {
        // malloc du la map de neurone
        for(int i = 0;i <NBLIGNES; i++)
        {
            data_vec[i] = (float *) malloc(NBCOLONNES * (sizeof(float)));
        }
    }

    /**
     * Allocation population vector
     */

    pop_struct* tab_population = malloc(NB_POPULATION * sizeof(typeof(pop_struct)));

    if (tab_population != NULL)
    {
        for(int i = 0;i <NB_POPULATION; i++)
        {
            tab_population[i].vector = (float *) malloc(NBCOLONNES * (sizeof(float)));
            tab_population[i].gain = 0.0;

        }
    }


    /**
     * get Data from file and catch them in vector
     */

    Catch_Data(data_vec);
    show_data_set(NBLIGNES, NBCOLONNES, data_vec);

    /**
     * init Frist population
     */

    Init_Population(tab_population);
    Population_Evaluation(tab_population);

    Affiche_struct(tab_population);

    int i = 0;
    while (i < NB_EPOCH){
        printf(" -Epoch : %d \n",i);
        Croisement(tab_population);
        Mutation(tab_population);
        init_gain_poplation(tab_population);
        Population_Evaluation(tab_population);
        i++;
    }

    Affiche_struct(tab_population);
    return 0;
}
