#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 30


int indexOf(char str[MAX], char procurado)
{
    int index;
    int length = strlen(str);

    for(index = 0; index < length; index++)
        if(str[index] == procurado)
            return index;
    return -1;
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

    posicaoDaVirgula = indexOf(numero, ',');
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

char transformarResto(char arrayCaracteres[26], int resto)
{
    int index = 0;

    if(resto <= 9)
        return resto + '0';

    for(index = 0; index < (resto-10); index++) {}

    return arrayCaracteres[index];
}


char* dezParaOutraParteInteira(int numero, int outraBase)
{
    char arrayCaracteres[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    char *restosInvertidos, *armazenamento = (char*)malloc(MAX*sizeof(char));
    int index, tamanhoDoVetor = 0;
    int resultadoDaDivisao = numero, resto;

    while(resultadoDaDivisao > 0)
    {
        resto = resultadoDaDivisao % outraBase;
        resultadoDaDivisao = (int)resultadoDaDivisao / outraBase;
        if(tamanhoDoVetor == MAX)
            break;

        char charResto = transformarResto(arrayCaracteres, resto);
        armazenamento[tamanhoDoVetor++] = charResto;
    }

    restosInvertidos = (char*)malloc(tamanhoDoVetor*sizeof(char));
    for(index = 0; index < tamanhoDoVetor; index++)
    {
        restosInvertidos[index] = armazenamento[tamanhoDoVetor-(index+1)];
    }
    free(armazenamento);
    return restosInvertidos;
}

char* dezParaOutra(double numero, int outraBase)
{
    char* parteInteira = dezParaOutraParteInteira((int) numero, outraBase);
    // parte fracionaria (fazer)
    return parteInteira;
}


int main()
{
    char numeroInicial[MAX];
    unsigned int baseInicial, baseDesejada;
    double resultado;

    fgets(numeroInicial, MAX, stdin);
    scanf("%u", &baseInicial);
    scanf("%u", &baseDesejada);
    fflush(stdin);

    resultado = algumaParaDez(numeroInicial, baseInicial);
    char* res = dezParaOutra(resultado, baseDesejada);
    printf("%s\n", res);


    return 0;
}
