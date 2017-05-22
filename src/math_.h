//
// Created by tazi on 2017/5/9.
//

#ifndef LMS_MATH_H
#define LMS_MATH_H
template <typename T>
T row_vector_mutiply(T* lhs,T*rhs,int num)
{
    T res = 0;
    for(int i = 0;i<num;i++)
    {
       res += lhs[i]*rhs[i];
    }
    return res;
}
#endif //LMS_MATH_H
