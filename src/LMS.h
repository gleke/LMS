//
// Created by tazi on 2017/4/27.
//

#ifndef LMS_LMS_H
#define LMS_LMS_H

#include <iostream>
#include <cstring>
#include "Adaptive_Filter.h"
#include "math_.h"
template <typename T>
class LMS {
private:

    int norder;     //滤波器阶数
    T cfactor;      //滤波器收敛因子
    T* ratios_ptr;      //滤波器参数序列
    T* ratios_forward_ptr;      //上一采样时间滤波器参数
public:
    LMS(int n,T f):norder(n),cfactor(f){      //初始化参数及序列
        ratios_ptr = new T[norder];
        memset(ratios_ptr,0,norder*sizeof(T));
        
        ratios_forward_ptr = new T[norder];
        memset(ratios_forward_ptr,0,norder*sizeof(T));
    };

    ~LMS(){     //释放序列内存空间
        delete[](ratios_ptr);
        delete[](ratios_forward_ptr);
    }

    void generateNPValue(Adaptive_Filter_In<T> *lms_in, Adaptive_Filter_Out<T>* lms_out){       //噪声信号值估计
        //获得瞬时误差估计   e(k) = d(k) - x'(k)w(k)
        static T correction = 0;
        lms_out->y = row_vector_mutiply(lms_in->x_ptr,ratios_ptr,norder);
        lms_out->error = lms_in->d - lms_out->y;

        correction =  cfactor* lms_out->error;        //计算系数修正值

        memcpy(ratios_forward_ptr,ratios_ptr,norder* sizeof(T));        //保存上一时刻滤波器系数

        //更新滤波器系数
        for(int i = 0;i<norder;i++)
        {
            ratios_ptr[i] = ratios_forward_ptr[i] + correction*lms_in->x_ptr[i];
        }
    };

    int getNOrder(){ return norder;};       //获取滤波器阶数
    T getCFactor(){return cfactor;};        //获取滤波器收敛因子

};




#endif //LMS_LMS_H
