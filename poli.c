#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para o polinomio
typedef struct
{
    float *coef;
    int n;
} polinomio;

// Função para criar um polinomio
polinomio *criaPoli(int grau)
{
    polinomio *p = malloc(sizeof(polinomio)); // Alocando e testando se memória foi alocada para o polinomio
    p->n = grau;
    if (p == NULL)
    {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }

    p->coef = malloc((grau + 1) * sizeof(float)); // Alocando e testando se memória foi alocada para os coeficientes
    if (p->coef == NULL)
    {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    for (int i = 0; i <= grau; i++)
    {
        p->coef[i] = 0; // Deixando todos os coeficientes = 0
    }
    return p;
}

// Função para liberar a memória alocada para o polinômio e coeficientes
void liberaMemoria(polinomio *p)
{
    free(p->coef);
    free(p);
}

// Função para ler um arquivo e identificar os coeficientes do polinomio
polinomio *lerArquivo(char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int grau = 0;
    float coeficiente;
    while (fscanf(arquivo, "%f", &coeficiente) != EOF)
    {
        grau++; // Leio quantos coeficientes tem no arquivo, logo determino qual sera o grau do polinomio
    }

    polinomio *p = criaPoli(grau - 1);

    rewind(arquivo); // Voltei o ponteiro para o inicio do arquivo e vou passar o valor dos coeficientes para o polinomio
    int i = 0;
    while (fscanf(arquivo, "%f", &coeficiente) != EOF)
    {
        p->coef[i] = coeficiente;
        i++;
    }

    fclose(arquivo);
    return p;
}

// Função para imprimir o polinômio
void imprime(polinomio *p)
{
    for (int i = p->n; i >= 0; i--)
    {
        printf("%.2fx^%d ", p->coef[i], i);
        if (i > 0)
        {
            printf("+ ");
        }
    }
    printf("\n");
}

// Função para calcular o valor de um polinômio para um determinado x
float valorPolinomio(polinomio *p, float x)
{
    float resultado = 0;
    for (int i = 0; i <= p->n; i++)
    {
        resultado += p->coef[i] * pow(x, i);
    }
    return resultado;
}

// Função para calcular a derivada
polinomio *calculaDerivada(polinomio *p)
{
    polinomio *derivada = criaPoli(p->n - 1);
    for (int i = 1; i <= p->n; i++)
    {
        derivada->coef[i - 1] = p->coef[i] * i; // Faz a regra do tombo para calcular a derivada
    }
    return derivada;
}

// Função para calcular a integral definida
float calculaIntegralDEF(polinomio *p, float x0, float x1)
{
    float resultado = 0;
    for (int i = 0; i <= p->n; i++)
    {
        resultado += (p->coef[i] / (i + 1)) * (pow(x1, i + 1) - pow(x0, i + 1));
    }
    return resultado;
}

// Função para somar polinômios
polinomio *somaPolinomios(polinomio *p1, polinomio *p2)
{
    int grau_max;
    if (p1->n > p2->n)
    {
        grau_max = p1->n;
    }
    else
    {
        grau_max = p2->n;
    }
    polinomio *soma = criaPoli(grau_max);
    for (int i = 0; i <= grau_max; i++)
    {
        float coef1, coef2;
        if (i <= p1->n)
        {
            coef1 = p1->coef[i];
        }
        else
        {
            coef1 = 0;
        }
        if (i <= p2->n)
        {
            coef2 = p2->coef[i];
        }
        else
        {
            coef2 = 0;
        }
        soma->coef[i] = coef1 + coef2;
    }

    return soma;
}

// Função para subtrair polinômios
polinomio *subtraiPolinomios(polinomio *p1, polinomio *p2)
{
    int grau_max;
    if (p1->n > p2->n)
    {
        grau_max = p1->n;
    }
    else
    {
        grau_max = p2->n;
    }

    polinomio *diferenca = criaPoli(grau_max);
    for (int i = 0; i <= grau_max; i++)
    {
        float coef1, coef2;
        if (i <= p1->n)
        {
            coef1 = p1->coef[i];
        }
        else
        {
            coef1 = 0;
        }
        if (i <= p2->n)
        {
            coef2 = p2->coef[i];
        }
        else
        {
            coef2 = 0;
        }
        diferenca->coef[i] = coef1 - coef2;
    }

    return diferenca;
}

// Função para multiplicar polinômios
polinomio *multiplicaPoli(polinomio *p1, polinomio *p2)
{
    int grau_resultante = p1->n + p2->n;
    polinomio *produto = criaPoli(grau_resultante);
    for (int i = 0; i <= p1->n; i++)
    {
        for (int j = 0; j <= p2->n; j++)
        {
            produto->coef[i + j] += p1->coef[i] * p2->coef[j];
        }
    }
    return produto;
}

int main()
{
    char nomeArquivo1[100];
    char nomeArquivo2[100];

    // Determina o nome do arquivo e lê
    printf("Digite o nome do arquivo do Polinomio 1: ");
    scanf("%s", nomeArquivo1);
    polinomio *polinomio1 = lerArquivo(nomeArquivo1);

    // Imprime Polinomio de acordo com o que foi lido no arquivo
    printf("Polinomio 1:\n");
    printf("P(x)= ");
    imprime(polinomio1);

    // Calcula e imprime Derivada do polinomio 1
    polinomio *derivada1 = calculaDerivada(polinomio1);
    printf("Derivada do Polinomio 1:\n");
    printf("P(x)= ");
    imprime(derivada1);

    // Calcula e imprime o valor do polinomio para um determinado X
    int xPoli1;
    printf("Digite valor de X para o polinomio 1: \n");
    scanf("%d", &xPoli1);
    int resultado = valorPolinomio(polinomio1, xPoli1);
    printf("P(%d) = %d\n\n", xPoli1, resultado);

    // Determina o nome do arquivo e lê
    printf("Digite o nome do arquivo do Polinomio 2: ");
    scanf("%s", nomeArquivo2);
    polinomio *polinomio2 = lerArquivo(nomeArquivo2);

    // Imprime Polinomio de acordo com o que foi lido no arquivo
    printf("Polinomio 2:\n");
    printf("P(x)= ");
    imprime(polinomio2);

    // Calcula e imprime Derivada do polinomio 1
    polinomio *derivada2 = calculaDerivada(polinomio2);
    printf("Derivada do Polinomio 2:\n");
    printf("P(x)= ");
    imprime(derivada2);

    // Calcula e imprime o valor do polinomio para um determinado X
    int xPoli2;
    printf("Digite valor de X para o polinomio 2: ");
    scanf("%d", &xPoli2);
    int resultadoPoli2 = valorPolinomio(polinomio2, xPoli2);
    printf("P(%d) = %d\n\n", xPoli2, resultadoPoli2);

    // Calcula e imprime a soma,subtraçao e multiplicação dos polinomios
    polinomio *soma = somaPolinomios(polinomio1, polinomio2);
    polinomio *diferenca = subtraiPolinomios(polinomio1, polinomio2);
    polinomio *produto = multiplicaPoli(polinomio1, polinomio2);
    printf("Soma dos Polinomios:\n");
    imprime(soma);
    printf("Subtracao dos Polinomios:\n");
    imprime(diferenca);
    printf("Produto dos Polinomios:\n");
    imprime(produto);

    // Usuario determina o valor dos limites para calcular as integrais
    float limiteInferior, limiteSuperior;
    printf("\nDigite o limite inferior e superior para a integracao: ");
    scanf("%f %f", &limiteInferior, &limiteSuperior);

    // Calcula e imprime as integrais dos polinomios
    float integral1 = calculaIntegralDEF(polinomio1, limiteInferior, limiteSuperior);
    float integral2 = calculaIntegralDEF(polinomio2, limiteInferior, limiteSuperior);
    printf("Integral do Polinomio 1: %.2f\n", integral1);
    printf("Integral do Polinomio 2: %.2f\n", integral2);

    // Libera memoria
    liberaMemoria(polinomio1);
    liberaMemoria(polinomio2);
    liberaMemoria(derivada1);
    liberaMemoria(derivada2);
    liberaMemoria(soma);
    liberaMemoria(diferenca);
    liberaMemoria(produto);

    return 0;
}
