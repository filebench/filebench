#ifndef lint
#ifdef __GNUC__
#define ATTRIBUTE(attrs) __attribute__(attrs)
#else
#define ATTRIBUTE(attrs)
#endif
static char Rcs_Id[] ATTRIBUTE((used)) =
    "$Id: rdcctest.cc,v 1.7 2012-12-30 16:24:49-08 geoff Exp $";
#endif

/*
 * Test the random-distribution library.  Usage:
 *
 * rdcctest seed how_many distribution [params...]
 *
 * where:
 *
 *	seed	is the random seed.  If seed is zero, the package's
 *		automatic seed generator is used.
 *	how_many
 *		is how many random numbers to generate.
 *	distribution
 *		is the distribution to draw from (see below).
 *	params	are the parameters to the distribution (see below).
 *
 * Distributions supported:
 *
 *   iuniform	A uniform distribution of integers on the interval [p1, p2).
 *   uniform	A uniform distribution on the interval [p1, p2).
 *   exponential	Exponential with mean p1, default 1.
 *   erlang	p1-Erlang with mean p2.
 *   weibull	Weibull with shape parameter p1 and scale parameter p2.
 *   normal	Normal with mean p1 and standard deviation p2.
 *   lognormal	Lognormal with scale parameter p1 and shape parameter p2.
 *   triangular	Triangular on the interval (p1, p2) with mode at p3.
 *   empirical	p1 with probability p2, p3 with probability p4, ...,
 *		p(2n+1) with probability p(2n).  Actually, the
 *		"probabilities" are
 *              weights, and do not need to sum to 1.
 *   continuous_empirical
 *		p1 to p3 with probability p2, p3 to p5 with
 *		probability p4, ..., p(2n+1) to p(2n+2) with
 *		probability p(2n).  Actually, the "probabilities" are
 *		weights, and do not need to sum to 1.
 *
 * $Log: rdcctest.cc,v $
 * Revision 1.7  2012-12-30 16:24:49-08  geoff
 * Use gcc attributes to suppress warnings on Rcs_Id.
 *
 * Revision 1.6  2010-12-10 03:28:19-08  geoff
 * Support the new empirical_distribution interface.
 *
 * Revision 1.5  2010-06-24 19:29:38+12  geoff
 * Include string.h to get rid of some warnings.
 *
 * Revision 1.4  2008-07-25 16:34:01-07  geoff
 * Fix notation for intervals in commentary.
 *
 * Revision 1.3  2004/03/30 07:29:43  geoff
 * Document the program better, and allow the random seed to be
 * controlled for verification testing.
 *
 * Revision 1.2  2003/09/11 05:50:53  geoff
 * Use the standard namespace.
 *
 * Revision 1.1  2001/06/18 10:09:35  geoff
 * Initial revision
 *
 */

#include "randistrs.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

int			main(int argc, char* argv[]);
static void		usage();

#define SEED_PARAM	1		/* Offset of seed param in argv */
#define COUNT_PARAM	2		/* Offset of count param in argv */
#define DISTR_PARAM	3		/* Offset of distr param in argv */
#define PARAM_OFFSET	4		/* Offset of params in argv */

int main(
    int			argc,		/* Argument count */
    char*		argv[])		/* Argument vector */
    {
    if (argc <= PARAM_OFFSET)
	usage();

    int seed = atoi (argv[SEED_PARAM]);
    size_t how_many = atoi(argv[COUNT_PARAM]);

    size_t n_params = argc - PARAM_OFFSET;
    double* params = new double[n_params];

    mt_empirical_distribution* empirical = NULL;
    size_t needed_params = 0;		/* Number of params needed by distr */
    size_t n_probs = 0;			/* Number of empirical probabilites */

    for (size_t i = 0;  i < n_params;  i++)
	params[i] = atof(argv[i + PARAM_OFFSET]);

    if (strcmp(argv[DISTR_PARAM], "iuniform") == 0)
	needed_params = 2;
    else if (strcmp(argv[DISTR_PARAM], "uniform") == 0)
	needed_params = 2;
    else if (strcmp(argv[DISTR_PARAM], "exponential") == 0)
	needed_params = 1;
    else if (strcmp(argv[DISTR_PARAM], "erlang") == 0)
	{
	if (n_params < 2  ||  params[0] < 1.0)
	    usage();
	needed_params = 2;
	}
    else if (strcmp(argv[DISTR_PARAM], "weibull") == 0)
	needed_params = 2;
    else if (strcmp(argv[DISTR_PARAM], "normal") == 0)
	needed_params = 2;
    else if (strcmp(argv[DISTR_PARAM], "lognormal") == 0)
	needed_params = 2;
    else if (strcmp(argv[DISTR_PARAM], "triangular") == 0)
	needed_params = 3;
    else if (strcmp(argv[DISTR_PARAM], "empirical") == 0)
	{
	if (n_params % 2 != 0  ||  n_params < 4)
	    usage();

	n_probs = n_params / 2;
	vector<double> probs;
	vector<double> values;

	for (size_t i = 0;  i < n_probs;  i++)
	    {
	    values.push_back(params[i * 2]);
	    probs.push_back(params[i * 2 + 1]);
	    if (probs[i] < 0)
		{
		(void)fprintf(stderr, "rdcctest: negative probability given\n");
		exit(2);
		}
	    }
	values.push_back(0.0);
	needed_params = n_params;
	empirical = new mt_empirical_distribution(probs, values);
	}
    else if (strcmp(argv[DISTR_PARAM], "continuous_empirical") == 0)
	{
	if (n_params % 2 == 0  ||  n_params < 5)
	    usage();
	n_probs = (n_params - 1) / 2;
	vector<double> probs;
	vector<double> values;

	for (size_t i = 0;  i < n_probs;  i++)
	    {
	    values.push_back(params[i * 2]);
	    probs.push_back(params[i * 2 + 1]);
	    if (probs[i] < 0)
		{
		(void)fprintf(stderr, "rdcctest: negative probability given\n");
		exit(2);
		}
	    }
	values.push_back(params[n_probs * 2]);
	needed_params = n_params;
	empirical = new mt_empirical_distribution(probs, values);
	}
    else
	usage();

    if (n_params != needed_params)
	usage();

    /*
     * Create a generator and seed it.
     */
    mt_distribution distr(seed == 0);
    if (seed != 0)
	distr.seed32(seed);

    for (size_t i = 0;  i < how_many;  i++)
	{
	double ran_value = 0.0;
	if (strcmp(argv[DISTR_PARAM], "iuniform") == 0)
	    ran_value = distr.iuniform((long)params[0], (long)params[1]);
	else if (strcmp(argv[DISTR_PARAM], "uniform") == 0)
	    ran_value = distr.uniform(params[0], params[1]);
	else if (strcmp(argv[DISTR_PARAM], "exponential") == 0)
	    ran_value = distr.exponential(params[0]);
	else if (strcmp(argv[DISTR_PARAM], "erlang") == 0)
	    ran_value = distr.erlang((int) params[0], params[1]);
	else if (strcmp(argv[DISTR_PARAM], "weibull") == 0)
	    ran_value = distr.weibull(params[0], params[1]);
	else if (strcmp(argv[DISTR_PARAM], "normal") == 0)
	    ran_value = distr.normal(params[0], params[1]);
	else if (strcmp(argv[DISTR_PARAM], "lognormal") == 0)
	    ran_value = distr.lognormal(params[0], params[1]);
	else if (strcmp(argv[DISTR_PARAM], "triangular") == 0)
	    ran_value = distr.triangular(params[0], params[1], params[2]);
	else if (strcmp(argv[DISTR_PARAM], "empirical") == 0)
	    ran_value = empirical->double_empirical(distr);
	else if (strcmp(argv[DISTR_PARAM], "continuous_empirical") == 0)
	    ran_value = empirical->continuous_empirical(distr);
	cout << ran_value << '\n';
	}
    return 0;
    }

static void usage()
    {
    cerr << "Usage: rdcctest count distribution p0 ...\n";
    cerr << "Distributions:\n";
    cerr << "\tiuniform lower upper\n";
    cerr << "\tuniform lower upper\n";
    cerr << "\texponential mean\n";
    cerr << "\terlang p mean\n";
    cerr << "\tweibull shape scale\n";
    cerr << "\tnormal mean sigma\n";
    cerr << "\tlognormal shape scale\n";
    cerr << "\ttriangular lower upper mode\n";
    cerr << "\tempirical v0 p0 v1 p1 ... vn-1 pn-1\n";
    cerr << "\tcontinuous_empirical v0 p0 v1 p1 ... vn-1 pn-1 vn\n";
    exit(2);
    }
