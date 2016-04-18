﻿#pragma once
#include "RtfParagraph.h"
#include "RtfShape.h"

class RtfOle : public IDocumentElement
{
public: 
	typedef enum{ ot_none, ot_emb, ot_link } OleType;
	
	OleType		m_eOleType;
	int			m_nShapeId;
	int			m_nWidth;
	int			m_nHeight;
	CString		m_sOleClass;
	RtfShapePtr m_oResultPic;

	RtfOle()
	{
		m_piStorage = NULL;
		SetDefault();
	}
	~RtfOle()
	{
		SetDefault();
	}
	int GetType( )
	{
		return TYPE_RTF_OLE;
	}
	bool IsValid()
	{
        return PROP_DEF != m_nWidth && PROP_DEF != m_nHeight && _T("") != m_sOleFilename;
                /*&& ::GetFileAttributes( m_sOleFilename ) != DWORD( -1 )*/
	}
	CString RenderToRtf(RenderParameter oRenderParameter)
	{
		if( false == IsValid() )
			return _T("");
		CString sResult;
		sResult.Append( _T("{\\object") );
		if( PROP_DEF != m_eOleType )
		{
			switch( m_eOleType )
			{
				case ot_emb:  sResult.Append( _T("\\objemb") );break;
				case ot_link:  sResult.Append( _T("\\objlink") );break;
			}
		}
		RENDER_RTF_INT( m_nWidth, sResult, _T("objw") );
		RENDER_RTF_INT( m_nHeight, sResult, _T("objh") );

        if( _T("") != m_sOleClass )
            sResult.AppendFormat( _T("{\\*\\objclass %ls}"), m_sOleClass.GetBuffer() );
		if( _T("") != m_sOleFilename )
        {
            CString str = RtfUtility::RtfInternalEncoder::Encode( m_sOleFilename );
            sResult.AppendFormat( _T("{\\*\\objdata %ls}"), str.GetBuffer() );
        }
		if( NULL != m_oResultPic )
		{
            CString str = m_oResultPic->RenderToRtf( oRenderParameter );
            sResult.AppendFormat( _T("{\\result \\pard\\plain%ls}"), str.GetBuffer() );
		}
		sResult.Append( _T("}") );
		return sResult;
	}
	CString RenderToOOX(RenderParameter oRenderParameter);

	void SetFilename( CString sFilename )
	{
		m_sOleFilename = sFilename;
	}
	void SetOle( POLE::Storage* piOle )
	{
		if (piOle == NULL) return;

		m_piStorage = piOle;
	}
	void SetDefault()
	{
		m_eOleType	 = ot_none;
		m_nShapeId	= PROP_DEF;
		m_nWidth	= PROP_DEF;
		m_nHeight	= PROP_DEF;
		
		RELEASEOBJECT( m_piStorage ); 
		Utils::RemoveDirOrFile( m_sOleFilename );
		m_sOleFilename = _T("");
	}
private: 
	POLE::Storage*	m_piStorage;
	CString			m_sOleFilename;

	CString RenderToOOXOnlyOle(RenderParameter oRenderParameter);
};
typedef boost::shared_ptr<RtfOle> RtfOlePtr;


#if defined (_WIN32) || defined (_WIN64)
	struct RtfOle1ToOle2Stream : OLESTREAM
	{
		BYTE* pBuffer;
		long nBufferSize;
		long nCurPos;
	};
	struct RtfOle2ToOle1Stream : OLESTREAM
	{
		std::vector<BYTE> aBuffer;
	};

	DWORD CALLBACK OleGet1(LPOLESTREAM oStream, void FAR* pTarget, DWORD dwRead);;
	DWORD CALLBACK OlePut1(LPOLESTREAM, const void FAR*, DWORD);
	DWORD CALLBACK OleGet2(LPOLESTREAM oStream, void FAR* pTarget, DWORD dwRead);;
	DWORD CALLBACK OlePut2(LPOLESTREAM, const void FAR*, DWORD);

#else
	struct RtfOle1ToOle2Stream :  POLE::Stream
	{
		BYTE* pBuffer;

		long nBufferSize;
		long nCurPos;
	};
	struct RtfOle2ToOle1Stream : POLE::Stream
	{
		std::vector<BYTE> aBuffer;
	};
#endif