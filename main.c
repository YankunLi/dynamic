#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


#define LIB_DISPLAY_PATH "/home/yankun/dynamic_lib/libdisplay.so"

typedef void (*DISP_FUNC)();

int main(int argc, char *argv[])
{
    void *handle;
    char *error;
    DISP_FUNC disp_func = NULL;

    handle = dlopen(LIB_DISPLAY_PATH, RTLD_LAZY);
    if (!handle){
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();

    *(void **) (&disp_func) = dlsym(handle, "display");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    (*disp_func)();

    dlclose(handle);
    return 0;
}
