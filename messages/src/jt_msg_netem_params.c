#include <string.h>
#include <assert.h>
#include <jansson.h>

#include "jt_message_types.h"
#include "jt_messages.h"

#include "jt_msg_netem_params.h"

static const char *jt_netem_params_test_msg =
    "{\"msg\":\"netem_params\", \"p\":{\"iface\":\"em1\", \"delay\":-1, "
    "\"jitter\":-1, \"loss\":-1}}";

const char *jt_netem_params_test_msg_get(void)
{
	return jt_netem_params_test_msg;
}

int jt_netem_params_free(void *data)
{
	struct jt_msg_netem_params *p = data;
	free(p);
	return 0;
}

int jt_netem_params_printer(void *data, char *out, int len)
{
	struct jt_msg_netem_params *p = data;

	snprintf(out, len, "Impairment params:\n"
	       "\tInterface:  %s\n"
	       "\tDelay:      %dms\n"
	       "\tJitter:  +/-%dms\n"
	       "\tLoss:       %d",
	       p->iface, p->delay, p->jitter, p->loss);
	return 0;
}

int jt_netem_params_unpacker(json_t *root, void **data)
{
	json_t *params_token;
	struct jt_msg_netem_params *params;

	params_token = json_object_get(root, "p");

	assert(JSON_OBJECT == json_typeof(params_token));
	assert(0 < json_object_size(params_token));

	params = malloc(sizeof(struct jt_msg_netem_params));

	json_t *token = json_object_get(params_token, "iface");
	if (!json_is_string(token)) {
		assert(0);
		goto cleanup_unpack_fail;
	}
	snprintf(params->iface, MAX_IFACE_LEN, "%s", json_string_value(token));

	token = json_object_get(params_token, "delay");
	if (!json_is_integer(token)) {
		assert(0);
		goto cleanup_unpack_fail;
	}
	params->delay = json_integer_value(token);

	token = json_object_get(params_token, "jitter");
	if (!json_is_integer(token)) {
		assert(0);
		goto cleanup_unpack_fail;
	}
	params->jitter = json_integer_value(token);

	token = json_object_get(params_token, "loss");
	if (!json_is_integer(token)) {
		assert(0);
		goto cleanup_unpack_fail;
	}
	params->loss = json_integer_value(token);

	*data = params;
	return 0;

cleanup_unpack_fail:
	free(params);
	return -1;
}

int jt_netem_params_packer(void *data, char **out)
{
	struct jt_msg_netem_params *params = data;
	json_t *t = json_object();
	json_t *p = json_object();

	json_object_set_new(p, "iface", json_string(params->iface));
	json_object_set_new(p, "delay", json_integer(params->delay));
	json_object_set_new(p, "jitter", json_integer(params->jitter));
	json_object_set_new(p, "loss", json_integer(params->loss));

	json_object_set_new(
	    t, "msg", json_string(jt_messages[JT_MSG_NETEM_PARAMS_V1].key));
	json_object_set(t, "p", p);
	*out = json_dumps(t, 0);
	json_object_clear(p);
	json_decref(p);
	json_object_clear(t);
	json_decref(t);
	return 0;
}
