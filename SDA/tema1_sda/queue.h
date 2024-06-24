/*AVRAMONIU Calin-Stefan - 312CC*/
#ifndef QUEUE_H
#define QUEUE_H

#include "query.h"
#include "search.h"
#include "struct.h"
#include "update.h"

void pushq(Coada *q, char *comanda, char *argument);
nodComanda *popq(Coada *q);

#endif