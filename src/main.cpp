#include <Python.h>

#include "Parser.h"

static PyObject * jem_main(PyObject *self, PyObject *args) {
    const char *filename = nullptr;

    if (!PyArg_ParseTuple(args, "s", &filename))
        return nullptr;
    
    Parser parser;
    parser.parse_file(filename, [](const std::string& s) {
        printf("Output: %s\n", s.c_str()); 
    }); 
    
    Py_RETURN_NONE;
}

static PyMethodDef JemMethods[] = {
    {"parse_file",  jem_main, METH_VARARGS, "Parse a file"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef jemmodule = {
    PyModuleDef_HEAD_INIT,
    "jem",   /* name of module */
    nullptr, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    JemMethods
};

PyMODINIT_FUNC PyInit_jem(void) {
    return PyModule_Create(&jemmodule);
}
