/*********************************************************
 *                     minunit.h                         *
 * DISTRIBUTE FREELY AS IF IN IN THE PUBLIC DOMAIN, WITH *
 * THE UNDERSTANDING  THAT IT COMES  WITH  ABSOLUTELY NO *
 * WARRANTY.                                             *
 *********************************************************/

/** \file: include/minunit.h 
 * \author Jera Design
 * \date Unknown
 *
 * \brief A very minimal unit test library.
 *
 * \see http://www.jera.com/techinfo/jtns/jtn002.html
 */

/** \def mu_assert
 * \brief Macro to assert equality in a unit test.
 *
 * This macro checks whether 'test' is a true value. If it is, then
 * the macro does nothing. Otherwise, it will pass a message as the
 * return value of the function in which the macro will be expanded.
 *
 * \param message This message will be the return value of whichever
 * function implements mu_assert. It should be a message to be sent
 * if the assertion fails.
 *
 * \param test This is the value being asserted. It should evaluate
 * to a true value in successful tests.
 */
 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)

 /** \def mu_run_test
  * \brief Macro to run a test.
  *
  * This macro is used to run a 'test' function, which should return
  * 0 if everything is alright. This macro should be included in functions
  * with a *char return type.
  * \param test A pointer to a function that resturns 0 if everything is
  * alright and a message (*char) if there's an error.
  */
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

/** \var int tests_run
 * \brief Global set to the amount of tests that ran.
 *
 * This variable gets increased when mu_run_test runs, and it should
 * hold the amount of tests ran at the end of the test program.
 * \see mu_run_test
 */
 extern int tests_run;