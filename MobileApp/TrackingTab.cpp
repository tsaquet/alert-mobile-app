/*
 * TrackingTab.cpp
 *
 *  Created on: 13 mai 2013
 *      Author: gdr
 */

#include "TrackingTab.h"

/**
 * Constructor.
 */
TrackingTab::TrackingTab(int language, String loginToken) :
		Screen(), LANGUAGE(language), _LOGINTOKEN(loginToken) {

	// Set title and icon of the stack screen.
	setTitle(Convert::tr(TRACKING_ALERT_TAB_EN + LANGUAGE));
//			setBackgroundColor(255,255,255);
	createUI();
}

/**
 * Destructor.
 */
TrackingTab::~TrackingTab() {

}

void TrackingTab::runTimerEvent() {
	String urlTmp = HOST;
	urlTmp += "/alerts/tracking/messages";
	//		urlTmp += "/plugins/1/informations";
	urlTmp += _LOGINTOKEN;
	urlTmp += "&media=1";
	lprintfln(urlTmp.c_str());
	connectUrl(urlTmp, TRACKING_LIST);

	lprintfln("timer");
}

void TrackingTab::dataDownloaded(MAHandle data, int result) {
	lprintfln("dataDownloaded trackingTab");
	mIsConnected = false;
	this->close();
	if (result == RES_OK) {
		connERR = 0;
		char * jsonData = new char[maGetDataSize(data) + 1];
								maReadData(data, jsonData, 0, maGetDataSize(data));
				String jsonTmp = jsonData;
				Convert::formatJSONBeforeParse(jsonTmp);

				MAUtil::YAJLDom::Value* root = YAJLDom::parse((const unsigned char*) jsonTmp.c_str(), maGetDataSize(data));


		parseJSONTrackingAlert(root);
		//this->close();
	} else if (result == CONNERR_DNS) {
		connERR++;
		lprintfln("AlertTab DataDownload result = %d", result);
		lprintfln("DNS resolution error.");
	} else {
		connERR++;
		lprintfln("TrackingTab DataDownload result = %d", result);
	}
	if(connERR >= 3)
	{
		getSystemConnection();
		String sMessage = "Connection ERROR. ERREUR:";
		sMessage += Convert::toString(result);
		maMessageBox("Connection Error", sMessage.c_str() );
	}
}

void TrackingTab::parseJSONTrackingAlert(MAUtil::YAJLDom::Value* root) {
//	char * jsonData = new char[maGetDataSize(data) + 1];
//	maReadData(data, jsonData, 0, maGetDataSize(data));
//
//	String Tmp = jsonData;
//
//	MAUtil::YAJLDom::Value* root = YAJLDom::parse(
//			(const unsigned char*) jsonData, maGetDataSize(data));
	// Traverse the Json tree and print data.
	// Check that the root is valid.
	// The root type should have type with above data ARRAY.
	if (NULL == root || YAJLDom::Value::NUL == root->getType()
			|| YAJLDom::Value::ARRAY != root->getType()) {
		lprintfln("Root node is not valid\n");

	} else {
		lprintfln("Root node is valid :) \n");
	}

	lprintfln("%d\n", root->getNumChildValues());

	STime lastSendAlertTmp;
	if(root->getNumChildValues() > 0)
	{
		MAUtil::YAJLDom::Value* valueTmp0 = root->getValueByIndex(0);
		String dateTmp = valueTmp0->getValueForKey("send_date")->toString();
		lastSendAlertTmp = Convert::toSTime(dateTmp);
	}


	if (lastSendAlertTmp > lastSendAlert) {
//		Screen::setMainWidget(new ActivityIndicator());
		Screen::removeChild(mainLayout);

		for(int idx1 = 0; idx1 < mapLVITA.size(); idx1++)
		{
			lValert->removeChild(mapLVITA[idx1]);
		}

	for (int idx = 0; idx <= root->getNumChildValues() - 1; idx++) {
		MAUtil::YAJLDom::Value* valueTmp = root->getValueByIndex(idx);

		mapTrackingAlertDate[idx] =
				valueTmp->getValueForKey("send_date")->toString();
		lprintfln(mapTrackingAlertDate[idx].c_str());
//		dateTmp1 = valueTmp->getValueForKey("send_date")->toString();
//
//		lastSendAlertTmp = Convert::toSTime(dateTmp1);
//		if (bCreateUI) {
//		if (idx == 0) {
//			String dateTmp = valueTmp->getValueForKey("send_date")->toString();
//			lastSendAlertTmp = Convert::toSTime(dateTmp);
//		}

		if(!bCreateUI)
		{
			String dateTmp1 = valueTmp->getValueForKey("send_date")->toString();
			STime lastSendAlertTmp1 = Convert::toSTime(dateTmp1);
//			lprintfln("%d %d %d %d %d %d", lastSendAlertTmp1.year,lastSendAlertTmp1.mon,lastSendAlertTmp1.day,lastSendAlertTmp1.hour,lastSendAlertTmp1.min,lastSendAlertTmp1.sec);
			if(lastSendAlertTmp1>lastSendAlert)
			{
//				lprintfln("%d %d %d %d %d %d", lastSendAlertTmp1.year,lastSendAlertTmp1.mon,lastSendAlertTmp1.day,lastSendAlertTmp1.hour,lastSendAlertTmp1.min,lastSendAlertTmp1.sec);
//				lprintfln("%d %d %d %d %d %d", lastSendAlert.year,lastSendAlert.mon,lastSendAlert.day,lastSendAlert.hour,lastSendAlert.min,lastSendAlert.sec);
				notification = new LocalNotification();
				notification->setContentBody(valueTmp->getValueForKey("content")->toString().c_str());
				lprintfln(valueTmp->getValueForKey("content")->toString().c_str());
					// Set some platform specific values.

					if (getPlatform() == ANDROID) {
						// Set the vibration duration to 5seconds when an alert is displayed.
						notification->setVibrate(true);
						notification->setVibrateDuration(5);
						// Set notification title and ticker.
				//				    notification->setContentTitle("My message title");
						notification->setTickerText("Nouvelle alerte");
					} else {
						// Set a badge number.
						notification->setBadgeNumber(6);
						// Set the title of the action button or slider.
						notification->setAlertAction("ok");
					}
					NotificationManager::getInstance()->unscheduleLocalNotification(notification);
					NotificationManager::getInstance()->scheduleLocalNotification(notification);
			}
		}

			mapHLTA[idx] = new HorizontalLayout();
			mapLTAHeure[idx] = new Label((mapTrackingAlertDate[idx]));
			mapLTAHeure[idx]->setBackgroundColor(0x666666);
			mapLTAHeure[idx]->setWidth(110);
			mapHLTA[idx]->addChild(mapLTAHeure[idx]);
			mapLTADesc[idx] = new Label(
					valueTmp->getValueForKey("content")->toString().c_str());
			mapHLTA[idx]->addChild(mapLTADesc[idx]);
			mapLVITA[idx] = new ListViewItem();
			mapLVITA[idx]->addChild(mapHLTA[idx]);

			lValert->addChild(mapLVITA[idx]);
		}

		lastSendAlert = lastSendAlertTmp;
		if (bCreateUI) {
			bCreateUI = false;
		}
		Screen::setMainWidget(mainLayout);
	}
}

void TrackingTab::createUI() {
	bCreateUI = true;
	String urlTmp = HOST;
	urlTmp += "/alerts/tracking/messages";
//		urlTmp += "/plugins/1/informations";
	urlTmp += _LOGINTOKEN;
	urlTmp += "&media=1";
	lprintfln(urlTmp.c_str());

	connectUrl(urlTmp, TRACKING_LIST);
	mainLayout = new VerticalLayout();
	// Make the layout fill the entire screen.
	mainLayout->fillSpaceHorizontally();
	mainLayout->fillSpaceVertically();
	// Add the layout as the root of the screen's widget tree.
//	Screen::setMainWidget(new ActivityIndicator());
		Screen::setMainWidget(mainLayout);
//	VerticalLayout* vl = new VerticalLayout();
//
//	        vl->addChild(new ActivityIndicator());
//
//
//	        vl->setChildHorizontalAlignment("center");
//	        vl->setChildVerticalAlignment("center");

	lValert = new ListView();
	mainLayout->addChild(lValert);
//	lprintfln("%d",maShowVirtualKeyboard());
}

void TrackingTab::connectUrl(String url, eTrakingTab fct) {
	//verifie si on est connecté
//		MACellInfo ci;
//		int res;
//		res = maGetCellInfo(&ci);
//		lprintfln("maGetCellInfo: %i\n", res);
//		lprintfln("MCC: %s\n", ci.mcc);
//		lprintfln("MNC: %s\n", ci.mnc);
//		lprintfln("LAC: %i\n", ci.lac);
//		lprintfln("CellId: %i\n", ci.cellId);
//		lprintfln("connecter ou pas ? %d ", maNetworkStatus());
	lprintfln("connectUrl");
	if (mIsConnected == false) {
		mIsConnected = true;
		fonction = fct;
		this->get(url.c_str());
	} else {
		lprintfln("Déjà connecté: %d", fonction);
	}
}

//void TrackingTab::drawChangeVerticalHorizontal(int width, int height) {
//
//	if (width < height) // Landscape
//			{
//		setTitle(Convert::getString(TRACKING_ALERT_TAB_EN));
//	} else // Portrait
//	{
//		setTitle("");
//		setIcon(LOGO);
//	}
//}