#ifndef TRUEBOOLARRAY_H
#define TRUEBOOLARRAY_H


class TrueBoolArray
{
    public:
        /** Default constructor */
        TrueBoolArray(int length);
        /** Default destructor */
        virtual ~TrueBoolArray();

        bool operator[](int i) { return arr[i >> 3] >> (char)(i & 7); };
        //bool set1(int i) { return arr[i >> 3] |= (char)(i & 7) };
        //bool set0(int i) { return arr[i >> 3] &= (char)(^i)}

    protected:


    private:
        unsigned char* arr;
};

#endif // TRUEBOOLARRAY_H
