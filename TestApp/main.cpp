#include <logger.h>

int main()
{
	Logger logger{ "./testApp.log" };
	logger.log("blah de blah");
}