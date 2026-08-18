#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include <string>
#include <vector>

struct Node {
    int srNo;
    std::string name, fname, dob, ward, id;
    int days;
    Node* next;
    Node* prev;

    Node(int serial, const std::string& pname, const std::string& pfname, const std::string& pdob,
         const std::string& pward, const std::string& pid, int pdays)
        : srNo(serial), name(pname), fname(pfname), dob(pdob), ward(pward), id(pid), days(pdays), next(nullptr), prev(nullptr) {}
};

class PatientList {
private:
    Node* head;
    Node* tail;
    int count;

public:
    PatientList();
    ~PatientList();
    void addPatient(int serial, const std::string& name, const std::string& fname, const std::string& dob,
                    const std::string& ward, const std::string& id, int days);
    Node* searchPatient(int srNo);
    bool editPatient(int srNo, const std::string& name, const std::string& fname, const std::string& dob,
                     const std::string& ward, const std::string& id, int days);
    bool deletePatient(int srNo);
    std::vector<Node*> getAllPatients();
    bool isEmpty() const { return head == nullptr; }
    bool isIdUnique(const std::string& id) const;
};

#endif