#pragma once

#include "ITextItem.h"
#include "Paragraph.h"

namespace ASCDocFileFormat
{
  class List: public ITextItem
  {
    private:
	  list<TextItemPtr> textItems;
	  short numID;
	  unsigned char level;

    protected:
	  void SetLevel( unsigned char _level );
	  void SetNumID( short _numID );

    public:
	  List( short _numID = 1 );
	  List( const list<TextItemPtr>& _textItems, short _numID = 1 );
      List( const List& _list );
	  /*Paragraphs MUST be already with LIST properties set.*/
	  void AddParagraph( const Paragraph& _paragraph );
	  /*List class sets LIST properties.*/
	  void AddTextItem( const ITextItem& _textItem );
      virtual wstring GetAllText() const;
	  virtual operator wstring() const;
	  virtual vector<TextItemPtr> GetAllParagraphsCopy() const;
	  virtual vector<ITextItem*> GetAllParagraphs();
	  virtual vector<IParagraphItemPtr> GetAllRunsCopy( vector<unsigned int>* allRunsOffsets ) const;
      virtual vector<IParagraphItemPtr> GetAllParagraphItemsCopy( vector<unsigned int>* allParagraphItemsOffsets ) const;
  	  virtual vector<PapxInFkp> GetAllParagraphsProperties( vector<unsigned int>* allParagraphsOffsets ) const;
	  virtual vector<Chpx> GetAllRunProperties( vector<unsigned int>* allRunsOffsets ) const;
	  virtual IVirtualConstructor* New() const;
	  virtual IVirtualConstructor* Clone() const;
	  virtual ~List();
  };
}