/*
 * HomeTab.cpp
 *
 *  Created on: 14 mai 2013
 *      Author: gdr
 */


#include "HomeTab.h"
//#include <MAUtil/Moblet.h>


	/**
	 * Constructor.
	 */
	HomeTab::HomeTab(int language): Screen(), LANGUAGE(language)
	{
//		char buffer[2500];
//MAHandle XML = maFileOpen("alert.xml",MA_ACCESS_READ);
//maFileRead(xmlFile, buffer, 2500);
//		int len = maGetDataSize(XML);
//			        char xmlbuffer[len + 1];
//			        maReadData(XML, xmlbuffer, 0, len);
//			        xmlbuffer[len] = '\0'; //Null terminator
//			        LOG("XML Input:");
//			        LOG("xmlbuffer");

			        // 2. Create an XML reader and parse the XML into it.
//			        AMXml::XmlReader xr;
//			        AMXml::XmlDocument* xml = xr.parseXML(xmlbuffer);

//			        LOG("Xml Parsed");
//			        LOG("RootNode '%s'", xml->rootNode->getName().c_str());

			        // 3. Create an XML writer, and write the XML out again
//			        XmlWriter xw;
//			        String outputxml = xw.toFragment(xml->rootNode);
//
//			        LOG("Xml written");
//			        LOG(outputxml.c_str());
//
//			        printf("Press zero or back to exit\n");
//		AMXml::XmlDocument test1("alert.xml");
//
//		AMXml::XmlReader test(UTF8);
//		test.

		// Set title and icon of the stack screen.
//		maGetImageData()
//		setIcon(LOGO);
//		char * testData = new char[maGetDataSize(TEST_STRING) + 1];
//										maReadData(TEST_STRING, testData, 0, maGetDataSize(TEST_STRING));



		setTitle(Convert::tr(HOME_TAB_EN + LANGUAGE));
			setBackgroundColor(255,255,255);
			createUI();
	}

	/**
	 * Destructor.
	 */
	HomeTab::~HomeTab()
	{

	}

	void HomeTab::dataDownloaded(MAHandle data , int result)
		{
			lprintfln("dataDownloaded HomeTab");

		//this->close();
		}

	void HomeTab::createUI()
	{

	}

//	void HomeTab::drawChangeVerticalHorizontal(int width, int height)
//	{
//
//	if (width > height) // Landscape
//			{
//		setTitle(Convert::getString(HOME_TAB_EN));
//	} else // Portrait
//	{
//		setTitle("");
//		setIcon(LOGO);
//	}
//	}

