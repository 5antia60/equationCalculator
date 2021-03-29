#include <stdio.h>
#include <conio.h>
#include <math.h>

//Funcoes
void grau1 (int qTermos, float *coeficiente, int *expoente);
float determinarABC(int qTermos, float *coeficiente, int *expoente, char termoEscolhido);
void grau2 (int qTermos, float *coeficiente, int *expoente);
void dicotomia(int qTermos, float *coeficiente, int *expoente, float intervaloA, float intervaloB, float precisao);

int main()
{
	//Resgatar a quantidade de termos presentes na equacao
	int qTermos, i, maiorExpoente = 0;
	float iA, iB, precisao;
	
	printf("Quantidade de termos da equacao: ");
	scanf("%i", &qTermos);
	
	float coeficiente[qTermos];
	int expoente[qTermos];
	
	//Formar a equacao
	for(i=0; i<qTermos; i++)
	{
		printf("Mostre o valor do %io coeficiente e do %io expoente de x (valores entre virgula): ", i+1, i+1);
		scanf("%f, %i", &coeficiente[i], &expoente[i]);
		
		if(expoente[i]>maiorExpoente)
		{
			maiorExpoente = expoente[i];
		}
	}
	
	float *pCoeficiente = coeficiente;
	int *pExpoente = expoente;
	
	switch (maiorExpoente)
		{	
		case 0:
			// 1o GRAU 
			printf("\nFuncao nao existe\n");
			break;
		
		case 1:
			// 1o GRAU 
			printf("\nFuncao de 1o grau!!!\n");
			grau1(qTermos, pCoeficiente, pExpoente);	
			break;

		case 2:
			// 2o GRAU 
			printf("\nFuncao de 2o grau!!!\n");
			grau2(qTermos, pCoeficiente, pExpoente);	
			break;
			
		default:
			//3o GRAU ou maior
			printf("\nFuncao de 3o grau ou maior!!!\n");
			
			//Receber intervalo
			printf("Valor do intervalo (valores entre virgula): ");
			scanf("%f, %f", &iA, &iB);
			printf("Valor da precisao (use ponto para numeros decimais): ");
			scanf("%f", &precisao);
			
			dicotomia(qTermos, pCoeficiente, pExpoente, iA, iB, precisao);
			

			break;
		}
	

    getch();
    return 0;
}

//Calculo de primeiro grau
void grau1 (int qTermos, float *coeficiente, int *expoente)
{	
	int i;
	float ladoDireito=0, ladoEsquerdo=0, resultado;

	for (i=0; i<qTermos; i++)
	{	
		if(expoente[i] == 0)
		{	
			//Somar os valores sem X
			ladoDireito = ladoDireito + coeficiente[i];	
		}
		else
		{
			//Somar os valores com X
			ladoEsquerdo = ladoEsquerdo + coeficiente[i];
		}
	}
	
	resultado = ladoDireito/ladoEsquerdo;

	printf("Resultado da equacao: %.3f\n", resultado);
}

//Determinar os tres principais termos para as formulas
float determinarABC(int qTermos, float *coeficiente, int *expoente, char termoEscolhido)
{
	float a=0, b=0, c=0;
	int i;
	
	for (i=0; i<qTermos; i++)
	{
		switch (expoente[i])
		{
			case 0:
				c = c + coeficiente[i];	
				break;
				
			case 1:
				b = b + coeficiente[i];	
				break;
				
			case 2:
				a = a + coeficiente[i];	
				break;
		}
	}
	
	float resultado = 0;
	switch (termoEscolhido)
		{
			case 'c':
				resultado = c;
				break;
				
			case 'b':
				resultado = b;
				break;
				
			case 'a':
				resultado = a;
				break;
		}
	
	return resultado;
}

//Calculo de segundo grau
void grau2(int qTermos, float *coeficiente, int *expoente)
{
	float a, b, c, x1, x2, delta;
	
	a = determinarABC(qTermos, coeficiente, expoente, 'a');
	b = determinarABC(qTermos, coeficiente, expoente, 'b');
	c = determinarABC(qTermos, coeficiente, expoente, 'c');
 
	//Formula do delta
	delta = (b*b) - (4*a*c);
	
	//Formula de bhaskara
	x1 = (-b+sqrt(delta)) / (2*a);
	//sqrt( ) = funcao para calcular raiz quadrada
	x2 = (-b-sqrt(delta)) / (2*a);
	

	if(delta < 0) 
	{
		printf("A equacao nao possui raizes reais!!!\n");
	} 
	else 
	{
		printf("Resultado de x1: %.3f...\n", x1);
		printf("Resultado de x2: %.3f...\n", x2);
	}
}

//Metodo da dicotomia
void dicotomia(int qTermos, float *coeficiente, int *expoente, float intervaloA, float intervaloB, float precisao)
{
	int i = 0, n=0;
	float termos[qTermos], media = (intervaloA+intervaloB) /2, fa=0, fm=0, fb=0, k;
	
	printf("\n\n\t\t\t\tInteracoes do Metodo da Dicotomia\n");
	printf("\ni\ta\t\tm\t\tb\t\tf(a)\t\tf(m)\t\tf(b)\n");
	
	//Calcular interacoes
	k = (log10(fabs(intervaloB-intervaloA)) - (log10(precisao))) / log10(2);
	
	//Formar e calcular equacoes
	for(i=0; i<qTermos; i++)
	{
		fa= fa + (coeficiente[i] * (pow(intervaloA,expoente[i])));
		fb= fb + (coeficiente[i] * (pow(intervaloB,expoente[i])));
		fm= fm + (coeficiente[i] * (pow(media,expoente[i])));	
	}
	printf("%i\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n", n, intervaloA, media, intervaloB, fa, fm, fb);
	
	do
	{
		//Fazer alteracao de A ou B e f(a) ou f(b)
		if(fm>=0) //Caso f(m) positivo
		{
			if(fa>=0)
			{
				fa = fm;
				intervaloA = media;
			}
			else
			{
				fb = fm;
				intervaloB = media;
			}
		}
		else //Caso f(m) negativo
		{
			if(fa<0)
			{
				fa = fm;
				intervaloA = media;
			}
			else
			{
				fb = fm;
				intervaloB = media;
			}
		}
		
		media = (intervaloA+intervaloB) /2;
		//Formar e calcular f(m) de acordo com a equação
		fm = 0;
		for(i=0; i<qTermos; i++)
		{
			fm= fm + (coeficiente[i] * (pow(media,expoente[i])));	
		}
		
		n++;
		printf("%i\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\t\t%.3f\n", n, intervaloA, media, intervaloB, fa, fm, fb);
		
		//fabs() = funcao para calcular modulo
	}while(fabs(fm) > precisao);
	
	printf("\nA raiz da funcao e %.3f com erro de %.3f (< %.3f).\n", media, fm, precisao);
	
	//ceil() = funcao que retorna o primeiro inteiro encontrado maior do que o valor resultado da operação
	printf("\nA quantidade de interacoes e aproximadamente %.2f (k = %.2f).", ceil(k), k);
}



