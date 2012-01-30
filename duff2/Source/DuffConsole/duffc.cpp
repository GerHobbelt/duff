// duffc.cpp : Defines the entry point for the console application.
//
#include <winbase.h>

#include "stdafx.h"
#include <conio.h>
#include "..\FileProcessor.h"

typedef CFileProcessor * (*FuncPtr)();


int main(int argc, char* argv[])
{
	printf("Loading Plugins...\n");

	HINSTANCE hInstance = LoadLibrary("d:\\doc\\cpp\\duff\\Debug\\plugins\\savelist.dll");
 FuncPtr MyFunc;
 bool Loaded = false;
 CFileProcessor * pProcessor;
 if (hInstance)
	{
		MyFunc = (FuncPtr) GetProcAddress(hInstance, "GetProcessorPtr");
  if (MyFunc)
		{	
			
			pProcessor = MyFunc();
			if (pProcessor)
			{
			//	m_ProcessPage.AddProcessor(hInstance,pProcessor);
		  Loaded = true;
			}
		}
	}
	
	if ( Loaded )
	{
		printf("Loaded '%s' %s plugin (%s)\n", pProcessor->GetName(), "processor","savelist.dll");
//		Count++;
	}
	else
	{
		printf("Skipping non-plugin DLL: %s\n", "savelist.dll");
	}
	//Log(Msg);

 printf("Finished loading plugins.\n");
	printf("\n_DUFF Console_\n\n");
	printf("0. configure file comparison layers\n");
	printf("1. configure directories\n");
	printf("2. configure filters\n");
	printf("3. configure markers\n");
	printf("4. configure processors\n");
	
	printf("\n");
	printf("s. start search\n");
	printf("c. configure options\n");
	printf("x. exit\n");

	printf("\nChoice: ");
 getch();
	return 0;
}

