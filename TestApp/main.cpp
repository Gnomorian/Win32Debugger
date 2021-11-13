#pragma warning(suppress:5050) // suppress debug crt bug. https://developercommunity.visualstudio.com/t/warning-c5050-when-using-stl-modules-and-one-of-md/873364
import Logger;

int main()
{
	Utils::Logger logger{"./testApp.log"};
	logger.log("Hello, World!");
}