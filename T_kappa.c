///integratio_Mn of given function using Trapezoidal rule
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OMEGA_0 1
#define OMEGA_M 0.3
#define OMEGA_LAMDA 0.7
#define H_0 70//2.2685E-18
#define  c  46.1//46.1
#define M_sun 1.99E30
#define alpha 1.64
#define k 1.87931 //k = 10^{0..274}

void plot_results(int graph_type);
int main()
{
    int graph_type = 1;

    plot_results(graph_type);

    return 0;
}

void plot_results(int graph_type)
{

    FILE *pipe = popen("gnuplot -persist", "w");

    fprintf(pipe, " reset\n");
    //fprintf(pipe, "set isosamples 10, 10\n");
    //fprintf(pipe, " set samples 30, 30\n");
    //fprintf(pipe, " unset key\n");
    //fprintf(pipe, " set xtics nomirror\n");

    //fprintf(pipe, " set xrange [0:2]\n");
    fprintf(pipe, "set xlabel \"T_{x}/keV\" offset 0,0, 0\n");

    fprintf(pipe, " set terminal postscript eps enhanced color solid lw 1 \"Times\" 24\n");

    if (graph_type == 1)
    {
        //fprintf(pipe, " set logscale y\n");
        //fprintf(pipe, " set logscale y\n");
        fprintf(pipe, " set xrange [0:20]\n");
        fprintf(pipe, " set yrange [0:6]\n");
        fprintf(pipe, " set ytics 1\n");
        fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/T_kappa.eps'\n");
        //fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/T_kappa_tom.eps'\n");
        //fprintf(pipe, " set title \"XSPEC, Luminosity Conversion Factor {/Symbol k}(T_{x}) \n");
        fprintf(pipe, " set ylabel \"{/Symbol k} (T_{x})\n");
        //fprintf(pipe, " set cbrange [1:10000]\n");
        //fprintf(pipe, " set yrange [0:100]\n");

        fprintf(pipe, "plot'/Users/cosimacalder/Documents/J/J_PROJECT/work/work/bolcorr_0.01_20.00.txt' u 1:(1.0/$2) w l linecolor rgb 'blue' title 'XMM-XCS:[0.05-100]-[0.1-2.4]keV', '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/bolcorr_0.5_2.0.txt' u 1:(1.0/$2) w l linecolor rgb 'red' title 'XMM-LSS:[0.50-2.0]-[0.1-2.4]keV'  \n");
    }


    fflush(pipe);
    fprintf(pipe, "exit \n");
    pclose(pipe);
}