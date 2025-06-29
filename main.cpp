#include <crow.h>
#include "src/routes/reservationRoutes.h"

int main() {
    crow::SimpleApp app;
    
    setupReservationRoutes(app);
    
    app.port(8080).multithreaded().run();
    
    return 0;
}