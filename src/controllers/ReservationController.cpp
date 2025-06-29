#include "ReservationController.h"
#include "../models/Treap.h"
#include <random>

static Treap reservationTreap;

std::string ReservationController::createReservation(const std::string& datetime, const std::string& clientName) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);

    std::string key = datetime + "_" + clientName;
    reservationTreap.insert(key, dis(gen));

    return "Reserva creada: " + key;
}

bool ReservationController::deleteReservation(const std::string& key) {
    reservationTreap.deleteKey(key);
    return true;
}

std::vector<std::string> ReservationController::getAllReservations() {
    return reservationTreap.getAllKeys();
}

std::string ReservationController::getTreeStructure(){
    return reservationTreap.serializeTree();
}