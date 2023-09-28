#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct YaleFormat {
	vector<T> values;
	vector<T> colIndeces;
	vector<T> rowDividers;
};

template<typename T>
class Matrix {
private:
	int rowSize;
	int colSize;
public:
	bool isYaleFormat;

	vector<vector<pair<int, T>>> dataLIL;
	YaleFormat<T> dataYale;

	Matrix(const int& m, const int& n) {
		isYaleFormat = false;
		rowSize = m;
		colSize = n;
		dataLIL = vector<vector<pair<int, T>>>(m, vector<pair<int, T>>());
	}

	void setValue(const int& i, const int& j, const T& val) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (isYaleFormat) {
			//???
		}
		else {
			vector<pair<int, T>> row = dataLIL[i];
			int k = 0;
			while (k < row.size()) {
				if (row[k].first > j) {
					break;
				}
				k++;
			}

			if (k == row.size()) {
				dataLIL[i].push_back(pair<int, T>(j, val));
			}
			else {
				dataLIL[i].insert(dataLIL[i].begin() + k, pair<int, T>(j, val));
			}
		}
	}

	T getValue(const int& i, const int& j) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (isYaleFormat) {
			// ???
		}
		else {
			for (pair<int, T> p : dataLIL[i]) {
				if (p.first == j) {
					return p.second;
				}
			}

			return 0;
		}
	}

	void display() {
		if (isYaleFormat) {
			// ???
		}
		else {
			for (int i = 0; i < rowSize; i++) {
				int k = 0;

				if (dataLIL[i].size()) {
					for (int j = 0; j < dataLIL[i].size(); j++) {
						while (k < dataLIL[i][j].first) {
							cout << 0 << '\t';
							k++;
						}

						cout << dataLIL[i][j].second << '\t';
						k++;
					}

					while (k < colSize) {
						cout << 0 << '\t';
						k++;
					}
				}
				else {
					for (int j = 0; j < colSize; j++) {
						cout << 0 << '\t';
					}
				}

				cout << endl;
			}
		}
	}
};