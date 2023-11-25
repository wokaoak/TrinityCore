#ifndef __CLY_AAVerify_H__
#define __CLY_AAVerify_H__


#include <iostream>
#include <string>

#include <fineftp/permissions.h>
#include <fineftp/fineftp_version.h>
#include <fineftp/fineftp_export.h>
#include <fineftp/server.h>

class AAVerify
{
public:
    AAVerify() {};
    ~AAVerify() {};
    static AAVerify* instance();
    std::string AA_Login();
    std::string AA_GetUUID();

    fineftp::FtpServer server;
    void AA_Ftp_Start(uint32 port, std::string path, std::string account);
    void AA_Ftp_Stop(uint32 port);
private:
};

#define sAAVerify AAVerify::instance()
#endif // __CLY_AAVerify_H__
