#include <crow.h>
#include "src/routes/reservationRoutes.h"

int main() {
    crow::SimpleApp app;
    
    // Configurar rutas
    setupReservationRoutes(app);
    
    // Configurar CORS si necesitas
    app.port(8080).multithreaded().run();
    
    return 0;
}