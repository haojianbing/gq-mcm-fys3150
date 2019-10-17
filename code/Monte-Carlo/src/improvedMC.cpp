#include "../include/mclib.h"

// Monte Carlo integration with spherical coordinates, where r is distributed along the exponential distribution.
double improvedMC(double infty,int MCsamples){
    double mc, var, fval; vec r1 = zeros<vec>(3); vec r2 = zeros<vec>(3); // Variable storage.

    double V = pow(M_PI,3)*pow(infty,6)/6; // Integration volume.

    // Initialize RNG (Mersenne Twister) in our intervals.
    mt19937::result_type seed = time(0);
    auto r_rand = bind(uniform_real_distribution<double>(0,1),mt19937(seed));
    auto costheta_rand = bind(uniform_real_distribution<double>(-1,1),mt19937(seed));
    auto phi_rand = bind(uniform_real_distribution<double>(0,2*M_PI),mt19937(seed));

    for (int i=0 ; i<MCsamples ; i++){
        // Fill vectors with random values in interval.
        r1(0) = -1.0/4 * log(1-r_rand()); r2(0) = -1.0/4 * log(1-r_rand());
        r1(1) = costheta_rand(); r2(1) = costheta_rand();
        r1(2) = phi_rand(); r2(2) = phi_rand();

        // Add function value to sum.
        mc += f2(r1,r2);
        var += f2(r1,r2) * f2(r1,r2);
    }
    // Find variance
    var = var/MCsamples-(mc/MCsamples)*(mc/MCsamples);
    // Find mean and multiply by integration volume.
    mc = (mc/MCsamples)*2*2*(2*M_PI)*(2*M_PI)/16;

    // Printing the variance.
    cout << "Variance is: " << var << endl;

    return mc;
}