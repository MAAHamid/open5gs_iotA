#include "core.h"
#include "core_errno.h"
#include "core_general.h"
#include "core_debug.h"
#include "core_pkbuf.h"

#include "testutil.h"

#include "s1ap_message.h"

static void s1ap_test1(abts_case *tc, void *data)
{
    /* S1SetupRequest */
    char *payload[] = {
        "\x00\x11\x00\x2d\x00\x00\x04\x00\x3b\x00\x09\x00\x00\xf1\x10\x40\x54\xf6\x40\x10\x00\x3c\x40\x09\x03\x00\x4a\x4c\x54\x2d\x36\x32\x31\x00\x40\x00\x07\x00\x0c\x0e\x40\x00\xf1\x10\x00\x89\x40\x01\x00",
    };

    s1ap_message message;
    pkbuf_t *pkb;
    int result;

    pkb = pkbuf_alloc(0, S1AP_SDU_SIZE);
    ABTS_PTR_NOTNULL(tc, pkb);
    pkb->len = 49;
    memcpy(pkb->payload, payload[0], pkb->len);

    result = s1ap_decode_pdu(&message, pkb);
    ABTS_INT_EQUAL(tc, 0, result);
}

static void s1ap_test2(abts_case *tc, void *data)
{
    /* InitialUE(Attach Request) */
    char *payload[] = {
        "\x00\x0c\x40\x6f\x00\x00\x06\x00\x08\x00\x02\x00\x01\x00\x1a\x00\x3c\x3b\x17\xdf\x67\x5a\xa8\x05\x07\x41\x02\x0b\xf6\x00\xf1\x10\x00\x02\x01\x03\x00\x03\xe6\x05\xf0\x70\x00\x00\x10\x00\x05\x02\x15\xd0\x11\xd1\x52\x00\xf1\x10\x30\x39\x5c\x0a\x00\x31\x03\xe5\xe0\x34\x90\x11\x03\x57\x58\xa6\x5d\x01\x00\xe0\xc1\x00\x43\x00\x06\x00\x00\xf1\x10\x30\x39\x00\x64\x40\x08\x00\x00\xf1\x10\x8c\x33\x78\x20\x00\x86\x40\x01\x30\x00\x4b\x00\x07\x00\x00\xf1\x10\x00\x02\x01"
    };

    s1ap_message message;
    pkbuf_t *pkb;
    int result;

    pkb = pkbuf_alloc(0, S1AP_SDU_SIZE);
    ABTS_PTR_NOTNULL(tc, pkb);
    pkb->len = 115;
    memcpy(pkb->payload, payload[0], pkb->len);

    result = s1ap_decode_pdu(&message, pkb);
    ABTS_INT_EQUAL(tc, 0, result);
}

static void s1ap_test3(abts_case *tc, void *data)
{
    /* initial context setup response */
    char *payload[] = {
        "\x20\x09\x00\x25\x00\x00\x03\x00\x00\x40\x05\xc0\x02\x00\x00\xbf\x00\x08\x40\x02\x00\x01\x00\x33\x40\x0f\x00\x00\x32\x40\x0a\x0a\x1f\x0a\x01\x23\xc6\x01\x00\x09\x08"
    };

    s1ap_message message;
    pkbuf_t *pkb;
    int result;

    pkb = pkbuf_alloc(0, S1AP_SDU_SIZE);
    ABTS_PTR_NOTNULL(tc, pkb);
    pkb->len = 41;
    memcpy(pkb->payload, payload[0], pkb->len);

    result = s1ap_decode_pdu(&message, pkb);
    ABTS_INT_EQUAL(tc, 0, result);
}

abts_suite *test_s1ap(abts_suite *suite)
{
    suite = ADD_SUITE(suite)
    {
        extern int _decoder;
        d_trace_level(&_decoder, 100);
    }

    abts_run_test(suite, s1ap_test1, NULL);
    abts_run_test(suite, s1ap_test2, NULL);
    abts_run_test(suite, s1ap_test3, NULL);

    return suite;
}
