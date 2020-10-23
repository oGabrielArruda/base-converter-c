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


int main()
{
    char numeroInicial[MAX];
    unsigned int baseInicial, baseDesejada;

    fgets(numeroInicial, MAX, stdin);
    scanf("%u", &baseInicial);
    scanf("%u", &baseDesejada);
    fflush(stdin);

    double resultado = algumaParaDez(numeroInicial, baseInicial);


    printf("%lf\n", resultado);


    return 0;
}
