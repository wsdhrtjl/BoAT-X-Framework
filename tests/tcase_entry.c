#include "check.h"

/* extern suite declaration */
extern  Suite * make_wallet_suite(void);
extern  Suite * make_ethereum_suite(void);
extern  Suite * make_utility_suite(void);

int main(int argc, char *argv[])
{
    SRunner *sr       = NULL;
    int failed_number = 0;
    
    /* new adding test case should create in here */
    Suite*  suite_wallet   = make_wallet_suite();
    Suite*  suite_ethereum = make_ethereum_suite();
    Suite*  suite_utility  = make_utility_suite();

     /* create srunner and add first suite to it.
        The first suite in a suite runner is always added in function srunner_create,
        here set suite_wallet as first adding suite. */
    sr = srunner_create(suite_wallet);
    /* set generate test log in running path */
    srunner_set_log(sr, "log.txt");
    /* add other suite to srunner, more test suite should be add in here */
    srunner_add_suite(sr, suite_ethereum);
    srunner_add_suite(sr, suite_utility);

    /* start to run all test case */
    srunner_run_all(sr, CK_NORMAL);
    /* get the failed unit test number */
    failed_number = srunner_ntests_failed(sr);

    srunner_free(sr);

    /* return failed unit number, return value can be used in CI, CI tools according
       to this return value determine the test is passed or not  */
	return failed_number;
}