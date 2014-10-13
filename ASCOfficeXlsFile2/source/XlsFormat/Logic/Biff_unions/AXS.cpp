#include "precompiled_xls.h"
#include "AXS.h"
#include <Logic/Biff_records/IFmtRecord.h>
#include <Logic/Biff_records/Tick.h>
#include <Logic/Biff_records/FontX.h>
#include <Logic/Biff_records/AxisLine.h>
#include <Logic/Biff_records/LineFormat.h>
#include <Logic/Biff_records/AreaFormat.h>
#include <Logic/Biff_unions/GELFRAME.h>
#include <Logic/Biff_unions/SHAPEPROPS.h>
#include <Logic/Biff_records/TextPropsStream.h>
#include <Logic/Biff_records/ContinueFrt12.h>

namespace XLS
{;


AXS::AXS()
{
}


AXS::~AXS()
{
}


//  (AxisLine LineFormat)
class Parenthesis_AXS_1: public ABNFParenthesis
{
	BASE_OBJECT_DEFINE_CLASS_NAME(Parenthesis_AXS_1)
public:
	BaseObjectPtr clone()
	{
		return BaseObjectPtr(new Parenthesis_AXS_1(*this));
	}

	const bool loadContent(BinProcessor& proc)
	{
		if(!proc.mandatory<AxisLine>())
		{
			return false;
		}
		proc.mandatory<LineFormat>();
		return true;
	};
};



BaseObjectPtr AXS::clone()
{
	return BaseObjectPtr(new AXS(*this));
}


/*
AXS = [IFmtRecord] [Tick] [FontX] *4(AxisLine LineFormat) [AreaFormat] [GELFRAME] *4SHAPEPROPS 
		[TextPropsStream *ContinueFrt12]
*/
const bool AXS::loadContent(BinProcessor& proc)
{
	proc.optional<IFmtRecord>();
	proc.optional<Tick>();
	proc.optional<FontX>();
	proc.repeated<Parenthesis_AXS_1>(0, 4);
	proc.optional<AreaFormat>();
	proc.optional<GELFRAME>();
	proc.repeated<SHAPEPROPS>(0, 4);
	if(proc.optional<TextPropsStream>())
	{
		proc.repeated<ContinueFrt12>(0, 0);
	}
	
	return true;
}

} // namespace XLS

