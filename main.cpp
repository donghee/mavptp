#include <iostream>
#include <thread>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "serial_port.h"

#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include <mavlink_helpers.h>
#include <common/mavlink.h>


#define BUFFER_LENGTH 1000

static Serial_Port *serial1;
static mavlink_system_t mavlink_system;

static uint64_t time_offset_ns = 0;

void signal_callback_handler(int signum)
{
	serial1->close_serial();
	exit(signum);
}

#define PTP_SYNC 0x00
#define PTP_FOLLOW_UP 0x08
#define PTP_DELAY_REQUEST 0x01
#define PTP_DELAY_RESPONSE 0x09

void send_message_ptp_timesync(int sysid, int compid, uint8_t seq,
			       uint8_t msg_type, uint64_t tv_sec, uint64_t tv_nsec)
{
	mavlink_ptp_timesync_t tsync;
	mavlink_message_t msg = {};

	tsync.seq = seq;
	tsync.msg_type = msg_type;
	tsync.tv_sec = tv_sec;
	tsync.tv_nsec = tv_nsec;
	mavlink_msg_ptp_timesync_encode(sysid, compid, &msg, &tsync);
	serial1->write_message(msg);
	// printf("[PTP TIMESYNC] S seq: %d, msg_type: %d, tv_sec: %llu, tv_nsec: %llu \n", tsync.seq, tsync.msg_type, tsync.tv_sec, tsync.tv_nsec);
}

void send_message_timesync(int sysid, int compid, uint64_t tc1, uint64_t ts1)
{
	mavlink_timesync_t tsync;
	mavlink_message_t msg = {};

	tsync.tc1 = tc1;
	tsync.ts1 = ts1;
	mavlink_msg_timesync_encode(sysid, compid, &msg, &tsync);
	serial1->write_message(msg);
	// mavlink_msg_timesync_send_struct(MAVLINK_COMM_1, &tsync);

}

#define NSEC_PER_SEC          1000000000L /* Seconds */
#define NSEC_PER_MSEC         1000000L /* Seconds */

// buf needs to store 30 characters
int timespec2str(char *buf, uint len, struct timespec *ts)
{
	int ret;
	struct tm t;

	tzset();

	if (gmtime_r(&(ts->tv_sec), &t) == NULL) {
		// if (localtime_r(&(ts->tv_sec), &t) == NULL) {
		return 1;
	}

	ret = strftime(buf, len, "%F %T", &t);

	if (ret == 0) {
		return 2;
	}

	len -= ret - 1;

	ret = snprintf(&buf[strlen(buf)], len, ".%09ld", ts->tv_nsec);

	if (ret >= len) {
		return 3;
	}

	return 0;
}

void handle_message_ptp_timesync(mavlink_message_t *msg)
{
	mavlink_ptp_timesync_t tsync = {};
	mavlink_msg_ptp_timesync_decode(msg, &tsync);
	// printf("[PTP TIMESYNC] R seq: %d, msg_type: %d, tv_sec: %llu, tv_nsec: %llu \n", tsync.seq, tsync.msg_type,
	//        tsync.tv_sec, tsync.tv_nsec);

	// DELAY_REQUEST
	if (tsync.msg_type == PTP_DELAY_REQUEST) {
		struct timespec t4 = {};
		clock_gettime(CLOCK_REALTIME, &t4);

		// printf("[PTP TIMESYNC] DELAY_REQUEST\n");

		// DELAY_RESPONSE
		send_message_ptp_timesync(mavlink_system.sysid,
					  mavlink_system.compid, 4, PTP_DELAY_RESPONSE,
					  t4.tv_sec, t4.tv_nsec);

		// struct timespec current_time = {};
		// clock_gettime(CLOCK_REALTIME, &current_time);
		printf("[PTP TIMESYNC] current_time: %lu.%04lu sec\n", (unsigned long)t4.tv_sec,
		       (unsigned long) t4.tv_nsec / 100000);

		const uint TIME_FMT = strlen("2012-12-31 12:59:59.123456789") + 1;
		char timestr[TIME_FMT];
		timespec2str(timestr, sizeof(timestr), &t4);
		printf("TIME: %s\n", timestr);
	}
}

void handle_message_timesync(mavlink_message_t *msg)
{
	mavlink_timesync_t tsync = {};
	mavlink_msg_timesync_decode(msg, &tsync);
	printf("[TIMESYNC] tc1:%llu ts1:%llu \n", tsync.tc1, tsync.ts1);

	struct timespec tv = {};
	clock_gettime(CLOCK_REALTIME, &tv);
	uint64_t now_ns = (uint64_t)tv.tv_sec * NSEC_PER_SEC + (uint64_t)tv.tv_nsec - time_offset_ns;

	if (tsync.tc1 == 0) {
		send_message_timesync(msg->sysid, msg->compid, now_ns, tsync.ts1);
		printf("[TIMESYNC] now_ns:%llu tsync.ts1:%llu \n", now_ns, tsync.ts1);

	} else {
		int64_t _offset_ns = (int64_t)(tsync.ts1 + now_ns - tsync.tc1 * 2) / 2 ;
		printf("[TIMESYNC] offset_ns:%llu \n", _offset_ns);
		printf("[TIMESYNC] time_off_ns:%llu \n", time_offset_ns);
	}
}


void handle_message_system_time(mavlink_message_t *msg)
{
	mavlink_system_time_t time;
	mavlink_msg_system_time_decode(msg, &time);
	struct timespec tv = {};
	clock_gettime(CLOCK_REALTIME, &tv);
	uint64_t onboard_tv_usec = tv.tv_sec * 1000000 + tv.tv_nsec / 1000;
	uint64_t fc_tv_usec = time.time_unix_usec;

	if (!time_offset_ns) {
		time_offset_ns = onboard_tv_usec * 1000 - time.time_boot_ms * 1000000;
		printf("time_offset_ns :%llu \n", time_offset_ns);
	}

}


int main(int argc, const char *argv[])
{
	int baudRate1 = 57600;
	const char *port1;


	if (argc == 2) {
		port1 = argv[1];
		printf("%s\n", port1);

	} else if (argc >= 3) {
		port1 = argv[1];
		sscanf(argv[2], "%d", &baudRate1);
	}

	try {
		mavlink_system.sysid = 0;
		mavlink_system.compid = 0;

		static Serial_Port sp1(port1, baudRate1);
		sp1.start();

		serial1 = &sp1;
		signal(SIGINT, signal_callback_handler);

		std::thread([]() {
			int success = 0;
			mavlink_message_t msg;

			while (true) {
				success = sp1.read_message(msg);

				if (success) {
					mavlink_system.sysid = msg.sysid;
					mavlink_system.compid = msg.compid;

					if (msg.msgid == MAVLINK_MSG_ID_SYSTEM_TIME) {
						handle_message_system_time(&msg);
					}

					if (msg.msgid == MAVLINK_MSG_ID_PTP_TIMESYNC) {
						handle_message_ptp_timesync(&msg);
					}
				}
			}
		}).detach();

		while (true) {
			if (mavlink_system.sysid && mavlink_system.compid) {
				// SYNC
				struct timespec t1 = {};
				clock_gettime(CLOCK_REALTIME, &t1);

				// printf("[PTP TIMESYNC] SYNC\n");
				send_message_ptp_timesync(mavlink_system.sysid,
							  mavlink_system.compid, 0, PTP_SYNC,
							  0, 0);
				usleep(1000);  // 1ms

				// FOLLOW_UP 
				send_message_ptp_timesync(mavlink_system.sysid,
							  mavlink_system.compid, 1, PTP_FOLLOW_UP,
							  t1.tv_sec, t1.tv_nsec);
			}

			usleep(1000 * 1000); // 5sec
		}

	} catch (...) { }

	return 0;
}
