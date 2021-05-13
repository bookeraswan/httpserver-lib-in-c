#ifndef ROUTE_STRUCT
#define ROUTE_STRUCT
typedef struct{
    char url[MAX_URL_LEN];
    void (*logic)(Request, Response*);
}Route;
#endif