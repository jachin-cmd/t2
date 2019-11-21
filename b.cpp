#include<iostream>
#include<string>
#include"tinyxml.h"
using namespace std;

enum SuccessEnum { FALLURE, SUCCESS };
TiXmlDocument doc;
TiXmlElement *root;
TiXmlElement *elem;
TiXmlElement *e2;
TiXmlElement *e1;
TiXmlElement *e3;
TiXmlElement *e4;
char car;
const char* modelName = "routes";
const char* tagName = "tag_routes";
int num;
string g_appid;
string attr_id;
const char * def_attr_tag;
const char * def_attr_model;
const char *attr_tag;
const char *attr_model;
const char* eleName;
string::size_type idx;
static int status;
static int status2;
SuccessEnum sttr(const char* csttr)
{
	if (!doc.LoadFile(csttr))
	{
		cerr << doc.ErrorDesc() << endl;
		//cout << "11" << endl;
		return FALLURE;
	}
	root = doc.FirstChildElement();
	if (root == NULL)
	{
		cerr << "Failed to load file:NO root element." << endl;
		return FALLURE;
	}

	cout << "请输入要查询的appid: " << endl;
	cin >> g_appid;
	while (g_appid.size() < 8)
	{
		cout << "输入appid太短，请重新输入appid:" << endl;
		cin >> g_appid;
	}
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		eleName = elem->Value();
		//cout << eleName << endl;

		if (strcmp(eleName, modelName) == 0)
		{
			e3 = elem->FirstChildElement();
			for (e4 = e3->FirstChildElement(),status=0; e4 != NULL; e4 = e4->NextSiblingElement())
			{
				attr_id = e4->Attribute("subappid");
				//cout << attr_id<<endl;;
				//cout << g_appid << endl;
				idx = attr_id.find(g_appid);
				if (idx != string::npos)
				{
					attr_model = e4->Attribute("subappid_default_model_ids");
					cout << "模块号（model_ids）:" << attr_model << endl;
					status = 1;
				}
			}
			if (status == 0)
			{
				def_attr_model = elem->Attribute("all_default_model_ids");
				cout << "模块号为默认：" << def_attr_model << endl;
			}
		}
		if (strcmp(eleName, tagName) == 0)
		{
			e1 = elem->FirstChildElement();
			for (e2 = e1->FirstChildElement(),status2=0; e2 != NULL; e2 = e2->NextSiblingElement())
			{
				attr_id = e2->Attribute("subappid");
			
				idx = attr_id.find(g_appid);
				if (idx != string::npos)
				{
					attr_tag = e2->Attribute("subappid_default_tag_srv");
					if (attr_tag == 0)
					{
						cout << "xml文件出错，请检查" << attr_id << "所在的行" << endl;
						break;
					}
					else
					{
						cout << "标签号 (tag_srv):" << attr_tag << endl;
						status2 = 1;
					}
				}
			}
			if (status2 == 0)
			{
				def_attr_tag = elem->Attribute("all_default_tag_srv");
				cout << "标签号为默认：" << def_attr_tag << endl;


			}
			//cout << endl;
		}
	}
}
int main()
{
	
	while (1)
	{
		cout << "*********************************   search   **********************************" << endl;
		cout << "                1、通用（srv_cfg_common_online）" << endl;
		cout << "                2、rcp（srv_cfg_rcp_online）" << endl;
		cout << "                3、vip（srv_cfg_vip_online）" << endl;
		cout << "-------------请输入要查询的接口（1、2、3）：";
		cin >> num;
		if (num == 1)
		{
			sttr("srv_cfg_common_online.xml");
			continue;
		}
		else if (num == 2)
		{
			sttr("srv_cfg_rcp_online.xml");
			continue;
		}
		else if (num == 3)
		{
			sttr("srv_cfg_vip_online.xml");
			continue;
		}
		else {
			while (cin.get() != '\n')
			{
				cin.clear();
			}
			cout << "请按要求输入..." << endl;
		}
		//sttr("srv_cfg_rcp_online.xml");
	}
	return 0;
}
