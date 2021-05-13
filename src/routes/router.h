#include "../lib/request.h"
#include "../lib/response.h"
#include "route.h"
#include "routes.h"



void router(Request req, Response* res){
    int number_of_routes = sizeof(routes)/sizeof(Route);
    for(int i = 0; i < number_of_routes; i++){
        int cmp = strcmp(routes[i].url, req.url);
        if(cmp == 0) return routes[i].logic(req, res);
    }
    routes[NUM_ROUTES-1].logic(req, res);
}
