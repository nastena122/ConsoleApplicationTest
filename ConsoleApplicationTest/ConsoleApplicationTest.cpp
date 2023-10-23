#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// Функция для вычисления скользящего среднего
template <typename T>
vector<T> simple_moving_average(const vector<T>& data, int window_size) {
    vector<T> moving_averages;
    for (int i = 0; i < data.size() - window_size + 1; ++i) {
        T sum = 0;
        for (int j = i; j < i + window_size; ++j) {
            sum += data[j];
        }
        moving_averages.push_back(sum / window_size);
    }
    return moving_averages;
}

int main() {
    // Генерация тестовых данных
    vector<double> data;
    for (int i = 0; i < 1000000; ++i) {
        data.push_back(static_cast<double>(i));
    }

    // Замер времени выполнения для разных длин окна и типов данных
    vector<int> window_sizes = { 4, 8, 16, 32, 64, 128 };

    for (int window_size : window_sizes) {
        auto start_time = chrono::high_resolution_clock::now();
        vector<double> result = simple_moving_average(data, window_size);
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << "Window size " << window_size << ": " << duration.count() << " ms" << endl;

        // Сохранение результатов в CSV-файл
        ofstream output_file("moving_average_results.csv");
        output_file << "Data, Moving Average" << endl;
        for (int i = 0; i < result.size(); ++i) {
            output_file << data[i] << "," << result[i] << endl;
        }
        output_file.close();
    }

    cout << "Saved in moving_average_results.csv" << endl;

    return 0;
}
