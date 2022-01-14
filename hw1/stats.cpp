//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Provided by: Erchard Samoh
// Email Address: esamoh000@citymail.cuny.edu
// *George Wolberg Fall 2021 CCNY CSC 212*
// FILE: stats.cpp
// HEADER FILE: stats.h
// CLASS PROVIDED: statistician
//  (a class to keep track of statistics on a sequence of real numbers)
//  This class is part of the namespace main_savitch_2C.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "stats.h"
#include <cassert>

using namespace std;

namespace main_savitch_2C{

    statistician::statistician()
    { // INITIALIZING DEFAULT VALUES FOR THE LENGTH AND SUM OF THE CLASS
        m_len = 0;
        m_sum = 0;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//PUBLIC MODIFICATION MEMBER FUNCTIONS: next() and reset()
//next(): takes a double value, adds to the statistician class
//reset(): resets the statistican class, giving it default values of 0 for length, sum, max and min

    void statistician::next(double r )
    {
        m_len++;
        m_sum += r;
        if (length() == 1) {
            m_min = r;
            m_max = r;
        }
        if (r > m_max) {
            m_max = r;
        }
        if (r < m_min) {
            m_min = r;
        }
    }

    void statistician::reset()
    {
        m_len = 0;
        m_sum = 0;
        m_max = 0;
        m_min = 0;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PUBLIC CONSTANT MEMBER FUNCTIONS: length(), sum(), mean(), minimum(), maximum()
// Respectively returns the length, sum, mean, minimum, and maximum of the statistician class

    int statistician::length() const
    {
        return m_len;
    }

    double statistician::sum() const
    {
        return m_sum;
    }

    double statistician::mean() const
    {
        assert(length() > 0); //precondition: length() > 0
        return m_sum / m_len;
    }

    double statistician::minimum() const
    {
        assert(length() > 0); //precondition: length() > 0
        return m_min;
    }

    double statistician::maximum() const
    {
        assert(length() > 0); //precondition: length() > 0
        return m_max;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FRIEND FUNCTIONS: operator + (append statistician classes) and operator * (scale statistician class)

    statistician operator + (const statistician& s1, const statistician& s2)
    {
        statistician s3;
        if (s1.length() == 0)
        {
            return s2;
        }
        if (s2.length() == 0)
        {
            return s1;
        }
        s3.m_sum = s2.m_sum + s1.m_sum;
        s3.m_len = s2.m_len + s1.m_len;
        if (s1.minimum() < s2.minimum())
        {
            s3.m_min = s1.m_min;
        }
        else
        {
            s3.m_min = s2.m_min;
        }
        if (s1.maximum() > s2.maximum())
        {
            s3.m_max = s1.m_max;
        }
        else
        {
            s3.m_max = s2.m_max;
        }
        return s3;
    }

    statistician operator * (double scale, const statistician& s)
    {
        statistician t;
        double newMin, newMax;
        if (s.length() == 0)
        {
            return s;
        }
        t.m_len = s.m_len;
        t.m_sum = s.m_sum * scale;
        newMin = s.m_min * scale;
        newMax = s.m_max * scale;
        if (newMin < newMax)
        {
            t.m_min = newMin;
            t.m_max = newMax;
        }
        else
        {
            t.m_min = newMax;
            t.m_max = newMin;
        }
        return t;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NON-MEMBER FUNCTION: operator ==
// Compares two statistician classes with one another, returns a certain boolean value depending on the comparison results

    bool operator == (const statistician& s1, const statistician& s2)
    {
        bool equal = false;
        if (s1.length() != s2.length())
        {
            equal = false;
        }
        else if ((s1.length() == 0 && s2.length() == 0) || (s1.mean() == s2.mean() && (s1.sum() == s2.sum()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum())))
        {
            equal = true;
        }
        return equal;
    }
}

