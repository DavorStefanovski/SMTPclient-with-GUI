This is an app which you can connect to different SMTP servers
 
1. In order to choose your SMTP server you need to set the address and the port of the target server in the smtpmanager.cpp
smtppointer = new SmtpClient("smtp.zoho.eu", 465, SmtpClient::SslConnection);

2. There are also different type of connection types which you can use.
enum ConnectionType
    {
        TcpConnection = 0,
        SslConnection = 1,
        TlsConnection = 2      // STARTTLS
    };
3. The project contains the source for the smtpclient library and it is already configured in the CMakeLists.txt to be built and linked.