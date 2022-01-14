//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NAME: Erchard Samoh
// EMAIL: esamoh000@citymail.cuny.edu
// FILE: sequence1.cpp
// HEADER: sequence1.h
// CLASS IMPLEMENTED: sequence
// INVARIANT for the sequence class:
//  1. number of items in the sequence is defined by the member variable m_m_used
//  2. index of current item of the sequence is defined by the member variable m_current_index
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "sequence1.h" // provides header file with class definitions + functions declarations
#include <cassert> // assert function

namespace main_savitch_3
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CONSTRUCTOR: for sequence class to initialize as an empty sequence
    sequence::sequence()
    {
        m_used = 0; // default value for used
        m_current_index = 0; // default value for current_index
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // MODIFICATION MEMBER FUNCTIONS:
    // start(): first item in sequence becomes current item, at index of 0
    void sequence::start()
    {
        m_current_index = 0;
    }
    // advance(): if the current item was the last item in sequence, there is no longer any current item after.
    // otherwise, new current item is after the last current item, advancing the current_index by 1
    void sequence::advance()
    {
        assert(is_item()); //precondition: is_item is true
        m_current_index++;
    }
    // insert(): an entry is added before the current item in the sequence, if there is no current item (empty sequnce),
    // it is the first item in the sequence. both cases, new item is the current item of the sequence!
    void sequence::insert(const value_type &entry)
    {
        assert(size() < CAPACITY); // precondition: size() < CAPACITY
        size_type i;
        if (!is_item())
        {
            m_current_index = 0;
        }
        for (i = m_used; i > m_current_index; --i)
        {
            data [i] = data [i-1];
        }
        data[m_current_index] = entry;
        m_used++;
    }
    // attach(): adds a new item in the sequence AFTER the current item
    // if no current item, the new entry is attached to the end of the sequence
    // both cases, new item is the current item of the sequence
    void sequence::attach(const value_type &entry)
    {
        assert(size() < CAPACITY); // precondition: size() < CAPACITY
        size_type i;
        if(!is_item())
        {
            data[m_current_index] = entry;
            m_used++;
        }
        else
        {
            for (i = m_used; i > m_current_index; --i) {
                data[i] = data[i - 1];
            }
            m_current_index++;
            data[m_current_index] = entry;
            m_used++;
        }
    }
    // remove_current(): remove current item from the sequence, the current item becomes the item after the previously
    // removed item
    void sequence::remove_current()
    {
        assert(is_item()); // precondition: is_item() is true
        size_type i;
        for (i = m_current_index + 1; i < m_used; ++i)
        {
            data [i-1] = data [i];
        }
        m_used--;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CONSTANT MEMBER FUNCTIONS:
    // size(): returns the number of items in the entire sequence
    sequence::size_type sequence::size() const
    {
        return m_used;
    }
    // is_item(): checks if there is a current item that is valid
    bool sequence::is_item() const
    {
        if(m_current_index < m_used)
        {
            return true;
        }
        else
            return false;
    }
    // current(): returns the current item in the sequence
    sequence::value_type sequence::current() const
    {
        assert(is_item()); // precondition: is_item() is true
        return data[m_current_index];
    }

}




