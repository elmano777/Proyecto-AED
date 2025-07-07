#include "reservationRoutes.h"
#include "../controllers/ReservationController.h"
#include <crow.h>
#include <crow/middlewares/cors.h>
#include <sstream>

static ReservationController controller;

std::string urlDecode(const std::string& str) {
    std::string result;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%' && i + 2 < str.length()) {
            int value;
            std::istringstream iss(str.substr(i + 1, 2));
            iss >> std::hex >> value;
            result += static_cast<char>(value);
            i += 2;
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

void setupReservationRoutes(crow::App<crow::CORSHandler> &app)
{
    CROW_ROUTE(app, "/reservations").methods("POST"_method)([](const crow::request &req)
    {
        auto body = crow::json::load(req.body);
        std::string datetime = body["datetime"].s();
        std::string client = body["client"].s();

        std::string result = controller.createReservation(datetime, client);

        crow::json::wvalue response;
        response["message"] = result;
        response["success"] = true;
        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/reservations").methods("GET"_method)([](const crow::request &req)
    {
        auto reservations = controller.getAllReservations();
        crow::json::wvalue result;
        result["reservations"] = reservations;
        return crow::response(200, result);
    });

    CROW_ROUTE(app, "/reservations/<string>").methods("DELETE"_method)([](const crow::request &req, std::string key)
    {
        std::string decodedKey = urlDecode(key);

        if (!controller.searchReservation(decodedKey)) {
            crow::json::wvalue errorResponse;
            errorResponse["message"] = "Reserva no encontrada";
            errorResponse["success"] = false;
            errorResponse["key"] = decodedKey;
            return crow::response(404, errorResponse);
        }

        bool deleted = controller.deleteReservation(decodedKey);

        crow::json::wvalue response;
        if (deleted) {
            response["message"] = "Reserva eliminada correctamente";
            response["success"] = true;
            response["deleted_key"] = decodedKey;
            return crow::response(200, response);
        } else {
            response["message"] = "Error al eliminar la reserva";
            response["success"] = false;
            response["key"] = decodedKey;
            return crow::response(500, response);
        }
    });

    CROW_ROUTE(app, "/reserva/tree").methods("GET"_method)([](const crow::request &req) {
        std::string treeStructure = controller.getTreeStructure();

        try {
            auto treeJson = crow::json::load(treeStructure);

            crow::json::wvalue response;
            response["message"] = "Estructura del arbol";
            response["tree"] = treeJson;
            response["success"] = true;

            return crow::response(200, response);
        } catch (const std::exception& e) {
            crow::json::wvalue errorResponse;
            errorResponse["message"] = "Error al obtener estructura del arbol";
            errorResponse["error"] = e.what();
            errorResponse["success"] = false;

            return crow::response(500, errorResponse);
        }
    });
}