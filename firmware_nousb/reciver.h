int recv_iteration();
int recv_initialize();

// Max of length message (bytes)
#define MSGMAXLEN 2
// Max of IR sensors count
#define SENSORS   8

extern uint8_t recv[MSGMAXLEN*SENSORS]; // 2 -- bytes on messag; 8 -- IR sensors
