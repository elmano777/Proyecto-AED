#include "reservationRoutes.h"
#include "../controllers/ReservationController.h"
#include <crow.h>
#include <crow/app.h>

static ReservationController controller;

void setupReservationRoutes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/reservations").methods("POST"_method)([](const crow::request &req)
                                                            {
        auto body = crow::json::load(req.body);
        std::string datetime = body["datetime"].s();
        std::string client = body["client"].s();

        std::string result = controller.createReservation(datetime, client);
        return crow::response(200, result); });

    CROW_ROUTE(app, "/reservations").methods("GET"_method)([](const crow::request &req)
                                                           {
        auto reservations = controller.getAllReservations();
        crow::json::wvalue result;
        result["reservations"] = reservations;
        return crow::response(200, result); });

    CROW_ROUTE(app, "/reservations/<string>").methods("DELETE"_method)([](const crow::request &req, std::string key)
                                                                       {
        controller.deleteReservation(key);
        return crow::response(200, "Deleted"); });

    CROW_ROUTE(app, "/reserva/tree").methods("GET"_method)([](const crow::request &req)
                                                           { std::string treeStructure = controller.getTreeStructure();
     crow::json::wvalue result;
     result["tree"] = crow::json::load(treeStructure);
     result["message"] = "Estructura del arbol p";
     return crow::response(200, result); });
}
