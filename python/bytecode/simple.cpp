#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "marshal.h"
#include <stdio.h>
#include <vector>


int main() {
        std::vector<unsigned char> bytecode = {0xe3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x40,0x0,0x0,0x0,0x73,0xc,0x0,0x0,0x0,0x64,0x0,0x64,0x1,0x84,0x0,0x5a,0x0,0x64,0x2,0x53,0x0,0x29,0x3,0x63,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x43,0x0,0x0,0x0,0x73,0xc,0x0,0x0,0x0,0x74,0x0,0x64,0x1,0x83,0x1,0x1,0x0,0x64,0x0,0x53,0x0,0x29,0x2,0x4e,0x7a,0xb,0x68,0x65,0x6c,0x6c,0x6f,0x20,0x77,0x6f,0x72,0x6c,0x64,0x29,0x1,0xda,0x5,0x70,0x72,0x69,0x6e,0x74,0xa9,0x0,0x72,0x2,0x0,0x0,0x0,0x72,0x2,0x0,0x0,0x0,0xda,0x0,0xda,0x4,0x6d,0x61,0x69,0x6e,0x2,0x0,0x0,0x0,0x73,0x2,0x0,0x0,0x0,0x0,0x1,0x72,0x4,0x0,0x0,0x0,0x4e,0x29,0x1,0x72,0x4,0x0,0x0,0x0,0x72,0x2,0x0,0x0,0x0,0x72,0x2,0x0,0x0,0x0,0x72,0x2,0x0,0x0,0x0,0x72,0x3,0x0,0x0,0x0,0xda,0x8,0x3c,0x6d,0x6f,0x64,0x75,0x6c,0x65,0x3e,0x2,0x0,0x0,0x0,0xf3,0x0,0x0,0x0,0x0};

	
	Py_Initialize();
	PyObject* obj = PyMarshal_ReadObjectFromString((const char*)bytecode.data(), bytecode.size());
	PyObject* mod = PyImport_ExecCodeModule("foo", obj);
	PyObject* res = PyObject_CallMethod(mod, "main", NULL);
	Py_Finalize();
}
