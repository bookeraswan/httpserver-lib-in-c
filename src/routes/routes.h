#include "routing-methods.h"

#define NUM_ROUTES 3


Route routes[] = {
    {"/", route_root},
    {"/counter", counter},
    {"/404", route_404}
};