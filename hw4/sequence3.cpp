//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NAME: Erchard Samoh
// EMAIL: esamoh000@citymail.cuny.edu
// FILE: sequence3.cpp
// HEADER: sequence3.h
// LINKED LIST TOOLKIT: node1.h
// CLASS IMPLEMENTED: sequence class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// INVARIANT
// head_ptr: pointer to the first node of the linked list
// tail_ptr: pointer to the last node of the linked list
// cursor: current item of sequence linked list
// precursor: item before current item of the linked list
// many_nodes: how many elements/nodes there are in the linked list
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <cassert> // Provides assert function
#include <cstdlib> // Provides size_t and NULL
#include "node1.h" // Provides linked list toolkit
#include "sequence3.h" // Provides sequence class

namespace main_savitch_5
{
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEFAULT CONSTRUCTOR: sequence class initialized as an empty sequence
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    sequence::sequence()
    {
        m_head_ptr = NULL;
        m_tail_ptr = NULL;
        m_cursor = NULL;
        m_precursor = NULL;
        m_many_nodes = 0;
    }
    // COPY CONSTRUCTOR: sequence class initialized as a copy of instance of sequence class known as source
    // the new copy will hold same items and have the same capacity as the source object
    // linked list time analysis: O(n)
    // dynamic array analysis: O(n)
    sequence::sequence(const sequence &source)
    {
        node *ptr;
        list_copy(source.m_head_ptr, m_head_ptr, m_tail_ptr);
        m_many_nodes = source.m_many_nodes;
        m_cursor = m_head_ptr;
        m_precursor = NULL;
        ptr = source.m_head_ptr;
        while(ptr != NULL && ptr != source.m_cursor)
        {
            ptr = ptr->link();
            m_precursor = m_cursor;
            m_cursor = m_cursor->link();
        }
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DESTRUCTOR: deallocate and release memory for the class object
    // linked list time analysis: O(n)
    // dynamic array analysis: O(n)
    sequence::~sequence()
    {
        list_clear(m_head_ptr);
        m_many_nodes = 0;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // MODIFICATION MEMBER FUNCTIONS:
    // start(): first item in linked list becomes current item
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    void sequence::start()
    {
        m_cursor = m_head_ptr;
        m_precursor = NULL;
    }
    // advance(): goes to next item in the sequence, that item is now the current item
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    void sequence::advance()
    {
        assert(is_item());
        m_precursor = m_cursor;
        m_cursor = m_cursor->link();
    }
    // insert(): an entry is added before the current item,
    // if there is no current item (empty sequence),
    // then it is the first item in the sequence (head node).
    // both cases, new item is the current item of the sequence!
    // many_nodes increments by 1
    // linked list time analysis: O(1)
    // dynamic array analysis: O(n)
    void sequence::insert(const value_type &entry)
    {
        if(!is_item())
        {
            list_head_insert(m_head_ptr, entry);
            m_precursor = NULL;
            m_cursor = m_head_ptr;
        }
        else
        {
            if(m_cursor == m_head_ptr)
            {
                list_head_insert(m_head_ptr, entry);
                m_cursor = m_head_ptr;
                m_precursor = NULL;
            }
            else
            {
                list_insert(m_precursor, entry);
                m_cursor = m_precursor->link();
            }
        }
        m_many_nodes++;
    }
    // attach(): adds a new item in the sequence AFTER the current item
    // if no current item, the new entry is attached to the end of the sequence
    // both cases, new item is the current item of the sequence
    // linked list time analysis: O(1)
    // dynamic array analysis: O(n)
    void sequence::attach(const value_type &entry)
    {
        if(is_item())
        {
            list_insert(m_cursor, entry);
            m_precursor = m_cursor;
            m_cursor = m_cursor->link();
        }
        else
        {
            if(m_precursor == NULL)
            {
                list_head_insert(m_head_ptr, entry);
                m_cursor = m_head_ptr;
                m_precursor = NULL;
            }
            else
            {
                m_cursor = list_locate(m_head_ptr, list_length(m_head_ptr));
                list_insert(m_cursor, entry);
                m_cursor = m_precursor->link();
            }
        }
        m_many_nodes++;
    }
    // remove_current(): remove current item from the sequence,
    // the current item becomes the item after the previously
    // removed item
    // linked list time analysis: O(1)
    // dynamic array analysis: O(n)
    void sequence::remove_current()
    {
        assert(is_item());
        if(m_precursor == NULL)
        {
            list_head_remove(m_head_ptr);
            m_cursor = m_head_ptr;
            m_precursor = NULL;
        }
        else
        {
            m_cursor = m_cursor->link();
            list_remove(m_precursor);
        }
        m_many_nodes--;
    }
    // OVERLOADED OPERATOR for assignment "="
    // linked list time analysis: O(n)
    // dynamic array analysis: O(n)
    void sequence::operator=(const sequence &source)
    {
        if(this == &source) // check for self-assignment
        {
            return;
        }
        list_clear(m_head_ptr);
        list_copy(source.m_head_ptr, m_head_ptr, m_tail_ptr);
        m_many_nodes = source.size();
        m_cursor = m_head_ptr;
        m_precursor = NULL;
        node* move = source.m_head_ptr;
        while(move != NULL && move != source.m_cursor)
        {
            move = move->link();
            m_precursor = m_cursor;
            m_cursor = m_cursor->link();
        }
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CONSTANT MEMBER FUNCTIONS:
    // size(): returns number of nodes/items in the sequence linked list
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    sequence::size_type sequence::size() const
    {
        return m_many_nodes;
    }
    // is_item(): checks if there is a current item/node that is valid
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    bool sequence::is_item() const
    {
        return (m_cursor != NULL && size() > 0);
    }
    // current(): returns current item in the sequence linked list
    // linked list time analysis: O(1)
    // dynamic array analysis: O(1)
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return m_cursor->data();
    }
}