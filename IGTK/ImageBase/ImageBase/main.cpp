// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include "ImageBase.h"
#include "ScopedTimer.h"
#include <Windows.h>
#include "CursorGuard.h"

int main()
{
	{
		std::string path = "path";
		
		IGTK::ImageBaseColor imageColor;
		printf("Object 1 was created\n\n");
		imageColor.SetName("Object 1");

		IGTK::ImageBaseColor imageColorB(path);
		printf("Object 2 was created\n\n");
		imageColorB.SetName("Object 2");

		IGTK::ImageBaseColor imageColorC(imageColorB);
		printf("Object 3 was created\n\n");
		imageColorC.SetName("Object 3");

		IGTK::ImageBaseGrayscale imageGrayscale;
		printf("Object 4 was created\n\n");
		imageGrayscale.SetName("Object 4");
	}

	{
		ScopedTimerWithExtraMember time;
		printf("Object destruction has begun\n");
	}
		_getch();
	{
		printf("\n\nTesting creation of new pointers:\n\n");
		printf("New pointer object created.\n");
		IGTK::CursorGuard<int> iPtr(new int(5));
		printf("Count read from first pointer object:%d\n", iPtr.GetRefCount());
		printf("New pointer object created based on first pointer.\n");
		IGTK::CursorGuard<int> iPtr2(iPtr);
		printf("Count read from first pointer object:%d\n", iPtr.GetRefCount());
		printf("New pointer object created based on second pointer.\n");
		IGTK::CursorGuard<int> iPtr3(iPtr2);
		printf("Count read from first pointer object:%d\n", iPtr.GetRefCount());
		printf("New pointer object created based on first pointer.\n");
		IGTK::CursorGuard<int> iPtr4(iPtr);
		printf("Count read from first pointer object:%d\n", iPtr.GetRefCount());
		printf("Frst pointer was set to point to a different location.\n");
		iPtr.SetNewPointer(new int(6));
		printf("Count read from first pointer object:%d\n", iPtr.GetRefCount());
		printf("Count read from second pointer object:%d\n", iPtr2.GetRefCount());
		printf("Value stored in each pointer:%d,%d,%d,%d\n", *iPtr, *iPtr2, *iPtr3, *iPtr4);
		printf("Value stored in each pointer:%d,%d,%d,%d\n", *iPtr, *iPtr2, *iPtr3, *iPtr4);

		IGTK::ColorPixel* c = new IGTK::ColorPixel();
		IGTK::CursorGuard<IGTK::ColorPixel> cPtr(c);
		printf("\n\nTesting -> operator:\n\n");
		printf("Value stored in each member before use of ->:%d,%d,%d\n", cPtr->m_r, cPtr->m_g, cPtr->m_b);
		cPtr->m_r = 1;
		cPtr->m_g = 2;
		cPtr->m_b = 3;
		printf("Value stored in each member:%d,%d,%d\n\n", cPtr->m_r, cPtr->m_g, cPtr->m_b);

		printf("\n\nTesting * operator:\n\n");

		printf("Value stored in iPtr:%d before use of *\n", *iPtr);
		*iPtr = 9;
		printf("Value stored in iPtr:%d \n\n", *iPtr);

		IGTK::CursorGuard<int> iPtr5(new int(7));
		iPtr5.SetNewPointer(new int(8));

		IGTK::CursorGuard<int> iPtr6(new int(4));

		IGTK::CursorGuard<int> iPtr7(nullptr);

		IGTK::CursorGuard<int> iPtr8(new int(3));

		iPtr8.Invalidate();

		printf("\n\nTesting == operator:\n\n");

		printf("Valid pointer compared to equivalent valid pointer:%d\n", iPtr2 == iPtr3);
		printf("Valid pointer compared to different valid pointer:%d\n", iPtr == iPtr3);
		printf("Valid pointer compared to nullptr:%d\n", iPtr == nullptr);
		printf("Valid pointer compared to valid pointer set to null:%d\n", iPtr == iPtr7);
		printf("Valid pointer compared to invalid pointer:%d\n\n", iPtr == iPtr8);

		iPtr2.Invalidate();

		iPtr.Invalidate();

		iPtr5.SetNewPointer(nullptr);

		printf("Invalid pointer compared to valid pointer:%d\n", iPtr == iPtr6);
		printf("Invalid pointer compared to nullptr:%d\n", iPtr == nullptr);
		printf("Invalid pointer compared to valid pointer set to null:%d\n", iPtr == iPtr5);
		printf("Invalid pointer compared to invalid pointer:%d\n\n", iPtr == iPtr2);

		printf("Valid pointer set to null compared to valid pointer:%d\n", iPtr5 == iPtr6);
		printf("Valid pointer set to null compared to nullptr:%d\n", iPtr5 == nullptr);
		printf("Valid pointer set to null compared to valid pointer set to null:%d\n", iPtr5 == iPtr7);
		printf("Valid pointer set to null compared to invalid pointer:%d\n", iPtr5 == iPtr2);

		iPtr5.SetNewPointer(new int(10));

		printf("\n\nTesting invalidation of pointers:\n\n");

		printf("iPtr2 was invalidated and points to the same location as iPtr3 and iPtr4\n\n");
		printf("Is iPtr2 valid:%d\n", iPtr2.IsValid());
		printf("Is iPtr3 valid:%d\n", iPtr3.IsValid());
		printf("Is iPtr4 valid:%d\n\n", iPtr4.IsValid());

		printf("New pointer iPtr9 was created based on iPtr2\n\n");
		IGTK::CursorGuard<int> iPtr9(iPtr2);
		printf("Is iPtr9 valid:%d\n", iPtr9.IsValid());

		_getch();
	}

	_getch();

    return 0;
}

