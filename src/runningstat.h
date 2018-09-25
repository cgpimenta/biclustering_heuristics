#ifndef STAT_H
#define STAT_H

#include <cmath>


class RunningStat{
private:
    int m_n;
    double m_oldM, m_newM, m_oldS, m_newS;

public:
    RunningStat() : m_n(0) {}

    void Clear(){
        m_n = 0;
    }

    void Push(double x);

    inline int NumDataValues() const { return m_n; }

    inline double Mean() const {
        return (m_n > 0) ? m_newM : 0.0;
    }

    inline double Variance() const {
        return ( (m_n > 1) ? m_newS/(m_n - 1) : 0.0 );
    }

    inline double StandardDeviation() const {
        return sqrt( Variance() );
    }
};

#endif