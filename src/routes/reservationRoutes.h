#ifndef RESERVATIONROUTES_H
#define RESERVATIONROUTES_H

#include <crow.h>
#include <crow/middlewares/cors.h>

void setupReservationRoutes(crow::App<crow::CORSHandler>& app);

#endif