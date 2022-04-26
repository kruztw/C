#include <rpc/rpc.h>
#include "math.h"

int * add_2_svc(var, svc)
vars *var;
struct svc_req *svc;
{
       static int result;
       result = var->a + var->b;
       return(&result);
}

int * sub_2_svc(var, svc)
vars *var;
struct svc_req *svc;
{
       static int result;
       result = var->a - var->b;
       return(&result);
}
