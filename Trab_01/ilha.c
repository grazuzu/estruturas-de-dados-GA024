#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


#define FILE_NAME "data.txt"

float **allocate_matrix(int ilin, int icols)
{
    int i;
    float **matrix;
    matrix = (float **)malloc(ilin * sizeof(float *));
    /*if (*matrix == NULL)*/
    if (matrix == NULL){   
        printf("ERROR: Not able to allocate the matrix\n");
        return NULL;
    }

    for (i = 0; i < ilin; i++){
        matrix[i] = (float *)malloc(icols * sizeof(float));
        /*if (*matrix == NULL)*/
        if (matrix[i] == NULL){
            printf("ERROR: Not able to allocate the matrix\n");
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(int ilin, int **matrix)
{
    int i;
    for (i = 0; i < ilin; i++)
        free(matrix[i]);
    free(matrix);
}

void print_matrix(int ilin, int icol, int **matrix)
{
    int i, j;
    for (i = 0; i < ilin; i++)
    {
        for (j = 0; j < icol; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix_float(int ilin, int icol, float **matrix)
{
    int i, j;
    for (i = 0; i < ilin; i++)
    {
        for (j = 0; j < icol; j++)
        {
            printf("%7.3f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void init_poluent_concentration(float **matrix_destino, int **matrix_origem, int ilin, int icols)
{
    int i, j;
    for (i = 0; i < ilin; i++)
    {
        for (j = 0; j < icols; j++)
        {
            if (matrix_origem[i][j] == 2)
            {
                matrix_destino[i][j] = 100;
            }
            else
            {
                matrix_destino[i][j] = 0.0;
            }
        }
    }
}

float calc_mean_concentration(float **matrix, int i, int j, int ilin, int icols)
{
    float m1 = 0.0, m2 = 0.0, m3 = 0.0, m4 = 0.0;
    float media = 0.0;

    media = (m1 + m2 + m3 + m4)/4.0;

    if(i != (ilin - 1)){
        m1 = matrix[i + 1][j];
    }

    if(i != 0){
        m2 = matrix[i - 1][j];
    }

    if(j != (icols - 1)){
        m3 = matrix[i][j + 1];
    }

    if(j != 0){
        m4 = matrix[i][j - 1];
    }

    media = (m1 + m2 + m3 + m4)/4.0;

    return media;
}

float **calc_disel_polution(int **matrix, int ilin, int icols, float tolerance)
{
    int i, j;
    float **m_base, **m_aux, **m_calc;
    float max_diff = 25, new_diff, E;

    m_base = allocate_matrix(ilin, icols);
    init_poluent_concentration(m_base, matrix, ilin, icols);
    m_calc = allocate_matrix(ilin, icols);
    init_poluent_concentration(m_calc, matrix, ilin, icols);

    if (!m_base || !m_calc){
        return 0;
    }

    while (max_diff > tolerance)
    {
        m_aux = m_base;
        m_base = m_calc;
        m_calc = m_aux;

        max_diff = 0;
        for (i = 0; i < ilin; i++)
        {
            for (j = 0; j < icols; j++)
            {
                if (matrix[i][j] && matrix[i][j] != 2)
                {
                    E = calc_mean_concentration(m_base, i, j, ilin, icols);
                    m_calc[i][j] = E;
                    new_diff = m_calc[i][j] - m_base[i][j];
                    if (new_diff > max_diff)
                    {
                        max_diff = new_diff;
                    }
                }
            }
        }
        printf("\n max_diff: %f\n", max_diff);
        print_matrix_float(ilin, icols, m_calc);
        sleep(1);
    }
    
    return m_calc;
}

int main()
{
    int i, j, ilin, icols;
    int **matrix;
    float **m_final;
    float tolerance = 0.1;/*error*/

    /*Leitura do arquivo*/
    FILE *file_pointer;
    file_pointer = fopen(FILE_NAME, "r");

    if (file_pointer == NULL){
        printf("ERROR: Not able to open/file doesn't exist\n");
        exit(1);
    }
    
    fscanf(file_pointer, "%d", &ilin);
    fscanf(file_pointer, "%d", &icols);
    printf("ilin: %d icols: %d \n", ilin, icols);
    matrix = (int **) malloc(ilin * sizeof(int *));
    for (i = 0; i < ilin; i++){
        matrix[i] = (int *) malloc(icols * sizeof(int));
        for (j = 0; j < icols; j++){
            fscanf(file_pointer, "%d", &matrix[i][j]);
        }
    }

    fclose(file_pointer);

    printf("Ilha inicial\n");
    print_matrix(ilin, icols, matrix);

    m_final = calc_disel_polution(matrix, ilin, icols, tolerance);

    free(m_final);

    return 0;
}