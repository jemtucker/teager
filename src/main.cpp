#include <Python.h>

#include "Parser.h"

static PyObject * Teager_parse_file(PyObject *self, PyObject *args) {
    const char *filename = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename))
        return nullptr;
    
    Parser parser;
    parser.parse_file(filename, [](const char *str) {
        printf("Output: %s\n", str); 
    }); 
    
    Py_RETURN_NONE;
}

static PyMethodDef TeagerMethods[] = {
    {"parse_file",  Teager_parse_file, METH_VARARGS, "Parse a file"},
    {NULL, NULL, 0, NULL}  
};

static struct PyModuleDef TeagerModule = {
    PyModuleDef_HEAD_INIT,
    "teager", // Module Name 
    nullptr,  // Documentation
    -1,
    TeagerMethods 
};

PyMODINIT_FUNC PyInit_teager(void) {
    return PyModule_Create(&TeagerModule);
}
