#ifndef PAIR_H
#define PAIR_H


class Pair
{
    public:
        /** Default constructor */
        Pair(int val);
        Pair(int val, Pair* key);
        /** Default destructor */
        virtual ~Pair();

        int getVal() { return this->val; };
        int setVal(int val) { return this->val = val; };
        Pair* getKey() { return this->key; };
        Pair* setKey(Pair* key) { return this->key = key; };

    protected:

    private:
        int val;
        Pair* key;
};

#endif // PAIR_H
