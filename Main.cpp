#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

struct Matrix{
    int I;
    int J;
};

bool validate_stream(std::string& s,std::vector<double>& arr, int J){
    std::istringstream iss(s);
    double temp;
    if(iss.fail()){
        return false;
    }
    for(int i = 0; i < J; ++i){
        if(iss >> temp){
            arr.push_back(temp);
            if(i == J-1 && iss >> temp){
                return false;
            }
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

bool fill_up(std::istream& is, std::vector<std::vector<double>>& arr, Matrix& m){
    if(is) {
        std::string s;
        int index = 0;
        while(index < m.I && std::getline(is, s)){
            std::vector<double> row;
            if(validate_stream(s, row, m.J)){
                arr.push_back(row);
                ++index;
                continue;
            }
            else {
                std::cerr << "Zły format!\n";
                return false;
            }
        }
    }
    return true;
}

bool parse_dimensions(Matrix& m, std::string s){
    std::istringstream iss(s);
    int a, c;
    char b;
    if((iss >> a >> b >> c && b == 'x') && a > 0 && b > 0){
        m.I = a;
        m.J = c;
        return true;
    } else {
        return false;
    }
}

void debug_matrix(std::vector<std::vector<double>>& v){
    for(int i = 0; i < v.size(); ++i){
        for(int j = 0; j < v[i].size(); ++j){
            std::cout << v[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<double>> multiply(std::vector<std::vector<double>>& m1,std::vector<std::vector<double>>& m2){
    std::vector<std::vector<double>> ans;
    for(int i = 0; i < m1[0].size(); ++i){
        std::vector<double> row;
        for(int j = 0; j < m2.size(); ++j){
            double cell = 0;
            for(int k = 0; k < m1[0].size(); ++k){
                cell += m1[i][k]*m2[k][j];
            }
            row.push_back(cell);
        }
        ans.push_back(row);
    }
    return ans;
}

int main(){

    std::cout << "Podaj rozmiar macierzy 1\n";
    Matrix m1;
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::vector<double>> mat1;
    if(parse_dimensions(m1, s)){
        std::cout << "Napisz macierz\n";
        if(!fill_up(std::cin, mat1, m1))
            return 0;
    } else
        return 0;
    std::cout << "Podaj rozmiar macierzy 2\n";
    Matrix m2;
    std::string s2;
    std::getline(std::cin, s2);
    std::vector<std::vector<double>> mat2;
    if(parse_dimensions(m2, s2)){
        if(m1.J != m2.I){
            std::cout << "Rozmiary nie pozwalaja na przemnozenie!";
            return 0;
        }
        std::cout << "Napisz macierz\n";
        if(!fill_up(std::cin, mat2, m2))
            return 0;
    } else
        return 0;
    std::vector<std::vector<double>> ans = multiply(mat1, mat2);
    std::cout << "Wynik: \n";
    debug_matrix(ans);

    return 0;
}