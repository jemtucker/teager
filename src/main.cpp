#include <Python.h>

#include "Parser.h"

static void Teager_callback(
    PyObject *callable,
    const std::string& symbol,
    SymbolType type,
    const std::string& filename,
    unsigned lineno) {

    auto args = Py_BuildValue(
        "ssI",
        symbol.c_str(),
        filename.c_str(),
        lineno);

    PyObject *result = PyEval_CallObject(callable, args);
    
    // TODO: result can be null if an exception is thrown in the above
    //       call. We should somehow pass that back to the original
    //       caller. 
    
    Py_DECREF(result);
    Py_DECREF(args);
}

static PyObject * Teager_parse_file(PyObject *self, PyObject *args) {
    const char *filename = nullptr;
    PyObject *callback = nullptr;

    if (!PyArg_ParseTuple(args, "sO", &filename, &callback))
        return nullptr;
    
    if (!PyCallable_Check(callback)) {
        PyErr_SetString(PyExc_TypeError, "Callback must be callable");
        return nullptr;
    }
    
    namespace ph = std::placeholders;

    Parser parser;
    parser.parse_file(
        filename, 
        std::bind(
            Teager_callback, 
            callback, 
            ph::_1, 
            ph::_2, 
            ph::_3, 
            ph::_4));
       
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
