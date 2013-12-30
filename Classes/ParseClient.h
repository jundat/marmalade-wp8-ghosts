#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ParseClient : public CCObject
{
public:
	static ParseClient* sharedParseClient() {
		if (_instance == NULL)
		{
			_instance = new ParseClient();
		}

		return _instance;
	}
	
	char* m_appId;
	char* m_restId;
	std::vector<std::string> m_header;

	void setAppId(char* appId) {
		m_appId = appId;
		_calculateHeader();
	}

	void setRestId(char* restId) {
		m_restId = restId;
		_calculateHeader();
	}

	char* getAppId() {
		return m_appId;
	}

	char* getRestId() {
		return m_restId;
	}

	//pSelector = void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
	void callCloudFunction(char* funcName, char* jsonData, SEL_HttpResponse pSelector, char* tag = NULL);

private:
	static ParseClient* _instance;
	ParseClient() {
		m_appId = "DKD7iIw2O7Ibkj6Du9LOI12338fOFkweFTgQR9CX";
		m_restId = "diKwmJku4gdSOoTCICb8VjBn6xjqTbJanIrztF9f";
		_calculateHeader();
	}

	void _calculateHeader() {
		CCString* s1 = CCString::createWithFormat("X-Parse-Application-Id: %s", m_appId);
		CCString* s2 = CCString::createWithFormat("X-Parse-REST-API-Key: %s", m_restId);

		m_header.push_back(std::string(s1->getCString())); //appid
		m_header.push_back(std::string(s2->getCString())); //apikey
		m_header.push_back(std::string("Content-Type: application/json"));
	}
};

#endif //__CLIENT_H__
