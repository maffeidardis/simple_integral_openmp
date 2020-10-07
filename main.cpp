#include <iostream>
#include <math.h>
#include <omp.h>
#include <chrono>

using namespace std;

#define PI 3.14159265

double f( double x)
{//Insira aqui a funcao que deseja integrar
    return cos(x)*cos(x);
}

int main (int argc, char *argv[])
{
    double xa,xb;
    double I, incr;
    int i,n;
    cout<<"Bem vindo ao integrador via Metodo do Trapezio.\n\nVamos determinar os intervalos de integracao.\n \nInsira o limite inferior em graus: ";
    cin>>xa;
    cout<<"Insira o limite superior em graus: ";
    cin>>xb;
    cout<<"Insira o numero de particoes: ";
    cin>>n;
    xa=xa*PI/180;
    xb=xb*PI/180;
    incr = (xb-xa)/n;
    I=0.0f;
    std::chrono::steady_clock::time_point start(std::chrono::steady_clock::now());
    #pragma omp parallel for num_threads (8)
    for (i=0;i<n; i++)
    {
        xb=xa+incr;

        I=I + (xb-xa)*(f(xa)+f(xb))/2.0f;

        xa=xb;
    }
    std::chrono::steady_clock::time_point end(std::chrono::steady_clock::now());
    printf("A integral definida eh: %g \n", I);
    std::cout <<"O tempo de execucaoo foi de: "<< std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

    return 0;
}
