
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    fprintf(pipe, " unset key\n");
    fprintf(pipe, " set xrange [0:2]\n");
    fprintf(pipe, " set xtics 0.5\n");
    //fprintf(pipe, " set x2label \" lookback time, t(z)/Gyr\"\n");
    //fprintf(pipe, " set logscale x\n");
    //fprintf(pipe, " set logscale y\n");
    //fprintf(pipe, " set logscale z\n");
    //fprintf(pipe, " set logscale cb\n");
    fprintf(pipe, " set terminal postscript eps enhanced color solid lw 1 \"Times\" 24\n");
    fprintf(pipe, " set size square\n");
    fprintf(pipe, " set view map\n");
    fprintf(pipe, " set pm3d explicit\n");


    if (graph_type == 1)
    {
        fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/T_correction_factor_2D.eps'\n");
        //fprintf(pipe, " set title \"The evolution of cluster mass, M(M_{0}, z)\n");
        //fprintf(pipe, " set xrange [0.01:10000]\n");
        fprintf(pipe, " set xlabel \"T_{x} offset 0,0, 0\n");
        fprintf(pipe, "set ylabel \"{/Symbol k}\" offset 0,0, 0\n");
        fprintf(pipe, " set yrange [1:10000]\n");
        fprintf(pipe, " f1(T) = a1*tanh(T/b1)\n");
        fprintf(pipe, "  a1 = 300; b1 = 0.005;  \n");
        //fprintf(pipe, " fit f1(T) '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/bolcorr_0.01_20.00.txt ' using 1:2 via a1, b1\n");
        fprintf(pipe, "plot '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/bolcorr_0.01_20.00.txt ' u 1:(1.0/2) ls 7  notitle, f1(T) pt 7 ps 0.5 linecolor rgb 'black' title 'XSPEC'\n");
    }
    else
    {
        fprintf(pipe, " set palette rgbformulae 33,13,10\n");
        fprintf(pipe, " unset colorbox\n");
        //fprintf(pipe, "set isosamples 10, 10\n");
        //fprintf(pipe, " set samples 30, 30\n");
        fprintf(pipe, " unset surface\n");
        fprintf(pipe, " set contour\n");
        fprintf(pipe, " set style increment userstyles \n");
        fprintf(pipe, " set cntrparam levels 11\n");
        fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/T_correction_factor_3D.eps'\n");
        fprintf(pipe, " set xlabel \" T(L_{bol}, L_{{/Symbol k}}\"\n");
        fprintf(pipe, " set ylabel \"L_{500}(z)/10^{44}ergss^{-1}\n");
        fprintf(pipe, " set title \"The evolution of cluster luminosity, L(L_{0}, z)\n");
        fprintf(pipe, "set zlabel \"L_{0}/10^{44}ergss^{-1}\" offset 0,0, 0\n");
        fprintf(pipe, "set cblabel \"L_{0}/10^{44}ergss^{-1}\" offset 0,0, 0\n");
        //fprintf(pipe, " set cbrange [0.0001:100]\n");
        //fprintf(pipe, " set yrange [0.0001:100]\n");
        //fprintf(pipe, " set cbrange [0.01:10000]\n");
        //fprintf(pipe, " set zrange [0.01:10000]\n");

        fprintf(pipe, "splot '/Users/cosimacalder/documents/J/J_PROJECT/work/work/DeltaM.txt' u 1:3:4 ls 7 notitle w pm3d, '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/MCXC.txt' u 1:3:(0.01) pt 7 ps 0.5 linecolor rgb 'black' title 'MCXC',  '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/XMMXCS_z_M_L.txt' u 1:2:(0.01) pt 9 ps 0.5 linecolor rgb 'black' title 'XMM-XCS'   \n");
        //splot "kamel.data2" with pm3d, "kamel-oben-peakpos.data" using 1:2:(0) with points

    }

    fflush(pipe);
    fprintf(pipe, "exit \n");
    pclose(pipe);
}