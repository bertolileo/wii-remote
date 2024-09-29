
# WII REMOTE READER

## Tecnologias Utilizadas:
- C/C++
- Git/Github


## Descrição geral
Lançado no final de 2006, o Nintendo Wii foi um console de videogame que concorreu com o Playstation 3
(da Sony) e o Xbox 360 (da Microsoft) na chamada “7a

geração dos videogames”. Mesmo tendo poder
computacional inferior aos seus concorrentes, o Wii vendeu mais unidades: mais de 100 milhões de
consoles no total, sendo um dos videogames mais vendidos da história.
O sucesso do Wii se deveu, em grande parte, ao seu esquema de controle, radicalmente diferente daquilo
que se encontrava em produtos anteriores e contemporâneos. O controle, apelidado de Wiimote (ver Fig. 1),
traz dentro de si uma série de sensores de movimento e inclinação (acelerômetros e giroscópios), que
permitem que os jogos sejam controlados por movimentos do próprio controle, e não apenas pelos
tradicionais botões e alavancas. Aliado a jogos simples e acessíveis, os controles de movimento do Wii
criaram um apelo junto a um público “casual”, que normalmente não consumia jogos eletrônicos.

## Desafio do trabalho
Suponha que o ano é 2004, e a sua equipe trabalha no centro de pesquisas da Nintendo, no “Project
Revolution” - que viria a se tornar o Wii. Vocês estão trabalhando no desenvolvimento do algoritmo para
detectar o sensor bar. A sua equipe deve criar uma função com o seguinte protótipo:
double detectaSensorBar (Imagem1C* img, Coordenada* l, Coordenada* r);

Wiimote

Sensor Bar

Esta função recebe como parâmetro de entrada um ponteiro para uma imagem do tipo Imagem1C. Esta
imagem é semelhante àquela mostrada na Fig. 3: escura e com 2 regiões mais claras. O objetivo da função
é processar a imagem e localizar os centros dos dois agrupamentos de LEDs. Considere que a imagem de
entrada pode ser modificada pela função (i.e. o conteúdo da imagem pode ser destruído).
Neste ponto do projeto, o sensor que será colocado no Wiimote ainda não foi escolhido, portanto a sua
função deve ser capaz de trabalhar com imagens de resolução arbitrária (no Wii real, a resolução é de
128x96 pixels). Note também que a imagem não é simplesmente “preta com círculos brancos”. O ambiente
pode criar reflexos, podem existir outras fontes de luz infravermelha, e a necessidade de manter o custo do
sensor baixo implica na presença de ruído. Além disso, a luz dos LEDs cria um efeito “borrado” ao seu redor.
Além da imagem de entrada, a função recebe 2 parâmetros de saída, l e r. Eles são ponteiros para
variáveis do tipo Coordenada, uma struct declarada no arquivo trabalho3.h. Estes parâmetros devem ser
preenchidos com as coordenadas dos centros dos agrupamentos esquerdo (l) e direito (r). Ao final, a
função deve retornar o ângulo entre os dois agrupamentos, em radianos, no intervalo (-π/2, +π/2).