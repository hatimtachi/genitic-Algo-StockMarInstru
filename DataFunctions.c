//
// Created by hatim tachi on 29/09/2019.
//

#include "DataFunctions.h"




void Catch_Data(float **data_vect)
{
    FILE *Data_Base = fopen("data.csv","r+");
    char Data_line[2048];
    int count_col = 0;
    int count_ligne = 0;

    const char s[2] = ";";
    char *token;

    while(fgets(Data_line,2048,Data_Base)){
        token = strtok(Data_line, s);

        while(token != NULL){

            if((count_col >= 1) && (count_ligne >= 1)) {
                data_vect[count_ligne - 1][count_col - 1] = (float) strtod(token, NULL);
            }
            token = strtok(NULL, s);
            count_col++;
        }
        count_col = 0;
        count_ligne++;
    }
    fclose(Data_Base);
}


/****************************************************************************/

void show_data_set(int Nb_Lines, int Nb_col, float **Data)
{
    for (int i = 0; i < Nb_Lines; i++) {
        for (int j = 0; j < Nb_col; j++) {

            printf(" %f ",Data[i][j]);

        }
        printf("\n");
    }
}
