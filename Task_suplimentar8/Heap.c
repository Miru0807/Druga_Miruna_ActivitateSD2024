#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Patient {
    char firstName[50];
    char lastName[50];
    int age;
    int urgencyLevel;
    bool cameByAmbulance;
} Patient;

typedef struct {
    Patient* patients;
    int maxCapacity;
    int currentSize;
} EmergencyHeap;

EmergencyHeap* createHeap(int capacity) {
    EmergencyHeap* heap = (EmergencyHeap*)calloc(1, sizeof(EmergencyHeap));
    if (!heap) {
        fprintf(stderr, "Memory allocation error for heap structure.\n");
        exit(EXIT_FAILURE);
    }
    heap->maxCapacity = capacity;
    heap->patients = (Patient*)calloc(capacity, sizeof(Patient));
    if (!heap->patients) {
        fprintf(stderr, "Memory allocation error for patients.\n");
        free(heap);
        exit(EXIT_FAILURE);
    }
    return heap;
}

void swapPatients(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(EmergencyHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->currentSize && heap->patients[left].urgencyLevel > heap->patients[largest].urgencyLevel)
        largest = left;
    if (right < heap->currentSize && heap->patients[right].urgencyLevel > heap->patients[largest].urgencyLevel)
        largest = right;

    if (largest != index) {
        swapPatients(&heap->patients[index], &heap->patients[largest]);
        heapify(heap, largest);
    }
}

void addPatient(EmergencyHeap* heap, Patient p) {
    if (heap->currentSize == heap->maxCapacity) {
        fprintf(stderr, "Heap is full. No more patients can be added.\n");
        return;
    }
    heap->patients[heap->currentSize] = p;
    int current = heap->currentSize;
    heap->currentSize++;

    while (current != 0 && heap->patients[(current - 1) / 2].urgencyLevel < heap->patients[current].urgencyLevel) {
        swapPatients(&heap->patients[(current - 1) / 2], &heap->patients[current]);
        current = (current - 1) / 2;
    }
}

void displayPatients(EmergencyHeap* heap) {
    while (heap->currentSize > 0) {
        Patient p = heap->patients[0];
        heap->patients[0] = heap->patients[heap->currentSize - 1];
        heap->currentSize--;
        heapify(heap, 0);
        printf("Patient: %s %s, Age: %d, Urgency Level: %d, Came by ambulance: %s\n",
            p.firstName, p.lastName, p.age, p.urgencyLevel, p.cameByAmbulance ? "Yes" : "No");
    }
}

void freeHeap(EmergencyHeap* heap) {
    if (heap) {
        free(heap->patients);
        free(heap);
    }
}

int main() {
    EmergencyHeap* heap = createHeap(10);

    addPatient(heap, (Patient) { .firstName = "Mihaela", .lastName = "Radulescu", .age = 52, .urgencyLevel = 11, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Ioana", .lastName = "Morosanu", .age = 33, .urgencyLevel = 10, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Ion", .lastName = "Popescu", .age = 45, .urgencyLevel = 9, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Ana", .lastName = "Vasile", .age = 37, .urgencyLevel = 8, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "George", .lastName = "Becali", .age = 61, .urgencyLevel = 7, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Vlad", .lastName = "Tepes", .age = 50, .urgencyLevel = 6, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Loredana", .lastName = "Iordan", .age = 48, .urgencyLevel = 5, .cameByAmbulance = true });
    addPatient(heap, (Patient) { .firstName = "Dan", .lastName = "Constantinescu", .age = 58, .urgencyLevel = 4, .cameByAmbulance = false });
    addPatient(heap, (Patient) { .firstName = "Maria", .lastName = "Ionescu", .age = 30, .urgencyLevel = 3, .cameByAmbulance = false });
    addPatient(heap, (Patient) { .firstName = "Elena", .lastName = "Marin", .age = 45, .urgencyLevel = 2, .cameByAmbulance = false });

    displayPatients(heap);
    freeHeap(heap);
    return 0;
}