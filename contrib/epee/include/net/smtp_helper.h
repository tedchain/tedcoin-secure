#pragma once
#include "smtp.h"

namespace epee
{
namespace net_utils
{
	namespace smtp
	{

		inline bool send_mail(const std::string& server, int port, const std::string& login, const std::string& pass, const std::string& from_addres, const std::string& from_name, const std::string& maillist, const std::string& subject, const std::string& mail_body)
		{
			net_utils::smtp::CSMTPClient smtp;

			if ( !smtp.ServerConnect( server.c_str(), port ) )
			{
				LOG_PRINT("Reporting: Failed to connect to server " << server <<":"<< port, LOG_LEVEL_0);
				return false;
			}

			if(login.size() && pass.size())
			{
				if ( !smtp.ServerLogin( login.c_str(), pass.c_str()) )
				{
					LOG_PRINT("Reporting: Failed to auth on server " << server <<":"<< port, LOG_LEVEL_0);
					return false;

				}
			}

			if ( !smtp.SendMessage( from_addres.c_str(),
				from_name.c_str(),
				maillist.c_str(),
				subject.c_str(),
				"bicycle-client",
				(LPBYTE)mail_body.data(),
				mail_body.size()))
			{
				char *szErrorText = smtp.GetLastErrorText();
				if ( szErrorText )
				{
					LOG_PRINT("Failed to send message, error text: " << szErrorText, LOG_LEVEL_0);
				}
				else
				{
					LOG_PRINT("Failed to send message, error text: null", LOG_LEVEL_0);
				}
				return false;
			}

			smtp.ServerDisconnect();

			return true;


		}
	}
}
}