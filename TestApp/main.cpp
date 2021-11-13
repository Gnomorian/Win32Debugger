#include <logger.h>

int main()
{
	Logger logger{ "./testApp.log" };
	logger.log(L"blah de blah");
}