#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OMEGA_0 1
#define OMEGA_M 0.3
#define OMEGA_LAMDA 0.7
#define H_0 70
#define H_0_Gyr 71.5868E-3//2.2685E-18 x 3.15569E7 x 10^9
#define  c  46.1//46.1
#define M_sun 1.99E30
#define alpha 1.64
#define k 1.87931 //k = 10^{0..274}
// enum VARIABLE_TYPE {MASS, LUMINOSITY};
//    typedef    enum GRAPH_TYPE     GRAPH_TYPE;
//     enum AXIS_TYPE {LINEAR, LOGSACELE};
//    typedef    enum AXIS_TYPE     AXIS_TYPE;
//    enum GRAPH_TYPE {REGULAR, RATIO};
//    typedef    enum GRAPH_TYPE   GRAPH_TYPE;
void PLOT_RESULTS(int VARIABLE_TYPE, int AXIS_TYPE, int GRAPH_TYPE);
double EQUATION_M(double z)
{
    return -(c / H_0) * ((1 + (1.11 * z)) / (1 + z)) * sqrt(((OMEGA_M * pow((1 + z), 3)) + OMEGA_LAMDA ) / (OMEGA_0 * pow((1 + z), 3)) + OMEGA_LAMDA);
}
double EQUATION_T(double z)
{
    return (1 / (H_0 * (1 + z) * sqrt(((pow((1 + z), 2) * ( 1 + (z * OMEGA_M))) - (z * (2 + z) * OMEGA_LAMDA)))));
    //return (1 / (H_0 * (1 + z) * sqrt(((OMEGA_0 * pow((1 + z), 3)) + OMEGA_LAMDA))));
}
double CONVERSION(double redshift, double mass)
{
    double E_z, L;

    E_z = sqrt((OMEGA_M * pow((1 + redshift), 3)) + OMEGA_LAMDA);

    L = k * pow(E_z, (7 / 3)) * pow((mass / (3E2)), alpha);

    return L;
}
double INTEGRATION(double n, double an, double a, double(*f)(double arg))
{
    int i;
    double h = 0, s = 0;

    h = (an - a) / n;
    s = f(a) + f(an);
    for (i = 1; i < n; i++)
        s += 2 * f(a + i * h);

    return ((h / 2) * s);
}

int main()
{
    double z, zn = 0, t, M_Z, M_0, L_Z, L_0, DELTA_M, RATIO_M, RATIO_L, INTEGRAL_M, INTEGRAL_t;
    int VARIABLE_TYPE, AXIS_TYPE, GRAPH_TYPE;

    //set up multiple file output
    char buf[0x100];

    snprintf(buf, sizeof(buf), "/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/DELTA_M.txt"); //sets variable name of outputted data file

    FILE *file = fopen(buf, "w");  //writes to file
    if (file != NULL) //checks file exists
    {
        for (M_Z = 1e-5; M_Z < 1e5; M_Z = M_Z * 1.1)
        {
            for (z = 0.001 ; z <= 14; z = z * 1.05)
            //for (z = 0.001 ; z <= 14; z = z+1)
            {
                INTEGRAL_M = INTEGRATION(1000, zn, z, EQUATION_M);
                t = INTEGRATION(1000, zn, z, EQUATION_T);
                //t = (2 / (3 * H_0_Gyr)) * ( 1 - sqrt(OMEGA_0) * pow((1 + z), -1.5));

                DELTA_M =  INTEGRAL_M * pow(M_Z , 1.1);
                M_0 = DELTA_M + M_Z;
                RATIO_M =  M_Z / M_0;

                L_Z = CONVERSION(z, M_Z);
                L_0 = CONVERSION(z, M_0);
                RATIO_L =  L_Z / L_0;

                fprintf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", z, t, L_Z, L_0, RATIO_L, M_Z, M_0, RATIO_M, RATIO_L);
                //fprintf(file, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", z, INTEGRAL_M, DELTA_M, M_Z, M_0, RATIO_M, t);
            }

            fprintf(file, "\n");
        }
    }

    fclose(file);       //closes the file

    for (VARIABLE_TYPE = 1; VARIABLE_TYPE <= 2; VARIABLE_TYPE ++)
        for (AXIS_TYPE = 1; AXIS_TYPE <= 2; AXIS_TYPE ++)
            for (GRAPH_TYPE = 1; GRAPH_TYPE <= 2; GRAPH_TYPE ++)
                PLOT_RESULTS(VARIABLE_TYPE, AXIS_TYPE, GRAPH_TYPE);

    return 0;
}

void PLOT_RESULTS(int VARIABLE_TYPE, int AXIS_TYPE, int GRAPH_TYPE)
{

    FILE *pipe = popen("gnuplot -persist", "w");
    fprintf(pipe, " reset\n");
    //fprintf(pipe, "set isosamples 10, 10\n");
    fprintf(pipe, " set samples 101, 101\n");
    fprintf(pipe, " unset key\n");
    //fprintf(pipe, " set key at 1.4, 13, 1\n");
    //fprintf(pipe, " set key horizontal outside bottom right\n");
    //fprintf(pipe, " set key above \n");



    //fprintf(pipe, " unset colorbox\n");
    //fprintf(pipe, " unset surface\n");
    //fprintf(pipe, " set xtics nomirror\n");
    //fprintf(pipe, " set x2tics\n");

    fprintf(pipe, " set palette rgbformulae 33,13,10\n");
    //fprintf(pipe, " set palette defined ( 0 0 0 0, 1 1 1 1 )\n");
    //fprintf(pipe, " set palette functions gray, gray, gray\n");
    //fprintf(pipe, "set palette positive nops_allcF maxcolors 0 gamma 1.5 color model CMY \n");
    //fprintf(pipe, " set palette rgbformulae 3,33, 13\n");

    fprintf(pipe, " set contour\n");
    fprintf(pipe, " set style increment userstyles \n");


    if (AXIS_TYPE == 1)
    {
        fprintf(pipe, " set xrange [0:1.5]\n");
        fprintf(pipe, " set xtics 0.2\n");
        fprintf(pipe, " set mxtics 0.1\n");

    }

    else
    {
        fprintf(pipe, " set xrange [0.003:1.5]\n");
        fprintf(pipe, " set logscale x\n");
        //fprintf(pipe, " set logscale x2\n");
        
    }

    fprintf(pipe, " set xlabel \" z\"\n");
    fprintf(pipe, " set x2label \" lookback time/Gyr\"\n");
    //fprintf(pipe, " set logscale x\n");
    fprintf(pipe, " set logscale y\n");
    fprintf(pipe, " set logscale z\n");
    fprintf(pipe, " set logscale cb\n");
    fprintf(pipe, " set terminal postscript eps enhanced color solid lw 1 \"Times\" 12\n");
    //fprintf(pipe, " set size square\n");
    fprintf(pipe, " set view map\n");
    fprintf(pipe, " set pm3d explicit\n");


    if (VARIABLE_TYPE == 1)
    {
        fprintf(pipe, " set cntrparam levels 11\n");
        fprintf(pipe, "set cblabel \"M_{0} [10^{12} solar masses]\" offset 2,0, 0\n");
        fprintf(pipe, "set zlabel \"M_{0} / [10^{12} solar masses]\" offset 2,0, 0\n");
        fprintf(pipe, " set cbrange [1:3000]\n");
        fprintf(pipe, " set cbtics ('1' 1, '10' 10, '10^{2}' 100, '10^{3}' 1000)\n");
        fprintf(pipe, " set mcbtics (2,3,4,5,6,7,8,9,20,30,40,50,60,70,80,90,200,300,400,500,600,700,800,900,2000,3000)\n");
        
        // fprintf(pipe, " set zrange [0.01:10000]\n");

        if (GRAPH_TYPE == 1)
        {
            if (AXIS_TYPE == 1) fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/M_Z.eps'\n");
            else fprintf(pipe, "set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/M_Z_log.eps'\n");
            fprintf(pipe, " set title \"{/Symbol D} XMM-XCS    {/Symbol \321} XMM-LSS    {/ZapfDingbats=m} MCXC    {/ZapfDingbats=o} PCCS-SZ\"  offset -2, 0, 0\n");
            fprintf(pipe, " set ylabel \"M_{500}(z)  [10^{12} solar masses]\"  offset -2, 0, 0\n");
            fprintf(pipe, " set yrange [1:3000]\n");
            fprintf(pipe, " set ytics ('1' 1, '10' 10, '10^{2}' 100, '10^{3}' 1000)\n");
            fprintf(pipe, " set mytics (2,3,4,5,6,7,8,9,20,30,40,50,60,70,80,90,200,300,400,500,600,700,800,900,2000,3000)\n");

            fprintf(pipe, "splot '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/DELTA_M.txt' u 1:6:7 ls 7 notitle  w pm3d, \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/MCXC.txt' u 1:2:(0.01) pt 65 ps 0.5 linecolor rgb 'black' title 'MCXC' , \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/XMM-XCS_z_M_L.txt' u 1:2:(0.01) pt 66 ps 0.5 linecolor rgb 'black' title 'XMM-XCS' ,\
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/XMM-LSS_z_M_L.txt' u 1:2:(0.01) pt 67 ps 0.5 linecolor rgb 'black' title 'XMM-LSS', \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/planck_z_M_L.txt' u 1:2:(0.01) pt 64 ps 0.5 linecolor rgb 'black'  title 'PCCS-SZ'  \n");
        }

        else if (GRAPH_TYPE == 2)
        {
            if (AXIS_TYPE == 1) fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/M_ratio.eps'\n");
            else fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/M_ratio_log.eps'\n");
            fprintf(pipe, " set xrange [0.001:14]\n");
            fprintf(pipe, " set ylabel \"M_{z}/M_{0}\n");
            fprintf(pipe, "splot '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/DELTA_M.txt' u 1:8:7 ls 7 notitle  w pm3d \n");
        }
    }

    else
    {
        fprintf(pipe, " set cntrparam levels 5\n");
        fprintf(pipe, "set zlabel \"L_{0} / 10^{44}ergss^{-1}\" offset 0,0, 0\n");
        fprintf(pipe, "set cblabel \"L_{0} / 10^{44}ergss^{-1}\" offset 0,0, 0\n");
        fprintf(pipe, " set cbrange [0.001:100]\n");

        //fprintf(pipe, " set cbrange [0.01:10000]\n");
        //fprintf(pipe, " set zrange [0.01:10000]\n");

        if (GRAPH_TYPE == 1)
        {
            if (AXIS_TYPE == 1) fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/L_Z.eps'\n");
            else fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/L_Z_log.eps'\n");

            fprintf(pipe, " set ylabel \"L_{500}(z)/10^{44}ergss^{-1}\n");
            fprintf(pipe, " set yrange [0.001:100]\n");

            fprintf(pipe, "splot '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/DELTA_M.txt' u 1:3:4  ls 7 notitle w pm3d,\
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/MCXC.txt' u 1:3:(0.01) pt 65 ps 0.5 linecolor rgb 'black' title 'MCXC', \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/XMM-XCS_z_M_L.txt' u 1:3:(0.01) pt 66 ps 0.5 linecolor rgb 'black' title 'XMM-XCS', \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/XMM-LSS_z_M_L.txt' u 1:3:(0.01) pt 67 ps 0.5 linecolor rgb 'black' title 'XMM-LSS', \
                '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/planck_z_M_L.txt' u 1:3:(0.01) pt 64 ps 0.5 linecolor rgb 'black' title 'PCCS-SZ'  \n");
        }

        else if (GRAPH_TYPE == 2)
        {
            if (AXIS_TYPE == 1) fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/L_ratio.eps'\n");
            else fprintf(pipe, " set output '/Users/cosimacalder/OneDrive/Year_4/Project/Lit_Review/Figures/L_ratio_log.eps'\n");
            fprintf(pipe, " set xrange [0.001:14]\n");
            fprintf(pipe, " set ylabel \"L_{z}/L_{0}\n");
            fprintf(pipe, "splot '/Users/cosimacalder/OneDrive/cos_transfer/J_PROJECT/work/work/DELTA_M.txt' u 1:9:4 ls 7 notitle  w pm3d \n");
        }

    }

    fflush(pipe);
    fprintf(pipe, "exit \n");
    pclose(pipe);
}