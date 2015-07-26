#ifndef STATS_THREAD_H
#define STATS_THREAD_H

struct sample {
	struct timespec timestamp;
	int64_t		whoosh_error_ns;
	int64_t 	rx_bytes;
	int64_t 	tx_bytes;
	int64_t 	rx_bytes_delta;
	int64_t 	tx_bytes_delta;
	int64_t 	rx_packets;
	int64_t 	rx_packets_delta;
	int64_t 	tx_packets;
	int64_t 	tx_packets_delta;
};

struct iface_stats {
	uint32_t 	sample_period_us;
	char	 	iface[MAX_IFACE_LEN];
	struct sample 	samples[SAMPLES_PER_FRAME];
	uint64_t	whoosh_err_mean;
	uint64_t	whoosh_err_max;
	uint64_t	whoosh_err_sd;
};

int stats_thread_init(void (*stats_handler) (struct iface_stats * counts));
void stats_monitor_iface(const char *_iface);

/* microseconds */
void set_sample_period(int sample_period_us);
int get_sample_period();

#endif
