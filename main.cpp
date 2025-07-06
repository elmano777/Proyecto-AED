#include <crow.h>
#include <crow/middlewares/cors.h>
#include "src/routes/reservationRoutes.h"

int main() {
    // Cambiar de SimpleApp a App con CORSHandler
    crow::App<crow::CORSHandler> app;
    
    // Configurar CORS para permitir cualquier origen (desarrollo)
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors.global()
        .origin("*")  // Permite cualquier origen
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .headers("*")  // Permite cualquier header
        .allow_credentials()
        .max_age(3600);
    
    setupReservationRoutes(app);
    
    app.port(8080).multithreaded().run();
    
    return 0;
}