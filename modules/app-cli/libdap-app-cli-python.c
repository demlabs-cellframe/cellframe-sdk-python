#include "dap_common.h"
#include "libdap-app-cli-python.h"

#define LOG_TAG "libdap-app-cli-crypto"

/**
 * @brief dap_app_cli_main_py
 * @param self
 * @param args
 * @return
 */
PyObject* dap_app_cli_main_py(PyObject *self, PyObject *args)
{
    (void) self;
    char *l_app_name    = NULL;
    char *l_socket_path = NULL;
    int l_argc          = 0;
    char **l_argv       = NULL;
    PyObject *l_argv_py = NULL;

    PyObject *l_from_list_obj   = NULL;
    PyObject *l_value_obj       = NULL;
    if (!PyArg_ParseTuple(args, "ssO", &l_app_name, &l_socket_path, & l_argv_py))
        return NULL;
    Py_ssize_t l_argv_size_py = PyList_Size(l_argv_py);
    l_argc = (int)l_argv_size_py;
    if (l_argv_size_py > 1){
        l_argv = PyMem_Calloc((size_t)l_argv_size_py, sizeof(char**));
        for (Py_ssize_t i=0; i < l_argv_size_py; i++){
            l_from_list_obj = PyList_GetItem(l_argv_py, i);
            l_value_obj = PyList_GetItem(l_argv_py, i);
            l_argv[i] = dap_strdup(PyUnicode_AsUTF8(l_value_obj));
        }
        int res = dap_app_cli_main(l_app_name, l_socket_path, l_argc, l_argv);
        for (Py_ssize_t i=0; i < l_argv_size_py; i++){
            DAP_FREE(l_argv[i]);
        }
        PyMem_Free(l_argv);
        return PyLong_FromLong(res);
    }
    else
        return PyLong_FromLong(-1024);
}
