#ifndef LIBSHMIPC_H
#define LIBSHMIPC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define SHMIPC_MESSAGE_TYPE_LENGTH 256

typedef enum {
	SHMIPC_AM_READ  = 0,
	SHMIPC_AM_WRITE = 1
} shmipc_access_mode;

typedef enum {
	SHMIPC_ERR_SUCCESS,
	SHMIPC_ERR_TIMEOUT,
	SHMIPC_ERR_UNKNOWN
} shmipc_error;

typedef struct shmipc shmipc;

shmipc* shmipc_create(const char* name, size_t buffer_size, int buffer_count, shmipc_access_mode mode);
shmipc* shmipc_open(const char* name, shmipc_access_mode mode);

shmipc_error shmipc_acquire_buffer_r(shmipc* me, char* out_type, const char** out_buffer, size_t* out_size, int timeout);
void shmipc_return_buffer_r(shmipc* me, const char** buffer);

shmipc_error shmipc_acquire_buffer_w(shmipc* me, char** out_buffer, int timeout);

void shmipc_return_buffer_w(shmipc* me, char** buffer, size_t size, const char* type);

shmipc_error shmipc_send_message(shmipc* me, const char* type, const char* message, size_t length, int timeout);
shmipc_error shmipc_recv_message(shmipc* me, char* out_type, char* out_message, size_t* out_size, int timeout);

void shmipc_destroy(shmipc** me);


#ifdef __cplusplus
}
#endif

#endif
