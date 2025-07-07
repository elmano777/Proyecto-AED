#include <crow.h>
#include <crow/middlewares/cors.h>
#include "src/routes/reservationRoutes.h"

int main() {
    crow::App<crow::CORSHandler> app;
    
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .origin("*")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .headers("*")
        .allow_credentials()
        .max_age(3600);
    
    setupReservationRoutes(app);
    
    app.port(8081).multithreaded().run();
    
    return 0;
}