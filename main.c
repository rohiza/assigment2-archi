#include <stdio.h>
#include <strings.h>
#include <memory.h>
#include <stdlib.h>


typedef struct Complex{
    double real;
    double img;
}Complex;

Complex horner(Complex* arr,Complex x, int n);

void add_complex(Complex number1, Complex number2,Complex* newComplex){
    (*newComplex).real = number1.real+number2.real;
    (*newComplex).img = number1.img+number2.img;
}


void sub_complex(Complex number1, Complex number2,Complex* newComplex){
    newComplex->real = number1.real-number2.real;
    newComplex->img = number1.img-number2.img;
}

void mul_complex(Complex number1, Complex number2,Complex* newComplex){
    newComplex->real = number1.real*number2.real - number1.img*number2.img;
    newComplex->img = number1.img*number2.real + number1.real*number2.img;
}

void div_complex(Complex number1, Complex number2,Complex* newComplex){
    Complex temp1;//a^2 + b^2
    temp1.real = (number2.real*number2.real);
    temp1.img = (number2.img*number2.img);
    Complex temp2;
    Complex temp3;
    temp3.real = number2.real;
    temp3.img = (number2.img*-1); //(a-bi)
    mul_complex(number1,temp3,&temp2); //(c+di) * 1 / (a^2 + b^2)
    newComplex->real = temp2.real / (temp1.real+temp1.img); // (a-bi) * ((c+di) * 1 / (a^2 + b^2))
    newComplex->img = temp2.img / (temp1.real+temp1.img);
}

void convert_to_Complex(double* polyinomReal, double* polyinomImg,int order,Complex* complexArray){
    for(int i=0;i<=order;i++){
        complexArray[i].real = polyinomReal[i];
        complexArray[i].img = polyinomImg[i];
    }

}

void calcDireative(double* polyinomReal,double *polynomImg,double *direativeReal,double* direativeImg,int order){
    for (int i = 0; i<order +1 ; ++i) {
        direativeReal[i] = polyinomReal[i+1]*(i+1);
        direativeImg[i] = polynomImg[i+1]*(i+1);
    }
}

double convert_complet_to_double(Complex comp){
    return comp.real*comp.real + comp.img*comp.img;
}

Complex next_calculation(double* polyinomReal,double *polynomImg,double *direativeReal,double* direativeImg, int order,Complex initial,Complex* complexArray){
    Complex divded;
    calcDireative(polyinomReal,polynomImg,direativeReal,direativeImg,order);
    Complex divArray[order];
    convert_to_Complex(direativeReal,direativeImg,order,divArray);
    divded = horner(divArray,initial,order-1);
    Complex result,finalResult;
    div_complex(horner(complexArray,initial,order), divded, &result);
    sub_complex(initial,result,&finalResult);
    return finalResult;

}


int main() {

// -----------------------------------------INPUT--------------------------------

    double epsilon;
    int order;
   Complex initial;
    scanf("epsilon = %lf\n",&epsilon); //read epsilon input
    scanf("order = %d\n", &order); // read order
    double polyinomReal[order+1];
    double polyinomImg[order+1];
    double polyinomDireativereal[order];
    double polyinomDireativeImg[order];
    Complex complexArray[order+1];


    for (int i = 0; i<= order; i++){ //read coeffs
        int index;
        double num1;
        double num2;
        scanf("coeff %d = %lf %lf\n", &index, &num1, &num2);
        polyinomReal[index] = num1;
        polyinomImg[index] = num2;
    }
    scanf("initial = %lf %lf",&initial.real,&initial.img); //read inital-value

    convert_to_Complex(polyinomReal,polyinomImg,order,complexArray); //inital complexArray

   // double next_zn = convert_complet_to_double(initial);

    while(convert_complet_to_double(horner(complexArray,initial,order)) >= (epsilon*epsilon)){
        initial = next_calculation(polyinomReal,polyinomImg,polyinomDireativereal,polyinomDireativeImg,order,initial,complexArray);
        //next_zn = convert_complet_to_double(initial);
    }
    printf("%lf %lf\n", initial.real,initial.img);

    return  0;
}


Complex horner(Complex* arr,Complex x, int n){
    Complex result;
    Complex temp;
    result = arr[n];
    for(int i = 1; i<=n;i++){
        mul_complex(result,x,&temp);
        result = temp;
        add_complex(result,arr[n-i], &temp);
        result = temp;
    }
    return result;
}


/*
epsilon = 1.0e-8
order = 2
coeff 2 = 2.0 0.0
coeff 1 = 5.0 0.0
coeff 0 = 3.0 0.0
initial = 1.0 -1.0

 */