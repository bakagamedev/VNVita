#pragma once

class DirectoryInfo
{
private:
SceUID uid;

private:
static bool isUidValid(SceUID uid)
{
return (uid >= 0);
}

public:
DirectoryInfo(const char * directoryName)
{
this->uid = sceIoDopen(directoryName);
}

~DirectoryInfo(void)
{
if(isUidValid(this->uid))
{
if(sceIoDclose(this->uid) < 0)
{
 // Throw exception
}
}
}

bool isValid(void) const
{
return isUidValid(this->uid);
}

SceUID getUID(void) const
{
return this->uid;
}
};
