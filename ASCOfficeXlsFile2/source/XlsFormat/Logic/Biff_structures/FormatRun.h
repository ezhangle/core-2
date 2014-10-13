#pragma once

#include "BiffStructure.h"
#include "FontIndex.h"

namespace XLS
{;

class CFRecord;

class FormatRun : public BiffStructure
{
	BASE_OBJECT_DEFINE_CLASS_NAME(FormatRun)
public:
	BiffStructurePtr clone();

	//virtual void setXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	//virtual void getXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	virtual void load(CFRecord& record);
	virtual void store(CFRecord& record);

private:
	unsigned __int16 ich;
	FontIndex ifnt;
};

typedef boost::shared_ptr<FormatRun> FormatRunPtr;

} // namespace XLS
