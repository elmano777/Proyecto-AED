#include "reservationRoutes.h"
#include "../controllers/ReservationController.cpp"
#include <crow.h>

void setupReservationRoutes(crow::SimpleApp& app) {
    // POST /reservations
    CROW_ROUTE(app, "/reservations").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        std::string datetime = body["datetime"].s();
        std::string client = body["client"].s();
        
        std::string result = ReservationController::createReservation(datetime, client);
        return crow::response(200, result);
    });
    
    // GET /reservations
    CROW_ROUTE(app, "/reservations")
    ([](const crow::request& req) {
        auto reservations = ReservationController::getAllReservations();
        crow::json::wvalue result;
        result["reservations"] = reservations;
        return crow::response(200, result);
    });
    
    // DELETE /reservations/<key>
    CROW_ROUTE(app, "/reservations/<string>")
    ([](const crow::request& req, std::string key) {
        ReservationController::deleteReservation(key);
        return crow::response(200, "Deleted");
    });
}