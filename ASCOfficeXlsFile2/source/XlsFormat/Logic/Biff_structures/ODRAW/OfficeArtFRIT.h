#pragma once

#include "../BiffStructure.h"

namespace XLS
{
	class CFRecord;
}

namespace ODRAW
{;

class OfficeArtFRIT : public XLS::BiffStructure
{
	BASE_OBJECT_DEFINE_CLASS_NAME(OfficeArtFRIT)
public:
	XLS::BiffStructurePtr clone();

	//virtual void setXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	//virtual void getXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	virtual void load(XLS::CFRecord& record);
	virtual void store(XLS::CFRecord& record);

public:
	unsigned __int16 fridNew;
	unsigned __int16 fridOld;
};

typedef boost::shared_ptr<OfficeArtFRIT> OfficeArtFRITPtr;


} // namespace XLS
