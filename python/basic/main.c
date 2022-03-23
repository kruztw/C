#include <Python.h>

// Wrapper method for python function 
int add(int a, int b, int c) {
    PyObject *pModule, *pFunc, *pArgs, *pKargs, *pRes;
    int res;

    // Import Python module & function
    pModule = PyImport_Import(PyUnicode_FromString("simple"));
    pFunc = PyObject_GetAttrString(pModule, "add");
    
    // Create args object to pass in
    pArgs = Py_BuildValue("(i)", a);
    pKargs = Py_BuildValue("{s:i, s:i}", "b", b, "c", c);

    // Call function with args
    pRes = PyObject_Call(pFunc, pArgs, pKargs);

    if (pRes == NULL) {
	// error
        return -1;
    }

    // PyObject to C type
    res = PyLong_AsLong(pRes);

    // Decrement reference counts to avoid memory leak
    Py_DECREF(pModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pKargs);
    Py_DECREF(pRes);

    return res;
}

int main() {
    // Init Python interpreter
    Py_Initialize();
    
    // Set Python search path
    PySys_SetPath(Py_DecodeLocale(".", NULL));
 
    // Call Python function
    printf("%d\n", add(1, 2, 3));

    // Frees memory allocated by Python interpreter 
    Py_Finalize();
}
