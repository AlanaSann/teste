// #################################################
// TESTE AUTOMÁTIZADO
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do
//  trabalho

//  ----- Dados do Aluno -----
//  Nome: Alana Santos de Oliveira
//  email: alana.sann03@gmail.com
//  Matrícula: 20221160021
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include "AlanaOliveira20221160021.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y) {
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x) { // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a) {
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

DataQuebrada quebraData(char data[]) {
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++) {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sDia[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++) {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2) { // testa se tem 1 ou dois digitos
    sMes[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++) {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4) { // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';       // coloca o barra zero no final
  } else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia,
mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa
podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */

int q1(char data[]) {
  // 1-Se o ano for uniformemente divisível por 4, vá para a etapa 2. Caso
  // contrário, vá para a etapa 5.
  // 2-Se o ano for uniformemente divisível por 100, vá para a etapa 3. Caso
  // contrário, vá para a etapa 4. 3-Se o ano for uniformemente divisível por
  // 400, vá para a etapa 4. Caso contrário, vá para a etapa 5. 4-O ano é
  // bissexto (tem 366 dias). 5-O ano não é um ano bissexto (tem 365 dias)
  // int datavalida = 1;
  int anobissexto = 0;
  DataQuebrada dataQuebrada = quebraData(data);
  if (dataQuebrada.valido == 0)
    return 0;
  if (dataQuebrada.iDia < 1 || dataQuebrada.iDia > 31)
    return 0;
  if (dataQuebrada.iMes < 1 || dataQuebrada.iMes > 12)
    return 0;
  if (dataQuebrada.iAno < 1 || dataQuebrada.iAno > 9999)
    return 0;
  if (dataQuebrada.iMes == 2 && dataQuebrada.iDia > 29)
    return 0;
  if ((dataQuebrada.iAno % 4 == 0 && dataQuebrada.iAno % 100 != 0) ||
      (dataQuebrada.iAno % 400 == 0)) {
    anobissexto = 1;
  }
  if (anobissexto == 0 && (dataQuebrada.iDia > 28 && dataQuebrada.iMes == 2)) {
    return 0;
  }
  return 1;

}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis
 valores abaixo
1 -> cálculo de diferença realizado com sucesso
2 -> datainicial inválida
3 -> datafinal inválida
4 -> datainicial > datafinal
Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem
ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]) {
  int data_Valida, i, difer_ano, difer_mes, difer_dia, ano_bissexto[2] = {0, 0},
                                                       diasdoMes;
  DataQuebrada data_quebrada[2];
  DiasMesesAnos dma;
  
  data_Valida = q1(datainicial);
  if (data_Valida == 0) {
    dma.retorno = 2;
    return dma;
  }
  data_Valida = q1(datafinal);
  if (data_Valida == 0) {
    dma.retorno = 3;
    return dma;
  }
  data_quebrada[0] = quebraData(datainicial);
  data_quebrada[1] = quebraData(datafinal);

  if ((data_quebrada[0].iAno > data_quebrada[1].iAno) ||
      (data_quebrada[0].iAno == data_quebrada[1].iAno &&
       data_quebrada[0].iMes > data_quebrada[1].iMes) ||
      (data_quebrada[0].iMes == data_quebrada[1].iMes &&
       data_quebrada[0].iDia > data_quebrada[1].iDia &&
       data_quebrada[0].iAno == data_quebrada[1].iAno)) {

    dma.retorno = 4;
    return dma;
  }

  difer_ano = data_quebrada[1].iAno - data_quebrada[0].iAno;
  if ((data_quebrada[0].iMes > data_quebrada[1].iMes) ||
      (data_quebrada[0].iMes == data_quebrada[1].iMes &&
       data_quebrada[0].iDia > data_quebrada[1].iDia)) {
    difer_ano = difer_ano - 1;
  }

  // MES
  if (data_quebrada[0].iMes <= data_quebrada[1].iMes) {
    difer_mes = data_quebrada[1].iMes - data_quebrada[0].iMes;
  }
  if (data_quebrada[0].iMes > data_quebrada[1].iMes) {
    difer_mes = (12 - data_quebrada[0].iMes) + data_quebrada[1].iMes;
  }
  if (data_quebrada[0].iDia > data_quebrada[1].iDia) {
    difer_mes = difer_mes - 1;
  }

  // DIA
  for (i = 0; i < 2; i++) {
    if ((data_quebrada[i].iAno % 4 == 0 && data_quebrada[i].iAno % 100 != 0) ||
        (data_quebrada[i].iAno % 400 == 0)) {
      ano_bissexto[i] = 1;
    }
  }

  if (data_quebrada[0].iDia < data_quebrada[1].iDia) {
    difer_dia = data_quebrada[1].iDia - data_quebrada[0].iDia;
  }

  if (data_quebrada[0].iMes == 4 || data_quebrada[0].iMes == 6 ||
      data_quebrada[0].iMes == 9 || data_quebrada[0].iMes == 11) {
    diasdoMes = 30;
  }
  if (data_quebrada[0].iMes == 1 || data_quebrada[0].iMes == 3 ||
      data_quebrada[0].iMes == 5 || data_quebrada[0].iMes == 7 ||
      data_quebrada[0].iMes == 8 || data_quebrada[0].iMes == 10) {
    diasdoMes = 31;
  }
  if (ano_bissexto[0] == 0 && (data_quebrada[0].iMes == 2)) {
    diasdoMes = 28;
  } else {
    if (ano_bissexto[0] == 1 && data_quebrada[0].iMes == 2) {
      diasdoMes = 29;
    }
  }

  if (data_quebrada[0].iDia > data_quebrada[1].iDia) {
    difer_dia = (diasdoMes - data_quebrada[0].iDia) + data_quebrada[1].iDia;
  }

  if (ano_bissexto[0] == 1 && data_quebrada[0].iMes <= 2 &&
      ano_bissexto[1] != 1 ) {
    difer_dia = difer_dia - 1;
  }
  if (ano_bissexto[1] == 1 && data_quebrada[1].iMes > 2 &&
      ano_bissexto[0] != 1 && data_quebrada[0].iMes <= 2) {
    difer_dia = difer_dia + 1;
  }

  dma.qtdAnos = difer_ano;
  dma.qtdMeses = difer_mes;
  dma.qtdDias = difer_dia;

  dma.retorno = 1;
  return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa
 Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar
 diferenças entre maiúsculos e minúsculos. Se isCaseSensitive != 1, a pesquisa
 não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
void removeAcento(char letras[])
{  
  
    int i, j, acento;
    for (i = 0, j = i; letras[i] != '\0'; i++)
    {
        acento = letras[i];
        if (acento != -61)
        {
            letras[j] = letras[i];
            j++;
        }
    }
}
int q3(char *texto, char c, int isCaseSensitive) {
  int numCaracteres = 0, qtdOcorrencias = 0;
  // nao é sensivel
  if (isCaseSensitive == 1) { // diferencia maiusculo e menusculo;
    while (texto[numCaracteres] != '\0') {

      if (texto[numCaracteres] == c) {
        qtdOcorrencias++;
      }
      numCaracteres++;
    }
    return qtdOcorrencias; // expulsa os insensiveis;
  }
  //é sensivel
  if (c >= 'a' && c <= 'z') {
    c = c - 32;
  }

  while (texto[numCaracteres] != '\0') {
    // maiusculo                                   //menusculo
    if (texto[numCaracteres] == c || texto[numCaracteres] == c + 32) {
      qtdOcorrencias++;
    }
    numCaracteres++;
  }
  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de
 inteiros (posicoes) que irá guardar as posições de início e fim de cada
 ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída
 correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do
 vetor deve ser preenchido com o índice de início do texto, e na posição 1,
 deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas
 ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim
 consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de
 busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se
 armazenar no vetor, da seguinte forma: posicoes[0] = 13; posicoes[1] = 16;
 Observe que o índice da posição no texto deve começar ser contado a partir
 de 1. O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char strBusca[], int posicoes[30]) {
  int qtdOcorrencias = 0, letras = 0, i, tamanhodeBusca, contador = 0, qtd = 0;
  removeAcento(strTexto);
  tamanhodeBusca = strlen(strBusca);
  while (strTexto[letras] != '\0') {
    if (strTexto[letras] == strBusca[0]) {
      for (i = 0; i < tamanhodeBusca; i++, letras++) {
        if (strTexto[letras] == strBusca[i]) {
          contador++;
        }
      }
      if (contador == tamanhodeBusca) {
        qtdOcorrencias++;
        posicoes[qtd] = letras - tamanhodeBusca + 1;
        posicoes[qtd + 1] = letras;
        qtd = qtd + 2;
      }
      letras = letras - i + 1;
      contador = 0;
    }
    letras++;
  }
  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
  int inverso = 0, cifra;
  for (; num > 0;) {
    cifra = num % 10;
    inverso = inverso * 10 + cifra;
    num /= 10;
  }
  return inverso;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
  int qtdOcorrencias = 0, unidade, copia = numerobusca, divisor;

  for (divisor = 1; copia > 0;
       divisor = divisor * 10) // identifica quantas unidades tem o numbusca
  {
    copia = copia / 10;
  }
  for (; numerobase > 0;) {
    unidade = numerobase % divisor;
    if (unidade == numerobusca) {
      qtdOcorrencias++;
      numerobase /= divisor;
    } else {
      numerobase /= 10;
    }
  } //  não funciona quando pede valores como 43, apenas unidade
  return qtdOcorrencias;
}