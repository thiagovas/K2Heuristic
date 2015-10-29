#ifndef _document_hpp
#define _document_hpp

#include "util.hpp"


class Document {
    private:
        std::vector<int> features;
        int nFeatures;

    public:
        // Number of features a document has.
        Document(int _nFeatures, int defaultvalue=0);
        void initFeatures(int _nFeatures, int defaultvalue);
        void setFeature(int index, int value);
        int getFeature(int index);
};

#endif
