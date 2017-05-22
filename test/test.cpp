#include <iostream>
#include <random>
#include "LMS.h"
#include <math.h>


void print_average_error_nd();
void print_average_error_sin();


int main() {
    //print_average_error_sin();
    print_average_error_nd();
    return 0;
}

//输出正态分布误差
void print_average_error_nd()
{
    const int FS = 10000;
    double average = 0;
    double average_raw = 0;
    double diff = 0;
    double diff_raw = 0;
    double data[3] ={0};
    LMS<double> predictor(3,0.001);


    double noise[10000] = {0};
    std::default_random_engine generator;
    std::normal_distribution<double> dis(0, 1);
    for(int i = 0 ; i< 10000;i++)
    {
        noise[i] = dis(generator);
    }

    double signal[10000] = {0};
    for(int i=0;i<10000;i++)
    {
        signal[i] = sin(10.0*3.1415*i/FS);
    }


    Adaptive_Filter_In<double> in;
    Adaptive_Filter_Out<double> out;
    for(int i = 2;i<10000;i++)
    {

        for(int j=0;j<3;j++)
        {
            data[j] = noise[i-j];
        }
        in.x_ptr = data;
        in.d = 0.2*noise[i]+ signal[i];
        predictor.generateNPValue(&in,&out);

        std::cout<<i<<":"<<out.error<<std::endl;
        diff = (signal[i]-out.error)/signal[i];
        diff_raw =(0.2*noise[i])/signal[i];
        average+= diff>=0?diff:-diff;
        average_raw += diff_raw>=0?diff_raw:-diff_raw;
    }
    std::cout<< "average_raw:" << average_raw/10000<<std::endl;
    std::cout<< "average:" << average/10000<<std::endl;
}
//输出单音正弦误差
void print_average_error_sin()
{
    LMS<double> predictor(3,0.0001);
    double average = 0;
    double diff = 0;
    double data[16] ={0};
    const int FS = 10000;
    double signal[10000] = {0};
    for(int i=0;i<10000;i++)
    {
        signal[i] = sin(2.0*3.1415*i/FS)+2*sin(2.0*3.14*5.0*i/FS);
    }
    Adaptive_Filter_In<double> in;
    Adaptive_Filter_Out<double> out;
    for(int i = 16;i<9999;i++)
    {
        for(int j=0;j<16;j++)
        {
            data[j] = signal[i-j];
        }
        in.x_ptr = data;
        in.d = *(signal+i+1);
        predictor.generateNPValue(&in,&out);
        diff = out.error/(*(signal+i+1));
        //std::cout<< diff  <<std::endl;
        average+= diff>=0? diff:(-diff);

    }
    average = average/10000;
    std::cout<< "average:" << average <<std::endl;
}