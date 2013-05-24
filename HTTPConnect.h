/*
 * Connection.h
 *
 *  Created on: 13 mai 2013
 *      Author: gdr
 */

#ifndef HTTPCONNECT_H_
#define HTTPCONNECT_H_


#include <matime.h>
#include <MAUtil/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/Layout.h>
#include <MAUI/EditBox.h>
#include <MAUI/Font.h>
#include <NativeUI/Widgets.h>
#include <MAUtil/Connection.h>

#include <Wormhole/HighLevelHttpConnection.h>
#include <Wormhole/MessageStreamJSON.h>
#include <mastdlib.h>



#define BUFSIZE 1024


using namespace Wormhole;
using namespace MAUtil;
using namespace NativeUI;
class HTTPConnect : public HighLevelHttpConnection
{
public:
	/**
	 * Initialize the application in the constructor.
	 */
	HTTPConnect();
	virtual ~HTTPConnect() {}

	void connectUrl(String url, String fct, Widget* ptr);

	void parsingJSON();

	void dataDownloaded(MAHandle , int );


private:

	String fonction;
	char mBuffer[BUFSIZE];
	 bool mIsConnected;
	 int count;
	 String contentString;
//	 AlertTab* pointeur;
};

#endif /* HTTPCONNECTION_H_ */