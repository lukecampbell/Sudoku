// SudokuStack.hpp - Template Class for Sudoku Stack implementation
// Luke Campbell
// 13 Nov 11

#ifndef SUDOKUSTACK_H_
#define SUDOKUSTACK_H_


template<class _T>
class SudokuStack
{
private:
    class Cell
    {
    public:
        _T data;
        Cell *next;
        Cell(_T data, Cell *next) :
            data(data), next(next)
        {
        }
    };
    Cell *head;
    unsigned int size;
public:

    SudokuStack();
    ~SudokuStack();

    _T pop();
    _T top()   const;
    _T peek()  const;
    _T at(int) const;
    void push(_T);
    unsigned int length() const;
    bool empty() const;

};
//-----------------------------------------------------------------------------
// SudokuStack()
// Initializes a blank stack
template<class _T>
SudokuStack<_T>::SudokuStack()
:head(NULL), size(0)
{

}
//-----------------------------------------------------------------------------
// ~SudokuStack()
// Frees all the allocated cells
template<class _T>
SudokuStack<_T>::~SudokuStack()
{
    _T tmp;
    while(!empty())
    {
        tmp = pop();
        delete tmp;
    }
}
//-----------------------------------------------------------------------------
// pop()
// returns the top value and pops the cell off the stack
template<class _T>
_T SudokuStack<_T>::pop()
{
    Cell *tmp = head;
    _T ret = head->data;
    head = head->next;
    delete tmp;
    size--;
    return ret;
}
//-----------------------------------------------------------------------------
// top()
// Returns the top element on the stack
template<class _T>
_T SudokuStack<_T>::top() const
{
    _T ret = head->data;
    return ret;
}
//-----------------------------------------------------------------------------
// peek()
// Returns the top element on the stack
template<class _T>
_T SudokuStack<_T>::peek() const
{
    _T ret = head->data;
    return ret;
}
//-----------------------------------------------------------------------------
// push()
// Pushes an element on the stack
template<class _T>
void SudokuStack<_T>::push(_T data)
{
    Cell *tmp = new Cell(data,head);
    head = tmp;
}
//-----------------------------------------------------------------------------
// at()
// Returns an elment at the specified index of the stack
// Warning there is no bounds checking, unpredictable behaviour can occur
// if request parameter is outside of bounds of stack
template<class _T>
_T SudokuStack<_T>::at(int n) const
{
    _T ret;
    Cell *scan = head;
    int i=0;
    for(i=0;i<n && scan; i++)
        scan = scan->next;
    if(scan)
        ret = scan->data;
    return ret;
}
//-----------------------------------------------------------------------------
// length()
// returns the number of elements in the stack
template<class _T>
unsigned int SudokuStack<_T>::length() const
{
    return size;
}
//-----------------------------------------------------------------------------
// empty()
// Returns a boolean for whether or not the stack contains elements
template<class _T>
bool SudokuStack<_T>::empty() const
{
    if(head)
        return false;
    return true;
}


#endif /* SUDOKUSTACK_H_ */
