#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Nod {
public:
    string nume;
    double medie;
    Nod *next;
    int index;

    Nod(const string &nume, double medie, Nod *next, int index) : nume(nume), medie(medie), next(next), index(index) {}
};

void split(Nod *head, Nod *&primaJumatate, Nod *&aDouaJumatate) {
    Nod *fast;
    Nod *slow;
    slow = head;
    fast = head->next;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    primaJumatate = head;
    aDouaJumatate = slow->next;
    slow->next = NULL;
}

Nod *getMax(Nod *primulStudent, Nod *alDoileaStudent) {
    if (primulStudent->medie > alDoileaStudent->medie) {
        return primulStudent;
    } else if (primulStudent->medie == alDoileaStudent->medie) {
        if (primulStudent->nume < alDoileaStudent->nume) {
            return primulStudent;
        }
        if (primulStudent->nume > alDoileaStudent->nume) {
            return alDoileaStudent;
        }
    } else {
        return alDoileaStudent;
    }
}

Nod *merge(Nod *primulStudent, Nod *alDoileaStudent) {
    if (primulStudent == NULL)
        return alDoileaStudent;
    if (alDoileaStudent == NULL)
        return primulStudent;
    Nod *head = getMax(primulStudent, alDoileaStudent);
    Nod *rezultat = head;
    if (head == primulStudent)
        primulStudent = primulStudent->next;
    else
        alDoileaStudent = alDoileaStudent->next;

    while (primulStudent != NULL && alDoileaStudent != NULL) {
        Nod *curr = getMax(primulStudent, alDoileaStudent);
        head->next = curr;
        head = curr;
        curr = curr->next;
        if (head == primulStudent)
            primulStudent = primulStudent->next;
        else
            alDoileaStudent = alDoileaStudent->next;
    }

    if (primulStudent == NULL)
        head->next = alDoileaStudent;
    else
        head->next = primulStudent;
    return rezultat;
}

Nod *mergeSort(Nod *head) {
    if (head == NULL || head->next == NULL)
        return head;

    Nod *primaJumatate;
    Nod *aDouaJumatate;
    split(head, primaJumatate, aDouaJumatate);

    primaJumatate = mergeSort(primaJumatate);
    aDouaJumatate = mergeSort(aDouaJumatate);

    return merge(primaJumatate, aDouaJumatate);
}

class Lista {

private:
    Nod *head;
public:
    Lista() {
        head = nullptr;
    }

    ~Lista() {
        Nod *nodCurent = head;
        while (nodCurent != nullptr) {
            Nod *nodUrmator = nodCurent->next;
            delete nodCurent;
            nodCurent = nodUrmator;
        }
    }

    void adaugaStudent(string nume, double medie) {
        if (head == nullptr)
            head = new Nod(nume, medie, head, 0);
        else
            head = new Nod(nume, medie, head, head->index + 1);
    }

    vector<int> returneazaIndecsiSortati() {
        vector<int> indecsi;
        head = mergeSort(head);
        for (auto i = head; i != nullptr; i = i->next) {
            indecsi.push_back(i->index);
        }
        return indecsi;
    }
};

int main() {
    Lista list;
    list.adaugaStudent("mihai", 7.50);
    list.adaugaStudent("ana", 9.66);
    list.adaugaStudent("marian", 8.23);
    list.adaugaStudent("cristi", 7.50);

    vector<int> v = list.returneazaIndecsiSortati();
    for (auto i: v)
        cout << i << " ";
}