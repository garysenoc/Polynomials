#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10


/*
Name: Gary Lloyd Senoc
Activity Name; Polynomials
Date: January 28, 2021
*/

typedef int *Polynomial;

Polynomial newPoly(); // allocate return the pointer
void destroy(Polynomial *p); ; // set to NULL after freeing
void display(const Polynomial p);
void addTerm(Polynomial p, int coef, int exp);
Polynomial add(const Polynomial p1, const Polynomial p2); // return a new polynomial that represents the sum of p1 and p2
Polynomial subtract(const Polynomial p1, const Polynomial p2); // return a new polynomial that represents the difference of p1 and p2
Polynomial derivative(const Polynomial p);// return a new polynomial that represents the derivative of p
int evaluate(Polynomial p, int x);// compute the value of the polynomial given a value for x
int isConstant(const Polynomial p);// return 1 if the value of p is constant, 0 otherwise
int isZero(const Polynomial p);// return 1 if the value of p is zero (0), 0 otherwise
int isComplete(const Polynomial p);// return 1 if there is coefficient for all exponents, 0 otherwise

int main(){
	
	Polynomial p1 = newPoly();
	Polynomial p2 = newPoly();
	Polynomial deriv1 = newPoly();
	Polynomial deriv2 = newPoly();
	Polynomial sum = newPoly();
	Polynomial diff = newPoly();
	
	//P1=2x^3+7x^2 +x, P2=2x^2-4x-12
	
	addTerm(p1,2,3);
	addTerm(p1,7,2);
	addTerm(p1,1,1);
	

	addTerm(p2,2,2);
	addTerm(p2,-4,1);
	addTerm(p2,-12,0);
	
	
	
	printf("P1: ");
	display(p1);
	printf("P2: ");
	display(p2);
	
	sum = add(p1,p2);
	diff = subtract(p1,p2);
	
	printf("Sum: ");
	display(sum);
	printf("Difference: ");
	display(diff);
	
	
	deriv1 = derivative(p1);
	deriv2 = derivative(p2);
	
	printf("P1 Derivative: ");
	display(deriv1);
	printf("P2 Derivative: ");
	display(deriv2);
	
	
	printf("Evaluate let x = 2 P1: %d \n",evaluate(p1,2));
	printf("Evaluate let x = 2 P2: %d \n",evaluate(p2,2));
	printf("Evaluate let x = 3 P1: %d \n",evaluate(p1,3));
	printf("Evaluate let x = 3 P2: %d \n",evaluate(p2,3));
	printf("P1 isConstant: %d \n",isConstant(p1));
	printf("P2 isConstant: %d \n",isConstant(p2));
	printf("P1 isZero: %d \n",isZero(p1));
	printf("P2 isZero: %d \n",isZero(p2));
	printf("P1 isComplete: %d \n",isComplete(p1));
	printf("P2 isComplete: %d \n",isComplete(p2));

	destroy(&p1);
	destroy(&p2);
	destroy(&deriv1);
	destroy(&deriv2);
	destroy(&sum);
	destroy(&diff);
	
	return 0;
}


Polynomial newPoly(){
	return (Polynomial)calloc(MAX, sizeof(int));	
}

void display(const Polynomial p){
	
	int i;
	int count = 0;
	for(i=MAX-1;i>=0;i--){
		if(p[i] == 0)
			continue;
		if(p[0]!=0&&i==0){
			if(count >0){
				if(p[i]>0)
					printf(" + ");
				else
					printf(" - ");
			}
			printf("%d ", abs(p[i]));
			count++;
		}
		else{
			if(i>=0 && i < MAX-1 && count >0){
				if(p[i]>0)
					printf(" + ");
				else
					printf(" - ");
			}
			if(p[i] == 1){
				if(i == 1)
					printf("x");
				else
					printf("x^%d",abs(i));
			}		
		else{
			if(i==1)
				printf("%dx ",abs(p[i]));
			else{
				printf("%dx^%d ",abs(p[i]),i);
			}
		}	
		count++;
		}
	}
	printf("\n");
	
}

void destroy(Polynomial *p){
	free(*p);
	*p = NULL;
}

void addTerm(Polynomial p, int coef, int exp){
	p[exp] = coef;
}

Polynomial add(const Polynomial p1, const Polynomial p2){
	Polynomial res = newPoly();
	for(int i = 0;i<=MAX/2;i++){ // the condition can be < because the max is 10 and it is even but we can use <= if the max number changed and become add to also check the middle 
		res[i] = p1[i] + p2[i]; // this loop will automatically solve the derivate at the start and end of the polynomials at the same time
		res[MAX-1-i] = p1[MAX-i-1] + p2[MAX-i-1];
	}
	
	
	return res;
}

Polynomial subtract(const Polynomial p1, const Polynomial p2){
	Polynomial res = newPoly();
	for(int i = 0;i<=MAX/2;i++){
			res[i] = p1[i] - p2[i];
			res[MAX-1-i] = p1[MAX-i-1] - p2[MAX-i-1];
	}
	
	
	return res;
}
Polynomial derivative(const Polynomial p){
	Polynomial res = newPoly();
	res[9] = 0;
	for(int i = 1;i<=MAX/2;i++){ // the condition can be < because the max is 10 and it is even but we can use <= if the max number changed and become add to also check the middle 
		res[i-1] = p[i] * i;// this loop will automatically solve the derivate at the start and end of the polynomials at the same time
		res[MAX-i] = p[MAX-i] * (MAX-i);
	}
	
	return res;
}
int evaluate(Polynomial p, int x){
	int res =p[0];
	for(int i = 1;i<=MAX/2;i++){
		if(p[i] == 0)
			continue;
		res= res + (int)(pow(x,i) * p[i]);
		if(p[MAX-i] == 0)
			continue;
		res = res + (int)(pow(x,MAX-i) * p[MAX-i]); // Evaluate the start and end until to the middle at the same time
	}

	return res;
}

int isConstant(const Polynomial p){
	for(int i=1;i<=MAX/2;i++)// the condition can be < because the max is 10 and it is even but we can use <= if the max number changed and become add to also check the middle
		if(p[i]!=0 || p[MAX-i]!=0)
			return 0;
	return 1; // considering 0 as a constant in index[0]
}
int isZero(const Polynomial p){
	for(int i =0;i<=MAX/2;i++)// the condition can be < because the max is 10 and it is even but we can use <= if the max number changed and become add to also check the middle
		if(p[i]!=0 || p[MAX-1-i]!=0) //this will search the start and end at of the array  at the same time until it reach the middle
			return 0;
	return 1;
}

	
int isComplete(const Polynomial p){
	for(int i=0;i<=MAX/2;i++) // the condition can be < because the max is 10 and it is even but we can use <= if the max number changed and become add to also check the middle
		if(p[i]==0 || p[MAX-1-i] ==0) //this will search the start and end of the array at the same time until it reach the middle
			return 0;
	return 1;
}
