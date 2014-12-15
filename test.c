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
double y(double z)
{
    return -(c / H_0) * ((1 + (1.11 * z)) / (1 + z)) * sqrt(((OMEGA_M * pow((1 + z), 3)) + OMEGA_LAMDA ) / (OMEGA_0 * pow((1 + z), 3)) + OMEGA_LAMDA);
}
double conversion(double redshift, double mass)
{
    double h_z, L;

    h_z = sqrt((OMEGA_M * pow((1 + redshift), 3)) + OMEGA_LAMDA);

    L = k * pow(h_z, (7 / 3)) * pow((mass / (3E2)), alpha);

    return L;
}
int main()
{
    double z, zn = 0, t, M_1, M_2, L_1, L_2, h, s, DeltaM, ratio_M, ratio_L;
    int i, n = 1000, graph_type;

    //set up multiple file output
    char buf[0x100];

    snprintf(buf, sizeof(buf), "/Users/cosimacalder/documents/J/J_PROJECT/work/work/DeltaM.txt"); //sets variable name of outputted data file

    FILE *file = fopen(buf, "w");  //writes to file
    if (file != NULL) //checks file exists
    {
        for (M_1 = 1e-5; M_1 < 1e5; M_1 = M_1 * 1.1)
        {
            for (z = 0.01 ; z <= 15; z = z * 1.1)
            {

                h = (zn - z) / n;
                s = y(z) + y(zn);
                for (i = 1; i < n; i++)
                {
                    s += 2 * y(z + i * h);
                }

                t = z / (3 * H_0 * OMEGA_0 * pow((1 + z), (3 / 2)));
                DeltaM = (h / 2) * s * pow(M_1 , 1.1);
                 M_2 = M_1 + DeltaM;
                ratio_M =  M_1 / M_2;
                L_1 = conversion(z, M_1);
                L_2 = conversion(z, M_2);
                ratio_L =  L_1/ L_2;

                fprintf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", z, t, L_1, L_2, ratio_L, M_1, M_2, ratio_M);
                //printf("%lf\t%lf\t%lf\t%lf\t\n", DeltaM);
            }

            fprintf(file, "\n");
        }
    }
    fclose(file);       //closes the file

    for (graph_type = 1 ; graph_type <= 2; graph_type  ++)
    {
        plot_results(graph_type);
    }


    return 0;
}

void plot_results(int graph_type)
{

    FILE *pipe = popen("gnuplot -persist", "w");

    fprintf(pipe, " reset\n");
    //fprintf(pipe, "set isosamples 10, 10\n");
    fprintf(pipe, " set samples 101, 101\n");
    //fprintf(pipe, " unset key\n");
    fprintf(pipe, " set key default\n");
    fprintf(pipe, " set key inside bottom right\n");
    fprintf(pipe, " unset colorbox\n");
    //fprintf(pipe, " unset surface\n");
    fprintf(pipe, " set xtics nomirror\n");
    //fprintf(pipe, " set x2tics\n");

    fprintf(pipe, " set palette rgbformulae 33,13,10\n");
    //fprintf(pipe, "set palette positive nops_allcF maxcolors 0 gamma 1.5 color model CMY \n");
    //fprintf(pipe, " set palette rgbformulae 3,33, 13\n");


    fprintf(pipe, " set contour\n");
    fprintf(pipe, " set style increment userstyles \n");
    fprintf(pipe, " set xrange [0:1.5]\n");
    fprintf(pipe, " set xtics 0.5\n");
    fprintf(pipe, " set xlabel \" z\"\n");
    //fprintf(pipe, " set x2label \" lookback time, t(z)/Gyr\"\n");
    //fprintf(pipe, " set logscale x\n");
    fprintf(pipe, " set logscale y\n");
    fprintf(pipe, " set logscale z\n");
    fprintf(pipe, " set logscale cb\n");
    fprintf(pipe, " set terminal postscript eps enhanced color solid lw 1 \"Times\" 24\n");
    fprintf(pipe, " set size square\n");
    fprintf(pipe, " set view map\n");
    fprintf(pipe, " set pm3d explicit\n");


    if (graph_type == 1)
    {
        fprintf(pipe, " set cntrparam levels 11\n");
        fprintf(pipe, " set output '/Users/cosimacalder/Documents/J/University/Year_4/Project/Lit_Review/Figures/M_Z.eps'\n");
        //fprintf(pipe, " set title \"The evolution of cluster mass, M(M_{0}, z)\n");
        fprintf(pipe, " set ylabel \"M_{500}(z)/10^{12}M\n");
        fprintf(pipe, "set cblabel \"M_{0}/10^{12}M\" offset 0,0, 0\n");
        fprintf(pipe, "set zlabel \"M_{0}/10^{12}M\" offset 0,0, 0\n");
        fprintf(pipe, " set cbrange [1:10000]\n");
        fprintf(pipe, " set yrange [1:10000]\n");
        // fprintf(pipe, " set zrange [0.01:10000]\n");

        fprintf(pipe, "splot '/Users/cosimacalder/documents/J/J_PROJECT/work/work/DeltaM.txt' u 1:6:7 ls 7  notitle  w pm3d, '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/MCXC.txt' u 1:2:(0.01) pt 65 ps 0.5 linecolor rgb 'black' title 'MCXC', '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/XMMXCS_z_M_L.txt' u 1:2:(0.01) pt 66 ps 0.5 linecolor rgb 'black' title 'XMM-XCS', '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/planck_z_M_L.txt' u 1:2:(0.01) pt 64 ps 0.5 linecolor rgb 'black'  title 'PCCS-SZ'  \n");
    }
    else
    {
        fprintf(pipe, " set cntrparam levels 5\n");
        fprintf(pipe, " set output '/Users/cosimacalder/Documents/J/University/Year_4/Project/Lit_Review/Figures/L_Z.eps'\n");
        fprintf(pipe, " set ylabel \"L_{500}(z)/10^{44}ergss^{-1}\n");
        //fprintf(pipe, " set title \"The evolution of cluster luminosity, L(L_{0}, z)\n");
        fprintf(pipe, "set zlabel \"L_{0}/10^{44}ergss^{-1}\" offset 0,0, 0\n");
        fprintf(pipe, "set cblabel \"L_{0}/10^{44}ergss^{-1}\" offset 0,0, 0\n");
        fprintf(pipe, " set cbrange [0.001:100]\n");
        fprintf(pipe, " set yrange [0.001:100]\n");
        //fprintf(pipe, " set cbrange [0.01:10000]\n");
        //fprintf(pipe, " set zrange [0.01:10000]\n");

        fprintf(pipe, "splot '/Users/cosimacalder/documents/J/J_PROJECT/work/work/DeltaM.txt' u 1:3:4 ls 7 notitle w pm3d, '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/MCXC.txt' u 1:3:(0.01) pt 65 ps 0.5 linecolor rgb 'black' title 'MCXC',  '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/XMMXCS_z_M_L.txt' u 1:3:(0.01) pt 66 ps 0.5 linecolor rgb 'black' title 'XMM-XCS', '/Users/cosimacalder/Documents/J/J_PROJECT/work/work/planck_z_M_L.txt' u 1:3:(0.01) pt 64 ps 0.5 linecolor rgb 'black' title 'PCCS-SZ'    \n");


    }

    fflush(pipe);
    fprintf(pipe, "exit \n");
    pclose(pipe);
}