#ifndef _document_hpp
#define _document_hpp

#include "util.hpp"


class Document {
    private:
        std::vector<int> features;
        int nFeatures;

    public:
        Document(int _nFeatures); // Number of features a document has.
        void initFeatures(int _nFeatures, int value);
        void initFeatures(std::vector<int> vFeatures);
};

#endif
