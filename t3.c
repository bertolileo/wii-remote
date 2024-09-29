//Lucas Agenor Moreira, RA; 2556588
//Leonardo
#include "trabalho3.h"
#include "imagem.h"
#define ARQUIVO "teste%d.bmp"
void filtraImagem(Imagem1C** img);
double detectaSensorBar (Imagem1C* img, Coordenada* l, Coordenada* r){
 filtraImagem(&img);

    int i, j, rotulo = 1, flag = 1, ja_encontrei=0, final_da_bolinha=0;
    Coordenada bolinha1, bolinha2;
    int menor_rotulo, maior_rotulo;
    int tamanho_linha_bolinha=0, maior_linha_bolinha=0;
    int numero_linha;
    Coordenada origem;


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


    //processo para encontrar o centro das bolinhas//
    //neste primeiro loop eu vou encontrar a primeira bolinha //
    int j_inicial, centro_bolinha_horizontal;
    for (i = 0; i < img->altura; i++)
    {
        for (j = 0; j < img->largura; j++)
            if(img->dados[i][j] && !ja_encontrei)
            {
            menor_rotulo = img->dados[i][j];
            ja_encontrei = 1;
            }
            else if(menor_rotulo && img->dados[i][j]== menor_rotulo)
            {
            j_inicial=j;
            while(!final_da_bolinha)
            {
                j++;
                tamanho_linha_bolinha++;
                if(tamanho_linha_bolinha> maior_linha_bolinha)
                { maior_linha_bolinha= tamanho_linha_bolinha;
                  numero_linha=i;
                  centro_bolinha_horizontal=(j- j_inicial)/2+j_inicial;
                }
                if(!img->dados[i][j])
                    final_da_bolinha=1;
            }
            tamanho_linha_bolinha=0;
            final_da_bolinha=0;
            }
    }

    bolinha1.x= centro_bolinha_horizontal;
    bolinha1.y= numero_linha;

    ja_encontrei=0;
    final_da_bolinha=0;
    tamanho_linha_bolinha=0;
    maior_linha_bolinha=0;

    //loop para achar o centro da segunda bolinha//
    for (i = 0; i < img->altura; i++)
    {
        for (j = 0; j < img->largura; j++)
            if(img->dados[i][j]>menor_rotulo && !ja_encontrei)
            {
            maior_rotulo = img->dados[i][j];
            ja_encontrei = 1;
            }
            else if(maior_rotulo && img->dados[i][j]== maior_rotulo)
            {
            j_inicial=j;
            while(!final_da_bolinha)
            {
                j++;
                tamanho_linha_bolinha++;
                if(tamanho_linha_bolinha> maior_linha_bolinha)
                { maior_linha_bolinha= tamanho_linha_bolinha;
                  numero_linha=i;
                  centro_bolinha_horizontal=(j- j_inicial)/2+j_inicial;
                }
                if(!img->dados[i][j])
                    final_da_bolinha=1;
            }
            tamanho_linha_bolinha=0;
            final_da_bolinha=0;
            }
    }

    bolinha2.x = centro_bolinha_horizontal;
    bolinha2.y = numero_linha;

    //compara-se as coordenadas horizontais das duas bolinhas//

    if(bolinha1.x > bolinha2.x)
    {
    *r = bolinha1;
    *l = bolinha2;
    }
    else
    {
    *r = bolinha2;
    *l = bolinha1;
    }
 double deltax, deltay;
    deltax = l->x - r->x;
    deltay = l->y - r->y;
    if (deltax < 0) {
        deltax *= -1;
    }
    if (deltay < 0) {
        deltay *= -1;
    }
    double angulo = atan2(deltay, deltax);

    return angulo;
}
void filtraImagem(Imagem1C** img) {
    int i, j;
    /*
     *filtra a imagem de acordo com um valor médio encontrado nas demais geradas
     *tornando ela binaria apenas com valores brancos e pretos (0 e 255). */
    for (i = 0; i < (*img)->altura; i++) {
        for (j = 0; j < (*img)->largura; j++) {
            if ((*img)->dados[i][j] > 105) {
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
