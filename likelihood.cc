#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu,k)*exp(-mu)/(tgamma(k+1));
}

double prob(std::vector<int> daten, double mu) {
    double product = 1.0;
    for(int k : daten){
        product *= pow(mu,k)*exp(-mu)/(tgamma(k+1));
    }
    return product;
}

double probWithK(std::vector<int> daten) {
    double product = 1.0;
    for(int k : daten){
        product *= pow(k,k)*exp(-k)/(tgamma(k+1));
    }
    return product;
}

int main() {
    using namespace std;
    vector<int> daten;
    double given_mu = 3.11538;
    int chiDOF = 233;
    
    ifstream fin("datensumme.txt");
    ofstream fout("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    double test = prob(daten, given_mu);
    for(double mu = 0.0; mu < 6.1; mu+=0.1){
        double mu_probablity = prob(daten, mu);
        double mu_log = - 2.0 * log(prob(daten,mu));
        fout << mu << " " << mu_probablity << std::endl;
        fout2 << mu << " " << mu_log << std::endl;
        fout3 << mu << " " << mu_log + 2.0 * log(prob(daten,given_mu))  << std::endl;
    }
    double lambda = - 2.0 * log(prob(daten, given_mu)/probWithK(daten));
    double z_value = (lambda-chiDOF)/sqrt(2*chiDOF);
    std::cout << prob(daten,given_mu) <<std::endl;
    std::cout << lambda <<std::endl;
    std::cout << "z:" << z_value << std::endl;
    fin.close();
    fout.close();
    fout2.close();
    fout3.close();
}
