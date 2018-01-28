#include "Client.h"
#include "Global/CGlobal.h"

void                exitSignal(int)
{
    CGlobal::Instance()->quit = true;
    CGlobal::Instance()->_Service->stop();
}

void                signalsHandler()
{
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = exitSignal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}


int                 main()
{
    Client          myClient;

    signalsHandler();

  if (myClient.Initialize("192.168.43.111", 8887) == -1)
        return (-1);
    myClient.Run();

    return (0);
}
