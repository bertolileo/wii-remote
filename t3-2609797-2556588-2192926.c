/*============================================================================*/
/* TRABALHO: WII SENSOR BAR                                                   */
/*----------------------------------------------------------------------------*/
/* Autor: Leonardo B. Sepulvida - 2609797                                     */
/* Autor: Lucas A. Moreira - 2556588                                          */
/*============================================================================*/
/** Esse arquivo contém as funções que são responsáveis por filtrar e rotular
 ** as imagens geredas. Além de calcular o ângulo entre os dois agrupamentos,
 ** em radianos, no intervalo (-pi/2, +pi/2).**/
/*===========================================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "trabalho3.h"
#include "imagem.h"

#define ARQUIVO "teste%d.bmp"

/*===========================================================================================================================*/

void filtraImagem (Imagem1C** img);
void maioresRotulos(int* rot1, int* rot2, Imagem1C** img);
double calculaAngulo (Coordenada* l, Coordenada* r);

/*===========================================================================================================================*/
/*função principal que chama as demais funções além de rotular e calcular o angulo que deve ser retornado.*/
double detectaSensorBar (Imagem1C* img, Coordenada* l, Coordenada* r) {
    filtraImagem(&img);
    int i, j, rotulo = 1, flag = 1;

    /* primeiro loop definindo rotulos de maneira comum */
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            if (img->dados[i][j] == 255) {
                /* Lado esquerdo */
                if (j > 0 && img->dados[i][j - 1] != 0 && img->dados[i][j - 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i][j - 1];
                    flag = 0;
                }
                /* Lado esquerdo em cima */
                if (i > 0 && j > 0 && img->dados[i - 1][j - 1] != 0 && img->dados[i - 1][j - 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i - 1][j - 1];
                    flag = 0;
                }
                /* lado acima */
                if (i > 0 && img->dados[i - 1][j] != 0 && img->dados[i - 1][j] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i - 1][j];
                    flag = 0;
                }
                /* Lado direita em cima */
                if (i > 0 && j < img->largura - 1 && img->dados[i - 1][j + 1] != 0 && img->dados[i - 1][j + 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i - 1][j + 1];
                    flag = 0;
                }
                /* Nenhum dos lados é verdadeiro, novo rótulo é criado */
                if (flag) {
                    img->dados[i][j] = rotulo;
                    rotulo++;
                }
            }
            flag = 1;
        }
    }
    /* loop invertido para corrigir possiveis erros dentro do rotulo criando anteriormente */
    for (i = img->altura - 1; i >= 0; i--) {
        for (j = img->largura - 1; j >= 0; j--) {
            if (img->dados[i][j] != 0) {
                /* Lado direito */
                if (j < img->largura - 1 && img->dados[i][j + 1] != 0 && img->dados[i][j + 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i][j + 1];
                }

                /* Lado direito abaixo */
                if (i < img->altura - 1 && j < img->largura - 1 && img->dados[i + 1][j + 1] != 0 && img->dados[i + 1][j + 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i + 1][j + 1];
                }

                /* Lado abaixo */
                if (i < img->altura - 1 && img->dados[i + 1][j] != 0 && img->dados[i + 1][j] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i + 1][j];
                }

                /* Lado esquerda abaixo */
                if (i < img->altura - 1 && j > 0 && img->dados[i + 1][j - 1] != 0 && img->dados[i + 1][j - 1] < img->dados[i][j]) {
                    img->dados[i][j] = img->dados[i + 1][j - 1];
                }

            }
        }
    }

    int rotulo_circulo1, rotulo_circulo2;
    maioresRotulos(&rotulo_circulo1, &rotulo_circulo2, &img);



    int tam_circulo1 = 0, tam_circulo2 = 0,
        circulo1x = 0, circulo1y = 0,
        circulo2x = 0, circulo2y = 0;


    //percorre a matriz e quando um rotulo pertencente a um circulo é encontrado
    //acumula as cordenadas em uma variavel conta o "tamanho" do circulo.
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            if(img->dados[i][j] == rotulo_circulo1) {
                circulo1x += j;
                circulo1y += i;
                tam_circulo1++;
            }
            if(img->dados[i][j] == rotulo_circulo2) {
                circulo2x += j;
                circulo2y += i;
                tam_circulo2++;
            }
        }
    }
    double deltax, deltay;
    //calcula uma media das cordenadas dos circulos

    l->x = circulo1x / tam_circulo1;
    l->y = circulo1y / tam_circulo1;
    r->x = circulo2x / tam_circulo2;
    r->y = circulo2y / tam_circulo2;

    deltax = l->x - r->x;
    deltay = l->y - r->y;
    if (l->x > r->x) {
        Coordenada temp = *l;
        *l = *r;
        *r = temp;
    }

    double angulo = atan2(deltay, deltax);

    return angulo;
}

/*===========================================================================================================================*/

/*função que tem como objetivo deixar a imagem mais legível e de uma maneira mais facil de trabalhar
 *elimando boa parte de seus ruídos e interferências externas*/
void filtraImagem(Imagem1C** img) {
    int i, j;
    /*
     *filtra a imagem de acordo com um valor médio encontrado nas demais geradas
     *tornando ela binaria apenas com valores brancos e pretos (0 e 255). */
    for (i = 0; i < (*img)->altura; i++) {
        for (j = 0; j < (*img)->largura; j++) {
            if ((*img)->dados[i][j] > 120) {
                (*img)->dados[i][j] = 255;
            } else {
                (*img)->dados[i][j] = 0;
            }
        }
    }

    /* for para eliminar pixeis brancos sozinhos espalhados na imagem. */
    for (i = 1; i < (*img)->altura - 1; i++) {
        for (j = 1; j < (*img)->largura - 1; j++) {
            if ((*img)->dados[i][j] == 255 && (*img)->dados[i + 1][j] != 255 && (*img)->dados[i - 1][j] != 255 && (*img)->dados[i][j + 1] != 255 && (*img)->dados[i][j - 1] != 255) {
                (*img)->dados[i][j] = 0;
            }
        }
    }
}

/*===========================================================================================================================*/
/* Função que itera sobre a matriz e guarda os dois valores do rotulo que mais tiveram
 * ocorrencias que supostamente representam os rotulos dos dois circulos buscados pela
 * função principal */

void maioresRotulos(int* rot1, int* rot2, Imagem1C** img) {

    int i, j,
        primeiro_maior = 1,
        segundo_maior = 1;

    /* vetor para armazenar a quantidade de ocorrencias de cada numero */
    int* cont = malloc(sizeof(int) * ((*img)->altura * (*img)->largura));

    for (i = 0; i < (*img)->altura * (*img)->largura; i++) {
        cont[i] = 0;
    }

    for (i = 0; i < (*img)->altura; i++) {
        for (j = 0; j < (*img)->largura; j++) {
            if ((*img)->dados[i][j] != 0) {
                cont[(*img)->dados[i][j]]++;
            }
        }
    }

    /* for para fazer a substituição dos maiores */
    for (i = 1; i < (*img)->altura * (*img)->largura; i++) {
        if (cont[i] > cont[primeiro_maior]) {
            segundo_maior = primeiro_maior;
            primeiro_maior = i;
        } else if (cont[i] > cont[segundo_maior] && i != primeiro_maior) {
            segundo_maior = i;
        }
    }

    *rot1 = primeiro_maior;
    *rot2 = segundo_maior;

    /* Liberar a memória alocada dinamicamente */
    free(cont);
}
/*===========================================================================================================================*/

