#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu,k)*exp(-mu)/(tgamma(k+1));
}

int main() {
    int number_events = 234;
    double mu_value = 3.11538;
    using namespace std;
    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    ofstream fout2("hist.txt");
    ofstream fout("histpoi.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    for ( unsigned int k = 0 ; k < zaehler.size (); ++ k ) {
        double poisson_value = poisson(mu_value,k);
        int output_poisson = number_events * poisson_value + 0.5;
        fout2 << k << " " << zaehler[k] << std::endl;
        fout << k << " " << zaehler[k] << " " << output_poisson << std::endl;
    }    
    fin.close();
    fout.close();
}
