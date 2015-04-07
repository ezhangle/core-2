#pragma once

#include "Chpx.h"

namespace ASCDocFileFormat
{
	class ChpxFkp : public IStreamWriter
	{
	public:
		static const unsigned short CHPX_FKP_SIZE	=	512;
		static const unsigned char CHPX_FKP_MAX_CRUN			=	0x65;

		ChpxFkp(const vector<unsigned int>& inRgfc, const vector<Chpx>& arrChpxs) : crun(0)
		{
			crun = arrChpxs.size();
			rgfc = inRgfc;

			unsigned long chpxSizeInBytes = 0;

			chpxs.push_back( arrChpxs[0] );
			chpxSizeInBytes = chpxs[0].Size();
			rgb.push_back( (unsigned char)( ( CHPX_FKP_SIZE - 1 - chpxSizeInBytes ) / 2 ) );

			for (int i = 1; i < crun; ++i)
			{
				chpxs.push_back( arrChpxs[i] );
				chpxSizeInBytes = chpxs[i].Size();
				rgb.push_back( (unsigned char)( rgb[i-1] - 1 - ( chpxSizeInBytes / 2 ) ) );
			}
		}

		virtual ~ChpxFkp()
		{
		}

		//
		virtual unsigned char* GetBytes(unsigned long* size) const
		{
			unsigned char* bytes = NULL;

			if ( size != NULL )
			{
				*size = 512;
				bytes = new unsigned char[*size];

				if ( bytes != NULL )
				{
					memset( bytes, 0, *size );

					int i = 0;

					for (; i < (crun + 1); ++i)
					{
						FormatUtils::SetBytes((bytes + (i * sizeof(rgfc[i]))), (int)rgfc[i]);
					}

					i = (crun + 1) * sizeof(rgfc[i]);

					unsigned char *chpxsbytes = NULL;
					unsigned long chpxssize = 0;

					for (int j = 0; j < crun; ++j, ++i)
					{
						bytes[i]			=	rgb[j];
						unsigned char *chpxsbytes	=	chpxs[j].GetBytes(&chpxssize);

						if ( chpxsbytes != NULL )
						{
							memcpy((bytes + ( bytes[i] * 2 ) ), chpxsbytes, chpxssize);
							RELEASEARRAYOBJECTS (chpxsbytes);
						}
					}

					bytes[511] = crun;
				}
			}

			return bytes;
		}

		inline unsigned int GetEndOffset() const
		{
			return (*(rgfc.end() - 1));
		}

		//
		static vector<ChpxFkp> GetAllChpxFkps(const vector<unsigned int>& inRgfc, const vector<Chpx>& arrChpxs)
		{
			vector<ChpxFkp>			allChpxFkps;
			vector<unsigned int>	rgfc;
			vector<Chpx>			chpxs;

			rgfc.push_back( inRgfc[0] );
			unsigned int allChpxsSize = 0;
			unsigned int rgfcCount = 2;

			for (unsigned int i = 0; i < arrChpxs.size(); ++i)
			{
				unsigned int chpxSize = arrChpxs[i].Size();
				allChpxsSize += chpxSize;

				//Check if all rgfcs and rgbs + Chpxs less then 512 bytes
				if ( ( ( rgfcCount * sizeof(unsigned int) + ( rgfcCount - 1 ) * sizeof(unsigned int) ) >= ( CHPX_FKP_SIZE / 2 ) ) ||
					( allChpxsSize >= ( CHPX_FKP_SIZE / 2 ) ) )
				{
					ChpxFkp chpxFkp(rgfc, chpxs);
					allChpxFkps.push_back(chpxFkp);
					rgfc.clear();
					chpxs.clear();
					rgfc.push_back(inRgfc[i]);
					allChpxsSize	=	chpxSize;
					rgfcCount		=	2;
				}

				rgfc.push_back(inRgfc[i+1]);
				chpxs.push_back(arrChpxs[i]);
				++rgfcCount;
			}

			if (!rgfc.empty() && !chpxs.empty())
			{
				ChpxFkp chpxFkp(rgfc, chpxs);
				allChpxFkps.push_back(chpxFkp);

				rgfc.clear();
				chpxs.clear();
			}

			return allChpxFkps;
		}

	private:

		unsigned char					crun;

		vector<unsigned int>	rgfc;
		vector<unsigned char>			rgb;
		vector<Chpx>			chpxs;
	};
}