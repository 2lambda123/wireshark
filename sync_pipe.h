/* sync_pipe.h
 * Low-level synchronization pipe routines for use by Wireshark/TShark
 * and dumpcap
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */


/** @file
 *
 *  Low-level sync pipe interfaces.
 */

#ifndef __SYNC_PIPE_H__
#define __SYNC_PIPE_H__

#include <ws_posix_compat.h>

/*
 * Maximum length of sync pipe message data.  Must be < 2^24, as the
 * message length is 3 bytes.
 * XXX - this must be large enough to handle a Really Big Filter
 * Expression, as the error message for an incorrect filter expression
 * is a bit larger than the filter expression.
 */
#define SP_MAX_MSG_LEN  4096

/*
 * Indications sent out on the sync pipe (from child to parent).
 * We might want to switch to something like Thrift
 * (http://thrift.apache.org/) or Protocol Buffers
 * (http://code.google.com/p/protobuf-c/) if we ever need to use more
 * complex messages.
 */
#define SP_FILE         'F'     /* the name of the recently opened file */
#define SP_ERROR_MSG    'E'     /* error message */
#define SP_BAD_FILTER   'B'     /* error message for bad capture filter */
#define SP_PACKET_COUNT 'P'     /* count of packets captured since last message */
#define SP_DROPS        'D'     /* count of packets dropped in capture */
#define SP_SUCCESS      'S'     /* success indication, no extra data */
#define SP_TOOLBAR_CTRL 'T'     /* interface toolbar control packet */
/*
 * Win32 only: Indications sent out on the signal pipe (from parent to child)
 * (UNIX-like sends signals for this)
 */
#define SP_QUIT         'Q'     /* "gracefully" capture quit message (SIGUSR1) */

/* Write a message, with a string body, to the recipient pipe in the
   standard format (1-byte message indicator, 3-byte message length
   (excluding length and indicator field), and the string.
   If msg is NULL, the message has only a length and indicator. */
extern void
sync_pipe_write_string_msg(int pipe_fd, char indicator, const char *msg);

/* Write a message, with an unsigned integer body, to the recipient
   pipe in the standard format (1-byte message indicator, 3-byte
   message length (excluding length and indicator field), and the
   unsigned integer, as a string. */
extern void
sync_pipe_write_uint_msg(int pipe_fd, char indicator, unsigned int num);

/** the child encountered an error, notify the parent */
/* Write a message, with two message strings as the body, to the
   recipient pipe.  The header is an SP_ERROR_MSG header, with the
   length being the length of two string submessages; the submessages
   are the body of the message, with each submessage being a message
   with an indicator of SP_ERROR_MSG, the first message having
   first message string and the second message having the second message
   string. */
extern void
sync_pipe_write_errmsgs_to_parent(int pipe_fd, const char *error_msg,
                                  const char *secondary_error_msg);

/** Has the parent signalled the child to stop? */
#define SIGNAL_PIPE_CTRL_ID_NONE "none"
#ifdef _WIN32
#define SIGNAL_PIPE_FORMAT "\\\\.\\pipe\\wireshark.%s.signal"
#endif

#endif /* sync_pipe.h */

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
