#ifndef PROTO_DINC_H
#define PROTO_DINC_H

/* jittertrap protocol */

/*
 * one of these is auto-created for each connection and a pointer to the
 * appropriate instance is passed to the callback in the user parameter
 *
 */

struct per_session_data__jittertrap {
	unsigned long consumer_id;
};

int callback_jittertrap(struct lws *wsi, enum lws_callback_reasons reason,
                        void *user, void *in, size_t len);
#endif
