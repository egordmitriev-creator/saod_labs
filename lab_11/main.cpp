#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>
using namespace std;
//int block_size = 10;

class ArithmeticEncoder {
public:
    ArithmeticEncoder(int precision) : precision(precision) {}

    void encode(const string& data) {
        low = 0.0;
        high = 1.0;
        range_size = 1.0;

        for (char symbol : data) {
            
            // Вывод интервала перед обновлением
            cout << "Interval: [" << low << ", " << high << ")" << endl;
            // print_result(block_size);

            low = low + range_size * sum_probabilities(data, symbol);
            high = low + range_size * probability(data, symbol);
            range_size = high - low;
        }

        // Вывод финального интервала
        cout << "Final Interval: [" << low << ", " << high << ")" << endl;
        cout << endl;

        code = static_cast<unsigned int>(low * pow(2, precision));
    }

    void print_result(int block_size) const {
        cout << "Encoded Code (Decimal): " << low << endl;
        cout << "Encoded Code (Binary): " << bitset<32>(code) << endl;
        cout << endl;
        // Определите длину интервала после кодирования k символов
    }
    
    unsigned int get_code() const {
        return code;
    }

private:
    double sum_probabilities(const string& data, char symbol) const {
        double sum = 0.0;
        for (char s : data) {
            if (s < symbol) {
                sum += probability(data, s);
            }
        }
        return sum;
    }

    double probability(const string& data, char symbol) const {
        int count = 0;
        for (char s : data) {
            if (s == symbol) {
                count++;
            }
        }
        return static_cast<double>(count) / data.size();
    }
    
private:
    double low;
    double high;
    double range_size;
    unsigned int code;
    int precision;
};

int main() {
    // Чтение текста из файла
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    int block_size = 10;
    int precision = 32;

    vector<string> blocks;
    for (size_t i = 0; i < text.size(); i += block_size) {
        blocks.push_back(text.substr(i, block_size));
    }

    vector<unsigned int> encoded_codes;

    for (const auto& block : blocks) {
        ArithmeticEncoder encoder(precision);
        encoder.encode(block);
        encoder.print_result(block_size);
        encoded_codes.push_back(encoder.get_code());
    }

    // Оценка коэффициента сжатия
    double compression_ratio = static_cast<double>(encoded_codes.size() * precision) / (text.size() * 8) * 100;
    cout << "Compression: " << compression_ratio << "%" << endl;


    // // Определить зависимость коэффициента сжатия данных от длины блока
    // cout << "Compression for Different Block Sizes:" << endl;
    // for (int block_size = 50; block_size <= 200; block_size += 50) {
    //     vector<string> blocks;
    //     for (size_t i = 0; i < text.size(); i += block_size) {
    //         blocks.push_back(text.substr(i, block_size));
    //     }

    //     vector<unsigned int> encoded_codes;

    //     for (const auto& block : blocks) {
    //         ArithmeticEncoder encoder(precision);
    //         encoder.encode(block);
    //         encoded_codes.push_back(encoder.get_code());
    //     }

    //     double compression_ratio = static_cast<double>(encoded_codes.size() * precision) / (text.size() * 8) * 100;
    //     cout << "Block Size: " << block_size << ", Compression: " << compression_ratio << "%" << endl;
    // }

    return 0;
}