#include "luceneindex.h"
#include <QDebug>

using namespace Baloo;

LuceneIndex::LuceneIndex(const QString& path)
{
    try {
        m_indexWriter = Lucene::newLucene<Lucene::IndexWriter>(Lucene::FSDirectory::open(path.toStdWString()),
            Lucene::newLucene<Lucene::StandardAnalyzer>(Lucene::LuceneVersion::LUCENE_CURRENT),
            Lucene::IndexWriter::DEFAULT_MAX_FIELD_LENGTH);
    }
    catch (Lucene::LuceneException& e) {
         qWarning() << "Exception:" << e.getError().c_str();
    }
}

LuceneIndex::~LuceneIndex()
{

}


void LuceneIndex::addDocument(LuceneDocument& doc)
{
    addDocument(doc.doc());
}

void LuceneIndex::addDocument(Lucene::DocumentPtr doc)
{
    try {
        m_indexWriter->addDocument(doc);
    }
    catch (Lucene::LuceneException &e) {
        qWarning() << "Exception" << e.getError().c_str();
    }
}

Lucene::IndexReaderPtr LuceneIndex::IndexReader()
{
    return m_indexWriter->getReader();
}

void LuceneIndex::commit(bool optimize)
{
    try {
        if (optimize){
            m_indexWriter->optimize();
        }
        m_indexWriter->commit();
    }
    catch (Lucene::LuceneException &e) {
        qWarning() << "Exception" << e.getError().c_str();
    }
}


