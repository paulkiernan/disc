#include "Geometry.h"
#include "Logging.h"

CGeometry::CGeometry()
{
}

CGeometry::CGeometry(CFrame* frame)
{
    Log.infoln("CGeometry::CGeometry: Initializing geometry");
}

CGeometry::~CGeometry()
{
    Log.infoln("CGeometry::~CGeometry: Destructing geometry");
}

void CGeometry::Continue()
{
}
