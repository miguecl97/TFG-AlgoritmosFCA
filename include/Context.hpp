/**
 * @file Context.h
 * @author mcantrero
 *
 **/

#include <iostream>
#include <vector>
#include "TextTable.hpp"

using namespace std;

#ifndef __CONTEXT__
#define __CONTEXT__

class Context {
        private:
                size_t nObj, nProp; /** Number of objects and properties in the context. */
                vector<string> attributes; /** Vector of properties in the context. */
                vector<string> objects; /** Vector of objects in the context. */
                vector<vector<bool>> table; /**<Binary table that represents the relation of the context. */

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
                 * @return the new Context
                 */

                Context(vector<vector<bool>> data, vector<string> obj, vector<string> attr);
                /** 
                 * @brief  Constructor from a incidence realtion
                 * @param data The binary matrix that represents the context.
                 * @return the new Context
                */               
                Context(vector<vector<bool>> data);

                /** 
                 * @brief getter of the numbers of objects in the context
                 * @return numbers of objects
                */
                size_t getNObjects() const {return nObj;}

                /** 
                 * @brief getter of the number of attributes of the context
                 * @return number of attributes of the context
                */
                size_t getNAttributes() const {return nProp;}

                /** 
                 * @brief getter of the vector with the names of the objects 
                 * @return the vector with the names of the objects
                */
                vector<string> getObjects() const { return objects;}

                /** 
                 * @brief getter of the vector with the number of the objects
                 * @return the vector with the numebrs of the objects
                */
                vector<int> getObjectsVector();

                /** 
                 * @brief getter of the vector with the names of the attributes 
                 * @return the vector with the names of the attributes
                */
                vector<string> getAttributes() const { return attributes;}
        
                /** 
                 * @brief getter of the vector with the number of the attributes
                 * @return the vector with the numebrs of the attributes
                */
                vector<int> getAttributesVector();

                /** 
                 * @brief getter of the incidence table of the context
                 * @return the boolean table with the incidence relation of the context, true if related false if not
                */
                vector<vector<bool>> getTable() const { return table;}

                /** 
                 * @brief getter of value of relation for an object and an attirbute
                 * @param i index of the object in the table
                 * @param j index of the attribute in the table
                 * @return true if they are related, false if they are not
                */
                bool getIncidence(int i, int j);

                /** 
                 * @brief object prime operator G'
                 * @param objset vector of objects that operator affects
                 * @param objPrime vector with the result of applying operator '
                */
                void objectPrime(vector<int> &objset, vector<int> &objPrime);

                /** 
                 * @brief attribute prime operator G'
                 * @param attrset vector of attributes that operator affects
                 * @param attributePrime vector with the result of applying operator '
                */
                void attributePrime(vector<int> &attrset, vector<int> &attributePrime);
               
                /** 
                 * @brief object double prime operator G''
                 * @param objset vector of objects that operator affects
                 * @param objPrime vector with the result of applying operator ''
                */
                void objectDoublePrime(vector<int> &objset, vector<int> &objDPrime);

                /** 
                 * @brief attribute double prime operator G'
                 * @param attrset vector of attributes that operator affects
                 * @param attributePrime vector with the result of applying operator ''
                */
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

