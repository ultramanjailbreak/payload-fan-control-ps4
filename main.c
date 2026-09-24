/*
 * PS4 Fan Control PayLoad (notification demo)
 * Sends a system notification with the title "Hello".
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <orbis/libkernel.h>

/* Orbis notification request layout (as used by other PS4 payloads). */
typedef struct notify_request {
    char useless1[45];
    char message[3075];
} notify_request_t;

int sceKernelSendNotificationRequest(int, notify_request_t *, size_t, int);

int main(void) {
    notify_request_t req;
    memset(&req, 0, sizeof(req));

    /* The notification body. The title "Hello" is the first line, the
       second line is a short description. */
    snprintf(req.message, sizeof(req.message),
             "Hello\nPS4 Fan Control PayLoad loaded");

    int fd = sceKernelSendNotificationRequest(0, &req, sizeof(req), 0);
    if (fd < 0) {
        /* Fall back to stdout for debugging over a serial/TCP shell. */
        printf("sceKernelSendNotificationRequest failed: 0x%08X\n", fd);
        return 1;
    }

    printf("Notification sent: Hello\n");
    return 0;
}
