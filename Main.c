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
    return restosInvertidos;
}

char* dezParaOutraParteFracionaria(double frac, int base)
{
    char *ret = (char*)malloc(MAX*sizeof(char));
    int tamanhoDoNumero = 0;

    while(frac != 0)
    {
        frac = frac * base;
        int parteInteira = (int) frac;

        frac = frac - parteInteira;
        ret[tamanhoDoNumero++] = transformarCharDaBase10(parteInteira);
    }
    ret[tamanhoDoNumero] = '\0';
    return ret;
}

char* dezParaOutra(double numero, int outraBase)
{
    char *parteInteira = dezParaOutraParteInteira((int) numero, outraBase);
    char *parteFracionaria = dezParaOutraParteFracionaria(numero - (int)numero, outraBase);
    int lenInteiro = strlen(parteInteira), lenFrac = strlen(parteFracionaria), index = 0;

    char *resultado = (char*)malloc((lenInteiro + lenFrac + 1) * sizeof(char));

    for(index = 0; index < lenInteiro; index++)
        resultado[index] = parteInteira[index];

    resultado[index] = ',';
    for(index = 0; index < lenFrac; index++)
        resultado[index+lenInteiro+1] = parteFracionaria[index];
    resultado[index]  = '\0';

    return resultado;
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
    char *res = dezParaOutra(resultado, baseDesejada);
    printf("%s\n", res);


    return 0;
}
