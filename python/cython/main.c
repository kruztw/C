#include <Python.h>
#include "simple.h"

int main() {
    // Init module & Python interpreter
    PyImport_AppendInittab("simple", PyInit_simple);
    Py_Initialize();
    PyImport_ImportModule("simple");
    
    // Call Python function
    printf("%d\n", add_c(1, 2, 3));

    // Frees memory allocated by Python interpreter 
    Py_Finalize();
}
