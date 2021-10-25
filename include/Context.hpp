/**
 * @file Context.h
 * @author mcantrero
 * */

#include <iostream>
#include <vector>

#include "TextTable.hpp"

using namespace std;

#ifndef __CONTEXT__
#define __CONTEXT__

class Context {
        private:
                size_t nObj, nProp; /**< Number of objects and properties in the context. */
                vector<string> attributes; /**< Vector of properties in the context. */
                vector<string> objects; /**< Vector of objects in the context. */
                vector<vector<bool>> table; /**< Binary table that represents the context. */

        public:
                /**
                 * @brief Default constructor.
                 */
                Context();
                /**
                 * @brief Constructor.
                 * @param data The binary matrix that represents the context.
                 * @param objects Vector of all objects of the context
                 * @param attributes Vector of all attributes of the context
                 */
                Context(vector<vector<bool>> data, vector<string> obj, vector<string> attr);               
                Context(vector<vector<bool>> data);

                size_t getNObjects() const {return nObj;}

                size_t getNAttributes() const {return nProp;}

                vector<string> getObjects() const { return objects;}
                vector<int> getObjectsVector();


                vector<string> getAttributes() const { return attributes;}
                vector<int> getAttributesVector();

                vector<vector<bool>> getTable() const { return table;}

                bool getIncidence(int i, int j);

                void objectPrime(vector<int> &objset, vector<int> &objPrime);

                void attributePrime(vector<int> &attrset, vector<int> &attributePrime);
               
                void objectDoublePrime(vector<int> &objset, vector<int> &objDPrime);

                void attributeDoublePrime(vector<int> &attrset, vector<int> &attributeDPrime);

};

/**
 * @brief Output operator.
 * @parem os Output stream.
 * @param c The context to be printed.
 * @return The output stream.
 * */
ostream& operator<<(ostream& os, Context& c);

#endif

