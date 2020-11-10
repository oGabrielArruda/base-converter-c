#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 30

char arrayCaracteres[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

int indexOf(char str[MAX], char procurado)
{
    int index;
    int length = strlen(str);

    for(index = 0; index < length; index++)
        if(str[index] == procurado)
            return index;
    return -1;
}

void replace(char* str, char toReplace, char newChar)
{
    int index;
    int length = strlen(str);

    for(index = 0; index < length; index++)
        if(str[index] == toReplace)
            str[index] = newChar;
}

double getValorDoCharNaBaseDez(char c)
{
    if(isdigit(c))
        return (double) c - 48;
    else
    {
        char cUpper = toupper(c);
        return (double) cUpper - 55;
    }
}

double algumaParaDez(char numero[MAX], int base)
{
    double resultado = 0;
    int index, posicaoDaVirgula, potenciaBasePraDez = 0;
    int length = strlen(numero)-1;

    posicaoDaVirgula = indexOf(numero, '.');
    if(posicaoDaVirgula == -1) posicaoDaVirgula = length;

    // percorre os valores antes da vírgula
    for(index = posicaoDaVirgula-1, potenciaBasePraDez = 0; index >= 0; index--)
    {
        double valorDoChar = getValorDoCharNaBaseDez(numero[index]);
        resultado = resultado + valorDoChar * pow(base, potenciaBasePraDez);
        potenciaBasePraDez++;
    }

    // percorre os valores depois da virgula, somente se existir vírgula
    if(posicaoDaVirgula != length-1) // se tiver vírgula
        for(index = posicaoDaVirgula+1, potenciaBasePraDez = 1; index < strlen(numero)-1; index++)
        {
            double valorDoChar = getValorDoCharNaBaseDez(numero[index]);
            resultado = resultado + valorDoChar * pow((double)1/base, (double)potenciaBasePraDez);
            potenciaBasePraDez++;
        }

    return resultado;
}

char transformarCharDaBase10(int resto)
{
    int index = 0;

    if(resto <= 9)
        return resto + '0';

    for(index = 0; index < (resto-10); index++) {}

    return arrayCaracteres[index];
}


char* dezParaOutraParteInteira(int numero, int outraBase)
{
    char *restosInvertidos, *armazenamento = (char*)malloc(MAX*sizeof(char));
    int index, tamanhoDoVetor = 0;
    int resultadoDaDivisao = numero, resto;

    while(resultadoDaDivisao > 0)
    {
        resto = resultadoDaDivisao % outraBase;
        resultadoDaDivisao = (int)resultadoDaDivisao / outraBase;
        if(tamanhoDoVetor == MAX)
            break;

        char charResto = transformarCharDaBase10(resto);
        armazenamento[tamanhoDoVetor++] = charResto;
    }

    restosInvertidos = (char*)malloc(tamanhoDoVetor*sizeof(char));
    for(index = 0; index < tamanhoDoVetor; index++)
    {
        restosInvertidos[index] = armazenamento[tamanhoDoVetor-(index+1)];
    }
    free(armazenamento);

    restosInvertidos[tamanhoDoVetor] = ',';
    restosInvertidos[tamanhoDoVetor+1] = '\0';
    return restosInvertidos;
}

char* dezParaOutraParteFracionaria(double frac, int base)
{
    char *ret = (char*)malloc(MAX*sizeof(char));
    if(frac == 0)
    {
        ret[0] = '0';
        ret[1] = '\0';
        return ret;
    }

    int tamanhoDoNumero = 0, count = 0;

    while(frac != 0 && count != 5)
    {
        frac = frac * base;
        int parteInteira = (int) frac;

        frac = frac - parteInteira;
        ret[tamanhoDoNumero++] = transformarCharDaBase10(parteInteira);
        count++;
    }
    ret[tamanhoDoNumero] = '\0';
    return ret;
}

char* dezParaOutra(double numero, int outraBase)
{
    int pInteiraNumero = floor(numero);
    double pFracNumero = numero - pInteiraNumero;

    char *parteInteira = dezParaOutraParteInteira(pInteiraNumero, outraBase);
    char *parteFracionaria = dezParaOutraParteFracionaria(pFracNumero, outraBase);

    strcat(parteInteira, parteFracionaria);

    return parteInteira;
}



char* calcular(char* numeroInicial, unsigned int baseInicial, unsigned int baseDesejada)
{
    char *resultado;
    if(baseInicial == baseDesejada)
        resultado = numeroInicial;
    else
    {
        double nmrNaBaseDez;
        if(baseInicial != 10)
            nmrNaBaseDez = algumaParaDez(numeroInicial, baseInicial);
        else
            sscanf(numeroInicial, "%lf", &nmrNaBaseDez);

        if(baseDesejada != 10)
            resultado = dezParaOutra(nmrNaBaseDez, baseDesejada);
        else
        {
            char* buff = (char*)malloc(MAX * sizeof(char));
            sprintf(buff, "%f", nmrNaBaseDez);
            resultado = buff;
        }
    }
    return resultado;
}

int main()
{
    printf("--------------------------------------------------\n");
    printf("CONVERSOR DE NUMEROS EM DIFERENTES BASES NUMERICAS\n");
    printf("--------------------------------------------------\n");

    int opcao = 1;

    do
    {
        char ehNegativo = 0;
        char numeroInicial[MAX], *resultado;
        unsigned int baseInicial, baseDesejada;

        printf("Digite o numero que se deseja converter: ");
        fflush(stdout);
        fgets(numeroInicial, MAX, stdin);
        fflush(stdin);

        printf("\nDigite a base do numero digitado: ");
        fflush(stdout);
        scanf("%u", &baseInicial);
        fflush(stdin);

        printf("\nDigite agora a base para que se deseja converter o numero: ");
        fflush(stdout);
        scanf("%u", &baseDesejada);
        fflush(stdin);

        replace(numeroInicial, ',', '.');

        if(indexOf(numeroInicial, '-') == 0)
        {
            int index;
            for(index = 0; index < strlen(numeroInicial); index++)
                numeroInicial[index] = numeroInicial[index+1];
            ehNegativo = 1;
        }

        resultado = calcular(numeroInicial, baseInicial, baseDesejada);

        printf("\nO resultado da conversao eh: ");

        if(ehNegativo) printf("-%s\n\n\n", resultado);
        else printf("%s\n", resultado);

        printf("Digite 1 para continuar: ");
        fflush(stdout);

        scanf("%d", &opcao);
        fflush(stdin);
    }
    while(opcao == 1);


    return 0;
}
