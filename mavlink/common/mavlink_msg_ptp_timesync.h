#pragma once
// MESSAGE PTP_TIMESYNC PACKING

#define MAVLINK_MSG_ID_PTP_TIMESYNC 229

MAVPACKED(
typedef struct __mavlink_ptp_timesync_t {
 int64_t tv_sec; /*< Time sync Second timestamp*/
 int64_t tv_nsec; /*< Time sync Nanosecond timestamp*/
 uint8_t msg_type; /*< Type of PTP message*/
 uint8_t seq; /*< Sequence of PTP message*/
}) mavlink_ptp_timesync_t;

#define MAVLINK_MSG_ID_PTP_TIMESYNC_LEN 18
#define MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN 18
#define MAVLINK_MSG_ID_229_LEN 18
#define MAVLINK_MSG_ID_229_MIN_LEN 18

#define MAVLINK_MSG_ID_PTP_TIMESYNC_CRC 1
#define MAVLINK_MSG_ID_229_CRC 1



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_PTP_TIMESYNC { \
    229, \
    "PTP_TIMESYNC", \
    4, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_ptp_timesync_t, msg_type) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_ptp_timesync_t, seq) }, \
         { "tv_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_ptp_timesync_t, tv_sec) }, \
         { "tv_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_ptp_timesync_t, tv_nsec) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_PTP_TIMESYNC { \
    "PTP_TIMESYNC", \
    4, \
    {  { "msg_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_ptp_timesync_t, msg_type) }, \
         { "seq", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_ptp_timesync_t, seq) }, \
         { "tv_sec", NULL, MAVLINK_TYPE_INT64_T, 0, 0, offsetof(mavlink_ptp_timesync_t, tv_sec) }, \
         { "tv_nsec", NULL, MAVLINK_TYPE_INT64_T, 0, 8, offsetof(mavlink_ptp_timesync_t, tv_nsec) }, \
         } \
}
#endif

/**
 * @brief Pack a ptp_timesync message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param msg_type Type of PTP message
 * @param seq Sequence of PTP message
 * @param tv_sec Time sync Second timestamp
 * @param tv_nsec Time sync Nanosecond timestamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ptp_timesync_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t msg_type, uint8_t seq, int64_t tv_sec, int64_t tv_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PTP_TIMESYNC_LEN];
    _mav_put_int64_t(buf, 0, tv_sec);
    _mav_put_int64_t(buf, 8, tv_nsec);
    _mav_put_uint8_t(buf, 16, msg_type);
    _mav_put_uint8_t(buf, 17, seq);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN);
#else
    mavlink_ptp_timesync_t packet;
    packet.tv_sec = tv_sec;
    packet.tv_nsec = tv_nsec;
    packet.msg_type = msg_type;
    packet.seq = seq;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PTP_TIMESYNC;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
}

/**
 * @brief Pack a ptp_timesync message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param msg_type Type of PTP message
 * @param seq Sequence of PTP message
 * @param tv_sec Time sync Second timestamp
 * @param tv_nsec Time sync Nanosecond timestamp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ptp_timesync_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t msg_type,uint8_t seq,int64_t tv_sec,int64_t tv_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PTP_TIMESYNC_LEN];
    _mav_put_int64_t(buf, 0, tv_sec);
    _mav_put_int64_t(buf, 8, tv_nsec);
    _mav_put_uint8_t(buf, 16, msg_type);
    _mav_put_uint8_t(buf, 17, seq);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN);
#else
    mavlink_ptp_timesync_t packet;
    packet.tv_sec = tv_sec;
    packet.tv_nsec = tv_nsec;
    packet.msg_type = msg_type;
    packet.seq = seq;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_PTP_TIMESYNC;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
}

/**
 * @brief Encode a ptp_timesync struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ptp_timesync C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ptp_timesync_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ptp_timesync_t* ptp_timesync)
{
    return mavlink_msg_ptp_timesync_pack(system_id, component_id, msg, ptp_timesync->msg_type, ptp_timesync->seq, ptp_timesync->tv_sec, ptp_timesync->tv_nsec);
}

/**
 * @brief Encode a ptp_timesync struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ptp_timesync C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ptp_timesync_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_ptp_timesync_t* ptp_timesync)
{
    return mavlink_msg_ptp_timesync_pack_chan(system_id, component_id, chan, msg, ptp_timesync->msg_type, ptp_timesync->seq, ptp_timesync->tv_sec, ptp_timesync->tv_nsec);
}

/**
 * @brief Send a ptp_timesync message
 * @param chan MAVLink channel to send the message
 *
 * @param msg_type Type of PTP message
 * @param seq Sequence of PTP message
 * @param tv_sec Time sync Second timestamp
 * @param tv_nsec Time sync Nanosecond timestamp
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ptp_timesync_send(mavlink_channel_t chan, uint8_t msg_type, uint8_t seq, int64_t tv_sec, int64_t tv_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_PTP_TIMESYNC_LEN];
    _mav_put_int64_t(buf, 0, tv_sec);
    _mav_put_int64_t(buf, 8, tv_nsec);
    _mav_put_uint8_t(buf, 16, msg_type);
    _mav_put_uint8_t(buf, 17, seq);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PTP_TIMESYNC, buf, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
#else
    mavlink_ptp_timesync_t packet;
    packet.tv_sec = tv_sec;
    packet.tv_nsec = tv_nsec;
    packet.msg_type = msg_type;
    packet.seq = seq;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PTP_TIMESYNC, (const char *)&packet, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
#endif
}

/**
 * @brief Send a ptp_timesync message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_ptp_timesync_send_struct(mavlink_channel_t chan, const mavlink_ptp_timesync_t* ptp_timesync)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_ptp_timesync_send(chan, ptp_timesync->msg_type, ptp_timesync->seq, ptp_timesync->tv_sec, ptp_timesync->tv_nsec);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PTP_TIMESYNC, (const char *)ptp_timesync, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
#endif
}

#if MAVLINK_MSG_ID_PTP_TIMESYNC_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_ptp_timesync_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t msg_type, uint8_t seq, int64_t tv_sec, int64_t tv_nsec)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_int64_t(buf, 0, tv_sec);
    _mav_put_int64_t(buf, 8, tv_nsec);
    _mav_put_uint8_t(buf, 16, msg_type);
    _mav_put_uint8_t(buf, 17, seq);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PTP_TIMESYNC, buf, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
#else
    mavlink_ptp_timesync_t *packet = (mavlink_ptp_timesync_t *)msgbuf;
    packet->tv_sec = tv_sec;
    packet->tv_nsec = tv_nsec;
    packet->msg_type = msg_type;
    packet->seq = seq;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_PTP_TIMESYNC, (const char *)packet, MAVLINK_MSG_ID_PTP_TIMESYNC_MIN_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN, MAVLINK_MSG_ID_PTP_TIMESYNC_CRC);
#endif
}
#endif

#endif

// MESSAGE PTP_TIMESYNC UNPACKING


/**
 * @brief Get field msg_type from ptp_timesync message
 *
 * @return Type of PTP message
 */
static inline uint8_t mavlink_msg_ptp_timesync_get_msg_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field seq from ptp_timesync message
 *
 * @return Sequence of PTP message
 */
static inline uint8_t mavlink_msg_ptp_timesync_get_seq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field tv_sec from ptp_timesync message
 *
 * @return Time sync Second timestamp
 */
static inline int64_t mavlink_msg_ptp_timesync_get_tv_sec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  0);
}

/**
 * @brief Get field tv_nsec from ptp_timesync message
 *
 * @return Time sync Nanosecond timestamp
 */
static inline int64_t mavlink_msg_ptp_timesync_get_tv_nsec(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int64_t(msg,  8);
}

/**
 * @brief Decode a ptp_timesync message into a struct
 *
 * @param msg The message to decode
 * @param ptp_timesync C-struct to decode the message contents into
 */
static inline void mavlink_msg_ptp_timesync_decode(const mavlink_message_t* msg, mavlink_ptp_timesync_t* ptp_timesync)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    ptp_timesync->tv_sec = mavlink_msg_ptp_timesync_get_tv_sec(msg);
    ptp_timesync->tv_nsec = mavlink_msg_ptp_timesync_get_tv_nsec(msg);
    ptp_timesync->msg_type = mavlink_msg_ptp_timesync_get_msg_type(msg);
    ptp_timesync->seq = mavlink_msg_ptp_timesync_get_seq(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_PTP_TIMESYNC_LEN? msg->len : MAVLINK_MSG_ID_PTP_TIMESYNC_LEN;
        memset(ptp_timesync, 0, MAVLINK_MSG_ID_PTP_TIMESYNC_LEN);
    memcpy(ptp_timesync, _MAV_PAYLOAD(msg), len);
#endif
}
