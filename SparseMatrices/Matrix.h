#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct YaleFormat {
	vector<T> values;
	vector<int> colIndeces;
	vector<int> rowDividers;

	YaleFormat<T>() {}
};

template<typename T>
class Matrix {
private:
	int rowSize;
	int colSize;
	bool hasYaleFormat;
	vector<vector<pair<int, T>>> dataLIL;
	YaleFormat<T> dataYale;
public:
	Matrix(const int& m, const int& n) {
		hasYaleFormat = false;
		rowSize = m;
		colSize = n;
		dataLIL = vector<vector<pair<int, T>>>(m, vector<pair<int, T>>());
		dataYale = YaleFormat<T>();
	}

	void setValue(const int& i, const int& j, const T& val) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (hasYaleFormat) {
			convertFromYale();
		}
		
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
		} else {
			dataLIL[i].insert(dataLIL[i].begin() + k, pair<int, T>(j, val));
		}
	}

	T getValue(const int& i, const int& j) {
		if (i < 0 || i >= rowSize || j < 0 || j >= colSize) {
			throw invalid_argument("Indeces out of bounds");
		}

		if (hasYaleFormat) {
			convertFromYale();
		}
		
		for (pair<int, T> p : dataLIL[i]) {
			if (p.first == j) {
				return p.second;
			}
		}

		return 0;
	}

public:
	void convert() {
		if (hasYaleFormat) {
			convertFromYale();
		} else {
			convertToYale();
		}
	}

private:
	void convertToYale() {
		dataYale = YaleFormat<T>();
		hasYaleFormat = true;

		int k = 0;
		for (int i = 0; i < rowSize; i++) {
			dataYale.rowDividers.push_back(k);

			for (auto p : dataLIL[i]) {
				dataYale.colIndeces.push_back(p.first);
				dataYale.values.push_back(p.second);
				k++;
			}
		}

		dataYale.rowDividers.push_back(k);

		dataLIL = vector<vector<pair<int, T>>>(rowSize, vector<pair<int, T>>());
	}

	void convertFromYale() {
		dataLIL = vector<vector<pair<int, T>>>(rowSize, vector<pair<int, T>>());
		hasYaleFormat = false;

		for (int i = 0; i < dataYale.rowDividers.size() - 1; i++) {
			for (int j = dataYale.rowDividers[i]; j < dataYale.rowDividers[i + 1]; j++) {
				dataLIL[i].push_back(pair<int, T>(dataYale.colIndeces[j], dataYale.values[j]));
			}
		}

		dataYale = YaleFormat<T>();
	}

public:
	void display() {
		if (hasYaleFormat) {
			convertFromYale();
		}
		
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
};