//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NAME: Erchard Samoh
// EMAIL: esamoh000@citymail.cuny.edu
// FILE: sequence2.cpp
// HEADER: sequence2.h
// CLASS IMPLEMENTED: sequence
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <cassert> // for assert function
#include <algorithm> //for copy function
#include "sequence2.h" //include header file with class definition

using namespace std;

namespace main_savitch_4
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEFAULT CAPACITY is constant at 30.
    const sequence::size_type sequence::DEFAULT_CAPACITY;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEFAULT CONSTRUCTOR: sequence class initialized as an empty sequence
    sequence::sequence(size_type initial_capacity)
    {
        data_ptr = new value_type[initial_capacity];
        CAPACITY = initial_capacity;
        m_current_index = 0;
        m_used = 0;
    }
    // COPY CONSTRUCTOR: sequence class initialized as a copy of instance of sequence class known as source
    // the new copy will hold same items and have the same capacity as the source object
    sequence::sequence(const sequence &source)
    {
        data_ptr = new value_type[source.CAPACITY];
        CAPACITY = source.CAPACITY;
        m_used = source.m_used;
        m_current_index = source.m_current_index;
        copy(source.data_ptr, source.data_ptr + m_used, data_ptr); // copy function from <algorithm>, used to copy elements within a range
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DESTRUCTOR: deallocate and release memory for the class object
    sequence::~sequence()
    {
        delete [] data_ptr;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // MODIFICATION MEMBER FUNCTIONS:
    // resize(): changes the current capacity of a sequence class to a new capacity, resizing the sequence
    void sequence::resize(size_type new_capacity)
    {
        value_type *new_array;
        if (new_capacity == CAPACITY)
        {
            return;
        }
        if (new_capacity < m_used)
        {
            new_capacity = m_used;
        }
        new_array = new value_type[new_capacity];
        copy(data_ptr, data_ptr + m_used, new_array); // copy function from <algorithm>, used to copy elements within a range
        delete [] data_ptr;
        data_ptr = new_array;
        CAPACITY = new_capacity;
    }
    // start(): first item in sequence becomes current item, at index of 0
    void sequence::start()
    {
        m_current_index = 0;
    }
    // advance(): if the current item was the last item in sequence, there is no longer any current item after.
    // otherwise, new current item is after the last current item, advancing the current_index by 1
    void sequence::advance()
    {
        assert(is_item());
        m_current_index++;
    }
    // insert(): an entry is added before the current item in the sequence,
    // if there is no current item (empty sequence),
    // then it is the first item in the sequence.
    // both cases, new item is the current item of the sequence!
    void sequence::insert(const value_type& entry)
    {
        size_type i;
        if (m_used == CAPACITY)
        {
            resize(CAPACITY + 1);
        }
        if (!is_item())
        {
            m_current_index = 0;
        }
        for (i = m_used; i > m_current_index; --i)
        {
            data_ptr [i] = data_ptr [i-1];
        }
        data_ptr [m_current_index] = entry;
        m_used++;
    }
    // attach(): adds a new item in the sequence AFTER the current item
    // if no current item, the new entry is attached to the end of the sequence
    // both cases, new item is the current item of the sequence
    void sequence::attach(const value_type& entry)
    {
        size_type i;
        if (m_used == CAPACITY)
        {
            resize(CAPACITY + 1);
        }
        if (!is_item())
        {
            data_ptr[m_current_index] = entry;
            m_used++;
        }
        else
        {
            for (i = m_used; i > m_current_index; --i) {
                data_ptr[i] = data_ptr[i - 1];
            }
            m_current_index++;
            data_ptr[m_current_index] = entry;
            m_used++;
        }
    }
    // remove_current(): remove current item from the sequence,
    // the current item becomes the item after the previously
    // removed item
    void sequence::remove_current()
    {
        assert(is_item()); // precondition: is_item() is true
        size_type i;
        for (i = m_current_index + 1; i < m_used; ++i)
        {
            data_ptr [i-1] = data_ptr [i];
        }
        m_used--;
    }
    // OVERLOADED OPERATOR for assignment "="
    void sequence::operator=(const sequence &source)
    {
        value_type *new_array;
        if (this == &source) // check for self-assignment
        {
            return;
        }
        if (CAPACITY != source.CAPACITY)
        {
            new_array = new value_type[source.CAPACITY];
            delete [] data_ptr;
            data_ptr = new_array;
            CAPACITY = source.CAPACITY;
        }
        m_current_index = source.m_current_index;
        m_used = source.m_used;
        copy(source.data_ptr, source.data_ptr + m_used, data_ptr); // copy function from <algorithm>, used to copy elements within a range
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CONSTANT MEMBER FUNCTIONS:
    // size(): returns the number of items within a sequence
    sequence::size_type sequence::size() const
    {
        return m_used;
    }
    // is_item(): checks if there is a current item that is valid
    bool sequence::is_item() const
    {
        if (m_current_index < m_used && m_current_index >= 0)
            return true;
        else
            return false;
    }
    // current(): returns the current item in sequence
    sequence::value_type sequence::current() const
    {
        assert(is_item()); // precondition: is_item() is true
        return data_ptr[m_current_index];
    }
}