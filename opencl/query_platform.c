#include <stdio.h>
#include <stdlib.h>
#include <CL/opencl.h>

#define BUFSIZE 1024
#define DIE(x) { fprintf(stderr, "%s\n", x); exit(EXIT_FAILURE); }

int main(int argc, char **argv) {
    // for platform test
    cl_uint num_platforms = 0;
    cl_platform_id *tbl_platforms = NULL;

    // for device test
    cl_uint *num_devices = NULL;
    cl_device_id **tbl_devices = NULL;

    // general
    cl_int res; //stores result
    int i, j;
    char buffer[BUFSIZE];

    puts("OpenCL TEST");

    /* Platform test */
    puts("==== Platform test ====");
    res = clGetPlatformIDs(0, NULL, &num_platforms);
    if(res != CL_SUCCESS){
        DIE("Cannot get platform total numbers.");
    }

    printf("There're %d platforms\n", num_platforms);
    tbl_platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms);
    res = clGetPlatformIDs(num_platforms, tbl_platforms, NULL);
    if(res != CL_SUCCESS)
        DIE("Cannot get device IDs.");

    for(i=0; i<num_platforms; ++i) {
        printf("Platform ID: %d\n", tbl_platforms[i]);
        clGetPlatformInfo(tbl_platforms[i], CL_PLATFORM_PROFILE, 
                          BUFSIZE, buffer, NULL);
        printf("CL_PLATFORM_PROFILE: %s\n", buffer);
        clGetPlatformInfo(tbl_platforms[i], CL_PLATFORM_VERSION, 
                          BUFSIZE, buffer, NULL);
        printf("CL_PLATFORM_VERSION: %s\n", buffer);
        clGetPlatformInfo(tbl_platforms[i], CL_PLATFORM_NAME, 
                          BUFSIZE, buffer, NULL);
        printf("CL_PLATFORM_NAME: %s\n", buffer);
        clGetPlatformInfo(tbl_platforms[i], CL_PLATFORM_VENDOR, 
                          BUFSIZE, buffer, NULL);
        printf("CL_PLATFORM_VENDOR: %s\n", buffer);
        clGetPlatformInfo(tbl_platforms[i], CL_PLATFORM_EXTENSIONS, 
                          BUFSIZE, buffer, NULL);
        printf("CL_PLATFORM_EXTENSINONS: %s\n", buffer);
        printf("\n");
    }


    /* Device test */
    puts("==== Device test ====");
    num_devices = (cl_uint *)malloc(sizeof(cl_uint) * num_platforms);
    tbl_devices = (cl_device_id **)malloc(sizeof(cl_device_id *) * num_platforms);
    for(i=0; i<num_platforms; ++i) {
        res = clGetDeviceIDs(tbl_platforms[i], CL_DEVICE_TYPE_ALL, 
                             0, NULL, num_devices + i);
        if(res != CL_SUCCESS)
            DIE("Cannot get device total numbers.");

        tbl_devices[i] = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices[i]);
        res = clGetDeviceIDs(tbl_platforms[i], CL_DEVICE_TYPE_ALL, 
                             num_devices[i], tbl_devices[i], NULL);
        printf("Platform %d (%d) has %d devices.\n", i, tbl_platforms[i], num_devices[i]);
    }

    putchar('\n');
    for(i=0; i<num_platforms; ++i) {
        printf("%d: platform_id(%d)\n", i, tbl_platforms[i]);
        for(j=0; j<num_devices[i]; ++j) {
            printf("Device ID: %d\n", tbl_devices[i][j]);
            clGetDeviceInfo(tbl_devices[i][j], CL_DEVICE_NAME, 
                            BUFSIZE, buffer, NULL);
            printf("CL_DEVICE_NAME: %s\n", buffer);
            clGetDeviceInfo(tbl_devices[i][j], CL_DEVICE_VENDOR, 
                            BUFSIZE, buffer, NULL);
            printf("CL_DEVICE_VENDOR: %s\n", buffer);
            clGetDeviceInfo(tbl_devices[i][j], CL_DEVICE_PROFILE, 
                            BUFSIZE, buffer, NULL);
            printf("CL_DEVICE_PROFILE: %s\n", buffer);
            clGetDeviceInfo(tbl_devices[i][j], CL_DEVICE_VERSION, 
                            BUFSIZE, buffer, NULL);
            printf("CL_DEVICE_VERSION: %s\n", buffer);
            clGetDeviceInfo(tbl_devices[i][j], CL_DRIVER_VERSION, 
                            BUFSIZE, buffer, NULL);
            printf("CL_DRIVER_VERSION: %s\n", buffer);

            printf("\n");
        }
    }


    /* okataduke */
    free(tbl_platforms);
    free(num_devices);
    for(i=0; i<num_platforms; ++i)
        free(tbl_devices[i]);
    free(tbl_devices);

    return EXIT_SUCCESS;
}
