#include "PatientList.h"

PatientList::PatientList() : head(nullptr), tail(nullptr), count(0) {}

PatientList::~PatientList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void PatientList::addPatient(int serial, const std::string& name, const std::string& fname, const std::string& dob,
                             const std::string& ward, const std::string& id, int days) {
    Node* newNode = new Node(serial, name, fname, dob, ward, id, days);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

Node* PatientList::searchPatient(int srNo) {
    Node* temp = head;
    while (temp) {
        if (temp->srNo == srNo) return temp;
        temp = temp->next;
    }
    return nullptr;
}

bool PatientList::editPatient(int srNo, const std::string& name, const std::string& fname, const std::string& dob,
                              const std::string& ward, const std::string& id, int days) {
    Node* target = searchPatient(srNo);
    if (target) {
        target->name = name;
        target->fname = fname;
        target->dob = dob;
        target->ward = ward;
        target->id = id;
        target->days = days;
        return true;
    }
    return false;
}

bool PatientList::deletePatient(int srNo) {
    Node* target = searchPatient(srNo);
    if (!target) return false;

    if (target == head) {
        head = head->next;
        if (head) head->prev = nullptr;
    } else if (target == tail) {
        tail = tail->prev;
        if (tail) tail->next = nullptr;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    delete target;
    count--;
    return true;
}

std::vector<Node*> PatientList::getAllPatients() {
    std::vector<Node*> patients;
    Node* temp = head;
    while (temp) {
        patients.push_back(temp);
        temp = temp->next;
    }
    return patients;
}

bool PatientList::isIdUnique(const std::string& id) const {
    Node* temp = head;
    while (temp) {
        if (temp->id == id) return false;
        temp = temp->next;
    }
    return true;
}