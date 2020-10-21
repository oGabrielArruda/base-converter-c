#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 30

int main()
{
    char numeroInicial[MAX];
    unsigned int baseInicial, baseDesejada, potenciaBasePraDez;
    int comeco, index;
    double resultado = 0;


    fgets(numeroInicial, MAX, stdin);
    scanf("%u", &baseInicial);
    scanf("%u", &baseDesejada);
    fflush(stdin);

    for(index = 0; index < strlen(numeroInicial); index++)
    {
        if(numeroInicial[index] == ',')
        {
            comeco = index;
            break;
        }
    }

    for(index = comeco-1, potenciaBasePraDez = 0; index >= 0; index--)
    {
        double valorDoChar = (double) numeroInicial[index]-48;
        resultado = resultado + valorDoChar * pow(baseInicial, potenciaBasePraDez);
        potenciaBasePraDez++;
    }

    for(index = comeco+1, potenciaBasePraDez = 1; index < strlen(numeroInicial)-1; index++)
    {
        double valorDoChar = (double) numeroInicial[index]-48;
        resultado = resultado + valorDoChar * pow((double)1/baseInicial, (double)potenciaBasePraDez);
        potenciaBasePraDez++;
    }

    printf("%lf\n", resultado);


    return 0;
}
