/////////////////////////////////////////////
// Vector.hpp
// Name : Nicholas Cheng
// CS Login: nicholasc
//
// Partner's Name (as listed in Canvas) : 
//
////////////////////////////////////////////

#ifndef VECTOR_HPP
#define VECTOR_HPP

/**
 * @brief this class derives from runtime_error
 *        It is thrown in the case of Non-postive matrix dimensions
 */
class IndexOutOfBoundsException : public std::runtime_error {
public:
    // DO NOT MODIFY THIS CLASS
    IndexOutOfBoundsException() : std::runtime_error("vector index out of bounds")
    {// no other code in the constructor
    }
};


/**
 * @brief Vector is a templated sequence container that uses dynamic size arrays.
 */
template <typename T>
class Vector
{
private:
    T * elements;         // an array of T, accessed by a pointer
    std::size_t capacity; // amt of storage allocated
    std::size_t size;     // current number of elements
    // we are going to use an initial_size that is ridiculously small
    // in order to test the ability to resize
    static const std::size_t initial_size = 4;

public:
    typedef T* iterator;  // allows us to use 'iterator' as a type
    typedef const T* const_iterator;
    
    /**
     * @brief Default Constructor.
     */
    Vector(){
        capacity = initial_size;
        elements = new T [initial_size];
        size = 0;
        }

    /**
     * @brief Copy Constructor.
     * @param other The vector from which we should copy all data members
     */
    Vector(const Vector &other) {
        // similar to operator= but with fewer lines of code
        // and no 'if' statement needed
    }

    /**
     * @brief Copy Assignment Operator.
     * @param other the vector on the RHS of the assignment.
     * @return A reference to the vector on the LHS.
     */
    Vector &operator=(const Vector &other) {
        if (this != &other) { // this avoids deletion of elements
            capacity = other.capacity;
            size = other.size;
            delete[] elements;
            elements = new T[capacity];
            // TODO use a for loop to copy the data from other.elements into elements

            return *this;
        }
    }


    /**
     * @brief Destructor.
     */
    ~Vector() {
        std::cout << "Destructor called" << std::endl; // leave this here !
        // TODO:  add one more line of code to prevent a memory leak
    }

    /**
     * @brief Gets the size of this vector
     * @return The number of elements in the container.
     */
    size_t Size() const {
        // TODO: write this code
    }

    /**
     * @brief Checks if the container is empty.
     * @return true if the container is empty, false otherwise.
     */
    bool Empty() const {
        // TODO: write this code    
    }

    /**
     * @brief Gets the capacity of this vector
     * @return The number of elements that can be held in currently allocated storage.
     */      
    size_t Capacity() const{
        // TODO: write this code
    }
   /**
     * @brief Overloaded array subscripting operator without bounds checking
     * @param pos The position of the element to access.
     * @return A reference to the element at specified location pos.
     */
    T &operator[](std::size_t index) {
        return elements[index];
    }

    /**
     * @brief Const overload of the overloaded array subscripting operator.
     * @param pos The position of the element to access.
     * @return A const reference to the element at specified location pos.
     */
    const T &operator[](std::size_t index) const {
        return elements[index];
    }

    /**
     * @brief Removes the last element of the container if it exists.
     *        The capacity of the vector is unchanged.
     *        If there are no elements in the container, then do nothing.
     */
    void Pop_Back() {
        // hint:  just modify size
        // TODO: write this code
        }
    }

    /**
     * @brief Begin iterator.
     * @return An iterator to the first element.
     */
    iterator Begin() {
        return elements;
    }

    /**
     * @brief End iterator.
     * @return An iterator to one past the last element.
     */
    iterator End() {
        // TODO: write this.... just need one line of code
    }

    /**
     * @brief Begin iterator.
     * @return A const iterator to the first element.
     */
    const_iterator Begin() const {
        return elements;
    }

    /**
     * @brief End iterator.
     * @return A const iterator to one past the last element.
     */
    const_iterator End() const {
        // same as the other End() function
        // TODO: write this code
    }

   /**
     * @brief Adds an element to the end.
     *        If there is no space to add an element, 
     *            capacity of the vector is doubled
     *            and data and memory are managed
     * @param elem The element to be added.
     */
    void Push_Back(T thing){
        if (size < capacity){
            elements[size] = thing;
            size++;
        }
        // TODO: complete this code
        else{ 
        }
    }


     /* @brief Removes all elements from the container.
     *        Leaves the capacity of the vector unchanged
     */
    void Clear() {
        size = 0; 
    }
    

    /**
     * @brief Erases an element at pos and updates size
     *        Assume that the iterator is valid for this vector
     * @param pos iterator to the element to remove.
     *         Hint: Use pointers to slide the array items down
     *               You do not need to use delete or new
     */
    void Erase(iterator posToDelete) {
        // hint:  use pointers to slide the array items to the left
        //        you do not need to use delete or new
        // TODO: write this code  
    }

    /**
     * @brief Access specified element with bounds checking.
     * @param pos The position of the element to access.
     * @return A reference to the element at specified location pos, with bounds checking.
     * @throw IndexOutOfBoundsException if out of range
     */
    T &At(std::size_t pos) {
        // TODO: you need to add a check to throw something here
        return elements[pos];
    }

    /**
     * @brief Access specified element with bounds checking.
     * @param pos The position of the element to access.
     * @return A const reference to the element at specified location pos, with bounds checking.
     * @throw IndexOutOfBoundsException if out of range
     */
    const T &At(std::size_t pos) const {
        // TODO: same as the non-const version    
    }

    /**
     * @brief standard friend function for operator<<
     * @param os the stream you are calling << with
     * @param v the vector you are trying to output
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector<T> &v) {
        // do not change this function....it will affect your output !
        for (int i=0; i < v.size; ++i){
            os << v.elements[i] << ", ";
        }
        return os;
    }
};


#endif 
