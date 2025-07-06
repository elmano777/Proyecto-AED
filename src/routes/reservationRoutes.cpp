#include "reservationRoutes.h"
#include "../controllers/ReservationController.h"
#include <crow.h>
#include <crow/middlewares/cors.h>

static ReservationController controller;

void setupReservationRoutes(crow::App<crow::CORSHandler> &app)
{
    CROW_ROUTE(app, "/reservations").methods("POST"_method)([](const crow::request &req)
                                                            {
        auto body = crow::json::load(req.body);
        std::string datetime = body["datetime"].s();
        std::string client = body["client"].s();

        std::string result = controller.createReservation(datetime, client);
        
        // Devolver JSON en lugar de texto plano
        crow::json::wvalue response;
        response["message"] = result;
        response["success"] = true;
        return crow::response(200, response); });

    CROW_ROUTE(app, "/reservations").methods("GET"_method)([](const crow::request &req)
                                                           {
        auto reservations = controller.getAllReservations();
        crow::json::wvalue result;
        result["reservations"] = reservations;
        return crow::response(200, result); });

    CROW_ROUTE(app, "/reservations/<string>").methods("DELETE"_method)([](const crow::request &req, std::string key)
                                                                       {
        controller.deleteReservation(key);
        
        // Devolver JSON en lugar de texto plano
        crow::json::wvalue response;
        response["message"] = "Reserva eliminada correctamente";
        response["success"] = true;
        response["deleted_key"] = key;
        return crow::response(200, response); });

        CROW_ROUTE(app, "/reserva/tree").methods("GET"_method)([](const crow::request &req) {
            std::string treeStructure = controller.getTreeStructure();
            
            // Construir la respuesta manualmente
            std::string response = "{\"message\":\"Estructura del arbol\",\"tree\":" + treeStructure + "}";
            
            crow::response res(200, response);
            res.add_header("Content-Type", "application/json");
            return res;
        });
}