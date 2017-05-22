//
// Created by tazi on 2017/5/8.
//

#ifndef LMS_ADAPTIVE_FILTER_H
#define LMS_ADAPTIVE_FILTER_H
template <typename T>
struct Adaptive_Filter_In
{
    T *x_ptr;         //指向输入数组矢量X的指针
    T d;                //输入参考数据
};


//定义输出参数结构体
template <typename T>
struct Adaptive_Filter_Out
{
    T y;                //滤波器的输出
    T error;        //误差输出
};


#endif //LMS_ADAPTIVE_FILTER_H
